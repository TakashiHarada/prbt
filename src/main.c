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
	if (read_rulelist(argv[1], rulelist) == false) {
		fprintf(stderr, "Can't read a rule-list file\n");
		exit(1);
	}
	
	{
		int i;
		for (i = 0; i < 100; ++i) {
			printf("%s\n", rulelist[i]);
			free(rulelist[i]);
		}
	}

	return 0;
}
