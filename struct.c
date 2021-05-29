/*
* Эта программа создаёт считывает список студентов из файла и выводит его в консоль. 
* Реализована проверка наличия файла на диске, а также целостность данных в файле. 
* Файл должен содержать список в таком формате:
* Номер Фамилия Имя Отчество Группа
* и заканчиваться пустой строкой.
*/

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXSZ 100

typedef struct Student
{
  char *listN;
  char *lastName;
  char *firstName;
  char *middleName;
  char *group;
  struct Student *next;
} PStudent;
PStudent *first = NULL;
PStudent *last = NULL;

int main(void)
{
  char line[MAXSZ], listN[3], lastName[MAXSZ], firstName[MAXSZ], middleName[MAXSZ], group[MAXSZ];
  FILE *in;
  PStudent *node;

  // Открываем файл для чтения.
  in = fopen("./lab2/group.txt", "r"); // Укажите свой файл!
  if (in == NULL)
  {
    printf("Ошибка открытия файла.\n");
    return 1;
  }

  // Читаем по строкам.
  while (fgets(line, sizeof(line), in) != NULL)
  {
    // Проверяем целостность файла (мало букафф или война и мир).
    if (line[0] == '\0')
    {
      printf("Строка слишком короткая.\n");
      return 1;
    }

    if (line[strlen(line) - 1] != '\n')
    {
      printf("Строка '%s' слишком длинная.\n", line);
      return 1;
    }

    line[strlen(line) - 1] = '\0';

    // Читаем поля в строке.
    if (sscanf(line, "%s %s %s %s %s",
               listN, lastName, firstName, middleName, group) != 5)
    {
      printf("В строке '%s' неверно заполнены поля.\n", line);
      return 1;
    }

    // Размещаем новый узел в памяти.
    node = malloc(sizeof(PStudent));
    if (node == NULL)
    {
      printf("Ошибка выделения памяти!\n");
      return 1;
    }

    // заполняем поля структруры полями строки текстового файла
    node->listN = strdup(listN);
    node->lastName = strdup(lastName);
    node->firstName = strdup(firstName);
    node->middleName = strdup(middleName);
    node->group = strdup(group);
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

  fclose(in);

  // Вывод списка на печать.
  node = first;
  while (node != NULL)
  {
    printf("%s %s %s %s %s \n",
           node->listN, node->lastName, node->firstName, node->middleName,
           node->group);
    node = node->next;
  }

  return 0;
}
