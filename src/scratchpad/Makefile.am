bin_PROGRAMS=ProofTraPar
a_out_SOURCES=ProofTraPar.cpp Parser/Program.cpp Parser/Process.cpp SCTransSystem/SCTransSystem.cpp AFA/AFAut.cpp Parser/QiParser.cpp AFA/AFAState.cpp AFA/PassTwo.cpp AFA/PassThree.cpp AFA/PassFourWeak.cpp AFA/PassFourAFA.cpp TSOTransSystem/TSOState.cpp TSOTransSystem/TSOTransSystem.cpp FenceFinder/FenceFinder.cpp RMMInterface.cpp
AUTOMAKE_OPTIONS=subdir-objects
AM_LDFLAGS = -L../extlib/boost_1_58_0/stage/lib   -L../extlib/z3-master/build -L../extlib/libfaudes-2_26g
AM_CPPFLAGS=-I../extlib/boost_1_58_0 -I../extlib/z3-master/src/api -I../extlib/libfaudes-2_26g/include
AM_CXXFLAGS = -std=c++11  
#-DDBGPRNT   
#LIBS = -lboost_regex -lfa -lboost_chrono -lboost_system -lz3
LIBS = -lz3 -Bstatic -l:libboost_regex.a -l:libboost_chrono.a -l:libboost_system.a -l:libboost_graph.a -l:libfaudes.a -lpthread
