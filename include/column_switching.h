/* column_switching.h */

#ifndef __PRBT_COLUMN_SWITCHING_H__
#define __PRBT_COLUMN_SWITCHING_H__

#ifndef __PRBT_TOOLS_H__
#include <tools.h>
#endif

#ifndef __PRBT_CONST_H__
#include <const.h>
#endif

#ifndef __PRBT_IO_H__
#include <io.h>
#endif

#ifndef __PRBT_RBT_H__
#include <rbt.h>
#endif

#ifndef __PRBT_PRBT_H__
#include <prbt.h>
#endif

struct column_switched_Pointed_Run_Based_Trie {
  unsigned** P; // for permutation of each rulelist
  prbt*** PRBTs;
};
typedef struct column_switched_Pointed_Run_Based_Trie csprbt;

void column_switching2rules(char**, unsigned*);
unsigned** column_switching(char***);
char*** devide_rulelist_to_2rulelists(char**);
csprbt* make_column_switched_Pointed_Run_Based_Trie(char **);
void free2rulelists(char***);
void free_permutation(unsigned**);
#endif
