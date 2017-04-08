/*
 * RMMInterface.cpp


 *
 *  Created on: 17-Jan-2016
 *      Author: chinmay
 */

#include "FenceFinder/FenceFinder.h"
#include "AFA/AFAut.h"
#include "Parser/Program.h"
#include "SCTransSystem/SCTransSystem.h"
#include "TSOTransSystem/TSOTransSystem.h"
#include "Parser/QiParser.h"
#include <boost/chrono.hpp>
#include <boost/assert.hpp>
#include <iostream>
#include <tuple>
#include <string>
#include <algorithm>
#include <libfaudes.h>

 //#define SANITYCHKASSN 0
//#define DBGPRNT
#include <c++/z3++.h>

void Remove(faudes::Generator& generator, std::vector<AFAut*> afaset, TSOTransSystem* T);
std::vector<AFAut* > ProveRMM(faudes::Generator& generator, TSOTransSystem* T, bool &result);
std::map<std::string,std::string> FinalOrders;
void Verify(std::string filename, std::string option, int bound)
{
	std::cout<<"Verifying "<<filename<<" for mm="<<option<<" and initial bound ="<<bound<<std::endl;
	auto start =  boost::chrono::system_clock::now();
	z3::context ctx;
	z3::solver s(ctx);
	client::Parser* expParser = client::GetParser();//it is callers responsibility to delete the parser object.
	Program* P = new Program(filename.c_str(),ctx,*expParser);
	P->ProcessInput();
#ifdef DBG
	std::cout<<" Program has "<<P->mAllSyms.size()<<" entries "<<std::endl;
#endif
	/** By this time our program input has been parsed successuflly*/
	Program* origProgram = P;
	bool check=false;
	std::vector<AFAut*> lastafaset;
	faudes::Generator lastgenerator;

	while(true)
	{
		TSOTransSystem* T = new TSOTransSystem(*P,s);
		faudes::Generator generator;
		T->BuildTSOTS(generator,bound);//generator represents the automaton.. in reverse..of bound depth
		Program* workingProgram = T->GetModifiedProgramObject();
#ifdef DBG
		std::cout<<" Gen Program has "<<workingProgram->mAllSyms.size()<<" entries "<<std::endl;
#endif
		T->DebugTSOSymbolInfo();//For Debug purposes
		//Check if we can break from this loop.. for completion part..
/*
		faudes::Generator res;
		faudes::LanguageDifference(generator,lastgenerator,res);
		generator.Assign(res);
*/
		faudes::Generator res;
		generator.StateNamesEnabled(false);
		faudes::Deterministic(generator,res);
		generator.Clear();
		generator.Assign(res);

		faudes::LanguageDifference(generator,lastgenerator,res);

		//generator.DotWrite("gen.dot");
		generator.Clear();
		generator.Assign(res);
		Remove(generator,lastafaset,T);
		if(faudes::IsEmptyLanguage(generator))
		{
			//then we are done and return
			std::cout<<"Reached FixedPoint for bound = "<<bound<<" and hence Done"<<std::endl;
			if(FinalOrders.size()!=0)
			{
				std::cout<<"Following orderings are needed for correction"<<std::endl;
				for(const auto& el: FinalOrders)
				{
					std::cout<<el.first<<" before "<<el.second<<std::endl;
				}
			}
			break;
		}else
		{
			bool result=true;
			std::vector<AFAut*> thisafaset= ProveRMM(generator,T,result);
			lastafaset.insert(lastafaset.end(),thisafaset.begin(),thisafaset.end());
#ifdef DBG
			std::cout<<"result is "<<result<<std::endl;
#endif
			if(!result){//means proof faile.. and it also modified the program..
				//insert fences to order and skip checking the next iteration of the same boudn..
				//note that.. dont increase the boun dhere..
				//update program,set check =false
//				std::cout<<"Proof failed and repeating again"<<std::endl;
				check=false;
				//break;//for debugging..
			}else
			{
				//return the set of afa's constructed in the proof..store them in last
				//set check=true
				check=true;
				lastgenerator.Assign(generator);
				//increase bound by 1 and continue..
				std::cout<<"Program is safe for bound = "<<bound<<" incrementing bound by 1"<<std::endl;
				bound=bound+1;
			}

		}
	}
	auto end = boost::chrono::system_clock::now();
				auto   elapsed = boost::chrono::duration_cast<boost::chrono::duration<double> >(end- start).count();
					std::cout << "Time spent = "<<elapsed << "seconds "<<'\n';

AFAState::mUnsatMemoization.clear();//so that destructor is not called on them. otherwise GC.exit was
//beging called which cleared this static object and called destructor on z3::expr formulae which was not
//supposed to happen..Intersetingly quetion is how wl

}

void Remove(faudes::Generator& generator, std::vector<AFAut*> afaset, TSOTransSystem* T)
{
	/*//Change 2nd March- rather than subtracting from afaset subtract from afa stored in AFA class..
	if(AFAut::mAFAInitStates.size()!=0)
	{
		AFAStatePtr tm = *(AFAut::mAFAInitStates.begin());
	AFAStatePtr newinit= new AFAState(tm->mType,tm->mAMap,*(AFAut::mProgram));//here mAMap does not matter.. just putting it
	newinit->mHMap=new z3::expr(*(tm->mHMap));

	std::set<std::pair<std::string,std::set<AFAStatePtr>>,transitionscomparatorraw> transsetthisone;
				for(auto const &st : AFAut::mAFAInitStates)
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

				AFAut* afa = new AFAut();//WHere is this getting deleted??
				afa->mInit=newinit;
			//now call intersection from generator and AFAut of newinit..
				{
					faudes::Generator intersectionres;

						std::map<faudes::Idx,faudes::Idx> oldNewInitStateMap;
						afa->Intersection(generator,intersectionres,oldNewInitStateMap);
				  	    //Copy back the assertion with resepct to tnewly created states..
						std::map<faudes::Idx, z3::expr> newassnmap;


						for(std::pair<faudes::Idx,faudes::Idx> elempair: oldNewInitStateMap)
						{
							newassnmap.insert(std::make_pair(std::get<1>(elempair),T->mShuffautAssnMap.find(std::get<0>(elempair))->second));
						}
						T->mShuffautAssnMap.clear();
						T->mShuffautAssnMap=newassnmap;


						//////////////////////////////////
						generator.Clear();
				//		T->DeterminizeAndReassignAssertionsInit(intersectionres,generator,T->mShuffautAssnMap);
						faudes::Deterministic(intersectionres,generator);
						//generator.Assign(intersectionres);
						intersectionres.Clear();
						faudes::aStateMin(generator);
						//T->MinimizeAndReassignAssertionsInit(generator,intersectionres,T->mShuffautAssnMap);
						faudes::StateSet s1=intersectionres.InitStates();
						generator.Clear();
						generator.Assign(intersectionres);//Make sure that it gets the same marking..
						faudes::StateSet s2=generator.InitStates();
						BOOST_ASSERT_MSG(s1==s2,"Some serious error, assignment is not properly done");
						//faudes::aStateMin(generator);
						#ifdef DBGPRNT
						     std::cout<<"Intersection: States = "<<generator.States().Size()<<" Transitions = "<<generator.TransRel().Size()<<std::endl;
						#endif
						//intersectionres.Clear();
				        //generator.Assign(intersectionres);
					}
				delete newinit;
				afa->mInit=NULL;
				delete afa;//This ordering is important otherwise whole AFA will be removed..
				//no need to return because genrator is passed as reference.. it must be updated..

	}*/

	//for each afa in afaset intersect it with generator and get new generator..
	//when done check if the the language of the resultant generator is empty or not.
	//if empty return true
	//else return false..
	//note that generator is also getting subtracted.. to ensure that the reference is getting updated
	//in the caller
	faudes::Generator intersectionres;
	for(const auto& afa: afaset)
	{
		/*afa->PrintToDot("afaremoving.dot");
		generator.DotWrite("gendot.dot");*/
		std::map<faudes::Idx,faudes::Idx> oldNewInitStateMap;
		afa->Intersection(generator,intersectionres,oldNewInitStateMap);
  	    //Copy back the assertion with resepct to tnewly created states..
//		std::map<faudes::Idx, z3::expr> newassnmap;

		/*for(std::pair<faudes::Idx,faudes::Idx> elempair: oldNewInitStateMap)
		{
			newassnmap.insert(std::make_pair(std::get<1>(elempair),T->mShuffautAssnMap.find(std::get<0>(elempair))->second));
		}
		T->mShuffautAssnMap.clear();
		T->mShuffautAssnMap=newassnmap;
*/
		/////////////////////////////////

		generator.Clear();
//		T->DeterminizeAndReassignAssertionsInit(intersectionres,generator,T->mShuffautAssnMap);
		faudes::Deterministic(intersectionres,generator);
		//generator.Assign(intersectionres);
		intersectionres.Clear();
		faudes::aStateMin(generator);
		//std::cout<<"interesected states are "<<generator.States().Size()<<std::endl;
		//T->MinimizeAndReassignAssertionsInit(generator,intersectionres,T->mShuffautAssnMap);
		//faudes::aStateMin(generator);
		#ifdef DBGPRNT
		     std::cout<<"Intersection: States = "<<generator.States().Size()<<" Transitions = "<<generator.TransRel().Size()<<std::endl;
		#endif
		//intersectionres.Clear();
        //generator.Assign(intersectionres);
	}

	//no need to return because genrator is passed as reference.. it must be updated..
}

std::vector<AFAut* > ProveRMM(faudes::Generator& generator, TSOTransSystem* T, bool &result){

	char* word;
	size_t length;
	std::vector<AFAut*> afaset;
	int cases=0;
	AFAut* proofafa=NULL;
	while(!faudes::IsEmptyLanguage(generator))
	{
		/*faudes::TransSet transrel=generator.TransRel();                         // transrel default order X1-Ev-X2
		// ... some operation to set up transrel
		faudes::TTransSet<faudes::TransSort::X2EvX1> transByX2;    // alternative order X2-Ev-X1
		transrel.ReSort(transByX2);                // copy and re-order transrel
		faudes::TransSet::Iterator tit    =transByX2.BeginByX2(x2);   // begin iterator, X2 specified
		faudes::TransSet::Iterator tit_end=transByX2.EndByX2(x2);     // end iterator, X2 specified
		for(; tit!=tit_end; ++tit) {               // loop over all transitions with specified x2
		// ... code to examine tramsitions with specified x2
		}
*/
		faudes::Idx startst;
		std::string revword(generator.GetShortestWord());
		//BOOST_ASSERT_MSG(T->mShuffautAssnMap.find(startst)!=T->mShuffautAssnMap.end(),"Some serious error look carefully");

		std::string original(revword);//for some debugging purposes
	#ifdef DBGPRNT
		std::cout<<"Original is "<<original<<std::endl;
	#endif
		//std::reverse(revword.begin(), revword.end());//reverse the word to get it back.
	#ifdef DBGPRNT
			std::cout<<"Getting accepted state for "<<revword<<std::endl;
	#endif
		//if SC
		//z3::expr wordphi= T->GetEndStateAssertionFromWord(revword);
		//if TSO
	z3::expr wordphi = T->GetEndStateAssertionFromWord(revword);//T->mShuffautAssnMap.find(startst)->second;
	std::string exword = revword;
	std::cout<<"Checking word "<<exword<<" with postcondition phi = "<<wordphi<<std::endl;

	z3::expr negphi = !wordphi;
	//struct fa* prooffa = AFAut::MakeAFAutProof(exword,negphi,P,cases);
	faudes::Generator proofgens;


	//delete proofafa;
	proofafa = AFAut::MakeAFAutProof(exword,negphi,T->GetModifiedProgramObject(),cases,result,proofgens);
		//what we got is already complemented version..
		if(result==false)//return null if hmap of initial state is unsat.
				{
					std::cout<<"An errorneous trace "<<std::endl;
					std::cout<<exword<<std::endl;
					//Construct value flow relation if TSO
					std::map<AFAStatePtr,RFRelPairs> memoized;
					std::tuple<std::map<std::string,std::string>,std::map<std::string,std::string>,std::map<std::string,std::string>> rfmaps = (proofafa->GetRFRelationFromProof(proofafa->mInit,*T,revword,memoized));
					std::map<std::string,std::string> rfemap=std::get<1>(rfmaps);
					std::map<std::string,std::string> rfimap=std::get<2>(rfmaps);
#ifdef DBG
					for(const auto& el: rfemap)
					{
						std::cout<<el.first<<" reads from "<<el.second<<std::endl;
					}
					for(const auto& el: rfimap)
					{
						std::cout<<el.first<<" reads from "<<el.second<<std::endl;
					}
#endif
					//get PO realtion from this trace
					PO poinfo = T->GetPO(exword);
#ifdef DBG
					for(const auto& el: poinfo)
						std::cout<<el.first<<" --> "<<el.second<<std::endl;
#endif

					//now call getorder function with rf, rfe, set of all nodes (same as elements in po+rfmap)
					//There find initial writes and add them to wwrelation..
					FenceFinder ffind(T);
					//IMP: pass here *workingprogram because we might need info on modified write variables as well
					std::cout<<"Finding fence orderings "<<std::endl;
					std::map<int,std::set<std::pair<std::string,std::string>>> orders=ffind.OrderFinder(poinfo,rfemap,rfimap, FinalOrders);
//					std::cout<<"ORdering found "<<std::endl;
					T->mProgram.InsertOrders(orders,FinalOrders);
					for(const auto& el: orders){
											for(const auto& el2: el.second){
												FinalOrders[el2.first]=el2.second;
											}
										}
					std::cout<<"Insertion of fences done"<<std::endl;
					//Here we are modifying stuff here only..later we can move it up..
					//afaset.clear(); dont clear it...we can still use partial information later..
					//afaset.push_back(proofafa);
					result=false;
					//std::cout<<"returning "<<std::endl;
					return afaset;
				}

		//Moved it here from before proofafa invocation because if proof fails then this must be returned inside
		//the previous condition an dhence we can not delete it in advance.
		if(afaset.size()==1)
			delete (*(afaset.begin()));
		afaset.clear();


		/*
		 * std::set<AFAStatePtr,mymapstatecomparatoreqclass> eqclass;
		 * std::string s1("lock==1");
		std::string s2("1==lock");
					z3::expr tst1 = client::ParseExp(T->mProgram.mParser,s1,T->mProgram.mVarExprMap,proofafa->mInit->mAMap.ctx());
					z3::expr tst2 = client::ParseExp(T->mProgram.mParser,s2,T->mProgram.mVarExprMap,proofafa->mInit->mAMap.ctx());
					AFAStatePtr p1 = new AFAState(ORLit,tst1,T->mProgram);
					AFAStatePtr p2 = new AFAState(ORLit,tst2,T->mProgram);
					eqclass.insert(p1);
					if(eqclass.find(p2)==eqclass.end()){
						std::cout<<"inserting"<<std::endl;
						eqclass.insert(p2);
					}
					std::cout<<"Size of set is "<<eqclass.size()<<std::endl;
					if(proofafa->mInit->IsLogicalEq(tst1,tst2)==true){
						std::cout<<"Both are equivalent"<<std::endl;
					}
std::exit(-1);
*/
		#ifdef SANITYCHKASSN
		std::cout<<"AFA construction over-complement.. dumping to complemented.dot file.Press any int to continue"<<std::endl;
		bool res= checkAccepting(original,prooffa);
		BOOST_ASSERT_MSG(res==false,"Some serious error as this word must not be accepted by this complemented FA");
#endif
	 faudes::Generator intersectionres;
#ifdef DBGPRNT
	 std::cout<<"Original: States="<<generator.States().Size()<<" Transitions = "<<generator.TransRel().Size()<<std::endl;
#endif
	 std::map<faudes::Idx,faudes::Idx> oldNewInitStateMap;

	 proofafa->Intersection(generator,intersectionres,oldNewInitStateMap);
	 afaset.push_back(proofafa);//INV: everytime at most one entry in afaset.
	 		/*delete(proofafa->mInit);
	 		proofafa->mInit=NULL;
	 		delete proofafa;*/
	 //Copy back the assertion with resepct to tnewly created states..
	 /*std::map<faudes::Idx, z3::expr> newassnmap;
	 for(std::pair<faudes::Idx,faudes::Idx> elempair: oldNewInitStateMap)
	 {
		 newassnmap.insert(std::make_pair(std::get<1>(elempair),T->mShuffautAssnMap.find(std::get<0>(elempair))->second));
	 }
	 T->mShuffautAssnMap.clear();
	 T->mShuffautAssnMap=newassnmap;*/
	 //////////////////////////////////

	 generator.Clear();
	 //T->DeterminizeAndReassignAssertionsInit(intersectionres,generator,T->mShuffautAssnMap);
     faudes::Deterministic(intersectionres,generator);
	 //generator.Assign(intersectionres);
     //intersectionres.Clear();
     faudes::aStateMin(generator);
     //generator.Assign(intersectionres);
     //faudes::aStateMin(generator);
     /*T->MinimizeAndReassignAssertionsInit(generator,intersectionres,T->mShuffautAssnMap);
     faudes::StateSet s1=intersectionres.InitStates();
     generator.Clear();
     generator.Assign(intersectionres);//Make sure that it gets the same marking..
     faudes::StateSet s2=generator.InitStates();
     BOOST_ASSERT_MSG(s1==s2,"Some serious error, assignment is not properly done");*/
	 //faudes::aStateMin(generator);
	 //delete proofafa;//dont delete it now as it is being returned.. for sc we can delete it..
#ifdef DBGPRNT
     std::cout<<"Intersection: States = "<<generator.States().Size()<<" Transitions = "<<generator.TransRel().Size()<<std::endl;
#endif

     //generator.Assign(intersectionres);

   	 cases++;
   	//std::exit(-1);
	}
//	std::cout<<"Total cases = "<<cases<<std::endl;
	result=true;
	return afaset;
}


