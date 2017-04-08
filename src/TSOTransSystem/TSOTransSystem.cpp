#include "../AFA/AFAState.h"
//another strange behaviour.. putting AFAState.h after TSOTransSystem also produces lot of errors..
#include "TSOTransSystem.h"
#include <boost/tokenizer.hpp>
#include <algorithm>
bool operator<(const POGenInfo& c1, const POGenInfo &c2){
	if(c1.mRest==c2.mRest)
		if(c1.mPO==c2.mPO)
			if(c1.mBuffInfo==c2.mBuffInfo)
				if(c1.mLastSym==c2.mLastSym)
					return c1.mCSinfo<c2.mCSinfo;
				else
					return c1.mLastSym<c2.mLastSym;
			else
				return c1.mBuffInfo<c2.mBuffInfo;
		else
			return c1.mPO<c2.mPO;
	else
		return c1.mRest<c2.mRest;
}

TSOTransSystem::TSOTransSystem(Program& prog,z3::solver& s): mProgram(prog), mSolver(s)
{
mTSOProgram = new Program((*mProgram.mFileName).c_str(),mProgram.mCtx,mProgram.mParser);
mTSOProgram->mGlobalVars=mProgram.mGlobalVars;
mTSOProgram->mInitString=mProgram.mInitString;
//Following three things are getting copied from origina program as they keep on updating based
//on buffer bound analysis(incremental)
mTSOChangedWriteReadSymbmap.insert(mProgram.mChangedWriteReadSymbmap.begin(),mProgram.mChangedWriteReadSymbmap.end());
mTSOExprToSymbMap.insert(mProgram.mExprToSymbMap.begin(),mProgram.mExprToSymbMap.end());
mTSONewOldSymbMap.insert(mProgram.mNewOldSymbMap.begin(),mProgram.mNewOldSymbMap.end());
//SANITY CHECK: Make sure that you have copied everythign important from original program to this one..
}

std::set<SymStatePair> TSOTransSystem::StepConcrete(int tid, const TSOState& st, faudes::Generator* lgenerator)
{
	std::set<SymStatePair> nextsymstates;


	//get the next instruction to be executed by tid based on its control state..
	//BOOST_ASSERT_MSG(st.getCState(tid)!=NULL,"Some serious issue as control state of a process should be valid");
	faudes::Idx current = st.getCState(tid);

	//for each next state from thi scontrol lstate..find corresponding labels..
	//then do a case analysis on label..
	//if read
	//if write
	//if assume
	//if fence
	//if sfence (in case of PSO)
	for(faudes::TransSet::Iterator lit = lgenerator->TransRelBegin(current);lit!=lgenerator->TransRelEnd(current);lit++)
	{
		std::string sym(lgenerator->EventName(lit->Ev));
		faudes::Idx dest = lit->X2;
		BOOST_ASSERT_MSG(mProgram.mSymType.find(sym)!=mProgram.mSymType.end(),"Some serious issue");
		if(mProgram.mSymType[sym].compare("read")==0)
		{

			std::tuple<z3::expr,z3::expr> pr = mProgram.mRWLHRHMap.find(sym)->second;
			z3::expr lhs=std::get<0>(pr);
			std::stringstream str;
			str<<lhs;
			std::string lhsstr=str.str();
			str.str("");
			str<<std::get<1>(pr);
			std::string rhsstr=str.str();
			//create a new state copying the current one..
			TSOState newst(st);
			//change control state to dest in new one..
			newst.setCState(tid,dest);
			newst.setTransSym(tid,sym);//NOTE here we are keeping the sym from origina program..
			//because only this can be used to tell if the resultant state is accepting or not..

			//two cases can happen based on if the write was present in the buffer or not??
			bool res=false;
			std::string foundsym="";
			z3::expr rhs=GetLastWrite(tid, rhsstr, st, res, foundsym);
			//std::cout<<"Checking if "<<rhsstr<<" is present in buffer "<<std::endl;
			if(res)
			{
				//check if a symbol with lhs as lhsstr and rhs as rhs is present or not..
				std::tuple<z3::expr,z3::expr,int> ExprPairtid=std::make_tuple(lhs,rhs,tid);
				std::pair<z3::expr,z3::expr> ExprPair=std::make_pair(lhs,rhs);
				std::string newsym;
				if(mTSOExprToSymbMap.find(ExprPairtid)==mTSOExprToSymbMap.end())
				{
					//assign a new symbol to this stuff..
					int t;
					if(mTSOChangedWriteReadSymbmap.find(sym)==mTSOChangedWriteReadSymbmap.end())
						t=1;
					else
						t=mTSOChangedWriteReadSymbmap[sym];
					mTSOChangedWriteReadSymbmap[sym]=t+1;
					//also add in programs same variable..
					mProgram.mChangedWriteReadSymbmap[sym]=t+1;
					newsym=sym+std::to_string(t);
					mTSOExprToSymbMap.insert(std::make_pair(ExprPairtid,newsym));
					mProgram.mExprToSymbMap.insert(std::make_pair(ExprPairtid,newsym));
					mTSONewOldSymbMap[newsym]=sym;
					mProgram.mNewOldSymbMap[newsym]=sym;
					//add newsymbol and substituted pr.second to the new program object..
					mTSOProgram->mRWLHRHMap.insert(std::make_pair(newsym,ExprPair));
					mTSOProgram->mAllSyms.push_back(newsym);
					mTSOProgram->mSymType[newsym]="read";
#ifdef DBG
					std::cout<<mTSOProgram->mAllSyms.size()<<"Added local read "<<lhs<<"="<<rhs<<std::endl;
#endif

				}else
				{
					//As a result of keeping a copy of mExprToSymbMap, and others in global program object
					//it is possible that this was copied and hence found but not added in this tso's object

					newsym=mTSOExprToSymbMap.find(ExprPairtid)->second;
					if(mTSOProgram->mRWLHRHMap.find(newsym)==mTSOProgram->mRWLHRHMap.end())
					{
						mTSOProgram->mRWLHRHMap.insert(std::make_pair(newsym,ExprPair));
						mTSOProgram->mAllSyms.push_back(newsym);
						mTSOProgram->mSymType[newsym]="read";//Blunder here: I was setting it as write..
#ifdef DBG
						std::cout<<mTSOProgram->mAllSyms.size()<<"Added local read "<<lhs<<"="<<rhs<<std::endl;
#endif
					}
				}
				std::set<std::string> symset;
				symset.insert(newsym);
//				std::cout<<"Inserting sym as "<<newsym<<std::endl;
				nextsymstates.insert(std::make_pair(symset,newst));
				//ADDED Later: to have rfi information stored.. note that this is
				//a case of local rf read.. we want to encode it somehow..
				mLocalRFMap[newsym]=foundsym;
			}else
			{
				//means no symbol present in buffer of tid.. just put this symbol as such..
				//put same entries in newprogram object as ni old..only ifnot there already
				//This was a bug found later when I was not checking if vector mAllSyms has
				//sym already been added or not.. as a result for petrson I was adding 3000 entries

				if(mTSOProgram->mRWLHRHMap.find(sym)==mTSOProgram->mRWLHRHMap.end())
				{
					mTSOProgram->mRWLHRHMap.insert(std::make_pair(sym,mProgram.mRWLHRHMap.find(sym)->second));
					mTSOProgram->mSymType[sym]=mProgram.mSymType[sym];
					mTSOProgram->mAllSyms.push_back(sym);
				}
				std::set<std::string> symset;
				symset.insert(sym);
//				std::cout<<"Inserting sym as "<<sym<<std::endl;

				nextsymstates.insert(std::make_pair(symset,newst));

			}
			//add sym and nestate to the set of symstate pair to be returned later.

		}else if(mProgram.mSymType[sym].compare("write")==0)
		{//if buff bound is zero then also do the following.. as it should emulate SC..
//			std::cout<<"Bufff bound is "<<st.mBuffBound<<std::endl;
			if(mProgram.mLocalWrites.find(sym)!=mProgram.mLocalWrites.end() || st.mBuffBound==0)
			{
				//means it is local write..
				//put in the buffer directly.
				TSOState newst(st);
				//change control state to dest in new one
				newst.setCState(tid,dest);
				newst.setTransSym(tid,sym);
				std::set<std::string> symset;
				symset.insert(sym);
				nextsymstates.insert(std::make_pair(symset,newst));
				if(mTSOProgram->mRWLHRHMap.find(sym)==mTSOProgram->mRWLHRHMap.end())
				{
					mTSOProgram->mRWLHRHMap.insert(std::make_pair(sym,mProgram.mRWLHRHMap.find(sym)->second));
					mTSOProgram->mAllSyms.push_back(sym);
					mTSOProgram->mSymType[sym]="write";//Blunder here: I was setting it as write..
					//std::cout<<mTSOProgram->mAllSyms.size()<<"Added local read "<<lhs<<"="<<rhs<<std::endl;
				}

			}
			//proceed only if buffer is not full
			else if(!st.isBuffFull(tid))
			{
			//call ChangedWriteop with sym and current state..
				TSOState newst(st);
				std::pair<std::set<std::string>,std::set<std::string>> writereadsyms = GetNewWriteReadSyms(sym, tid, st,newst);
			//it will return with added bookkeeping.. and a single writesym and a set of read symbols..
				std::set<std::string> writesymset=std::get<0>(writereadsyms);
				BOOST_ASSERT_MSG(writesymset.size()==1,"Some serious error , look at it carefully");
				std::string writesym=*(writesymset.begin());//as this set must be singleton..
				std::set<std::string> readsymset=std::get<1>(writereadsyms);
			//change control state to dest in new one

				newst.setCState(tid,dest);
				newst.setTransSym(tid,sym);
				//IMP: we have to set the changed LI request (if any also in the same piece)
			//add newsym to the buffer
				newst.enqueToBuffer(tid,writesym);
			//return epsilon and new state..
				nextsymstates.insert(std::make_pair(readsymset,newst));
			}

		}else if(mProgram.mSymType[sym].compare("assume")==0)
		{
			//same as in read above..
			//put same entries in newprogram object as ni old..only if not added earlier..
			if(mTSOProgram->mAssumeLHRHMap.find(sym)==mTSOProgram->mAssumeLHRHMap.end())
			{
				mTSOProgram->mAssumeLHRHMap.insert(std::make_pair(sym,mProgram.mAssumeLHRHMap.find(sym)->second));
				mTSOProgram->mRevAssumeLHRHMap.insert(std::make_pair(mProgram.mAssumeLHRHMap.find(sym)->second,sym));
				mTSOProgram->mSymType[sym]=mProgram.mSymType[sym];
				mTSOProgram->mAllSyms.push_back(sym);

			}
			//create a new state copying the current one..
			TSOState newst(st);
			//change control state to dest in new one..
			newst.setCState(tid,dest);
			newst.setTransSym(tid,sym);
			//add sym and nestate to the set of symstate pair to be returned later.
			std::set<std::string> symset;
			symset.insert(sym);
			nextsymstates.insert(std::make_pair(symset,newst));
		}else if(mProgram.mSymType[sym].compare("lcas")==0)
		{
			//BOOST_ASSERT_MSG(false,"Op sem of LCAS under TSO is not sure. So lets keep it for future work");
			//Implementing lcas-- semantics is.. before executing it buffer must be empty
			//and write must go to the history which means lcas must go to the history as well.
			//proceed only if buffer is emtpy..
			if(st.isBuffEmpty(tid))
			{
				//same as in read above..
				//put same entries in newprogram object as ni old..
				if(mTSOProgram->mCASLHRHMap.find(sym)==mTSOProgram->mCASLHRHMap.end())
				{
					mTSOProgram->mCASLHRHMap.insert(std::make_pair(sym,mProgram.mCASLHRHMap.find(sym)->second));
					mTSOProgram->mSymType[sym]=mProgram.mSymType[sym];
					mTSOProgram->mAllSyms.push_back(sym);
//					std::cout<<mTSOProgram->mAllSyms.size()<<std::endl;
				}
				//create a new state copying the current one..
				//change control state to dest in new one..
				//return sym and new state..
				//change the control state only..
				TSOState newst(st);
				newst.setCState(tid,dest);
				newst.setTransSym(tid,sym);
				//also reset the LI index for each variable of this tid.
				newst.initAllIndex(tid);
				//return lcas and new state..so that lcas can be put in the history.
				std::set<std::string> symset;
				symset.insert(sym);
				nextsymstates.insert(std::make_pair(symset,newst));
			}

		}else if(mProgram.mSymType[sym].compare("rfence")==0)//for w-r fence
		{
			//proceed only if buffer is emtpy..
			if(st.isBuffEmpty(tid))
			{
				//change the control state only..
				TSOState newst(st);
				newst.setCState(tid,dest);
				newst.setTransSym(tid,sym);
				//also reset the LI index for each variable of this tid.
				newst.initAllIndex(tid);
				//return epsilon and new state..
				std::set<std::string> symset;
				//empty set represents epsilon
				nextsymstates.insert(std::make_pair(symset,newst));
			}

		}else if(mProgram.mSymType[sym].compare("wfence")==0)//for w-w fence
		{
			//TODO for PSO mem model
			BOOST_ASSERT_MSG(false,"No sfence instruction for TSO memory model");
		}
		else
			BOOST_ASSERT_MSG(false,"Some serious error happend");

	}


return nextsymstates;
}


std::pair<std::set<std::string>,std::set<std::string>> TSOTransSystem::GetNewWriteReadSyms(std::string oldsym, int tid, const TSOState& st, TSOState& newst)
{
	//from mProgram object get the z3 exprs left and write corresponding to oldsym
	BOOST_ASSERT_MSG(mProgram.mRWLHRHMap.find(oldsym)!=mProgram.mRWLHRHMap.end()," Some serious error");
	std::tuple<z3::expr,z3::expr> pr = mProgram.mRWLHRHMap.find(oldsym)->second;
	std::set<std::string> writesymset;
	std::set<std::string> readsymset;
	//first part of the pair is lhs (i.e. variable.. and the second part is the expressions)
	//we will keep the first part same.. and process the second part..
	//1. find the variables from the expressions pr.second
//	std::cout<<"Getting free var of "<<std::get<1>(pr)<<std::endl;
	std::set<z3::expr,z3comparator> freevars = mProgram.HelperGetFreeVars(std::get<1>(pr));
	std::map<std::string, int> mapstr;
	z3::expr_vector src(mProgram.mCtx),dest(mProgram.mCtx);

	//2. for each of these variables get the current LI for
	for(z3::expr var: freevars)
	{
//		std::cout<<"Found free var"<<std::endl;
		//get string form of var..
		std::stringstream streams;
		streams<<var;
		std::string varstr(streams.str());
//		std::cout<<"Free var is "<<varstr<<std::endl;
		//check the lastinstance of var from tid
		int li = st.getLastIndex(tid,varstr);
		//increase it by one and set it back..
		//IMP: We can safely wrap this integer around.. when??? when it reaches the buffer bound..
		if(li==st.mBuffBound)
			li=1;
		else if(li==-1) //means first access, or this is not set yet..
			li=1;
		else
			li=li+1;
		newst.setLastIndex(tid,varstr,li);
		//add var string and int to a map
		mapstr[varstr]=li;
		//get z3::expr for varsting#int concatenated.. if not already create a new one..
		std::string concatstr(varstr+std::to_string(li));
		z3::expr newexp = mProgram.AddIfNot(concatstr);
		//we have to create a read isntruction of the form var:=newexp and add to set of symbols..
//		std::cout<<"About to inserting read expr "<<newexp<<"="<<var<<" with label as "<<concatstr<<std::endl;
		if(mTSOProgram->mRWLHRHMap.find(concatstr)==mTSOProgram->mRWLHRHMap.end())
		{
			mTSOProgram->mRWLHRHMap.insert(std::make_pair(concatstr,std::make_pair(newexp,var)));
			mTSOProgram->mAllSyms.push_back(concatstr);
			mTSOProgram->mSymType[concatstr]="read";
#ifdef DBG
			std::cout<<mTSOProgram->mAllSyms.size()<<"inserting read expr "<<newexp<<"="<<var<<" with label as "<<concatstr<<std::endl;
#endif
			readsymset.insert(concatstr);
		}else
		{
			//means this read has been added earlier..[here we give the symbol same name as of local var]
			//so make sure that name of local var do not clash with the name of some label in the
			//original program
//			std::cout<<"Added earlier "<<mTSOProgram->mRWLHRHMap.find(concatstr)
			readsymset.insert(concatstr);
		}
		//create a substitution order saying replace z3::expr with new z3::expr (concatented one)
		src.push_back(var);
		dest.push_back(newexp);
	}
	if(!freevars.empty())
	{//when done check if oldsym, varstring int map is already seen or not..
//		std::cout<<" free var of "<<oldsym<<" is not empty "<<std::endl;
		z3::expr rhs(std::get<1>(pr));
		z3::expr l3(rhs.substitute(src,dest));
		std::tuple<z3::expr,z3::expr,int> ExprAssntid=std::make_tuple(std::get<0>(pr),l3,tid);
		std::pair<z3::expr,z3::expr> ExprAssn=std::make_pair(std::get<0>(pr),l3);
//		std::cout<<"Modified expr is "<<l3<<std::endl;
//		std::cout<<"Searching for expression "<<std::get<0>(pr)<<"="<<l3<<std::endl;
		if(mTSOExprToSymbMap.find(ExprAssntid)==mTSOExprToSymbMap.end())
		{
//			std::cout<<"Expression "<<std::get<0>(pr)<<"="<<l3<<" not found "<<std::endl;
			//assign a new symbol to this stuff..
			int t;
			if(mTSOChangedWriteReadSymbmap.find(oldsym)==mTSOChangedWriteReadSymbmap.end())
				t=1;
			else
				t=mTSOChangedWriteReadSymbmap[oldsym];
			mTSOChangedWriteReadSymbmap[oldsym]=t+1;
			mProgram.mChangedWriteReadSymbmap[oldsym]=t+1;
			std::string newsym(oldsym+std::to_string(t));
			mTSOExprToSymbMap.insert(std::make_pair(ExprAssntid,newsym));
			mProgram.mExprToSymbMap.insert(std::make_pair(ExprAssntid,newsym));
			//we should add this write to newoldsymb map..
			mTSONewOldSymbMap[newsym]=oldsym;
			mProgram.mNewOldSymbMap[newsym]=oldsym;
#ifdef DBG
			std::cout<<mTSOProgram->mAllSyms.size()<<"inserting write expr "<<std::get<0>(pr)<<"="<<l3<<" with label as "<<newsym<<std::endl;
#endif

			//mNewOldSymbMap[newsym]=oldsym;IMP: not putting them in mNewOldSymbMap;;on purpose
			//This is fine because we dont want to reason with l_3=l kind of assignments later..
			//so it wont matter whether we put it in global map or not..
			//Essentially we dont satisfy the invariant that for every mExprToSymbMap var we have
			//corresponding old symbol that generated this.. because this particular assignment
			//does not correspond to any old..
			//add newsymbol and substituted pr.second to the new program object..
			mTSOProgram->mRWLHRHMap.insert(std::make_pair(newsym,std::make_pair(std::get<0>(pr),l3)));
			mTSOProgram->mAllSyms.push_back(newsym);
			mTSOProgram->mSymType[newsym]="write";
			//return newsymbol
//			std::cout<<"inserting sym as "<<newsym<<std::endl;
			writesymset.insert(newsym);
		}else
		{//else
//			std::cout<<"Expression "<<std::get<0>(pr)<<"="<<l3<<" was found "<<std::endl;
			//New thing scomes up now because of copying tso's mExprToSymbMap from global
			//it is possible that ExprAssn found in mExprTosSymbMap but was copied earlier..
			//so if not added in mRWLHRHMap then add to mAllSyms , mSymType and mRWLHRHMap again here
			//as well
			std::string sy=mTSOExprToSymbMap.find(ExprAssntid)->second;
			if(mTSOProgram->mRWLHRHMap.find(sy)==mTSOProgram->mRWLHRHMap.end())
			{
				mTSOProgram->mRWLHRHMap.insert(std::make_pair(sy,ExprAssn));
				mTSOProgram->mAllSyms.push_back(sy);
				mTSOProgram->mSymType[sy]="write";
#ifdef DBG
				std::cout<<mTSOProgram->mAllSyms.size()<<"inserting write expr left "<<ExprAssn.first<<"="<<ExprAssn.second<<" with label as "<<sy<<std::endl;
#endif

			}
			//get the already seen mapping and return it..
			writesymset.insert(sy);
//			std::cout<<"inserting sym as "<<sy<<std::endl;
		}
	}
	else
	{
//		std::cout<<" free var of "<<oldsym<<" is empty "<<std::endl;
		//else return oldsym directly by adding its info in new program object as well..
		if(mTSOProgram->mRWLHRHMap.find(oldsym)==mTSOProgram->mRWLHRHMap.end())
		{

			mTSOProgram->mRWLHRHMap.insert(std::make_pair(oldsym,mProgram.mRWLHRHMap.find(oldsym)->second));
			mTSOProgram->mAllSyms.push_back(oldsym);
			mTSOProgram->mSymType[oldsym]="write";
			//std::cout<<mTSOProgram->mAllSyms.size()<<"Adding "<<oldsym<<" as type "<<mTSOProgram->mSymType[oldsym]<<std::endl;
		}
		//return newsymbol
//		std::cout<<"inserting sym as "<<oldsym<<std::endl;
		writesymset.insert(oldsym);
	}

	return std::make_pair(writesymset,readsymset);

}


std::set<SymStatePair> TSOTransSystem::StepFlush(int tid, const TSOState& st)
{
	//if buff of tid is empty for state st return null..
	std::set<SymStatePair> setpair;
	if(st.isBuffEmpty(tid))
		return setpair;
	else
	{
		//else remove one from the buffer.. and return it along with the modified state..
		TSOState newst(st);
		std::string bufelem(newst.flushBuf(tid));
		std::set<std::string> symset;
		symset.insert(bufelem);
		setpair.insert(std::make_pair(symset,newst));
		return setpair;
		//in modified state only buffer gets changed, no change in the contorl locations.
	}

}


void TSOTransSystem::BuildTSOTS(faudes::Generator& resultgen, int buffbound)
{
	faudes::Generator lGen;
	//from program object get number of process their regex and convert them to automata..
	std::vector<faudes::Generator*> autset= mProgram.GetSpecOfAllProcesses();
	std::map<std::string,z3::expr> assnMap = mProgram.GetAssnMapForAllProcesses();
	/*std::vector<struct fa*> automata;
	int i=1;
	std::cout<<"regexes size is "<<regexes.size()<<std::endl;
	for(;i<=mProgram.mNumThds;i++)
	{
		#ifdef	DBGPRNT
		std::cout<<"Extracted Regex is "<<regexes[i]<<std::endl;
		#endif
		//construct an automaton
		struct fa* aut;
		int res = fa_compile(regexes[i].c_str(),(size_t)regexes[i].length(),&aut);
		BOOST_ASSERT_MSG(aut!=NULL,"could not construct the automaton from a given expression");
		automata.push_back(aut);
		mInitCS.resize(i+1);
		mInitCS[i]=aut->initial;
	}
	std::cout<<"MInitCS size is "<<mInitCS.size()<<std::endl;
	*/

	int numprocesses=mProgram.mNumThds;
	//create an initial state with control locations set to initial state of each process automaton.
	TSOState inittso(buffbound,mProgram.mNumThds);
	//set initstate's process cs from automata.
	for(int i=1;i<=mProgram.mNumThds;i++)
	{

		inittso.setCState(i,autset[i]->InitState());
#ifdef DBG
		std::cout<<i<<" succ "<<std::endl;
#endif
	}
	//a map from tso state to generator's state.
	std::map<TSOState,faudes::Idx> statemap;//Imp to have this comparator..
	std::set<TSOState> workset;
	//put the state in a workset

	/*
	 * ALso add write instructions correpsonding to initial values before starting any exlploration.
	*/
	faudes::Idx init=lGen.InsState();
	lGen.SetInitState(init);
	faudes::Idx tmp=init;
	for(std::string::iterator it = mProgram.mInitString.begin();it!=mProgram.mInitString.end();it++)
			{
				char sym = *it;
				std::string symstr(1,sym);
				mTSOProgram->mRWLHRHMap.insert(std::make_pair(symstr,mProgram.mRWLHRHMap.find(symstr)->second));
				mTSOProgram->mAllSyms.push_back(symstr);
				mTSOProgram->mSymType[symstr]="write";
				faudes::Idx t = lGen.InsState();
				faudes::Idx ev = lGen.InsEvent(symstr);
				lGen.SetTransition(tmp,ev,t);
				tmp=t;
			}
	statemap[inittso]=tmp;
	workset.insert(inittso);
	//we are not inserting events in generator because we do not know in adavnce the alphabet
	//so we will do it when we get next states along with transitions..
	//while(workset is not empty)
	int dbgCount=0;
	while(!workset.empty())
	{
//		std::cout<<"inside"<<std::endl;
		TSOState st=*(workset.begin());
		workset.erase(st);
		dbgCount++;
		//get its associated generator state
		BOOST_ASSERT_MSG(statemap.find(st)!=statemap.end(),"Some serious error look carefully");
		faudes::Idx sourcest=statemap[st];
		//for each threadid find next transitions (concrete and flush from state st)
		for(int i=1; i<=numprocesses; i++)
		{
//			std::cout<<"For proc "<<i<<std::endl;
			std::set<SymStatePair> nextconcstates(StepConcrete(i,st,autset[i]));
			for(SymStatePair sspair: nextconcstates)
			{
				std::set<std::string> syms=std::get<0>(sspair);
				TSOState nextst=std::get<1>(sspair);
				//if syms is empty then it implies the symbol as epsilon..
				if(syms.empty())
				{
					//add epsilon to InsEvent set of generator
					faudes::Idx ev = lGen.InsEvent("epsilon");
					//or else create a new state and insert it in statemap
					if(statemap.find(nextst)==statemap.end())
					{
						statemap[nextst]=lGen.InsState();
						//add to worklist
						workset.insert(nextst);
					}
					//add an edge from sourcest to this state on symbol sym.
					lGen.SetTransition(sourcest,ev,statemap[nextst]);
				}else
				{
					int cnt=1;
					faudes::Idx tmpsource=sourcest;
					for(std::string sym: syms)
					{
						faudes::Idx ev = lGen.InsEvent(sym);
						if(cnt==syms.size())
						{
							//or else create a new state and insert it in statemap

							nextst.mEndingWith=sym;

							if(statemap.find(nextst)==statemap.end())
							{
								statemap[nextst]=lGen.InsState();
								//add to worklist
								workset.insert(nextst);
							}
						//add an edge from sourcest to this state on symbol sym.
//						std::cout<<"Inserted an edge on symbol "<<sym<<std::endl;
						lGen.SetTransition(tmpsource,ev,statemap[nextst]);
						std::pair<bool,z3::expr> pr= IsAcc(sym);
						if(pr.first){
							mSymAssnMap.insert(std::make_pair(sym,pr.second));
							lGen.SetMarkedState(statemap[nextst]);
						}
						}else{
							//create intermediate states not putting them to workset and statemap
							faudes::Idx tt=lGen.InsState();
							lGen.SetTransition(tmpsource,ev,tt);
							tmpsource=tt;
						}
						cnt++;
					}
				}
			}

			//next flush for this process if any
			std::set<SymStatePair> nextflushstates(StepFlush(i,st));
			for(SymStatePair sspair: nextflushstates)
			{
				std::set<std::string> syms=std::get<0>(sspair);
				TSOState nextst=std::get<1>(sspair);
				//syms must be singelton
				BOOST_ASSERT_MSG(syms.size()==1,"Some serious error, look into it");
				faudes::Idx ev = lGen.InsEvent(*(syms.begin()));
				//create a new state and insert it in statemap if not present
				nextst.mEndingWith="epsilon";
				if(statemap.find(nextst)==statemap.end())
				{
					statemap[nextst]=lGen.InsState();
					//add to worklist
					workset.insert(nextst);
				}
				//add an edge from sourcest to this state on symbol sym.
				lGen.SetTransition(sourcest,ev,statemap[nextst]);
			}

		}//end for number of processes
		//check if sourcest is accepting state or not..
		/*bool isacc=false;
		z3::expr accassn = mProgram.mCtx.bool_val(true);
		for(int i=1; i<numprocesses; i++)
		{
			std::string accsym(st.getTransSym(i));
//			std::cout<<"Acc sysm is "<<accsym<<std::endl;
			if(mProgram.mAssnMap.find(accsym)!=mProgram.mAssnMap.end())
			{
				isacc=true;
				accassn=(accassn && (mProgram.mAssnMap.find(accsym)->second));
				//get its assertion and conjunct with the initial one..
			}
		}
		//if yes then make this mapped state also as a marked one.
		//if yes then make it accepting with assertion to be checked as whatever is here already
		//conjuncted with the assertion of this process at this label..
		if(isacc)
		{
//			std::cout<<"marked states done"<<std::endl;
			lGen.SetMarkedState(sourcest);
			mShuffautAssnMap.insert(std::make_pair(sourcest,(accassn.simplify())));
		}*/
	}//end of whileloop workset empty
#ifdef DBG
	std::cout<<"Number of states are "<<dbgCount<<","<<lGen.States().Size()<<std::endl;
#endif
	faudes::Idx stt;
	std::string wd = lGen.GetShortestWord();
#ifdef DBG
	std::cout<<"Accepted word one is "<<wd<<std::endl;
#endif
//projecting out from language with alphabet not containing epsilon
	if(buffbound!=0)
	{
		faudes::EventSet evset;
		for(std::string sym: mTSOProgram->mAllSyms)
			evset.Insert(sym);
		//check that this set is same as the one on which evetns were inserted minus epsilon..
		//good to have this check..
		std::map<faudes::Idx,faudes::StateSet> changedSetMap;
		faudes::Project(lGen,evset,changedSetMap,resultgen);
#ifdef DBG
		std::cout<<"Number of states after projection are "<<dbgCount<<","<<resultgen.States().Size()<<std::endl;
#endif
		//minimize the states..
		std::vector<faudes::StateSet> subsetvec;
		std::vector<faudes::Idx> statevec;
		faudes::Generator minresult;
	}else
	{
		resultgen.Assign(lGen);
	}
	//minimization.. and determinization..
	/*faudes::StateMin(resultgen,minresult,subsetvec,statevec);
	std::cout<<"States after m in are "<<minresult.States().Size()<<std::endl;
*/

	//Note that the marked stateset for resultgen are not same as of lGen
	//because Project also calls determinisitc internally.. Otherwise only projection will keep the
	//marked states same.. that is interesting..
	//But thanks to lifbfaudes guys that they also exported a function that returns the mapping of
	//original states to deterministic genrator's states.. and we will use that to reconstruct the
	//assertion map (mshuffautAssnMap)

	//For each marked state of resultgen..
		//1. assert that the states it map to were all marked in lGen
		//2. construct the assertions for marked states of resultgen from assertions of lGen based on changedSetMap

	/*faudes::StateSet::Iterator it;
	std::map<faudes::Idx,z3::expr> newshuffAssnMap;
	for(it=resultgen.MarkedStatesBegin();it!=resultgen.MarkedStatesEnd();++it)
	{
		faudes::StateSet markedorig = changedSetMap[*it];
//		std::cout<<" For marked state "<<*it<<" origina "<<markedorig.Size()<<" states are mapped to it"<<std::endl;
		//assert that all states in markedorig are marked..
		faudes::StateSet::Iterator it2;
		z3::expr assrn=mProgram.mCtx.bool_val(true);
		bool acc=false;
		for(it2=markedorig.Begin();it2!=markedorig.End();it2++)
		{
			if(mShuffautAssnMap.find(*it2)!=mShuffautAssnMap.end())
			{
				acc=true;
				assrn=assrn && mShuffautAssnMap.find(*it2)->second;
			}
		}
		if(acc)
			newshuffAssnMap.insert(std::make_pair(*it,assrn.simplify()));
		//BOOST_ASSERT_MSG(lGen.MarkedStates().Exists(*it2),"Some seriour error");
	}


	mShuffautAssnMap.clear();
	mShuffautAssnMap=newshuffAssnMap;
	faudes::StateSet markedstates=resultgen.MarkedStates();
	std::cout<<"Accepted word one is "<<resultgen.GetWord(stt)<<std::endl;*/
	faudes::LanguageReverse(resultgen);
	//BOOST_ASSERT_MSG(resultgen.InitStates()==markedstates," Some serious error need to rethink of strategy");
	//resultgen.StateNamesEnabled(false);
	//ONCE we are done.. from mmTSONewOldSymbMap remove all those symbols which were not added in
	//this iteration..i.e. all those which do not appear in mTSOProgram->mAllSyms vector..
	std::map<std::string,std::string>::iterator itr = mTSONewOldSymbMap.begin();
	while (itr != mTSONewOldSymbMap.end()) {
	    if (std::find (mTSOProgram->mAllSyms.begin(), mTSOProgram->mAllSyms.end(), itr->first)==mTSOProgram->mAllSyms.end()) {
	       mTSONewOldSymbMap.erase(itr++);
	    } else {
	       ++itr;
	    }
	}
#ifdef DBG
	std::cout<<"Total symbols are "<<mTSOProgram->mAllSyms.size()<<std::endl;
#endif
	//parition symbols..
	mTSOProgram->PartitionSimilarSymbols();

}//end of function

Program* TSOTransSystem::GetModifiedProgramObject()
{
	return mTSOProgram;
}

z3::expr TSOTransSystem::GetEndStateAssertionFromWord(std::string afaword){
	std::string lastsym;
 		boost::char_separator<char> sep(".");
		boost::tokenizer<boost::char_separator<char>> tokens1(afaword, sep);
			for(const std::string& sym: tokens1){
				lastsym=sym;
				break;
			}
		BOOST_ASSERT_MSG(mSymAssnMap.find(lastsym)!=mSymAssnMap.end(),"Some serious issue as the last char must be the one where assn is defined");
		return mSymAssnMap.find(lastsym)->second;
}

std::pair<bool,z3::expr> TSOTransSystem::IsAcc(std::string sym){
	std::string ssym;
	z3::expr falseformula = mProgram.mCtx.bool_val(false);

	if(mTSONewOldSymbMap.find(sym)!=mTSONewOldSymbMap.end())
		ssym=mTSONewOldSymbMap[sym];
	else
		ssym=sym;
	if(mProgram.mAssnMap.find(ssym)!=mProgram.mAssnMap.end())
		return std::make_pair(true,mProgram.mAssnMap.find(ssym)->second);
	else
		return std::make_pair(false,falseformula);

}

z3::expr TSOTransSystem::GetLastWrite(int tid, std::string var, const TSOState st, bool& found, std::string& foundsym)
{
	found=false;
	z3::expr retval=mProgram.mCtx.bool_val(true);
	WriteBuffer::const_iterator it=st.mBufferMap.find(tid)->second.begin();
	for(;it!=st.mBufferMap.find(tid)->second.end();++it)
	{
		std::string sym=*it;
		BOOST_ASSERT_MSG(mTSOProgram->mRWLHRHMap.find(sym)!=mTSOProgram->mRWLHRHMap.end(),"Some serious error");
		std::tuple<z3::expr,z3::expr> pr = mTSOProgram->mRWLHRHMap.find(sym)->second;
		z3::expr lhs=std::get<0>(pr);
		std::stringstream st;
		st<<lhs;
		std::string lhsstr=st.str();
		if(lhsstr==var)
		{
			found=true;
			foundsym=sym;
			retval=std::get<1>(pr);
		}
	}
	return retval;
}

void TSOTransSystem::DebugTSOSymbolInfo()
{
#ifdef DBG
	std::cout<<"Newly added symbols are "<<std::endl;
#endif
	for(std::pair<std::string,std::string> newsymp: mTSONewOldSymbMap)
	{

		std::tuple<z3::expr,z3::expr> exprpair=mTSOProgram->mRWLHRHMap.find(newsymp.first)->second;
#ifdef DBG
		std::cout<<newsymp.first<<":"<< std::get<0>(exprpair)<<"="<<std::get<1>(exprpair)<<std::endl;
#endif
	}
}


void TSOTransSystem::DeterminizeAndReassignAssertionsInit(const faudes::Generator& rGen, faudes::Generator& rRes, std::map<faudes::Idx, z3::expr>& assnMap)
{

	std::map<faudes::Idx, faudes::StateSet> entrysetmap;
	faudes::Deterministic(rGen,entrysetmap,rRes);
	faudes::StateSet::Iterator it;
	std::map<faudes::Idx,z3::expr> newshuffAssnMap;
	for(it=rRes.InitStatesBegin();it!=rRes.InitStatesEnd();++it)
	{
		faudes::StateSet initorig= entrysetmap[*it];
//		std::cout<<" For marked state "<<*it<<" origina "<<markedorig.Size()<<" states are mapped to it"<<std::endl;
		//assert that all states in markedorig are marked..
		faudes::StateSet::Iterator it2;
		z3::expr assrn=mProgram.mCtx.bool_val(true);
		bool acc=false;
		for(it2=initorig.Begin();it2!=initorig.End();it2++)
		{
			if(assnMap.find(*it2)!=assnMap.end())
			{
				acc=true;
				assrn=assrn && assnMap.find(*it2)->second;
			}
		}
		if(acc)
			newshuffAssnMap.insert(std::make_pair(*it,assrn.simplify()));
		//BOOST_ASSERT_MSG(lGen.MarkedStates().Exists(*it2),"Some seriour error");
	}
	assnMap.clear();
	for(auto t: newshuffAssnMap)
		assnMap.insert(t);


}

void TSOTransSystem::MinimizeAndReassignAssertionsInit(faudes::Generator& rGen, faudes::Generator& rRes, std::map<faudes::Idx, z3::expr>& assnMap)
{
	std::vector<faudes::StateSet> subsets;
	std::vector<faudes::Idx> newindices;
	faudes::StateMin(rGen,rRes,subsets,newindices);
	BOOST_ASSERT_MSG(subsets.size()==newindices.size()," Some serious error");

	std::map<faudes::Idx,z3::expr> newshuffAssnMap;
	for(int i=0;i<newindices.size();i++)
	{
		if(rRes.InitStates().Exists(newindices[i]))
		{
			faudes::StateSet initorig= subsets[i];
			faudes::StateSet::Iterator it2;
			z3::expr assrn=mProgram.mCtx.bool_val(true);
			bool acc=false;
			for(it2=initorig.Begin();it2!=initorig.End();it2++)
			{
				if(assnMap.find(*it2)!=assnMap.end())
				{
					acc=true;
					assrn=assrn && assnMap.find(*it2)->second;
				}
			}
			if(acc)
				newshuffAssnMap.insert(std::make_pair(newindices[i],assrn.simplify()));
						//BOOST_ASSERT_MSG(lGen.MarkedStates().Exists(*it2),"Some seriour error");

		}
	}
	assnMap.clear();
	for(auto t: newshuffAssnMap)
			assnMap.insert(t);

}

/**
 * This function, given a trace of TSOTransition system returns program order relation embedded in that
 * trace. Note that some of the symbols in trace need to be mapped back to the original alphabet of the
 * program therefore this function is non-trivial.
 */
PO TSOTransSystem::GetPO(std::string trace){

	//reverse the trace (keeping . intact)
	std::string rev="";
	boost::char_separator<char> sep(".");
	boost::tokenizer<boost::char_separator<char>> tokens(trace, sep);
	//reverse and remove intial value writes from the trace.
	for (const std::string& sym: tokens)
	{
		if(rev.length()==0)
			rev=sym;
		else if(mProgram.mInitString.find(sym)==std::string::npos)//add only if not global variable, i.e. not present in mInitString
			rev=sym+"."+rev;

			//std::cout<<sym<<" is an initial write "<<std::endl;
	}

	//create initial POGenInfo and push to a workingset
	POGenInfo initinfo;
//	std::cout<<"String to anlayze is "<<rev<<std::endl;
	initinfo.mRest=rev;
	std::map<std::string,std::vector<std::string>> emp;
	std::vector<faudes::Generator*> autset=mProgram.GetSpecOfAllProcesses();
	BOOST_ASSERT_MSG(autset.size()==mProgram.mNumThds+1,"Some serious error in invariant check");
	for(int i=1;i<=mProgram.mNumThds;i++)
	{
		initinfo.mBuffInfo[i]=emp;
		initinfo.mCSinfo[i]=autset[i]->InitState();
	}
	std::set<POGenInfo> workset;
	workset.insert(initinfo);
	while(!workset.empty())
	{
		//iterate while workingset not empty
		POGenInfo picked=*(workset.begin());
		workset.erase(workset.begin());
		if(picked.mRest.size()==0){
/*
			for(int t=1;t<=mProgram.mNumThds;t++){
				std::cout<<"-----for proc "<<t<<std::endl;
				for(const auto& el: picked.mBuffInfo[t]){
					std::cout<<"For sym "<<el.first<<" size of vector is "<<el.second.size()<<std::endl;
				}
			}
*/

			bool res = IsExhaustable(picked);//This function changes picked in place in case it is exhaustable.
			if(res){
			/*	std::cout<<"Returning from getPO function "<<std::endl;
				for(int t=1;t<=mProgram.mNumThds;t++){
											std::cout<<"-----Inside: for proc "<<t<<std::endl;
											for(const auto& el: picked.mBuffInfo[t]){
												std::cout<<"For sym "<<el.first<<" size of vector is "<<el.second.size()<<std::endl;
											}
										}*/
				return picked.mPO;
			}
			else
			{

/*
				std::cout<<" Left out stuff is :"<<std::endl;
				for(int t=1;t<=mProgram.mNumThds;t++){
								std::cout<<"-----for proc "<<t<<std::endl;
								for(const auto& el: picked.mBuffInfo[t]){
									std::cout<<"For sym "<<el.first<<" size of vector is "<<el.second.size()<<std::endl;
								}
							}
*/

			}
		}else{
//			std::cout<<"calling GetNextStep on "<<picked.mRest<<std::endl;
			std::set<POGenInfo> rets=GetNextStep(picked);
//			std::cout<<" Returned set size is "<<rets.size()<<std::endl;
			workset.insert(rets.begin(),rets.end());
		}
	}


BOOST_ASSERT_MSG(false,"Control should not reach here, some serious issue");

}

std::set<POGenInfo> TSOTransSystem::GetNextStep(POGenInfo& info){

	BOOST_ASSERT_MSG(info.mRest.length()!=0,"Some serious error, check carefully");
	//token the first symbol in sym
	std::vector<faudes::Generator*> autset= mProgram.GetSpecOfAllProcesses();
	std::string rest;
	std::pair<std::string,std::string> symstr=ExtractFirstFromOld(info.mRest,rest);//return the original alphabet mapped symbol if any.
	std::string sym=std::get<0>(symstr);
	std::string strsy=std::get<1>(symstr);
	//in fact this function should not return anything that was added new
	BOOST_ASSERT_MSG(mProgram.mSymTidMap.find(sym)!=mProgram.mSymTidMap.end(),"Some serious error check ");
	int tid = mProgram.mSymTidMap[sym];
	std::set<POGenInfo> retset;
	//let us start mCSinfo vector from 1 to ensure that we do not start from 0.
	std::map<std::string,faudes::Idx> labnextstpair=GetLabNextPair(info.mCSinfo[tid],autset[tid]);

	BOOST_ASSERT_MSG(labnextstpair.find("rfence")==labnextstpair.end(),"Some error as by this time rfence must be handled by getlabnextpair function");
/*
	if(labnextstpair.find("rfence")!=labnextstpair.end())//means one rfence was found..
	{
		//increase control state to next and keep everything same and put it in retset..
		POGenInfo tmp=info;
		tmp.mCSinfo[tid]=labnextstpair["rfence"];
		retset.insert(tmp);
	}
*/
	//try to match the sym with next transition from tid's next transtion
	if(labnextstpair.find(sym)==labnextstpair.end()){
		//if it does not then check if tid's label has something that is in next of tid's transition
		bool notdone=true;
		for(const auto& nextlab: labnextstpair){
			if(info.mBuffInfo[tid].find(nextlab.first)!=info.mBuffInfo[tid].end()){
				if(info.mBuffInfo[tid][nextlab.first].size()!=0)
				{
					POGenInfo tmp=info;
					std::string sm=info.mBuffInfo[tid][nextlab.first].front();
					tmp.mBuffInfo[tid][nextlab.first].erase(tmp.mBuffInfo[tid][nextlab.first].begin());
					tmp.mCSinfo[tid]=nextlab.second;
					//remove from buffer, update next trans state and add a po from last of tid to this and set this as last for tid
					if(tmp.mLastSym.find(tid)==tmp.mLastSym.end())
						tmp.mLastSym[tid]=sm;
					else
					{
						if(tmp.mLastSym[tid].length()!=0){
						tmp.mPO[tmp.mLastSym[tid]]=sm;
						tmp.mLastSym[tid]=sm;
						}else
						{
							BOOST_ASSERT_MSG(false,"SOme error");
							tmp.mLastSym[tid]=sm;
						}
					}
					notdone=false;
					retset.insert(tmp);
				}
			}
		}
		//if this does not match too then put it in the buffer of tid and remove from rest..
		if(notdone){
			POGenInfo tmp=info;
			tmp.mRest=rest;
			tmp.mBuffInfo[tid][sym].push_back(strsy);
			retset.insert(tmp);
		}
	}else
	{
	//else remove it from rest, update next trans state, add a po from last of tid to this and set this as last for tid
		POGenInfo tmp=info;
		tmp.mRest=rest;
		tmp.mCSinfo[tid]=labnextstpair[sym];
		if(tmp.mLastSym.find(tid)==tmp.mLastSym.end()){
			tmp.mLastSym[tid]=strsy;
		}
		else{
			if(tmp.mLastSym[tid].length()!=0){
			tmp.mPO[tmp.mLastSym[tid]]=strsy;
			tmp.mLastSym[tid]=strsy;
			}else{
				BOOST_ASSERT_MSG(false,"SOme error");
				tmp.mLastSym[tid]=strsy;
			}
		}
		retset.insert(tmp);
	}
return retset;
}

std::pair<std::string,std::string> TSOTransSystem::ExtractFirstFromOld(std::string& orig, std::string& rest)
{
	boost::char_separator<char> sep(".");
	boost::tokenizer<boost::char_separator<char>> tokens(orig, sep);
	rest.assign(orig);
	std::string thiss(orig);
	for (const std::string& sym: tokens)
	  {
		rest.erase(0,sym.length()+1);//+1 for . concatenated at the end
							//for each character encountered..
		//if assert then return
		//Later argue if this was needed or not..
		BOOST_ASSERT_MSG(mTSOProgram->mSymType.find(sym)!=mTSOProgram->mSymType.end()," Some seriour error check");
		/*if(mTSOProgram->mSymType[sym]=="assume")
		{
			thiss.erase(0,sym.length()+1);
			continue;
		}*/

		//if symbol is present in mProgram's symbol return
		if(mProgram.mSymType.find(sym)!=mProgram.mSymType.end())
			return std::make_pair(sym,thiss);
		//if symbol is present in mTSO's newoldmap then return its map
		if(mTSONewOldSymbMap.find(sym)!=mTSONewOldSymbMap.end())
			return std::make_pair(mTSONewOldSymbMap[sym],thiss);
		//else continue
		//IMP: Note that we dont want to return those symbols which were added to facilitate
		//reads linking in case of write operations.. so I will not put them in mNewOldSymbMap in
		//BuildTS function
		thiss.erase(0,sym.length()+1);
	  }
	BOOST_ASSERT_MSG(false,"Control should not reach here.. Check ");

}

bool TSOTransSystem::IsExhaustable(POGenInfo& info){

	BOOST_ASSERT_MSG(info.mRest.length()==0," Some serious error, check carefully");
	//for each tid see if we can exhaust info.buffer[i] entries..
	//let us start mCSinfo vector from 1 to ensure that we do not start from 0.
	std::set<POGenInfo> workset,resultset,seenset;
	std::vector<faudes::Generator*> autset= mProgram.GetSpecOfAllProcesses();
	resultset.insert(info);
	for(int tid=1;tid<=mProgram.mNumThds;tid++)
	{
		//copy from resultset to workset
		workset.clear();
		workset.insert(resultset.begin(),resultset.end());
		resultset.clear();

		while(workset.size()!=0)
		{
			POGenInfo tinfo = *(workset.begin());
			workset.erase(workset.begin());
			seenset.insert(tinfo);
			if(IsExhaustDone(tid,tinfo))
			{
//				std::cout<<"Exahust done for pcoess "<< tid<<std::endl;
				resultset.insert(tinfo);
#ifdef DBG
				for(int tt=1;tt<=mProgram.mNumThds;tt++){
										std::cout<<"-----Inside: for proc (New)"<<tt<<std::endl;
													for(auto& e: tinfo.mBuffInfo[tt]){
													std::cout<<"For sym "<<e.first<<" size of vector is "<<e.second.size()<<std::endl;
													}
										}
#endif
				break;
			}else
			{
				std::map<std::string, faudes::Idx> labnextstpair=GetLabNextPair(tinfo.mCSinfo[tid],autset[tid]);
				bool found=false;
				if(labnextstpair.find("rfence")!=labnextstpair.end())//means one rfence was found..
					{
						//increase control state to next and keep everything same and put it in retset..
						POGenInfo tmp=info;
						tmp.mCSinfo[tid]=labnextstpair["rfence"];
						workset.insert(tmp);
						found=true;
					}

				for(const auto& elpr: tinfo.mBuffInfo[tid])
					{
						if(elpr.second.size()!=0 && labnextstpair.find(elpr.first)!=labnextstpair.end())
						{
						//remove first entry from elpr.second vector..
							found=true;
//							std::cout<<"moved next "<<std::endl;
							std::string s=elpr.second.front();
							POGenInfo tmp=tinfo;
							tmp.mBuffInfo[tid][elpr.first].erase(tmp.mBuffInfo[tid][elpr.first].begin());
//							std::cout<<"After erase size of "<<elpr.first<<" is "<<tmp.mBuffInfo[tid][elpr.first].size()<<std::endl;
							tmp.mCSinfo[tid]=labnextstpair[elpr.first];
							if(tinfo.mLastSym[tid].length()!=0){
							tmp.mPO[tinfo.mLastSym[tid]]=s;
							tmp.mLastSym[tid]=s;
							}else
								tmp.mLastSym[tid]=s;
						//update last ..po and next control state in new POGenInfo
							workset.insert(tmp);
						//put it in worklist
						}
					}
				if(!found){
#ifdef DBG
					std::cout<<"Nothing to be matched from CS transitions :"<<std::endl;
					for(const auto&n: labnextstpair)
											std::cout<<"----"<<n.first<<std::endl;
#endif

					//This is an interesting case.. it means no symbol next was found to be stored in buffer of
					//poinfo.. hence it must been in process buffer and did not contribute to the
					//error trace.. but we found (in pgsql example) that one such error trace
					//must have that write in buffer to find out the reason of error anf hence fence
					//location.. therefore add it as a symbol in po as well..
					//In other part (in rf finding from proof) also add that write simply as a..
					//for now we can assert that no other one with that name was present..
					//later we can think of ways of making them actually at the end.
					for(const auto& elpr: labnextstpair)
					{
						POGenInfo tmp=tinfo;
						tmp.mCSinfo[tid]=elpr.second;//move control point to next..
						tmp.mLastSym[tid]=elpr.first;
						//Interseting:: it seems sufficient ot add this only in PO
						/// this will cause it to have a node in graph and hence a cycle can be found
						//as well.let see with pgsql example..
						if(seenset.find(tmp)==seenset.end())//means not seen earlier
						{
//							std::cout<<"skipping past"<<std::endl;
							workset.insert(tmp);
						}
					}
				}
			}
		}
	}
	BOOST_ASSERT_MSG(resultset.size()==1," Some serious error, llok");
	//when done.. resultset will have final entries.. check for each of them at least one
	//process must be at its accepting state??or rather its last symbol must be the one where
	//assertion is being checked..
	for(auto& el: resultset)
	{
		std::map<int,std::map<std::string,std::vector<std::string>>> tmg=el.mBuffInfo;
		/*for(const auto& els: el.mPO)
								std::cout<<els.first<<" --> "<<els.second<<std::endl;
*/
		for(int t=1; t<= mProgram.mNumThds;t++)
		{
			//get first sym from el.mLastSym[tid]
			std::string tm;

			//it is possible that only one thread's events are present in trace int that case
			//no po will be done for other thread and hence mLastSym for that tid will be empty.
			if(el.mLastSym.find(t)!=el.mLastSym.end())
			{

				tm=el.mLastSym.find(t)->second;//mLastSym[t] is giving error that const can not be passed
				std::string sym=ExtractFirst(tm);
#ifdef DBG
				std::cout<<"Last sym for process "<<t<<" is "<<tm<<" and "<<sym<<std::endl;
#endif
				if(mProgram.mAssnMap.find(sym)!=mProgram.mAssnMap.end())
				{
					info=el;//does it copy the content from el to info??
				/*	for(int tt=1;tt<=mProgram.mNumThds;tt++){
									std::cout<<"-----Inside: for proc "<<tt<<std::endl;

									for(auto& e: tmg[tt]){
									std::cout<<"For sym "<<e.first<<" size of vector is "<<e.second.size()<<std::endl;
									}
						}
*/


					return true;
				}
			}

		}
	}
	return false;
	//return any one of them (modify in place in input)
}

bool TSOTransSystem::IsExhaustDone(int tid, POGenInfo& info)
{
	//check if in info all buffers of tid are empty or not..
	for(const auto& elpr: info.mBuffInfo[tid])
	{
		if(elpr.second.size()!=0)
			return false;
//		std::cout<<"For pro "<<tid<<" buff of "<<elpr.first<<" is empty"<<std::endl;
	}
	return true;
}

//One issue was arising here: if rfence is encounterd then we want to skip the state and pass to the next one
std::map<std::string,faudes::Idx> TSOTransSystem::GetLabNextPair(faudes::Idx curr, faudes::Generator* lGen)
{
	//get all successors of st
	std::map<std::string, faudes::Idx> res;
	for(faudes::TransSet::Iterator lit = lGen->TransRelBegin(curr);lit!=lGen->TransRelEnd(curr);lit++)
	{
		std::string sym(lGen->EventName(lit->Ev));
		faudes::Idx dest = lit->X2;
		if(res.find(sym)!=res.end())
		{
			std::cout<<"Two transitiosn on symbol "<<sym<<" from this state"<<std::endl;
		BOOST_ASSERT_MSG(res.find(sym)==res.end(),"Some error, from this state on saem sym go to two diff states.. look carefully");
		}
		if(sym.compare("rfence")==0){
			//then recursively find the transitions starting from next state (dest) and add them to res..
			//we can safely assume (but assert) that no two consecutive rfence appear here..
			for(faudes::TransSet::Iterator lits = lGen->TransRelBegin(dest);lits!=lGen->TransRelEnd(dest);lits++)
				{
					std::string syms(lGen->EventName(lits->Ev));
					faudes::Idx dests = lits->X2;
					BOOST_ASSERT_MSG(syms.compare("rfence")!=0,"SOme error as two consecutive rfence should not be there");
					if(res.find(syms)!=res.end())
					{
							std::cout<<"Two transitiosn on symbol "<<syms<<" from this state (after rfence)"<<std::endl;
							BOOST_ASSERT_MSG(res.find(syms)==res.end(),"Some error, from this state on saem sym go to two diff states (maybe after rfence).. look carefully");
					}
					res.insert(std::make_pair(syms,dests));
				}
		}
		else
			res.insert(std::make_pair(sym,dest));
	}
	return res;
}


std::string TSOTransSystem::ExtractFirst(const std::string nd)
{
	//extract first symbol till .
	boost::char_separator<char> sep(".");
	boost::tokenizer<boost::char_separator<char>> tokens(nd, sep);
	BOOST_ASSERT_MSG(tokens.begin()!=tokens.end()," At least one symbol must be present some serious error");
    for (const std::string& sym: tokens)
	   {
    	std::string ncsym=sym;
    	return ncsym;
	   }
    BOOST_ASSERT_MSG(false,"Control should not reach here");
}

TSOTransSystem::~TSOTransSystem()
{
	if(mTSOProgram!=NULL)
	{
		delete mTSOProgram;
		mTSOProgram=NULL;
	}

}

