/* prbt.c */

#include <prbt.h>

void traverse_and_make_backbone_PRBT(prbt* PT, run r)
{
	unsigned l = strlen(r.run);
	char* bit_string = (char*)malloc((l+1)*sizeof(char));
	strcpy(bit_string, r.run);
	bit_string[l] = '\0';
	unsigned i;
	prbt* ptr = PT;

	for (i = 0; '\0' != bit_string[i]; ++i) {
		if ('0' == r.run[i]) {
			if (NULL == ptr->left)
				ptr->left = make_PRBT_node('0');
			ptr = ptr->left;
		}
		else {
			if (NULL == ptr->right)
				ptr->right = make_PRBT_node('1');
			ptr = ptr->right;
		}
	}
	ptr->rs = add_run_to_RBT_node(ptr->rs, r); // add_run_to_RBT_node can be used to PRBT node.

	free(bit_string);
}

prbt* make_PRBT_node(char b)
{
	prbt* node = (prbt*)malloc(sizeof(prbt));
	node->bit = b;
	node->left = NULL;
	node->right = NULL;
	node->rs = NULL;

	return node;
}

prbt** make_Pointed_Run_Based_Trie(char** rulelist)
{
	prbt** PT = (prbt**)malloc(_w*sizeof(prbt));
	/* make a root nodes PT[0], PT[1], ..., PT[w-1] 
	 * Caution! Pointed Run-Based Trie PT[i] starts from PT[0] not PT[1] */
	{	unsigned i;
		for (i = 0; i < _w; ++i)
			PT[i] = make_PRBT_node('_');
	}

	/* at first, make a Run-Based Trie */
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
	if (NULL != PT->left)
		free(PT->left);
	if (NULL != PT->right)
		free(PT->right);
}

void free_PRBT(prbt** PT)
{
	if (NULL == PT)
		return;

	{ unsigned i;
		for (i = 0; i < _w; ++i) {
			free_traverse_PRBT(PT[i]);
		}
	}
}
