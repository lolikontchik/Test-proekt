#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <C:\\failiki\Bob.h>
int main()
{
    setlocale(LC_ALL, "Rus");
    int n, lf, rt;
    printf("Введите размер массива n: ");
    scanf_s("%d", &n);
    printf("Введите границы случайных чисел [lf, rt]: ");
    scanf_s("%d %d", &lf, &rt);
    if (n <= 0)
    {
        printf("Ошибка\n");
        return 1;
    }
    if (lf > rt)
    {
        printf("Ошибка\n");
        return 1;
    }
    const char* fname = "data.txt";
    const char* backup = "backup.txt";
    Create_File(fname, n, lf, rt);

    FILE* fsrc;
    FILE* fdst;
    fopen_s(&fsrc, fname, "r");
    fopen_s(&fdst, backup, "w");
    if (fsrc != NULL && fdst != NULL)
        CopyFile(fsrc, fdst);
    if (fsrc != NULL) fclose(fsrc);
    if (fdst != NULL) fclose(fdst);

    int* arr = new int[n];
    int* temp = new int[n];

    FILE* f;
    errno_t err = fopen_s(&f, fname, "r");
    if (err != 0)
    {
        perror("Ошибка открытия файла для чтения");
        delete[] arr;
        delete[] temp;
        return 1;
    }
    int i;
    for (i = 0; i < n; i++)
        fscanf_s(f, "%d", &arr[i]);
    fclose(f);

    if (n <= 30)
    {
        printf("Исходный массив: ");
        Print_File(fname);
        printf("\n\n");
    }

    clock_t start, end;
    double t;

    for (i = 0; i < n; i++) temp[i] = arr[i];
    start = clock();
    SelectionSort(temp, n);
    end = clock();
    t = (double)(end - start) / CLOCKS_PER_SEC;
    if (n <= 30)
    {
        printf("Прямой выбор:");
        PrintArray(temp, n);
    }
    printf("Время прямого выбора:   %.6f сек\n\n", t);

    for (i = 0; i < n; i++) temp[i] = arr[i];
    start = clock();
    BinaryInsertionSort(temp, n);
    end = clock();
    t = (double)(end - start) / CLOCKS_PER_SEC;
    if (n <= 30)
    {
        printf("Вставка с дв. поиском:  ");
        PrintArray(temp, n);
    }
    printf("Время вставки: %.6f сек\n\n", t);

    for (i = 0; i < n; i++) temp[i] = arr[i];
    start = clock();
    BubbleSort(temp, n);
    end = clock();
    t = (double)(end - start) / CLOCKS_PER_SEC;
    if (n <= 30)
    {
        printf("Пузырек:");
        PrintArray(temp, n);
    }
    printf("Время пузырька:  %.6f сек\n", t);

    delete[] arr;
    delete[] temp;

    return 0;
}