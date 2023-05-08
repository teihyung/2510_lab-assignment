#include <stdio.h>
#include <stdlib.h>

typedef struct bnode
{
    int data;
    struct bnode *left;
    struct bnode *right;
} BinNode;

int Remove(BinNode **root, int data);
BinNode *Add1(BinNode *p, int data);
BinNode *Add2(BinNode *p, int data);

static BinNode *AllocBinNode(void)
{
    return calloc(1, sizeof(BinNode));
}

static void SetBinNode(BinNode *n, int data, BinNode *left, BinNode *right)
{
    n->data = data;
    n->left = left;
    n->right = right;
}

int Remove(BinNode **root, int data)
{
    BinNode *next, *temp;
    BinNode **left;
    BinNode **p = root;

    while (1)
    {
        if (*p == NULL)
        {
            printf("COMP2510ERROR: %d is not here\n", data);
            return -1;
        }
        else if (data == (*p)->data)
        {
            break;
        }
        else if (data < (*p)->data)
        {
            p = &((*p)->left);
        }
        else if (data > (*p)->data)
        {
            p = &((*p)->right);
        }
        else
        {
            *p = Add2(*p, (*p)->data);
        }
    }

    if ((*p)->left == NULL)
    {
        next = (*p)->right;
    }
    else
    {
        left = &((*p)->left);
        while ((*left)->right != NULL)
        {
            left = &(*left)->right;
        }
        next = *left;
        *left = (*left)->left;
        next->left = (*p)->left;
        next->right = (*p)->right;
    }
    temp = *p;
    *p = next;
    free(temp);

    return 0;
}

BinNode *Add1(BinNode *p, int data)
{
    if (p == NULL)
    {
        p = AllocBinNode();
        SetBinNode(p, data, NULL, NULL);
    }
    else if (data == p->data)
    {
        p->left = Add1(p->left, data);
    }
    else if (data < p->data)
    {
        //        Add(p->left, data);
        p->left = Add1(p->left, data);
    }
    else if (data > p->data)
    {
        //        Add(p->right, data);
        p->right = Add1(p->right, data);
    }
    return p;
}
BinNode *Add2(BinNode *p, int data)
{
    if (p == NULL)
    {
        p = AllocBinNode();
        SetBinNode(p, data, NULL, NULL);
    }
    else if (data == p->data)
    {
        //        printf("Error! There is same data\n");
        Remove(&p, p->data);
    }
    else if (data < p->data)
    {
        //        Add(p->left, data);
        p->left = Add2(p->left, data);
    }
    else if (data > p->data)
    {
        //        Add(p->right, data);
        p->right = Add2(p->right, data);
    }
    return p;
}

void PrintTree(FILE *fop, const BinNode *p)
{
    if (p != NULL)
    {
        fprintf(fop, "%d\n", p->data);
        PrintTree(fop, p->left);
        PrintTree(fop, p->right);
    }
}

void freeTree(BinNode *root)
{
    if (root == NULL)
    {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(int argc, char **argv)
{
    FILE *fip1, *fip2, *fop;
    int data;
    BinNode *root = NULL;
    char line[10];

    fip1 = fopen(argv[1], "r");
    fip2 = fopen(argv[2], "r");
    fop = fopen(argv[3], "w");

    if (fip1 == NULL || fip2 == NULL || fop == NULL)
    {
        printf("COMP2510ERROR: Failed to open file\n");
    }

    while (fscanf(fip1, "%d", &data) != EOF) {
        root = Add1(root, data);
    }
    while (fscanf(fip2, "%d", &data) != EOF) {
        root = Add2(root, data);
    }


    PrintTree(fop, root);

    fclose(fip1);
    fclose(fip2);
    fclose(fop);

    freeTree(root);

    return 0;
}
