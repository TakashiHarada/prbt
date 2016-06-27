/* classify.hpp */

#ifndef __CLASIFICATION_CLASSIFY_HPP__
#define __CLASIFICATION_CLASSIFY_HPP__

#ifndef __CLASIFICATION_OPENFILE_HPP__
#include <openfile.hpp>
#endif

#ifndef __CLASIFICATION_RBT_HPP__
#include <rbt.hpp>
#endif

#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

class Result {
	private:
		static double _latency_of_sequential;
		static double _latency_of_simpleSearch;
		static double _latency_of_RBTDtreeSearch;
		static double _latency_of_RBTNDtreeSearch;
		static double _construct_time_of_naive_dtree;
		static double _construct_time_of_dtree;
		string _packet;
		unsigned _retVal;
	public:
		Result(string p, unsigned v) { _packet = p, _retVal = v; }
		string getPacket() { return _packet; }
		unsigned getValue() { return _retVal; }
		static void setLatencySequential(double t) { _latency_of_sequential = t; }
		static void setLatencySimpleSearch(double t) { _latency_of_simpleSearch = t; }
		static void setLatencyRBTDtree(double t) { _latency_of_RBTDtreeSearch = t; }
		static void setLatencyRBTNDtree(double t) { _latency_of_RBTNDtreeSearch = t; }
		static void setConstructTimeOfRBTDtree(double t) { _construct_time_of_dtree = t; }
		static void setConstructTimeOfRBTNDtree(double t) { _construct_time_of_naive_dtree = t; }
		static double getLatencySequential() { return _latency_of_sequential; }
		static double getLatencySimpleSearch() { return _latency_of_simpleSearch; }
		static double getLatencyRBTDtree() { return _latency_of_RBTDtreeSearch; }
		static double getLatencyRBTNDtree() { return _latency_of_RBTNDtreeSearch; }
		static double getConstructTimeOfRBTDtree() { return _construct_time_of_dtree; }
		static double getConstructTimeOfRBTNDtree() { return _construct_time_of_naive_dtree; }
};


//void classifyViaRBTNDtree(Dtree*&, vector<MR>*&, list<string>*&, list<Result> *);
//void classifyViaRBTDtree(Dtree*&, vector<MR>*&, list<string>*&, list<Result> *);
void classifyViaSimpleSearch(vector<RBT>*&, unsigned&, list<string>*&, list<Result> *);
void classifyViaSequentialSearch(list<Rule>*&, list<string>*&, list<Result> *);
//unsigned RBTDtreeSearch(Dtree *&, vector<MR> *&, string &);
unsigned simpleSearch(vector<RBT> *&, vector<unsigned>*, string&, unsigned);
bool compareRuleAndPacket(Rule&, string&);
unsigned sequentialSearch(list<Rule> *&, string&);

#endif
