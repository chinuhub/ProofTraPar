/*
 * FenceFinder.h
 *
 *  Created on: 30-Dec-2015
 *      Author: chinmay
 */

#ifndef SRC_FENCEFINDER_FENCEFINDER_H_
#define SRC_FENCEFINDER_FENCEFINDER_H_
#include<map>
#include<set>
#include<string>
#include <boost/graph/graph_traits.hpp>
#include<boost/graph/adjacency_list.hpp>
//#include <boost/graph/topological_sort.hpp>
#include <boost/graph/transitive_closure.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>
#include "../Parser/Program.h"
#include "../TSOTransSystem/TSOTransSystem.h"
typedef std::map<std::string,std::string> PO;
//Intersting tips: If I put vertex_index_t property as int then later there is a successor function
//in transitive_closure.hpp which gives error because it assume long unsigned int..therefore I had to change the type of vertex_index_t
//to unsigned long int.
typedef boost::adjacency_list<boost::setS, boost::listS, boost::directedS, boost::property<boost::vertex_index_t, long unsigned int, boost::property<boost::vertex_name_t, std::string> > > DGraph;
typedef DGraph::vertex_descriptor gvertex;
typedef DGraph::vertex_iterator vertex_iter;
typedef DGraph::out_edge_iterator out_edge_iter;//using edge_iterator inplace of out_edge_iterator will not allow to use out_edges froma  a vertex
typedef std::map<std::string,std::string> RF;
typedef std::set<std::string> Nodes;

class FenceFinder {
	void AddRFEdges(RF& rfedges, DGraph& grph, std::map<std::string,boost::graph_traits<DGraph>::vertex_descriptor>& graphnodemap, std::map<gvertex,gvertex>&, bool);
	void AddProgramOrderEdges(PO& poedges, DGraph& grph, std::map<std::string,boost::graph_traits<DGraph>::vertex_descriptor>& graphnodemap);
	void ExtractWW(DGraph& graph, std::map<gvertex,std::string>& wmap, std::map<gvertex,std::set<gvertex>>& wwrel);
	void AddRWEdges(DGraph& graph, std::map<gvertex,gvertex>& rf, std::map<gvertex,std::set<gvertex>>& wwrel);
	void SaturateGraph(DGraph& graph, std::map<gvertex,gvertex>& rf, std::map<gvertex,std::string>& wmap, std::map<gvertex,std::string>& rmap,std::vector<std::set<gvertex>>&,boost::property_map<DGraph, boost::vertex_name_t>::type&);
	bool IsInitial(std::string nd);
	void ExtractAndFillPOLOCEdges(DGraph& polocgraph, DGraph& pograph,std::map<gvertex,gvertex> poandpolocnodemap, std::map<gvertex,std::string>& varmap);
	void AddInitialWWRel(DGraph& graph, std::map<std::string,gvertex>& initmap, std::map<gvertex,std::string>& wmap);
	std::string GetOldSym(const std::string nds);
	std::map<int,std::set<std::pair<std::string,std::string>>> GetOrderFromCriticalCycle(std::string mincycle);
	int GetOldSymTid(const std::string nds);
	TSOTransSystem* mTsoTransSystem;
	std::map<int,std::set<std::pair<std::string,std::string>>> GetCriticalCycle(DGraph& pograph, std::map<std::string,gvertex>& pographnodemap, PO& rfe,std::map<std::string, std::string>& );
public:
	FenceFinder(TSOTransSystem*);
	virtual ~FenceFinder();
	void CycleDetector(DGraph& graph);
	std::map<int,std::set<std::pair<std::string,std::string>>> OrderFinder(PO po, RF rfe, RF rfi,std::map<std::string, std::string>& );
	//This function does graph manipulation and saturation algorithm to find out a set of ww relations.
	//Validing of given RF relations comes from the fact that whether it is acyclic or not..
	void Saturate(PO&, PO&, RF& rfe, RF& rfi, Nodes& nds, std::map<std::string,std::string>&);
	bool IsRead(const std::string nd);
	bool IsWrite(const std::string nd);
	std::string GetGVarAccessed(const std::string nd);

};

#endif /* SRC_FENCEFINDER_FENCEFINDER_H_ */
