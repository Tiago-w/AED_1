#include <stdlib.h>

struct ListNode {
	int				 val;
	struct ListNode* next;
};

struct TreeNode {
	int				 val;
	struct TreeNode* left;
	struct TreeNode* right;
};

static struct TreeNode* novoNoArvore( int v ) {
	struct TreeNode* n = ( struct TreeNode* )malloc( sizeof( struct TreeNode ) );
	n->val			   = v;
	n->left			   = NULL;
	n->right		   = NULL;
	return n;
}

static struct ListNode* acharMeioECortar( struct ListNode* head ) {
	struct ListNode* prev = NULL;
	struct ListNode* slow = head;
	struct ListNode* fast = head;

	while( fast != NULL && fast->next != NULL ) {
		prev = slow;
		slow = slow->next;
		fast = fast->next->next;
	}

	if( prev != NULL ) {
		prev->next = NULL; 
	}
	return slow; 
}

struct TreeNode* sortedListToBST( struct ListNode* head ) {
	if( head == NULL )
		return NULL;
	if( head->next == NULL )
		return novoNoArvore( head->val );

	struct ListNode* meio = acharMeioECortar( head );

	struct TreeNode* raiz = novoNoArvore( meio->val );

	if( meio == head )
		raiz->left = NULL;
	else
		raiz->left = sortedListToBST( head );

	raiz->right = sortedListToBST( meio->next );
	return raiz;
}
