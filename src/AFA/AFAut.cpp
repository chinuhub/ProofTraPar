/*
 * AFAut.cpp
 *
 *  Created on: 23-Aug-2015
 *      Author: jaganmohini
 */

#include "AFAut.h"
#include <iterator>
#include <map>
#include<set>
#include<boost/tokenizer.hpp>
template <class Name>

class myEdgeWriter {
  public:
         myEdgeWriter(Name _name) : name(_name) {}
              template <class VertexOrEdge>
                     void operator()(std::ostream& out, const VertexOrEdge& v) const {
                                   out << "[label=\"" << name[v].label << "\"]";
                                        }
  private:
                   Name name;
};


template <class Name>
class myVertWriter {
  public:
         myVertWriter(Name _name) : name(_name) {}
              template <class VertexOrEdge>
                     void operator()(std::ostream& out, const VertexOrEdge& v) const {
//                                   out << "[label=\"" << name[v].vertlabel << "\", xlabel=\" "<<name[v].xlabel<<"\", color="<<name[v].color<<",shape="<<name[v].shape<<"]";
            	  out << "[label=\"" << name[v].vertlabel << "\", color="<<name[v].color<<",shape="<<name[v].shape<<"]";
                                        }
  private:
                   Name name;
};

struct autstatecomparator{
	bool operator() (const struct autstate* one, const struct autstate*  two) const
	{
		return one<two;
	}
};

Program* AFAut::mProgram;
std::set<AFAStatePtr> AFAut::mAFAOrLitStates;
std::set<AFAStatePtr> AFAut::mAFAInitStates;
/**
 * Function to convert an NFA/DFA to an AFA
 */
/*
AFAut* AFAut::MakeAFAutFromFA(struct fa* nfa,Program* program, z3::context& ctx){
	mProgram= program;

	AFAut* afa = new AFAut();
	std::map<struct autstate*, AFAStatePtr> seenstates;
	AFAStatePtr init = RecMakeAFAutFromFA(nfa->initial,seenstates,ctx);

	BOOST_ASSERT_MSG(seenstates.find(nfa->initial)->second==init,"Some serious issue");
	afa->mInit=init;

	BOOST_FOREACH(auto t, init->mTransitions){
		BOOST_FOREACH(auto v, t.second)
				std::cout<<v<<","<<std::endl;
	}
	afa->PrintToDot("tryinside.dot");

	//complete the AFA
	//Now before returning, complete the AFA, i.e. for each state, get set of symbols on which it has
		 	    //transitions, then find where it doesnt have and add an edge from this state on this symbol to error state.
		 	   z3::expr trueexp = ctx.bool_val(true);
		 	   AFAStatePtr errorstate= new AFAState(OR,trueexp, *mProgram);
		 	   SetAFAStatesPtr seterrostate;
		 	   seterrostate.insert(errorstate);
		 	   std::set<std::string> allsyms(mProgram->mAllSyms.begin(),mProgram->mAllSyms.end());
		 	  //add self loop on every transition from errostate to itself.
 	  	 	   errorstate->mTransitions.clear();// a small convenience as we know by this time only 0 has been added
 	  	 	   //by the constructor of AFAState for this error state.
 	  	 	   BOOST_FOREACH(auto symp, allsyms)
 	  	 	   	   errorstate->mTransitions.insert(std::make_pair(symp,seterrostate));

		 	   BOOST_FOREACH(auto st, seenstates){
		 		   AFAStatePtr state = st.second;
		 		   std::set<std::string> alltransyms =state->getTransitionKeys();
		 		   std::set<std::string> diffset;
		 		   std::set_difference(allsyms.begin(),allsyms.end(),alltransyms.begin(),alltransyms.end(),std::inserter(diffset,diffset.begin()));
		 		   BOOST_FOREACH(auto ss, diffset){
		 			   state->mTransitions.insert(std::make_pair(ss,seterrostate));
		 		   }
		 	   }
	return afa;
}
*/

/*
AFAStatePtr AFAut::RecMakeAFAutFromFA(struct autstate* state, std::map<struct autstate*, AFAStatePtr>& seenstates,z3::context& ctx)
{
//std::cout<<"iter"<<std::endl;
	if(seenstates.find(state)!=seenstates.end())
	{
		return seenstates.find(state)->second;
	}
	z3::expr trueexp = ctx.bool_val(true);
	AFAStatePtr st = new AFAState(ORLit,trueexp,*mProgram);
	if(state->accept)
	{
#ifdef	DBGPRNT
		std::cout<<"set as an accepted state"<<std::endl;
#endif
		st->mIsAccepted=true;

	}
	seenstates.insert(std::make_pair(state,st));
	//for each outgoing edge from state.. call Recursively and get the AFAStatePtr to be added to st's
	//transition system
	for(int i=0; i< state->tused; i++)
		{
			struct auttrans trans = state->trans[i];
			//find the destination state
			struct autstate* dest = trans.to;
			//find symbol

			std::string sym(1,trans.min);
//			std::cout<<"character is "<<trans.min<<" and string symbol is "<<sym<<std::endl;
			AFAStatePtr destafa = RecMakeAFAutFromFA(dest,seenstates,ctx);
//			std::cout<<"Adding edge"<<std::endl;
			SetAFAStatesPtr setown;
			setown.insert(destafa);
			//st->mTransitions.insert(std::make_pair(sym,setown));
			st->HelperAddEdgeIfAbsent(st,destafa,sym);
		}
	return st;
}

*/

/**
 * Function to construct and AFA corresponding to word w and neg phi as phi
 */
AFAut* AFAut::MakeAFAutProof(std::string& word, z3::expr& mPhi,Program* p, int count, bool& bres, faudes::Generator& generator, std::string memmodel){
	mProgram= p;
	 //for mPhi, create a state appropriately.., add this state to a worklist.. and repeat until worklist is empty..
			//inside loop, remove an element from this worklist and invoke the function FillState on it..
			//whatever is returned is added to the worklist.
			z3::context& ctx= mPhi.ctx();
			AFAut* afa = new AFAut();
			z3::tactic t = z3::tactic(ctx,"tseitin-cnf");
			z3::goal g(ctx);
			g.add(mPhi);
			z3::apply_result res = t(g);
			std::map<AFAStatePtr,AFAStatePtr,mapstatecomparator> allStates;
			if(res.size()>1){
								//then it is surely of or type.. claus 1 or clause 2.. create an DisjAND state
				z3::expr formula = g.as_expr();
				AFAStatePtr st = new AFAState(OR, word, formula,*mProgram);
				allStates.insert(std::make_pair(st,st));
#ifdef	DBGPRNT
				std::cout<<mPhi<<" found to be a or b or c type "<<std::endl;
#endif
				st->PassOne(allStates);
				afa->mInit=st;
			}else if(res.size()==1){
				z3::expr formula = res[0].as_expr();

				if(formula.decl().decl_kind()==Z3_OP_AND)
				{
					AFAStatePtr st = new AFAState(AND,word,formula,*mProgram);
					allStates.insert(std::make_pair(st,st));
#ifdef	DBGPRNT
					std::cout<<mPhi<<" found to be a and b and c type "<<std::endl;
#endif
					st->PassOne(allStates);
					afa->mInit = st;
				}else if(formula.decl().decl_kind()==Z3_OP_OR)
				{
					AFAStatePtr st = new AFAState(OR,word,mPhi,*mProgram);
					allStates.insert(std::make_pair(st,st));
#ifdef	DBGPRNT
					std::cout<<mPhi<<" found to be a or b type "<<std::endl;
#endif
					st->PassOne(allStates);
					afa->mInit = st;
				}else
				{
					AFAStatePtr st = new AFAState(ORLit,word,mPhi,*mProgram);
					allStates.insert(std::make_pair(st,st));
#ifdef	DBGPRNT
					std::cout<<mPhi<<" found to be a literal "<<" and type is "<<st->mType<<std::endl;
#endif
					st->PassOne(allStates);
					afa->mInit = st;
				}
			}
#ifdef DBGPRNT
			afa->PrintToDot("Pass1.dot");
#endif
			std::map<AFAStatePtr,AFAStatePtr,mapstatecomparator> passtwoallstates;
			if(!afa->mInit->HelperIsUnsat(*(afa->mInit->mHMap)))
			{
				bres=false;
				//Still create Pass2 because we would like to check if this error can be solved
				//or not..
				afa->mInit->PassTwo(passtwoallstates);
				//afa->PrintToDot("Pass2.dot");
				return afa;//to denote that this trace is erroneous
			}
			bres=true;

#ifdef	DBGPRNT
			afa->PrintToDot("Pass1.dot");
#endif

			//Pass two..
#ifdef	DBGPRNT
			std::cout<<"Starting Pass two"<<std::endl;
#endif

			afa->mInit->PassTwo(passtwoallstates);
#ifdef	DBGPRNT
			std::cout<<"Pass two ended"<<std::endl;
			afa->PrintToDot("Pass2.dot");
#endif
			//when this call is returned, passtwoallstates contain only those states which survived extinction.. So we can delete all other
			//states as thy become unreachable as well.\
			std::set<AFAStatePtr,mapstatecomparator> unreachable;
			BOOST_FOREACH(auto t, allStates){
				AFAStatePtr el = t.first;
				if(passtwoallstates.find(el)==passtwoallstates.end()){
					//means this element was not reachable after pruning of edges..
#ifdef	DBGPRNT
					std::cout<<"Found unreachable node after Pass two "<<std::endl;
#endif
					delete el;
				}
			}
#ifdef	DBGPRNT
	 	    std::cout<<"Starting Pass four "<<std::endl;
#endif
	 	    //Pass four- adding more edges respecting implications, this is a function of AFAut only not of AFAstate
	 	    //std::tuple<SetAFAStatesPtr,SetAFAStatesPtr,AFAStatePtr> retvals =afa->mInit->PassFour(afa->mInit,passtwoallstates);
	 	   //struct fa* complementedaut=afa->mInit->PassFour(afa->mInit,passtwoallstates);
//	 	   struct fa* complementedaut=
	 	    std::set<AFAStatePtr> allStatesDel;
	 	    AFAut* proofafa = afa->PassFourNew(afa->mInit,allStatesDel,count,generator);
	 	   //delete alls tates in passtwoallstates;-- Do it later;;
	 	  BOOST_FOREACH(auto t, allStatesDel){
	 	  		delete(t);
	 	  	}
	 	  afa->mInit=NULL;
	 	  delete afa;//no longer in use..
//	 	  std::cout<<"Proofafa done"<<std::endl;

	 	  return proofafa;
}
/**
 * Complement this AFA and changes init accordingly==
*/

AFAStatePtr AFAut::Complement(AFAStatePtr falseacc){
	std::map<AFAStatePtr,bool> mapseenset;
  //falseacc->mIsAccepted=false;
	z3::expr falsexp = mInit->mAMap.ctx().bool_val(false);
	AFAStatePtr newerrorstate=new AFAState(ORLit,falsexp,*mProgram);
	newerrorstate->mHMap=new z3::expr(falsexp);
	newerrorstate->mIsAccepted=true;
	SetAFAStatesPtr errorstateset;
	errorstateset.insert(newerrorstate);
	BOOST_FOREACH(auto sym, mProgram->mAllSyms)
		newerrorstate->mTransitions.insert(std::make_pair(sym,errorstateset));

	if(mInit->mType!=ORLit){
		//means it will have only 0 labeled edges.. we must do the necessary part here (cnverting and/or and then call
		//recomplement function on each of them..
		//assert that all keys from this state is of 0 form..
		std::set<std::string> transset = mInit->getTransitionKeys();

		BOOST_ASSERT_MSG(transset.size()==1 && transset.find("0")!=transset.end(),"Some issue as all transitions from such states must be on 0");
		//convert these transitions to OR
		//Same code as used in RecComplement function in next code
		std::set<SetAFAStatesPtr> tobeaddedset;
		SetAFAStatesPtr empty;
		tobeaddedset.insert(empty);
		for(std::multimap<std::string, SetAFAStatesPtr>::iterator it= mInit->mTransitions.equal_range("0").first; it!=mInit->mTransitions.equal_range("0").second; it++)
					{
//			std::cout<<"Inside one"<<std::endl;
						std::set<SetAFAStatesPtr> tmptobeaddedset;
						SetAFAStatesPtr curr = it->second;
						BOOST_FOREACH(auto singlesetSetStates, tobeaddedset)
						{
							for(SetAFAStatesPtr::iterator itset=curr.begin();itset!=curr.end();itset++)
							{
								SetAFAStatesPtr tmp;
								tmp.insert(singlesetSetStates.begin(),singlesetSetStates.end());
#ifdef	DBGPRNT
								std::cout<<"Invoking recomplement with "<<*itset<<std::endl;
#endif
								RecComplement(*itset,mapseenset,errorstateset,falseacc);
								tmp.insert(*itset);
								tmptobeaddedset.insert(tmp);
							}
						}
						tobeaddedset.clear();
						tobeaddedset.insert(tmptobeaddedset.begin(),tmptobeaddedset.end());
					}

					//add new ones..
					mInit->mTransitions.erase("0");//remove all elements of this symbol..
					BOOST_FOREACH(auto ele, tobeaddedset)
						mInit->mTransitions.insert(std::make_pair("0",ele));


	}else
		RecComplement(mInit,mapseenset,errorstateset,falseacc);

  return newerrorstate;
}

void AFAut::RecComplement(AFAStatePtr state, std::map<AFAStatePtr,bool>& mapseenset, SetAFAStatesPtr errorstateset,AFAStatePtr falseacc)
{

	if(mapseenset.find(state)!=mapseenset.end())
	{
		return;
	}else
	{
		mapseenset.insert(std::make_pair(state,true));

		if(state->mIsAccepted)
			state->mIsAccepted=false;
		else
			state->mIsAccepted=true;
		std::set<std::string> allsyms(mProgram->mAllSyms.begin(),mProgram->mAllSyms.end());

		for(std::set<std::string>::iterator it= allsyms.begin(); it!=allsyms.end(); it++){
			std::string sym = *it;
			std::set<SetAFAStatesPtr> tobeaddedset;
			SetAFAStatesPtr emptyset;
			tobeaddedset.insert(emptyset);
			//INV: Following loop must be entered for every symbol.
//			std::cout<<"Checking for edge on "<<sym<<" from "<<state<<std::endl;
#ifdef	DBGPRNT
			//Not every state is supposed to have a transition on every symbol.. because it depends upon
			//whether that transition has appeared in the input trace yet or not.
			if(state->mTransitions.find(sym)==state->mTransitions.end())
				std::cout<<"No transition from "<<state<<" on symbol "<<sym<<std::endl;
			BOOST_ASSERT_MSG(state->mTransitions.find(sym)!=state->mTransitions.end(),"Some serious error as this state must have transition on every symbol");
#endif
      bool found=false;
      int i=0;
			for(std::multimap<std::string, SetAFAStatesPtr>::iterator it= state->mTransitions.equal_range(sym).first; it!=state->mTransitions.equal_range(sym).second; it++)
			{
        found=true;
				std::set<SetAFAStatesPtr> tmptobeaddedset;
				SetAFAStatesPtr curr = it->second;
				BOOST_FOREACH(auto singlesetSetStates, tobeaddedset)
				{
					for(SetAFAStatesPtr::iterator itset=curr.begin();itset!=curr.end();itset++)
					{
						SetAFAStatesPtr tmp;
						tmp.insert(singlesetSetStates.begin(),singlesetSetStates.end());
						RecComplement(*itset,mapseenset,errorstateset,falseacc);
						tmp.insert(*itset);
						tmptobeaddedset.insert(tmp);
					}
				}
				tobeaddedset.clear();
				tobeaddedset.insert(tmptobeaddedset.begin(),tmptobeaddedset.end());
        i++;
			}
      //Following is necessary otherwise an empty entry present in tobeaddedset
      //will cause two entris to be added for this stuff.. this was a bug..
      if(!found)
        tobeaddedset.clear();

			//add new ones..
			state->mTransitions.erase(sym);//remove all elements of this symbol..
			BOOST_FOREACH(auto ele, tobeaddedset){
        if(ele.find(falseacc)!=ele.end())//if old accepted state is present in the tobeadded trans continue;;
          continue;
				state->mTransitions.insert(std::make_pair(sym,ele));
      }
			//The following part is to make sure that if there was no edge labelled some sym from this state
			//then on this symbol a transition must go to erstwhile error state which has now become an accepting state
			if(!found){
				state->mTransitions.insert(std::make_pair(sym,errorstateset));
			}
		}
	}
}

/*
 * Copy the input AFA to another one by replicating states and return the new AFA..
 */

AFAut* AFAut::CloneAFA(std::set<AFAStatePtr>& newset, std::map<AFAStatePtr,AFAStatePtr>& newoldmap){

	AFAut* n = new AFAut();
	//start with init state..clone it and put the copy old-new in map
	//a worklist to contain what need to be processed yet..
	std::set<AFAStatePtr> workset;
	std::map<AFAStatePtr,AFAStatePtr> oldnewmap;
	workset.insert(mInit);
	AFAStatePtr cp = mInit->Clone();
	n->mInit = cp;
	if(cp->mType==ORLit)
		newset.insert(cp);
	newoldmap.insert(std::make_pair(cp,mInit));
	oldnewmap.insert(std::make_pair(mInit,cp));
	while(!workset.empty())
	{
		AFAStatePtr picked = *(workset.begin());
		//get mapped one..
		workset.erase(picked);
		AFAStatePtr pickedmapped = oldnewmap.find(picked)->second;
		//for each transition in picked.. add transition in pickedmapped with mapped AFAStates
		for(auto const& trans: picked->mTransitions)
		{
			SetAFAStatesPtr setst;
			for(auto const& t: trans.second)
			{
				//get mapped one from oldnewmap.. if not found then create anew .. add to workset and oldnewmap
				//and then add to transition..
				AFAStatePtr c;
				if(oldnewmap.find(t)==oldnewmap.end()){
					c = t->Clone();
					if(c->mType==ORLit)
						newset.insert(c);
					workset.insert(t);
					oldnewmap.insert(std::make_pair(t,c));
					newoldmap.insert(std::make_pair(c,t));
				}else{
					c=oldnewmap.find(t)->second;
				}
				setst.insert(c);
			}
			pickedmapped->mTransitions.insert(std::make_pair(trans.first,setst));
		}
	}
//std::cout<<"New set size is "<<newset.size()<<std::endl;
	return n;

}



/**
* Returns this union second-- Not used anymore
*/
void AFAut::Union(AFAut& second){
/*
	z3::context& ctx = mInit->mAMap.ctx();
	z3::expr trueexp = ctx.bool_val(true);
	AFAStatePtr newinit = new AFAState(OR,trueexp);
	SetAFAStatesPtr nextset;
	nextset.insert(mInit);
	newinit->mTransitions.insert(std::make_pair("0",nextset));
	nextset.clear();
	nextset.insert(second.mInit);
	newinit->mTransitions.insert(std::make_pair("0",nextset));
	std::set<SetAFAStatesPtr> rettrans = newinit->RecSaturateEpsilon();
	newinit->mTransitions.clear();
	BOOST_FOREACH(auto t, rettrans)
			newinit->mTransitions.insert(std::make_pair("0",t));
	//memeory leak here.. should I delete old inittial states if they were Or/AND??
	mInit=newinit;
*/
}

/**
* Returns this intersection secon-- Not used anymore
*/
void AFAut::Intersection(AFAut& second){
/*
	z3::context& ctx = mInit->mAMap.ctx();
	BOOST_ASSERT_MSG(ctx!=NULL,"Serious error");
	z3::expr trueexp = ctx.bool_val(true);
	AFAStatePtr newinit = new AFAState(AND,trueexp);
	//std::cout<<"Default value of accepting is "<<newinit->mIsAccepted<<std::endl;
		SetAFAStatesPtr nextset;
		nextset.insert(mInit);
		nextset.insert(second.mInit);
		newinit->mTransitions.insert(std::make_pair("0",nextset));
		std::set<SetAFAStatesPtr> rettrans = newinit->RecSaturateEpsilon();
		newinit->mTransitions.clear();
		BOOST_FOREACH(auto t, rettrans)
			newinit->mTransitions.insert(std::make_pair("0",t));
		//memory leak ehre .. should I delete old initial states if they were Or/And?
		mInit=newinit;
*/


}
/**
 * Print to dot file
 */
void AFAut::PrintToDot(std::string filename){
			 	    Graph graph;
			 	    std::map<AFAStatePtr,vertex_t,mapstatecomparator> mapindex;
			 	    mInit->PassThree(graph,mapindex);//fill the graph object
		  	    myEdgeWriter<Graph> ew(graph);
			 	    myVertWriter<Graph> vw(graph);
			 	    //IMPO we need to put writers after graph is filled.

		//	#ifdef DEBUG_FILE

			 	    std::ofstream outf(filename);
			 	    write_graphviz(outf, graph, vw,ew);

}
/**
 * Extract one accepted word of this AFA and returns that-- NOw not begin called.
 */
std::string AFAut::GetWord(){

	std::map<SetAFAStatesPtr,bool> seenset;
	std::set<std::pair<SetAFAStatesPtr,std::string>> workset;
	SetAFAStatesPtr initset;
	//Dont just put init in the initset if init is of type OR/AND but find all transitions on 0 from here
	if(mInit->mType==OR || mInit->mType==AND){
		std::set<std::string> transkeys  = mInit->getTransitionKeys();

		BOOST_ASSERT_MSG(transkeys.size()==1 && transkeys.find("0")!=transkeys.end(),"Some serious error as AND/OR must have only 0 labeled outgoing transitions");
		BOOST_FOREACH(auto t, mInit->mTransitions){
			workset.insert(std::make_pair(t.second,""));
			seenset.insert(std::make_pair(t.second,true));
		}
	}
	else
	{
		initset.insert(mInit);
		workset.insert(std::make_pair(initset,""));
		seenset.insert(std::make_pair(initset,true));
	}
	std::set<std::string> allsyms(mProgram->mAllSyms.begin(),mProgram->mAllSyms.end());
	while(!workset.empty())
	{
		SetAFAStatesPtr elemset = (workset.begin())->first;
		std::string word = (workset.begin())->second;
		workset.erase(workset.begin());
		bool allaccepting=true;
		BOOST_FOREACH(auto t, elemset){
			if(!(t->mIsAccepted)){
				allaccepting=false;
			}
		}
		if(allaccepting && (word.length()!=0)){
			return word;
		}

		for(std::set<std::string>::iterator it= allsyms.begin(); it!=allsyms.end(); it++){
			std::string sym = *it;
			std::set<SetAFAStatesPtr> tobeaddedset;
			SetAFAStatesPtr emptyset;
			tobeaddedset.insert(emptyset);
			for(SetAFAStatesPtr::iterator itset = elemset.begin(); itset!=elemset.end(); itset++)
			{
				AFAStatePtr state = *itset;
				BOOST_ASSERT_MSG(state->mTransitions.find("0")==state->mTransitions.end(),"Somer serious issue, as no transition should have label 0");
				BOOST_ASSERT_MSG(state->mTransitions.find(sym)!=state->mTransitions.end(),"Some serious issue, every state, after complement must have transition on every symbol");
						std::set<SetAFAStatesPtr> tmptobeaddedset;
						BOOST_FOREACH(auto singlesetSetStates, tobeaddedset){
							for(std::multimap<std::string, SetAFAStatesPtr>::iterator it= state->mTransitions.equal_range(sym).first; it!=state->mTransitions.equal_range(sym).second; it++){
								SetAFAStatesPtr curr = it->second;
								SetAFAStatesPtr tmp;
								tmp.insert(singlesetSetStates.begin(),singlesetSetStates.end());
								tmp.insert(curr.begin(),curr.end());
								tmptobeaddedset.insert(tmp);
							}
						}
						tobeaddedset.clear();
						tobeaddedset.insert(tmptobeaddedset.begin(),tmptobeaddedset.end());

			}
			BOOST_FOREACH(auto setstates, tobeaddedset){
				if(seenset.find(setstates)==seenset.end()){
					seenset.insert(std::make_pair(setstates,true));
					/*if(sym.compare("0")==0) NOW there will never be a zero on edges hence on sym of AFA.
							workset.insert(std::make_pair(setstates,(word)));
					else
					*/{
						std::string combined = word+sym;
						workset.insert(std::make_pair(setstates,combined));
					}
					}
			}
		}
	}
#ifdef	DBGPRNT
	std::cout<<"No accepted word found"<<std::endl;
#endif
	return "";//means only empty string is accepted here.
}

/**
 * Checks if the given string is accepted by this AFA or not.-- Now not called.
 */
bool AFAut::IsAccepted(std::string word){
	//We need seenset only to avoid self loopon nop symbol.. FOr that also we must keep word as well to check..
	std::multimap<SetAFAStatesPtr,std::string> seenset;
	std::set<std::pair<SetAFAStatesPtr,std::string>> workset;
	SetAFAStatesPtr initset;
	//Dont just put init in the initset if init is of type OR/AND but find all transitions on 0 from here
	if(mInit->mType==OR || mInit->mType==AND){
		std::set<std::string> transkeys  = mInit->getTransitionKeys();

		BOOST_ASSERT_MSG(transkeys.size()==1 && transkeys.find("0")!=transkeys.end(),"Some serious error as AND/OR must have only 0 labeled outgoing transitions");
		BOOST_FOREACH(auto t, mInit->mTransitions){
			workset.insert(std::make_pair(t.second,word));
			seenset.insert(std::make_pair(t.second,word));
		}
	}
	else
	{
		initset.insert(mInit);
		workset.insert(std::make_pair(initset,word));
		seenset.insert(std::make_pair(initset,word));
	}
	//IT is interesting to see that there is a huge similarity between this function and getword function of this class
	//Only difference being that here we only iterate on symbol trying to match and 0 while in getword we iterate over
	//all symbols include 0.
	while(!workset.empty())
	{
		SetAFAStatesPtr elemset = (workset.begin())->first;
		std::string word = (workset.begin())->second;

/*
		std::cout<<"Word to search is "<<word<<std::endl;
		std::cout<<"From states ";
		BOOST_FOREACH(auto t, elemset)
			std::cout<<t->mAMap<<",accepting="<<t->mIsAccepted;
		std::cout<<std::endl;
*/

		workset.erase(workset.begin());
		bool allaccepting=true;
		BOOST_FOREACH(auto t, elemset){
			if(!(t->mIsAccepted))
				allaccepting=false;
		}
		if(allaccepting && word.length()==0)
			return true;
		//NOte that this word can never contain 0 because the word accepted is also not accepting 0..
		//but our AFA can contain 0 and hence it must consider matching 0 derivatives with non consumed rest of the string
		//Otherwise we will not be able to handle things..
		if(word.length()!=0)
		{
			std::string sym(1,word.at(0));
			std::string restofword(word.substr(1));
			std::set<std::string> allsyms;
			allsyms.insert(sym);
			for(std::set<std::string>::iterator it= allsyms.begin(); it!=allsyms.end(); it++){
					std::string sym = *it;
					std::set<SetAFAStatesPtr> tobeaddedset;
					SetAFAStatesPtr emptyset;
					tobeaddedset.insert(emptyset);
					for(SetAFAStatesPtr::iterator itset = elemset.begin(); itset!=elemset.end(); itset++)
					{
						AFAStatePtr state = *itset;
/*
						std::cout<<"Checking transitions on "<<sym<<" from "<< state<<std::endl;
						BOOST_FOREACH(auto w,state->mTransitions)
						std::cout<<w.first<<",";
						std::cout<<std::endl;
*/
						BOOST_ASSERT_MSG(state->mTransitions.find("0")==state->mTransitions.end(),"Somer serious issue, as no transition should have label 0");
						BOOST_ASSERT_MSG(state->mTransitions.find(sym)!=state->mTransitions.end(),"Somer serious issue, as after complementation (which it is) every state must have ");
//							std::cout<<"checking for "<<sym<<" inside"<<std::endl;
								std::set<SetAFAStatesPtr> tmptobeaddedset;
								BOOST_FOREACH(auto singlesetSetStates, tobeaddedset){
									for(std::multimap<std::string, SetAFAStatesPtr>::iterator it= state->mTransitions.equal_range(sym).first; it!=state->mTransitions.equal_range(sym).second; it++){
										SetAFAStatesPtr curr = it->second;
										SetAFAStatesPtr tmp;
										tmp.insert(singlesetSetStates.begin(),singlesetSetStates.end());
										tmp.insert(curr.begin(),curr.end());
										tmptobeaddedset.insert(tmp);
									}
								}
								tobeaddedset.clear();
								tobeaddedset.insert(tmptobeaddedset.begin(),tmptobeaddedset.end());

						}

					BOOST_FOREACH(auto setstates, tobeaddedset){
						if(seenset.find(setstates)==seenset.end()){
							//means not seen already, add to seenset and workingset
							seenset.insert(std::make_pair(setstates,restofword));
							workset.insert(std::make_pair(setstates,restofword));

							} else if(seenset.find(setstates)!=seenset.end())//present
							{
								//now check if the word is same as the one being added here..
								std::set<std::string> sset;
	for(std::multimap<SetAFAStatesPtr,std::string>::iterator it = seenset.equal_range(setstates).first; it!=seenset.equal_range(setstates).second; it++)
	{
		sset.insert(it->second);
	}
								if(sset.find(restofword)==sset.end()){//means not in the set of string for this setstates.
//									std::cout<<"added"<<std::endl;
									seenset.insert(std::make_pair(setstates,restofword));
									workset.insert(std::make_pair(setstates,restofword));
								}
							}
					}
				}
		}
		//returning false immediately here does not make sense unless we have explored all possible cases..
	}
#ifdef	DBGPRNT
	std::cout<<"WOrd not found"<<std::endl;
#endif
 return false;//means this word was not accepted
}

typedef std::tuple<faudes::Idx,std::set<AFAStatePtr>> GenAFATuple;
struct GenAFAComparator{
	bool operator()(const GenAFATuple& one, const GenAFATuple& two) const{
		if(std::get<0>(one)==std::get<0>(two))
			return (std::get<1>(one)<std::get<1>(two));
		else
			return (std::get<0>(one)<std::get<0>(two));
	}
};

struct customcomp{
	bool operator() (const std::pair<std::set<AFAStatePtr>,std::string>& one, const std::pair<std::set<AFAStatePtr>,std::string>& two) const
	{
		bool res = std::includes(one.first.begin(), one.first.end(), two.first.begin(), two.first.end());
		if(one.second==two.second)
			if(one.first.size()<two.first.size() && !res)
				return true;
			else
				return false;
		return one<two;
	}
};


void AFAut::Intersection(faudes::Generator& rGen, faudes::Generator& rRes, std::map<faudes::Idx,faudes::Idx>& oldNewInitStatesMap)
{

	std::map<GenAFATuple, faudes::Idx, GenAFAComparator> seenmap;
	std::set<GenAFATuple, GenAFAComparator> workset;

	//Insert events in rRes..
	//std::cout<<"Inserting "<<mProgram->mAllSyms.size()<<" entries in resgen"<<std::endl;
	BOOST_FOREACH(auto sym, mProgram->mAllSyms)
	{
//		std::cout<<"Inserting event "<<sym<<" in intersected gen"<<std::endl;
		rRes.InsEvent(sym);
	}
	//std::cout<<"Ins over"<<std::endl;
	//get initial states of afa and mix with init states of Gen to create new tuples..
//	PrintToDot("final.dot");
//	std::cout<<"printing done"<<std::endl;
	if(mInit->mType==ORLit){
		 for(faudes::StateSet::Iterator lit = rGen.InitStatesBegin(); lit != rGen.InitStatesEnd(); ++lit)
			  {
				  faudes::Idx state=*lit;
				  std::set<AFAStatePtr> setnxt;
				  setnxt.insert(mInit);
				  GenAFATuple entry = std::make_tuple(state,setnxt);
				  faudes::Idx stid = rRes.InsState();
				  rRes.SetInitState(stid);
				  oldNewInitStatesMap.insert(std::make_pair(state,stid));
				  seenmap.insert(std::make_pair(entry,stid));
				  workset.insert(entry);
			  }
	}else{
	  for(faudes::StateSet::Iterator lit = rGen.InitStatesBegin(); lit != rGen.InitStatesEnd(); ++lit)
	  {
		    faudes::Idx state=*lit;
		    BOOST_FOREACH(auto trans, mInit->mTransitions){
		  	BOOST_ASSERT_MSG(trans.first=="0","Some serious error");
		  	std::set<AFAStatePtr> setnxt(trans.second.begin(),trans.second.end());
		  	GenAFATuple entry = std::make_tuple(state,setnxt);
		  	faudes::Idx stid = rRes.InsState();
		  	rRes.SetInitState(stid);
		  	oldNewInitStatesMap.insert(std::make_pair(state,stid));
		  	seenmap.insert(std::make_pair(entry,stid));
		  	workset.insert(entry);
		  }
	  }
	}
	///Now iterate over workset till it becomes empty..
	while(!workset.empty())
	{
		GenAFATuple thistuple = *(workset.begin());
		workset.erase(workset.begin());
		BOOST_ASSERT_MSG(seenmap.find(thistuple)!=seenmap.end(),"Some serious issue, this element must be present");
		faudes::Idx mappedthistuple = seenmap.find(thistuple)->second;

		faudes::Idx gensrc = std::get<0>(thistuple);
		std::set<AFAStatePtr> afastates = std::get<1>(thistuple);
		//if genstate is marked and all states in afastaes are accepting then mark mappedthistuple as marked..
		bool allacc=true;
		BOOST_FOREACH(auto st, afastates){
			if(!st->mIsAccepted){
				allacc=false; break;
			}
		}
		/*if(rGen.MarkedStates().Find(gensrc)!=rGen.MarkedStatesEnd())
			std::cout<<"gen has marked state"<<std::endl;
		if(allacc)
			std::cout<<"One tuple has all as marked"<<std::endl;*/
		if(allacc && rGen.MarkedStates().Find(gensrc)!=rGen.MarkedStatesEnd())
		{
//			std::cout<<"Found one marked state"<<std::endl;
			rRes.SetMarkedState(mappedthistuple);
		}


		//find transitions out of genstate.. and iterate over them..
		for(faudes::TransSet::Iterator lit = rGen.TransRelBegin(gensrc);lit!=rGen.TransRelEnd(gensrc);lit++)
		{
			std::string sym(rGen.EventName(lit->Ev));
			faudes::Idx gendest = lit->X2;
			//return the set of transitions from afastates on sym
			std::set<std::set<AFAStatePtr>> res=GetConjunctedTransitions(afastates,sym);
			BOOST_FOREACH(auto trans, res)
			{
				//preapare a new tuple with gendest and trans..
				GenAFATuple entry = std::make_tuple(gendest,trans);
				faudes::Idx residx;
				if(seenmap.find(entry)==seenmap.end())
				{
					residx = rRes.InsState();
					seenmap.insert(std::make_pair(entry,residx));
					workset.insert(entry);
				}else
				{
					residx = seenmap.find(entry)->second;
				}
				//add a transition from mappedthistuple to residx
				rRes.SetTransition(mappedthistuple,lit->Ev,residx);
			}
		}

	}
#ifdef DBGPRNT
	rGen.DotWrite("Original.dot");
	this->PrintToDot("subtracted.dot");
	std::cout<<"After Intersection before coacc: States = "<<rRes.States().Size()<<" trans = "<<rRes.TransRel().Size()<<std::endl;
#endif
	//std::cout<<"done intersection"<<std::endl;
	//std::cout<<"After Intersection: States = "<<rRes.States().Size()<<" trans = "<<rRes.TransRel().Size()<<std::endl;
	rRes.Coaccessible();//make it coaccessible..
	//std::cout<<"done coaccessible"<<std::endl;
	std::cout<<"After Intersection: States = "<<rRes.States().Size()<<" trans = "<<rRes.TransRel().Size()<<std::endl;
#ifdef DBGPRNT
	std::cout<<"After Intersection after coacc: States = "<<rRes.States().Size()<<" trans = "<<rRes.TransRel().Size()<<std::endl;
	rRes.DotWrite("After Intersection.dot");
#endif
}


/*
struct fa* AFAut::ConvertToNFA(){
	struct fa* nfa = fa_make_empty();
	std::map<SetAFAStatesPtr, struct autstate*> seenmap;
	std::set<SetAFAStatesPtr> workset;
	struct autstate* init;
	std::set<std::tuple<struct autstate*,struct autstate*>> epsilonset;
	if(mInit->mType!=ORLit)
	{
		init=add_autstate(nfa,0);
		BOOST_FOREACH(auto t, mInit->mTransitions){
			if(seenmap.find(t.second)!=seenmap.end()){
//				add_epsilon_trans(init,seenmap.find(t.second)->second);
				//do nothing as epsilon must have been added before putting it here from init (next block)
			}else{
				//create a new state..
				struct autstate* newst = add_autstate(nfa,0);
				seenmap.insert(std::make_pair(t.second,newst));
				workset.insert(t.second);
				epsilonset.insert(std::make_pair(init,newst));
				//add_epsilon_trans(init,newst); we cant add epsilon directly only after every thing has been added..
			}

		}
	}else{
		SetAFAStatesPtr newstset;
		newstset.insert(mInit);
		//create a new state..
		struct autstate* newst = add_autstate(nfa,0);
		seenmap.insert(std::make_pair(newstset,newst));
		workset.insert(newstset);
		init=newst;
	}


	nfa->initial=init;
	while(!workset.empty()){
		//dont forget to put some states as accepting states as well.
		SetAFAStatesPtr setstates = *(workset.begin());
		workset.erase(workset.begin());
		//if it is in workset it means some autstate* must have been assigned to this set of afa states..
#ifdef	DEBUGSTMTS
		BOOST_ASSERT_MSG(seenmap.find(setstates)!=seenmap.end(),"Some serious issue as by this time it must have been added here");
#endif
		std::set<std::string> allsyms(mProgram->mAllSyms.begin(),mProgram->mAllSyms.end());
		struct autstate* curr = seenmap.find(setstates)->second;
		//check if this can be set as an accepting state.. by checking every state in setstates is accepting..
		bool allaccepting=true;
		BOOST_FOREACH(auto t, setstates){
				if(!(t->mIsAccepted)){
						allaccepting=false;
					}
		}
		if(allaccepting)
			curr->accept=1;//set it as accepting state.

		BOOST_FOREACH(auto sym, allsyms){
			std::set<SetAFAStatesPtr> tobeaddedset;
			SetAFAStatesPtr emptyset;
			tobeaddedset.insert(emptyset);
			BOOST_FOREACH(auto state, setstates){
				if(state->mTransitions.find(sym)==state->mTransitions.end()){
					tobeaddedset.clear();//This is necessary to avoid executing the loop with partially filled tobeaddedset
					break;//means now we can not proceed to have an outgoing edge on this  symbol because at least one
					//does not have that..
				}
				std::set<SetAFAStatesPtr> tmptobeaddedset;
				BOOST_FOREACH(auto w, tobeaddedset){

					for(std::multimap<std::string, SetAFAStatesPtr>::iterator it= state->mTransitions.equal_range(sym).first; it!= state->mTransitions.equal_range(sym).second; it++)
					{
						SetAFAStatesPtr tmp = it->second;
						SetAFAStatesPtr tobeadded(w.begin(),w.end());
						tobeadded.insert(tmp.begin(),tmp.end());
						tmptobeaddedset.insert(tobeadded);
					}

				}
				tobeaddedset.clear();
				tobeaddedset.insert(tmptobeaddedset.begin(),tmptobeaddedset.end());

			}
			//now we have tobeaddedset ready.. for sym on this state transitions are to these states..
			BOOST_FOREACH(auto setst, tobeaddedset){
				if(seenmap.find(setst)!=seenmap.end()){
					struct autstate* dest = seenmap.find(setst)->second;
					add_new_auttrans(curr,dest,sym.at(0),sym.at(0));
				}else{
					//create a new aut state..
					struct autstate* newdest = add_autstate(nfa,0);
					//put to seenmap
					seenmap.insert(std::make_pair(setst,newdest));
					//put to worklist
					workset.insert(setst);
					add_new_auttrans(curr,newdest,sym.at(0),sym.at(0));
				}
			}

		}

	}

	BOOST_FOREACH(auto t, epsilonset){
		add_epsilon_trans(std::get<0>(t),std::get<1>(t));//this will trigger a saturation
	}

	return nfa;


}
*/

bool AFAut::IsUnsafe(){
	z3::expr wp(*(mInit->mHMap));
	z3::expr falseformula = mInit->mAMap.ctx().bool_val(false);
	if(eq(wp,falseformula))
		return false;
	else
		return true;
}


/*******
 * This function constructs a value flow relation from a proof AFA
 * Used for TSO/PSO analysis when, after finding that the program reaches erroneous state we
 * first want to come up with the set of value flow relations (essential) which contributed to
 * deriving true as the weakest precondition.
 */
RFRelPairs AFAut::GetRFRelationFromProof(AFAStatePtr st, TSOTransSystem& tsotranssystem, std::string& trace, std::map<AFAStatePtr,RFRelPairs>& memoized)
{
	VarDefInfo vdinfo;
	VarUseDefRel vusedefrelrfe;
	VarUseDefRel vusedefrelrfi;
	if(st->mIsAccepted)
		return std::make_tuple(vdinfo,vusedefrelrfe,vusedefrelrfi);//if it is an accepting stte return the empty set
	else if(memoized.find(st)!=memoized.end())
		return memoized[st];
	else
	{
		//For each successor state of st along some edge say e.. call this function recursively
		//and recieve rf relation along that path
		//INV: by this time every state must have only one transition.. in case of AND(uinversal) state
		//one transition only but its set willhave two states.
		BOOST_ASSERT_MSG(st->mTransitions.size()==1," Some serious error in invariant, check");
		for(const auto& elem: st->mTransitions)
		{
			std::string sym=elem.first;
			if(elem.second.size()!=1)
				BOOST_ASSERT_MSG(sym.compare("0")==0, " Some invariant eror, by this time only 0 linked transition can have more than one outgoing edges");
			for(const AFAStatePtr& s: elem.second)
			{
				RFRelPairs retv=GetRFRelationFromProof(s,tsotranssystem,trace,memoized);
				//After getting rf relation..copy it to result.. make sure no conflict
				//Here conflict means that different values (either vdinfo or relation) appear along
				//different branches going out from this state which should not be true.
				VarDefInfo retvdinfo=std::get<0>(retv);
				VarUseDefRel retvusedefrelrfe=std::get<1>(retv);
				VarUseDefRel retvusedefrelrfi=std::get<2>(retv);

				for(const auto& e: retvdinfo)
				{

					if(vdinfo.find(e.first)!=vdinfo.end())
					{
						//assign the one that is latest..between e.second and vdinfo[e.first]
						if(e.second.find(vdinfo[e.first])!=-1)
						{
							//e.second contains vdinfo[e.first] hence use longer one..(NO smaller one, one near end..)
							//vdinfo[e.first]=e.second;
						}else if(vdinfo[e.first].find(e.second)!=-1)
						{
							vdinfo[e.first]=e.second;
						}else
							BOOST_ASSERT_MSG(false, "SOme error, it should not be the case");

					}
					else

						vdinfo[e.first]=e.second;
				}
				for(const auto& e: retvusedefrelrfe)
				{
					if(vusedefrelrfe.find(e.first)!=vusedefrelrfe.end())
						BOOST_ASSERT_MSG(vusedefrelrfe[e.first]==e.second," Some serious error look carefully");
					else
						vusedefrelrfe[e.first]=e.second;
				}
				for(const auto& e: retvusedefrelrfi)
				{
					if(vusedefrelrfi.find(e.first)!=vusedefrelrfi.end())
						BOOST_ASSERT_MSG(vusedefrelrfi[e.first]==e.second," Some serious error look carefully");
					else
						vusedefrelrfi[e.first]=e.second;
				}

//				std::cout<<"After copy of return size is "<<vdinfo.size()<< " and "<<vusedefrel.size()<<std::endl;
				////////////////Consistency check over..
				//get the symbol (prefix closed) based on st->mRWord and the edge
				//label.. do it only if label is not epsilon or assume
				if(sym.compare("0")!=0 && mProgram->mSymType[sym]!="assume")
				{
//					std::cout<<"Sym is "<<sym<<std::endl;
					//then it must be a read or write symbol..in mRWLRMap..
					//BOOST_ASSERT_MSG(mProgram->mRWLHRHMap.find(sym)!=mProgram->mRWLHRHMap.end(),"Some serious invariant error, look crefully");
					//Above invariant no longer holds if sym is of lcas type as well
					//I am modifying GetDefVar and GetUseVars function below in case sym is lcas..
					//get def var of sym
					std::string def=mProgram->GetDefVar(sym);
					//get use vars of sym
					std::set<std::string> uses=mProgram->GetUseVars(sym);
					//get suffix of mRWord starting from sym
					std::string cp(st->mRWord);
					boost::char_separator<char> sep(".");
					    boost::tokenizer<boost::char_separator<char>> tokens(st->mRWord, sep);
					    for (const auto& t : tokens) {
					        if(t==sym)
					                break;
					        cp.erase(0,t.length()+1);
					    }
				   //     std::cout<<" Symbol name is "<<cp<<std::endl;
				   std::string thissym(cp);
/*
				   std::cout<<" def is "<<def<<" thissym is "<<thissym<<std::endl;
				   std::cout<<" use is  "<<std::endl;

				   for(auto tt: uses)
					   std::cout<<tt<<",";
				   std::cout<<std::endl;
				   */
  				   //update the information based on this symbol type..(directly in result)
				   //add def-thissym mapping in vdinfo (checking the conflict)
				   //only if it is s awrit esymbol with lhs as a shared variable
				   if(mProgram->mSymType[sym]=="write")
				   {
//					   std::cout<<sym<<" is a write"<<std::endl;
					   if(mProgram->mGlobalVars.find(def)!=mProgram->mGlobalVars.end())
					   {
//						   std::cout<<def<<" ia a global var"<<std::endl;
						   std::string chopandrevthissym=ChopAndReverse(trace,thissym);
						   //INTERSTING Finding: no need to check here if it already exists and is sam
						   //because it is possible that it already exists from past but this sym
						   //is going to redefine that var again.. so checking fo rconcsistency will
						   //only be needed in starting as we are doing in the start of the loop.
	//					   if(vdinfo.find(def)!=vdinfo.end()){
//							   BOOST_ASSERT_MSG(vdinfo.find(def)->second==chopandrevthissym," Some serious error.. this def is already set to differnt symbol.. not possible");
		//				   }
			//			   else{
							   vdinfo[def]=chopandrevthissym;
				//		   }

					   }
					   //else
//						   std::cout<<def<<" is not a global var"<<std::endl;

				   }
				  /* else
					   std::cout<<sym<<" is a not a write"<<std::endl;*/
				   //if sym is a read symbol such that its rhs is a global variable then find
				   //the last write done to this global variable and let that sym be defsym
				   //add defsym-thissym in vusedefrel relation (while checking the conflict as well)
				   else if(mProgram->mSymType[sym]=="read")
				   {
//					   std::cout<<sym<<" is a read"<<std::endl;
					   if(uses.size()==1)
					   {
//						   std::cout<<"use size  is 1"<<std::endl;
						   std::string useg=*(uses.begin());
						   if(mProgram->mGlobalVars.find(useg)!=mProgram->mGlobalVars.end())
						   {
//							   std::cout<<useg<<" ia a global var"<<std::endl;
							   //get last mod symbol that defines this global variable..
							   //this must be defined..
//							   BOOST_ASSERT_MSG(vdinfo.find(useg)!=vdinfo.end()," Some serious issue by now this def must be there ");
							   std::string lastmod=vdinfo[useg];
							   std::string chopandrevthissysm=ChopAndReverse(trace,thissym);
							   //std::string chopandrevlastmode=ChopAndReverse(trace,lastmod);
							   //IMP: no need to reverse and chop what was in vdinfo as it must have been already so
							   if(vusedefrelrfe.find(chopandrevthissysm)!=vusedefrelrfe.end())
								   BOOST_ASSERT_MSG(vusedefrelrfe[chopandrevthissysm]==lastmod," Some serious issue in conflicting information ");
							   else{
								   vusedefrelrfe[chopandrevthissysm]=lastmod;
							   }
						   }/*else
							   std::cout<<useg<<" is not global var"<<std::endl;means of the form l(index)=l, not interesting*/
					   }/*else
						   std::cout<<"use size  is not 1"<<std::endl;*/
					   if(tsotranssystem.mLocalRFMap.find(sym)!=tsotranssystem.mLocalRFMap.end())
					   {
#ifdef DBG
							std::cout<<"----------_Symbol "<<sym<<" is a local read"<<std::endl;
#endif

						   //BOOST_ASSERT_MSG(false," Intersting.. it means a rfi contributed to making it error.. first analyze this example and then we can safely comment it as I think this case has been handled carefulll");
						   //means it is a local rf information, encode this rfi information
						   std::string locwritesym = tsotranssystem.mLocalRFMap[sym];
						   //remove thissysm suffix from trace
						   //find last occurrence of locwritesym before thissym in trace
						   /*
						    * int aa=ss.rfind("5.6.8.5.7.3133.9");
								int bb =ss.rfind("3133",aa);
								std::cout<<ss.substr(0,bb+1);
						    *
						    */
						   int a=trace.rfind(thissym);
						   int b=trace.rfind(locwritesym,a);
#ifdef DBG
						   std::cout<<sym<<" is alocal read sym read from "<<locwritesym<<std::endl;
#endif
						   //BOOST_ASSERT_MSG(b!=-1," Some error ");
						   /*
						    * Found intersting scenario when local read happende but the element in the
						    * buffer was not flused in the trace hence it does not appear..Whereas
						    * we were asserting that locwritesym must appear as part of the trace
						    * hence now we change this assert.. in fact we will encode this rfi only
						    * if the corresponding write was also present..
						    * BOOST_ASSERT_MSG(b!=-1," Some error "); commented
						    * IMP thing is-- will this rf have any impact in finding fences..??
						    */
						   if(b!=-1){
							   std::string locwrite=trace.substr(0,b+1);
#ifdef DBG
							   std::cout<<"Read from "<<locwrite<<std::endl;
#endif
							   std::string chopandrevthissym=ChopAndReverse(trace,thissym);
							   std::reverse(locwrite.begin(),locwrite.end());
							   //add to rf
							   if(vusedefrelrfi.find(chopandrevthissym)!=vusedefrelrfi.end())
								   BOOST_ASSERT_MSG(vusedefrelrfi[chopandrevthissym]==locwrite," Some serious error look carefully");
							   else
								   vusedefrelrfi[chopandrevthissym]=locwrite;
						   }
					   }else{
#ifdef DBG
						   std::cout<<"----------_Symbol "<<sym<<" is a not a local read"<<std::endl;
#endif
					   }
				   }else if(mProgram->mSymType[sym]=="lcas")//if lcas symboll
				   {
					   //get the var that is being used.. first argument from casrwmap of program object
					   //find last def of this variable..
					   //construct rf from def and this use..
					   std::string useg=*(uses.begin());
					   std::string lastmod=vdinfo[useg];
					   std::string chopandrevthissysm=ChopAndReverse(trace,thissym);
					   //std::string chopandrevlastmode=ChopAndReverse(trace,lastmod);
					  	//IMP: no need to reverse and chop what was in vdinfo as it must have been already so
					  	if(vusedefrelrfe.find(chopandrevthissysm)!=vusedefrelrfe.end())
					  		BOOST_ASSERT_MSG(vusedefrelrfe[chopandrevthissysm]==lastmod," Some serious issue in conflicting information ");
					  	else{
					  		vusedefrelrfe[chopandrevthissysm]=lastmod;
					  	}
					  	//after putting in rf put in def part as well..
					  	//INTERSTING Finding: no need to check here if it already exists and is sam
					  	//because it is possible that it already exists from past but this sym
					  	//is going to redefine that var again.. so checking fo rconcsistency will
					  	//only be needed in starting as we are doing in the start of the loop.
					  	//if(vdinfo.find(def)!=vdinfo.end()){
					  	//BOOST_ASSERT_MSG(vdinfo.find(def)->second==chopandrevthissym," Some serious error.. this def is already set to differnt symbol.. not possible");
					  	//				   }
					  	//			   else{
					  	//put this symbol as def of variable also.. as lcas is both read and write operation
					  	vdinfo[useg]=chopandrevthissysm;
				   }else
					   BOOST_ASSERT_MSG(false," No valid symbol found, serious error look carefully");
				   /*else
					   std::cout<<sym<<" is not a read"<<std::endl;*/
				}

			}//end of stateset iteration
		}
		//return this rf relation constructed so far.
//		std::cout<<" return map size is "<<vdinfo.size()<<", and "<<vusedefrel.size()<<std::endl;
		memoized[st]=std::make_tuple(vdinfo,vusedefrelrfe,vusedefrelrfi);
		return std::make_tuple(vdinfo,vusedefrelrfe,vusedefrelrfi);
	}


}

std::string AFAut::ChopAndReverse(std::string& orig, std::string& mrword)
{

	//dont do rfind till mrword because we want to retain the first occurrence of the mrword..
	//so extract first one from mrword
	boost::char_separator<char> sep(".");
	std::string tmpmrword=mrword;
	boost::tokenizer<boost::char_separator<char>> tokens1(mrword, sep);
	for(const std::string& sym: tokens1){
		tmpmrword.erase(0,sym.length()+1);
		break;
	}

//A speical case happens when orig is 2.3.4 and mrword is 4
	//then we would like to keep thing as it is..i.e. 4.3.2, therefore we increase aa by 1 because in this case . does not appear after what is left
	int aa = orig.rfind(tmpmrword);
	if(tmpmrword.length()==0)
		aa=aa+1;
	std::string tmporig=orig.substr(0,aa-1);
	std::string rev="";
	boost::tokenizer<boost::char_separator<char>> tokens(tmporig, sep);

		//reverse and remove intial value writes from the trace.
		for (const std::string& sym: tokens)
		{
			if(rev.length()==0)
				rev=sym;
			else
				rev=sym+"."+rev;

		}
	//std::cout<<"Choprev of "<<orig<<", and "<<mrword<<" is "<<rev<<std::endl;
return rev;
}



AFAut::~AFAut() {
	//This destructor will traverse over the automaton starting from init and store the set of AFA states in a set.
	//after completing the traversal it calls delete on each one of them.
	std::map<AFAStatePtr,bool> seenset;
	SetAFAStatesPtr workset;
	if(mInit!=NULL){


			workset.insert(mInit);
			seenset.insert(std::make_pair(mInit,true));
			while(!workset.empty())
			{
				AFAStatePtr st = *(workset.begin());
				workset.erase(workset.begin());
				BOOST_FOREACH(auto v, st->mTransitions )
				{
					BOOST_FOREACH(auto t, v.second){
						if(seenset.find(t)==seenset.end())//means not seen already.. add to seenset and workset
						{
							seenset.insert(std::make_pair(t,true));
							workset.insert(t);
						}
					}
				}
			}
			//when finished.. call destructor on every key of seenset
			BOOST_FOREACH(auto t, seenset){
				delete t.first;
			}
	}
}

