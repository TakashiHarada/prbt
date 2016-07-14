/* classify.c */

#include <classify.h>

bool match_rule_and_header(char* rule, char* header)
{
  unsigned i;
  for (i = 0; i < _w; ++i)
    if (rule[i] != '*' && rule[i] != header[i])
      return false;

  return true;
}

void sequential_search(char** rulelist, char* header)
{
  unsigned i;
  for (i = 0; i < _n; ++i)
    if (match_rule_and_header(rulelist[i], header)) {
      break;
    }

	/*	
  char defaultrule[_w+1];
  unsigned j;
  for (j = 0; j < _w; ++j)
  	defaultrule[j] = '*';
  	defaultrule[_w] = '\0';
	*/

	/*
  if (i != _n)
  //printf("%s -> rule[%2d] %s\n", header, i+1, rulelist[i]);
  	printf("%s --> %2d\n", header, i+1);
  else
  //printf("%s -> rule[%2d] %s\n", header, _n+1, defaultrule);
  	printf("%s --> %2d\n", header, i+1);
	*/
}

void do_sequential_search(char** rulelist, char** headerlist)
{
  printf("==================== Sequential Search ==================== \n");
  struct timeval start_time, end_time;
  double sec_time_of_day;
  unsigned i;
  gettimeofday(&start_time, NULL);
  for (i = 0; i < _hn; ++i)
    sequential_search(rulelist, headerlist[i]);
  gettimeofday(&end_time, NULL);
  printf("=========================================================== \n");
  sec_time_of_day = (end_time.tv_sec - start_time.tv_sec) 
    + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
  printf("w = %d, n = %d, number of header = %d -- %f\n", _w, _n, _hn, sec_time_of_day);
}

void simple_search(rbt** T, char* header, unsigned* A)
{
  rbt* ptr;
  runlist* it;
	unsigned priority = _n+1;

  { unsigned k, i, s, t;
    for (k = 0; k < _w; ++k) {
      ptr = T[k];
      for (i = k; i < _w; ++i) {
	if ('0' == header[i]) {
	  if (NULL != ptr->left) { ptr = ptr->left; }
	  else { break; }
	}
	else {
	  if (NULL != ptr->right) { ptr = ptr->right; }
	  else { break; }
	}
	if (NULL != ptr->rs)
	  for (it = ptr->rs; NULL != it; it = it->next) {
	    s = it->run.rule_num;
	    t = it->run.run_num;
			++_compare_number_simple_search;
	    if (A[s] == t-1) {
	      A[s] = t;
	      if (it->run.terminal)
		if (s < priority) { priority = s; }
	    }
	  }
      }
    }
  }
  //printf("%s --> %2d\n", header, priority);
}

void do_simple_search(rbt** T, char** headerlist)
{
  printf("====================== Simple Search ======================\n");
  unsigned A[_n+1];
  unsigned i;
  struct timeval start_time, end_time;
  double sec_time_of_day;
	_compare_number_simple_search = 0;
  gettimeofday(&start_time, NULL);
  for (i = 0; i < _hn; ++i) {
    memset(A+1, 0, _n*sizeof(unsigned));
    simple_search(T, headerlist[i], A);
  }
  gettimeofday(&end_time, NULL);
  printf("===========================================================\n");
  sec_time_of_day = (end_time.tv_sec - start_time.tv_sec) 
    + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
  printf("w = %d, n = %d, number of header = %d -- %f, %d\n", _w, _n, _hn, sec_time_of_day, _compare_number_simple_search);
}

void pointer_search(prbt** PT, char* header, unsigned* A)
{
  prbt* ptr = PT[0];
  runlist* it;
	unsigned priority = _n+1;

  { unsigned i, j, k;
    for (i = 0; i < _w; ++i) {
      if ('0' == header[i]) {
	if (NULL != ptr->pleft) { ptr = ptr->pleft; }
	else { break; }
      }
      else {
	if (NULL != ptr->pright) { ptr = ptr->pright; }
	else { break; }
      }
      if (NULL != ptr->rs)
	for (it = ptr->rs; NULL != it; it = it->next) {
	  j = it->run.rule_num;
	  k = it->run.run_num;
		++_compare_number_pointer_search;
	  if (A[j] == k-1) {
	    A[j] = k;
	    if (it->run.terminal)
	      if (j < priority) { priority = j; }
	  }
	}
    }
  }
  //printf("%s --> %2d\n", header, priority);
}

void do_pointer_search(prbt** PT, char** headerlist)
{
  unsigned A[_n+1];
  struct timeval start_time, end_time;
  double sec_time_of_day;
  unsigned i;
  printf("============== Pointed Run-Based Trie Search ==============\n");
	_compare_number_pointer_search = 0;
  gettimeofday(&start_time, NULL);
  for (i = 0; i < _hn; ++i) {
		memset(A+1, 0, _n*sizeof(unsigned));
    pointer_search(PT, headerlist[i], A);
  }
  printf("===========================================================\n");
  gettimeofday(&end_time, NULL);
  sec_time_of_day = (end_time.tv_sec - start_time.tv_sec) 
    + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
  printf("w = %d, n = %d, number of header = %d -- %f, %d\n", _w, _n, _hn, sec_time_of_day, _compare_number_pointer_search);
}
