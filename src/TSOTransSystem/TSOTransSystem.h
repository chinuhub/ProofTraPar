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
#include <map>
#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <c++/z3++.h>
#include "TSOState.h"
//#include "../FenceFinder/FenceFinder.h"
#include "../Parser/Program.h"



typedef std::pair<std::string, std::map<std::string,int>> OldSymInfo;
class TSOTransSystem;
typedef std::map<std::string,std::string> PO;
struct oldsyminfocomparator{
	bool operator() (const OldSymInfo& one, const OldSymInfo&  two) const
		{
			if(one.first==two.first)
				return one.second<two.second;
			else
				return one.first<two.first;
		}
  };



struct POGenInfo{
	std::map<int,std::map<std::string,std::vector<std::string>>> mBuffInfo;
	std::map<int,faudes::Idx> mCSinfo;
	std::string mRest;
	std::map<int,std::string> mLastSym;
	std::map<std::string,std::string> mPO;
	friend bool operator<(const POGenInfo& c1, const POGenInfo &c2);

};


class TSOTransSystem
{

	z3::solver& mSolver;

	std::map<std::string,int> mTSOChangedWriteReadSymbmap;
	std::map<std::tuple<z3::expr,z3::expr,int>,std::string,pairexpcomparator> mTSOExprToSymbMap;
	std::set<SymStatePair> StepConcrete(int tid, const TSOState& st,faudes::Generator* lG);
	std::set<SymStatePair>  StepFlush(int tid, const TSOState& st);
	std::pair<std::set<std::string>,std::set<std::string>> GetNewWriteReadSyms(std::string oldsym, int tid, const TSOState& st, TSOState& newst);
	bool IsExhaustDone(int tid, POGenInfo& info);
	std::map<std::string,faudes::Idx> GetLabNextPair(faudes::Idx curr, faudes::Generator* lGen);
	std::pair<std::string,std::string> ExtractFirstFromOld(std::string& orig, std::string& rest);
	std::string ExtractFirst(  std::string nd);
public:
	std::map<std::string,std::string> mTSONewOldSymbMap;
	z3::expr GetEndStateAssertionFromWord(std::string afaword);
	std::map<std::string, z3::expr> mSymAssnMap;
	std::pair<bool,z3::expr>  IsAcc(std::string sym);
	Program& mProgram;
	Program* mTSOProgram;
	std::map<std::string,std::string> mLocalRFMap;

	z3::expr GetLastWrite(int tid, std::string var, const TSOState st, bool&, std::string&);
	void DebugTSOSymbolInfo();
	void DeterminizeAndReassignAssertionsInit(const faudes::Generator& rGen, faudes::Generator& rRes, std::map<faudes::Idx, z3::expr>& assnMap);
	void MinimizeAndReassignAssertionsInit(faudes::Generator& rGen, faudes::Generator& rRes, std::map<faudes::Idx, z3::expr>& assnMap);
	TSOTransSystem(Program&,z3::solver& s);

	void BuildTSOTS(faudes::Generator&, int buffbound);
	Program* GetModifiedProgramObject();
	PO GetPO(std::string trace);
	std::set<POGenInfo> GetNextStep(POGenInfo& );
	bool IsExhaustable(POGenInfo&);
	virtual ~TSOTransSystem();//here delete all expr stored in mShuffautAssnMap, fa as well..
};

#endif
