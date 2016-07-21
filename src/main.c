/* main.c */

#include <main.h>

int main(int argc, char** argv)
{
  /* check arguments */
  if (argc != 3) {
    fprintf(stderr, "Usage: $./main <rule list> <pseudo packets>\n");
    exit(1);
  }
  
  /* read rule-list and header-list files */
  char** rulelist;
  if ((rulelist = read_rule_list(argv[1])) == NULL) {
    fprintf(stderr, "Can't read an input rule-list file\n");
    return 1;
    exit(1);
  }
  
  char** headerlist;
  if ((headerlist = read_header_list(argv[2])) == NULL) {
    fprintf(stderr, "Can't read an input header-list file\n");
    exit(1);
  }
  
  /* make a Run-Based Trie */
  rbt** T = make_Run_Based_Trie(rulelist);
  
  /* make a Pointed Run-Based Trie */
  prbt** PT = make_Pointed_Run_Based_Trie(rulelist);
  //traverse_PRBT(PT);
  
  /* classify headers via a kind of methods */
  do_sequential_search(rulelist, headerlist);
  putchar('\n');
  do_simple_search(T, headerlist);
  putchar('\n');
  do_pointer_search(PT, headerlist);
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
