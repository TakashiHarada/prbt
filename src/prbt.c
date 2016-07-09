/* prbt.c */

#include <prbt.h>

void set_pointer(prbt* high, prbt* low)
{
	if (NULL == high->pleft) { high->pleft = low->pleft; }
	if (NULL == high->pright) { high->pright = low->pright; }
}

runlist* copy_run(runlist* r1, runlist* r2)
{
	runlist* ptr = r2;
	runlist* wptr = NULL;
	bool flag = false;
	unsigned l;
	runlist* head;
	runlist* new;
	while (NULL != ptr) {
		l = strlen(ptr->run.run) + 1;
		new = (runlist*)malloc(sizeof(runlist));
		new->run.run = (char*)malloc(l*sizeof(char));
		strcpy(new->run.run, ptr->run.run);
		new->run.run[_w] = '\0';
		new->run.rule_num = ptr->run.rule_num;
		new->run.run_num = ptr->run.run_num;
		new->run.trie_number = ptr->run.trie_number;
		new->run.terminal = ptr->run.terminal;
		new->prev = new->next = NULL;

		//printf("(%d %d)\n", new->run.rule_num, new->run.run_num);
		if (!flag) { flag = true; wptr = head = new; }
		else {
			while (NULL != wptr->next) { wptr = wptr->next; }
			wptr->next = new;
			new->prev = wptr;
		}

		ptr = ptr->next;
	}
	if (NULL == r1) { return head; }
	wptr = r1;
	while (NULL != wptr->next) { wptr = wptr->next; }
	wptr->next = head;

	return r1;
}

void low_trie_traverse(prbt* high, prbt** PT)
{
	unsigned len = strlen(high->label);
	char* bit_string = (char*)malloc((len+1)*sizeof(char));
	strcpy(bit_string, high->label);
	bit_string[len] = '\0';

	printf("%d %s\n", high->trie_number, high->label);
	{ unsigned i, l, j = 1;
		prbt* low;
		for (i = high->trie_number; i < _w-1; ++i, ++j) {
			low = PT[i+1];
			for (l = j; l < len; ++l) {
				if ('0' == bit_string[l] && NULL != low->pleft) { low = low->pleft; }
				else if ('1' == bit_string[l] && NULL != low->pright) { low = low->pright; }
				else { break; }
			}
			if (l == len) {
				/* set pointer for classify */
				if (NULL == high->pleft || NULL == high->pright) { set_pointer(high, low); }
				/* set run for classify */
				if (NULL != low->rs) { high->rs = copy_run(high->rs, low->rs); }
				break;
			}
		}
	}

	free(bit_string);
}

void lower_trie_traverse_via_label_of_runs_on_higher_trie(prbt* high, prbt** PT)
{
	if (NULL == high) { return; }
	lower_trie_traverse_via_label_of_runs_on_higher_trie(high->left, PT);
	lower_trie_traverse_via_label_of_runs_on_higher_trie(high->right, PT);
	low_trie_traverse(high, PT);
}

void make_pointer_from_PTi_to_PTj(prbt* pi, prbt* pj)
{
	if (NULL == pi->left)
		pi->pleft = pj;
	if (NULL == pi->right)
		pi->pright = pj;
}

void traverse_and_make_backbone_PRBT(prbt* PT, run r)
{
	unsigned l = strlen(r.run);
	unsigned k = r.trie_number-1;  // trie_number starts from 0 not 1 
	char* buf = (char*)malloc((l+1)*sizeof(char));
	char* bit_string = (char*)malloc((l+1)*sizeof(char));
	strcpy(bit_string, r.run);
	bit_string[l] = '\0';
	unsigned i;
	prbt* ptr = PT;

	for (i = 0; '\0' != bit_string[i]; ++i) {
		if ('0' == r.run[i]) {
			if (NULL == ptr->left)  {
				strncpy(buf, bit_string, i+1); // cut a label 
				buf[i+1] = '\0';
				ptr->left = make_PRBT_node('0', buf, k);
			}
			ptr->pleft = ptr->left;
			ptr = ptr->left;
		}
		else {
			if (NULL == ptr->right) {
				strncpy(buf, bit_string, i+1); // cut a label
				buf[i+1] = '\0';
				ptr->right = make_PRBT_node('1', buf, k);
			}
			ptr->pright = ptr->right;
			ptr = ptr->right;
		}
	}
	ptr->rs = add_run_to_RBT_node(ptr->rs, r); // add_run_to_RBT_node can be used to PRBT node.

	free(bit_string);
	free(buf);
}

prbt* make_PRBT_node(char b, char* str, unsigned tn)
{
	prbt* node = (prbt*)malloc(sizeof(prbt));
	node->bit = b;
	node->left = NULL;
	node->right = NULL;
	node->rs = NULL;

	node->pleft = NULL;
	node->pright = NULL;
	node->trie_number = tn;
	unsigned l = strlen(str);
	node->label = (char*)malloc((l+1)*sizeof(char));
	strcpy(node->label, str);
	(node->label)[l] = '\0';

	return node;
}

prbt** make_Pointed_Run_Based_Trie(char** rulelist)
{
	prbt** PT = (prbt**)malloc(_w*sizeof(prbt));
	/* make a root nodes PT[0], PT[1], ..., PT[w-1] 
	 * Caution! Pointed Run-Based Trie PT[i] starts from PT[0] not PT[1] */
	{	unsigned i;
		for (i = 0; i < _w; ++i) {
			PT[i] = make_PRBT_node('_', "root", i);
		}
	}

	/* at first, make a Run-Based Trie. This is a base of Pointed Run-Based Trie  */
	{	unsigned i;
		char copy[_w+1];
		for (i = 0; i < _n; ++i) {
			strcpy(copy, rulelist[i]);
			runlist* runs = cut_run(copy);
			add_rule_number(runs, i+1);
			runlist* ptr = runs;
			while (ptr != NULL) {
				traverse_and_make_backbone_PRBT(PT[ptr->run.trie_number-1], ptr->run);
				ptr = ptr->next;
			}
			free_runlist(runs);
		}
	}

	/* set all nodes to have a left child and right child */
	{ unsigned i;
		prbt* pi;
		prbt* pj;
		/* if a root node of PT[i] does not have left of right or both childs, 
		 * then each pointers of root of PT[i] points to root of PT[j] */
		for (i = 0; i < _w-1; ++i) { // PT[w-1] needs not to have both pointers.
			pi = PT[i];
			pj = PT[i+1];
			make_pointer_from_PTi_to_PTj(pi, pj);   // PT_(j) means PT_(i+1)
		}

		prbt* high_trie;
		for (i = _w-2; ; --i) { // start from PT[w-2]
			high_trie = PT[i];
			lower_trie_traverse_via_label_of_runs_on_higher_trie(high_trie, PT);
			if (i == 0) { break; }
		}
	}

	return PT;
}

void free_traverse_PRBT(prbt* PT)
{
	if (NULL == PT) { return; }
	free_traverse_PRBT(PT->left);
	free_traverse_PRBT(PT->right);

	if (NULL != PT->rs) {
		runlist* ptr = PT->rs;
		runlist* ptr2;
		while (NULL != ptr) {
			//printf("free run (%s, %2d, %d)\n", ptr->run.run, ptr->run.rule_num, ptr->run.run_num);
			ptr2 = ptr;
			ptr = ptr->next;
			free(ptr2);
		}
	}
	if (NULL != PT->label) { free(PT->label); }
	if (NULL != PT->left) { free(PT->left); }
	if (NULL != PT->right) { free(PT->right); }
}

void free_PRBT(prbt** PT)
{
	if (NULL == PT) { return; }

	unsigned i;
	for (i = 0; i < _w; ++i)
		free_traverse_PRBT(PT[i]);
}

void traverse_PT(prbt* PT)
{
	if (NULL == PT) { return; }
	traverse_PT(PT->left);
	traverse_PT(PT->right);

	printf("%s, ", PT->label);
	runlist* ptr = PT->rs;
	while (NULL != ptr) {
		printf("(%d, %d) ", ptr->run.rule_num, ptr->run.run_num);
		ptr = ptr->next;
	}
	if (NULL != PT->pleft)
		printf("L--> (%d %s) ", PT->pleft->trie_number+1, PT->pleft->label);
	else
		printf("L--> NULL ");
	if (NULL != PT->pright)
		printf("R--> (%d %s) ", PT->pright->trie_number+1, PT->pright->label);
	else
		printf("R--> NULL ");
	putchar('\n');
}

void traverse_PRBT(prbt** PT)
{
	unsigned i;
	for (i = 0; i <_w; ++i) {
		printf("========== %d ==========\n", i+1);
		traverse_PT(PT[i]);
	}
}
