/*
* Написать программу, которая обрабатывает файл input.txt и 
* составляет для него алфавитно-частотный словарь в файле output.txt.
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// эмулируем булевый тип для наглядности
#define TRUE 1
#define FALSE 0
typedef int BOOL;

// создаём структуру узла
typedef struct Node
{
  char *Word;
  int count; // это поле не нужно, можно удалить.
  struct Node *next;
} PNode;

PNode *Head = NULL;

/* создаём новый элемент списка типа PNode на основе переданного значения NewWord */
PNode *CreateNode(char *NewWord)
{
  PNode *NewNode;
  NewNode = (PNode *)malloc(sizeof(PNode));
  NewNode->Word = (char *)malloc(strlen(NewWord) + 1);
  strcpy(NewNode->Word, NewWord);
  NewNode->count = 1; //счётчик слов = 1
  NewNode->next = NULL;
  return NewNode;
}

/* Функция AddFirst добавляет новый элемент типа PNode в начало списка  */
PNode *AddFirst(PNode *head, PNode *NewNode)
{
  NewNode->next = head;
  return NewNode;
}

/* Функция AddLast добавляет новый элемент типа PNode в конец списка  */
PNode *AddLast(PNode *head, PNode *NewNode)
{
  PNode *p2;
  if (head == NULL)
    return NewNode;
  // находим конец списка
  for (p2 = head; p2->next != NULL; p2 = p2->next)
    ;
  p2->next = NewNode;
  return head;
}

/* Добавляем элемента в середину списка в алфавитном порядке*/
PNode *AddMiddle(PNode *head, PNode *NewNode)
{
  BOOL found = FALSE;
  PNode *p1, *p2;
  if (head == NULL)
  { // особый случай, когда список пуст
    head = AddFirst(head, NewNode);
    return head;
  }
  // Основной цикл. В переменную p2 сохраняем значение p1
  p2 = p1 = head;

  while (!found)
  {
    if (found == strcmp(p1->Word, NewNode->Word) < 0)
    {
      if (p1 == head)
      {
        head = AddFirst(head, NewNode);

        return head;
      }
      else
      { //Общий случай. Вставляем новое слово NewNode в список.
        p2->next = NewNode;
        NewNode->next = p1;
        return head;
      }
    }
    // если не найдено совпадений, то вставить слово в конец списка.
    if (p1->next == NULL)
    {
      head = AddLast(head, NewNode);
      return head;
    }

    // Сохраняемся перед заходом на новый виток.
    p2 = p1;
    p1 = p1->next;

  } // Конец цикла.
  return 0;
}

// для вывода на печать используем приём pointer-to-pointer
void PrintList(PNode **head)
{
  PNode **tracer = head, **sorter;
  int count = 1;
  while ((*tracer) != NULL)
  {
    sorter = tracer;
    tracer = &(*tracer)->next;
    if ((*tracer))
    {
      if ((strcmp((*tracer)->Word, (*sorter)->Word) == 0))
      {
        count++;
      }
      else
      {
        printf("%-15s\t%d\n", (*sorter)->Word, count);
        count = 1;
      }
    }
  }
}

// удаляем знаки препинания и приводим строки к нижнему регистру
// tolower - нижний регистр - работает только с символами ASCII!!!

void reformat_string(char *src)
{
  char *dst;
  dst = src;
  for (; *src; ++src)
    if (!ispunct((unsigned char)*src))
      *dst++ = tolower((unsigned char)*src);
  *dst = 0;
}

/* чтение файла выполняется дважды, поэтому процедура вынесена в отдельную функцию */
void ReadFile()
{
  FILE *in;
  char _word[80];
  int n;
  in = fopen("./lab3/input.txt", "r");
  if (in == NULL)
  {
    printf("Ошибка! Файл не найден.\n");
    // Выход из программы если указатель на файл возрващает NULL.
    exit(1);
  }
  while (1)
  {
    n = fscanf(in, "%s", _word); //читаем слово из файла
    if (n <= 0)
      break;
    reformat_string(_word);
    Head = AddMiddle(Head, CreateNode(_word));
  }
  fclose(in);
}

int main(int argc, char **argv)
{

  int count = 1;
  PNode *Sort;
  FILE *in, *out;
  out = fopen("./lab3/output.txt", "w");

  ReadFile();
  while (Head)
  {
    Sort = Head;
    Head = Head->next;

    if (Head != NULL)
    {
      if (strcmp(Sort->Word, Head->Word) == 0)
        count++;
      else
      {
        fprintf(out, "%-15s\t%d\n", Sort->Word, count);
        count = 1;
      }
    }
  }
  fclose(out);
  ReadFile();
  PrintList(&Head);

  return 0;
}
