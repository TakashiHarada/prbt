/* tools.c */

#include <tools.h>

unsigned sizeofstrlist(str_list* sl)
{
  unsigned i = 0;
  str_list* it;
  for (it = sl; NULL != it; it = it->next)
    ++i;

  return i;
}

str_list* delete_newline_strlist(str_list* sl)
{
  str_list *it, *it2;
  if (!strcmp("\n", sl->elem)) {
    it = sl;
    sl = sl->next;
    free(it);
    return sl;
  }
  
  it = sl;
  while (NULL != it) {
    it2 = it;
    it = it->next;
    if (NULL != it) {
      if(!strcmp("\n", it->elem)) {
	it2->next = it->next;
	free(it);
      }
    }
  }

  return sl;
}

str_list* delete_strlist_element(str_list* strings, str_list* deleted)
{
  str_list *it, *it2;
  if (strings == deleted) {
    it = strings->next;
    free(strings);
    return it;
  }

  it = strings;  
  while (NULL != it) {
    it2 = it;
    if (it == deleted) {
      it2->next = it->next;
      //free(it->elem);
      //free(it);
      break;
    }
    it = it->next;
  }

  return strings;
}

bool in_newline(char* s)
{
  unsigned i, l = strlen(s);
  for (i = 0; i < l; ++i)
    if ('\n' == s[i])
      return true;
  return false;
}

/* "aa bb cc" => ptr->"aa"->"bb"->"cc"->NULL */
str_list* string_to_strings(char* rule)
{
  str_list* strings = NULL;

  char* copy = (char*)malloc(sizeof(char)*(strlen(rule)));
  strcpy(copy,rule);
  char* f;

  f = strtok(copy, " ");
  strings = concat_strlist(strings,new_strlist(f));
  while (NULL != f) {
    f = strtok(NULL, " ");
    if (NULL != f) {
      strings = concat_strlist(strings,new_strlist(f));
    }
  }

  free(copy);
  return strings;
}

str_list* concat_strlist(str_list* s, str_list* t)
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
  str_list* it = s;
  while (NULL != it->next)
    it = it->next;
  it->next = t;

  return s;
}

str_list* new_strlist(char* s)
{
  str_list* new = (str_list*)malloc(sizeof(str_list));
  new->elem = (char*)malloc((sizeof(char))*strlen(s)+1);
  strcpy(new->elem,s);
  new->next = NULL;

  return new;
}

str_list* int_pair_to_01m(unsigned a, unsigned b, unsigned w)
{
  char* bin = (char*)malloc(w*sizeof(char)+1);

  double a1 = a, b1 = b, l;
  int d;
  l = log2(b1-a1+1);
  d = (int)l;

  // printf("a = %d, b = %d, d = %d\n", a, b, d);
  int i;
  for (i = w-1; i>=0; --i) {
    // printf("%d", (a >> i) & 1);
    // putchar(48+((a >> i) & 1));
    bin[w-i-1] = 48 + ((a>>i)&1);
  }
  bin[w] = '\0';

  for (i = 0; i < d; ++i) {
    bin[w-i-1] = '*';
  }
  //putchar('\n');
  //printf("%s\n",bin);

  return new_strlist(bin);
}

str_list* range_to_01ms_sub(unsigned a, unsigned b, unsigned low, unsigned high)
{
  unsigned m = (low+high-1)/2;
  unsigned n = (low+high+1)/2;
  // printf("a = %d, b = %d, low = %d, high = %d, m = %d, n = %d\n", a, b, low, high, m, n);

  if (a == low && b == high) 
    return int_pair_to_01m(a,b,BIT_LENGTH);
  else if (b <= m) 
    return range_to_01ms_sub(a,b,low,m);
  else if (a <= m && n <= b)
    return concat_strlist(range_to_01ms_sub(a,m,low,m),range_to_01ms_sub(n,b,n,high));
  else 
    return range_to_01ms_sub(a,b,n,high);

  return NULL;
}

/* LOW (=0) and HIGH (=65535) are predefined in the tool.h

     a-b  => 010101..10**, 111101..1111, ...
e.g. 3-17 => 0000000000000011,00000000000001**,0000000000001***,000000000001000*
   
*/
str_list* range_to_01ms(char* rule)
{
  char *num;
  unsigned a, b;
  num = strtok(rule,"-");
  a = (unsigned)atoi(num);
  num = strtok(NULL, "");
  b = (unsigned)atoi(num);
  return range_to_01ms_sub(a,b,LOW,HIGH);
}

void free_strlist(str_list* sl)
{
  str_list *it = sl, *tmp;
  while (NULL != it) {
    tmp = it;
    it = it->next;
    free(tmp->elem);
    free(tmp);
  }
}
