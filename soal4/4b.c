#include<stdio.h> 
#include<pthread.h> 
#include<unistd.h> 
#include<stdlib.h> 
#include<time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
/*
    Sum 1-n
*/
void *sum(void* arg) 
{ 
  int *data = (int *)arg; 
  int i,k = 0; 
  
  for (i = 1; i <= *data; i++) 
    k += i; 
  
  int *p = (int*)malloc(sizeof(int)); 
  *p = k; 
  pthread_exit(p); 
} 

int main() 
{ 
  
  /*
    Acces Shared Memory
  */
  key_t exchangeKey = 1111;
  int shmid = shmget(exchangeKey,22 * sizeof(int),0666| IPC_CREAT);
  int *sharedHasil = (int *) shmat(shmid,(void*)0,0);
  
  int i,j;
  int count=0;
  int max=sharedHasil[0]*sharedHasil[1];

  /*
    Print shared memory result
  */
  printf("{+]Matrix Hasil:\n");
  for (i = 0; i < sharedHasil[0]*sharedHasil[1]; i++)  
  { 
    printf("%d ",sharedHasil[i+2]); 
    if ((i + 1) % sharedHasil[1] == 0) 
      printf("\n"); 
  }
  printf("\n");
  
  /*
    Make thread array
  */
  pthread_t *threads; 
  threads = (pthread_t*)malloc((max)*sizeof(pthread_t)); 
  /*
    untuk tiap elemen pada array hasil lalukan operasi sum pada thread
  */
  for(i=0;i<max;i++){
    int* data= malloc(sizeof(*data));
    *data=sharedHasil[i+2];
    pthread_create(&threads[count++], NULL, sum, (void*)(data)); 
  }

  /*
    Join thread and print
  */
  printf("[+]Sigma Elemen Matrix:\n"); 
  for (i = 0; i < max; i++)  
  { 
    void *k; 
    pthread_join(threads[i], &k); 

    int *p = (int *)k;

    printf("%d ",*p); 
    if ((i + 1) % sharedHasil[1] == 0) {
      printf("\n"); 
    }
  }
  
  printf("\n");
  
  return 0; 
} 