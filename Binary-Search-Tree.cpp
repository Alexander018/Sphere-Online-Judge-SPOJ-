//Question: https://www.spoj.com/problems/SDITSBST/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct node {//create node
    long long val,pos;
    struct node *left;//ledt sub tree of said node
     struct node *right;//right sub tree of said node
} Node;
 
typedef struct bst {//create binary search tree struct
    Node *_root;
    unsigned int size;
} BST;
 
 
Node* make(long long value) {//make tree
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->val = value;
    newNode->pos= 0;
    newNode->left = newNode->right = NULL;
    return newNode;
}
 

Node* insert(Node *root, long long value) {//insert node
    Node *temp = NULL;
    if (root == NULL) {
        temp = make(value);
   
        return temp;    
    }
 
    if (value < root->val){
        root->left = insert(root->left, value);
    }
    else if (value > root->val){
        root->pos++;
        root->right = insert(root->right, value);
    }
    
    return root;
}
 
Node* search(Node *root, int value) {//search for said node
    while (root != NULL) {
        if (value < root->val)
            root = root->left;
        else if (value > root->val)
            root = root->right;
        else
            return root;
    }
    return root;
}
 
 
void initialize(BST *bst) {//initialize the tree to empty tree
    bst->_root = NULL;
    bst->size = 0;
}
 
 
long long bst_post(Node *bst, long long value) {//find position 
    Node *temp = bst;
    if (temp == NULL)
        return -1;
    if( temp->val > value){
        long long index = bst_post(temp->left, value);
        if(index == -1) 
            return -1;
        else 
            return index + temp->pos + 1;
    } else if (temp->val<value){
        return bst_post(temp->right, value);
    }else
        return temp->pos;
}
bool find(BST *bst, int value) {//find in bst 
    Node *temp = search(bst->_root, value);
    if (temp == NULL)
        return false;
    
    if (temp->val == value)
        return true;
    else
        return false;
}
void bst_insert(BST *bst, long long value) {//insert in bst
    if (!find(bst, value)) {
        bst->_root = insert(bst->_root, value);
        bst->size++;
    }
}

int main(){
    BST tree;
    initialize(&tree);
    long long int  num; //num of nodes
    long long int  option;//what option 1 or 2
    long long int value; //value to be inserted or search 
    long long int s = 0; // place holder to return index of the desire node

    scanf("%lld", &num);

    while (num > 0){//cgoes through all the nodes the input says it will have
        scanf("%lld", &option);
        
        if (option == 1){//option 1 insert to tree
            scanf("%lld",&value);
            bst_insert(&tree,value);
        }else if(option == 2){//option 2 search for the value 
            scanf("%lld",&value);
            s = bst_post(tree._root, value);
            if (s == -1)//it is not in the tree if true 
            printf("Data tidak ada\n");//print this weird word
            else 
            printf("%lld\n", s+1);//print index of location 

        }
        num--;
    }
    return 0;
}