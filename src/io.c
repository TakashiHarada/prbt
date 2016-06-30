/* io.c */

#include <const.h>
#include <tools.h>
#include <io.h>

char** read_header_list(char* header_file_name)
{
	FILE* fp;
	if ((fp = fopen(header_file_name,"r")) == NULL) { fclose(fp); return false; }

	/* get the number of rules (n) in an input rule-list and the length (w) of the rule */
	char* line = NULL;
	size_t len = 0;
	ssize_t read;
	unsigned n = 0;
	unsigned w;
	while ((read = getline(&line, &len, fp)) != -1) {
		w = read-1;
		++n;
	}
	//printf("n = %d\n", n);
	if (_w != w) {
		fprintf(stderr, "rule length not equals to header length\n");
		exit(1);
	}

	/* allocate memory and make rulelist */
	char** headerlist = (char**)malloc(n*sizeof(char*));
	rewind(fp);
	{
		unsigned i = 0;
		while ((read = getline(&line, &len, fp)) != -1) {
			headerlist[i] = (char*)malloc(_w*sizeof(char));
			strncpy(headerlist[i], line, _w);
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
	if ((fp = fopen(rule_file_name,"r")) == NULL) { fclose(fp); return false; }

	/* get the number of rules (n) in an input rule-list and the length (w) of the rule */
	char* line = NULL;
	size_t len = 0;
	ssize_t read;
	unsigned n = 0;
	unsigned w;
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
			rulelist[i] = (char*)malloc(w*sizeof(char));
			strncpy(rulelist[i], line, w);
			++i;
		}
	}

	fclose(fp);
	_n = n;
	_w = w;

	return rulelist;
}
