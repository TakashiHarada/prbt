/* rbt.h */

#ifndef __PRBT_RBT_H__
#define __PRBT_RBT_H__

#ifndef __PRBT_CONST_H__
#include <const.h>
#endif

#ifndef __PRBT_TOOLS_H__
#include <tools.h>
#endif

#ifndef __PRBT_IO_H__
#include <io.h>
#endif

unsigned _number_of_rbt;

typedef struct run {
	char* run;
	unsigned rule_num;
	unsigned run_num;
	bool terminal;
} run;

struct rl {
	run run;
	struct rl* prev;
	struct rl* next;
};
typedef struct rl runlist;

struct rbt_node {
	char bit;
	runlist* head;
	runlist* tail;
	struct rbt_node* left;
	struct rbt_node* right;
};
typedef struct rbt_node rbt;

runlist* add_run_to_RBT_node(runlist*, runlist*, run);
rbt* make_RBT_node(char, run);
rbt** make_Run_Based_Trie(char**);

#endif
