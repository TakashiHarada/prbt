/* column_switching.c */

#include <column_switching.h>

// each rulelist contains at most 2 rules
// RR[1] = (R[1],R[2]), RR[2] = (R[3],R[4]), .., RR[n/2] = (R[n-1],R[n])
char*** devide_rulelist_to_2rulelists(char** rulelist)
{
  unsigned n = (_n+1)/2;
  char*** RR = (char***)malloc(n*sizeof(char**));

  {
    unsigned i, j, k;
    if (_n%2==0) {
      for (i = 0, k = 0; i < n; ++i) {
	RR[i] = (char**)malloc(2*sizeof(char*));
	for (j = 0; j < 2; ++j) {
	  RR[i][j] = (char*)malloc((_w+1)*sizeof(char));
	  strcpy(RR[i][j], rulelist[k]);
	  ++k;
	}
      }
    }
    else {
      for (i = 0, k = 0; i < n-1; ++i) {
	RR[i] = (char**)malloc(2*sizeof(char*));
	for (j = 0; j < 2; ++j) {
	  RR[i][j] = (char*)malloc((_w+1)*sizeof(char));
	  strcpy(RR[i][j], rulelist[k]);
	  ++k;
	}
      }
      RR[n-1] = (char**)malloc(sizeof(char*));
      RR[n-1][0] = (char*)malloc((_w+1)*sizeof(char));
      strcpy(RR[n-1][0], rulelist[k]);
    }
  }

  return RR;
}

prbt*** make_column_switched_Pointed_Run_Based_Trie(char **rulelist)
{
  char*** rulelists = devide_rulelist_to_2rulelists(rulelist);
  {
    unsigned i, j, n = (_n+1)/2;
    printf("%d hoge\n", _n);
    if (_n%2 == 0) {
      for (i = 0; i < n; ++i)
  	for (j = 0; j < 2; ++j)
  	  printf("%s\n", rulelists[i][j]);
    }
    else {
      for (i = 0; i < n-1; ++i)
  	for (j = 0; j < 2; ++j)
  	  printf("%s\n", rulelists[i][j]);
      printf("%s\n", rulelists[n-1][0]);
    }
  }
  return NULL;
}
