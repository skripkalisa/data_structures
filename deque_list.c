/*
* Дек на основе двусвязного списка
*/

#include <malloc.h>
#include <stdio.h>

#define MAX 20
typedef struct dequeList
{
  int deque;
  struct dequeList *prev, *next; //ссылка на предыдущий и следующий узел
} dequeList;
struct dequeList *Head = NULL, *Tail = NULL;

/*
Функция типа struct для создания нового узла типа dequeList
*/
struct dequeList *createNode(int data)
{
  struct dequeList *newNode = (struct dequeList *)malloc(sizeof(struct dequeList)); // выделяем память под новый узел
  newNode->deque = data;
  //записываем аргумент в поле deque
  newNode->next = newNode->prev = NULL;
  // инициализируем ссылки на соседние элементы
  return (newNode);
}
void init() // Задаём начальные значениея для головы и хвоста дека
{
  Head = createNode(0);
  Tail = createNode(0);
  Head->next = Tail; //замыкаем голову на хвост,
  Tail->prev = Head; //и наоборот
}
void addTail()
{
  dequeList el;
  int elem, data;
  printf("Сколько элементов надо добавить справа? ");
  scanf("%d", &elem);
  for (int i = 0; i < elem; i++)
  {
    struct dequeList *newNode, *temp;
    data = elem * 100 + i;
    newNode = createNode(data);
    temp = Tail->prev;
    Tail->prev = newNode;
    newNode->next = Tail;
    newNode->prev = temp;
    temp->next = newNode;
  }
}

void addHead()
{
  int elem, data;
  printf("Сколько элементов надо добавить слева? ");
  scanf("%d", &elem);
  for (int i = 0; i < elem; i++)
  {
    struct dequeList *newNode, *temp;
    data = -elem * 10 - i;
    newNode = createNode(data);
    temp = Head->next;
    Head->next = newNode;
    newNode->prev = Head;
    newNode->next = temp;
    temp->prev = newNode;
  }
}

void deleteHead()
{
  struct dequeList *temp;
  if (Head->next == Tail)
  {
    printf("Queue is empty\n");
  }
  else
  {
    temp = Head->next;
    Head->next = temp->next;
    temp->next->prev = Head;
    printf("Удалённый элемент: %d\n", temp->deque);
    free(temp);
  }
  return;
}

void deleteTail()
{
  struct dequeList *temp;
  if (Tail->prev == Head)
  {
    printf("Дек пуст\n");
  }
  else
  {
    temp = Tail->prev;
    Tail->prev = temp->prev;
    temp->prev->next = Tail;
    printf("Удалённый элемент: %d\n", temp->deque);
    free(temp);
  }
  return;
}

void printDeque()
{
  struct dequeList *temp;
  if (Head->next == Tail)
  {
    printf("Дек пуст\n");
    return;
  }
  temp = Head->next;
  while (temp != Tail)
  {
    printf("%d ", temp->deque);
    temp = temp->next;
  }
  printf("\n");
}

void deque()
{
  int action;
  do
  {
    printf("Введите номер команды : ");
    scanf("%d", &action);
    getchar();
    switch (action)
    {
    case 1:
      addHead();
      printDeque();
      break;
    case 2:
      addTail();
      printDeque();
      break;
    case 3:
      deleteHead();
      printDeque();
      break;
    case 4:
      deleteTail();
      printDeque();
      break;
    case 5:
      printDeque();
      break;
    case 6:
      break;
    default:
      printf("Ошибка ввода. Не ломай программу!\n");
      break;
    }
  } while (action != 6);
}

int main()
{
  printf("1.Добавить элемент(ы) в начало дека\n");
  printf("2.Добавить элемент(ы) в конец дека\n");
  printf("3.Удалить элемент в начале дека\n");
  printf("4.Удалить элемент в конце дека\n");
  printf("5.Вывести дек на экран\n");
  printf("6.Выход из программы\n");
  init();
  deque();

  return 0;
}
