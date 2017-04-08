/*
 * Program.h
 *
 *  Created on: 09-Jun-2015
 *      Author: Chinmay Narayan
 *      Description: This class is responsible for parsing the input file and generate
 *      an appropriate number of Process objects, one for each process description present in
 *      the file. These process objects are stored in an object of this class.
 */

#ifndef PARSER_PROGRAM_H_
#define PARSER_PROGRAM_H_
#include<iostream>
#include<fstream>
#include<vector>
#include <unordered_map>
#include<map>
#include "ResultType.h"
#include "QiParser.h"
#include <libfaudes.h>//WHY this ordering was important.. If I put it after c++/z3++ then lots of error..
#include <c++/z3++.h>
#include <tuple>
#include <set>

struct z3comparator{
	bool operator()(const z3::expr& one, const z3::expr& two) const;
};


struct pairexpcomparator{
	bool operator() (const std::tuple<z3::expr,z3::expr,int>& one, const std::tuple<z3::expr,z3::expr,int>& two) const
	  	{

			z3::expr firstone=std::get<0>(one);
			z3::expr secondone=std::get<1>(one);
			z3::expr firsttwo=std::get<0>(two);
			z3::expr secondtwo=std::get<1>(two);
			int tidone=std::get<2>(one);
			int tidtwo=std::get<2>(two);
	  			if (tidone==tidtwo)
	  				if (firstone.hash()==firsttwo.hash())
	  					return secondone.hash() < secondtwo.hash();
	  				else
	  					return firstone.hash()<firsttwo.hash();
	  			else
	  				return tidone<tidtwo;
	  	}
};
class Program {




public:
	/** Following three vars added to support renaming under relaxed memory models..*/
	std::map<std::string,int> mChangedWriteReadSymbmap;
	std::map<std::tuple<z3::expr,z3::expr,int>,std::string,pairexpcomparator> mExprToSymbMap;
	std::map<std::string,std::string> mNewOldSymbMap;

	///////////////////////////////////////////////////////////////////////////////////
	void PartitionSimilarSymbols();
	std::set<std::string > mPartitionedSymClass;
	std::map<std::string,std::set<std::string>> mPartitionedSyms;
std::string mRootPath;
	std::map<std::string, z3::expr> mGlobalVars;//map for global variable and its initial values
	std::string* mFileName;
	client::Parser& mParser;
	std::string mInitString;
	z3::context& mCtx;
	std::map<std::string,std::string> mSymType;
	std::map<std::string, z3::expr> mVarExprMap;
	std::map<std::string, std::tuple<z3::expr, z3::expr>> mRWLHRHMap;
	std::map<std::string, z3::expr> mAssumeLHRHMap;
	std::map<z3::expr,std::string,z3comparator> mRevAssumeLHRHMap;
	std::map<std::string, std::tuple<z3::expr, z3::expr,z3::expr>> mCASLHRHMap;
	std::map<std::string, z3::expr> mAssnMap;//map for label-> assert statements for all processes
	std::vector<faudes::Generator*> mProcessesSpec;
	std::vector<std::string> mAllSyms;
	std::set<std::string> mLocalWrites;
	std::map<std::string,int> mSymTidMap;
	int mNumThds;
	int mGVarCount;
	Program(const char* filename, z3::context& c, client::Parser& parser);
	ResultType ProcessInput();
	z3::expr AddIfNot(std::string& var);
	std::vector<faudes::Generator*> GetSpecOfAllProcesses();
	std::map<std::string, z3::expr >& GetAssnMapForAllProcesses();
	void ExtractGlobalVarsAssignment(std::string line);
	void PrintGlobalVars();
	std::string GetDefVar(std::string sym);
	std::set<std::string> GetUseVars(std::string sym);
	static std::set<std::string> HelperGetFreeVarsStr(z3::expr& phi);
	static std::set<z3::expr,z3comparator> HelperGetFreeVars(z3::expr& phi);
	void PrintVector( std::vector <std::string> & v );
	void InsertOrders(std::map<int,std::set<std::pair<std::string,std::string>>>& Orders, std::map<std::string,std::string>&);
	//New function added to readin a automata file in dot format..
	void ReadAutSpec(std::string filename,faudes::Generator&, int);


	virtual ~Program();
};

#endif /* PARSER_PROGRAM_H_ */
