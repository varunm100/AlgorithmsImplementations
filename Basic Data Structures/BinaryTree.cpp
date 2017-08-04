#include <stdio.h>
#include <iostream>
#include <stdlib.h>
//#include <conio.h>

using namespace std;

struct treeNode
{
    int data;
    treeNode *left;
    treeNode *right;
};
treeNode* FindMin(treeNode *node)
{
    if(node==NULL)
    {
        return NULL;
    }
    if(node->left)
        return FindMin(node->left);
    else
        return node;
}

treeNode *Insert(treeNode *node,int data)
{
    if(node==NULL)
    {
        treeNode *CurrentCounter;
        CurrentCounter=new treeNode;
        CurrentCounter -> data = data;
        CurrentCounter -> left = CurrentCounter -> right = NULL;
        return CurrentCounter;
    }
    if(data >(node->data))
    {
        node->right = Insert(node->right,data);
    }
    else if(data < (node->data))
    {
        node->left = Insert(node->left,data);
    }
    return node;
}

treeNode * Delet(treeNode *node, int data)
{
    treeNode *CurrentCounter;
    if(node==NULL)
    {
        cout<<"Core Dump, JK, JK, JK, LOL, you are accessing something which you are not supposed to";
    }
    else if(data < node->data)
    {
        node->left = Delet(node->left, data);
    }
    else if(data > node->data)
    {
        node->right = Delet(node->right, data);
    }
    else
    {
        if(node->right && node->left)
        {
            CurrentCounter = FindMin(node->right);
            node -> data = CurrentCounter->data;
            node -> right = Delet(node->right,CurrentCounter->data);
        }
        else
        {
            CurrentCounter = node;
            if(node->left == NULL)
                node = node->right;
            else if(node->right == NULL)
                node = node->left;
            free(CurrentCounter);
        }
    }
    return node;
}

treeNode * Find(treeNode *node, int data)
{
    if(node==NULL)
    {
        return NULL;
    }
    if(data > node->data)
    {
        return Find(node->right,data);
    }
    else if(data < node->data)
    {
        return Find(node->left,data);
    }
    else
    {
        return node;
    }
}
void Inorder(treeNode *node)
{
    if(node==NULL)
    {
        return;
    }
    Inorder(node->left);
    cout<<node->data<<" ";
    Inorder(node->right);
}
void PrintOutBinaryTree(treeNode *node)
{
    if(node==NULL)
    {
        return;
    }
    cout << node -> data << " ";
    PrintOutBinaryTree(node->left);
    PrintOutBinaryTree(node->right);
}

int main()
{
    treeNode *root = NULL,*CurrentCounter;
    root = Insert(root, 10);
    root = Insert(root, 120);
    root = Insert(root, 3);
    root = Insert(root, 12);
    root = Insert(root, 5);
    root = Insert(root, 100);
    root = Insert(root, 80);
    root = Insert(root, 70);
    printf("%s\n", "Before: ");
    PrintOutBinaryTree(root);
    root = Delet(root, 70);
    root = Delet(root, 5);
    printf("%s\n", "After: ");
    PrintOutBinaryTree(root);
    return 0;
}