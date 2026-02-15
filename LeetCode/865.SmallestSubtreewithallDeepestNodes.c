#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
	int				 val;
	struct TreeNode* left;
	struct TreeNode* right;
};

typedef struct {
	int				 depth;
	struct TreeNode* node;
} Result;

Result dfs( struct TreeNode* root ) {
	if( root == NULL ) {
		return ( Result ){ 0, NULL };
	}

	Result left	 = dfs( root->left );
	Result right = dfs( root->right );

	if( left.depth == right.depth ) {
		return ( Result ){ left.depth + 1, root };
	}

	if( left.depth > right.depth ) {
		return ( Result ){ left.depth + 1, left.node };
	} else {
		return ( Result ){ right.depth + 1, right.node };
	}
}

struct TreeNode* subtreeWithAllDeepest( struct TreeNode* root ) {
	return dfs( root ).node;
}

struct TreeNode* createNode( int val ) {
	struct TreeNode* newNode = ( struct TreeNode* )malloc( sizeof( struct TreeNode ) );
	newNode->val			 = val;
	newNode->left			 = NULL;
	newNode->right			 = NULL;
	return newNode;
}

int main() {
	struct TreeNode* root	 = createNode( 3 );
	root->left				 = createNode( 5 );
	root->right				 = createNode( 1 );
	root->left->left		 = createNode( 6 );
	root->left->right		 = createNode( 2 );
	root->left->right->left	 = createNode( 7 );
	root->left->right->right = createNode( 4 );
	root->right->left		 = createNode( 0 );
	root->right->right		 = createNode( 8 );

	struct TreeNode* result = subtreeWithAllDeepest( root );

	if( result ) {
		printf( "A raiz da menor subárvore é o nó com valor: %d\n", result->val );
	}

	return 0;
}