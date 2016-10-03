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

unsigned _number_of_rbt_node;
unsigned _number_of_run_of_rbt;

typedef struct run {
  char* run;
  unsigned rule_num;
  unsigned run_num;
  unsigned trie_number;
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
  runlist* rs;
  struct rbt_node* left;
  struct rbt_node* right;
};
typedef struct rbt_node rbt;

void free_runlist(runlist*);
void add_rule_number(runlist*, unsigned);
runlist* add_run_to_RBT_node(runlist*, run);
void traverse_and_make_RBT_node(rbt*, run);
void add_terminal_mark(runlist*);
runlist* add_run(runlist*, char*, unsigned, unsigned);
runlist* cut_run(char*);
rbt* make_RBT_node(char);
rbt** make_Run_Based_Trie(char**);

runlist* concat_runlist(runlist*, runlist*);
void set_run_number(run* r, unsigned i);
runlist* get_run_from_classbench_field(char*, unsigned*, unsigned);
rbt** make_Run_Based_Trie_in_classbench_format(char**);
runlist* delete_newline_element(runlist*);

void free_traverse_RBT(rbt*);
void free_RBT(rbt**);

#endif
