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

runlist* add_run_to_RBT_node(runlist *rs, run r)
{
	//printf("%s ", run_str);
	runlist* new = (runlist*)malloc(sizeof(runlist));
	unsigned l = strlen(r.run);
	new->run.run = (char*)malloc((l+1)*sizeof(char));
	strcpy(new->run.run,r.run);
	new->run.run[l] = '\0';
	new->run.rule_num = r.rule_num;
	new->run.run_num = r.run_num;
	new->run.trie_number = r.trie_number;
	new->run.terminal = r.terminal;
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

rbt* make_RBT_node(char b)
{
	rbt* node = (rbt*)malloc(sizeof(rbt));
	node->bit = b;
	node->left = NULL;
	node->right = NULL;
	node->rs = NULL;

	return node;
}

void traverse_and_make_RBT_node(rbt* T, run r)
{
	unsigned l = strlen(r.run);
	char* bit_string = (char*)malloc((l+1)*sizeof(char));
	strcpy(bit_string, r.run);
	bit_string[l] = '\0';
	unsigned i;
	rbt* ptr = T;

	for (i = 0; '\0' != bit_string[i]; ++i) {
		if ('0' == r.run[i]) {
			if (NULL == ptr->left)
				ptr->left = make_RBT_node('0');
			ptr = ptr->left;
		} 
		else {
			if (NULL == ptr->right)
				ptr->right = make_RBT_node('1');
			ptr = ptr->right;
		}
	}
	//ptr->head = add_run_to_RBT_node(ptr->head, ptr->tail, r);
	ptr->rs = add_run_to_RBT_node(ptr->rs, r);

	free(bit_string);
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
			runlist* ptr = runs;
			while (ptr != NULL) {
				//printf("[str = %4s i = %d rule = %2d run = %d ] ", ptr->run.run, ptr->run.trie_number, ptr->run.rule_num, ptr->run.run_num);
				traverse_and_make_RBT_node(T[ptr->run.trie_number-1], ptr->run);
				ptr = ptr->next;
			}
			//putchar('\n');
			free_runlist(runs);
		}
	}

	return T;
}

void free_traverse_RBT(rbt* T)
{
	if (NULL == T) { return; }
	free_traverse_RBT(T->left);
	free_traverse_RBT(T->right);

	if (NULL != T->rs) {
		runlist* ptr = T->rs;
		runlist* ptr2;
		while (NULL != ptr) {
			//printf("free run (%4s, %2d, %d)\n", ptr->run.run, ptr->run.rule_num, ptr->run.run_num);
			ptr2 = ptr;
			ptr = ptr->next;
			free(ptr2);
		}
	}

	if (NULL != T->left)
		free(T->left);
	if (NULL != T->right)
		free(T->right);
}

void free_RBT(rbt** T)
{
	{ unsigned i;
		for (i = 0; i < _w; ++i) {
			free_traverse_RBT(T[i]);
		}
	}
}
