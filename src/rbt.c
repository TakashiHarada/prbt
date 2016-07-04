/* rbt.c */

#include <rbt.h>

runlist* add_run_to_RBT_node(runlist *head, runlist* tail, run r)
{
	runlist* ptr = (runlist*)malloc(sizeof(runlist));
	strcpy(ptr->run.run, r.run);
	ptr->run.rule_num = r.rule_num;
	ptr->run.run_num = r.run_num;
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

runlist* cut_run(char* rule)
{
	return NULL;
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
			/* add run */
			//printf("R[%2d] = %s: %s\n", i+1, copy, rulelist[i]); 
		}
	}

	return T;
}
