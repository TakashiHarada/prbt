/* prbt.h */

#ifndef __PRBT_PRBT_H__
#define __PRBT_PRBT_H__

#ifndef __PRBT_CONST_H__
#include <const.h>
#endif

#ifndef __PRBT_TOOLS_H__
#include <tools.h>
#endif

#ifndef __PRBT_IO_H__
#include <io.h>
#endif

#ifndef __PRBT_RBT_H__
#include <rbt.h>
#endif

unsigned _number_of_prbt_node;
unsigned _number_of_run_of_prbt;

struct prbt_node {
	char bit;
	runlist* rs;
	struct prbt_node* left;
	struct prbt_node* right;
	/* following are for Pointed Run-Based Trie Search */
	char* label; 
	unsigned trie_number;
	struct prbt_node* pleft;
	struct prbt_node* pright;
};
typedef struct prbt_node prbt;

unsigned _number_of_prbt;

void traverse_PT(prbt*);
void traverse_PRBT(prbt**);
runlist* copy_run(runlist*, runlist*);
void low_trie_traverse(prbt*, prbt**);
void lower_trie_traverse_via_label_of_runs_on_higer_trie(prbt*, prbt**);
void traverse_and_make_backbone_PRBT(prbt*, run);
prbt* make_PRBT_node(char, char*, unsigned);
prbt** make_Pointed_Run_Based_Trie(char**);
void free_PRBT(prbt**);

#endif
