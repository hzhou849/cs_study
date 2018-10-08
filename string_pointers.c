
int str_find(const char* c, const char* s) {

/*	strings can be stored either
* stores &
ex: 
char * str - pointer variables 
str=&str1

char str1[] = "Hello"
char *str2 = "Goodbye"
*/
	char str1[] = "Hello";
	char *str2 = "Goodbye";

	printf("%s\n", str1);
	printf("%s\n", str2);

	printf("%x %x %s\n", &str1, str1, str1);
	printf("address: %x -->value: %x %s\n", &str2, str2, str2);
	return 0;
}