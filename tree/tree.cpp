/*
Date: Sometime in 2018 first quarter
Author: Maulik Soni
Author's github id: soni-maulik
Author email: Maulik.Soni@GMail.com


Program Description:
This program builds and displays a simple BST(Binary Search Tree) data structure

*/

#include <iostream>

using namespace std;
typedef struct Node
{
  int d;
  struct Node* l;
  struct Node* r;

  Node() { d=0; l = r = NULL; }
  Node(int x) { d = x; l = r = NULL; }
}Node;

void ShowInOrder(Node* r)
{
  if(r == NULL)	return;
  ShowInOrder(r->l);
  cout << r->d << ",";
  ShowInOrder(r->r);
}

void ShowPreOrder(Node* r)
{
  if(r == NULL)	return;
  cout << r->d << ",";
  ShowPreOrder(r->l);
  ShowPreOrder(r->r);
}

void ShowPostOrder(Node* r)
{
  if(r == NULL) return;
  ShowPostOrder(r->l);
  ShowPostOrder(r->r);
  cout << r->d << ",";
}

Node* InsertBST(Node* r, Node* n)
{
  if(r == NULL)	return n;
  if(n->d <= r->d)
  {
    if(r->l != NULL)
      InsertBST(r->l, n);
    else {
      r->l = n;
    }
  } else {
    if(r->r != NULL)
      InsertBST(r->r, n);
    else {
      r->r = n;
    }
  }
  return r;
}

Node* InsertBST(int a[], int sz)
{
  Node* root = NULL;
  for(int i=0; i<sz; ++i) {
    root = InsertBST(root, new Node(a[i]));
    //ShowInOrder(root);	cout << endl;
  }
  return root;
}

int main(int gc, char* gv[])
{
  Node* r = NULL;
  int a[5] = { 5, 2, 1, 3, 4 };
  r = InsertBST(a, 5);

  ShowInOrder(r); cout <<endl;
  ShowPreOrder(r); cout << endl;
  ShowPostOrder(r); cout << endl;

  cout << endl;
}

