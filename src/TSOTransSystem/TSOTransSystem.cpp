#include "../AFA/AFAState.h"
//another strange behaviour.. putting AFAState.h after TSOTransSystem also produces lot of errors..
#include "TSOTransSystem.h"



TSOTransSystem::TSOTransSystem(Program& prog,z3::solver& s): mProgram(prog), mSolver(s)
{
mTSOProgram = new Program((*mProgram.mFileName).c_str(),mProgram.mCtx,mProgram.mParser);
mTSOProgram->mGlobalVars=mProgram.mGlobalVars;
}

std::set<SymStatePair> TSOTransSystem::StepConcrete(ThdId tid, const TSOState& st)
{
	std::set<SymStatePair> nextsymstates;


	//get the next instruction to be executed by tid based on its control state..
	BOOST_ASSERT_MSG(st.getCState(tid)!=NULL,"Some serious issue as control state of a process should be valid");
	autstate* current = st.getCState(tid);

	//for each next state from thi scontrol lstate..find corresponding labels..
	//then do a case analysis on label..
	//if read
	//if write
	//if assume
	//if fence
	//if sfence (in case of PSO)

	for(int i=0; i< current ->tused; i++)
	{

		struct auttrans trans = current->trans[i];
		//find the destination state
		struct autstate* dest = trans.to;
		std::string sym(1,trans.min);
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
			z3::expr rhs=GetLastWrite(tid, rhsstr, st, res);
			//std::cout<<"Checking if "<<rhsstr<<" is present in buffer "<<std::endl;
			if(res)
			{
				//check if a symbol with lhs as lhsstr and rhs as rhs is present or not..
				std::pair<z3::expr,z3::expr> ExprPair=std::make_pair(lhs,rhs);
				std::string newsym;
				if(mExprToSymbMap.find(ExprPair)==mExprToSymbMap.end())
				{
					//assign a new symbol to this stuff..
					int t;
					if(mChangedWriteReadSymbmap.find(sym)==mChangedWriteReadSymbmap.end())
						t=1;
					else
						t=mChangedWriteReadSymbmap[sym];
					mChangedWriteReadSymbmap[sym]=t+1;
					newsym=sym+std::to_string(t);
					mExprToSymbMap.insert(std::make_pair(ExprPair,newsym));
					mNewOldSymbMap[newsym]=sym;
					//add newsymbol and substituted pr.second to the new program object..
					mTSOProgram->mRWLHRHMap.insert(std::make_pair(newsym,ExprPair));
					mTSOProgram->mAllSyms.push_back(newsym);
					mTSOProgram->mSymType[newsym]="read";

				}else
				{
					newsym=mExprToSymbMap.find(ExprPair)->second;
				}
				std::set<std::string> symset;
				symset.insert(newsym);
				nextsymstates.insert(std::make_pair(symset,newst));
			}else
			{
				//means no symbol present in buffer of tid.. just put this symbol as such..
				//put same entries in newprogram object as ni old..
				mTSOProgram->mRWLHRHMap.insert(std::make_pair(sym,mProgram.mRWLHRHMap.find(sym)->second));
				mTSOProgram->mSymType[sym]=mProgram.mSymType[sym];
				mTSOProgram->mAllSyms.push_back(sym);
				std::set<std::string> symset;
				symset.insert(sym);
				nextsymstates.insert(std::make_pair(symset,newst));

			}
			//add sym and nestate to the set of symstate pair to be returned later.

		}else if(mProgram.mSymType[sym].compare("write")==0)
		{
			//proceed only if buffer is not full
			if(!st.isBuffFull(tid))
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
			//put same entries in newprogram object as ni old..
			mTSOProgram->mAssumeLHRHMap.insert(std::make_pair(sym,mProgram.mAssumeLHRHMap.find(sym)->second));
			mTSOProgram->mRevAssumeLHRHMap.insert(std::make_pair(mProgram.mAssumeLHRHMap.find(sym)->second,sym));
			mTSOProgram->mSymType[sym]=mProgram.mSymType[sym];
			mTSOProgram->mAllSyms.push_back(sym);
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
			BOOST_ASSERT_MSG(false,"Op sem of LCAS under TSO is not sure. So lets keep it for future work");
			//proceed only if buffer is emtpy..
			if(st.isBuffEmpty(tid))
			{
				//same as in read above..
				//put same entries in newprogram object as ni old..
				//create a new state copying the current one..
				//change control state to dest in new one..
				//return sym and new state..
			}

		}else if(mProgram.mSymType[sym].compare("mfence")==0)
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

		}else if(mProgram.mSymType[sym].compare("sfence")==0)
		{
			//TODO for PSO mem model
			BOOST_ASSERT_MSG(false,"No sfence instruction for TSO memory model");
		}
		else
			BOOST_ASSERT_MSG(false,"Some serious error happend");

	}


return nextsymstates;
}


std::pair<std::set<std::string>,std::set<std::string>> TSOTransSystem::GetNewWriteReadSyms(std::string oldsym, ThdId tid, const TSOState& st, TSOState& newst)
{
	//from mProgram object get the z3 exprs left and write corresponding to oldsym
	BOOST_ASSERT_MSG(mProgram.mRWLHRHMap.find(oldsym)!=mProgram.mRWLHRHMap.end()," Some serious error");
	std::tuple<z3::expr,z3::expr> pr = mProgram.mRWLHRHMap.find(oldsym)->second;
	std::set<std::string> writesymset;
	std::set<std::string> readsymset;
	//first part of the pair is lhs (i.e. variable.. and the second part is the expressions)
	//we will keep the first part same.. and process the second part..
	//1. find the variables from the expressions pr.second
	std::set<z3::expr,mapexpcomparator> freevars = AFAState::HelperGetFreeVars(std::get<1>(pr));
	std::map<std::string, int> mapstr;
	z3::expr_vector src(mProgram.mCtx),dest(mProgram.mCtx);

	//2. for each of these variables get the current LI for
	for(z3::expr var: freevars)
	{
		//get string form of var..
		std::stringstream streams;
		streams<<var;
		std::string varstr(streams.str());
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
		if(mTSOProgram->mRWLHRHMap.find(concatstr)==mTSOProgram->mRWLHRHMap.end())
		{
			mTSOProgram->mRWLHRHMap.insert(std::make_pair(concatstr,std::make_pair(newexp,var)));
			mTSOProgram->mAllSyms.push_back(concatstr);
			mTSOProgram->mSymType[concatstr]="read";
			readsymset.insert(concatstr);
		}else
		{
			//means this read has been added earlier..[here we give the symbol same name as of local var]
			//so make sure that name of local var do not clash with the name of some label in the
			//original program
			readsymset.insert(concatstr);
		}
		//create a substitution order saying replace z3::expr with new z3::expr (concatented one)
		src.push_back(var);
		dest.push_back(newexp);
	}
	if(!freevars.empty())
	{//when done check if oldsym, varstring int map is already seen or not..
		z3::expr rhs(std::get<1>(pr));
		z3::expr l3(rhs.substitute(src,dest));
		std::pair<z3::expr,z3::expr> ExprAssn=std::make_pair(std::get<0>(pr),l3);
		if(mExprToSymbMap.find(ExprAssn)==mExprToSymbMap.end())
		{
			//assign a new symbol to this stuff..
			int t;
			if(mChangedWriteReadSymbmap.find(oldsym)==mChangedWriteReadSymbmap.end())
				t=1;
			else
				t=mChangedWriteReadSymbmap[oldsym];
			mChangedWriteReadSymbmap[oldsym]=t+1;
			std::string newsym(oldsym+std::to_string(t));
			mExprToSymbMap.insert(std::make_pair(ExprAssn,newsym));
			mNewOldSymbMap[newsym]=oldsym;
			//add newsymbol and substituted pr.second to the new program object..
			mTSOProgram->mRWLHRHMap.insert(std::make_pair(newsym,std::make_pair(std::get<0>(pr),l3)));
			mTSOProgram->mAllSyms.push_back(newsym);
			mTSOProgram->mSymType[newsym]="write";
			//return newsymbol
			writesymset.insert(newsym);
		}else
		{//else
			//get the already seen mapping and return it..
			writesymset.insert(mExprToSymbMap.find(ExprAssn)->second);
		}
	}
	else
	{
		//else return oldsym directly by adding its info in new program object as well..
		mTSOProgram->mRWLHRHMap.insert(std::make_pair(oldsym,mProgram.mRWLHRHMap.find(oldsym)->second));
		mTSOProgram->mAllSyms.push_back(oldsym);
		mTSOProgram->mSymType[oldsym]="write";
		//return newsymbol
		writesymset.insert(oldsym);
	}

	return std::make_pair(writesymset,readsymset);

}


std::set<SymStatePair> TSOTransSystem::StepFlush(ThdId tid, const TSOState& st)
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
	std::vector<std::string> regexes = mProgram.GetRegexOfAllProcesses();
	std::map<std::string,z3::expr> assnMap = mProgram.GetAssnMapForAllProcesses();
	std::vector<struct fa*> automata;
	for(std::string regex: regexes)
	{
		#ifdef	DBGPRNT
		std::cout<<"Extracted Regex is "<<regex<<std::endl;
		#endif
		//construct an automaton
		struct fa* aut;
		int res = fa_compile(regex.c_str(),(size_t)regex.length(),&aut);
		BOOST_ASSERT_MSG(aut!=NULL,"could not construct the automaton from a given expression");
		automata.push_back(aut);
	}
	int numprocesses = automata.size();
	//create an initial state with control locations set to initial state of each process automaton.
	TSOState inittso(buffbound,numprocesses);
	//set initstate's process cs from automata.
	int i=1;
	for(struct fa* aut: automata)
	{
		inittso.setCState(i,aut->initial);
		i++;
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
		TSOState st=*(workset.begin());
		workset.erase(st);
		dbgCount++;
		//get its associated generator state
		BOOST_ASSERT_MSG(statemap.find(st)!=statemap.end(),"Some serious error look carefully");
		faudes::Idx sourcest=statemap[st];
		//for each threadid find next transitions (concrete and flush from state st)
		for(int i=1; i<=numprocesses; i++)
		{
			std::set<SymStatePair> nextconcstates(StepConcrete(i,st));
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
							if(statemap.find(nextst)==statemap.end())
							{
								statemap[nextst]=lGen.InsState();
								//add to worklist
								workset.insert(nextst);
							}
						//add an edge from sourcest to this state on symbol sym.
						lGen.SetTransition(tmpsource,ev,statemap[nextst]);
						}else{
							//create intermediate states not putting them to workset and statemap
							faudes::Idx tt=lGen.InsState();
							lGen.SetTransition(tmpsource,ev,tt);
							tmpsource=tt;
						}
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
		bool isacc=false;
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
		}
	}//end of whileloop workset empty
//	std::cout<<"Number of states are "<<dbgCount<<","<<lGen.States().Size()<<std::endl;
	faudes::Idx stt;
	std::string wd = lGen.GetWord(stt);
	std::cout<<"Accepted word one is "<<wd<<std::endl;
//projecting out from language with alphabet not containing epsilon
	faudes::EventSet evset;
	for(std::string sym: mTSOProgram->mAllSyms)
		evset.Insert(sym);
	//check that this set is same as the one on which evetns were inserted minus epsilon..
	//good to have this check..
	std::map<faudes::Idx,faudes::StateSet> changedSetMap;
	faudes::Project(lGen,evset,changedSetMap,resultgen);
	std::cout<<"Number of states after projection are "<<dbgCount<<","<<resultgen.States().Size()<<std::endl;
	//minimize the states..
	std::vector<faudes::StateSet> subsetvec;
	std::vector<faudes::Idx> statevec;
	faudes::Generator minresult;
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

	faudes::StateSet::Iterator it;
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
	faudes::LanguageReverse(resultgen);
	BOOST_ASSERT_MSG(resultgen.InitStates()==markedstates," Some serious error need to rethink of strategy");
	resultgen.StateNamesEnabled(false);
}//end of function

Program* TSOTransSystem::GetModifiedProgramObject()
{
	return mTSOProgram;
}

z3::expr TSOTransSystem::GetLastWrite(ThdId tid, std::string var, const TSOState st, bool& found)
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
			retval=std::get<1>(pr);
		}
	}
	return retval;
}

void TSOTransSystem::DebugTSOSymbolInfo()
{
	std::cout<<"Newly added symbols are "<<std::endl;
	for(std::pair<std::string,std::string> newsymp: mNewOldSymbMap)
	{
		std::tuple<z3::expr,z3::expr> exprpair=mTSOProgram->mRWLHRHMap.find(newsymp.first)->second;
		std::cout<<newsymp.first<<":"<< std::get<0>(exprpair)<<"="<<std::get<1>(exprpair)<<std::endl;
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

TSOTransSystem::~TSOTransSystem()
{
	if(mTSOProgram!=NULL)
	{
		delete mTSOProgram;
		mTSOProgram=NULL;
	}

}

