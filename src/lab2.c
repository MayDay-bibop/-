#include "../include/lab2.h"



int main2() {
    int arr[MAXLEN];
    int n, methodChoice, typeChoice;

    printf("выбор метода сортировки:\n");
    printf("1 - пузырьком\n");
    printf("2 - шелла\n");
    scanf("%d", &methodChoice);

    if (methodChoice != 1 && methodChoice != 2) {
        printf("\nнеправильный выбор");
        return 1;
    }

    printf("\nспособ заполнения:\n");
    printf("1 - ввод с клавиатуры\n");
    printf("2 - генерация случайных чисел\n");
    printf("3 - чтение из файла\n");
    scanf("%d", &typeChoice);

    switch(typeChoice) {
        case 1:
        {
            printf("\nвведите длину массива (макс. %d): ", MAXLEN);
            scanf("%d", &n);
            printf("\nвведите массив длины %d:\n", n);
            for (int i = 0; i < n; i++) {
                scanf("%d", &arr[i]);
            }
            break;
        }
        case 2:
        {
            printf("\nвведите длину массива (макс. %d): ", MAXLEN);
            scanf("%d", &n);
            generate_random(arr, n);
            printf("\nсгенерированный массив:\n");
            print_array(arr, n);
            break;
        }
        case 3:
        {
            
            n = read_from_file(arr);

            printf("\nпрочитанный массив:\n");
            print_array(arr, n);
            break;
        }
        default:
            printf("\nне то нажал\n");
            return 1;
    }

    clock_t start = clock();

    switch(methodChoice) {
        case 1:
            bubble_sort(arr, n);
            break;
        case 2:
            shell_sort(arr, n);
            break;
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nмассив после сортировки:\n");
    print_array(arr, n);
    printf("\nвремя выполнения: %.6f сек\n", time_spent);

    return 0;
}
int read_from_file(int arr[]) {
    FILE *file = fopen("test2.txt", "rt");
    if(!file) return 0;

    int count = 0;
    while(fscanf(file, "%d", &arr[count]) == 1 && count < MAXLEN) {
        count++;
    }

    fclose(file);
    return count;
}
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void shell_sort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void generate_random(int arr[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
}


