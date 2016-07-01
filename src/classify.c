/* classify.c */

#include <classify.h>

bool match_rule_and_header(char* rule, char* header)
{
	unsigned i;
	for (i = 0; i < _w; ++i)
		if (rule[i] != '*' && rule[i] != header[i])
			return false;

	return true;
}

void sequential_search(char** rulelist, char* header)
{
	unsigned i;
	for (i = 0; i < _n; ++i)
		if (match_rule_and_header(rulelist[i], header)) {
			break;
		}

	char defaultrule[_w];
	unsigned j;
	for (j = 0; j < _w; ++j)
		defaultrule[j] = '*';

	if (i != _n)
		printf("%s -> rule[%2d] %s \n", header, i+1, rulelist[i]);
	else
		printf("%s -> rule[%2d] %s\n", header, _n+1, defaultrule);
}

void do_sequential_search(char** rulelist, char** headerlist)
{
	unsigned i;
	for (i = 0; i < _hn; ++i)
		sequential_search(rulelist, headerlist[i]);
}
