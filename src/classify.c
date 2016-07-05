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

	char defaultrule[_w+1];
	unsigned j;
	for (j = 0; j < _w; ++j)
		defaultrule[j] = '*';
	defaultrule[_w] = '\0';

	if (i != _n)
		;//printf("%s -> rule[%2d] %s\n", header, i+1, rulelist[i]);
	else
		;//printf("%s -> rule[%2d] %s\n", header, _n+1, defaultrule);
}

void do_sequential_search(char** rulelist, char** headerlist)
{
	unsigned i;
	for (i = 0; i < _hn; ++i)
		sequential_search(rulelist, headerlist[i]);
}

void Simple_Search(rbt** T, char* header)
{
	unsigned* A = (unsigned*)calloc(_n+1, sizeof(unsigned));
	rbt* ptr;
	unsigned priority = _n+1;
	runlist* it;

	{ unsigned k, i;
		for (k = 0; '\0' != header[k]; ++k) {
			ptr = T[i];
			for (i = k-1; i < _w; ++i) {
				if ('0' == header[i])
					if (NULL != ptr->left)
						ptr = ptr->left;
					else
						break;
				else
					if (NULL != ptr->right)
						ptr = ptr->right;
					else
						break;
				if (NULL != ptr->rs) 
					for (it = ptr->rs; NULL != it; it = it->next) {
						if (A[it->run.rule_num] == it->run.run_num-1) {
							++A[it->run.rule_num];
							if (it->run.terminal)
								if (it->run.rule_num < priority)
									priority = it->run.rule_num;
						}
					}
			}
		}
	}
	printf("%s --> %2d\n", header, priority);

	free(A);
}

void do_Simple_Search(rbt** T, char** headerlist)
{
	unsigned i;
	for (i = 0; i < _hn; ++i)
		Simple_Search(T, headerlist[i]);
}
