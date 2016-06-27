#include <main.hpp>

int main(int argc, char* argv[])
{
	/* check arguments */
	if (argc != 3) {
		printf("Usage: $./main <rule list> <pseudo packets>\n");
		return 1;
	}

	/* open and read a rulelist */
	list<Rule> *rulelist = new list<Rule>;
	try {
		readRulelist(argv[1],rulelist);
	} catch (string error_message) {
		cout << error_message; return 1;
	}

	/* open and read packets */
	list<string> *packets = new list<string>;
	try {
		readPackets(argv[2],packets);
	} catch (string error_message) {
		cout << error_message; return 1;
	}

	/* do the sequential search */
	list< list<Result> > results;
	list<Result>* resultOfSequential = new list<Result>;
	classifyViaSequentialSearch(rulelist, packets, resultOfSequential);

	/*{
		list<Result>::iterator it, end;
		it = resultOfSequential->begin(), end = resultOfSequential->end();
		while (it != end) {
			cout << it->getPacket() << " " << it->getValue() << endl;
			++it;
		}
	}*/

	/* make a Run-Based Trie */
	vector<RBT>* rbt = new vector<RBT>;
	makeRunBasedTrie(rulelist,rbt);

	{
		vector<RBT>::iterator it, end;
		it = rbt->begin(), end = rbt->end();
		unsigned i = 0;
		while (it != end) {
			printf("===== %d =====\n\n",i);
			postTraverse(&(*it));
			++i;
			++it;
		}
	}

	/* do the simple search */
	list<Result>* resultOfSimpleSearch = new list<Result>;
	{
  	unsigned n = rulelist->size();
		classifyViaSimpleSearch(rbt, n, packets, resultOfSimpleSearch);
	}
	results.push_back(*resultOfSimpleSearch);

	/* make a Pointed Run-Based Trie */
	vector<PRBT>* prbt = new vector<PRBT>;
	makePointedRunBasedTrie(rbt, prbt, rulelist);

	//assert(0 == checkClassifyResult(resultOfSequential, results));

	/* delete dynamicaly allocated memories */
	delete rulelist;
	delete packets;
	delete rbt;
	delete resultOfSequential;
	delete resultOfSimpleSearch;

	return 0;
}
