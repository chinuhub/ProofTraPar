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
typedef std::map<std::string,std::string> PO;
typedef std::map<std::string,std::string> RF;
typedef std::set<std::string> Nodes;
class FenceFinder {
public:
	FenceFinder();
	virtual ~FenceFinder();

	//This function does graph manipulation and saturation algorithm to find out a set of ww relations.
	//Validing of given RF relations comes from the fact that whether it is acyclic or not..
	void Saturate(PO&, RF& rfe, RF& rfi, Nodes& nds);

};

#endif /* SRC_FENCEFINDER_FENCEFINDER_H_ */
