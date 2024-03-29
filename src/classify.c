/* classify.c */

#include <classify.h>

bool match_rule_and_header(char* rule, char* header)
{
  unsigned i;
  for (i = 0; i < _w; ++i) {
    ++_compare_number_sequential_search;
    if (rule[i] != '*' && rule[i] != header[i])
      return false;
  }

  return true;
}

unsigned sequential_search(char** rulelist, char* header)
{
  unsigned i;
  for (i = 0; i < _n; ++i)
    if (match_rule_and_header(rulelist[i], header)) {
      break;
    }

  // printf("%s --> %2d\n", header, i+1);
  return i+1;
  
  /* char defaultrule[_w+1]; */
  /* unsigned j; */
  /* for (j = 0; j < _w; ++j) */
  /*   defaultrule[j] = '*'; */
  /* defaultrule[_w] = '\0'; */

  /*
    if (i != _n)
    printf("%s -> rule[%2d] %s\n", header, i+1, rulelist[i]);
    else
    printf("%s -> rule[%2d] %s\n", header, _n+1, defaultrule);
    printf("%s --> %2d\n", header, i+1);
  */
}

void do_sequential_search(char** rulelist, char** headerlist)
{
  printf("==================== Sequential Search ==================== \n");
  struct timeval start_time, end_time;
  double sec_time_of_day;
  unsigned i;
  _compare_number_sequential_search = 0;
  gettimeofday(&start_time, NULL);
  for (i = 0; i < _hn; ++i)
    sequential_search(rulelist, headerlist[i]);
  gettimeofday(&end_time, NULL);
  // printf("=========================================================== \n");
  sec_time_of_day = (end_time.tv_sec - start_time.tv_sec) 
    + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
  printf("Search Time : %f\n", sec_time_of_day);
  printf("Total       : %ld\n", _compare_number_sequential_search);
}

unsigned simple_search(rbt** T, char* header, unsigned* A)
{

  rbt* ptr;
  runlist* it;
  unsigned candidate = _n+1;

  unsigned k, i, s, t;
  for (k = 0; k < _w; ++k) {
    ptr = T[k];
    for (i = k; i < _w; ++i) {
      ++_trav_rbt; // 辿れるか
      if ('0' == header[i]) {
	++_trav_rbt; // 辿れるか
	if (NULL != ptr->left) { ptr = ptr->left; }
	else { break; }
      }
      else {
	++_trav_rbt; // 辿れるか
	if (NULL != ptr->right) { ptr = ptr->right; }
	else { break; }
      }
      if (NULL != ptr->rs)
	for (it = ptr->rs; NULL != it; it = it->next) {
	  s = it->run.rule_num;
	  t = it->run.run_num;
	  ++_arr_rbt; // 順番通りに合致しているかをチェック
	  if (A[s] == t-1) {
	    A[s] = t;
	    ++_is_last_run_rbt; // 最後の連かどうかをチェック
	    if (it->run.terminal) {
	      ++_cand_rbt; // 現在の最優先候補との比較
	      if (s < candidate) { candidate = s; }
	    }
	  }
	}
    }
  }

  return candidate;
  //printf("%s --> %2d\n", header, candidate);
}

void do_simple_search(rbt** T, char** headerlist)
{
  printf("====================== Simple Search ======================\n");
  unsigned A[_n+1];
  unsigned i;
  struct timeval start_time, end_time;
  double sec_time_of_day;

  _trav_rbt = _arr_rbt = _cand_rbt = _is_last_run_rbt = 0;

  gettimeofday(&start_time, NULL);
  for (i = 0; i < _hn; ++i) {
    memset(A+1, 0, _n*sizeof(unsigned));
    simple_search(T, headerlist[i], A);
    // printf("%s --> %3d\n", headerlist[i], simple_search(T, headerlist[i], A));
  }
  gettimeofday(&end_time, NULL);
  // printf("===========================================================\n");
  sec_time_of_day = (end_time.tv_sec - start_time.tv_sec) 
    + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
  printf("Search Time : %f\n", sec_time_of_day);
  printf("Traverse  : %ld\n", _trav_rbt);
  printf("Array     : %ld\n", _arr_rbt);
  printf("Last Run? : %ld\n", _is_last_run_rbt);
  printf("Candidate : %ld\n", _cand_rbt);
  printf("Total     : %ld\n", _trav_rbt + _arr_rbt + _is_last_run_rbt + _cand_rbt);
}

unsigned pointer_search(prbt* PT, char* header, unsigned* A)
{

  prbt* ptr = PT;
  runlist* it;
  unsigned candidate = _n+1;
	
  unsigned i, j, k;
  for (i = 0; i < _w; ++i) {
    ++_trav_prbt; // 辿れるか
    if ('0' == header[i]) {
      ++_trav_prbt; // 辿れるか
      if (NULL != ptr->pleft) { ptr = ptr->pleft; }
      else { break; }
    }
    else {
      ++_trav_prbt; // 辿れるか
      if (NULL != ptr->pright) { ptr = ptr->pright; }
      else { break; }
    }
    if (NULL != ptr->rs)
      for (it = ptr->rs; NULL != it; it = it->next) {
	j = it->run.rule_num;
	k = it->run.run_num;
	++_arr_prbt; // 順番通りに合致しているかをチェック
	if (A[j] == k-1) {
	  A[j] = k;
	  ++_is_last_run_prbt; // 最後の連かどうかをチェック
	  if (it->run.terminal) {
	    ++_cand_prbt; // 現在の最優先候補との比較
	    if (j < candidate) { candidate = j; }
	  }
	}
      }
  }

  //printf("%s --> %2d\n", header, candidate);
  return candidate;
}

void do_pointer_search(prbt* PT, char** headerlist)
{
  unsigned A[_n+1];
  struct timeval start_time, end_time;
  double sec_time_of_day;
  unsigned i;
  printf("============== Pointed Run-Based Trie Search ==============\n");

  _trav_prbt = _arr_prbt = _cand_prbt = _is_last_run_prbt = 0;

  gettimeofday(&start_time, NULL);
  for (i = 0; i < _hn; ++i) {
    memset(A+1, 0, _n*sizeof(unsigned));
    pointer_search(PT, headerlist[i], A);
    // printf("%s --> %3d\n", headerlist[i], pointer_search(PT, headerlist[i], A));
  }
  gettimeofday(&end_time, NULL);
  // printf("===========================================================\n");
  sec_time_of_day = (end_time.tv_sec - start_time.tv_sec) 
    + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
  printf("Search Time : %f\n", sec_time_of_day);
  printf("Traverse  : %ld\n", _trav_prbt);
  printf("Array     : %ld\n", _arr_prbt);
  printf("Last Run? : %ld\n", _is_last_run_prbt);
  printf("Candidate : %ld\n", _cand_prbt);
  printf("Total     : %ld\n", _trav_prbt + _arr_prbt + _is_last_run_prbt + _cand_prbt);
}

unsigned count_run_number(char*rule)
{
  char tmp = '*';
  unsigned i = 0;
  unsigned m = 0;

  while (rule[i] != '\0') {
    if ('*' != rule[i] && '*' == tmp ) {
      ++m;
    }
    tmp = rule[i];
    ++i;
  }

  return m;
}

void count_run_number_on_rule_in_rulelist(char** rulelist, unsigned* R)
{
  unsigned i;
  for (i = 1; i <= _n; ++i)
    R[i] = count_run_number(rulelist[i-1]);
  //printf("%s %d\n", rulelist[i-1], R[i]);
}

bool classbench_compare(rrule* rule, char* header, unsigned* len, unsigned* start)
{
  unsigned i, j, k, h;
  str_list* it;

  for (i = 0; i < 2; ++i) {
    it = (rule->f)[i];
    j = 0;
    h = start[i];
    k = h + len[i];
    // printf("len[%d] = %d, start[%d] = %d\n", i, len[i], i, start[i]);
    while (h < k) {
      ++_compare_number_sequential_search;
      if (it->elem[j] != header[h] && it->elem[j] != '*') { // ここの比較回数を数える
	//printf("it->elem[%d] = %c, header[%d] = %c\n", j, it->elem[j], h, header[h]);
	return false;
      }
      ++j;
      ++h;
    }
  }

  /* here, check the range rule [a,b] */
  bool flag;
  for (i = 2; i < 4; ++i) {
    it = (rule->f)[i];
    flag = true;
    while (NULL != it) {
      j = 0;
      h = start[i];
      k = h + len[i];
      while (h < k) {
	++_compare_number_sequential_search;
	if (it->elem[j] != header[h] && it->elem[j] != '*') // ここの比較回数を数える
	  break;
	++j;
	++h;
      }
      if (h == k) {
	flag = false;
	break;
      }
      it = it->next;
    }
    if (flag)
      return false;
  }

  for (i = 4; i < _d; ++i) {
    it = (rule->f)[i];
    j = 0;
    h = start[i];
    k = h + len[i];
    while (h < k) {
      ++_compare_number_sequential_search;
      if (it->elem[j] != header[h] && it->elem[j] != '*') // ここの比較回数を数える
	return false;
      ++h;
      ++j;
    }
  }

  return true;
}

unsigned classbench_sequential_search(rrule** rulelist, char* header, unsigned* len, unsigned* start)
{
  unsigned i;
  for (i = 0; i < _n; ++i)
    if (classbench_compare(rulelist[i], header, len, start))
      break;

  // printf("%s --> %3d\n", header, i+1);
  return i+1;
}

rrule* convert_string_to_rrule(char* r, unsigned rule_number)
{
  // printf("R[%d]: %s\n", rule_number, r);
  rrule* rule = (rrule*)malloc(sizeof(rrule*));
  rule->number = rule_number;

  str_list *sl = string_to_strings(r);
  sl = delete_newline_strlist(sl);
  unsigned d = sizeofstrlist(sl);
  _d = d;
  rule->f = (str_list**)malloc(d*sizeof(str_list*));

  str_list* it = sl;
  unsigned i = 0;
  while (NULL != it) {
    // printf("[%s]\n", it->elem);
    if (in_hyphen(it->elem)) {
      (rule->f)[i] = range_to_01ms(it->elem);
    } else {
      (rule->f)[i] = new_strlist(it->elem);
    }
    it = it->next;
    ++i;
  }

  /* for (i = 0; i < _d; ++i) { */
  /*   it = (rule->f)[i]; */
  /*   while (NULL != it) { */
  /*     printf("f[%d] = [%s]\n", i, it->elem); */
  /*     it = it->next; */
  /*   } */
  /* } */

  free_strlist(sl);

  return rule;
}

rrule** make_classbench_rulelist(char** rulelist)
{
  unsigned i;
  rrule** list = (rrule**)malloc(sizeof(rrule*)*_n);

  for (i = 0; i < _n; ++i) {
    // printf("Rule[%d] = %s\n", i, rulelist[i]);
    list[i] = convert_string_to_rrule(rulelist[i],i+1);
    /* unsigned j; */
    /* str_list* it; */
    /* for (j = 0; j < _d; ++j) { */
    /*   it = (list[i]->f)[j]; */
    /*   while (NULL != it) { */
    /* 	printf("R[%d]-f[%d] = [%s]\n", i, j, it->elem); */
    /* 	it = it->next; */
    /*   } */
    /* } */
    /* putchar('\n'); */
  }
  return list;
}

void do_classbench_sequential_search(char** rulelist, char** headerlist)
{
  printf("==================== Sequential Search ==================== \n");
  struct timeval start_time, end_time;
  double sec_time_of_day;
  unsigned i;
  rrule** rrulelist = make_classbench_rulelist(rulelist); // convert string to range rule
  _compare_number_sequential_search = 0;

  /* for (i = 0; i < _n; ++i) { */
  /*   unsigned j; */
  /*   str_list* it; */
  /*   for (j = 0; j < _d; ++j) { */
  /*     it = (rrulelist[i]->f)[j]; */
  /*     while (NULL != it) { */
  /*   	printf("R[%d]-f[%d] = [%s]\n", i,j, it->elem); */
  /*   	it = it->next; */
  /*     } */
  /*   } */
  /*   putchar('\n'); */
  /* } */

  unsigned len[] = { 32, 32, 16, 16, 8, 16 }; // ここを求めるプログラムが必要
  unsigned start[] = { 0, 32, 64, 80, 96, 104, 120 }; // ここを求めるプログラムが必要

  gettimeofday(&start_time, NULL);
  for (i = 0; i < _hn; ++i)
    classbench_sequential_search(rrulelist, headerlist[i], len, start);
  gettimeofday(&end_time, NULL);
  // printf("=========================================================== \n");
  sec_time_of_day = (end_time.tv_sec - start_time.tv_sec) 
    + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
  printf("Search Time : %f\n", sec_time_of_day);
  printf("Total       : %ld\n", _compare_number_sequential_search);
}
