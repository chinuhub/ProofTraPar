/*
 * TSOState.h
 *
 *  Created on: 21-Dec-2015
 *      Author: jaganmohini
 */

#ifndef TSOSTATE_H_
#define TSOSTATE_H_
#include <libfaudes.h>//WHY this ordering was important.. If I put it after c++/z3++ then lots of error..
#include "../Parser/Program.h"
#include <vector>
#include <boost/circular_buffer.hpp>

typedef int BuffPtr;
typedef boost::circular_buffer<std::string> WriteBuffer;
typedef int ThdId;
class TSOState{
	std::map<ThdId, std::map<std::string,int>> mLastInstanceMap;
	std::map<ThdId, struct autstate*> mCStatesMap;

	int mNumThreads;
	std::map<ThdId,std::string> mTransSym;
	const TSOState& operator=( const TSOState& );
public:
	TSOState(int buffbound, int numthreads);
	TSOState(const TSOState& src); //IMP issue here: Always put const if you are explicitly making
	//a copy constructor.. otherwise instantiation of pair (stl) was giving a very obstruse error which
	//was difficult to find out..
	int mBuffBound;
	std::map<ThdId, WriteBuffer> mBufferMap;

	/**
	 * Returns true if buffer is empty else returns false.
	 */
	bool isBuffEmpty(ThdId tid) const;

	/**
	 * Returns true if buffer is full else returns false.
	*/
	bool isBuffFull(ThdId tid) const;

	/*
	 * Getter and Setter for local variable var in LI map of thread tid
	 */
	int getLastIndex(ThdId tid, std::string& var) const;
	void setLastIndex(ThdId tid, std::string& var, int index);
	void initAllIndex(ThdId tid);
	/*
	 * Remove the first entry from the buffer (by increasing buff pointers
	 * and return the symbol.. return NULL if buf is empty for this process
	 */
	std::string flushBuf(ThdId tid);
	/*
	 * Add a symbol to the buffer, assert failure if buffer is full.
	 */
	void enqueToBuffer(ThdId tid, std::string sym);


	/*
	 * getControlState for a process tid
	 */
	struct autstate* getCState(ThdId tid) const;

	/*
	 * setControlState for a process tid
	 */
	void setCState(ThdId tid, struct autstate*);

	void setTransSym(ThdId tid,std::string sym);
	std::string getTransSym(ThdId tid) const;

	friend bool operator <(const TSOState& one, const TSOState&  two);//IMP: This is the way to make
	//a class comparable.. pair needed this hence was done..

};

typedef std::pair<std::set<std::string>, TSOState> SymStatePair;

#endif
