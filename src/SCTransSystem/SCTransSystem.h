/*
 * SCTransSystem.h
 *
 *  Created on: 10-Jun-2015
 *      Author: jaganmohini
 */

#ifndef SCTRANSSYSTEM_SCTRANSSYSTEM_H_
#define SCTRANSSYSTEM_SCTRANSSYSTEM_H_
#include <libfaudes.h>//WHY this ordering was important.. If I put it after c++/z3++ then lots of error..
#include "../Parser/Program.h"
#include <set>
#include <libfaudes.h>//??WHY this ordering was important.. If I put it after c++/z3++ then lots of error..
#include <map>
#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <c++/z3++.h>

class SCTransSystem {
	Program& mProgram;
	z3::solver& mSolver;

	std::map<faudes::Idx, z3::expr> mShuffautAssnMap;
public:
	faudes::Generator* mMerged;
	SCTransSystem(Program&,z3::solver& s);
	void BuildSCTS(faudes::Generator&);
	void FA_Merge(std::vector<faudes::Generator*>& autset,std::map<std::string,z3::expr>& assnMap,faudes::Generator&);
//	std::tuple<bool,z3::expr> GetAcceptAssn(std::set<faudes::Idx>&, std::map<faudes::Idx, z3::expr>&);
	z3::expr GetEndStateAssertionFromWord(std::string afaword);
	virtual ~SCTransSystem();//here delete all expr stored in mShuffautAssnMap, fa as well..
};

#endif /* SCTRANSSYSTEM_SCTRANSSYSTEM_H_ */
