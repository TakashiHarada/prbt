/* tools.c */

#include <tools.h>

/* str_list* rangerule_to_01mlist(char* rule, unsigned low, unsigned high) */
/* { */
/* 	char del[] = " -."; */
/* 	char *num; */
/* 	unsigned a, b; */
/* 	num = strtok(rule, del); */
/* 	a = (unsigned)atoi(num); */
/* 	num = strtok(NULL, del); */
/* 	b = (unsigned)atoi(num); */
/* 	return NULL; //convert_range_to_01m(a,b,low,high); */
/* } */

str_list* concat_strlist(str_list* s, str_list* t)
{
	return NULL;
}

str_list* int_pair_to_01m(unsigned a, unsigned b, unsigned w)
{
	printf("a = %d, b = %d\n", a, b);
	return NULL;
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
		concat_strlist(range_to_01ms_sub(a,m,low,m),range_to_01ms_sub(n,b,n,high));
	else 
		return range_to_01ms_sub(a,b,n,high);

	return NULL;
}

/* LOW (=0) and HIGH (=65535) are predefined in the tool.h */
str_list* range_to_01ms(unsigned a, unsigned b)
{
	return range_to_01ms_sub(a,b,LOW,HIGH);
}
