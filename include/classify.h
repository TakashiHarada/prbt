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

#ifndef __PRBT_COLUMN_SWITCHING_H__
#include <column_switching.h>
#endif

#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

unsigned long _compare_number_sequential_search;

unsigned long _trav_prbt;
unsigned long _arr_prbt;
unsigned long _cand_prbt;
unsigned long _is_last_run_prbt;

unsigned long _trav_rbt;
unsigned long _arr_rbt;
unsigned long _cand_rbt;
unsigned long _is_last_run_rbt;

unsigned count_run_number(char*);
void count_run_number_on_rule_in_rulelist(char**, unsigned*);
unsigned csprbt_search(csprbt*, char*);
unsigned pointer_search(prbt*, char*, unsigned*);
unsigned simple_search(rbt**, char*, unsigned*);
unsigned sequential_search(char **, char*);
void do_csprbt_search(csprbt*, char**);
void do_pointer_search(prbt*, char**);
void do_simple_search(rbt**, char**);
void do_sequential_search(char **, char**);


rrule* convert_string_to_rrule(char*, unsigned);
bool classbench_compare(rrule*, char*, unsigned*, unsigned*);
unsigned classbench_sequential_search(rrule**, char*, unsigned*, unsigned*);
void do_classbench_sequential_search(char**, char**);

#endif
