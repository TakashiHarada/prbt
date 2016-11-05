/* column_switching.c */

#include <column_switching.h>

// each rulelist contains at most 2 rules
// RR[1] = (R[1],R[2]), RR[2] = (R[3],R[4]), .., RR[n/2] = (R[n-1],R[n])
char*** devide_rulelist_to_2rulelists(char** rulelist)
{
  /* copy rulest to 2 dimension array A[n][w] */
  char** A = (char**)malloc(_n*sizeof(char*));
  {
    unsigned i;
    for (i = 0; i < _n; ++i) {
      A[i] = (char*)malloc((_w+1)*sizeof(char)); // +1 for '\0'
      strcpy(A[i],rulelist[i]);
      printf("%s\n", A[i]);
    }
  }
  return NULL;
}

prbt*** make_column_switched_Pointed_Run_Based_Trie(char **rulelist)
{
  char*** rulelists = devide_rulelist_to_2rulelists(rulelist);
  return NULL;
}
