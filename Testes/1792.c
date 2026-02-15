#include <stdio.h>
#include <stdlib.h>

double maxAverageRatio( int** classes, int classesSize, int* classesColSize, int extraStudents );

int main() {
	int	 t1[]	   = { 1, 2 };
	int	 t2[]	   = { 3, 5 };
	int	 t3[]	   = { 2, 2 };
	int* classes[] = { t1, t2, t3 };

	int classesSize	  = 3;
	int colSizes[]	  = { 2, 2, 2 };
	int extraStudents = 2;

	double res = maxAverageRatio( classes, classesSize, colSizes, extraStudents );

	printf( "%.5f\n", res );

	return 0;
}

double maxAverageRatio( int** classes, int classesSize, int* classesColSize, int extraStudents ) {
	
	int* heap = ( int* )malloc( classesSize * sizeof( int ) );
	for( int i = 0; i < classesSize; i++ ) {
		heap[i] = i;
	}

	for( int i = classesSize / 2 - 1; i >= 0; i-- ) {
		int atual = i;
		while( 1 ) {
			int maior = atual;
			int esq	  = 2 * atual + 1;
			int dir	  = 2 * atual + 2;

			if( esq < classesSize ) {
				int	   idxEsq	= heap[esq];
				int	   idxMaior = heap[maior];
				double ganhoEsq = ( double )( classes[idxEsq][0] + 1 ) / ( classes[idxEsq][1] + 1 ) -
								  ( double )classes[idxEsq][0] / classes[idxEsq][1];
				double ganhoMaior = ( double )( classes[idxMaior][0] + 1 ) / ( classes[idxMaior][1] + 1 ) -
									( double )classes[idxMaior][0] / classes[idxMaior][1];

				if( ganhoEsq > ganhoMaior )
					maior = esq;
			}

			if( dir < classesSize ) {
				int	   idxDir	= heap[dir];
				int	   idxMaior = heap[maior];
				double ganhoDir = ( double )( classes[idxDir][0] + 1 ) / ( classes[idxDir][1] + 1 ) -
								  ( double )classes[idxDir][0] / classes[idxDir][1];
				double ganhoMaior = ( double )( classes[idxMaior][0] + 1 ) / ( classes[idxMaior][1] + 1 ) -
									( double )classes[idxMaior][0] / classes[idxMaior][1];

				if( ganhoDir > ganhoMaior )
					maior = dir;
			}

			if( maior != atual ) {
				int temp	= heap[atual];
				heap[atual] = heap[maior];
				heap[maior] = temp;
				atual		= maior;
			} else {
				break;
			}
		}
	}

	while( extraStudents > 0 ) {
		int idx = heap[0];
		classes[idx][0]++;
		classes[idx][1]++;
		extraStudents--;

		int atual = 0;
		while( 1 ) {
			int maior = atual;
			int esq	  = 2 * atual + 1;
			int dir	  = 2 * atual + 2;

			if( esq < classesSize ) {
				int	   idxEsq	= heap[esq];
				int	   idxMaior = heap[maior];
				double ganhoEsq = ( double )( classes[idxEsq][0] + 1 ) / ( classes[idxEsq][1] + 1 ) -
								  ( double )classes[idxEsq][0] / classes[idxEsq][1];
				double ganhoMaior = ( double )( classes[idxMaior][0] + 1 ) / ( classes[idxMaior][1] + 1 ) -
									( double )classes[idxMaior][0] / classes[idxMaior][1];

				if( ganhoEsq > ganhoMaior )
					maior = esq;
			}

			if( dir < classesSize ) {
				int	   idxDir	= heap[dir];
				int	   idxMaior = heap[maior];
				double ganhoDir = ( double )( classes[idxDir][0] + 1 ) / ( classes[idxDir][1] + 1 ) -
								  ( double )classes[idxDir][0] / classes[idxDir][1];
				double ganhoMaior = ( double )( classes[idxMaior][0] + 1 ) / ( classes[idxMaior][1] + 1 ) -
									( double )classes[idxMaior][0] / classes[idxMaior][1];

				if( ganhoDir > ganhoMaior )
					maior = dir;
			}

			if( maior != atual ) {
				int temp	= heap[atual];
				heap[atual] = heap[maior];
				heap[maior] = temp;
				atual		= maior;
			} else {
				break;
			}
		}
	}

	double total = 0.0;
	for( int i = 0; i < classesSize; i++ ) {
		total += ( double )classes[i][0] / classes[i][1];
	}

	free( heap );
	return total / classesSize;
}
