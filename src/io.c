/* io.c */

#include <tools.h>
#include <io.h>

bool read_rulelist(char* rule_file_name, char** rulelist)
{
	FILE *fp;

	if ((fp = fopen(rule_file_name,"r")) == NULL) { fclose(fp); return false; }
	rulelist = (char**)malloc(100);
	{
		int i;
		for (i = 0; i < 100; ++i)
			rulelist[i] = (char*)malloc(50);
	}
	fclose(fp);

	return true;
}
