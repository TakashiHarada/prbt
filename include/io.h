/* io.h */

#ifndef __PRBT_IO_H__
#define __PRBT_IO_H__

#ifndef __PRBT_TOOLS_H__
#include <tools.h>
#endif

#ifndef __PRBT_CONST_H__
#include <const.h>
#endif

struct range_rule {
  unsigned number;
  str_list** f;
};
typedef struct range_rule rrule;

unsigned get_header_length_in_bitstring_format(char*);
char** read_classbench_header_list(char*);
bool in_hyphen(char*);
unsigned get_rule_length_in_bitstring_format(char*);
char** read_classbench_rule_list(char*);
char** read_header_list(char*);
char** read_rule_list(char*);

#endif
