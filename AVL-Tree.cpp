//Question: https://www.spoj.com/problems/SDITSAVL/

#include "stdio.h"
#include "stdlib.h"
#include "limits.h"

int flag;
typedef struct node {
	int val;
	struct node *left;
	struct node *right;
	int left_child;
	int right_child;
	int height;
} node;

int max (int a, int b) {
	if(a > b)
        return a; 
    else 
        return b; 
}

int height (node *root) {//height of tree/node
    if (root == NULL)
        return 0;
    else 
        return root -> height; 
	
}

node *new_node (int val, int left_child, int right_child) {
	node *tmp_node = (node *) malloc( sizeof(node) );
	tmp_node -> val = val;
	tmp_node -> left = NULL;
	tmp_node -> right = NULL;
	tmp_node -> height = 1;
	tmp_node -> left_child = left_child;
	tmp_node -> right_child = right_child;
	return tmp_node;
}

node *right_rotate (node *y) {
	node *x = y -> left;
	node *T2 = x -> right;

	x -> right = y;
	y -> left = T2;

	y -> height = max( height(y -> left), height(y -> right) ) + 1;
	x -> height = max( height(x -> left), height(x -> right) ) + 1;
	
	if (T2 != NULL) y -> left_child = T2 -> left_child + T2 -> right_child + 1; else y -> left_child = 0;
	x -> right_child = y -> left_child + y -> right_child + 1;

	return x;
}

node *left_rotate (node *x) {
	node *y = x -> right;
	node *T2 = y -> left;

	y -> left = x;
	x -> right = T2;

	x -> height = max( height(x -> left), height(x -> right) ) + 1;
	y -> height = max( height(y -> left), height(y -> right) ) + 1;

	if (T2 != NULL)
        x -> right_child = T2 -> left_child + T2 -> right_child + 1; 
    else 
        x -> right_child = 0;

	y -> left_child = x -> left_child + x -> right_child + 1;
	
	return y;
}

int get_balance_factor (node *root) {//find the balance factor
	if (root == NULL) 
        return 0;
	else 
        return height(root -> left) - height(root -> right);
}

node *insert(node *root, int val) {//inserts node 
	if (root == NULL) 
        return new_node(val, 0, 0);//make new node if tree emptry 
    //insert if > or <
	if (val < root -> val) {
		root -> left = insert(root -> left, val);
		root -> left_child++;
	}
	else if (val > root -> val) {
		root -> right = insert(root -> right, val);
		root -> right_child++;
	}
	else return root;

	root -> height = max( height(root -> left), height(root -> right) ) + 1;

	int balance = get_balance_factor(root);

	
    //if the tree is unbalance then fix it 
	if ( (balance > 1) && (val < root -> left -> val) )
         return right_rotate(root);

	if ( (balance < -1) && (val > root -> right -> val) ) 
        return left_rotate(root);

	if ( (balance > 1) && (val > root -> left -> val) ) {
		root -> left = left_rotate(root -> left);
		return right_rotate(root);
	}

	if ( (balance < -1) && (val < root -> right -> val) ) {
		root -> right = right_rotate(root -> right);
		return left_rotate(root);
	}

	return root;
}


int find_by_val (node *root, int val) {//finds the value 
	if (root != NULL) {
		
		if (val > root -> val)
             return root -> left_child + 1 + find_by_val(root -> right, val);
		else if (val < root -> val) 
            return find_by_val(root -> left, val);
		else
             return root -> left_child;
	} else {
	
		flag = 1;
		return -1;
	};
}
	

int main () {

	long long int n;
    int option; 
    long long int value; 
	scanf("%lld", &n);
	node *root = NULL;

    while (n > 0){
    scanf("%d", &option);
        
        if (option == 1){//option 1 insert to tree
            scanf("%lld",&value);
            root = insert(root, value);
        }else if(option == 2){//option 2 search for the value 
            scanf("%lld",&value);
            flag = 0;
            long long int rank = find_by_val(root, value) + 1;
			if (flag)
             printf("Data tidak ada\n");//print this if not found 
            else 
            printf("%lld\n", rank);// print index if found 
           

        }
        n--;

    }

    
	
	return 0;
}

