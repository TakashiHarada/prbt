/* rbt.cpp */

#include <rbt.hpp>

template <class T>
void makePointedRunBasedTrie(vector<T>*& rbt, vector<T>* prbt, list<Rule>*& rulelist)
{
	;
}

/*
void settingNIndex(Dtree* d, Dtree* dummy)
{
	if (NULL != d->getChild()) {
		vector<Dtree*>::iterator it = d->getChild()->begin();
		unsigned i = 0, max = 0;
		while (i < d->getNumberOfChild()) {
			if ((*(d->getChild()))[i]->getNindex() > i) {
				d->getChild()->insert(it, (*(d->getChild()))[i]->getNindex()-max, dummy);
				it = d->getChild()->begin();
				for (unsigned k = 0; k < i; ++k) { ++it; }
			}
			if ("dummy" != (*(d->getChild()))[i]->getNodeString()) {
				max = (*(d->getChild()))[i]->getNindex()+1;
			}
			settingNIndex((*(d->getChild()))[i], dummy);
			++i;
			++it;
		}
	}
}

bool isNoChild(Dtree *n)
{
	if (0 == n->getNumberOfChild() && 0 == n->getRule()) { 
		Dtree::decNumberOfDtree();
		return true;
	}
	return false;
}

void cutChildNode(Dtree* n)
{
	n->setRule((*(n->getChild()))[0]->getRule());
	Dtree::minusNumberOfDtree(n->getNumberOfChild());
	n->deleteChild();
}

void checkChildNode(Dtree *d)
{
	if (0 == d->getNumberOfChild()) { return ; }
	else if (1 == d->getNumberOfChild()) {
		if (0 != (*(d->getChild()))[0]->getRule()) { cutChildNode(d); }
		else {
			if (0 == (*(d->getChild()))[0]->getNumberOfChild()) { cutChildNode(d); }
			return ;
		}
	} else {
		d->getChild()->erase(
				remove_if(d->getChild()->begin(), d->getChild()->end(), isNoChild), d->getChild()->end());
		if (0 == (*(d->getChild()))[0]->getRule()) { return ; }
		unsigned x = (*(d->getChild()))[0]->getRule();
		for (unsigned i = 1; i < d->getNumberOfChild(); ++i)
			if ((*(d->getChild()))[i]->getRule() != x)
				return ;
		cutChildNode(d);
	}
}

void addRuleToLeaf(Dtree *n)
{
	unsigned defaultRule = Rule::getNumberOfRule();
	unsigned priority = defaultRule+1;
	
	if (NULL != n->getRun()) {
		vector<unsigned> A;
		for (unsigned i = 0; i <= defaultRule; ++i) { A.push_back(0); }
		list<Run>::reverse_iterator rit, ritEnd;
		rit = n->getRun()->rbegin(), ritEnd = n->getRun()->rend();
		while (rit != ritEnd) {
			if (A[rit->getRuleNumber()] == rit->getRunNumber()-1) {
				A[rit->getRuleNumber()] = rit->getRunNumber();
				if (rit->isTerminal())
					if (rit->getRuleNumber() < priority)
						priority = rit->getRuleNumber();
			}
			++rit;
		}
	}
	n->setRule(priority);
}

void traverseMRTforRevert(MR* w, string s)
{
	unsigned i = 0; 
	for ( ; i < s.length(); ++i) {
		checkSafePointer(w);
		if ('0' == s[i]) {
			if (NULL != w->getLeft()) { w = w->getLeft(); }
			else { break; }
		} else {
			if (NULL != w->getRight()) { w = w->getRight(); }
			else { break; }
		}
	}
}

void revertMRS(MR* wptr, Dtree* p)
{
	list<string>* mrlist = p->getMRS();
	if (NULL == mrlist) { return ; }

	list<string>::iterator it, end;
	it = mrlist->begin(), end = mrlist->end();
	MR* w = wptr;
	//if (w->getSafeWeight() > 0) {
	if (w->getSafeNeedNode()) {
		w->setNeedNode(true); w->setSafeNeedNode(false);
	}
		//w->setWeight(w->getSafeWeight());
		//w->setSafeWeight(0);
	
	while (it != end) {
		traverseMRTforRevert(wptr, *it);
		++it;
	}
}

void checkSafePointer(MR* wptr)
{
	if (NULL != wptr->getSafeLeft()) {
		wptr->setLeft(wptr->getSafeLeft());
		wptr->setSafeLeft(NULL);
	}
	if (NULL != wptr->getSafeRight()) {
		wptr->setRight(wptr->getSafeRight());
		wptr->setSafeRight(NULL);
	}
}

void revertWptr(MR* wptr, Dtree* p)
{
	string bitStr = p->getNodeString();
	if ('0' != bitStr[0] && '1' != bitStr[0]) { return ; }
	if (1 == bitStr.length()) { return ; }

	for (unsigned i = 1; i < bitStr.length(); ++i) {
		checkSafePointer(wptr);
		if ('0' == bitStr[i]) {
			if (NULL != wptr->getLeft()) { wptr = wptr->getLeft(); }
			else { break; }
		} else {
			if (NULL != wptr->getRight()) { wptr = wptr->getRight(); }
			else { break; }
		}
	}
}

void revert(MR* wptr, Dtree* p)
{
	revertWptr(wptr, p);
	revertMRS(wptr, p);
}

MR* setPivotNode(MR* wptr)
{
	MR* w = wptr;
	//while (0 == w->getWeight()) {
	while (!w->isNeeded()) {
		if (NULL != w->getParent()) { w = w->getParent(); }
		else { break; }
	}
	return w;
}

void modifyLeftDummyPointer(MR* wptr)
{
	if (NULL != wptr)
		if (NULL != wptr->getLeft()) {
			wptr->setSafeLeft(wptr->getLeft());
			wptr->setLeft(NULL);
		}
}

void modifyRightDummyPointer(MR* wptr)
{
	if (NULL != wptr) 
		if (NULL != wptr->getRight()) {
			wptr->setSafeRight(wptr->getRight());
			wptr->setRight(NULL);
		}
}

MR* modifyWptr(MR* wptr, Dtree* p)
{
	string bitStr = p->getNodeString();
	if ('0' != bitStr[0] && '1' != bitStr[0]) { return wptr; }
	if (1 == bitStr.length()) { return wptr; }

	MR* w = wptr;
	unsigned i = 1;
	for ( ; i < bitStr.length(); ++i) {
		if ('0' == bitStr[i]) {
			modifyRightDummyPointer(w);
			if (NULL != w->getLeft()) { w = w->getLeft(); }
			else { break; }
		} else {
			modifyLeftDummyPointer(w);
			if (NULL != w->getRight()) { w = w->getRight(); }
			else { break; }
		}
	}
	w = setPivotNode(w);

	return w;
}

void modifySafeWeight(MR* w)
{
	w->setSafeWeight(w->getWeight());
	w->setWeight(0);
}

MR* traverseMRT(MR* w, string bitStr)
{
	unsigned i = 0;
	for ( ; i < bitStr.length() && NULL != w; ++i) {
		if ('0' == bitStr[i]) {
			if (NULL != w->getLeft()) { w = w->getLeft(); }
			else { break; }
		} else {
			if (NULL != w->getRight()) { w = w->getRight(); }
			else { break; }
		}
	}
	if (bitStr.length() == i) { return w; }

	return NULL;
}

void modifyMRT(MR* wptr, Dtree* p)
{
	list<string>* mrlist = p->getMRS();
	if (NULL == mrlist) { return ; }

	list<string>::iterator it, end;
	it = mrlist->begin(), end = mrlist->end();
	MR* w;
	while (it != end) {
		string bitStr = *it;
		w = traverseMRT(wptr, bitStr);
		if (NULL != w) {
			if (NULL != w->getParent()) {
				MR* base = w;
				w = w->getParent();
				if (w->getLeft() == base) {
					w->setSafeLeft(w->getLeft());
					w->setLeft(NULL);
				}
				else {
					w->setSafeRight(w->getRight());
					w->setRight(NULL);
				}
			}
		}
		else if ("0" == bitStr) {
			string pStr = p->getNodeString();
			if (NULL != wptr->getRight() && 1 == pStr.length()) 
				//if (wptr->getRight()->getWeight() > 0) 
				if (wptr->getRight()->isNeeded()) {
					wptr->setNeedNode(false);
					wptr->setSafeNeedNode(true);
					//modifySafeWeight(wptr); 
				}
		}
		else if ("1" == bitStr) {
			string pStr = p->getNodeString();
			if (NULL != wptr->getLeft() && 1 == pStr.length())
				//if (wptr->getLeft()->getWeight() > 0)
				if (wptr->getLeft()->isNeeded()) {
					wptr->setNeedNode(false);
					wptr->setSafeNeedNode(true);
				 //modifySafeWeight(wptr);	
				}
		}
		++it;
	}
}

void cutMRSFirstBit(Dtree *n)
{
	list<string>* mrlist = n->getMRS();
	if (NULL != mrlist) {
		list<string>::iterator it, itEnd;
		it = mrlist->begin(), itEnd = mrlist->end();
		while (it != itEnd) {
			if (1 < (*it).length()) { *it = &(*it)[1]; }
			else { it = mrlist->erase(it); continue; }
			++it;
		}
		mrlist->unique();
	}
}

string compSameBit(string s1, string s2)
{
	if (s1[0] == s2[0]) { return ""; }

	string s, l;
	if (s1.length() < s2.length()) {
		s = s1, l = s2;
	} else {
		s = s2, l = s1;
	}
	string str = "";
	unsigned i = 1;
	for ( ; i < s.length(); ++i) {
		if (s[i] != l[i]) { return ""; }
		str += s[i];
	}
	for ( ; i < l.length(); ++i) {
		str += l[i];
	}
	str = "*" + str;

	return str;
}

void spanMaskForPhi(Dtree *n)
{
	if (NULL != n->getMRS()) {
		list<string> *cutInfo = NULL;
		list<string> *MRSInfo = n->getMRS();
		list<string>::iterator it1, it2, itEnd1, itEnd2;
		it1 = MRSInfo->begin(), itEnd1 = MRSInfo->end(), itEnd2 = MRSInfo->end();

		while (it1 != itEnd1) {
			string strA = *it1;
			it2 = it1;
			++it2;
			while (it2 != itEnd2) {
				string strB = *it2;
				string addStr = compSameBit(strA, strB);
				if ("" != addStr) {
					if (NULL == cutInfo) { cutInfo = new list<string>; }
					cutInfo->push_back(addStr);
				}
				++it2;
			}
			++it1;
		}
		n->deleteMRS();
		n->setMRS(cutInfo);
	}
}

void deleteDuplicatingElements(Dtree *n)
{
	if (NULL == n->getMRS()) { return ; }
	list<string>::iterator it1, it2;
	it1 = n->getMRS()->begin();
	unsigned i = 0, j;

	while (i < n->getMRS()->size()) {
		it2 = it1;
		++it2;
		j = i+1;
		while (j < n->getMRS()->size()) {
			if (*it1 == *it2) {
				it2 = n->getMRS()->erase(it2);
				--j, --it2;
			}
			++j;
			++it2;
		}
		++i;
		++it1;
	}
}

void inheritMRS(Dtree *d, list<string>* mrlist)
{
	if (NULL == mrlist) { return ; }
	 
	string dStr = d->getNodeString();
	list<string>::iterator it, itEnd;
	it = mrlist->begin(), itEnd = mrlist->end();
	while (it != itEnd) {
		if ("p" == dStr) { d->addMRS(*it); }
		else if ((*it).length() > dStr.length()) {
			string sSub = (*it).substr(0, dStr.length());
			if (!dStr.compare(sSub)) { d->addMRS(*it); }
		}
		++it;
	}

	deleteDuplicatingElements(d);
}

void inheritRun(Dtree *d, list<Run>* runlist)
{
	if (NULL == runlist) { return ; }
	list<Run>::iterator it, itEnd;
	it = runlist->begin(), itEnd = runlist->end();
	while (it != itEnd) {
		d->addRun(*it);
		++it;
	}
}

Dtree* makeNaiveDtreeNode(MR* w, Dtree *p)
{
	string tmpStr = w->getNodeString();
	Dtree *tmpNode = new Dtree(tmpStr, w->getRun(), NULL, w->getDindex());
	string pStr = p->getNodeString();

	inheritRun(tmpNode, p->getRun());

	p->setChild(tmpNode);

	return tmpNode;
}

Dtree* makeDtreeNode(MR* w, Dtree *p)
{
	string tmpStr = w->getNodeString();
	Dtree *tmpNode = new Dtree(tmpStr, w->getRun(), w->getMRInfo(), w->getDindex());
	string pStr = p->getNodeString();

	inheritRun(tmpNode, p->getRun());
	inheritMRS(tmpNode, p->getMRS());

	if ("p" == tmpStr) { spanMaskForPhi(tmpNode); }
	if ("root" != pStr) {
		if (tmpStr.length() < pStr.length()) { tmpNode->modifyString(pStr); }
	}

	cutMRSFirstBit(tmpNode);
	p->setChild(tmpNode);

	return tmpNode;
}

void traverseMRforDtree(MR* w, Dtree* p, vector<MR> *mr)
{
	if (NULL == w) { return ; }
	traverseMRforDtree(w->getLeft(), p, mr);
	traverseMRforDtree(w->getRight(), p, mr);

	if (w->isNeeded()) {
		unsigned tn = w->getTrieNumber();
		Dtree *n = makeDtreeNode(w, p);

		if (tn < mr->size()-1) {
			Dtree* ptr = n;
			MR* wptr = &(*mr)[tn+1];
			MR* sptr = wptr;
			modifyMRT(wptr,ptr);
			wptr = modifyWptr(wptr, ptr);
			traverseMRforDtree(wptr, ptr, mr);
			revert(sptr, ptr);
		} else { addRuleToLeaf(n); }
		n->deleteRun();
		checkChildNode(n);
	}
}

void traverseMRforNaiveDtree(MR* w, Dtree* p, vector<MR> *mr)
{
	if (NULL == w) { return ; }
	traverseMRforNaiveDtree(w->getLeft(), p, mr);
	traverseMRforNaiveDtree(w->getRight(), p, mr);

	if (w->isNeeded()) {
		unsigned tn = w->getTrieNumber();
		Dtree *n = makeNaiveDtreeNode(w, p);
		if (tn < mr->size()-1) {
			Dtree* ptr = n;
			MR* wptr = &(*mr)[tn+1];
			traverseMRforNaiveDtree(wptr, ptr, mr);
		} else { addRuleToLeaf(n); }
		n->deleteRun();
	}
}

void constructDtree(Dtree *d, vector<MR>* mr)
{
	Dtree* p = d;
	MR* wptr = &(*mr)[1];
	traverseMRforDtree(wptr, p, mr);
	Dtree* dummy = new Dtree("dummy");
	Dtree::decNumberOfDtree();
	settingNIndex(d, dummy);
}

void constructNaiveDtree(Dtree *d, vector<MR>* mr)
{
	Dtree* p = d;
	MR* wptr = &(*mr)[1];
	traverseMRforNaiveDtree(wptr, p, mr);

}

void addDIndex(MR* ptr)
{
	if (NULL == ptr) { return ; }

	addDIndex(ptr->getLeft());
	addDIndex(ptr->getRight());

	if (ptr->isNeeded()) {
		ptr->setDIndex(MR::getCounterForDIndex());
		MR::incDIndex();
	}
}

void settingDIndex(vector<MR>* mrt)
{
	unsigned w = mrt->size();
	MR* ptr;
	for (unsigned i = 1; i <= w; ++i) {
		ptr = &(*mrt)[i];
		MR::initDIndex();
		addDIndex(ptr);
		MR::setMaxDIndex(MR::getCounterForDIndex()-1);
	}
}

void addMRTInfo(MR* mr)
{
	MR *ptr = mr, *base = mr;

	ptr = ptr->getParent();
	while (NULL != ptr) {
		//if (0 < ptr->getWeight()) {
		if (ptr->isNeeded()) {
			ptr->setMRInfo(base->getNodeString());
		}
		ptr = ptr->getParent();
	}
}

void MRTInfoTraverse(MR* mr)
{
	if (NULL == mr) { return; }

	MRTInfoTraverse(mr->getLeft());
	MRTInfoTraverse(mr->getRight());

	//if (mr->getWeight() > 0) { addMRTInfo(mr); }
	if (mr->isNeeded()) { addMRTInfo(mr); }
}

void settingMRInfo(vector<MR>* mrt)
{
	vector<MR>::iterator it = mrt->begin();
	vector<MR>::iterator end = mrt->end();
	while (it != end) {
		MRTInfoTraverse(&(*it));
		++it;
	}
}

void moveRun(MR* p, MR* c)
{
	if (NULL != p->getRun()) {
		list<Run>::iterator it = p->getRun()->begin();
		list<Run>::iterator end = p->getRun()->end();
		while (it != end) {
			c->setRun(*it);
			++it;
		}
	}
}

void updateMRT(MR* mrp, MR* mrc, char c)
{
	unsigned i = mrp->getTrieNumber();
	if (NULL == mrc) { 
		if ("p" == mrp->getNodeString()) 
			if ('0' == c) { mrp->setLeft(new MR(c, i, "0", mrp)); }
			else { mrp->setRight(new MR(c, i, "1", mrp)); }
		else
			if ('0' == c) { mrp->setLeft(new MR(c, i, mrp->getNodeString()+"0", mrp)); }
			else { mrp->setRight(new MR(c, i, mrp->getNodeString()+"1", mrp)); }
	}
	if ('0' == c) { 
		moveRun(mrp, mrp->getLeft()), mrp->deleteRun();
		mrp->getLeft()->setNeedNode(true);
	}
	else { 
		moveRun(mrp, mrp->getRight()), mrp->deleteRun(); 
		mrp->getRight()->setNeedNode(true);
	}
	mrp->setNeedNode(false);
}

bool noMRS(MR* mr)
{
	if (NULL == mr) { return true; }
	if (!mr->isNeeded()) { return true; }

	return false;
}

void changeMRSet(MR* mr)
{
	if (NULL == mr) { return ; }

	if (mr->isNeeded()) {
		if (noMRS(mr->getLeft()) && !noMRS(mr->getRight())) // _ r 
			updateMRT(mr, mr->getLeft(), '0');
		if (!noMRS(mr->getLeft()) && noMRS(mr->getRight())) // l _ 
			updateMRT(mr, mr->getRight(), '1');
	}

	changeMRSet(mr->getLeft());
	changeMRSet(mr->getRight());
}

void changeAllMRSet(vector<MR>* mrt)
{
	vector<MR>::iterator it = mrt->begin();
	vector<MR>::iterator end = mrt->end();
	while (it != end) {
		changeMRSet(&(*it));
		++it;
	}
}

void addRun(MR* wptr, MR* base)
{
	list<Run>::iterator it = wptr->getRun()->begin();
	list<Run>::iterator end = wptr->getRun()->end();
	while (it != end) {
		base->setRun(*it);
		++it;
	}
}

bool isMRS(MR* mr)
{
	if (NULL == mr) { return false; }
	return mr->getDeleteSign();
}

void checkIsNeeded(MR* mr)
{
	if (isMRS(mr->getLeft()) && isMRS(mr->getRight())) {
		mr->setDeleteSign(true);
		mr->setNeedNode(false);	
		mr->deleteRun(); 
	}
}

void walkToRoot(MR* ptr)
{
	MR *wptr = ptr;

	wptr = wptr->getParent();
	while (NULL != wptr) {
		if (NULL != wptr->getRun() || 'p' == wptr->getNodeBit()) {
			if ('p' != wptr->getNodeBit()) { addRun(wptr, ptr); }
		}
		wptr = wptr->getParent();
	}
}

void MRTTraverseToDeleteUnnucessaryElements(MR* mr)
{
	if (NULL == mr) { return; }

	MRTTraverseToDeleteUnnucessaryElements(mr->getLeft());
	MRTTraverseToDeleteUnnucessaryElements(mr->getRight());

	if (mr->isNeeded()) { 
		walkToRoot(mr);
		checkIsNeeded(mr); 
	}
}

void MRTWeightTraverse(MR* mr)
{
	if (NULL == mr) { return; }

	MRTWeightTraverse(mr->getLeft());
	MRTWeightTraverse(mr->getRight());

	if (mr->getWeight() > 0) { walkToRoot(mr); }
}

void allMRTTraverseToDeleteUnnecessaryElements(vector<MR>* mrt)
{
	vector<MR>::iterator it = mrt->begin();
	vector<MR>::iterator end = mrt->end();
	while (it != end) {
		MRTTraverseToDeleteUnnucessaryElements(&(*it));
		++it;
	}
}

void traverseAndMakeMRTNode(RBT* rbt, MR* mr, unsigned& i)
{
	if (NULL == rbt) { return ;}

	if ("p" == mr->getNodeString()) { 
		mr->setNeedNode(true); 
		mr->setDeleteSign(true);
	}
	if (NULL != rbt->getRun()) {
		list<Run>::iterator it = rbt->getRun()->begin();
		list<Run>::iterator itEnd = rbt->getRun()->end();
		while (it != itEnd) {
			mr->setRun(*it);
			++it;
		}
		mr->setNeedNode(true);
		mr->setDeleteSign(true);
	}

	if (NULL != rbt->getLeft())
		mr->setLeft(new MR('0', i, rbt->getLeft()->getNodeString(), mr)); 
  if (NULL != rbt->getRight())
		mr->setRight(new MR('1', i, rbt->getRight()->getNodeString(), mr)); 

	traverseAndMakeMRTNode(rbt->getLeft(), mr->getLeft(), i);
	traverseAndMakeMRTNode(rbt->getRight(), mr->getRight(), i);
}

void copyRBTtoMRT(vector<RBT>*& rbt, vector<MR>* mr)
{
	unsigned w = rbt->size()-1;
	for (unsigned i = 1; i < w+1; ++i) {
		//traverseAndMakeMRTNode(&(*rbt)[i], &(*mr)[i], w, i);
		traverseAndMakeMRTNode(&(*rbt)[i], &(*mr)[i], i);
	}
}

void createTheMRTRootNodes(vector<MR>* mr, unsigned w)
{
  mr->push_back(MR(' ', 0, " ", NULL));
	unsigned i = 1;
	while (i < w) {
		mr->push_back(MR('p', i, "p", NULL));
		++i;
	}
}

void makeMatchRunSetTrie(vector<RBT>*& rbt, vector<MR>* mr)
{
	createTheMRTRootNodes(mr, rbt->size());
	copyRBTtoMRT(rbt,mr);
	allMRTTraverseToDeleteUnnecessaryElements(mr);
	changeAllMRSet(mr);
	settingMRInfo(mr);
	settingDIndex(mr);
}
*/

template <class T>
void traverseAndMakeRBTNode(T *rbt, Run run)
{
	string bitString = run.getBitString();
	unsigned l = bitString.length();
	unsigned tn = rbt->getTrieNumber();
	unsigned i = 0;
	T* ptr = rbt;

	while (i < l) {
		if (bitString[i] == '0') {
			if (NULL == ptr->getLeft()) {
				T* lptr = new T('0', tn, bitString.substr(0,i+1));
				ptr->setLeft(lptr);
			}
			ptr = ptr->getLeft();
		}
		else {
			if (NULL == ptr->getRight()) {
				T* rptr = new T('1', tn, bitString.substr(0,i+1));
				ptr->setRight(rptr);
			}
			ptr = ptr->getRight();
		}
		++i;
	}

	ptr->setRun(run);
}
template void traverseAndMakeRBTNode(RBT *rbt, Run run);
template void traverseAndMakeRBTNode(PRBT *rbt, Run run);

list<RunPair>* cutOutRun(Rule rule)
{
	unsigned ruleNumber = rule.getRuleNumber();
	string bitString = rule.getRuleBitString();
	unsigned w = bitString.length();
	unsigned i = 0;
	unsigned runNumber = 1;
	bool flag = false;
	string buf = "";
	list<RunPair>* runPair = new list<RunPair>;

	while (i < w) {
		if ('*' == bitString[i]) {
			if (true == flag) {
				Run run = Run(buf, runNumber, ruleNumber);
				runPair->push_back(RunPair(i+1-buf.length(),run));
				flag = false, buf = "", ++runNumber;
			}
		}
		else 
			flag = true, buf += bitString[i];
		++i;
	}

	if (true == flag) {
		Run run = Run(buf, runNumber, ruleNumber);
		runPair->push_back(RunPair(i+1-buf.length(),run));
	}

	list<RunPair>::iterator it = runPair->end();
	--it;

	Run tmpRun = it->getRun();
	unsigned tmpStart = it->getStartBit();
	tmpRun.setTerminalTrue();

	runPair->pop_back();
	runPair->push_back(RunPair(tmpStart, tmpRun));

	return runPair;
}

template <class T>
void createTheRBTRootNodes(vector<T>* rbt, unsigned w)
{
	/* create the root nodes not to rbt[w-1] but to rbt[w] */
  rbt->push_back(T(' ', 0, " "));
	unsigned i = 1;
	while (i <= w) {
		rbt->push_back(T('p', i, "p"));
		++i;
	}
}


template <class T>
void makeRunBasedTrie(list<Rule>*& rulelist, vector<T> *rbt)
{
	list<Rule>::iterator ruleIt = rulelist->begin();
	list<Rule>::iterator ruleItEnd = rulelist->end();

	createTheRBTRootNodes(rbt,ruleIt->getRuleBitString().size());

	list<RunPair>* rpPtr;
	list<RunPair>::iterator rpIt, rpItEnd; 
	while (ruleIt != ruleItEnd) {
		rpPtr = cutOutRun(*ruleIt);
		rpIt = rpPtr->begin(), rpItEnd = rpPtr->end();
		while (rpIt != rpItEnd) {
			traverseAndMakeRBTNode(&(*rbt)[rpIt->getStartBit()], rpIt->getRun());
			++rpIt;
		}
		++ruleIt;
	}
}
template void makeRunBasedTrie(list<Rule>*&, vector<RBT> *);
template void makeRunBasedTrie(list<Rule>*&, vector<PRBT> *);

/* following codes are for debug */

template <class T>
void postTraverse(T *rbt)
{
	if (NULL == rbt) { return ; }
	postTraverse(rbt->getLeft());
	postTraverse(rbt->getRight());
	list<Run>* runlist;

	if (NULL != (runlist = rbt->getRun())) {
		cout << rbt->getNodeString() << ": ";
		list<Run>::iterator it, itEnd;
		it = runlist->begin(), itEnd = runlist->end();
		while (it != itEnd) {
			cout << '(' << it->getRuleNumber() << ',' << it->getRunNumber() << ',' << it->isTerminal() << ") ";
			++it;
		}
		putchar('\n');
	}
}

/*
void postTraverse(MR *mr)
{
	if (NULL == mr) { return ; }
	postTraverse(mr->getLeft());
	postTraverse(mr->getRight());

	//if (mr->getWeight() > 0) {
	//if (NULL != mr->getRun()) {
	if (mr->isNeeded()) {
		cout << mr->getNodeString() << ' ' << mr->getDindex();
		//cout << mr->getNodeString() << ' ' << mr->getDindex() << endl;

	list<Run>* runlist;
	if (NULL != (runlist = mr->getRun())) {
		printf(": ");
		list<Run>::iterator it, itEnd;
		it = runlist->begin(), itEnd = runlist->end();
		while (it != itEnd) {
			cout << '(' << it->getRuleNumber() << ',' << it->getRunNumber() << ") ";
			++it;
		}
	}

	list<string>* slist;
	if (NULL != (slist = mr->getMRInfo())) {
		printf(" -- [");
		list<string>::iterator it, itEnd;
		it = slist->begin(), itEnd = slist->end();
		while (it != itEnd) {
			cout << *it << ", ";
			++it;
		}
		cout << "]";
	}
	putchar('\n');
	}
}

void showChild(Dtree* d)
{
	if (NULL != d->getChild()) {
		for (unsigned i = 0; i < d->getNumberOfChild(); ++i) {
			if ((*(d->getChild()))[i]->getNodeString() != "dummy") {
				if ((*(d->getChild()))[i]->getNindex() != i) { cout << "[n]"; }
				else { cout << '[' << (*(d->getChild()))[i]->getNindex() << ']'; }
				cout << (*(d->getChild()))[i]->getNodeString();
				cout << ' ';
				showChild((*(d->getChild()))[i]);
			}
		}
	} else {
		cout << '(' << d->getRule() << ')' << endl;
	}
}
*/
