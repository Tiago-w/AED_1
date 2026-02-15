#include <stdio.h>

int maximumGain( char* s, int x, int y );

int main() {
	char s[] = { "abababa" };
	int	 x = 4, y = 5;

	int resultado = maximumGain( s, x, y );

	printf( "%d", resultado );

	return 0;
}

int maximumGain( char* s, int x, int y ) {

	int score = 0;

	char c1 = 'a', c2 = 'b';
	int	 pontos1 = x, pontos2 = y;

	if( y > x ) {
		c1		= 'b';
		c2		= 'a';
		pontos1 = y;
		pontos2 = x;
	}

	int top = -1;

	for( int i = 0; s[i] != '\0'; i++ ) {

		if( top >= 0 && s[top] == c1 && s[i] == c2 ) {
			top--;
			score += pontos1;
		} else {
			s[++top] = s[i];
		}
	}
	s[top + 1] = '\0';
	top		   = -1;

	for( int i = 0; s[i] != '\0'; i++ ) {
		if( top >= 0 && s[top] == c2 && s[i] == c1 ) {
			top--;
			score += pontos2;
		} else {
			s[++top] = s[i];
		}
	}
	s[top + 1] = '\0';

	return score;
}