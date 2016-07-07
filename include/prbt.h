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

struct prbt_node {
	char bit;
	runlist* rs;
	struct prbt_node* left;
	struct prbt_node* right;
};
typedef struct prbt_node prbt;

unsigned _number_of_prbt;

void traverse_and_make_backbone_PRBT(prbt*, run);
prbt* make_PRBT_node(char);
prbt** make_Pointed_Run_Based_Trie(char**);
void free_PRBT(prbt**);

#endif