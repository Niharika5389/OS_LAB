#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int n;
int *a;

void* fib(){
    if(n<=0) return NULL;

    a[0] = 0;
    if(n>1) a[1] = 1;

    for(int i=2;i<n;i++){
        a[i] = a[i-1] + a[i-2];
    }

    return NULL;
}

int main(){
    printf("Enter number of elements: ");
    scanf("%d",&n);

    if(n<=0){
        printf("Enter positive number\n");
        return 1;
    }
    a = malloc(n*sizeof(int));


    pthread_t t1;

    pthread_create(&t1,NULL,fib,NULL);
    pthread_join(t1,NULL);

    printf("Fibonacci: ");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");

    free(a);

    return 0;
}