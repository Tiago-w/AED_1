#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* largestNumber( int* nums, int numsSize ) {

	static char resultado[100];
	char		a[50], b[50];

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

}

int main() {
	int nums[]	 = { 3, 30, 34, 5, 9 };
	int numsSize = 5;

	printf( "%s", largestNumber( nums, numsSize ) );

	return 0;
}