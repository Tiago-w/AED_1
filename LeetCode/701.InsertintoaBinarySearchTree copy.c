#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
	int				 val;
	struct TreeNode* left;
	struct TreeNode* right;
};

struct TreeNode* insertIntoBST( struct TreeNode* root, int val ) {

	if( root == NULL ) {
		struct TreeNode* root = ( struct TreeNode* )malloc( sizeof( struct TreeNode ) );
		root->val			  = val;
		root->left			  = NULL;
		root->right			  = NULL;
		return root;
	}

	if( val < root->val ) {
		root->left = insertIntoBST( root->left, val );
	} else if( val > root->val ) {
		root->right = insertIntoBST( root->right, val );
	}
	return root;
}

int main() {
	int				 numeros[] = { 4, 2, 7, 1, 3 };
	int				 tam	   = 5;
	int				 valor	   = 5;
	struct TreeNode* root;
	root = NULL;

	for( int i = 0; i < tam; i++ ) {
		root = insertIntoBST( root, numeros[i] );
	}
	root = insertIntoBST( root, valor );
}