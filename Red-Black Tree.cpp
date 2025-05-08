#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

struct Node{
	int data;
	int color;
	struct Node *left, *right, *parent;
};

struct Node* createNode(int data){
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = data;
	newNode->color = RED;
	newNode->left = newNode->right = newNode->parent = NULL;
	return newNode;
}

// berfungsi untuk melakukan rotasi ke kanan
void rightRotate(struct Node **root, struct Node *x){
	struct Node *y = x->left;
	x->left = y->right;
	if (y->right != NULL){
		y->right->parent = x;
		}
	y->parent = x->parent;
	if (x->parent == NULL){
		(*root) = y;
	} else if (x == x->parent->right){
		x->parent->right = y;
	} else{
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;
}

// berfungsi untuk melakukan rotasi kiri
void leftRotate(struct Node **root, struct Node *x){
	struct Node *y = x->right;
	x->right = y->left;
	if (y->left != NULL){
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == NULL){
		(*root) = y;
	} else if (x == x->parent->left){
		x->parent->left = y;
	} else{
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

// berfungsi untuk memperbaiki tree setelah nambah node baru
void insertFixUp(struct Node **root, struct Node *z){
	while (z != *root && z->parent->color == RED){
		if (z->parent == z->parent->parent->left){
			struct Node *y = z->parent->parent->right;
			if (y != NULL && y->color == RED){
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			} else{
				if (z == z->parent->right){
					z = z->parent;
					leftRotate(root, z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				rightRotate(root, z->parent->parent);
			}
		} else{
			struct Node *y = z->parent->parent->left;
			if (y != NULL && y->color == RED){
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			} else{
				if (z == z->parent->left){
					z = z->parent;
					rightRotate(root, z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				leftRotate(root, z->parent->parent);
			}
		}
	}
	(*root)->color = BLACK;
}

// berfungsi untuk menambahkan node baru ke Red-Black Tree
void insertNode(struct Node **root, int data){
	struct Node *z = createNode(data);
	struct Node *y = NULL;
	struct Node *x = (*root);
	
	while (x != NULL){
		y = x;
		if (z->data < x->data){
			x = x->left;
		} else{
			x = x->right;
		}
	}
	z->parent = y;
	if (y == NULL){
		(*root) = z;
	} else if (z->data < y->data){
		y->left = z;
	} else{
		y->right = z;
	}
	z->left = NULL;
	z->right = NULL;
	z->color = RED;
	
	insertFixUp(root, z);
}

// Berfungsi untuk print tree dengan format pre-order
void preOrder(struct Node *root){
	if (root != NULL){
		printf("%d ", root->data);
		preOrder(root->left);
		preOrder(root->right);
	}
}

// Berfungsi untuk print tree dengan format in-order
void inOrder(struct Node *root){
	if (root != NULL){
		inOrder(root->left);
		printf("%d ", root->data);
		inOrder(root->right);
	}
}

// Berfungsi untuk print tree dengan format post-order
void postOrder(struct Node *root){
	if (root != NULL){
		postOrder(root->left);
		postOrder(root->right);
		printf("%d ", root->data);
	}
}

int main(){
	struct Node *root = NULL;
	insertNode(&root, 8);
	insertNode(&root, 15);
	insertNode(&root, 5);
	insertNode(&root, 12);
	insertNode(&root, 13);
	insertNode(&root, 23);
	insertNode(&root, 19);
	insertNode(&root, 9);
	
	printf("In-order: ");
	inOrder(root);
	printf("\n");
	
	printf("Pre-order: ");
	preOrder(root);
	printf("\n");
	
	printf("Post-order: ");
	postOrder(root);
	printf("\n");
	
	return 0;
}