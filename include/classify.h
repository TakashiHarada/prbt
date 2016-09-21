/* classify.h */

#ifndef __PRBT_CLASSIFY_H__
#define __PRBT_CLASSIFY_H__

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

#ifndef __PRBT_PRBT_H__
#include <prbt.h>
#endif

#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

unsigned _compare_priority_in_pointer_search;
unsigned _compare_priority_in_simple_search;
unsigned long _compare_number_sequential_search;
unsigned _compare_number_simple_search;
unsigned _traverse_number_simple_search;
unsigned _compare_number_pointer_search;
unsigned _traverse_number_pointer_search;

unsigned pointer_search2(prbt**, char*, unsigned*, unsigned*);
unsigned simple_search2(rbt**, char*, unsigned*, unsigned*);
unsigned count_run_number(char*);
void count_run_number_on_rule_in_rulelist(char**, unsigned*);
void do_simple_search2(rbt**, char**, char**);
void do_pointer_search2(prbt**, char**, char**);

unsigned pointer_search(prbt*, char*, unsigned*);
unsigned simple_search(rbt**, char*, unsigned*);
unsigned sequential_search(char **, char*);
void do_pointer_search(prbt*, char**);
void do_simple_search(rbt**, char**);
void do_sequential_search(char **, char**);

#endif
