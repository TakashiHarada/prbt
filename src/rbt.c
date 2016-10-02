/* rbt.c */

#include <rbt.h>

void free_runlist(runlist* rl)
{
  if (rl == NULL) { return ; }
  runlist* ptr = rl;
  runlist* wptr;
  while (ptr != NULL) {
    wptr = ptr;
    ptr = ptr->next;
    free(wptr);
  }
}

runlist* add_run_to_RBT_node(runlist *rs, run r)
{
  //printf("%s ", run_str);
  runlist* new = (runlist*)malloc(sizeof(runlist));
  unsigned l = strlen(r.run);
  new->run.run = (char*)malloc((l+1)*sizeof(char));
  strcpy(new->run.run,r.run);
  new->run.run[l] = '\0';
  new->run.rule_num = r.rule_num;
  new->run.run_num = r.run_num;
  new->run.trie_number = r.trie_number;
  new->run.terminal = r.terminal;
  new->prev = new -> next = NULL;

  ++_number_of_run_of_rbt;

  runlist* ptr = rs;
  if (NULL == rs) { 
    return new;
  }
  while (NULL != ptr->next) { ptr = ptr->next; }
  ptr->next = new;
  new->prev = ptr;

  return rs;
}

rbt* make_RBT_node(char b)
{
  rbt* node = (rbt*)malloc(sizeof(rbt));
  node->bit = b;
  node->left = NULL;
  node->right = NULL;
  node->rs = NULL;

  return node;
}

void traverse_and_make_RBT_node(rbt* T, run r)
{
  unsigned l = strlen(r.run);
  char* bit_string = (char*)malloc((l+1)*sizeof(char));
  strcpy(bit_string, r.run);
  bit_string[l] = '\0';
  unsigned i;
  rbt* ptr = T;

  for (i = 0; '\0' != bit_string[i]; ++i) {
    if ('0' == r.run[i]) {
      if (NULL == ptr->left) {
	ptr->left = make_RBT_node('0');
	++_number_of_rbt_node;
      }
      ptr = ptr->left;
    } 
    else {
      if (NULL == ptr->right) {
	ptr->right = make_RBT_node('1');
	++_number_of_rbt_node;
      }
      ptr = ptr->right;
    }
  }
  //ptr->head = add_run_to_RBT_node(ptr->head, ptr->tail, r);
  ptr->rs = add_run_to_RBT_node(ptr->rs, r);

  free(bit_string);
}

void add_rule_number(runlist* rs, unsigned i)
{
  if (NULL == rs) { return ; }
  runlist* ptr = rs;
  while (NULL != ptr) {
    ptr->run.rule_num = i;
    ptr = ptr->next;
  }
}

void add_terminal_mark(runlist* rs)
{
  if (NULL == rs) { return ; }
  runlist* ptr = rs;
  while (NULL != ptr->next) {
    ptr = ptr->next;
  }
  ptr->run.terminal = true;
}

runlist* add_run(runlist* rs, char* run_str, unsigned run_num, unsigned tn)
{
  //printf("%s ", run_str);
  runlist* new = (runlist*)malloc(sizeof(runlist));
  new->run.run = (char*)malloc((_w+1)*sizeof(char));
  strcpy(new->run.run,run_str);
  new->run.run[_w] = '\0';
  new->run.rule_num = 0;
  new->run.run_num = run_num;
  new->run.trie_number = tn;
  new->run.terminal = false;
  new->prev = new->next = NULL;

  runlist* ptr = rs;
  if (NULL == rs) { 
    return new;
  }
  while (NULL != ptr->next) { ptr = ptr->next; }
  ptr->next = new;
  new->prev = ptr;
  return rs;
}

runlist* cut_run(char* rule)
{
  runlist* rs = NULL;
  { unsigned i;
    int s = -1, t = -1;
    unsigned run_counter = 0;
    bool sign = false;
    char* buf = (char*)malloc((_w+1)*sizeof(char));
    // printf("%s : ", rule);
    for (i = 0; i < _w; ++i) {
      if ('*' != rule[i]) {
	if (!sign) {
	  s = i+1;
	  ++run_counter;
	  sign = true;
	}
      }
      else if (sign) {
	t = i;
	strncpy(buf, rule+s-1, t-s+1);
	buf[t-s+1] = '\0';
	/* index start from 0. T[0], T[1], ... , T[w-1] */
	rs = add_run(rs, buf, run_counter, s);
	// printf("%s ", buf);
	sign = false;
      }
    }
    if (sign) {
      strncpy(buf, rule+s-1, _w-s+1);
      buf[_w-s+1] = '\0';
      rs = add_run(rs, buf, run_counter, s);
      // printf("%s ", buf);
    }
    free(buf);
  }
  add_terminal_mark(rs);
  return rs;
}

rbt** make_Run_Based_Trie(char** rulelist)
{
  _number_of_rbt_node = 0;
  rbt** T = (rbt**)malloc(_w*sizeof(rbt*));
  /* make a root nodes T[0], T[1], ..., T[w-1] */
  {	unsigned i;
    for (i = 0; i < _w; ++i) {
      T[i] = make_RBT_node('_');
      ++_number_of_rbt_node;
    }
  }

  /* cut run from a rule and add it to an appropriate Trie */
  { unsigned i;
    char copy[_w+1];
    for (i = 0; i < _n; ++i) {
      strcpy(copy,rulelist[i]);
      runlist* runs = cut_run(copy);
      add_rule_number(runs, i+1);
      runlist* ptr = runs;
      while (ptr != NULL) {
	// printf("[str = %4s i = %d rule = %2d run = %d ] ", ptr->run.run, ptr->run.trie_number, ptr->run.rule_num, ptr->run.run_num);
	traverse_and_make_RBT_node(T[ptr->run.trie_number-1], ptr->run);
	ptr = ptr->next;
      }
      //putchar('\n');
      free_runlist(runs);
    }
  }

  printf("A number of Nodes of RBT = %d\n", _number_of_rbt_node);
  printf("A number of Runs  of RBT = %d\n\n", _number_of_run_of_rbt);
  return T;
}

runlist* delete_newline_element(runlist* runs)
{
  runlist *it, *it2;
  if (!strcmp("\n",runs->run.run)) {
    it = runs;
    runs = runs->next;
    free(it);
    return runs;
  }

  it = runs;
  while (NULL != it) {
    it2 = it;
    it = it->next;
    if (NULL != it) {
      if (!strcmp("\n",it->run.run)) {
	it2->next = it->next;
	//free(it);
      }
    }
  }

  return runs;
}

void set_run_number(run* r, unsigned i)
{
  r->run_num = i;
}

bool check_whether_all_mask_rule(char* rule)
{
  unsigned i, l = strlen(rule);
  for (i = 0; i < l; ++i)
    if (rule[i] != '*')
      return false;
  return true;
}

runlist* concat_runlist(runlist* s, runlist* t)
{
   if (NULL == s) {
    if (NULL == t)	// s = NULL and t = NULL (0,0)
      return NULL;
    else	// s = NULL and t /= NULL (0,1)
      return t;
  }
  else if (NULL == t) {	// s /= NULL and t = NULL (1,0)
    return s;
  }

  // s /= NULL and t /= NULL (1,1)
  runlist* it = s;
  while (NULL != it->next)
    it = it->next;
  it->next = t;

  return s;
}

runlist* get_run_from_classbench_field(char* field, unsigned* run_counter, unsigned run_start_point)
{
  if (check_whether_all_mask_rule(field))
    return NULL;

  runlist* rs = NULL;
  unsigned l = strlen(field);

  unsigned i;
  int s = -1, t = -1;
  bool sign = false;
  char* buf = (char*)malloc(sizeof(char)*(1+_w));
  // printf("%s : ", field);

  for (i = 0; i < l; ++i) {
    if ('*' != field[i]) {
      if (!sign) {
	s = i+1;
	++(*run_counter);
	sign = true;
      }
    }
    else if (sign) {
      t = i;
      strncpy(buf, field+s-1, t-s+1);
      buf[t-s+1] = '\0';
      /* index start from 0. T[0], T[1], ... , T[w-1] */
      rs = add_run(rs, buf, (*run_counter), s+run_start_point);
      // printf("%s (%d)", buf, s+run_start_point-1);
      sign = false;
    }
  }
  if (sign) {
    strncpy(buf, field+s-1, _w-s+1);
    buf[_w-s+1] = '\0';
    rs = add_run(rs, buf, (*run_counter), s+run_start_point);
    // printf("%s (%d)", buf, s+run_start_point-1);
  }
  free(buf);
  // putchar('\n');

  return rs;
}

rbt** make_Run_Based_Trie_in_classbench_format(char** rulelist)
{
  _number_of_rbt_node = 0;
  rbt** T = (rbt**)malloc(_w*sizeof(rbt*));
  /* make a root nodes T[0], T[1], ..., T[w-1] */
  {	
    unsigned i;
    for (i = 0; i < _w; ++i) {
      T[i] = make_RBT_node('_');
      ++_number_of_rbt_node;
    }
  }



  /* cut run from a rule and add it to an appropriate Trie */
  { 
    unsigned i, l, run_counter, sp;
    char copy[_capacity+1];
    str_list *sl, *sl2, *it, *it2;
    runlist *runs, *tmp, *ptr;
    for (i = 0; i < _n; ++i) {
      strcpy(copy,rulelist[i]);
      sl = string_to_strings(copy);
      it = sl;
      run_counter = 0;
      // printf("%s\n", rulelist[i]);
      runs = NULL;
      sp = 0;
      while (NULL != it) {
	// printf("%d %s\n", run_counter, it->elem);
	l = strlen(it->elem);
	if (in_hyphen(it->elem)) {
	  it2 = sl2 = range_to_01ms(it->elem);
	  while (NULL != it2) {
	    tmp = get_run_from_classbench_field(it2->elem, &run_counter, sp);
	    if (NULL != tmp && NULL != it2->next)
	      --run_counter;
	    runs = concat_runlist(runs, tmp);
	    it2 = it2->next;
	  }
	  free_strlist(sl2);
	  sp += BIT_LENGTH;
	} else {
	  runs = concat_runlist(runs, get_run_from_classbench_field(it->elem, &run_counter, sp));
	  sp += l;
	}
	it = it->next;
      }
      add_rule_number(runs, i+1);
      runs = delete_newline_element(runs);
      add_terminal_mark(runs); // 最後の連が複数ある場合に対してデバッグが必要 20161002
      ptr = runs;
      while (ptr != NULL) {
      	traverse_and_make_RBT_node(T[ptr->run.trie_number-1], ptr->run);
      	/* if (ptr->run.terminal) */
      	/*   printf("[str = %32s i = %3d rule = %3d run = %2d  true]\n", ptr->run.run, ptr->run.trie_number, ptr->run.rule_num, ptr->run.run_num); */
      	/* else */
      	/*   printf("[str = %32s i = %3d rule = %3d run = %2d false]\n", ptr->run.run, ptr->run.trie_number, ptr->run.rule_num, ptr->run.run_num); */
      	ptr = ptr->next;
      }
      free_runlist(runs);
      free_strlist(sl);
      // putchar('\n');
    }
  }

  printf("A number of Nodes of RBT = %d\n", _number_of_rbt_node);
  printf("A number of Runs  of RBT = %d\n\n", _number_of_run_of_rbt);
  return T;
}

void free_traverse_RBT(rbt* T)
{
  if (NULL == T) { return; }
  free_traverse_RBT(T->left);
  free_traverse_RBT(T->right);

  if (NULL != T->rs) {
    runlist* ptr = T->rs;
    runlist* ptr2;
    while (NULL != ptr) {
      // printf("free run (%s, %2d, %d)\n", ptr->run.run, ptr->run.rule_num, ptr->run.run_num);
      ptr2 = ptr;
      ptr = ptr->next;
      free(ptr2);
    }
  }

  if (NULL != T->left)
    free(T->left);
  if (NULL != T->right)
    free(T->right);
}

void free_RBT(rbt** T)
{
  { unsigned i;
    for (i = 0; i < _w; ++i) {
      // printf("===== free T[%2d] =====\n", i);
      free_traverse_RBT(T[i]);
    }
  }
}
