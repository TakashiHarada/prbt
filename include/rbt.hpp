/* rbt.hpp */

#ifndef __CLASIFICATION_RBT_HPP__
#define __CLASIFICATION_RBT_HPP__

#ifndef __CLASIFICATION_OPENFILE_HPP__
#include <openfile.hpp>
#endif

#include <vector>
#include <cmath>
#include <algorithm>

class Run {
	private:
		string _bitString;
		unsigned _runNumber;
		unsigned _ruleNumber;
		bool _terminal;
	public:
		Run() { }
		Run(string bitString, unsigned runNumber, unsigned ruleNumber) {
			_bitString = bitString;
			_runNumber = runNumber;
			_ruleNumber = ruleNumber;
			_terminal = false;
		}
		~Run() { /* printf("call the Run deconstructor.\n"); */ }
		string getBitString() { return _bitString; }
		unsigned getRunNumber() { return _runNumber; }
		unsigned getRuleNumber() { return _ruleNumber; }
		bool isTerminal() { return _terminal; }
		void setTerminalTrue() { _terminal = true; }
};	

class RBT {
	protected:
		static long unsigned _number_of_node_of_rbt;
		char _nodeBit;
		string _nodeString;
		unsigned _trieNumber;
		RBT* _left;
		RBT* _right;
		list<Run>* _runlist;
	public:
		RBT() { }
		RBT(char nodeBit, unsigned trieNumber, string nodeString) {
			_nodeBit = nodeBit;
			_nodeString = nodeString;
			_trieNumber = trieNumber;
			_left = NULL;
			_right = NULL;
			_runlist = NULL;
		}
		~RBT() { /* printf("call a RBT deconstructor.\n"); */ }
		static void showNumberOfNodeOfRBT() { cout << _number_of_node_of_rbt << endl; }
		char getNodeBit() { return _nodeBit; }
		string getNodeString() { return _nodeString; }
		unsigned getTrieNumber() { return _trieNumber; }
		RBT* getLeft() { return _left; }
		RBT* getRight() { return _right; }
		list<Run>* getRun() { return _runlist; }
		void setLeft(RBT* left) { _left = left; }
		void setRight(RBT* right) { _right = right; }
		void setRun(Run r) {
			if (NULL == _runlist) { _runlist = new list<Run>; }
			_runlist->push_back(r);
		}
};

/* for constructing a Run-Based Trie */
class RunPair {
	private:
		unsigned _startBit;
		Run _run;
	public:
		RunPair() { }
		RunPair(unsigned startBit, Run run) {
			_startBit = startBit;
			_run = run;
		}
		~RunPair() { /* printf("call a RunPair deconstructor.\n"); */ }
		unsigned getStartBit() { return _startBit; }
		Run getRun() { return _run; }
};

/* pointed Run-Based Trie */
class PRBT : public RBT {
	private:
		static long unsigned _number_of_node_of_prbt;
		/*
		char _nodeBit;
		string _nodeString;
		unsigned _trieNumber;
		PRBT* _left;
		PRBT* _right;
		list<Run>* _runlist;
		*/
	public:
		PRBT() { }
		PRBT(char nodeBit, unsigned trieNumber, string nodeString) {
			_nodeBit = nodeBit;
			_nodeString = nodeString;
			_trieNumber = trieNumber;
			_left = NULL;
			_right = NULL;
			_runlist = NULL;
		}
		~PRBT() { /* printf("call a PRBT deconstructor.\n"); */ }
		static void showNumberOfNodeOfPRBT() { cout << _number_of_node_of_prbt << endl; }
		/*
		char getNodeBit() { return _nodeBit; }
		string getNodeString() { return _nodeString; }
		unsigned getTrieNumber() { return _trieNumber; }
		PRBT* getLeft() { return _left; }
		PRBT* getRight() { return _right; }
		list<Run>* getRun() { return _runlist; }
		void setLeft(PRBT* left) { _left = left; }
		void setRight(PRBT* right) { _right = right; }
		void setRun(Run r) {
			if (NULL == _runlist) { _runlist = new list<Run>; }
			_runlist->push_back(r);
		}
		*/
};

/* Match Run Set Trie */
class MR {
	private:
		static long unsigned _number_of_node_of_mr;
		static long unsigned _counterForDIndex;
		static vector<long unsigned> *_maxDIndex;
		char _nodeBit;
		string _nodeString;
		long _dIndex;           /* an index for a Decision Tree Search */
		unsigned _trieNumber;
		//////////////////////////////////////////////////////////////////////
		unsigned long long _weight;
		bool _needNode;
		bool _forDeleteSign;
		//////////////////////////////////////////////////////////////////////
		MR* _parent;
		MR* _left;
		MR* _right;
		list<Run>* _runlist;
		string _safeNodeString;         /* for pruning the Decision Tree */
		MR* _safeLeft;                  /* for pruning the Decision Tree */
		MR* _safeRight;                 /* for pruning the Decision Tree */
		//////////////////////////////////////////////////////////////////////
		unsigned long long _safeWeight; /* for pruning the Decision Tree */
		bool _safeNeedNode;
		//////////////////////////////////////////////////////////////////////
		list<string>* _mrlist;          /* for pruning the Decision Tree */
	public:
		MR() { }
		MR(char b) {
			_nodeBit = b;
			_nodeString = "";
			_dIndex = -1;
			_trieNumber = 0;
			//////////////////////////////////////////////////////////////////////
			_weight = 0;
			_needNode = false;
			_forDeleteSign = false;
			//////////////////////////////////////////////////////////////////////
			_parent = NULL;
			_left = NULL;
			_right = NULL;
			_runlist = NULL;
			_mrlist = NULL;
			_safeNodeString = "";
			_safeLeft = NULL;
			_safeRight = NULL;
			//////////////////////////////////////////////////////////////////////
			_safeWeight = 0;
			_safeNeedNode = false;
			//////////////////////////////////////////////////////////////////////
		}
		MR(char b, int tn) {
			_nodeBit = b;
			_nodeString = "";
			_dIndex = -1;
			_trieNumber = tn;
			//////////////////////////////////////////////////////////////////////
			_weight = 0;
			_needNode = false;
			_forDeleteSign = false;
			//////////////////////////////////////////////////////////////////////
			_weight = 0;
			_parent = NULL;
			_left = NULL;
			_right = NULL;
			_runlist = NULL;
			_mrlist = NULL;
			_safeNodeString = "";
			_safeLeft = NULL;
			_safeRight = NULL;
			//////////////////////////////////////////////////////////////////////
			_safeWeight = 0;
			_safeNeedNode = false;
			//////////////////////////////////////////////////////////////////////
		}
		MR(char nodeBit, unsigned trieNumber, string nodeString, MR* p) {
			_nodeBit = nodeBit;
			_nodeString = nodeString;
			_dIndex = -1;
			_trieNumber = trieNumber;
			//////////////////////////////////////////////////////////////////////
			_weight = 0;
			_needNode = false;
			_forDeleteSign = false;
			//////////////////////////////////////////////////////////////////////
			_weight = 0;
			_parent = p;
			_left = NULL;
			_right = NULL;
			_runlist = NULL;
			_mrlist = NULL;
			_safeNodeString = "";
			_safeLeft = NULL;
			_safeRight = NULL;
			_safeWeight = 0;
			_safeNeedNode = false;
			//////////////////////////////////////////////////////////////////////
		}
		~MR() { /* printf("call a MR deconstructor.\n"); */ }
		static void showNumberOfNodeOfMRT() { cout << _number_of_node_of_mr << endl; }
		static void initDIndex() { _counterForDIndex = 0; }
		static void incDIndex() { ++_counterForDIndex; }
		static void decDIndex() { --_counterForDIndex; }
		static long unsigned getCounterForDIndex() { return _counterForDIndex; }
		static void setMaxDIndex(long unsigned n) {
			if (NULL == _maxDIndex) { _maxDIndex = new vector<long unsigned>; }
			_maxDIndex->push_back(n);
		}
		static long unsigned getMaxDIndex(unsigned i) { return (*_maxDIndex)[i]; }
		char getNodeBit() { return _nodeBit; }
		string getNodeString() { return _nodeString; }
		long getDindex() { return _dIndex; }
		unsigned getTrieNumber() { return _trieNumber; }
		//////////////////////////////////////////////////////////////////////
		unsigned long long getWeight() { return _weight; }
		bool isNeeded() { return _needNode; }
		bool getDeleteSign() { return _forDeleteSign; }
		//////////////////////////////////////////////////////////////////////
		MR* getParent() { return _parent; }
		MR* getLeft() { return _left; }
		MR* getRight() { return _right; }
		list<Run>* getRun() { return _runlist; }
		list<string>* getMRInfo() { return _mrlist; }
		MR* getSafeLeft() { return _safeLeft; }
		MR* getSafeRight() { return _safeRight; }
		unsigned long long getSafeWeight() { return _safeWeight; }
		bool getSafeNeedNode() { return _safeNeedNode; }
		//////////////////////////////////////////////////////////////////////
		void setWeight(unsigned long long w) { _weight = w; }
		void setNeedNode(bool b) { _needNode = b; }
		void setDeleteSign(bool b) { _forDeleteSign = b; }
		//////////////////////////////////////////////////////////////////////
		void setLeft(MR* left) { _left = left; }
		void setRight(MR* right) { _right = right; }
		void setRun(Run r) {
			if (NULL == _runlist) { _runlist = new list<Run>; }
			_runlist->push_back(r);
		}
		void setMRInfo(string s) {
			if (NULL == _mrlist) { _mrlist = new list<string>; }
			_mrlist->push_back(s);
		}
		void subtractWeight(unsigned long long m) { _weight -= m; }
		void deleteRun() { 
			if (NULL != _runlist) { delete _runlist, _runlist = NULL; }
		}
		void deleteMRInfo() {
			if (NULL != _mrlist) {delete _mrlist, _mrlist = NULL; }
		}
		void changeNodeString(string s) { _nodeString = s; }
		void setSafeLeft(MR* l) { _safeLeft = l; }
		void setSafeRight(MR* r) { _safeRight = r; }
		void setSafeWeight(unsigned long long w) { _safeWeight = w; }
		void setSafeNeedNode(bool b) { _safeNeedNode = b; }
		void setDIndex(long n) { _dIndex = n; }
};

class Dtree {
	private:
		static unsigned long _number_of_node_of_dtree;
		long _nindexed;
		unsigned _Rule;
		vector<Dtree*>* _children;
		bool _offspring;
		string _nodeString;
		list<Run>* _runlist;
		list<string>* _mrlist;
	public:
		Dtree() { }
		Dtree(string s) {
			++_number_of_node_of_dtree;
			_nindexed = -1;
			_Rule = 0;
			_children = NULL;
			_offspring = false;
			_nodeString = s;
			_runlist = NULL;
			_mrlist = NULL;
		}
		Dtree(string s, list<Run>* ri, list<string>* si, long ni) {
			++_number_of_node_of_dtree;
			_nindexed = ni;
			_Rule = 0;
			_nodeString = s;
			_offspring = false;
			if (NULL != si) {
				_mrlist = new list<string>;
				list<string>::iterator it, itEnd;
				it = si->begin(), itEnd = si->end();
				while (it != itEnd) {
					_mrlist->push_back(*it);
					++it;
				}
			} else { _mrlist = NULL; }
			if (NULL != ri) {
				_runlist = new list<Run>;
				list<Run>::iterator it, itEnd;
				it = ri->begin(), itEnd = ri->end();
				while (it != itEnd) {
					_runlist->push_back(*it);
					++it;
				}
			} else { _runlist = NULL; }
			_children = NULL;
		}
		Dtree(const Dtree& d) {
			_nindexed = d._nindexed;
			_Rule = d._Rule;
			_nodeString = d._nodeString;
			_runlist = d._runlist;
			_children = d._children;
			_offspring = d._offspring;
		}
		~Dtree() { /* printf("call the Dtree deconstructor.\n"); */ }
		static void initNumberOfNodeOfDtree() { _number_of_node_of_dtree = 0; }
		static void showNumberOfNodeOfDtree() { cout << _number_of_node_of_dtree << endl;}
		static void decNumberOfDtree() { --_number_of_node_of_dtree; }
		static void minusNumberOfDtree(long n) { _number_of_node_of_dtree -= n; }
		long getNindex() { return _nindexed; }
		string getNodeString() { return _nodeString; }
		list<Run>* getRun() { return _runlist; }
		list<string>* getMRS() { return _mrlist; }
		unsigned getNumberOfChild() {
			if (NULL != _children) { return _children->size(); }
			else { return 0; }
		}
		vector<Dtree*>* getChild() { return _children; }
		unsigned getRule() { return _Rule; }	
		void addRun(Run r) {
			if (NULL == _runlist) { _runlist = new list<Run>; }
			_runlist->push_back(r);
		}
		void addMRS(string s) {
			if (NULL == _mrlist) { _mrlist = new list<string>; }
			_mrlist->push_back(s);
		}
		void modifyString(string s) { _nodeString = &s[1]; }
		void setChild(Dtree* c) {
			if (NULL == _children) { _children = new vector<Dtree*>; }
			_children->push_back(c);
		}
		void setRule(unsigned r) { _Rule = r; }
		void setMRS(list<string>* sl) {
			if (NULL != sl) {
				_mrlist = new list<string>;
				list<string>::iterator it, end;
				it = sl->begin(), end = sl->end();
				while (it != end) {
					_mrlist->push_back(*it);
					++it;
				}
			} else { _mrlist = NULL; }
		}
		void deleteMRS() {
			if (NULL != _mrlist) { delete _mrlist; }
			_mrlist = NULL;
		}
		void deleteRun() {
			if (NULL != _runlist) { delete _runlist; }
			_runlist = NULL;
		}
		void deleteChild() {
			if (NULL != _children) { delete _children; }
			_children = NULL;
		}
};



void makePointedRunBasedTrie(vector<RBT>*&, vector<PRBT>*, list<Rule>*&);

/*
void settingNIndex(Dtree*, Dtree*);
bool isNoChild(Dtree*);
void cutChildNode(Dtree*);
void checkChildNode(Dtree*);
void addRuleToLeaf(Dtree*);
void traverseMRTforRevert(MR*, string);
void revertMRS(MR*, Dtree*);
void checkSafePointer(MR*);
void revertWptr(MR*, Dtree*);
void revert(MR*, Dtree*);
MR* setPivotNode(MR*);
void modifyLeftDummyPointer(MR*);
void modifyRightDummyPointer(MR*);
MR* modifyWptr(MR*, Dtree*);
void modifySafeWeight(MR*);
MR* traverseMRT(MR*, string);
void modifyMRT(MR*, Dtree*);
void cutMRSFirstBit(Dtree*);
string compSameBit(string, string);
void spanMaskForPhi(Dtree*);
void deleteDuplicatingElements(Dtree*);
void inheritMRS(Dtree *, list<string>*);
void inheritRun(Dtree *, list<Run>*);
Dtree* makeDtreeNode(MR*, Dtree*);
void traverseMRforNaiveDtree(MR*, Dtree*, vector<MR>*);
void traverseMRforDtree(MR*, Dtree*, vector<MR>*);
void constructNaiveDtree(Dtree*, vector<MR>*);
void constructDtree(Dtree*, vector<MR>*);
void addDIndex(MR*);
void settingDIndex(vector<MR>*);
void addMRTInfo(MR*);
void MRTInfoTraverse(MR*);
void settingMRInfo(vector<MR>*);
void moveRun(MR*, MR*);
void updateMRT(MR*, MR*, char);
bool noMRS(MR*);
void changeMRSet(MR*);
void changeAllMRSet(vector<MR>*);
void walkToRoot(MR*);
void MRTWeightTraverse(MR*);
void allMRTWeightTraverse(vector<MR>*);
void traverseAndMakeMRTNode(RBT *, MR *, unsigned&, unsigned&);
void traverseAndMakeMRTNode(RBT*, MR*, unsigned&);
void copyRBTtoMRT(vector<RBT>*&, vector<MR>*);
void createTheMRTRootNodes(vector<MR>*, unsigned);
void makeMatchRunSetTrie(vector<RBT>*&, vector<MR>*);
*/
template <class T> void traverseAndMakeRBTNode(T*, Run);
list<RunPair>* cutOutRun(Rule);
template <class T> void createTheRBTRootNodes(vector<T>*, unsigned);
template <class T> void makeRunBasedTrie(list<Rule>*&, vector<T> *);
template <class T> void postTraverse(T*);
//void postTraverse(MR*);
//void showChild(Dtree *);

#endif
