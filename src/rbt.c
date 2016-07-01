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

rbt* make_RBT_node(char b, run r)
{
	rbt* node = (rbt*)malloc(sizeof(rbt));
	node->bit = b;
	node->left = NULL;
	node->right = NULL;
	if (!strcmp(r.run,"dummy")) 
		node->head = node->tail = NULL;
	else 
		node->tail = add_run_to_RBT_node(node->head, node->tail, r);

	return node;
}

rbt** make_Run_Based_Trie(char** rulelist)
{
	rbt** T = (rbt**)malloc(_w*sizeof(rbt*));
	/* make a root nodes T[0], T[1], ..., T[w-1] */
	{	unsigned i;
		run r = { "dummy", 0, 0, false };
		for (i = 0; i < _w; ++i)
			T[i] = make_RBT_node('_', r);
	}

	return T;
}
