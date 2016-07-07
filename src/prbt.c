/* prbt.c */

#include <prbt.h>

void low_trie_traverse(prbt* high, prbt** PT)
{
	unsigned len = strlen(high->label);
	char* bit_string = (char*)malloc((len+1)*sizeof(char));
	strcpy(bit_string, high->label);
	bit_string[len] = '\0';

	{ unsigned i, l, j = 0;
		prbt* low;
		for (i = high->trie_number; i < _w-1; ++i) {
			low = PT[i+1];
			for (l = j; l < len; ++l) {
				if ('0' == bit_string[l] && NULL != low->left) { low = low->left; }
				else if ('1' == bit_string[l] && NULL != low->right) { low = low->right; }
				else { break; }
			}
			if (l == len) {
				if (NULL == high->left || NULL == high->right) { ; }
				if (NULL != low->rs) { ; }
				break;
			}
		}
	}
	//printf("%d | %c | %s\n", low->trie_number, low->bit, bit_string);

	free(bit_string);
}

void lower_trie_traverse_via_label_of_runs_on_higher_trie(prbt* low, prbt** PT)
{
	if (NULL == low) { return; }
	lower_trie_traverse_via_label_of_runs_on_higher_trie(low->left, PT);
	lower_trie_traverse_via_label_of_runs_on_higher_trie(low->right, PT);
	low_trie_traverse(low, PT);
}

void make_pointer_from_PTi_to_PTj(prbt* pi, prbt* pj)
{
	if (NULL == pi->left)
		pi->left = pj;
	if (NULL == pi->right)
		pi->right = pj;
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
	node->pright = NULL;
	node->rs = NULL;

	node->right = NULL;
	node->pleft = NULL;
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

		prbt* low_trie;
		for (i = _w-2; ; --i) { // start from PT[w-2]
			low_trie = PT[i];
			lower_trie_traverse_via_label_of_runs_on_higher_trie(low_trie, PT);
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
			//printf("free run (%4s, %2d, %d)\n", ptr->run.run, ptr->run.rule_num, ptr->run.run_num);
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

	{ unsigned i;
		for (i = 0; i < _w; ++i)
			free_traverse_PRBT(PT[i]);
	}
}
