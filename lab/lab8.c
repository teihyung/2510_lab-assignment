#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode{
    int data;
    struct TreeNode *right;
    struct TreeNode *left;
} TreeNode;

void insertNode(TreeNode **root, int data){
    if(*root == NULL){
        *root = (TreeNode*) malloc(sizeof(TreeNode));
        (*root)->data = data;
        (*root)->left = NULL;
        (*root)->right = NULL;
    }
    else if(data < (*root)->data){
        insertNode(&((*root)->left), data);
    }
    else{
        insertNode(&((*root)->right), data);
    }
}

void inorder(TreeNode *root, FILE *fop){
    if(root == NULL){
        return;
    }
    inorder(root->left, fop);
    fprintf(fop, "%d\n", root->data);
    inorder(root->right, fop);
}

void freeTree(TreeNode * root){
    if(root == NULL){
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(int argc, char **argv){
    FILE *fip, *fop;
    TreeNode *root = NULL;
    int data;

    fip = fopen(argv[1], "r");
    fop = fopen(argv[2], "w");

    while(fscanf(fip, "%d", &data) == 1){
        insertNode(&root, data);
    }

    inorder(root, fop);

    fclose(fip);
    fclose(fop);
    freeTree(root);
    return 0;
}
