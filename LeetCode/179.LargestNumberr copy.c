#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* largestNumber( int* nums, int numsSize ) {

	char* resultado = ( char* )malloc( numsSize * 12 * sizeof( char ) + 1 );
	char  a[50], b[50];

	for( int i = 0; i < numsSize; i++ ) {
		for( int j = i + 1; j < numsSize; j++ ) {

			sprintf( a, "%d%d", nums[i], nums[j] );
			sprintf( b, "%d%d", nums[j], nums[i] );

			if( strcmp( b, a ) > 0 ) {
				int temp = nums[i];
				nums[i]	 = nums[j];
				nums[j]	 = temp;
			}
		}
	}

	if( nums[0] == 0 ) {
		return "0";
	}

	char* ptr = resultado;

	for( int i = 0; i < numsSize; i++ ) {
		ptr += sprintf( ptr, "%d", nums[i] );
	}

	return resultado;
}

int main() {
	int nums[]	 = { 1, 30, 8, 7, 3 }; // 873301
	int numsSize = 5;

	printf( "%s", largestNumber( nums, numsSize ) );
	
	return 0;
}