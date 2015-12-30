/*
 * TSOTransSystem.h
 *
 *  Created on: 21-Dec-2015
 *      Author: jaganmohini
 */

#ifndef TSOTRANSSYSTEM_H_
#define TSOTRANSSYSTEM_H_
#include <libfaudes.h>//WHY this ordering was important.. If I put it after c++/z3++ then lots of error..
//in fact putting it after fa.h also generates lot of strage errors.
extern "C"
{
#include <fa.h>
}
#include <map>
#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <c++/z3++.h>
#include "TSOState.h"
#include "../Parser/Program.h"



typedef std::pair<std::string, std::map<std::string,int>> OldSymInfo;
class TSOTransSystem;
struct oldsyminfocomparator{
	bool operator() (const OldSymInfo& one, const OldSymInfo&  two) const
		{
			if(one.first==two.first)
				return one.second<two.second;
			else
				return one.first<two.first;
		}
  };

struct pairexpcomparator{
	bool operator() (const std::pair<z3::expr,z3::expr>& one, const std::pair<z3::expr,z3::expr>& two) const
	  	{

			z3::expr firstone=std::get<0>(one);
			z3::expr secondone=std::get<1>(one);
			z3::expr firsttwo=std::get<0>(two);
			z3::expr secondtwo=std::get<1>(two);
	  			if (firstone.hash()==firsttwo.hash())
					return secondone.hash()<secondtwo.hash();
				else
					return firstone.hash()<firsttwo.hash();
	  	}
};

class TSOTransSystem
{
	Program& mProgram;
	z3::solver& mSolver;
	Program* mTSOProgram;
	std::map<std::string,int> mChangedWriteReadSymbmap;
	std::map<std::string,std::string> mNewOldSymbMap;
	std::map<std::pair<z3::expr,z3::expr>,std::string,pairexpcomparator> mExprToSymbMap;

	std::set<SymStatePair> StepConcrete(ThdId tid, const TSOState& st);
	std::set<SymStatePair>  StepFlush(ThdId tid, const TSOState& st);
	std::pair<std::set<std::string>,std::set<std::string>> GetNewWriteReadSyms(std::string oldsym, ThdId tid, const TSOState& st, TSOState& newst);

public:
	std::map<faudes::Idx, z3::expr> mShuffautAssnMap;

	z3::expr GetLastWrite(ThdId tid, std::string var, const TSOState st, bool&);
	void DebugTSOSymbolInfo();
	void DeterminizeAndReassignAssertionsInit(const faudes::Generator& rGen, faudes::Generator& rRes, std::map<faudes::Idx, z3::expr>& assnMap);
	void MinimizeAndReassignAssertionsInit(faudes::Generator& rGen, faudes::Generator& rRes, std::map<faudes::Idx, z3::expr>& assnMap);
	TSOTransSystem(Program&,z3::solver& s);

	void BuildTSOTS(faudes::Generator&, int buffbound);
	Program* GetModifiedProgramObject();
	virtual ~TSOTransSystem();//here delete all expr stored in mShuffautAssnMap, fa as well..
};


#endif
