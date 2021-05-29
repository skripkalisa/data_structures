/*
* Задание 2. 
* Динамические массивы – заполнение двумерных массивов различными способами. 
* Входной параметр, определяющий размерность массива: n. 
* Вывод полученного массива на консоль в удобном для пользователя, «читабельном» виде.
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
  int n = 0;
  float **matrix_mxn, *column;
  printf("Введите размер квадратной матрицы: ");
  scanf("%d", &n);

  column = (float *)malloc(n * sizeof(float)); // Выделяем память под столбец column
  if (column == NULL)
  {
    puts("Не создан динамический массив!");
    return -1;
  }
  matrix_mxn = (float **)malloc(sizeof(float *) * n); // Выделяем память под массив  указателей
  if (matrix_mxn == NULL)
  {
    puts("Не создан динамический массив!");
    return -2;
  }

  for (int i = 0; i < n; i++)
  {
    matrix_mxn[i] = (float *)malloc(sizeof(float) * n); // Выделяем память под i-ю строку
    if (NULL == matrix_mxn[i])
    {
      puts("Не создан динамический массив!");
      return -3;
    }
    for (int j = 0; j < n; j++)
      if (i == j)
        matrix_mxn[i][j] = n;
      else if (i > j)
        matrix_mxn[i][j] = n - i + j;
      else
        matrix_mxn[i][j] = 0;
  }
  for (int j = 0; j < n; j++)
  {
    column[j] = 0;
    for (int i = 0; i < n; i++)
    {
      column[j] += matrix_mxn[i][j];
    }
  }

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
      printf("%-3g", matrix_mxn[i][j]);
    printf("\n");
  }

  for (int i = 0; i < n; i++)
    free(matrix_mxn[i]); //Освобождаем память i – й строки
  free(matrix_mxn);      // Освобождаем память массива указателей
  free(column);          // Освобождаем память массива сумм
  return 0;
}
