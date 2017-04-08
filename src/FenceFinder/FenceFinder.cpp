/*
 * FenceFinder.cpp
 *
 *  Created on: 30-Dec-2015
 *      Author: chinmay
 */

#include "FenceFinder.h"
#include <boost/tokenizer.hpp>
#include<tuple>
#include <sstream>
#include <map>
//#include <boost/graph/directed_graph.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/tiernan_all_cycles.hpp>
#include <boost/graph/iteration_macros.hpp>
template <class Name>
class myEdgeWritertwo {
  public:
         myEdgeWritertwo(Name _name) : name(_name) {}
              template <class VertexOrEdge>
                     void operator()(std::ostream& out, const VertexOrEdge& v) const {
                                   out << "[label=\"" << name[v].label << "\"]";
                                        }
  private:
                   Name name;
};


template <class Name>
class myVertWritertwo {
  public:
         myVertWritertwo(Name _name) : name(_name) {}
              template <class VertexOrEdge>
                     void operator()(std::ostream& out, const VertexOrEdge& v) const {
//                                   out << "[label=\"" << name[v].vertlabel << "\", xlabel=\" "<<name[v].xlabel<<"\", color="<<name[v].color<<",shape="<<name[v].shape<<"]";
            	  out << "[label=\"" << name[v]<< "\"]";
                                        }
  private:
                   Name name;
};
//I am assuming ordered set and hence it will contain cycles in increasing size..
//also assuming that smaller cycle will be of smaller length.. might not be true.
std::set<std::string> mincyclemap;
//int mincyclelen=0;
template <typename OutputStream>
struct cycle_printer
{
    cycle_printer(OutputStream& stream)
        : os(stream)
    { }

    template <typename Path, typename Graph>
    void cycle(const Path& p, const Graph& g)
    {
        // Get the property map containing the vertex indices
        // so we can print them.
        typedef typename boost::property_map<Graph, boost::vertex_index_t>::const_type IndexMap;
        typedef typename boost::property_map<DGraph, boost::vertex_name_t>::const_type VertMap;

        IndexMap indices = boost::get(boost::vertex_index, g);
        VertMap vertindices = boost::get(boost::vertex_name,g);

        // Iterate over path printing each vertex that forms the cycle.
        typename Path::const_iterator i, end = p.end();
        int len=0;
        std::stringstream ss;
        for(i = p.begin(); i != end; ++i) {
        	ss << boost::get(vertindices, *i) << ",";
//        	os << boost::get(vertindices, *i) << ", ";
        	//std::cout<<"symbol extracted fropm node is "<<boost::get(vertindices,*i)<<std::endl;
        	len++;
        }
       // os << std::endl;

        BOOST_ASSERT_MSG(len!=0, " Some serious error");
        mincyclemap.insert(ss.str());
       /* if(mincyclelen==0 || mincyclelen>len)
        {
        	mincyclelen=len;
        	mincycle=ss.str();
    //    	std::cout<<" Smaller is "<<mincycle<<std::endl;
        }*/
        //os<<"t"<<std::endl;

    }
    OutputStream& os;
};

FenceFinder::FenceFinder(TSOTransSystem* mP): mTsoTransSystem(mP) {
	// TODO Auto-generated constructor stub

}

FenceFinder::~FenceFinder() {
	// TODO Auto-generated destructor stub
}

std::map<int,std::set<std::pair<std::string,std::string>>> FenceFinder::OrderFinder(PO po, RF rfe, RF rfi, std::map<std::string, std::string>& existingorders)
{
	rfe.insert(rfi.begin(),rfi.end());
	//rfi.clear();
	std::set<std::string > nds;
	std::set<std::string> varinterest;
//first fill all nodes which contribute to rf..
	for(const auto& el: rfe){
		//std::cout<<el.first<<" reads from "<<el.second<<std::endl;
//				nds.insert(el.first);
	//			nds.insert(el.second);
				varinterest.insert(GetGVarAccessed(el.first));
			}

	for(const auto& el: rfi){
		//std::cout<<"Local--"<<el.first<<" reads from "<<el.second<<std::endl;
				/*nds.insert(el.first);
				nds.insert(el.second);
				varinterest.insert(GetGVarAccessed(el.first));*/
			}

	//fill prevpo..
	PO prevpo;
	PO finalpo;
	std::set<std::string > poelems;
	for(const auto& el: po){
		prevpo[el.second]=el.first;
		finalpo[el.first]=el.second;
	}
	std::set<std::string> initstr;
	for(const auto& el: po){

		if(prevpo.find(el.first)==prevpo.end())
		{
//			std::cout<<"init is "<<el.first<<std::endl;
			initstr.insert(el.first);

		}
	}

	//fill in po only among those nodes.. which are either in rfe or rfi or are write to the variables
	//which rfe/rfi reads from..
	for(const auto& i: initstr )
	{
	std::string curr=i;
	while(true){
//		std::cout<<"curr is "<<curr<<std::endl;
		if(!IsRead(curr) && !IsWrite(curr)){
					if(prevpo.find(curr)!=prevpo.end())
					{
						if(finalpo.find(curr)!=finalpo.end())
						{
							finalpo[prevpo[curr]]=finalpo[curr];
							prevpo[finalpo[curr]]=prevpo[curr];
							prevpo.erase(curr);
							std::string tmpcurr=finalpo[curr];
							finalpo.erase(curr);
							curr=tmpcurr;
						}else
						{
							finalpo.erase(prevpo[curr]);
							break;
						}
					}
					else
					{
						if(finalpo.find(curr)!=finalpo.end())
							{
								prevpo.erase(finalpo[curr]);
								std::string tmpcurr=finalpo[curr];
								finalpo.erase(curr);
								curr=tmpcurr;
							}else
							{
								BOOST_ASSERT_MSG(false,"Some serious errror");
							}
					}
		}else if(varinterest.find(GetGVarAccessed(curr))!=varinterest.end()){
	//		nds.insert(curr);
			if(finalpo.find(curr)!=finalpo.end())
				curr=finalpo[curr];
			else
				break;
		}else{
			if(prevpo.find(curr)!=prevpo.end())
								{
									if(finalpo.find(curr)!=finalpo.end())
									{
										finalpo[prevpo[curr]]=finalpo[curr];
										prevpo[finalpo[curr]]=prevpo[curr];
										prevpo.erase(curr);
										std::string tmpcurr=finalpo[curr];
										finalpo.erase(curr);
										curr=tmpcurr;
									}else
									{
										finalpo.erase(prevpo[curr]);
										break;
									}
								}
								else
								{
									if(finalpo.find(curr)!=finalpo.end())
										{
											prevpo.erase(finalpo[curr]);
											std::string tmpcurr=finalpo[curr];
											finalpo.erase(curr);
											curr=tmpcurr;
										}else
										{
											BOOST_ASSERT_MSG(false,"Some serious errror");
										}
								}
		}

	}
	}
	for(const auto& el: finalpo){
		nds.insert(el.first);
		nds.insert(el.second);
	}
	for(const auto& el: rfe){
		BOOST_ASSERT_MSG(nds.find(el.first)!=nds.end(),"Error ");
//		std::cout<<el.first<<" is in there "<<std::endl;
		nds.insert(el.second);
		BOOST_ASSERT_MSG(nds.find(el.second)!=nds.end(),"Error ");
//		std::cout<<el.second<<" is in there "<<std::endl;
	}
#ifdef DBG
	for(const auto& el: finalpo){
		BOOST_ASSERT_MSG(nds.find(el.first)!=nds.end(),"Error ");
		BOOST_ASSERT_MSG(nds.find(el.second)!=nds.end(),"Error ");
				std::cout<<el.first<<" connected to ---> "<<el.second<<std::endl;
		}
#endif
	po.clear();
	po.insert(finalpo.begin(),finalpo.end());
#ifdef DBG
	for(const auto& el: po){
			BOOST_ASSERT_MSG(nds.find(el.first)!=nds.end(),"Error ");
			BOOST_ASSERT_MSG(nds.find(el.second)!=nds.end(),"Error ");
					std::cout<<el.first<<" dddd connected to ---> "<<el.second<<std::endl;
			}
#endif
	BOOST_ASSERT_MSG(nds.find("")==nds.end()," Some error");
#ifdef DBG
	std::cout<<"Number of nodes in graph are "<<nds.size()<<std::endl;
#endif

//Add nodes in the graph corresponding to nds..


//add PO edges from po and poloc to separate graphs

//add rf edges from rfe and rfi to different graphs..


	//Take Trans closure of both graphs

	//Repeat{
	//store in tmps;
	//1. fill rw based on rfe and rfi and add these edges to both graphs
	//2. for each read in rfe, see if a new edge can be added..
	//3. for each read in rfi, see if a new edge can be added..
	//4. Take trans closure of both graphs
	//}Until no change in graphs from the earlier snapshot

//DO: add nodes in the graph corresponding to nds
	std::map<std::string,gvertex> pographnodemap;
	std::map<std::string,gvertex> polocgraphnodemap;
	DGraph pograph;
	DGraph polocgraph;
	std::map<gvertex,std::string> wmappograph;
	std::map<gvertex,std::string> wmappolocgraph;
	std::map<gvertex,std::string> rmappograph;
	std::map<gvertex,std::string> rmappolocgraph;
	std::map<gvertex, std::set<gvertex>> wwrelpograph;
	std::map<gvertex, std::set<gvertex>> wwrelpolocgraph;
	std::map<gvertex,gvertex> rfeinfopograph;
	std::map<gvertex,gvertex> rfeinfopolocgraph;
	std::map<gvertex,gvertex> rfiinfopolocgraph;
	std::map<gvertex,gvertex> rfiinfopograph;
	std::map<std::string, gvertex> initpographmap;
	std::map<std::string, gvertex> initpolocgraphmap;
	std::map<gvertex,gvertex> poandpolocnodemap;
	std::map<gvertex,std::string> varmappograph;
	/** fill in node maps and create graphs*/


			unsigned long count=0;//IMP: Alwasy put graph's index from 0.. I found it by hard way..
			//Because any vector (of size = number of nodex) will start indexing from 0 upto the length
			//and if it find idnex of somethign as length of the vector it will corrupt memroy..

			//Getting following map was important that was used to assign name and index to vertices
			//which were being create.. note that these two maps come from the fact that vertexpoerty
			//of DGraph has two properites vertex_name_t and vertex_index_t..
			//If I do not do this filling of map then write_graphviz generates all nodes with label 0.
	boost::property_map<DGraph, boost::vertex_name_t>::type   namemappo = boost::get(boost::vertex_name_t(), pograph);
	boost::property_map<DGraph, boost::vertex_name_t>::type   namemappoloc = boost::get(boost::vertex_name_t(), polocgraph);
	boost::property_map<DGraph, boost::vertex_index_t>::type   indexmapppo = boost::get(boost::vertex_index_t(), pograph);
	boost::property_map<DGraph, boost::vertex_index_t>::type   indexmappoloc = boost::get(boost::vertex_index_t(), polocgraph);

	std::set<std::string> writenodes;
	for(const std::string& nod: nds)
	{
//		VertexProp vp;
//		vp.shape="rectangle";
//		vp.color="yellow";
		std::string node=nod;
		boost::graph_traits<DGraph>::vertex_descriptor v0 = boost::add_vertex(pograph);
		boost::graph_traits<DGraph>::vertex_descriptor v1 = boost::add_vertex(polocgraph);
		pographnodemap.insert(std::make_pair(node,v0));
		polocgraphnodemap.insert(std::make_pair(node,v1));
		if(IsRead(node))
		{
			std::string var=GetGVarAccessed(node);
			BOOST_ASSERT_MSG(var.length()!=0,"Some seriour error");
//			std::cout<<"Var of "<<node<<" is "<<var<<std::endl;
			rmappograph[v0]=var;
			rmappolocgraph[v1]=var;
			varmappograph[v0]=var;
		}else if(IsWrite(node))
		{
			writenodes.insert(node);
			std::string var=GetGVarAccessed(node);
			BOOST_ASSERT_MSG(var.length()!=0,"Some seriour error");
//			std::cout<<"Var of "<<node<<" is "<<var<<std::endl;
			wmappograph[v0]=var;
			wmappolocgraph[v1]=var;
			varmappograph[v0]=var;
			if(IsInitial(node)){
				initpographmap[var]=v0;
				initpolocgraphmap[var]=v1;
			}
		}//it can be assume also then we dont keep track of them..
		poandpolocnodemap[v0]=v1;

//		std::stringstream stream;
//		stream << node;
//		vp.vertlabel=stream.str();
//		stream.str(std::string());//erase the buffer
//		vp.xlabel=stream.str();
//		get(vertex_index,pograph[v0]=count;
		//pograph[v1]=count;
		namemappo[v0]=node;
		namemappoloc[v1]=node;
		indexmapppo[v0]=count;
		indexmappoloc[v1]=count;
		count++;
	}

/*
	for(const auto& el: varmappograph)
		std::cout<<"elem is "<<el.first<<","<<el.second<<std::endl;
 */
	AddProgramOrderEdges(po,pograph,pographnodemap);
#ifdef DBG
	std::ofstream podotfile ("posaturated.dot");
	boost::write_graphviz(podotfile, pograph, boost::make_label_writer(boost::get(boost::vertex_name_t(), pograph)));
#endif

    boost::warshall_transitive_closure(pograph);
	//Insert ww edges..
	for(auto const& wt: writenodes)
	{
		boost::graph_traits<DGraph>::vertex_descriptor vouter = pographnodemap[wt];
		for(auto const& wt2: writenodes)
				{
			boost::graph_traits<DGraph>::vertex_descriptor vin = pographnodemap[wt2];
					if(wt2.length()>wt.length() && wmappograph[vin].compare(wmappograph[vouter])==0)
					{
						//add an ww edge from wt2 to wt..
						boost::add_edge(vin,vouter,pograph);

					}
				}

	}
	//0. extract wwrel from TCpotmp and TCpoloctmp, fill them in wwrelpograph and wwrelpolocgraph
	ExtractWW(pograph,wmappograph,wwrelpograph);
#ifdef DBG
	for(const auto& el: wwrelpograph){
		std::cout<<namemappo[el.first]<<" is connected in ww to "<<std::endl;
		for(const auto& e: el.second){
			std::cout<<"----"<<namemappo[e]<<std::endl;
		}
	}
#endif
    AddRFEdges(rfe,pograph,pographnodemap,rfeinfopograph,true);
#ifdef DBG
    for(const auto& el: rfe){
    		std::cout<<el.first<<" reads from "<<el.second<<std::endl;
    }
#endif
    AddRWEdges(pograph,rfeinfopograph, wwrelpograph);
    /*for(const auto& el: wwrelpograph){
    		std::cout<<namemappo[el.first]<<" is connected in ww to "<<std::endl;
    		for(const auto& e: el.second){
    			std::cout<<"----"<<namemappo[e]<<std::endl;
    		}
    	}*/
    //for debugging purpose.. print poloc graph
    //	 boost::write_graphviz(podotfile, pograph, boost::make_label_writer(boost::get(boost::vertex_name_t(), pograph)));
    //boost::write_graphviz(polocdotfile, polocgraph, boost::make_label_writer(boost::get(boost::vertex_name_t(), polocgraph)));
     //Find cycles in pograph.. and cycles of length >1 (or remove self cycles whichever work earlier)
     cycle_printer<std::ostream> vis(std::cout);
#ifdef DBG
     std::cout<<"Number of nodesin grpah are "<<boost::num_vertices(pograph)<<std::endl;
#endif
     boost::tiernan_all_cycles(pograph,vis,boost::num_vertices(pograph));

     /*
     std::cout<<"Min cycle is of length "<<mincyclelen;
     std::cout<<"Min cycle is "<<mincycle<<std::endl;*/
     std::map<int,std::set<std::pair<std::string,std::string>>> Order,totalorder;
     bool issame=true;
     for(const auto& cycle: mincyclemap)
     {
    	 Order =GetOrderFromCriticalCycle(cycle);
//    	 std::cout<<"cycle is "<<cycle<<std::endl;
    	 issame=true;
    	 for(const auto& el: Order){
    	     		 for(const auto& els: el.second)
    	     		 {
    	     			 //std::cout<<"Order is "<<els.first<<" before "<<els.second<<std::endl;
    	     			 totalorder[el.first].insert(Order[el.first].begin(),Order[el.first].end());
    	     			 /*if(existingorders.find(els.first)==existingorders.end() || existingorders[els.first]!=els.second)
    	     				 {issame=false;
    	     			 	 break;}*/
    	     		 }
    	     		/* if(!issame)
    	     			 break;*/

    	     	 }
    	 /*if(!issame)
    		 break;*/
     }
     //BOOST_ASSERT_MSG(issame==false,"Some serious error");

//It is important that existing orders are not returned by iternan_all_cycles function..How to ensure that..
//Make change sin tiernan custom function to return set of all cycles..in the increasing order of their size..
     //for each of them find order.. if same as existing increase the number and check another..
#ifdef DBG
    	 for(const auto& el: totalorder){
    		 for(const auto& els: el.second)
    			 std::cout<<"Order "<<els.first<<" before "<<els.second<<std::endl;
    	 }
#endif
       return Order;


}

std::map<int,std::set<std::pair<std::string,std::string>>> FenceFinder::GetOrderFromCriticalCycle(std::string mincycle){

	  boost::char_separator<char> sep(",");
	     boost::tokenizer<boost::char_separator<char>> tokens(mincycle, sep);
	     BOOST_ASSERT_MSG(tokens.begin()!=tokens.end()," At least one symbol must be present some serious error");
	     std::vector<std::string> cycle;
	     std::string lastsym,lastop,lastvar,thissym,thisop,thisvar,firstsym,firstvar,firstop="";
	     int lasttid,thistid,firsttid;
	     std::map<int,std::set<std::pair<std::string,std::string>>> Order;
//	     std::cout<<"Finding orders for cycle "<<mincycle<<std::endl;
	     for (const std::string& sym: tokens)
	     {
//	    	 std::cout<<"Insider order finding loop "<<sym<<std::endl;


	    	 if(lastsym.length()==0)
	    	 {
	    		 lastsym=GetOldSym(sym);

	    		 if(IsRead(sym))
	    		 lastop="read";
	    		 else if(IsWrite(sym))
	    			 lastop="write";
	    		 else{
	    			 std::cout<<lastsym<<" is neither read, nor write sym"<<std::endl;

	    			 BOOST_ASSERT_MSG(false,"Some serious error, cycle must not include assert or fence");
	    		 }
	    		 lastvar=GetGVarAccessed(sym);
	    		 lasttid=GetOldSymTid(sym);
	    		 firstsym=lastsym;
	    		 firsttid=lasttid;
	    		 firstvar=lastvar;
	    		 firstop=lastop;
	    	 }else{
	    		  thissym=GetOldSym(sym);
	    		  if(IsRead(sym))
	    		  thisop="read";
	    		  else if(IsWrite(sym))
	    		  thisop="write";
	    		  else
	    		  BOOST_ASSERT_MSG(false,"Some serious error, cycle must not include assert or fence");
	    		  thisvar=GetGVarAccessed(sym);
	    		  thistid=GetOldSymTid(sym);

	    		  if(lasttid==thistid && lastvar.compare(thisvar)!=0 && lastop=="write" && thisop=="read")//FOR TSO.. for PSO make different
	    				  {
//	    					  std::cout<<"Order "<<lastsym<<" before "<<thissym<<std::endl;
	    					  if(Order.find(lasttid)!=Order.end())
	    						  Order[lasttid].insert(std::make_pair(lastsym,thissym));
	    					  else
	    					  {
	    						  Order[lasttid]=std::set<std::pair<std::string,std::string>>();
	    						  Order[lasttid].insert(std::make_pair(lastsym,thissym));
	    					  }
	    				  }
	    		  else if(firsttid==thistid && firstvar.compare(thisvar)!=0 && firstop=="read" && thisop=="write")//FOR TSO.. for PSO make different
	    		  {
//	    			  std::cout<<"Order "<<thissym<<" before "<<firstsym<<std::endl;
	    		    					  if(Order.find(thistid)!=Order.end())
	    		    						  Order[thistid].insert(std::make_pair(thissym,firstsym));
	    		    					  else
	    		    					  {
	    		    						  Order[thistid]=std::set<std::pair<std::string,std::string>>();
	    		    						  Order[thistid].insert(std::make_pair(thissym,firstsym));
	    		    					  }
	    		  }
	    		  lastsym=thissym;
	    		  lasttid=thistid;
	    		  lastvar=thisvar;
	    		  lastop=thisop;


	    	 }
	     }
	     /*for(const auto& el: Order){
	    	 std::cout<<"For process "<<el.first<<std::endl;
	    	 for(const auto& ors: el.second)
	    	 {
	    		 std::cout<<"Order "<<ors.first<<" before "<<ors.second<<std::endl;
	    	 }
	     }*/
	     return Order;

}


std::map<int,std::set<std::pair<std::string,std::string>>> FenceFinder::GetCriticalCycle(DGraph& pograph, std::map<std::string,gvertex>& pographnodemap, PO& rfe, std::map<std::string, std::string>& existing)
{
	std::map<int,std::set<std::pair<std::string,std::string>>> Ord;
	for(const auto& elrf: rfe)
	{

		//get read node..
		std::string rnd = elrf.first;
		//std::cout<<"Checking from read "<<elrf.first<<" read from "<<elrf.second<<std::endl;
		//get vertex corresponding to rnd.
		BOOST_ASSERT_MSG(pographnodemap.find(rnd)!=pographnodemap.end()," Some serious issue ");
		gvertex rndv=pographnodemap[rnd];
		std::set<gvertex> lastset;
		std::map<gvertex,std::string> lastsetmap;
		lastset.insert(rndv);
		lastsetmap[rndv]=(boost::get(boost::vertex_name, pograph,rndv));
		int cnt=1;
		while(cnt<=6)//change it later
		{
			std::set<gvertex> newlastset;
			std::map<gvertex,std::string> newlastsetmap;
			for(const auto& gnd: lastset)
			{
				//put each successor of gnd in newlastset(if not there) with newlastmap as derived
				//from lastmap of gnd with this transition..
				//get its successors..
				out_edge_iter ei, ei_end;
				for (tie(ei, ei_end) = boost::out_edges(gnd,pograph); ei != ei_end; ++ei)
				{
				  gvertex dest = (*ei).m_target;
				  //get string back from this..
	/*			  if(dest==rndv)
					  return lastsetmap[gnd];*/
				  if(newlastset.find(dest)==newlastset.end())
				  {
					  newlastset.insert(dest);
					  newlastsetmap[dest]=lastsetmap[gnd]+","+boost::get(boost::vertex_name , pograph,dest);
				  }

				 }
			}
			//clear lastset and copy newlastset to lastset and similarly to newlastmap..
				lastset.clear();
				lastset.insert(newlastset.begin(),newlastset.end());
				lastsetmap.clear();
				lastsetmap.insert(newlastsetmap.begin(),newlastsetmap.end());
			cnt++;
		}
		if(lastset.find(rndv)!=lastset.end())
		{
			//means cycle found.. get order from cycle..
			Ord = GetOrderFromCriticalCycle(lastsetmap[rndv]);

			//if every order is in existing then repeate else return ord..
			for(const auto& el: Ord){
				for(const auto& els: el.second){
					if(existing.find(els.first)==existing.end())
						return Ord; //means one such order found that was not present earlier..
				}
			}
			//else continue in the loop for next cycle..
		}
//			return lastsetmap[rndv];
	}

	BOOST_ASSERT_MSG(false," Control should not reach here as no critical cycle found within the stipulated distance");
}
std::string FenceFinder::GetOldSym(const std::string nds)
{
	//extract first symbol till .
		boost::char_separator<char> sep(".");
		boost::tokenizer<boost::char_separator<char>> tokens(nds, sep);
		BOOST_ASSERT_MSG(tokens.begin()!=tokens.end()," At least one symbol must be present some serious error");
	    for (const std::string& sym: tokens)
		   {
	    	 if(mTsoTransSystem->mTSONewOldSymbMap.find(sym)!=mTsoTransSystem->mTSONewOldSymbMap.end())
	    		 return mTsoTransSystem->mTSONewOldSymbMap[sym];
	    	 else
	    		 return sym;
		   }
	    BOOST_ASSERT_MSG(false,"Control should not reach here");
}

int FenceFinder::GetOldSymTid(const std::string nds)
{
	//extract first symbol till .
			boost::char_separator<char> sep(".");
			boost::tokenizer<boost::char_separator<char>> tokens(nds, sep);
			BOOST_ASSERT_MSG(tokens.begin()!=tokens.end()," At least one symbol must be present some serious error");
		    for (const std::string& sym: tokens)
			   {
		    	 if(mTsoTransSystem->mTSONewOldSymbMap.find(sym)!=mTsoTransSystem->mTSONewOldSymbMap.end())
		    	 {
		    		 std::string st=mTsoTransSystem->mTSONewOldSymbMap[sym];
		    		 BOOST_ASSERT_MSG(mTsoTransSystem->mProgram.mSymTidMap.find(st)!=mTsoTransSystem->mProgram.mSymTidMap.end()," Some seriour error");
		    		 return mTsoTransSystem->mProgram.mSymTidMap[st];
		    	 }
		    	 else{
		    		 BOOST_ASSERT_MSG(mTsoTransSystem->mProgram.mSymTidMap.find(sym)!=mTsoTransSystem->mProgram.mSymTidMap.end()," Some seriour error");
		    		 return mTsoTransSystem->mProgram.mSymTidMap[sym];
		    	 }

			   }
		    BOOST_ASSERT_MSG(false,"Control should not reach here");
}

void FenceFinder::ExtractAndFillPOLOCEdges(DGraph& polocgraph, DGraph& pograph,std::map<gvertex,gvertex> poandpolocnodemap, std::map<gvertex,std::string>& varmap)
{
	///take TClosure of pograph
	//DGraph TCpotmp1;
	boost::warshall_transitive_closure(pograph);
    //boost::transitive_closure(pograph,TCpotmp1);
    //pograph.clear();
    //boost::copy_graph
	//I wanted inplace transtive closure hence used warshall directly..

	//for all nodes of pograph
	vertex_iter vi,vi_end;
	for(tie(vi,vi_end)=boost::vertices(pograph);vi!=vi_end;++vi)
	{
		//get its successors..
		out_edge_iter ei, ei_end;
		for (tie(ei, ei_end) = boost::out_edges(*vi,pograph); ei != ei_end; ++ei)
		{
			  gvertex dest = (*ei).m_target;
			  if(varmap.find(*vi)!=varmap.end() && varmap.find(dest)!=varmap.end())//to avoid assume nodes..
			  {
				  //if nod and successor wok on same variable add an edge between their mapped nodes
				  if(varmap[*vi].compare(varmap[dest])==0){
//					  std::cout<<" Var are "<<varmap[*vi]<<","<<varmap[dest]<<std::endl;
					  boost::add_edge(poandpolocnodemap[*vi],poandpolocnodemap[dest],polocgraph);
				  }
			  }

		}
	}

}

void FenceFinder::AddInitialWWRel(DGraph& graph, std::map<std::string,gvertex>& initmap, std::map<gvertex,std::string>& wmap)
{
	//Forr all nodes of graph
	vertex_iter vi,vi_end;
	for(tie(vi,vi_end)=boost::vertices(graph);vi!=vi_end;++vi)
	{
		//get its var if in wmap
		if(wmap.find(*vi)!=wmap.end())
		{
			//get init vertex for var from initmap and add en edge in graph between two.
			if(initmap.find(wmap[*vi])!=initmap.end())
			{
				//only if both are different..
				if(initmap[wmap[*vi]]!=*vi)
					boost::add_edge(initmap[wmap[*vi]],*vi,graph);
			}
		}
	}
}


void FenceFinder::ExtractWW(DGraph& graph, std::map<gvertex,std::string>& wmap, std::map<gvertex,std::set<gvertex>>& wwrel)
{

	for(const auto& gndpair: wmap)
	{
		gvertex nd=gndpair.first;
		//get all its successor from graph..
		out_edge_iter ei, ei_end;
		tie(ei, ei_end) = boost::out_edges(nd,graph);
		for (;ei != ei_end; ++ei)
		{
		  gvertex dest = (*ei).m_target;
		  if(wmap.find(dest)!=wmap.end())
		  {
			  if(wmap[nd]==wmap[dest])
				  wwrel[nd].insert(dest);//wwrel is being passed as map hence updating in place
		  }
		}
	}
}

void FenceFinder::AddRWEdges(DGraph& graph, std::map<gvertex,gvertex>& rf, std::map<gvertex,std::set<gvertex>>& wwrel)
{
	for(const auto& gndpair: rf)
		{
			const gvertex rd=gndpair.first;//read symbol
			const gvertex wt=gndpair.second;//write symbol
			//get set of ww of wt from wwrel.
			std::set<gvertex> wws=wwrel[wt];
			for(const auto& wn: wws){
				boost::add_edge(rd,wn,graph);

			}
		}

}
void FenceFinder::SaturateGraph(DGraph& graph, std::map<gvertex,gvertex>& rf, std::map<gvertex,std::string>& wmap, std::map<gvertex,std::string>& rmap, std::vector<std::set<gvertex>>& adjlist, boost::property_map<DGraph, boost::vertex_name_t>::type& namemappo)
{

	//2 cases.. 1.if path from a read node to some write node in graph and both have same var to work upon
	//then add an edge in graph from one write to another
	//2.if path from a write to a node in graph and both have same var to work upon then add and edge in graph
	//from one write to another unless they are same.
	std::pair<vertex_iter, vertex_iter> vp;
	for (vp = boost::vertices(graph); vp.first != vp.second; ++vp.first)
	{
		gvertex nd=*vp.first;
		//Case 1.
		if(rmap.find(nd)!=rmap.end())
		{
			std::string rvar=rmap[nd];
//			out_edge_iter ei, ei_end;
			//find all outedges of node nd..
			std::set<gvertex> outgoing =   adjlist[boost::get(boost::vertex_index,graph,nd)];
			for (const auto& dest: outgoing)//tie(ei, ei_end) = boost::out_edges(nd,graph); ei != ei_end; ++ei)
			{
			  //gvertex dest = (*ei).m_target;
			  if(wmap.find(dest)!=wmap.end())//means it is a write
			  {
				 if(rvar==wmap[dest] && rf.find(nd)!=rf.end())//means same var and this read has been resolved earlier
				 {
					 if(rf[nd]!=dest){//check if no edge from dest to rf[nd]
						 boost::add_edge(rf[nd],dest,graph);//add ww edge..unless both are same node..
//						 std::cout<<"adding ww from "<<namemappo[rf[nd]]<<" to "<<namemappo[dest]<<std::endl;
					 }
				 }
			  }
			}

		}
		//Case 2

		if(wmap.find(nd)!=wmap.end())
				{
					std::string wvar=wmap[nd];
					std::set<gvertex> outgoing =   adjlist[boost::get(boost::vertex_index,graph,nd)];
					for (const auto& dest: outgoing)//tie(ei, ei_end) = boost::out_edges(nd,graph); ei != ei_end; ++ei)
					{


					  if(rmap.find(dest)!=rmap.end())//means it is a read
					  {
//						  std::cout<<"writer "<<wmap[nd]<<" has a path to read "<<rmap[dest]<<std::endl;
						 if(wvar==rmap[dest] && rf.find(dest)!=rf.end())//means same var and this read is resolved by some write
						 {
//							 std::cout<<"about to add an edge from "<<wmap[nd]<<" to writer of "<<rmap[dest]<<std::endl;
							 if(nd!=rf[dest]){//check if no edge from rf[dest] to nd
								 boost::add_edge(nd,rf[dest],graph);//add ww edge..unless both are same node..
//								 std::cout<<"adding an edge from --2--"<<namemappo[nd]<<" to "<<namemappo[rf[dest]]<<std::endl;
							 }

						 }
					  }
					}

				}


	}
}


/*
 * Now onwards we consider lcas both as read and as a write symbol
 */

bool FenceFinder::IsRead(const std::string nd)
{
	//extract first symbol till .
	boost::char_separator<char> sep(".");
		boost::tokenizer<boost::char_separator<char>> tokens(nd, sep);
//	std::cout<<" isread sym is "<<nd<<std::endl;
	BOOST_ASSERT_MSG(tokens.begin()!=tokens.end()," At least one symbol must be present some serious error");
    for (const std::string& sym: tokens)
	   {
    	if(mTsoTransSystem->mTSOProgram->mSymType.find(sym)!=mTsoTransSystem->mTSOProgram->mSymType.end())
    	{
    		if(mTsoTransSystem->mTSOProgram->mSymType[sym]=="read")
    			return true;
    		else if (mTsoTransSystem->mTSOProgram->mSymType[sym]=="lcas")
    			    	    			return true;
    		else
    			return false;
    	}
    	else
    		return false;
	   }
    BOOST_ASSERT_MSG(false,"Control should not reach here");
}

bool FenceFinder::IsWrite(const std::string nd)
{
	boost::char_separator<char> sep(".");
		boost::tokenizer<boost::char_separator<char>> tokens(nd, sep);
		BOOST_ASSERT_MSG(tokens.begin()!=tokens.end()," At least one symbol must be present some serious error");
	    for (const std::string& sym: tokens)
		   {
	    	if(mTsoTransSystem->mTSOProgram->mSymType.find(sym)!=mTsoTransSystem->mTSOProgram->mSymType.end())
	    	 {
	    	    		if(mTsoTransSystem->mTSOProgram->mSymType[sym]=="write")
	    	    			return true;
	    	    		else if (mTsoTransSystem->mTSOProgram->mSymType[sym]=="lcas")
	    	    			return true;
	    	    		else
	    	    			return false;
	    	 }
	    	else
	    		return false;
		   }
	    BOOST_ASSERT_MSG(false,"Control should not reach here");
}


bool FenceFinder::IsInitial(std::string nd)
{
	boost::char_separator<char> sep(".");
		boost::tokenizer<boost::char_separator<char>> tokens(nd, sep);
		BOOST_ASSERT_MSG(tokens.begin()!=tokens.end()," At least one symbol must be present some serious error");
	    for (const std::string& sym: tokens)
		   {
	    	if(mTsoTransSystem->mTSOProgram->mInitString.find(sym)==std::string::npos)
	    		return false;
	    	else
	    		return true;
		   }
	    BOOST_ASSERT_MSG(false,"Control should not reach here");
}

void FenceFinder::AddProgramOrderEdges(PO& poedges, DGraph& grph, std::map<std::string,boost::graph_traits<DGraph>::vertex_descriptor>& graphnodemap)
{

	//IMP: modified this code so that we add po edges only between important nodes..
	//DO: add PO edges from po--
	for(const auto& el: poedges)
	{
/*
		BOOST_ASSERT_MSG(graphnodemap.find(el.first)!=graphnodemap.end(),"Some serious error");
		BOOST_ASSERT_MSG(graphnodemap.find(el.second)!=graphnodemap.end(),"Some serious error");
*/
		if(graphnodemap.find(el.first)!=graphnodemap.end()){
			if(graphnodemap.find(el.second)!=graphnodemap.end())
				boost::add_edge(graphnodemap[el.first],graphnodemap[el.second],grph);
			else{
				//transitively look for connected one from el.second in poedges map till it is
				//present in graphnodemap.. then break and add an edge between two..
				std::string lst=el.second;
				bool notfound=false;
				while(graphnodemap.find(lst)==graphnodemap.end())
				{
					if(poedges.find(lst)==poedges.end())//means no po edge from that.. break..
					{
						notfound=true;
						break;
					}
					else
						lst=poedges[lst];
				}
				if(!notfound)
					boost::add_edge(graphnodemap[el.first],graphnodemap[lst],grph);
			}
		}

	}

}

void FenceFinder::AddRFEdges(RF& rfedges, DGraph& grph, std::map<std::string,boost::graph_traits<DGraph>::vertex_descriptor>& graphnodemap, std::map<gvertex,gvertex>& rfmap, bool isAdd)
{
	for(const auto& el: rfedges)//NOTE that rf is of type read-write.. so the edges will be from second to first
		{
			BOOST_ASSERT_MSG(graphnodemap.find(el.first)!=graphnodemap.end(),"Some serious error");
			BOOST_ASSERT_MSG(graphnodemap.find(el.second)!=graphnodemap.end(),"Some serious error");
			if(isAdd)
				boost::add_edge(graphnodemap[el.second],graphnodemap[el.first],grph);
			rfmap[graphnodemap[el.first]]=graphnodemap[el.second];
			//in graph edge is from write to read (secon to first) but rfmap keeps it in read->write form
			//hence a change in order of first and second.
		}

}

//NOTE here.. nd is also in the form of 1.2.3.4..
std::string FenceFinder::GetGVarAccessed(const std::string nd)
{
	//extract first symbol from the node..(till .)
	//from winfo find the mapped variable..
	boost::char_separator<char> sep(".");
	boost::tokenizer<boost::char_separator<char>> tokens(nd, sep);
	std::string symsingle="";
	for (const std::string& sym: tokens)
	{
		symsingle=sym;
		break;
	}

	std::string actualsym="";
	if(IsWrite(nd))
	{
		if(mTsoTransSystem->mTSONewOldSymbMap.find(symsingle)!=mTsoTransSystem->mTSONewOldSymbMap.end())
		{
			actualsym=mTsoTransSystem->mTSONewOldSymbMap[symsingle];
		}else
			actualsym=symsingle;
//		std::cout<<" Def of "<<actualsym<<" is "<<mTsoTransSystem->mProgram.GetDefVar(actualsym);
		//get def of this from program
		return mTsoTransSystem->mProgram.GetDefVar(actualsym);
	}else if(IsRead(nd))
	{
		if(mTsoTransSystem->mTSONewOldSymbMap.find(symsingle)!=mTsoTransSystem->mTSONewOldSymbMap.end())
		{
			actualsym=mTsoTransSystem->mTSONewOldSymbMap[symsingle];
		}else
			actualsym=symsingle;
		//get def of this from program
		std::set<std::string> useset=mTsoTransSystem->mProgram.GetUseVars(actualsym);
		BOOST_ASSERT_MSG(useset.size()==1," SOme serious error as this must be single read of global variable");
//		std::cout<<" Use of "<<actualsym<<" is "<<*(useset.begin())<<std::endl;
		return *(useset.begin());
	}else
		BOOST_ASSERT_MSG(false," This function must be called only when symbol is either read or write");
	//mProgram.mSymType
	//if no mapping present it means it is not a write symbol, return "" empty string.
}
