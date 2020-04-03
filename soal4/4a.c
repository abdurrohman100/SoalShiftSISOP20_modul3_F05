#include<stdio.h> 
#include<pthread.h> 
#include<unistd.h> 
#include<stdlib.h> 
#include<time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
/*
  Lakukan perkalian untuk tiap baris dan tiap kolom
*/
void *mult(void* arg) 
{ 
  int *data = (int *)arg; 
  int k = 0, i = 0; 

  int x = data[0]; 
  for (i = 1; i <= x; i++) 
    k += data[i]*data[i+x]; 

  int *p = (int*)malloc(sizeof(int)); 
  *p = k; 

  pthread_exit(p); 
}

int main() 
{ 
  int matA[4][2];  
  int matB[2][5];  
  
  int baris1=4;
  int kolom1=2;
  
  int baris2=2;
  int kolom2=5;
  
  int i,j,k; 
  
  /*
    Create matrix
  */
  srand(time(NULL));
  for (i = 0; i < baris1; i++)  
    for (j = 0; j < kolom1; j++)  
       matA[i][j] = (rand() % 20) + 1;   

  for (i = 0; i < baris2; i++)  
    for (j = 0; j < kolom2; j++)
    matB[i][j] = (rand() % 20) + 1;  

  printf("Matrix 1:\n");
  for (i = 0; i < baris1; i++){ 
    for(j = 0; j < kolom1; j++) 
     printf("%d ",matA[i][j]); 
    printf("\n"); 
  } 
  printf("\n");  
  printf("Matrix 2:\n");
  for (i = 0; i < baris2; i++){ 
    for(j = 0; j < kolom2; j++) 
      printf("%d ",matB[i][j]); 
    printf("\n");     
  } 
  printf("\n");  

  /*
    Acces Shared Memory
  */
  key_t exchangeKey = 1111;
    int shmid = shmget(exchangeKey,22 * sizeof(int),0666| IPC_CREAT);
    //Attach SharedMemory
    int *sharedHasil = (int *) shmat(shmid,(void*)0,0);
  
  int max = baris1*kolom2; 
  sharedHasil[0]=baris1;
  sharedHasil[1]=kolom2;
  
  /*
    Make thread array
  */
  pthread_t *threads; 
  threads = (pthread_t*)malloc(max*sizeof(pthread_t)); 
  
  int threadCount = 0;    
  int* data = NULL; 
  /*
    Untuk tiap baris dan kolom lakukan perkalian pada thread
  */
  for (i = 0; i < baris1; i++) 
    for (j = 0; j < kolom2; j++) 
    { 
      
      data = (int *)malloc((20)*sizeof(int)); 
      data[0] = kolom1;
      
      for (k = 0; k < kolom1; k++) data[k+1] = matA[i][k]; 
      for (k = 0; k < baris2; k++) data[k+kolom1+1] = matB[k][j]; 
      
      pthread_create(&threads[threadCount++], NULL,  
      mult, (void*)(data)); 
    } 
  /*
    Cetak hasil
  */
  printf("Hasil:\n"); 
  for (i = 0; i < max; i++)  
  { 
    void *k; 
    pthread_join(threads[i], &k); 

    int *p = (int *)k; 
    printf("%d ",*p); 
    if ((i + 1) % kolom2 == 0) 
      printf("\n"); 
  }
  printf("\n");

  return 0; 
} 