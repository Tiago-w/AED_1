#include <stdio.h>
#include <stdlib.h>

static const int MOD = 1000000007;

static int comb[1001][1001];
static int comb_pronto = 0;

static void prepararComb( int n ) {
	if( comb_pronto )
		return;
	comb_pronto = 1;

	for( int i = 0; i <= n; i++ ) {
		comb[i][0] = 1;
		comb[i][i] = 1;
		for( int j = 1; j < i; j++ ) {
			comb[i][j] = ( comb[i - 1][j - 1] + comb[i - 1][j] ) % MOD;
		}
	}
}

static int modNorm( long x ) {
	x %= MOD;
	if( x < 0 )
		x += MOD;
	return ( int )x;
}

static int resolver( int* a, int n ) {
	if( n <= 2 )
		return 1;

	int raiz = a[0];

	int* esq = ( int* )malloc( n * sizeof( int ) );
	int* dir = ( int* )malloc( n * sizeof( int ) );
	int	 L = 0, R = 0;

	for( int i = 1; i < n; i++ ) {
		if( a[i] < raiz )
			esq[L++] = a[i];
		else
			dir[R++] = a[i];
	}

	int waysE = resolver( esq, L );
	int waysD = resolver( dir, R );

	long ans = comb[n - 1][L];
	ans		 = ( ans * waysE ) % MOD;
	ans		 = ( ans * waysD ) % MOD;

	free( esq );
	free( dir );
	return ( int )ans;
}

int numOfWays( int* nums, int numsSize ) {
	prepararComb( numsSize );

	int total = resolver( nums, numsSize );
	total	  = modNorm( ( long )total - 1 );
	return total;
}

static void testar( int* v, int n ) {
	printf( "Entrada: " );
	for( int i = 0; i < n; i++ )
		printf( "%d ", v[i] );
	printf( "\nSaida: %d\n\n", numOfWays( v, n ) );
}

int main( void ) {
	int a1[] = { 2, 1, 3 };
	testar( a1, 3 );

	int a2[] = { 3, 4, 5, 1, 2 };
	testar( a2, 5 );

	int a3[] = { 1, 2, 3 };
	testar( a3, 3 );

	return 0;
}
