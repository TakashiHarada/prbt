/* column_switching.c */

#include <column_switching.h>

void replace_string(unsigned i, unsigned j, char* s)
{
  char tmp;
  tmp = s[i];
  s[i] = s[j];
  s[j] = tmp;
}

void replace_array(unsigned i, unsigned j, unsigned* P)
{
  unsigned tmp;
  tmp = P[i];
  P[i] = P[j];
  P[j] = tmp;
}

int search_only_s2_is_zo(char* s1, char* s2, unsigned i)
{
  unsigned w = strlen(s1);
  unsigned j;
  for (j = i; j < w; ++j)
    if (s1[j] == '*' && s2[j] != '*')
      return j;

  return -1;
}

int search_both_s1_and_s2_zo(char* s1, char* s2, unsigned i)
{
  unsigned w = strlen(s1);
  unsigned j;
  for (j = i; j < w; ++j)
    if (s1[j] != '*' && s2[j] != '*')
      return j;

  return -1;
}

int search_only_s1_is_zo(char* s1, char* s2, unsigned i)
{
  unsigned w = strlen(s1);
  unsigned j;
  for (j = i; j < w; ++j)
    if (s1[j] != '*' && s2[j] == '*')
      return j;

  return -1;
}

void column_switching2rules(char** R, unsigned* P)
{
  char *s1, *s2;
  s1 = R[0], s2 = R[1];
  {
    unsigned i;
    int j;
    for (i = 0; i < _w; ++i) {
      j = search_only_s1_is_zo(s1, s2, i);
      if (-1 != j) {
	replace_string(i, j, s1);
	replace_string(i, j, s2);
	replace_array(i, j, P);
	continue;
      }
      j = search_both_s1_and_s2_zo(s1, s2, i);
      if (-1 != j) {
	replace_string(i, j, s1);
	replace_string(i, j, s2);
	replace_array(i, j, P);
	continue;
      }
      j = search_only_s2_is_zo(s1, s2, i);
      if (-1 != j) {
	replace_string(i, j, s1);
	replace_string(i, j, s2);
	replace_array(i, j, P);
      }
    }
  }
}

int find_zo(char* rule, unsigned i)
{
  unsigned w = strlen(rule);
  unsigned j;
  for (j = i; j < w; ++j)
    if (rule[j] != '*')
      return j;
  return -1;
}

void column_switching_a_rule(char* rule, unsigned* P)
{
  unsigned i;
  int j;
  for (i = 0; i < _w; ++i) {
    j = find_zo(rule, i);
    if (-1 != j) {
      replace_string(i, j, rule);
      replace_array(i, j, P);
      continue;
    }
  }
}

unsigned** column_switching(char*** RR)
{
 unsigned n = (_n+1)/2;
 unsigned** P = (unsigned**)malloc(n*sizeof(unsigned*));
 {
   unsigned i, j;
   for (i = 0; i < n; ++i) {
     P[i] = (unsigned*)malloc(_w*sizeof(unsigned));
     for (j = 0; j < _w; ++j)
       P[i][j] = j+1;
   }
 }
 {
   unsigned i;
   if (_n%2==0)
     for (i = 0; i < n; ++i)
       column_switching2rules(RR[i], P[i]);
   else {
     for (i = 0; i < n-1; ++i)
       column_switching2rules(RR[i], P[i]);
     column_switching_a_rule(RR[n-1][0],P[n-1]);
   }
 }

 return P;
}

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

csprbt* make_column_switched_Pointed_Run_Based_Trie(char **rulelist)
{
  char*** RR = devide_rulelist_to_2rulelists(rulelist);
  unsigned** P = column_switching(RR);
  unsigned n = (_n+1)/2;
  prbt*** PTT = (prbt***)malloc(n*sizeof(prbt**));
  {
    unsigned i;
    if (_n%2==0) {
      for (i = 0; i < n; ++i)
	PTT[i] = make_Pointed_Run_Based_Trie_n(RR[i], 2);
    }
    else {
      for (i = 0; i < n-1; ++i)
	PTT[i] = make_Pointed_Run_Based_Trie_n(RR[i], 2);
      PTT[n-1] = make_Pointed_Run_Based_Trie_n(RR[n-1], 1);
    }
  }

  csprbt* CSPT = (csprbt*)malloc(sizeof(csprbt));
  CSPT->P = P;
  CSPT->PRBTs = PTT;
  return CSPT;
}

void free_permutation(unsigned** P)
{
  unsigned i, j, n = (_n+1)/2;
  for (i = 0; i < n; ++i) {
    for (j = 0; j < _w; ++j)
      printf("%d ", P[i][j]);
    putchar('\n');
    free(P[i]);
  }
  free(P);
}


void free2rulelists(char*** RR)
{
  {
    unsigned i, j, n = (_n+1)/2;
    //printf("%d hoge\n", _n);
    if (_n%2 == 0) {
      for (i = 0; i < n; ++i)
  	for (j = 0; j < 2; ++j) {
  	  printf("%s\n", RR[i][j]);
	  free(RR[i][j]);
	}
    }
    else {
      for (i = 0; i < n-1; ++i)
  	for (j = 0; j < 2; ++j) {
  	  printf("%s\n", RR[i][j]);
	  free(RR[i][j]);
	}
      printf("%s\n", RR[n-1][0]);
      free(RR[n-1][0]);
    }
    for (i = 0; i < n; ++i)
      free(RR[i]);
  }
  free(RR);
}
