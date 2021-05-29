#include <stdio.h>

#define MAX 20

int dequeArray[MAX];
int Head = -1;
int Tail = -1;

void addTail()
{
  int elem;
  printf("Сколько элементов надо добавить справа? ");
  scanf("%d", &elem);
  for (int i = 0; i <= elem; i++)
  {
    if ((Head == 0 && Tail == MAX - 1) || (Head == Tail + 1))
    {
      printf("Дек переполнен\n");
      return;
    }
    if (Head == -1) /* проверяем наличие элементов в деке */
    {
      Head = 0;
      Tail = 0;
    }
    else if (Tail == MAX - 1) /*Tail в конце дека? */
      Tail = 0;
    else
      Tail = Tail + 1;
    dequeArray[Tail] = elem * 100 + i;
  }
}

void addHead()
{
  int elem;
  printf("Сколько элементов надо добавить слева? ");
  scanf("%d", &elem);
  for (int i = 0; i <= elem; i++)
  {
    if ((Head == 0 && Tail == MAX - 1) || (Head == Tail + 1))
    {
      printf("Дек переполнен\n");
      return;
    }
    if (Head == -1) /*Проверяем, пуст ли дек*/
    {
      Head = 0;
      Tail = 0;
    }
    else if (Head == 0)
      Head = MAX - 1;
    else
      Head = Head - 1;
    dequeArray[Head] = -elem * 10 - i;
  }
}

void deleteHead()
{
  if (Head == -1)
  {
    printf("Дек не заполнен\n");
    return;
  }
  printf("Удалённый элемент: %d\n", dequeArray[Head]);
  if (Head == Tail) /*В деке всего один элемент */
  {
    Head = -1;
    Tail = -1;
  }
  else if (Head == MAX - 1)
    Head = 0;
  else
    Head = Head + 1;
}

void deleteTail()
{
  if (Head == -1)
  {
    printf("Дек не заполнен\n");
    return;
  }
  printf("Удалённый элемент: %d\n", dequeArray[Tail]);
  if (Head == Tail) /*в деке всего один элемент*/
  {
    Head = -1;
    Tail = -1;
  }
  else if (Tail == 0)
    Tail = MAX - 1;
  else
    Tail = Tail - 1;
}

void printDeque()
{
  int Front = Head, Rear = Tail;
  if (Head == -1)
  {
    printf("Дек пуст\n");
    return;
  }
  printf("Элементы дека :\n");
  if (Front <= Rear)
  {
    while (Front <= Rear)
    {
      printf("%d ", dequeArray[Front]);
      Front++;
    }
  }
  else
  {
    while (Front <= MAX - 1)
    {
      printf("%d ", dequeArray[Front]);
      Front++;
    }
    Front = 0;
    while (Front <= Rear)
    {
      printf("%d ", dequeArray[Front]);
      Front++;
    }
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
  deque();

  return 0;
}
