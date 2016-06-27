/* openfile.cpp */

#include <openfile.hpp>

void readPackets(char *&filename, list<string>* packets) throw (string)
{
	ifstream ifs(filename);
	
	if (ifs.fail())
		throw "Error: Can't open an input packets file.\n";
	
	string tmp;
	while (getline(ifs, tmp)) {
		packets->push_back(tmp);
	}
	ifs.close();

	if (0 == packets->size())
		throw "Error: Input Packets file has no packt.\n";
}

void readRulelist(char *&filename, list<Rule>* rulelist) throw (string)
{
	ifstream ifs(filename);

	if (ifs.fail())
		throw "Error: Can't open an input rulelist file.\n";

	unsigned rulenumber = 1;
	string tmp;
	while (getline(ifs, tmp)) {
		rulelist->push_back(Rule(rulenumber,tmp));
		++rulenumber;
	}
	ifs.close();

	if (0 == rulelist->size())
		throw "Error: Input Rulelist file has no rule.\n";
}
