# Self generating C source code.
# This program prints to the standard output it's own source code.
# Wrote by Henrique Gemignani Passos Lima

#include <stdio.h>

char buf1[2048], buf2[2048];
void escp(char* a, char* b) {
	int i, j;
	for(i = 0, j = 0; a[i] != 0; i++) {
		if(a[i] == 34 || a[j] == 92) b[j++] = 92;
		b[j++] = a[i];
	}
}

char *argsval = "char *argsval = \"%s\", *HEADERS = \"%s\", *FUNCTION = \"%s\", *REPLICATE_START = \"%s\", *REPLICATE_VARIABLES = \"%s\", *REPLICATE_END = \"%s\", *MAIN = \"%s\";",
	 *HEADERS = "#include <stdio.h>",
	 *FUNCTION = "char buf1[2048], buf2[2048]; void escp(char* a, char* b) { int i, j; for(i = 0, j = 0; a[i] != 0; i++) { if(a[i] == 34 || a[j] == 92) b[j++] = 92; b[j++] = a[i]; } }",
	 *REPLICATE_START = "void replicate(){ puts(HEADERS); puts(FUNCTION); escp(argsval, buf1); escp(FUNCTION, buf2);",
	 *REPLICATE_VARIABLES = "printf(argsval, buf1, HEADERS, buf2, REPLICATE_START, REPLICATE_VARIABLES, REPLICATE_END, MAIN);",
	 *REPLICATE_END = "puts(REPLICATE_START); puts(REPLICATE_VARIABLES); puts(REPLICATE_END); puts(MAIN); }",
	 *MAIN = "int main(int argc, char **argv){ replicate(); return 0; }";

void replicate() {
	puts(HEADERS);
	puts(FUNCTION);
	escp(argsval, buf1);
	escp(FUNCTION, buf2);
	printf(argsval, buf1, HEADERS, buf2, REPLICATE_START, REPLICATE_VARIABLES, REPLICATE_END, MAIN);
	
	puts(REPLICATE_START);
	puts(REPLICATE_VARIABLES);
	puts(REPLICATE_END);
	puts(MAIN);
}
int main(int argc, char **argv) {
	replicate();
	return 0;
}