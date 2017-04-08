#include "TSOState.h"
#include <string>

bool operator <(const TSOState& one, const TSOState&  two){
	if(one.mBuffBound==two.mBuffBound)
		if(one.mNumThreads==two.mNumThreads)
			if(one.mEndingWith == two.mEndingWith)
				if(one.mBufferMap==two.mBufferMap)
					if(one.mCStatesMap==two.mCStatesMap)
						if(one.mLastInstanceMap==two.mLastInstanceMap)
							return one.mTransSym<two.mTransSym;
						else
							return one.mLastInstanceMap<two.mLastInstanceMap;
					else
						return one.mCStatesMap<two.mCStatesMap;
				else
					return one.mBufferMap<two.mBufferMap;
			else
				return one.mEndingWith < two.mEndingWith;
			else
				return one.mNumThreads<two.mNumThreads;
		else
			return one.mBuffBound<two.mBuffBound;

}

TSOState::TSOState(const TSOState& src){
	this->mBufferMap = src.mBufferMap;
	this->mCStatesMap = src.mCStatesMap;
	this->mLastInstanceMap = src.mLastInstanceMap;
	this->mBuffBound = src.mBuffBound;
	this->mNumThreads = src.mNumThreads;
	this->mTransSym=src.mTransSym;
	this->mEndingWith = src.mEndingWith;
}

TSOState::TSOState(int buffbound,int numthreads){
	mBuffBound = buffbound;
	mNumThreads = numthreads;
	mEndingWith="";
	std::map<std::string, int> limap;

	for(int i=1; i<=numthreads; i++){
		WriteBuffer buff(buffbound);
		mBufferMap[i]=buff;
		mLastInstanceMap[i]=limap;
		mTransSym[i]="0";//some initialization
	}
	//Note that we are keeping containers by value.. it might be a good idea ot keep them as pointer
	//so that we do in place update without making any temporary copy..
	//In that case, copy constructor above must create new objects when copying stuff..
}
/**
 * Returns true if buffer is empty else returns false.
 */
bool TSOState::isBuffEmpty(int tid) const{
	BOOST_ASSERT_MSG(mBufferMap.find(tid)!=mBufferMap.end(),"Some serious error happend");
	return mBufferMap.find(tid)->second.empty();
	//herer mBufferMap[tid].empty did not work because of const nature of this function.
}

/**
 * Returns true if buffer is full else returns false.
 */
bool TSOState::isBuffFull(int tid) const{
	BOOST_ASSERT_MSG(mBufferMap.find(tid)!=mBufferMap.end(),"Some serious error happend");
	return mBufferMap.find(tid)->second.full();
}

/*
 * Getter and Setter for local variable var in LI map of thread tid
 */
int TSOState::getLastIndex(int tid, std::string& var) const
{
	BOOST_ASSERT_MSG(mLastInstanceMap.find(tid)!=mLastInstanceMap.end(),"Some serious error happeend");
	if(mLastInstanceMap.find(tid)->second.find(var)==mLastInstanceMap.find(tid)->second.end())
	{
		//means this is the first instance being used for this.. so add to map and set to 0(or 1.. check it).
		//mLastInstanceMap[tid][var]=0;
		return -1;
	}
	else
	{
		return mLastInstanceMap.find(tid)->second.find(var)->second;
		//again, using mLastInstanceMap[tid][var] was giving compilation error due to const nature of this function
	}
}

/*
 * Reset all instance indices to 0 for a particular thread id.
 */

void TSOState::initAllIndex(int tid)
{
	std::map<std::string,int> newmap;
	for(auto t: mLastInstanceMap[tid]){
		newmap[t.first]=0;
	}
	mLastInstanceMap[tid]=newmap;
}


void TSOState::setLastIndex(int tid, std::string& var, int index)
{
	BOOST_ASSERT_MSG(mLastInstanceMap.find(tid)!=mLastInstanceMap.end(),"Some serious error happened");
	mLastInstanceMap[tid][var]=index;
	//even if it is the first instance of var, indexed access adds the entry if needed.
}

/*
 * Remove the first entry from the buffer (by increasing buff pointers
 * and return the symbol.. return NULL if buf is empty for this process
 */
std::string TSOState::flushBuf(int tid)
{
	if(mBufferMap[tid].empty())
		return NULL;
	else
		{
		std::string tmp = *(mBufferMap[tid].begin());
		mBufferMap[tid].pop_front();
		return tmp;
		}
}

/*
 * Add a symbol to the buffer, assert failure if buffer is full.
 */
void TSOState::enqueToBuffer(int tid, std::string sym)
{
	BOOST_ASSERT_MSG(!mBufferMap[tid].full(),"Buffer is full, this must be checked before calling this function, look into this");
	mBufferMap[tid].push_back(sym);

}


/*
 * getControlState for a process tid
 */
faudes::Idx TSOState::getCState(int tid) const
{
	BOOST_ASSERT_MSG(mCStatesMap.find(tid)!=mCStatesMap.end(),"Some serious error, for each process we should have its control state, look into this ");
	return mCStatesMap.find(tid)->second;
}

/*
 * setControlState for a process tid
 */
void TSOState::setCState(int tid, faudes::Idx newone)
{
//	BOOST_ASSERT_MSG(mCStatesMap.find(tid)!=mCStatesMap.end(),"Some serious error, for each process we should have its control state, look into this ");
	mCStatesMap[tid]=newone;
}

void TSOState::setTransSym(int tid,std::string sym){
	mTransSym[tid]=sym;
}

std::string TSOState::getTransSym(int tid) const {
	return mTransSym.find(tid)->second;
}

