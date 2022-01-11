#include <bits/stdc++.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

using namespace std;

// Buffer Size
const int N = 10;

// Semaphore and threads
sem_t sem_full, sem_empty;
pthread_mutex_t mutex_obj;

// Producer Consumer Buffer and index
int buf[N], idx = 0;

// Function Declaration
void * produce(void *);
void * consume(void *);
int rand_val();

// Main
int main(int argc, char const *argv[]){
    // Semaphore init
    sem_init(&sem_empty, 0, N);
    sem_init(&sem_full, 0, 0);
    
    // Threading 
    pthread_t producer, consumer;

    // Mutex init
    pthread_mutex_init(&mutex_obj, NULL);

    // Producer and Consumer
    pthread_create(&producer, NULL, produce, NULL);
    pthread_create(&consumer, NULL, consume, NULL);

    // Exit
    pthread_exit(NULL);
    return 0;
}

int rand_val(){
    return (int)(rand() % 100);
}

void * produce(void * arg){
    while(true){
        sleep(1);
        sem_wait(&sem_empty);
        int item = rand_val();
        buf[idx++] = item;
        cout << "Producer produced : " << item << endl;
        pthread_mutex_unlock(&mutex_obj);
        sem_post(&sem_full);
    }
}

void * consume(void * arg){
    while(true){
        sleep(1);
        sem_wait(&sem_full);
        pthread_mutex_lock(&mutex_obj);
        int item = buf[--idx];
        cout << "Consumer consumed : " << item << endl;
        pthread_mutex_unlock(&mutex_obj);
        sem_post(&sem_empty);
    }
}