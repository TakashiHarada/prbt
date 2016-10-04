/* io.c */

#include <io.h>

char* delete_space(char* h)
{
  unsigned i, j, l = strlen(h);
  char* header = (char*)malloc(sizeof(char)*(_w+1));
  i = j = 0;
  while (i < l) {
    if (' ' != h[i]) {
      header[j] = h[i];
      ++j;
    }
    ++i;
  }
  header[_w] = '\0';
  // printf("%s\n", header);
  free(h), h = NULL;
  return header;
}

unsigned get_header_length_in_classbench_format(char* header)
{
  char* copy = (char*)malloc(sizeof(char)*(strlen(header)));
  strcpy(copy,header);
  char* f;
  unsigned w = 0;

  f = strtok(copy, " ");
  if (NULL != f)
    w += strlen(f);
  while (NULL != f) {
    f = strtok(NULL, " ");
    if (NULL != f) 
      w += strlen(f);
  }
  --w; // for '\n'

  free(copy), copy = NULL;

  return w;
}

char** read_classbench_header_list(char* header_file_name)
{
  FILE* fp;
  if ((fp = fopen(header_file_name,"r")) == NULL) { return NULL; }

  /* get the number of rules (n) in an input rule-list and the length (w) of the rule */
  char* line = NULL;
  size_t len = 0;
  ssize_t read;
  unsigned n = 0;
  unsigned w = 0;

  getline(&line,&len,fp);
  w = get_header_length_in_classbench_format(line);

  if (_w != w) {
    fprintf(stderr, "Rule length not equals to header length.\nCheck the input rule list file and header liest file.\n");
    exit(1);
  }
  ++n;
  while (getline(&line, &len, fp) != -1) {
    ++n;
  }
  // printf("w = %d, n = %d\n", w, n);

  /* allocate memory and make rulelist */
  char** headerlist = (char**)malloc(n*sizeof(char*));
  rewind(fp);
  {
    unsigned i = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
      headerlist[i] = (char*)malloc((w+1)*sizeof(char));
      line = delete_space(line);
      strcpy(headerlist[i], line);
      // printf("h[%d] = %s\n",i, headerlist[i]);
      ++i;
    }
  }

  fclose(fp);
  _hn = n;

  return headerlist;
}

bool in_hyphen(char* rule)
{
  unsigned i, l = strlen(rule);
  for (i = 0; i < l; ++i) 
    if ('-' == rule[i])	
      return true;

  return false;
}

unsigned get_rule_length_in_bitstring_format(char* rule)
{
  char* copy = (char*)malloc(sizeof(char)*(strlen(rule)));
  strcpy(copy,rule);
  char* f;
  unsigned w = 0;

  f = strtok(copy, " ");
  w += strlen(f);
  if (NULL != f)
    if ('\n' == f[strlen(f)-1])
      --w;

  while (NULL != f) {
    if (NULL != f)
      if ('\n' == f[strlen(f)-1])
	--w;
    f = strtok(NULL, " ");
    if (NULL != f) {
      if (in_hyphen(f))
	w += BIT_LENGTH;
      else
	w += strlen(f);
    }
  }
  // printf("w = %d\n", w);

  free(copy), copy = NULL;
  return w;
}

char** read_classbench_rule_list(char* rule_file_name)
{
  FILE* fp;
  if ((fp = fopen(rule_file_name,"r")) == NULL) { return NULL; }

  /* get the number of rules (n) in an input rule-list and the length (w) of the rule */
  char* line = NULL;
  size_t len = 0;
  ssize_t read;
  unsigned n = 0;
  unsigned w = 0;

  w = getline(&line,&len,fp)-1;
  ++n;
  _w = get_rule_length_in_bitstring_format(line);

  while ((read = (getline(&line, &len, fp))) != -1) {
    if (read > w)
      w = read;
    //printf("%s",line);
    ++n;
  }
  /*
    printf("w = %d\n", w);
    printf("n = %d\n", n);
  */
  if (w > _w)  _capacity = w;
  else _capacity = _w;

  /* allocate memory and make rulelist */
  char** rulelist = (char**)malloc(n*sizeof(char*));
  rewind(fp);
  {
    unsigned i = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
      rulelist[i] = (char*)malloc((w+1)*sizeof(char));
      strncpy(rulelist[i], line, w);
      rulelist[i][w] = '\0';
      ++i;
    }
  }

  fclose(fp);
  _n = n;

  return rulelist;
}


char** read_header_list(char* header_file_name)
{
  FILE* fp;
  if ((fp = fopen(header_file_name,"r")) == NULL) { return NULL; }

  /* get the number of rules (n) in an input rule-list and the length (w) of the rule */
  char* line = NULL;
  size_t len = 0;
  ssize_t read;
  unsigned n = 0;
  unsigned w = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    w = read-1;
    ++n;
  }
  //printf("n = %d\n", n);
  if (_w != w) {
    fprintf(stderr, "Rule length not equals to header length.\nCheck the input rule list file and header liest file.\n");
    exit(1);
  }

  /* allocate memory and make rulelist */
  char** headerlist = (char**)malloc(n*sizeof(char*));
  rewind(fp);
  {
    unsigned i = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
      headerlist[i] = (char*)malloc((_w+1)*sizeof(char));
      strncpy(headerlist[i], line, _w);
      headerlist[i][_w] = '\0';
      ++i;
    }
  }

  fclose(fp);
  _hn = n;

  return headerlist;
}

char** read_rule_list(char* rule_file_name)
{
  FILE* fp;
  if ((fp = fopen(rule_file_name,"r")) == NULL) { return NULL; }

  /* get the number of rules (n) in an input rule-list and the length (w) of the rule */
  char* line = NULL;
  size_t len = 0;
  ssize_t read;
  unsigned n = 0;
  unsigned w = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    w = read-1;
    ++n;
  }
  // printf("w = %d\n", w);
  // printf("n = %d\n", n);

  /* allocate memory and make rulelist */
  char** rulelist = (char**)malloc(n*sizeof(char*));
  rewind(fp);
  {
    unsigned i = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
      rulelist[i] = (char*)malloc((w+1)*sizeof(char));
      strncpy(rulelist[i], line, w);
      rulelist[i][w] = '\0';
      ++i;
    }
  }

  fclose(fp);
  _n = n;
  _w = w;

  return rulelist;
}
