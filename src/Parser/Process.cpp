/*
 * Process.cpp
 *
 *  Created on: 10-Jun-2015
 *      Author: jaganmohini
 */

#include "Process.h"

Process::Process(Program& P, z3::context& ct, client::Parser& par, int tid): mProgram(P), mCtx(ct), mParser(par) {
	// TODO Auto-generated constructor stub
	mTid=tid;

}

void Process::ParseInput(std::ifstream& inputfile)
		{
			bool state=false;
			//mProgram.mAllSyms.push_back("0");//no need to push now..


			while(inputfile.good())
			{
				std::string line;
				std::getline(inputfile,line);
				std::vector <std::string> fields;
				boost::split_regex( fields, line, boost::regex( ":" ) );
				std::string symname(fields.front());
				if(symname.compare("Regex")==0){
#ifdef	DBGPRNT
					std::cout<<"Regex is "<<fields.back()<<std::endl;
#endif
					//in place of regex, write automata file to read from
					faudes::Generator* spec= new faudes::Generator();
					//By this time all symbols needed for this process must been added in
					//Program's symbol table.. hence pass tid as well
					mProgram.ReadAutSpec(mProgram.mRootPath+"/"+fields.back(),*spec,mTid);
					BOOST_ASSERT_MSG(spec->InitStatesEmpty()==false," Some serious issue");
					mProgram.mProcessesSpec.resize(mTid+1);
					mProgram.mProcessesSpec[mTid]=spec;//put at tid'th index of vector..
					break;
					//extract regex and then break from the loop
				}else if(symname.compare("AMap")==0){
					state=true;

				}else if(state==true){
					//means we are ready to read sym: asserntion..
					boost::split_regex( fields, line, boost::regex( ":" ) );
					z3::expr assrt(client::ParseExp(mParser,fields.back(),mProgram.mVarExprMap,mCtx));
					mProgram.mAssnMap.insert(std::pair<std::string,z3::expr>(fields.front(),assrt));
#ifdef	DBGPRNT
					std::cout<<"Assertion checkable at "<<fields.front()<<" is "<<fields.back()<<std::endl;
#endif
				}
				else {
					fields.erase(fields.begin());//remove the first element;

					//add the symname to the vector so that it could be used later
					mProgram.mAllSyms.push_back(symname);

					mProgram.mSymTidMap.insert(std::make_pair(symname,mTid));

					std::vector <std::string> inside;

					boost::split_regex(inside, fields.front(),boost::regex("[(]"));

					std::string opname(inside.front());
#ifdef	DBGPRNT
					std::cout<<"opname = "<<opname<<std::endl;
#endif
					if(opname.compare("r")==0){
						inside.clear();
						boost::match_results<std::string::const_iterator> results;
						if(boost::regex_match(fields.front(), results, boost::regex("(r)[(](.*?)[)][(](.*?)[)]")))
						{
							std::string res2(results[2]);
							std::string res3(results[3]);
#ifdef	DBGPRNT
							std::cout<<"Found read "<<results[2]<<"="<<results[3]<<std::endl;
#endif
							//NOtice the difference here.. because
							//the formate of read in input file is r(gvar)(lvar) hence we want to represent it as
							//lvar:=rvar
							z3::expr lhs = mProgram.AddIfNot(res3);
							z3::expr rhs = client::ParseExp(mParser,res2,mProgram.mVarExprMap,mCtx);
							std::pair<z3::expr,z3::expr> pr = std::make_pair(lhs,rhs);
							mProgram.mRWLHRHMap.insert(std::make_pair(symname,pr));
							mProgram.mSymType.insert(std::make_pair(symname,"read"));
							//results[2] is lhs
							//results[3] is rhs
						}
					}else if(opname.compare("w")==0 || opname.compare("locw")==0){
						inside.clear();
						boost::match_results<std::string::const_iterator> results;
						if(boost::regex_match(fields.front(), results, boost::regex("(locw)[(](.*?)[)][(](.*?)[)]")))
						{
#ifdef	DBGPRNT
							std::cout<<"Found write "<<results[2]<<"="<<results[3]<<std::endl;
							#endif
							std::string res2(results[2]);
							std::string res3(results[3]);
							z3::expr lhs = mProgram.AddIfNot(res2);
							z3::expr rhs = client::ParseExp(mParser,res3,mProgram.mVarExprMap,mCtx);
							std::pair<z3::expr,z3::expr> pr = std::make_pair(lhs,rhs);
							mProgram.mRWLHRHMap.insert(std::make_pair(symname,pr));
							mProgram.mSymType.insert(std::make_pair(symname,"write"));
							//add it as a localwrite
							mProgram.mLocalWrites.insert(symname);
						}
						if(boost::regex_match(fields.front(), results, boost::regex("(w)[(](.*?)[)][(](.*?)[)]")))
						{
#ifdef	DBGPRNT
							std::cout<<"Found write "<<results[2]<<"="<<results[3]<<std::endl;
#endif
							std::string res2(results[2]);
							std::string res3(results[3]);
							z3::expr lhs = mProgram.AddIfNot(res2);
							z3::expr rhs = client::ParseExp(mParser,res3,mProgram.mVarExprMap,mCtx);
							std::pair<z3::expr,z3::expr> pr = std::make_pair(lhs,rhs);
							mProgram.mRWLHRHMap.insert(std::make_pair(symname,pr));
							mProgram.mSymType.insert(std::make_pair(symname,"write"));

						}
					}else if(opname.compare("assume")==0){
						inside.clear();
						boost::match_results<std::string::const_iterator> results;
						if(boost::regex_match(fields.front(), results, boost::regex("(assume)[(](.*?)[)]")))
						{
#ifdef	DBGPRNT
							std::cout<<"Found assume "<<results[2]<<std::endl;
#endif
							std::string res2(results[2]);
							z3::expr lhs = client::ParseExp(mParser,res2,mProgram.mVarExprMap,mCtx);
							mProgram.mAssumeLHRHMap.insert(std::make_pair(symname,lhs));
							mProgram.mRevAssumeLHRHMap.insert(std::make_pair(lhs,symname));
							mProgram.mSymType.insert(std::make_pair(symname,"assume"));
																					//results[2] is formula
						}
					}else if(opname.compare("lcas")==0){
						inside.clear();
						boost::match_results<std::string::const_iterator> results;
						if(boost::regex_match(fields.front(), results, boost::regex("(lcas)[(](.*?)[)][(](.*?)[)][(](.*?)[)]")))
						{
#ifdef	DBGPRNT
							std::cout<<"Found lcas "<<results[2]<<"="<<results[3]<<"="<<results[4]<<std::endl;
#endif
							std::string res2(results[2]);
							std::string res3(results[3]);
							std::string res4(results[4]);
							z3::expr var = mProgram.AddIfNot(res2);
							z3::expr val1 = client::ParseExp(mParser,res3,mProgram.mVarExprMap,mCtx);
							z3::expr val2 = client::ParseExp(mParser,res4,mProgram.mVarExprMap,mCtx);
							std::tuple<z3::expr,z3::expr,z3::expr> pr = std::make_tuple(var,val1,val2);
							z3::expr assumepart= (var==val1);
							mProgram.mCASLHRHMap.insert(std::make_pair(symname,pr));
							mProgram.mRevAssumeLHRHMap.insert(std::make_pair(assumepart,symname));
							mProgram.mSymType.insert(std::make_pair(symname,"lcas"));
							//results[2] is variable
							//results[3] is value 1
							//results[4] is value 2
						}
					}else
						BOOST_ASSERT_MSG(false,"No compatible operation was found in the input file");
				}

			}

		}


		Process::~Process() {
			// TODO Auto-generated destructor stub
		}

