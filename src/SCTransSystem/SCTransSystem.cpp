/*
 * SCTransSystem.cpp
 *
 *  Created on: 10-Jun-2015
 *      Author: jaganmohini
 */

#include "SCTransSystem.h"
#include <boost/foreach.hpp>
#include <boost/assert.hpp>
#include <boost/tokenizer.hpp>

typedef std::tuple<faudes::Idx ,std::tuple<std::vector<faudes::Idx>,bool>> newstateinfo;

struct newstateinfocompare{
	bool operator() (const newstateinfo one, const newstateinfo two) const
		{
		bool first = std::get<1>(std::get<1>(one));
		bool second = std::get<1>(std::get<1>(two));
		std::vector<faudes::Idx> firstset = std::get<0>(std::get<1>(one));
		std::vector<faudes::Idx> secondset = std::get<0>(std::get<1>(two));
		if(first!=second)
			return first<second;
		else
			return firstset<secondset;
//			if(std::get<1>(std::get<1>(*one))!=std::get<1>(std::get<1>(*two)))
//			return (std::get<1>(*one))<(std::get<1>(*two));
		}
};


 SCTransSystem::SCTransSystem(Program& P, z3::solver& s):mProgram(P), mSolver(s) {
	 mMerged = new faudes::Generator();
}

z3::expr SCTransSystem::GetEndStateAssertionFromWord(std::string afaword)
{
	std::string lastsym;
	std::map<std::string,z3::expr> assnMap = mProgram.GetAssnMapForAllProcesses();
	boost::char_separator<char> sep(".");
	boost::tokenizer<boost::char_separator<char>> tokens1(afaword, sep);
		for(const std::string& sym: tokens1){
			lastsym=sym;
			break;
		}
	BOOST_ASSERT_MSG(assnMap.find(lastsym)!=assnMap.end(),"Some serious issue as the last char must be the one where assn is defined");
	return assnMap.find(lastsym)->second;

}

void SCTransSystem::BuildSCTS(faudes::Generator& lGenerator){
	std::vector<faudes::Generator*> automata= mProgram.GetSpecOfAllProcesses();
	std::map<std::string,z3::expr> assnMap = mProgram.GetAssnMapForAllProcesses();


	FA_Merge(automata,assnMap,lGenerator);
	//Now reverse the generator..
	faudes::LanguageReverse(lGenerator);
	BOOST_ASSERT_MSG(!faudes::IsEmptyLanguage(lGenerator), " Some seriour error, merged language must not be empty");
	mMerged->Assign(lGenerator);//ARE we really using mMerged variable anywhere?? if not.. cant we simply remove it..
	//std::cout<<"Merged done"<<std::endl;

	//lGenerator is already reversed shuffle automata..
#ifdef DBGPRNT
		std::cout<<"Is deterministic "<<mMerged->deterministic<<std::endl;
#endif
		/*FILE* OUT;
					OUT=fopen("try.dot","w");
					BOOST_ASSERT_MSG(OUT!=NULL,"Error");
					fa_dot(OUT,mMerged);
					fclose(OUT);*/

/*
		struct fa* forreverse = fa_clone(mMerged);
		reverseInPlace(forreverse);
*/
//		mMerged->deterministic=0;
//		mMerged->minimal=0;
//		fa_minimize(mMerged);//For some examples generated FA is Non deterministic hence we need to make it deterministic
				//minimiation make it deterministic but we can also separately call determinize which is not exported from fa
				//library yet.. but I am doing this shortcut for checking the correctness .. speed can be improved later.
/*		return forreverse ;//return reversed of merged FA..*/
}

void SCTransSystem::FA_Merge(std::vector<faudes::Generator*>& autset,std::map<std::string,z3::expr>& assnMap, faudes::Generator& lGenerator)
{
	std::vector<faudes::Idx> initset;
	std::map<faudes::Idx, z3::expr> stateAssnMap;

	//A small thing; here automata vector wills tart from 1.. But we dont want this to happen..
		//hence create another compact vector from 0 to tid-1.
	for(int i=1; i<=mProgram.mNumThds;i++)
		initset.push_back(autset[i]->InitState());

//add all symbols to generator

	BOOST_FOREACH(auto t, mProgram.mAllSyms){
		//add events
		lGenerator.InsEvent(t);
	}
	//Should I add fence instructions as well..Ifff Sc reasongin is invoked on a program with fence
	//instruction then this will be aproblem..So may be dont do right now..

	std::map<newstateinfo, newstateinfo, newstateinfocompare> seenmap;
		//create a new state, init
		faudes::Idx init = lGenerator.InsState();
		lGenerator.SetInitState(init);
		faudes::Idx last=init;
    //lGenerator.SetMarkedState(st.str());
		//set init as initial state of merged
		//now for each character in mProgram.mInitString create sequential transitions from init..by adding new states.
		//and transitions .. the last state will be added to newstatinfo object create later..
		for(std::string::iterator it = mProgram.mInitString.begin();it!=mProgram.mInitString.end();it++)
		{
			char sym = *it;
			std::string symstr(1,sym);
			faudes::Idx curr = lGenerator.InsState();
			lGenerator.SetTransition(last,lGenerator.EventIndex(symstr),curr);
			last=curr;
		}

		//map last to initset
		newstateinfo initinfo;
		std::get<0>(initinfo) = last;
		std::get<0>(std::get<1>(initinfo)) = initset;
		std::get<1>(std::get<1>(initinfo)) = false;
		//initset must be non-accepting (some weak link here) so set bool as false.
		seenmap[initinfo]=initinfo;
		//put init to a worklist, arraylist of struct autstate*
				std::list<newstateinfo> worklist;
				worklist.push_back(initinfo);
				while(worklist.size()!=0)
				{
					newstateinfo picked = worklist.front();
					worklist.pop_front();
					//get state of shuffled automaton.
					faudes::Idx shuffstate = std::get<0>(picked);
					std::vector<faudes::Idx> productset = std::get<0>(std::get<1>(picked));
					//no need to extract bool here..
					for(int k=0;k<productset.size();k++)
					{
						faudes::Idx procstate=productset[k];
						faudes::Generator* procaut=autset[k+1];//because auts are stored tid wise.. not from0
						for(faudes::TransSet::Iterator lit = procaut->TransRelBegin(procstate);lit!=procaut->TransRelEnd(procstate);lit++)
						{
							std::string searched(procaut->EventName(lit->Ev));
							//find the destination state
							faudes::Idx dest = lit->X2;
							//struct autstate* dest = trans.to;
							//construct new reachable product states set
							std::vector<faudes::Idx> newproductset = productset;
							newproductset[k]=dest;
							//check if the new product set is in seenmap
							newstateinfo newstepstateinfo;
							//before that check if this transition was assertion causing one and hence this state becomes accepting state as well.
							bool isacc=false;
							if(assnMap.find(searched)!=assnMap.end()){
								//means set this as accepting
								isacc=true;
								std::get<1>(std::get<1>(newstepstateinfo))=true;
							}else
								std::get<1>(std::get<1>(newstepstateinfo))=false;

							std::get<0>(std::get<1>(newstepstateinfo))=newproductset;
							faudes::Idx newshuffledstate=-1;
							if(seenmap.find(newstepstateinfo)!=seenmap.end()){
								//means the key was found..and accept/nonaccept was also matched
								//std::cout<<"No new element is added "<<std::endl;
								//get the associated shuffled state.
								newstepstateinfo = seenmap[newstepstateinfo];
								newshuffledstate = std::get<0>(newstepstateinfo);
								if(assnMap.find(searched)!=assnMap.end()){
									BOOST_ASSERT_MSG(lGenerator.MarkedStates().Find(newshuffledstate)!=lGenerator.MarkedStates().End(),"THis must have been set earlier otherwise serious error");
								}
							}else
							{
								//std::cout<<"New element is added "<<std::endl;
								//else newstepstateinfo was correctly allocated..
								//create a new state in shuffled automaton
								newshuffledstate = lGenerator.InsState();
								if(assnMap.find(searched)!=assnMap.end()){//check if the transition caused by this symbol by this procstate causes it to reach to assertion point
									//means key found
									z3::expr ex = assnMap.find(searched)->second;
									lGenerator.SetMarkedState(newshuffledstate);
									//mShuffautAssnMap.insert(std::make_pair(newshuffledstate,ex));
									//No need to do this now as we can get it from the last character of
									//the trace.. for TSO/PSO we will need this variable in program object
								}
									// No need to do this newshuffledstate->accept=0;
								std::get<0>(newstepstateinfo) = newshuffledstate;
								//insert it to seenmap as well as in worklist
								seenmap[newstepstateinfo]=newstepstateinfo;
								worklist.push_back(newstepstateinfo);
							}
							//add a transition from shuffstate to this shuffled state with label extracted from this transition
							//std::cout<<"Inserting edge on "<<searched<<" from "<<shuffstate<<" to "<<newshuffledstate<<std::endl;
							lGenerator.SetTransition(shuffstate,lGenerator.EventIndex(searched),newshuffledstate);
						}
					}
				}
#ifdef DBGPRNT
				//minimize automaton and then return it.
/*
				FILE *fp;
				fp = fopen("./originalMerged.dot", "w");
				BOOST_ASSERT_MSG(fp!=NULL,"Can't open input file in.list!\n");

				//no need to determinize here as by construction it is determinzed;
				fa_dot(fp,merged);
				fclose(fp);
*/
#endif


}
/*

std::tuple<bool,z3::expr> SCTransSystem::GetAcceptAssn(std::set<struct autstate*, newsetofstatescomparator>&  productset, std::map<struct autstate*, z3::expr>& stateAssnMap)
{
	bool found=false;
	z3::context& ctx = mSolver.ctx();
	z3::expr trueexp = ctx.bool_val(true);
	BOOST_FOREACH(struct autstate* st, productset)
		{
			if(stateAssnMap.find(st)!=stateAssnMap.end())
			{
				found=true;
				z3::expr ex = stateAssnMap.find(st)->second;
				trueexp = trueexp && ex;
			}
		}
	if(found==false)
		return std::tuple<bool,z3::expr>(false,trueexp);
	else
		return std::tuple<bool,z3::expr>(true,trueexp.simplify());
}*/

SCTransSystem::~SCTransSystem() {


}

