/* main.c */

#include <main.h>

int main(int argc, char** argv)
{
  char** rulelist = NULL;
  char** headerlist = NULL;
  rbt** T = NULL;
  prbt** PT = NULL;
  csprbt* CSPT = NULL;
  bool classbench_flag = false;

  /* check arguments */
  if (!strcmp("-c",argv[1])) { 
    /* each rule of the input rulelist format is class bench like format and separated by 6 fields 
       Source Address, Destination Address, Source Port, Destination Port, Protocol, Flag */

    classbench_flag = true;

    if ((rulelist = read_classbench_rule_list(argv[2])) == NULL) {
      fprintf(stderr, "Can't read an input rule-list file\n");
      exit(1);
    }

    if ((headerlist = read_classbench_header_list(argv[3])) == NULL) {
      fprintf(stderr, "Can't read an input header-list file\n");
      exit(1);
    }

    /* printf("%s\n", rulelist[0]); */
    /* str_list* ptr = string_to_strings(rulelist[0]); */
    /* str_list* it = ptr; */
    /* while (NULL != it) { */
    /*   printf("%s\n", it->elem); */
    /*   it = it->next; */
    /* } */
    /* free_strlist(ptr); */

    /* make a Run-Based Trie */
    T = make_Run_Based_Trie_in_classbench_format(rulelist);

    /* make a Pointed Run-Based Trie */
    PT = make_Pointed_Run_Based_Trie_in_classbench_format(rulelist);
    // traverse_PRBT(PT);

  } else if (argc == 3) {
    /* each rule of the input rule-list is continuous, not separated by fields */
    /* read rule-list and header-list files */
    if ((rulelist = read_rule_list(argv[1])) == NULL) {
      fprintf(stderr, "Can't read an input rule-list file\n");
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

    /* make column switched rule Pointed Run-Based Trie */
    CSPT = make_column_switched_Pointed_Run_Based_Trie(rulelist);

  } else {
    fprintf(stderr, "Usage: $./main <rule list> <pseudo packets>\n");
    exit(1);
  }
  
  /* classify headers via a kind of methods */
  if (true == classbench_flag) do_classbench_sequential_search(rulelist, headerlist);
  else do_sequential_search(rulelist, headerlist);
  putchar('\n');
  do_simple_search(T, headerlist);
  putchar('\n');
  do_pointer_search(PT[0], headerlist);
  putchar('\n');
  do_csprbt_search(CSPT, headerlist);
  putchar('\n');

  /* from here ========== freeing memories ========== */ 
  {	
    unsigned i;
    for (i = 0; i < _n; ++i) {
      // printf("%s\n",rulelist[i]);
      free(rulelist[i]);
    }

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
