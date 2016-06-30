/* io.h */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __PRBT_TOOLS_H__
#include <tools.h>
#endif

#ifndef __PRBT_CONST_H__
#include <const.h>
#endif

#ifndef __PRBT_IO_H__
#define __PRBT_IO_H__

char** read_header_list(char*);
char** read_rule_list(char*);

#endif
