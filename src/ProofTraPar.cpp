
/*
 * Test.cpp

 *
 *  Created on: 09-Jun-2015
 *      Author: jaganmohini
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
#define DBGPRNT
#include <c++/z3++.h>
void Verify(std::string filename, std::string option, int bound);

int main(int argc, char* argv[]){



	if(argc==1){
		std::cout<<"Enter the program file as first argument"<<std::endl;
		exit(-1);
	}
	else if(argc==4)
	{
		//std::cout<<"Enter the program file as first argument"<<std::endl;
		std::string filename(argv[1]);
		std::string option(argv[2]);
		int bound=std::atoi(argv[3]);
		Verify(filename,option,bound);
		return 0;
	}else if(argc!=2){
		std::cout<<"usage: ProofTrapar filename [tso/pso bound]"<<std::endl;
		exit(-1);
	}
	//FOR SC
	std::string filename(argv[1]);

	auto start =  boost::chrono::system_clock::now();
	faudes::Generator generator,lGenerator;
	z3::context ctx;
	z3::solver s(ctx);
	client::Parser* expParser = client::GetParser();//it is callers responsibility to delete the parser object.
	Program* P = new Program(filename.c_str(),ctx,*expParser);
	std::cout<<"About to process input "<<std::endl;
	P->ProcessInput();
    SCTransSystem* T = new SCTransSystem(*P,s);
    T->BuildSCTS(lGenerator);
//   lGenerator.StateNamesEnabled(false);

 // Needed for SC case??
   faudes::Deterministic(lGenerator,generator);
#ifdef DBGPRNT
   //generator.DotWrite("DetermOriginal.dot");
#endif
   //std::cout<<"Determinisitic done"<<std::endl;

   //faudes::StateMin(lGenerator,generator);

#ifdef DBGPRNT
   std::cout<<"Determinization done "<<std::endl;
#endif
   generator.StateNamesEnabled(false);
   faudes::aStateMin(generator);
#ifdef DBGPRNT
   std::cout<<"Minimization done "<<std::endl;
#endif

	char* word;
	size_t length;
	//fa_example(revmerged,&word,&length);
	//std::string revword(word,length);
	int i;
	int cases=0;
  while(!faudes::IsEmptyLanguage(generator))
  {

	  faudes::Idx startst;
    std::string revword(generator.GetShortestWord());
	std::string original(revword);//for some debugging purposes
#ifdef DBGPRNT
    std::cout<<"Original is "<<original<<std::endl;
#endif
		//std::reverse(revword.begin(), revword.end());//reverse the word to get it back.
#ifdef DBGPRNT
		std::cout<<"Getting accepted state for "<<revword<<std::endl;
#endif
		//if SC
		z3::expr wordphi= T->GetEndStateAssertionFromWord(revword);
		//if TSO
		//z3::expr wordphi =  P->Get
		std::string exword = revword;
		std::cout<<"Checking word "<<exword<<" with postcondition phi = "<<wordphi<<std::endl;

		z3::expr negphi = !wordphi;

		bool result=false;
		faudes::Generator proofgens;

		AFAut* proofafa = AFAut::MakeAFAutProof(exword,negphi,P,cases,result,proofgens);
		//what we got is already complemented version..
		if(result==false)//return null if hmap of initial state is unsat.
				{
					std::cout<<"An errorneous trace "<<std::endl;
					std::cout<<exword<<std::endl;
					auto end = boost::chrono::system_clock::now();
				auto   elapsed = boost::chrono::duration_cast<boost::chrono::duration<double> >(end- start).count();
					std::cout << "Time spent = "<<elapsed << "seconds "<<'\n';
					std::exit(-1);
				}

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
	 generator.Clear();
	 //T->DeterminizeAndReassignAssertionsInit(intersectionres,generator,T->mShuffautAssnMap);
     faudes::Deterministic(intersectionres,generator);
	 //generator.Assign(intersectionres);
     intersectionres.Clear();
     faudes::aStateMin(generator);
	 delete proofafa;
#ifdef DBGPRNT
     std::cout<<"Intersection: States = "<<generator.States().Size()<<" Transitions = "<<generator.TransRel().Size()<<std::endl;
#endif

     //generator.Assign(intersectionres);

   	 cases++;
   	//std::exit(-1);
}
	std::cout<<"Total cases = "<<cases<<std::endl;
	delete P;
	delete T;
	delete expParser;
	auto end = boost::chrono::system_clock::now();
	auto   elapsed = boost::chrono::duration_cast<boost::chrono::duration<double> >(end- start).count();
	std::cout << "Time spent = "<<elapsed << "seconds "<<'\n';
	//to avoid double free problem as in verify function.. clear mUNsatMemoization map..
	AFAState::mUnsatMemoization.clear();
	return 0;

}

