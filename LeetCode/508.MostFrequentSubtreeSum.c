#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
	int				 val;
	struct TreeNode* left;
	struct TreeNode* right;
};

int sums[10000];
int sum_count = 0;

int getSubtreeSum( struct TreeNode* root ) {
	if( root == NULL )
		return 0;

	int left_sum	= getSubtreeSum( root->left );
	int right_sum	= getSubtreeSum( root->right );
	int current_sum = root->val + left_sum + right_sum;

	sums[sum_count++] = current_sum;

	return current_sum;
}

int* findFrequentTreeSum( struct TreeNode* root, int* returnSize ) {
	if( root == NULL ) {
		*returnSize = 0;
		return NULL;
	}

	sum_count = 0;
	getSubtreeSum( root );

	int	 max_freq	 = 0;
	int* frequencies = ( int* )calloc( sum_count, sizeof( int ) );

	for( int i = 0; i < sum_count; i++ ) {
		int count = 0;
		for( int j = 0; j < sum_count; j++ ) {
			if( sums[i] == sums[j] )
				count++;
		}
		frequencies[i] = count;
		if( count > max_freq )
			max_freq = count;
	}

	int* result		= ( int* )malloc( sum_count * sizeof( int ) );
	int	 result_idx = 0;

	for( int i = 0; i < sum_count; i++ ) {
		if( frequencies[i] == max_freq ) {
			int already_in = 0;
			for( int k = 0; k < result_idx; k++ ) {
				if( result[k] == sums[i] )
					already_in = 1;
			}
			if( !already_in ) {
				result[result_idx++] = sums[i];
			}
		}
	}

	free( frequencies );
	*returnSize = result_idx;
	return result;
}

struct TreeNode* createNode( int val ) {
	struct TreeNode* newNode = ( struct TreeNode* )malloc( sizeof( struct TreeNode ) );
	newNode->val			 = val;
	newNode->left			 = NULL;
	newNode->right			 = NULL;
	return newNode;
}

int main() {
	struct TreeNode* root = createNode( 5 );
	root->left			  = createNode( 2 );
	root->right			  = createNode( -3 );

	int	 returnSize;
	int* result = findFrequentTreeSum( root, &returnSize );

	printf( "Somas mais frequentes: " );
	for( int i = 0; i < returnSize; i++ ) {
		printf( "%d ", result[i] );
	}
	printf( "\n" );

	free( result );
	return 0;
}