/* tools.h */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __PRBT_TOOLS_H__
#define __PRBT_TOOLS_H__

#define LOW 0
#define HIGH 65535
#define BIT_LENGTH 16

#ifndef __cplusplus
typedef enum { false, true } bool; /* not needed for C++ */
#endif

struct sl {
	char** elem;
	struct sl* next;
};
typedef struct sl str_list;

str_list* int_pair_to_01m(unsigned, unsigned, unsigned);
str_list* concat_strlist(str_list*, str_list*);
str_list* range_to_01ms_sub(unsigned, unsigned, unsigned, unsigned);
str_list* range_to_01ms(unsigned, unsigned);

#endif
