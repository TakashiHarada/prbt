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

#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

void sequential_search(char **, char*);
void do_sequential_search(char **, char**);

#endif