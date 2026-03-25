#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t mutex;
sem_t wrt;

int readcount = 0;
int data = 0;

void* reader(void* arg){
    for(int i=0;i<5;i++){
        sem_wait(&mutex);
        readcount++;
        if(readcount == 1){
            sem_wait(&wrt);
        }
        sem_post(&mutex);

        printf("Reader %ld is reading data = %d\n",(long)arg,data);
        sleep(1);

        sem_wait(&mutex);
        readcount--;
        if(readcount == 0){
            sem_post(&wrt);
        }
        sem_post(&mutex);

        sleep(1);
    }
    return NULL;
}

void* writer(void* arg){
    for(int i=0;i<5;i++){
        sem_wait(&wrt);

        data++;
        printf("Writer %ld is writing data = %d\n",(long)arg,data);
        sleep(1);

        sem_post(&wrt);

        sleep(1);
    }
    return NULL;
}

int main(){
    pthread_t r1,r2,w1;

    sem_init(&mutex,0,1);
    sem_init(&wrt,0,1);

    pthread_create(&r1,NULL,reader,(void*)1);
    pthread_create(&r2,NULL,reader,(void*)2);
    pthread_create(&w1,NULL,writer,(void*)1);

    pthread_join(r1,NULL);
    pthread_join(r2,NULL);
    pthread_join(w1,NULL);

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
