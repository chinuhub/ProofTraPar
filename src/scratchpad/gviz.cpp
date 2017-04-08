#include <boost/graph/graphviz.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/test/minimal.hpp>
#include <string>
#include <fstream>
#include <boost/graph/iteration_macros.hpp>
using namespace boost;

typedef boost::adjacency_list<vecS, vecS, directedS,
                              property<vertex_name_t, std::string>,
                              property<edge_weight_t, std::string>
			 > Digraph;

typedef boost::adjacency_list<vecS, vecS, undirectedS,
                              property<vertex_name_t, std::string>,
                              property<edge_weight_t, double> > Graph;

int test_main(int c, char** argv)
{
std::string filename="12.dot";
  std::ifstream in(filename.c_str());
  BOOST_REQUIRE(in);

  Digraph g;
  dynamic_properties dp(boost::ignore_other_properties);
  dp.property("label", get(vertex_name, g));
//  dp.property("fixedsize", get(fix_name, g));
//  dp.property("regular", get(reg_name, g));
  dp.property("label", get(edge_weight, g));
  read_graphviz(in, g, dp, "label");


  
//  typedef graph_traits<Digraph>::vertex_descriptor Vertex;

 // std::map<std::string, Vertex> name_to_vertex;
  BGL_FORALL_VERTICES(v, g, Digraph){ 
    std::cout<<"Name is "<<get(vertex_name, g, v)<<std::endl;
	BGL_FORALL_OUTEDGES_T(v, en, g, Digraph){
	std::string evn=get(edge_weight,g,en);
	//extract till :
	std::string mod = evn.substr(0,evn.find_first_of(":"));
		std::cout<<"Connected to "<<get(vertex_name,g,(en).m_target)<<" with label as "<<get(edge_weight,g,en)<<" and "<<mod<<std::endl;
	} 
     }


}


