/* rbt.c */

#include <rbt.h>

void free_runlist(runlist* rl)
{
	if (rl == NULL) { return ; }
	runlist* ptr = rl;
	runlist* wptr;
	while (ptr != NULL) {
		wptr = ptr;
		ptr = ptr->next;
		free(wptr);
	}
}

runlist* add_run_to_RBT_node(runlist *head, runlist* tail, run r)
{
	runlist* ptr = (runlist*)malloc(sizeof(runlist));
	strcpy(ptr->run.run, r.run);
	ptr->run.rule_num = r.rule_num;
	ptr->run.run_num = r.run_num;
	ptr->run.trie_number = r.trie_number;
	ptr->next = NULL;

	if (NULL == tail) {
		ptr->prev = NULL;
		head = tail = ptr;
	}
	else {
		ptr->prev = tail;
		tail = ptr;
	}

	return tail;
}

rbt* make_RBT_node(char b)
{
	rbt* node = (rbt*)malloc(sizeof(rbt));
	node->bit = b;
	node->left = node->right = NULL;
	node->head = node->tail = NULL;

	return node;
}

void add_rule_number(runlist* rs, unsigned i)
{
	if (NULL == rs) { return ; }
	runlist* ptr = rs;
	while (NULL != ptr) {
		ptr->run.rule_num = i;
		ptr = ptr->next;
	}
}

void add_terminal_mark(runlist* rs)
{
	if (NULL == rs) { return ; }
	runlist* ptr = rs;
	while (NULL != ptr->next) {
		ptr = ptr->next;
	}
	ptr->run.terminal = true;
}

runlist* add_run(runlist* rs, char* run_str, unsigned run_num, unsigned tn)
{
	//printf("%s ", run_str);
	runlist* new = (runlist*)malloc(sizeof(runlist));
	new->run.run = (char*)malloc((_w+1)*sizeof(char));
	strcpy(new->run.run,run_str);
	new->run.run[_w] = '\0';
	new->run.rule_num = 0;
	new->run.run_num = run_num;
	new->run.trie_number = tn;
	new->run.terminal = false;
	new->prev = new -> next = NULL;

	runlist* ptr = rs;
	if (NULL == rs) { 
		return new;
	}
	while (NULL != ptr->next) { ptr = ptr->next; }
	ptr->next = new;
	new->prev = ptr;
	return rs;
}

runlist* cut_run(char* rule)
{
	runlist* rs = NULL;
	{ unsigned i;
		int s = -1, t = -1;
		unsigned run_counter = 0;
		bool sign = false;
		char* buf = (char*)malloc((_w+1)*sizeof(char));
		// printf("%s : ", rule);
		for (i = 0; i < _w; ++i) {
			if ('*' != rule[i]) {
			 if (!sign) {
				 s = i+1;
				 ++run_counter;
				 sign = true;
			 }
			}
			else if (sign) {
				t = i;
				strncpy(buf, rule+s-1, t-s+1);
				buf[t-s+1] = '\0';
				/* index start from 0. T[0], T[1], ... , T[w-1] */
				rs = add_run(rs, buf, run_counter, s);
				// printf("%s ", buf);
				sign = false;
			}
		}
		if (sign) {
			strncpy(buf, rule+s-1, _w-s+1);
			buf[_w-s+1] = '\0';
			rs = add_run(rs, buf, run_counter, s);
			// printf("%s ", buf);
		}
		free(buf);
	}
	add_terminal_mark(rs);
	return rs;
}

rbt** make_Run_Based_Trie(char** rulelist)
{
	rbt** T = (rbt**)malloc(_w*sizeof(rbt*));
	/* make a root nodes T[0], T[1], ..., T[w-1] */
	{	unsigned i;
		for (i = 0; i < _w; ++i)
			T[i] = make_RBT_node('_');
	}

	/* cut run from a rule and add it to an appropriate Trie */
	{ unsigned i;
		char copy[_w+1];
		for (i = 0; i < _n; ++i) {
			strcpy(copy,rulelist[i]);
			runlist* runs = cut_run(copy);
			add_rule_number(runs, i+1);
			// debug
			runlist* ptr = runs;
			while (ptr != NULL) {
				printf("[str = %4s i = %d rule = %2d run = %d ] ", ptr->run.run, ptr->run.trie_number, ptr->run.rule_num, ptr->run.run_num);
				ptr = ptr->next;
			}
			putchar('\n');
			// debug
			/* add run */
			//printf("R[%2d] = %s: %s\n", i+1, copy, rulelist[i]); 
			free_runlist(runs);
		}
	}

	return T;
}
