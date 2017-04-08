/*
 * PassFourAFA.cpp

 *
 *  Created on: 23-Sep-2015
 *      Author: jaganmohini
 */

#include "AFAut.h"
#include <unordered_map>

AFAut* AFAut::PassFourNew(AFAStatePtr init, std::set<AFAStatePtr>& tobedeleted, int cases,faudes::Generator& lGenerator)
{


	int i;
	//keep all values present in statemap to be deleted after next loop.
	//Pass 1:
	std::set<std::tuple<AFAStatePtr,std::string,AFAStatePtr>, tuplecomparator> toANDLink;
	std::set<AFAStatePtr> ANDORStates;
	std::set<AFAStatePtr> ORLitStates;
  std::map<AFAStatePtr,	std::set<std::tuple<std::string,AFAStatePtr>>> assumeinfomap;
#ifdef DBGPRNT
	std::cout<<"About to construct phase1 pass4"<<std::endl;
#endif

	init->PassFourPhaseOne(ANDORStates,ORLitStates,toANDLink,assumeinfomap);
	//when done in seenmap we have Eq classes for every distinct amap.
	//delete all states present in the set allstates.., No we cant as we are currently in a state only..
	//so its better to return it..
	/*BOOST_FOREACH(auto t, allStates){
		delete(t.first);
	}*/
	//NO change in graph by this pass.. only collecting information to be used in phase 2
	AFAut* tm=new AFAut();
	tm->mInit=init;
#ifdef DBGPRNT
	//tm->PrintToDot("Pass4Phase1.dot");
	std::cout<<"Pass 1 over"<<std::endl;
	//std::cin>>i;
#endif
/*
	tm->PrintToDot("Pass4Phase1.dot");
		std::cout<<"Pass 1 over"<<std::endl;
*/
	//Pass0: propoage 0's on OR/AND states so that after this every 0's transition from OR/AND goest to ORLit state only.
	//we can use the fact that by this time we have a nice tree like structure of FA
  std::map<AFAStatePtr,std::set<std::set<AFAStatePtr>>> donemap;
  //std::cout<<"About to construct phase0 pass4"<<std::endl;
	std::set<std::set<AFAStatePtr>> retset = init->PassFourPhaseZero(donemap);
	//if init was OR/AND then all this set will be on 0,
	//if init was ORLit then it will be single state (init) in the returned set


		tm->mInit=init;
#ifdef DBGPRNT
		//tm->PrintToDot("Pass4Phase0.dot");
		std::cout<<"Pass 0 over"<<std::endl;
		//std::cin>>i;
#endif


		tobedeleted.insert(ANDORStates.begin(),ANDORStates.end());
		//This was earlier: tobedeleted.insert(ORLitStates.begin(),ORLitStates.end()); But now(read next line comments)

//Mar 2nd: Intersting thing has happened.. I would now like to have earlier AFA with me (thos obtained
		//after removing and/or nodes and only ORLitStates//
		//This will be used to get added in subsequent iterations so as to give more coverage..
		//Let us see if it affect the performance. Therefore Now I am commenting the fact that
		//we should delete ORLitStates..

	//Pass 2: //now we will add transitions  toANDLink,

	//for cases when orlit has a sym labeled edge to OR/AND replace that OR/AND by its transitions which will certainly be OR/AND
	//create epsilon closure for 0 labeled edges coming out from ANDOR eq states..
	//sufficient to look at ORLIt states and check if they have an edge to ANDORStates.. if yes on some symbol say sym
	//then add that ANDOR state's transitions on sym to this state.after remvoing zero to that ANDORState..

	BOOST_FOREACH(auto t, toANDLink){
		AFAStatePtr src = std::get<0>(t);
		std::string sym = std::get<1>(t);
		AFAStatePtr dest = std::get<2>(t);
	 // BOOST_ASSERT_MSG(dest->mType!=ORLit,"Some serious error");
		std::set<std::pair<std::string,std::set<AFAStatePtr>>,transitionscomparatorraw> transsetthisone;
		//asssert AFAut* PassFourNew(AFAStatePtr init, std::set<AFAStatePtr>& allStates , int, faudes::Generator&);
		for(std::multimap<std::string,SetAFAStatesPtr>::iterator it= src->mTransitions.equal_range(sym).first;it!=src->mTransitions.equal_range(sym).second;it++)
		{
			if(it->second.find(dest)!=it->second.end()){
				BOOST_ASSERT_MSG(it->second.size()==1,"Seriour error");
			}else
			{
				std::set<AFAStatePtr> custset(it->second.begin(),it->second.end());
				transsetthisone.insert(std::make_pair(it->first,custset));
			}
		}
		src->mTransitions.erase(sym);
		BOOST_FOREACH(auto t, src->mTransitions){
			std::set<AFAStatePtr> own(t.second.begin(),t.second.end());
			transsetthisone.insert(std::make_pair(t.first,own));
		}

    if(dest->mType!=ORLit)
    {
  		BOOST_FOREACH(auto t, dest->mTransitions){
	  		//BOOST_ASSERT_MSG(t.first=="0","SOmer serious error");
		  	std::set<AFAStatePtr> custset(t.second.begin(),t.second.end());
        //if t.second is singleton and is same as src then dont add...
        if(t.second.size()==1)
        {
          AFAStatePtr ss= *(t.second.begin());
          if(src->mAMap.hash()==ss->mAMap.hash() && src->mHMap->hash()==ss->mHMap->hash())
            continue;
        }
    		transsetthisone.insert(std::make_pair(sym,custset));
		  }
    }else
    {
      std::set<AFAStatePtr> dset;
      dset.insert(dest);
      transsetthisone.insert(std::make_pair(sym,dset));
    }
  	src->mTransitions.clear();
		BOOST_FOREACH(auto t, transsetthisone){
			SetAFAStatesPtr custset(t.second.begin(),t.second.end());
			src->mTransitions.insert(std::make_pair(t.first,custset));
		}
	//	src->mTransitions.insert(transsetthisone.begin(),transsetthisone.end());
	}
	//IMportant is this ordering.. first add all edges which come by virtue of connecting to future actions assume
	//and if any orlit is left without any edge on some assume symbol then add that assume symbol as well..
	//note that in all this addition of edge labelling assume symbol do it only when its hmap is false.
/*
	BOOST_FOREACH(auto orlitstate, ORLitStates){
				bool isorlitunsat = HelperIsUnsat(*(orlitstate->mHMap));
				if(isorlitunsat)
				{
					//add self loops on assume symbols, [ONLY on those on which it does not have already an edge]
					SetAFAStatesPtr own;
					own.insert(orlitstate);
					BOOST_FOREACH(auto sym, AFAut::mProgram->mAssumeLHRHMap){
						if(orlitstate->mTransitions.find(sym.first)==orlitstate->mTransitions.end())
							orlitstate->mTransitions.insert(std::make_pair(sym.first,own));
					}
				}
			}
*/


#ifdef DBGPRNT
		std::cout<<"Pass 2 over"<<std::endl;
		tm->PrintToDot("Pass4Phase2.dot");
		std::cin>>i;
#endif
		//	std::cin>>i;



/**********Now create equivalence classes for similar/same amap same hmap states..
 * By this time no AND OR node left.., in the newly create equivalence class add same amap hmap as for all..
 */

		/*
		 * Change on 2nd march- As I am now storing AFA constructed so far. So I would like to add
		 * those ORLitStates to ORLItStates and combine init of this to init seens so far
		 * Then we will create equivalence classes and work on that..
		 * NOte: mAFAOrLitStates should be equivalence classes constructed so far..not the original ones
		 */
		std::set<AFAStatePtr> newORLitSet;
					AFAStatePtr newinit;
		ORLitStates.insert(mAFAOrLitStates.begin(),mAFAOrLitStates.end());
		std::set<AFAStatePtr> oldORLitStates;
		AFAStatePtr falseEqClass=NULL;
		{//start block
			std::unordered_map<AFAStatePtr, AFAStatePtr, myhash,comparatoreqclass> eqclass;
			std::set<AFAStatePtr> seenset;
			std::set<AFAStatePtr> workset;
			std::set<AFAStatePtr> inputset;
			for(int i=0; i<2; i++)
			{
				//Interseting story how I found this bug.. so the scenario goes like this,
				// eq class had amap as a=1 and it created a node for that.
				//if we mix everything ie. .eq class with the result of this iteration then it is possible that
				//we first pick from this iteration and hence add 1=a next time.. so my eqclass will now have
				//both..??
				if(i==0)
					inputset.insert(mAFAOrLitStates.begin(),mAFAOrLitStates.end());
				else
				{
					inputset.clear();
					inputset.insert(ORLitStates.begin(),ORLitStates.end());
				}

					BOOST_FOREACH(auto elem, inputset){
						AFAStatePtr currentst = elem;
						AFAStatePtr newst;
						if(eqclass.count(currentst)==0){
//							std::cout<<"Inserting "<<currentst->mAMap<<"in eq class"<<std::endl;

							newst = new AFAState(ORLit,currentst->mAMap,*mProgram);
							//tobedeleted.insert(newst);
							newst->mHMap=new z3::expr(*(currentst->mHMap));
							eqclass.insert(std::make_pair(currentst,newst));
							/*std::cout<<"Entries are :"<<std::endl;
							for(auto const& el: eqclass)
								std::cout<<el.first->mAMap<<"-"<<el.second->mAMap<<",";*/
//							std::cout<<std::endl;
							if( newst->HelperIsUnsat((newst->mAMap)))
								falseEqClass = newst;
						}else{
//							std::cout<<currentst->mAMap<<" already present as "<<eqclass.find(currentst)->second->mAMap<<std::endl;
							newst=eqclass.find(currentst)->second;
						}
						newORLitSet.insert(newst);
						if(elem->mIsAccepted)
							newst->mIsAccepted=true;
						std::set<std::pair<std::string,std::set<AFAStatePtr>>,transitionscomparatorraw> transsetthisone;
						BOOST_FOREACH(auto trans, newst->mTransitions){
							std::set<AFAStatePtr> cutset(trans.second.begin(),trans.second.end());
							transsetthisone.insert(std::make_pair(trans.first,cutset));
						}
						BOOST_FOREACH(auto trans, currentst->mTransitions){
							std::string sym = trans.first;
							std::set<AFAStatePtr> transset;
							BOOST_FOREACH(auto w, trans.second){
							if(eqclass.count(w)==0){
								AFAStatePtr eqc = new AFAState(ORLit,w->mAMap,*mProgram);
//								std::cout<<"Inserting "<<w->mAMap<<"in eq class"<<std::endl;
								//tobedeleted.insert(eqc);
								eqc->mHMap=new z3::expr(*(w->mHMap));
								eqclass.insert(std::make_pair(w,eqc));
								/*std::cout<<"Entries are :"<<std::endl;
								for(auto const& el: eqclass)
									std::cout<<el.first->mAMap<<"-"<<el.second->mAMap<<",";
								std::cout<<std::endl;*/
								if( eqc->HelperIsUnsat((newst->mAMap)))
									falseEqClass = newst;
								transset.insert(eqc);
							}else{
//								std::cout<<w->mAMap<<" already present as "<<eqclass.find(w)->second->mAMap<<std::endl;
								transset.insert(eqclass.find(w)->second);
								}
							}
							//insert to mappedone's transition only if this transset not already present on symbol sym from
							//this state..
							transsetthisone.insert(std::make_pair(sym,transset));
						}
						newst->mTransitions.clear();
						BOOST_FOREACH(auto trans, transsetthisone){
							SetAFAStatesPtr tt(trans.second.begin(),trans.second.end());
							newst->mTransitions.insert(std::make_pair(trans.first,tt));
						}
					}
			}
			//Set init properly..
			if(init->mType!=ORLit)
				tobedeleted.erase(init); //We dont want this state to be deleted...

			mAFAInitStates.insert(init);
			std::set<AFAStatePtr> newAFAInitStates;
			for(auto const &st: mAFAInitStates )
			{
				//if t is ORLitState, then replace it with mapped state in eqclass and put it in
				//newAFAInitStates..
				//else put t in newAFAInitStates but replace all occurrences of 0 labeled with
								//corresponding eqclass states..
				if(st->mType==ORLit)
					newAFAInitStates.insert(eqclass.find(st)->second);
				else{//change the content of the transitions of OR/AND node..and keep newinit as the same init.
					//for each transition in this state construct
					//also remove this node from tobedeleted set..
						std::set<std::pair<std::string,std::set<AFAStatePtr>>,transitionscomparatorraw> transsetthisone;
							BOOST_FOREACH(auto t, st->mTransitions){
								std::set<AFAStatePtr> transset;
									BOOST_FOREACH(auto w, t.second){
												transset.insert(eqclass.find(w)->second);
											 }
									transsetthisone.insert(std::make_pair(t.first,transset));
									}
							st->mTransitions.clear();
							BOOST_FOREACH(auto w, transsetthisone){
								SetAFAStatesPtr tt(w.second.begin(),w.second.end());
								st->mTransitions.insert(std::make_pair(w.first,tt));
							}
							//insert st to newAFAInitStates..
							newAFAInitStates.insert(st);
					}

			}
			//clear mAFAInitStates and copy newAFAInitStates to it..
			oldORLitStates.insert(mAFAInitStates.begin(),mAFAInitStates.end());
			mAFAInitStates.clear();
			mAFAInitStates.insert(newAFAInitStates.begin(),newAFAInitStates.end());
			//add mAFAOrLitStates to tobedeleted set..
			tobedeleted.insert(ORLitStates.begin(),ORLitStates.end());
			//clear mAFAOrLitStates and copy newOrLitStatas to mAFAOrLitStates..
			mAFAOrLitStates.clear();
			mAFAOrLitStates.insert(newORLitSet.begin(),newORLitSet.end());

			//Changed: added on 3rd march.. saturate eqclass AFA by addin gedges
				//There might be a tradeoff between adding edges and its benefits.. so
				//I will proceed over time with multiple enhancements.. This is clearly version one.
			/**********
			 *
			 */

			SaturateEqClassAFA(mAFAOrLitStates,oldORLitStates,falseEqClass);



			//now create newinit state with info from the set mAFAInitStateas..
			newinit= new AFAState(AND,init->mAMap,*mProgram);//here mAMap does not matter.. just putting it
			newinit->mHMap=new z3::expr(*(init->mHMap));
			//Intersting that I should put its type as ANDORStates so that later trueinit can also be added
			//simply as an entry to 0.
			//for the sake of creating AFA..Question is: When is it getting deleted..may be
			//when we are done with the AFA..but just call delete on this AFAstate not on AFA..
			std::set<std::pair<std::string,std::set<AFAStatePtr>>,transitionscomparatorraw> transsetthisone;
			for(auto const &st : mAFAInitStates)
			{
				if(st->mType==ORLit)
				{
					std::set<AFAStatePtr> setst;
					setst.insert(st);
					transsetthisone.insert(std::make_pair("0",setst));
				}else
				{
					BOOST_FOREACH(auto t, st->mTransitions){
						std::set<AFAStatePtr> transset;
						transset.insert(t.second.begin(),t.second.end());
						transsetthisone.insert(std::make_pair("0",transset));
					}
				}
			}
			//now insert transitions of transsetthisone to newinit
			BOOST_FOREACH(auto w, transsetthisone){
				SetAFAStatesPtr tt(w.second.begin(),w.second.end());
				newinit->mTransitions.insert(std::make_pair(w.first,tt));
			}
		}
/*
for(auto const& st: mAFAOrLitStates)
{
	std::cout<<"Pointer is "<<st<<std::endl;
}

for(auto const& st: mAFAInitStates)
{
	std::cout<<"Initial Pointer is "<<st<<std::endl;
}
*/

/*
std::set<AFAStatePtr> newORLitSet;
			AFAStatePtr newinit;
{//start block


	std::map<AFAStatePtr, AFAStatePtr, mymapstatecomparator> eqclass;
	std::set<AFAStatePtr> seenset;
	std::set<AFAStatePtr> workset;
	BOOST_FOREACH(auto t, ORLitStates){
		AFAStatePtr currentst = t;
		AFAStatePtr newst;
		if(eqclass.find(currentst)==eqclass.end()){
			newst = new AFAState(ORLit,currentst->mAMap,*mProgram);
			//tobedeleted.insert(newst);
			newst->mHMap=new z3::expr(*(currentst->mHMap));
			eqclass.insert(std::make_pair(currentst,newst));
		}else{
			newst=eqclass.find(currentst)->second;
		}
		newORLitSet.insert(newst);
		if(t->mIsAccepted)
			newst->mIsAccepted=true;
		std::set<std::pair<std::string,std::set<AFAStatePtr>>,transitionscomparatorraw> transsetthisone;
		BOOST_FOREACH(auto trans, newst->mTransitions){
			std::set<AFAStatePtr> cutset(trans.second.begin(),trans.second.end());
			transsetthisone.insert(std::make_pair(trans.first,cutset));
		}
		BOOST_FOREACH(auto t, currentst->mTransitions){
			std::string sym = t.first;
			std::set<AFAStatePtr> transset;
			BOOST_FOREACH(auto w, t.second){
			if(eqclass.find(w)==eqclass.end()){
				AFAStatePtr eqc = new AFAState(ORLit,w->mAMap,*mProgram);
				//tobedeleted.insert(eqc);
				eqc->mHMap=new z3::expr(*(w->mHMap));
				eqclass.insert(std::make_pair(w,eqc));
				transset.insert(eqc);
			}else{
				transset.insert(eqclass.find(w)->second);
				}
			}
			//insert to mappedone's transition only if this transset not already present on symbol sym from
			//this state..
			transsetthisone.insert(std::make_pair(sym,transset));
		}
		newst->mTransitions.clear();
		BOOST_FOREACH(auto t, transsetthisone){
			SetAFAStatesPtr tt(t.second.begin(),t.second.end());
			newst->mTransitions.insert(std::make_pair(t.first,tt));
		}
	}
	//Set init properly..
	if(init->mType==ORLit)
		newinit=eqclass.find(init)->second;
	else{//change the content of the transitions of OR/AND node..and keep newinit as the same init.
		//for each transition in this state construct
		//also remove this node from tobedeleted set..
		tobedeleted.erase(init);
				std::set<std::pair<std::string,std::set<AFAStatePtr>>,transitionscomparatorraw> transsetthisone;
				BOOST_FOREACH(auto t, init->mTransitions){
					std::set<AFAStatePtr> transset;
					BOOST_FOREACH(auto w, t.second){
						transset.insert(eqclass.find(w)->second);
					 }
					transsetthisone.insert(std::make_pair(t.first,transset));
				}
				init->mTransitions.clear();
				BOOST_FOREACH(auto w, transsetthisone){
					SetAFAStatesPtr tt(w.second.begin(),w.second.end());
					init->mTransitions.insert(std::make_pair(w.first,tt));
				}
				newinit=init;
	}
}
*/



tm->mInit=newinit;
//tm->PrintToDot(std::string("EqClassOver.dot"));
#ifdef DBGPRNT
	std::cout<<"Phase eqclass over"<<std::endl;
	tm->PrintToDot(std::string("Pass4PhaseEqClass.dot"));
#endif

	//std::cin>>i;

/************NOw add self loops on those non-assume symbols whose freevar does not match with free var of current
 * state's mAMap..-- Should we also add assume symbols?? Lets keep that open for the time being..
 */


AFAStatePtr trueinit=NULL;
AFAStatePtr falseaccepted;
z3::expr truev=newinit->mAMap.ctx().bool_val(true);


std::set<AFAStatePtr> newset;
	std::map<AFAStatePtr,AFAStatePtr> newoldmap;
	BOOST_ASSERT_MSG(tm->mInit->mType!=ORLit,"Some error");
	AFAut* newafa = tm->CloneAFA(newset,newoldmap);
	delete newinit;//Because after cloning we dont need it anymore
	tm->mInit = newafa->mInit;
	newafa->mInit=NULL;
	delete newafa;
	newinit=tm->mInit;
//	tm->PrintToDot("aftercopy.dot");
	/*for(const auto& t: newset)
		std::cout<<"pointer is "<<t<<std::endl;*/
//Modifed CloneAFA so that AND state is not added here..same holds for newoldmap as well.. actually it does not matter
	//for newoldmap part.. but still..
	//Add self loops and
	//add self loops transitions (get added only on non-zero symbols):
 {


           std::set<std::string> allsyms;
           allsyms.insert(AFAut::mProgram->mAllSyms.begin(),AFAut::mProgram->mAllSyms.end());
		BOOST_FOREACH(auto w, newset)
			{
			//For every state.. if it has a transition to some other state
						//then add the same transition on every equivalent symbol as well..
			/////////////////////////////////////////////////////////////////////////////////////
			std::set<std::pair<std::string,std::set<AFAStatePtr>>,transitionscomparatorraw> transsetthisone;
			BOOST_FOREACH(auto t, w->mTransitions)
				{
					std::string sm=t.first;
					std::set<AFAStatePtr> setsts(t.second.begin(),t.second.end());
					//for every similar symbol as of sm.. add an edge on that sym to setsts
					/*if(mProgram->mPartitionedSyms.find(sm)==mProgram->mPartitionedSyms.end())
						std::cout<<"No partition found for symbol "<<sm<<std::endl;
					BOOST_ASSERT_MSG(mProgram->mPartitionedSyms.find(sm)!=mProgram->mPartitionedSyms.end()," Some error.. every sym  must have a parition, worst case single one");*/
					//It is possible that no parition is found for some symbol, like the one added by TSO transition system
					//local variable instances etc..in those cases it is better to not insert those..
					if(mProgram->mPartitionedSyms.find(sm)!=mProgram->mPartitionedSyms.end())
					{
						for(const auto& el: mProgram->mPartitionedSyms[sm])
						{
							if(el!=sm){
								transsetthisone.insert(std::make_pair(el,setsts));
								}
						}
					}
				}
			//insert from transsetthisone to w->mTransitions
			BOOST_FOREACH(auto t, transsetthisone){
				SetAFAStatesPtr custset(t.second.begin(),t.second.end());
				w->mTransitions.insert(std::make_pair(t.first,custset));
			}
			/////////////////////////////////////////////////////////////////////////////

			SetAFAStatesPtr own;
			own.insert(w);
			if(w->mAMap.hash()==truev.hash()){//if valid
				trueinit=w;
			  BOOST_FOREACH(auto t, AFAut::mProgram->mAllSyms){
				 // if(w->mTransitions.find(t)==w->mTransitions.end()){//add only if that symbol is not present..
						w->mTransitions.insert(std::make_pair(t,own));
				//  }
			  }
			}else	if(w->HelperIsUnsat(w->mAMap)){
				falseaccepted=w;
				BOOST_FOREACH(auto t, AFAut::mProgram->mAllSyms)
				w->mTransitions.insert(std::make_pair(t,own));
			}else{
				std::set<z3::expr,z3comparator> freevars = mProgram->HelperGetFreeVars(w->mAMap);
				BOOST_FOREACH(auto t, AFAut::mProgram->mRWLHRHMap)
				{
                  // if(w->mTransitions.find(t.first)!=w->mTransitions.end())
                    //      continue;
					std::string sym = t.first;
					z3::expr lhs = std::get<0>(t.second);
					if(freevars.find(lhs)==freevars.end())//means not found as a free variable..
						{
						//add a self loop on this symbol to itself..
						w->mTransitions.insert(std::make_pair(sym,own));
						}
				}
				BOOST_FOREACH(auto t, AFAut::mProgram->mCASLHRHMap)
				{
                   //if(w->mTransitions.find(t.first)!=w->mTransitions.end())
                     // continue;
                   std::string sym = t.first;
                   z3::expr lhs = std::get<0>(t.second);
                   if(freevars.find(lhs)==freevars.end())//means not found as a free variable..
					{
						//add a self loop on this symbol to itself..
						w->mTransitions.insert(std::make_pair(sym,own));
					}
				}
		        BOOST_FOREACH(auto t, AFAut::mProgram->mAssumeLHRHMap)
				{
                  //if(w->mTransitions.find(t.first)!=w->mTransitions.end())
                   // continue;
		        	//add a self loop on this symbol to itself..
		        	w->mTransitions.insert(std::make_pair(t.first,own));
				}
			}
			//For every state.. if it has a transition to some other state
			//then add the same transition on every equivalent symbol as well..

		}
 }

		//BUG: I was not adding a transition from newinit to trueinit..
		//If newinint is AND/OR then just add it as 0 labeled transition
		//if newinint is ORLit then create a new ANDOR state and add newinit and this one as transition on 0..v
 	 if(trueinit!=NULL)
 	 {
 		 //As old states have changed by cloning AFA hence we need to get the old one to be inserted in
 		 //mAFAInitStates set. threfore using this information.
 		 mAFAInitStates.insert(newoldmap.find(trueinit)->second);//because otherwise it was not being added as init state..
 		SetAFAStatesPtr setst;
 		setst.insert(trueinit);
 		newinit->mTransitions.insert(std::make_pair("0",setst));
		/*if(newinit->mType!=ORLit){
			SetAFAStatesPtr trueinitset;
			trueinitset.insert(trueinit);
			newinit->mTransitions.insert(std::make_pair("0",trueinitset));
		}else{
			//create a new ANDOR node and add newinit and trueinit as its children..
			AFAStatePtr newnode = new AFAState(AND,newinit->mAMap,*mProgram);
			//tobedeleted.insert(newnode);
			newnode->mHMap=new z3::expr(*(newinit->mHMap));
			SetAFAStatesPtr newinset;
			newinset.insert(newinit);
			SetAFAStatesPtr trueinitset;
			trueinitset.insert(trueinit);
			newnode->mTransitions.insert(std::make_pair("0",newinset));
			newnode->mTransitions.insert(std::make_pair("0",trueinitset));
			newinit=newnode;
		}*/
 	 }
		//tm->mInit=newinit; Not needed
// 	 std::cout<<"Falseaccc is "<<falseaccepted<<std::endl;
//		tm->PrintToDot(std::string("Beforecomp.dot"));

#ifdef DBGPRNT
		std::cout<<"Phase self loop addition over"<<std::endl;
		tm->PrintToDot(std::string("Pass4PhaseSelfLoop.dot"));
#endif

		//Create generator


    AFAStatePtr falseerror=tm->Complement(falseaccepted);
#ifdef DBGPRNT
	std::cout<<"Complement done "<<std::endl;
	tm->PrintToDot(std::string("Pass4PhaseComplement.dot"));
#endif
//	tm->PrintToDot(std::string("aftercomp.dot"));
//	std::cin>>i;
std::cout<<"Size of proofafa is "<<newORLitSet.size()<<std::endl;
return tm;

}

struct tmpcomparator{
	bool operator() (const AFAStatePtr& one, const AFAStatePtr&  two) const
	{
		if(one->mAMap.hash()==two->mAMap.hash())
			return (one->mHMap->hash()<two->mHMap->hash());
		else
			return one->mAMap.hash()<two->mAMap.hash();
	}
};

void AFAut::SaturateEqClassAFA(std::set<AFAStatePtr> AFAOrLitStates,std::set<AFAStatePtr> oldORLitStates,AFAStatePtr falseEqClass)
{
	std::set<AFAStatePtr, tmpcomparator> check;
	check.insert(oldORLitStates.begin(),oldORLitStates.end());

	for(auto const& st: AFAOrLitStates)
	{
		z3::context& ctx = st->mAMap.ctx();

		if(check.find(st)==check.end()){
			//means a new eq class that was not present earlier..
			//for each symbol start working..one per eq class(partition)
			std::set<z3::expr,z3comparator> freevars=Program::HelperGetFreeVars(st->mAMap);
			for(auto const& sym: AFAut::mProgram->mPartitionedSymClass)
			{
				/*
				 * if assume then check if st->mAMap and its connunction is unsat or not.. if yes add edge from
				 * st to falsestate on sym
				 * if read or write then check if assertion obtained after substittuting free vars of st->mAMap
				 * with lhs of the modification is unsat or not.. if yes add edge from st to falsestate on sym.
				 * Right now I am only working on cases when sym is either assume or read/write type..
				 */
				if(mProgram->mRWLHRHMap.find(sym)!=mProgram->mRWLHRHMap.end()){
					//means it is a read/write symbol
					bool isPresent;
					//if does not conflict with the set -1 then add to mNonConflict set
					z3::expr left(std::get<0>((mProgram->mRWLHRHMap.find(sym)->second)));
				#ifdef	DBGPRNT
						    		std::cout<<"RW:lhs of exp is "<<left<<std::endl;
					#endif
				    if(freevars.find(left)!=freevars.end()){
						    //means this symbol conflict with phi and hence must be used for processing..
						    z3::expr right(std::get<1>((mProgram->mRWLHRHMap.find(sym)->second)));
						    z3::expr_vector src(ctx),dest(ctx);
						    src.push_back(left);
						    dest.push_back(right);
						    z3::expr l1(st->mAMap.substitute(src,dest));
						    l1=st->HelperSimplifyExpr(l1);
						    bool isfalse=false;
						    bool istrue=false;
						    if(st->HelperIsUnsat(l1) && falseEqClass!=NULL){
						    	//connect a transition from st to falseeqclass on symbol sym.
						    	SetAFAStatesPtr falsestatest;
						    	falsestatest.insert(falseEqClass);
						    	if(st->mTransitions.find(sym)==st->mTransitions.end())
						    		st->mTransitions.insert(std::make_pair(sym,falsestatest));
						    }/* Leave true for the time being.. will see later.
						    if(st->HelperIsValid(l1)){
						    	l1=ctx.bool_val(true);
						    	istrue=true;
						    }*/
				    }
				}else if(mProgram->mAssumeLHRHMap.find(sym)!=mProgram->mAssumeLHRHMap.end()){
				    	//means it is an assume symbol
				    	//get the second argument..
				    	bool isPresent;
				    	z3::expr assumepsi(mProgram->mAssumeLHRHMap.find(sym)->second);
				    	z3::expr combined(st->mAMap && assumepsi);
				    	combined=st->HelperSimplifyExpr(combined);
				    	if(st->HelperIsUnsat(combined) && falseEqClass!=NULL){
				    		//connect a transition from st to falseeqclass on symbol sym.
				    		SetAFAStatesPtr falsestatest;
				    		falsestatest.insert(falseEqClass);
				    		if(st->mTransitions.find(sym)==st->mTransitions.end())
				    			st->mTransitions.insert(std::make_pair(sym,falsestatest));
				    	}
				    	/*	    		if(HelperIsValid(combined)){ Leave validity for the time being..
				    		    			combined=ctx.bool_val(true);
				    		    			istrue=true;
				    		    		}*/
				 }
			}//end for loop
		}//end if condition
	}//end for loop
}

std::set<std::set<AFAStatePtr>> AFAut::GetConjunctedTransitions(std::set<AFAStatePtr> stateset, std::string sym){
			std::set<std::set<AFAStatePtr>> tobeaddedset;
			std::set<AFAStatePtr> emptyset;
			tobeaddedset.insert(emptyset);
			BOOST_FOREACH(auto state, stateset){
				if(state->mTransitions.find(sym)==state->mTransitions.end()){
					tobeaddedset.clear();//This is necessary to avoid executing the loop with partially filled tobeaddedset
					break;//means now we can not proceed to have an outgoing edge on this  symbol because at least one
					//does not have that..
				}
				std::set<std::set<AFAStatePtr>> tmptobeaddedset;
				BOOST_FOREACH(auto w, tobeaddedset){
					for(std::multimap<std::string, SetAFAStatesPtr>::iterator it= state->mTransitions.equal_range(sym).first; it!= state->mTransitions.equal_range(sym).second; it++)
					{
						std::set<AFAStatePtr> tmp(it->second.begin(),it->second.end());
						std::set<AFAStatePtr> tobeadded(w.begin(),w.end());
						tobeadded.insert(tmp.begin(),tmp.end());
						tmptobeaddedset.insert(tobeadded);
					}

				}
				tobeaddedset.clear();
				tobeaddedset.insert(tmptobeaddedset.begin(),tmptobeaddedset.end());

			}
			return tobeaddedset;
}


std::set<AFAStatePtr> AFAut::GetDisjunctedTransitions(std::set<AFAStatePtr> stateset, std::string sym){
			std::set<AFAStatePtr> tobeaddedset;
			BOOST_FOREACH(auto state, stateset){
				if(state->mTransitions.find(sym)!=state->mTransitions.end()){
					for(std::multimap<std::string,SetAFAStatesPtr>::iterator it= state->mTransitions.equal_range(sym).first;it!=state->mTransitions.equal_range(sym).second;it++)
					{
						SetAFAStatesPtr st = it->second;
						tobeaddedset.insert(st.begin(),st.end());
					}
				}
			}
			return tobeaddedset;
}


