/*
* Пример 1-4
* Построение бинарного дерева и его обход тремя способами.
*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct Tree
{
  int value;
  Tree *left;
  Tree *right;
  Tree *parent;
} Tree;

Tree *create(int key)
{
  Tree *root = (Tree *)malloc(sizeof(Tree));
  root->value = key;
  root->parent = NULL;
  root->left = root->right = NULL;
  return root;
}

Tree *add(Tree *root, int key)
{
  Tree *root2 = root, *root3 = NULL;
  Tree *tmp = (Tree *)malloc(sizeof(Tree));
  tmp->value = key;
  while (root2 != NULL)
  {
    root3 = root2;
    if (key < root2->value)
      root2 = root2->left;
    else
      root2 = root2->right;
  }
  tmp->parent = root3;
  tmp->left = NULL;
  tmp->right = NULL;
  if (key < root3->value)
    root3->left = tmp;
  else
    root3->right = tmp;
  return root;
}

Tree *search(Tree *root, int key)
{
  if ((root == NULL) || (root->value = key))
    return root;
  if (key < root->value)
    return search(root->left, key);
  else
    return search(root->right, key);
}

void printHTree(Tree *p, int level, int bln)
{
  if (p)
  {
    printHTree(p->right, level + 1, 1);

    if (bln == 0)
    {
      printf(" ~%d\n", p->value);
    }
    for (int i = 0; i < level; i++)
    {
      if (i == 0)
        printf("   ");
      else
        printf("|  ");
    }
    if (bln == 1 && p->parent->right)
      printf("┌──%d\n", p->value);
    else if (bln == 2)
      printf("└──%d\n", p->value);
    printHTree(p->left, level + 1, 2);
  }
}

void preorder(Tree *root)
{
  if (root == NULL)
    return;
  if (root->value)
    printf("%d ", root->value);
  preorder(root->left);
  preorder(root->right);
}

void postorder(Tree *root)
{
  if (root == NULL)
    return;
  postorder(root->left);
  postorder(root->right);
  if (root->value)
    printf("%d ", root->value);
}

void inorder(Tree *root)
{
  if (root == NULL)
    return;
  inorder(root->left);
  if (root->value)
    printf("%d ", root->value);
  inorder(root->right);
}

int intRandom(int N)
{
  srand(time(NULL));
  return rand() % N + 1;
}
int main()
{
  int num, al;
  printf("Эта программа строит бинарное дерево из случайных чисел и выводит его на печать.\n");
  printf("Укажите количество элементов дерева: ");
  scanf("%d", &num);
  al = abs(num);
  int intArray[al];
  for (int i = 0; i < al; i++)
    intArray[i] = intRandom(i + al + 10);

  int intArrLength = sizeof intArray / sizeof *intArray;
  Tree *root = create(intArray[0]);
  for (int i = 1; i < intArrLength; i++)
    add(root, intArray[i]);
  printf("\n\n");
  printHTree(root, 0, 0);

  printf("\nОбход дерева сверху вниз:\n");
  preorder(root);
  printf("\nОбход дерева слева направо:\n");
  inorder(root);
  printf("\nОбход дерева снизу вверх:\n");
  postorder(root);

  printf("\n\n");

  return 0;
}
