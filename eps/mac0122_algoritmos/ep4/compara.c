#include <stdio.h>
#include <stdlib.h>

int comparaString( char s1[], char s2[] ) {
	int i;
	for( i = 0; s1[i] == s2[i] && s1[i] != '\0'; i++ );
	return (s2[i] - s1[i]);
}

int main() {
	char s1[128], s2[128], c;
	int i;
	while(42) {
		i = 0;
		while( (c = fgetc( stdin )) != ' ' && c != '\n' ) {
			s1[i] = c;
			i++;
		}
		s1[i] = '\0';
		i = 0;
		while( (c = fgetc( stdin )) != ' ' && c != '\n' ) {
			s2[i] = c;
			i++;
		}
		s2[i] = '\0';
		printf("'%s','%s': %d\n", s1, s2, comparaString( s1, s2 ) );
	}
	return 0;
}