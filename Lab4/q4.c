#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int n;             
int *arr;         


void* bubbleSort() {
    int a[n];
    for (int i = 0; i < n; i++) a[i] = arr[i];

    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (a[j] > a[j+1]) {
                int t = a[j]; 
                a[j] = a[j+1]; a
                [j+1] = t;
            }

    printf("Bubble Sort: ");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");

    return NULL;
}


void* selectionSort() {
    int a[n];
    for (int i = 0; i < n; i++) a[i] = arr[i];

    for (int i = 0; i < n-1; i++) {
        int min = i;
        for (int j = i+1; j < n; j++){
            if (a[j] < a[min]) 
                min = j;
        }
        int t = a[i]; 
        a[i] = a[min]; 
        a[min] = t;
    }

    printf("Selection Sort: ");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");

    return NULL;
}


void* insertionSort() {
    int a[n];
    for (int i = 0; i < n; i++) a[i] = arr[i];

    for (int i = 1; i < n; i++) {
        int key = a[i], j = i-1;
        while (j >= 0 && a[j] > key) { 
            a[j+1] = a[j]; 
            j--; 
        }
        a[j+1] = key;
    }

    printf("Insertion Sort: ");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");

    return NULL;
}

int main() {
    printf("Enter number of elements: ");
    scanf("%d", &n);

    arr = malloc(n * sizeof(int));
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    pthread_t t1, t2, t3;

    pthread_create(&t1, NULL, bubbleSort, NULL);
    pthread_create(&t2, NULL, selectionSort, NULL);
    pthread_create(&t3, NULL, insertionSort, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("Original array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    free(arr);
    return 0;
}
