/*
* Дан массив целых чисел. Решить поставленную задачу и 
* переставить найденный элемент обоими методами оптимизации поиска в начало 
* списка. Разработать и протестировать код на Си.
* 
* 15. Найти значение lg(x) от каждого элемента и переставить на 1 место 
* элемент, значение функции от которого максимально.
*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct PData
{
  int iData;
  double dData;
  struct PData *next;
} PData;

PData *first = NULL;
PData *last = NULL;

int searchPreceed(PData *table, double key)
{
  printf("Запрос: %lg - ", key);
  PData *q = NULL;
  PData *p = table;
  PData *search;
  while (p != NULL)
  {
    if (key == p->dData)
    {
      search = p;
      if (q == NULL)
      {
        printf("Перестановка не нужна\n");
        return 1;
      }
      else
        printf("Делаю перестановку\n");
      q->next = p->next;
      p->next = table;
      first = p;
    }
    q = p;
    p = p->next;
  }
  search = NULL;
  return 0;
}

int searchTranspose(PData *table, double key)
{
  printf("Запрос: %lg - ", key);
  PData *s = NULL;
  PData *q = NULL;
  PData *p = table;
  PData *search;
  while (p != NULL)
  {
    if (key == p->dData)
    {
      if (q == NULL)
      {
        printf("Перестановка не нужна\n");
        return 1;
      }
      else
        printf("Делаю перестановку\n");
      q->next = p->next;
      p->next = q;
      if (s == NULL)
        // table = p;
        first = p;
      else
      {
        s->next = p;
        search = p;
      }
    }
    s = q;
    q = p;
    p = p->next;
  }
  search = NULL;
  return 0;
}

/*
* Генераторы чисел: Фибоначчи, n! и случайных.
* vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
*/
int loopFib(int n)
{
  int Fib[n + 1];
  Fib[0] = 0;
  Fib[1] = 1;
  for (int i = 2; i <= n; ++i)
    Fib[i] = Fib[i - 1] + Fib[i - 2];
  return Fib[n];
}
int recFact(int n)
{
  if (n == 0)
    return 1;
  return (n <= 1) ? n : n * recFact(n - 1);
}
int intRandom(int N)
{
  srand(time(NULL));
  return rand() % N;
}
/*
* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
* Генераторы чисел: Фибоначчи, n! и случайных.
*/

void makeArray(int *intArray, int l)
{
  for (int i = 0; i < l; i++)
  {
    intArray[i] = intRandom(loopFib(i + 10));
  }
}

//Создание в памяти односвязного списка из данных файла
PData *makeList(int *numArr, int l)
{
  PData *node;
  // Заполняем структуру из массива
  for (int i = 0; i < l; i++)
  {
    // Размещаем новый узел в памяти.
    node = (PData *)malloc(sizeof(PData));
    if (node == NULL)
    {
      printf("Ошибка выделения памяти!\n");
      exit(404);
      // return 1;
    }
    // заполняем поля структруры полями строки текстового файла
    node->iData = numArr[i];
    node->dData = log10((double)numArr[i]);
    node->next = NULL;
    if (first != NULL)
    {
      last->next = node;
      last = node;
    }
    else
    {
      first = node;
      last = node;
    }
  }
  return node;
}

void printArray() {}
// Вывод списка на печать.
void printList(PData *node)
{
  node = first;
  while (node != NULL)
  {
    printf("%lg ", node->dData);
    node = node->next;
  }
}

double maxNumber(PData *node)
{
  double max = 0.0;
  while (node != NULL)
  {
    if (max < node->dData)
      max = node->dData;
    node = node->next;
  }
  return max;
}
int main()
{
  int x = 0, al;
  PData *node;
  printf("Эта программа вычисляет lg(x) для каждого целого числа из массива случайных чисел, находит наибольшее значение и переставляет это число на первое место с помощью разных методов оптимизации поиска.\n");
  printf("\nЗадайте количество случайных чисел в исходном массиве: ");
  scanf("%d", &al);
  int intArray[al];
  double logs[al], max;

  printf("\nИсходный массив:\n");
  makeArray(intArray, al);
  for (int i = 0; i < al; i++)
    printf("%d ", intArray[i]);
  printf("\n");
  printf("\nОдносвязный список десятичных алгоритмов чисел исходного массива:\n");
  node = makeList(intArray, al);
  printList(node);
  max = maxNumber(first);
  printf("\nНаибольшее число: %lg\n", max);
  printf("\nПоиск с перестановкой в начало:\n");

  while (x == 0)
  {
    x = searchPreceed(first, max);
  }
  printList(node);

  printf("\n\nПоиск с транспозицией:\n");
  x = 0;
  first = NULL;
  node = makeList(intArray, al);
  while (x == 0)
  {
    x = searchTranspose(first, max);
  }
  printList(node);
  printf("\n");

  return 0;
}
