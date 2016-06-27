/* classify.cpp */

#include <classify.hpp>

/*
void classifyViaRBTNDtree(Dtree*& ndtree, vector<MR>*& mrt, list<string>*& packets, list<Result> *results)
{
	list<string>::iterator pIt, pEnd;
	pIt = packets->begin(), pEnd = packets->end();

	struct timeval startTime, endTime;
	double sec_timeOfDay;
	unsigned result;

	gettimeofday(&startTime, NULL);

	while (pIt != pEnd) {
		result = RBTDtreeSearch(ndtree, mrt, *pIt);
		Result r(*pIt, result);
		results->push_back(r);
		++pIt;
	}

	gettimeofday(&endTime, NULL);
	sec_timeOfDay = (endTime.tv_sec - startTime.tv_sec)
		               + (endTime.tv_usec - startTime.tv_usec) / 1000000.0;
	Result::setLatencyRBTNDtree(sec_timeOfDay);
}

void classifyViaRBTDtree(Dtree*& dtree, vector<MR>*& mrt, list<string>*& packets, list<Result> *results)
{
	list<string>::iterator pIt, pEnd;
	pIt = packets->begin(), pEnd = packets->end();

	struct timeval startTime, endTime;
	double sec_timeOfDay;
	unsigned result;

	gettimeofday(&startTime, NULL);

	while (pIt != pEnd) {
		result = RBTDtreeSearch(dtree, mrt, *pIt);
		Result r(*pIt, result);
		results->push_back(r);
		++pIt;
	}

	gettimeofday(&endTime, NULL);
	sec_timeOfDay = (endTime.tv_sec - startTime.tv_sec)
		               + (endTime.tv_usec - startTime.tv_usec) / 1000000.0;
	Result::setLatencyRBTDtree(sec_timeOfDay);
}

unsigned RBTDtreeSearch(Dtree *&d, vector<MR> *&mrt, string& packet)
{
	MR* mptr;
	Dtree* dptr = d;
	unsigned w = packet.length();
	unsigned result = mrt->size();

	for (unsigned t = 1; t <= w; ++t) {
		int index = -1;
		mptr = &(*mrt)[t];
		for (unsigned i = t-1; i < w; ++i) {
			//cout << "dindex: " << mptr->getDindex() << endl;
			if (-1 != mptr->getDindex()) { index = mptr->getDindex(); }
			if ('0' == packet[i]) {
				if (NULL != mptr->getLeft()) { 
					mptr = mptr->getLeft(); 
//					cout << packet[i] << endl;
				}
				else { break; }
			} else {
				if (NULL != mptr->getRight()) { 
					mptr = mptr->getRight(); 
					//cout << packet[i] << endl;
				}
				else { break; }
			}
		}
		//cout << "index: " << index << endl;
		//
		if (dptr->getNodeString() == "dummy") {
			printf("dummy\n"); break;
		}
		//
		if (-1 != mptr->getDindex()) { index = mptr->getDindex(); }
		dptr = (*(dptr->getChild()))[index];
		//cout << dptr->getNodeString() << endl;
		if (0 != dptr->getRule()) { 
			result = dptr->getRule(); 
			break; 
		}
	}

	return result;
}
*/

void classifyViaSimpleSearch(vector<RBT>*& rbt, unsigned& n, list<string>*& packets, list<Result>* results)
{
	list<string>::iterator pIt, pEnd;
	pIt = packets->begin(), pEnd = packets->end();

	struct timeval startTime, endTime;
	double sec_timeOfDay;
	unsigned result;
	vector<unsigned> *A = new vector<unsigned>;
	for (unsigned i = 0; i <=n ; ++i) { A->push_back(0); }

	gettimeofday(&startTime, NULL);

	while (pIt != pEnd) {
		for (unsigned i = 0; i <=n ; ++i) { (*A)[i] = 0; }
		result = simpleSearch(rbt, A, *pIt, n);
		Result r(*pIt, result);
		results->push_back(r);
		++pIt;
	}

	gettimeofday(&endTime, NULL);
	sec_timeOfDay = (endTime.tv_sec - startTime.tv_sec)
		               + (endTime.tv_usec - startTime.tv_usec) / 1000000.0;
	Result::setLatencySimpleSearch(sec_timeOfDay);
}

unsigned simpleSearch(vector<RBT>*& rbt, vector<unsigned> *A, string& packet, unsigned n)
{
	RBT* ptr;
	unsigned w = packet.length();
	unsigned match = n+1;
	list<Run>::iterator runIt, runItEnd;

	for (unsigned t = 1; t <= w; ++t) {
		ptr = &(*rbt)[t];
		for (unsigned i = t-1; i < w; ++i) {
			if ('0' == packet[i])
				if (NULL != ptr->getLeft()) { ptr = ptr->getLeft(); }
				else { break; }
			else 
				if (NULL != ptr->getRight()) { ptr = ptr->getRight(); }
				else { break; }
			if (NULL != ptr->getRun()) {
				runIt = ptr->getRun()->begin(), runItEnd = ptr->getRun()->end();
				while (runIt != runItEnd) {
					unsigned j = runIt->getRuleNumber();
					unsigned k = runIt->getRunNumber();
					if (k-1 == (*A)[j]) {
						(*A)[j] = k;
						if (runIt->isTerminal())
							if (j < match) { match = j; }
					}
					++runIt;
				}
			}
		}
	}

	return match;
}

void classifyViaSequentialSearch(list<Rule>*& rulelist, list<string>*& packets, list<Result>* results)
{
	list<string>::iterator pIt, pEnd;
	pIt = packets->begin(), pEnd = packets->end();

	struct timeval startTime, endTime;
	double sec_timeOfDay;
	unsigned result;

	gettimeofday(&startTime, NULL);

	while (pIt != pEnd) {
		result = sequentialSearch(rulelist, *pIt);
		Result r(*pIt, result);
		results->push_back(r);
		++pIt;
	}

	gettimeofday(&endTime, NULL);
	sec_timeOfDay = (endTime.tv_sec - startTime.tv_sec)
		               + (endTime.tv_usec - startTime.tv_usec) / 1000000.0;
	Result::setLatencySequential(sec_timeOfDay);
}

bool compareRuleAndPacket(Rule& rule, string& packet)
{
	string ruleBitString = rule.getRuleBitString();
	unsigned l = ruleBitString.size();
	unsigned i = 0;
	while (i < l) {
		if (ruleBitString[i] != '*' && ruleBitString[i] != packet[i])
			return false;
		++i;
	}
	return true;
}

unsigned sequentialSearch(list<Rule>*& rulelist, string& packet)
{
	list<Rule>::iterator ruleIt = rulelist->begin();
	list<Rule>::iterator ruleItEnd = rulelist->end();

	while (ruleIt != ruleItEnd) {
		if (compareRuleAndPacket(*ruleIt, packet))
			return ruleIt->getRuleNumber();
		++ruleIt;
	}
	
	return rulelist->size()+1;
}
