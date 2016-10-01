/* main.c */

#include <main.h>

int main(int argc, char** argv)
{
  char** rulelist;
  char** headerlist;
  rbt** T;
  prbt** PT;
  bool classbench_flag = false;

  /* check arguments */
  if (!strcmp("-c",argv[1])) { 
    /* input rulelist format is class bench like format and separeted by 6 fields 
       Source Address, Destination Address, Source Port, Destination Port, Protocol, Flag */
    char s[] = "67-75";

    classbench_flag = true;

    str_list* sl = range_to_01ms(3,17);
    str_list* it = sl;
    while (it != NULL) {
      printf("%s\n", it->elem);
      it = it->next;
    }
    /* if ((headerlist = read_classbench_header_list(argv[3])) == NULL) { */
    /*   fprintf(stderr, "Can't read an input header-list file\n"); */
    /*   exit(1); */
    /* } */
    exit(1);

  } else if (argc == 3) {
    /* read rule-list and header-list files */
    if ((rulelist = read_rule_list(argv[1])) == NULL) {
      fprintf(stderr, "Can't read an input rule-list file\n");
      return 1;
      exit(1);
    }
  
    if ((headerlist = read_header_list(argv[2])) == NULL) {
      fprintf(stderr, "Can't read an input header-list file\n");
      exit(1);
    }
  
    /* make a Run-Based Trie */
    T = make_Run_Based_Trie(rulelist);
  
    /* make a Pointed Run-Based Trie */
    PT = make_Pointed_Run_Based_Trie(rulelist);
    // traverse_PRBT(PT);
  } else {
    fprintf(stderr, "Usage: $./main <rule list> <pseudo packets>\n");
    exit(1);
  }
  
  /* classify headers via a kind of methods */
  if (true == classbench_flag) ;
  else do_sequential_search(rulelist, headerlist);
  putchar('\n');
  do_simple_search(T, headerlist);
  putchar('\n');
  do_pointer_search(PT[0], headerlist);
  putchar('\n');

  /* from here ========== freeing memories ========== */ 
  {	
    unsigned i;
    for (i = 0; i < _n; ++i) {
      // printf("%s\n",rulelist[i]);
      free(rulelist[i]);
    }
  }
  
  {	
    unsigned i;
    for (i = 0; i < _hn; ++i) {
      //printf("%s\n", headerlist[i]);
      free(headerlist[i]);
    }
  }
  free(rulelist);
  free(headerlist);
  
  free_RBT(T);
  free(T);
  free_PRBT(PT);
  free(PT);
  /* ========== freeing memories ========== ----> to here*/ 
  
  return 0;
}
