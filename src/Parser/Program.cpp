/*
 * Program.cpp

 *
 *  Created on: 09-Jun-2015
 *      Author: Chinmay Narayan
 */

#include "Program.h"
#include <boost/foreach.hpp>
#include <boost/assert.hpp>
#include <boost/algorithm/string/regex.hpp>
#include "Process.h"
#include "../AFA/AFAState.h"
#include <boost/graph/graphviz.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <fstream>
#include <boost/graph/iteration_macros.hpp>



bool z3comparator::operator()(const z3::expr& one, const z3::expr& two) const
{
	return one.hash()<two.hash();
}


	Program::Program(const char* filename, z3::context& c, client::Parser& parser):mCtx(c),mParser(parser){
		mFileName = new std::string(filename);
		mNumThds=0;

	}

	/**
	 * A big function to do the work of parsing, whenever it sees a line in the input file
	 * that denotes a new process, it creates a new process object and pass the responsibility
	 * of parsing the relevant information to the class Process. By this any change at the process
	 * description level gets localized to the class Process.
	 */
	ResultType Program::ProcessInput(){
		std::ifstream fin;
		std::string line;
		fin.open(mFileName->c_str());
#ifdef	DBGPRNT
		std::cout<<"About to open the file "<<mFileName->c_str()<<std::endl;
#endif

		if(!fin.is_open())
		{
			BOOST_ASSERT_MSG(false,"Not able to open the input file");
		}
		//extract the path of the mFilenName by removing the last part till

		std::string tfname=*mFileName;
		size_t ind = tfname.rfind("/");
		mRootPath= tfname.substr(0,ind);
		//now pass rest to every process.. where it will append the directory and dot file name
		//to get complete path..
			/**
			 * Extract global variables and store in a map
			 */
			std::getline(fin,line);
			if(line.length()!=0)
			{
				std::vector <std::string> fields;
				boost::split_regex( fields, line, boost::regex( ":" ) );
				BOOST_ASSERT_MSG(fields.front().compare("Init")==0, "First line of the input file must start with Init for global variables");
				fields.erase(fields.begin());//remove the first element Init
				line=fields.front();
				ExtractGlobalVarsAssignment(line);
			}
			/**
			 * Extract process information and pass the filepointer to Process clss to fill their object.
			 */
			while(fin.good())
			{
				std::getline(fin,line);
				if(line.length()==0)
					break;
				std::vector <std::string> fields;
				boost::split_regex( fields, line, boost::regex( ":" ) );
				//std::cout<<"instead of proce we found "<<fields.front()<<std::endl;
				BOOST_ASSERT_MSG(fields.front().compare("Proc")==0, "Process description should start with Proc keyword");
				int tid=std::atoi(fields.back().c_str());
				mNumThds++;
				//Pass the fin object to a newly created Process class.
				Process proc(*this,mCtx,mParser,tid);
				proc.ParseInput(fin);
//				BOOST_ASSERT_MSG(mProcessesSpec[tid]->InitStatesEmpty()==false," Some serious issue");
				std::cout<<"Init is "<<mProcessesSpec[tid]->InitState()<<std::endl;

			}

		fin.close();
//following means we are giving the label name also as rfence for an instruction named rfence.
		//when extending for PSO add one more for wfence.
		mSymType["rfence"]="rfence";//As this should not contribute to po determination..
				//hence no need to put it for some tid.. THis is getting scary.. need to align all of them
				//with some invariants about what is consistent and what is not..

		//Parition symbols.
		PartitionSimilarSymbols();
		return Pro_Parse_Succ;
	}




	std::vector<faudes::Generator*> Program::GetSpecOfAllProcesses()
	{
		return mProcessesSpec;
	}

	std::map<std::string, z3::expr>& Program::GetAssnMapForAllProcesses()
	{
			return mAssnMap;

	}
	void Program::ExtractGlobalVarsAssignment(std::string line)
	{
		std::vector <std::string> fields;
		boost::split_regex( fields, line, boost::regex( "," ) );
		int count =1;
		BOOST_FOREACH(std::string& strs, fields){
					std::vector<std::string> varsval;
					boost::split_regex( varsval, strs, boost::regex( "=" ) );
					//first one is variable, third one is value.
					std::string vars = varsval.front();
					std::string val(varsval.back());
					z3::expr valexp = client::ParseExp(mParser,val,mVarExprMap,mCtx);
					z3::expr varexp = AddIfNot(varsval.front());
					mGlobalVars.insert(std::make_pair(vars,valexp));
					mVarExprMap.insert(std::make_pair(vars,varexp));
					//also add them as a symbol in LRWMap..with new symbols starting from 1 onwards..
#ifdef	DBGPRNT
					std::cout<<"Inserting initial values as write "<<vars<<"="<<val<<std::endl;
#endif
					std::string symname = std::to_string(count);
					mAllSyms.push_back(symname);//so that thse symbols are also present here..
					count++;
					mInitString=mInitString+symname;
					std::pair<z3::expr,z3::expr> pr = std::make_pair(varexp,valexp);
					mRWLHRHMap.insert(std::make_pair(symname,pr));
					mSymType[symname]="write";

			}
		mGVarCount=count-1;//store number of global variables
#ifdef	DBGPRNT
		PrintGlobalVars();
#endif
	}

	z3::expr Program::AddIfNot(std::string& var)
	{
		if(mVarExprMap.find(var)==mVarExprMap.end()){
			z3::expr exp= mCtx.int_const(var.c_str());
			mVarExprMap.insert(std::make_pair(var,exp));
			return exp;
		}else
			return mVarExprMap.find(var)->second;
	}


	void Program::PrintVector( std::vector <std::string> & v )
	{
	  for (size_t n = 0; n < v.size(); n++)
	    std::cout << "\"" << v[ n ] << "\"\n";
	  std::cout << std::endl;
	}

	void Program::PrintGlobalVars(){

		BOOST_FOREACH(auto pars, mGlobalVars){
			std::cout<<pars.first<<"="<<pars.second<<std::endl;
		}
	}

	std::string Program::GetDefVar(std::string sym){
		BOOST_ASSERT_MSG((mRWLHRHMap.find(sym)!=mRWLHRHMap.end()) || (mSymType[sym]=="lcas")," THis symbol is neither read nor write.. invoke this function only on read/write symbols or lcas");
		if(mRWLHRHMap.find(sym)!=mRWLHRHMap.end())
		{
			std::tuple<z3::expr,z3::expr> pr =mRWLHRHMap.find(sym)->second;
			z3::expr lhs=std::get<0>(pr);
			std::stringstream stt;
			stt<<lhs;
			return stt.str();
		}else if(mSymType[sym]=="lcas"){
			std::tuple<z3::expr,z3::expr,z3::expr> pr =mCASLHRHMap.find(sym)->second;
			z3::expr lhs=std::get<0>(pr);
			std::stringstream stt;
			stt<<lhs;
			return stt.str();
		}else
			BOOST_ASSERT_MSG(false,"Control should not reach here, look carefully");

	}

	std::set<std::string> Program::GetUseVars(std::string sym){
		BOOST_ASSERT_MSG((mRWLHRHMap.find(sym)!=mRWLHRHMap.end()) || (mSymType[sym]=="lcas")," THis symbol is neither read nor write.. invoke this function only on read/write symbols or lcas");
		if(mRWLHRHMap.find(sym)!=mRWLHRHMap.end())
		{
			std::tuple<z3::expr,z3::expr> pr =mRWLHRHMap.find(sym)->second;
			z3::expr rhs=std::get<1>(pr);
			std::set<std::string> useset=HelperGetFreeVarsStr(rhs);
			return useset;
		}else if(mSymType[sym]=="lcas"){
			std::tuple<z3::expr,z3::expr,z3::expr> pr =mCASLHRHMap.find(sym)->second;
			z3::expr lhs=std::get<0>(pr);
			std::stringstream stt;
			stt<<lhs;
			std::set<std::string> retset;
			retset.insert(stt.str());
			return retset;
		}else
			BOOST_ASSERT_MSG(false,"Control should not reach here, look carefully");

	}

	std::set<std::string> Program::HelperGetFreeVarsStr(z3::expr& phi){
		std::set<z3::expr,z3comparator> res = HelperGetFreeVars(phi);
		std::set<std::string> rest;

		for(const auto& ex: res)
		{
			std::stringstream sst;
			sst<<ex;
			rest.insert(sst.str());
		}

		return rest;
	}

	std::set<z3::expr,z3comparator> Program::HelperGetFreeVars(z3::expr& phi){
		if(phi.is_var()){
			BOOST_ASSERT_MSG(phi.is_var(),"Some problem: This must be var only");
			std::set<z3::expr,z3comparator> res;
			if(phi.is_int()&&!phi.is_numeral()){//I dont know when will it come here.. this function needs more understanding of z3
				std::cout<<phi<<" is not numeral"<<std::endl;
				res.insert(phi);
			    return res;
			}else
				return res;
		}else if(phi.is_app()){
			std::set<z3::expr,z3comparator> res;
			if(phi.is_int()&&!phi.is_numeral()){
				if(phi.num_args()==0)
				{
//					std::cout<<phi<<" is var too "<<std::endl;
					res.insert(phi);
				}
			}
//			std::cout<<phi<<" is app "<<std::endl;
			unsigned num = phi.num_args();
			for (unsigned i = 0; i < num; i++) {
				z3::expr arg = phi.arg(i);
		        std::set<z3::expr,z3comparator> curr= HelperGetFreeVars(arg);
		        res.insert(curr.begin(),curr.end());
		     }
			return res;
		}else if(phi.is_quantifier()){
			//std::cout<<phi<<" is quantifier"<<std::endl;
			z3::expr arg = phi.body();
			return HelperGetFreeVars(arg);
		}else
			BOOST_ASSERT_MSG(false,"None type of expr found in freevar");


	}

//TODO: later mInitString should also become . separated string..
	/*
	 * Change: 16Mar: I am changing the insertion code so that now instead of inserting fence
	 * before read I will insert it after the write operation.
	 * We need to ensure in the specification that all writes are uniquely labeled.
	 */

	void Program::InsertOrders(std::map<int,std::set<std::pair<std::string,std::string>>>& Orders, std::map<std::string,std::string>& earlierones)
		{

			for(int i=1; i<=mNumThds;i++)
			{
				//get regex of Thdi
				faudes::Generator* gen=mProcessesSpec[i];
				std::set<std::string> secondpart;
				for(const auto& O: Orders[i])
				{
					if(earlierones.find(O.first)==earlierones.end())
						secondpart.insert(O.first);//extract the first part. the write symbol
				}

				//Now pass through generator and whenever a symbol is obtained on a transition that
				//is in firstpart then create another interemediate state with label as rfencsymane
				//and then from that state continue the transitions as were from this state.
				std::set<faudes::Idx> workset;
				std::map<faudes::Idx,bool> seenset;
				workset.insert(gen->InitState());

				while(!workset.empty())
				{
					faudes::Idx curr = *(workset.begin());
					workset.erase(curr);
					seenset.insert(std::make_pair(curr,true));
					std::set<std::pair<faudes::Idx,faudes::Idx>> addtrans;
					//find all outgoing transition from curr..
					//find transitions out of genstate.. and iterate over them..
					//std::set<faudes:>
					faudes::TransSet todel;
					for(faudes::TransSet::Iterator lit = gen->TransRelBegin(curr);lit!=gen->TransRelEnd(curr);lit++)
					{
						std::string sym(gen->EventName(lit->Ev));
						faudes::Idx gendest = lit->X2;
						if(secondpart.find(sym)!=secondpart.end())//means found.. insert fence
						{
#ifdef DBG
							std::cout<<"Inserting fence after "<<sym<<std::endl;
#endif
							//create a new state
							faudes::Idx newst=gen->InsState();
							//add atransition from curr to newst on this symbol,
							//CAVEAT: dont add it now otherwise this loop will never exit
							//as iteration must have changed by then..so
							//put this info in a set like todel and do it later..
							addtrans.insert(std::make_pair(lit->Ev,newst));
							//gen->SetTransition(curr,lit->Ev,newst);
							//add a transition from newst to gendest on rfencesym
							gen->SetTransition(newst,gen->EventIndex("rfence"),gendest);
							//delete this transition
							todel.Insert(*lit);
						}
						//if gendest is not seen add to workset../note we do not add newly added one in
						//in order to avoid repetition.. add newly added one to seenset as well..
						//interesting to proove that it wont happen because only one incoming edge to
						//thisnewly creted node that too by the one that has been seen..
						//[ABOVE INV NOW IS CHANGED because of insertinf fence after write instruction]
						if(seenset.find(gendest)==seenset.end())
						{
							workset.insert(gendest);
						}
					}
					//now add from curr to all states which got create by previous loop..
					for(const auto& pr: addtrans)
						gen->SetTransition(curr,pr.first,pr.second);
					//delete transition in todel..
					faudes::TransSet::Iterator it= todel.Begin();
					while(it!=todel.End()){
						gen->ClrTransition(*it);
						it++;
					}


				}
			}

		}

/*
	void Program::InsertOrders(std::map<int,std::set<std::pair<std::string,std::string>>>& Orders)
	{

		for(int i=1; i<=mNumThds;i++)
		{
			//get regex of Thdi
			faudes::Generator* gen=mProcessesSpec[i];
			std::set<std::string> secondpart;
			for(const auto& O: Orders[i])
			{
				secondpart.insert(O.second);//extract the second part.
			}

			//Now pass through generator and whenever a symbol is obtaind on a transition that
			//is in secondpart then create another interemediate state with label as rfencsymane
			//and then from that state continue the transitions as were from this state.
			std::set<faudes::Idx> workset;
			std::map<faudes::Idx,bool> seenset;
			workset.insert(gen->InitState());

			while(!workset.empty())
			{
				faudes::Idx curr = *(workset.begin());
				workset.erase(curr);
				seenset.insert(std::make_pair(curr,true));
				//find all outgoing transition from curr..
				//find transitions out of genstate.. and iterate over them..
				//std::set<faudes:>
				faudes::TransSet todel;
				for(faudes::TransSet::Iterator lit = gen->TransRelBegin(curr);lit!=gen->TransRelEnd(curr);lit++)
				{
					std::string sym(gen->EventName(lit->Ev));
					faudes::Idx gendest = lit->X2;
					if(secondpart.find(sym)!=secondpart.end())//means found.. insert fence
					{
						//create a new state
						faudes::Idx newst=gen->InsState();
						//add atransition from newst to gendest on this symbol
						gen->SetTransition(newst,lit->Ev,gendest);
						//add a transition from curr to newst on rfencesym
						gen->SetTransition(curr,gen->EventIndex("rfence"),newst);
						//delete this transition
						todel.Insert(*lit);
						seenset.insert(std::make_pair(newst,true));
					}
					//if gendest is not seen add to workset../note we do not add newly added one in
					//in order to avoid repetition.. add newly added one to seenset as well..
					//interesting to proove that it wont happen because only one incoming edge to
					//thisnewly creted node that too by the one that has been seen..
					if(seenset.find(gendest)==seenset.end())
					{
						workset.insert(gendest);
					}
				}
				//delete transition in todel..
				faudes::TransSet::Iterator it= todel.Begin();
				while(it!=todel.End()){
					gen->ClrTransition(*it);
					it++;
				}


			}
		}

	}
*/

	void Program::ReadAutSpec(std::string filename,faudes::Generator& generator, int tid){
		{
		typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
		                              boost::property<boost::vertex_name_t, std::string>,
		                              boost::property<boost::edge_weight_t, std::string> > Digraph;

		  std::ifstream in(filename.c_str());
		  if(!in.is_open())
	  		{
			  std::cout<<"Not able to open the input file "<<filename<<std::endl;
		  			BOOST_ASSERT_MSG(false,"Not able to open the input file");
	  		}
		  Digraph g;
		  boost::dynamic_properties dp(boost::ignore_other_properties);
		  std::map<std::string, faudes::Idx>genstatemap;
		  dp.property("label", boost::get(boost::vertex_name, g));
		  dp.property("label", boost::get(boost::edge_weight, g));
		  (read_graphviz(in, g, dp, "label"));

		  //MAKE 0 always as init state..
		  //insert events from symtid map which are of same tid..
		  for(const auto& sympair: mSymTidMap)
		  {
			  if(sympair.second==tid){
				  generator.InsEvent(sympair.first);
			  }
		  }
		  //also add mfence event..
		  generator.InsEvent("rfence");
		  BGL_FORALL_VERTICES(v, g, Digraph){
			std::string verna=boost::get(boost::vertex_name, g, v);
//		    std::cout<<"Name is "<<verna<<std::endl;
		    faudes::Idx src;
		    if(genstatemap.find(verna)!=genstatemap.end())
		    	src=genstatemap.find(verna)->second;
		    else{
		    	src=generator.InsState();
		    	genstatemap[verna]=src;
		    }
		    if(verna.compare("0")==0)
		    	generator.InsInitState(src);
		    BGL_FORALL_OUTEDGES_T(v, en, g, Digraph){
		    	std::string vernb=boost::get(boost::vertex_name,g,en.m_target);
		    	faudes::Idx dest;
		    	if(genstatemap.find(vernb)!=genstatemap.end())
		    	    	dest=genstatemap.find(vernb)->second;
		    	    else{
		    	    	dest=generator.InsState();
		    	    	genstatemap[vernb]=dest;
		    	    }
     std::string evn=boost::get(boost::edge_weight,g,en);
        //extract till :
        std::string mod = evn.substr(0,evn.find_first_of(":"));

//		         std::cout<<"Connected to "<<boost::get(boost::vertex_name,g,(en).m_target)<<" with label as "<<mod<<std::endl;
		    	//add edge from src to dest on get(edge_weight,g,en)
		    	generator.SetTransition(src,generator.EventIndex(mod),dest);
		        }
		     }

		}
	}



	//It is worth checking if class z3::expr has built in comparator becaue then in that case
	//we wont need following comparator..
	struct z3comparatortwo{
	bool operator()(const std::tuple<z3::expr,z3::expr>& one, const std::tuple<z3::expr,z3::expr>& two) const
	{
		if(std::get<0>(one).hash()==std::get<0>(two).hash())
			return std::get<1>(one).hash() < std::get<1>(two).hash();
		else
			return std::get<0>(one).hash() < std::get<0>(two).hash();
	}
	};

	struct z3comparatorthree
	{
	bool operator()(const std::tuple<z3::expr,z3::expr,z3::expr>& one, const std::tuple<z3::expr,z3::expr,z3::expr>& two) const
		{
		if(std::get<0>(one).hash()==std::get<0>(two).hash())
			if(std::get<1>(one).hash()==std::get<1>(two).hash())
				return std::get<2>(one).hash() < std::get<2>(two).hash();
			else
				return std::get<1>(one).hash() < std::get<1>(two).hash();
		else
			return std::get<0>(one).hash() < std::get<0>(two).hash();

		}
	};
	/*
	 * Following function must be called only after all symbols have been added to mAllSyms
	 */

	void Program::PartitionSimilarSymbols(){
		//mMap
		    std::map<std::tuple<z3::expr, z3::expr>,std::set<std::string>,z3comparatortwo> RWLHRHMap;
			std::map<z3::expr,std::set<std::string>,z3comparator> AssumeLHRHMap;
			std::map<std::tuple<z3::expr, z3::expr,z3::expr>,std::set<std::string>,z3comparatorthree> CASLHRHMap;

		for(const auto& sym: mAllSyms)
		{
			if(mSymType[sym]=="read"||mSymType[sym]=="write"){
				std::tuple<z3::expr,z3::expr> info = mRWLHRHMap.find(sym)->second;
				if(RWLHRHMap.find(info)==RWLHRHMap.end()){
					std::set<std::string> sset;
					sset.insert(sym);
					RWLHRHMap.insert(std::make_pair(info,sset));
				}else{
					RWLHRHMap[info].insert(sym);
				}

			}else if(mSymType[sym]=="assume"){
				z3::expr info = mAssumeLHRHMap.find(sym)->second;
				if(AssumeLHRHMap.find(info)==AssumeLHRHMap.end()){
					std::set<std::string> sset;
					sset.insert(sym);
					AssumeLHRHMap.insert(std::make_pair(info,sset));
				}else{
					AssumeLHRHMap[info].insert(sym);
				}
			}else if(mSymType[sym]=="lcas"){
				std::tuple<z3::expr,z3::expr,z3::expr> info = mCASLHRHMap.find(sym)->second;
				if(CASLHRHMap.find(info)==CASLHRHMap.end()){
					std::set<std::string> sset;
					sset.insert(sym);
					CASLHRHMap.insert(std::make_pair(info,sset));
				}else{
					CASLHRHMap[info].insert(sym);
				}

			}//lets not do it for fence..
		}//

		//after we are done with all symbols..iterate over these maps to construct a mapof similar symbols..
		for(const auto& elp: RWLHRHMap)
		{
			for(const auto& el: elp.second)
			{
				mPartitionedSyms[el]=elp.second;
			}
		}

		for(const auto& elp: AssumeLHRHMap)
		{
			for(const auto& el: elp.second)
			{
				mPartitionedSyms[el]=elp.second;
			}
		}

		for(const auto& elp: CASLHRHMap)
		{
			for(const auto& el: elp.second)
			{
				mPartitionedSyms[el]=elp.second;
			}
		}

		//parition classes of symbols..
		std::set<std::string>allsyms;
		allsyms.insert(mAllSyms.begin(),mAllSyms.end());
			std::set<std::string> partsyms;
			while(!allsyms.empty()){
				std::string sm = *(allsyms.begin());
				mPartitionedSymClass.insert(sm);
				//from allsyms remove all states prsent in mProgram->mPartitionedSyms[sm] except sm itself..
				std::set<std::string> toremove = mPartitionedSyms[sm];
				std::set<std::string> res;
				std::set_difference(allsyms.begin(),allsyms.end(),toremove.begin(),toremove.end(),std::inserter(res,res.end()),allsyms.value_comp());
				allsyms.clear();
				allsyms.insert(res.begin(),res.end());
			}
			//when finished mPartitionedSymClass will have partitioned symbols..


	}

	/**
	 * Destructor
	 */
	Program::~Program() {
		if(mFileName!=NULL)
		{
			delete mFileName;
			mFileName=NULL;
		}

	}
