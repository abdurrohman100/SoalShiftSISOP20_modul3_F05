----------
# SoalShiftSISOP20_modul2_F5
Repository Praktikum Sisop 1

5111840000100-ABDUR ROHMAN

5111840000166-FERALDY NATHANAEL

----------
# SoalShiftSISOP20_modul2_F5
Repository Praktikum Sisop 1

5111840000100-ABDUR ROHMAN

5111840000166-FERALDY NATHANAEL

## Penjelasan Penyelesaian Soal nomor 3
Pada soal nomor 3 kita diminta untuk membuat program yang dapat mengkategorikan file-file dalam sebuah direktori. File-file tersebut akan dikategorikan dan dimasukkan ke dalam direktori baru berdasarkan ekstensi dari file tersebut. Program ini dapat menerima 3 jenis argumen / berjalan dalam 3 mode. 

Mode 1 yaitu -f, mode -f akan mengkategorikan file-file yang diminta oleh user. Mode 2 yaitu -d, mode -d akan mengkategorikan file-file dalam direktori yang diminta oleh user. Terakhir yaitu mode \*. Mode \* akan mengkategorikan file-file dalam direktori dimana file program ini berada.

```
int main (int arg,char *argmode[]){
    sprintf(truepath,"%s",getcwd(cwd2,sizeof(cwd2)));
    if(argmode[1][0]=='*'){
        categorize1();
    }
    else if(argmode[1][1]=='d'){
        char path[1024];
        strcpy(path,argmode[2]);
        printf("%s\n",path);
        categorize2(path);
    }
    else {
        int l;
        for(l=2;argmode[l]!=NULL;l++){
            int err;
            err = pthread_create(&(tid[i]),NULL,&solver3,argmode[l]);
            if(err!=0){
                printf("error\n");
            }
            i++;
        }
    }
    int iter;
    for(iter=0;iter<=i;iter++){
        pthread_join(tid[iter],NULL);
    }
    return(0);
}
```
Pada fungsi main, jika argumen * maka akan memanggil fungsi categorize1. Jika argumen d maka akan memanggil fungsi categorize2 dan terakhir jika argumen f maka akan langsung membuat thread-thread tiap argumen yang diterima. 

```
void categorize1(){
    d = opendir(".");
        if(d){
        while((dir = readdir(d))!=NULL){
            if(dir->d_type != DT_DIR){ 
                int err;
                err = pthread_create(&(tid[i]),NULL,&solver1,dir->d_name);
                if(err!=0){
                    printf("error\n");
                }
                i++;
            }
        }
    closedir(d);
        }
}

void categorize2(char* path){ 
    chdir(path);
    d = opendir(path);
    
        if(d){
        while((dir = readdir(d))!=NULL){
            if(dir->d_type != DT_DIR){ 
                int err;
                err = pthread_create(&(tid[i]),NULL,&solver2,dir->d_name);
                if(err!=0){
                    printf("error\n");
                }
                i++;
            }
        }
        closedir(d);
        }
}
```
Pada fungsi categorize 1 dan 2, akan dibuka direktori sesuai yang diminta. Lalu akan dibaca semua file di dalamnya. Jika file yang dibaca bukan merupakan sebuah direktori maka nama file tersebut akan di parsing sebagai sebuah argumen ke dalam sebuah thread. Hal ini akan terjadi terhadap semua file yang dibaca dalam direktori yang diminta. 

```
void* solver1 (void* args){
   //printf("masuk thread\n");
    char* dname ;
    dname =  (char *) args;
 //  printf("%s\n",dname);
    int flag=0;
    int lenght = strlen(dname);
                char nama[lenght+1],ekstensi[10],nmdir[1000];
                strcpy(nama,dname);
                for(z=0;lenght>0;lenght--){
                    if(nama[lenght]=='.'){
                        flag=1;
                        break;
                    } 
                }
                if(flag==0){
                    strcpy(ekstensi,"Uknown");
                }
                else strcpy(ekstensi,nama+lenght+1);

                int k;
                for(k=0;k<strlen(ekstensi);k++){
                    ekstensi[k]=tolower(ekstensi[k]);
                }

                
                char dest[1024];
                char cwd[1024];
                
                sprintf(dest,"%s/%s/%s",getcwd(cwd,sizeof(cwd)),ekstensi,nama);
                sprintf(nmdir,"%s/%s",truepath,ekstensi);
                mkdir(nmdir,0777);
                if(rename(nama,dest)!=0){
                    char ekstensi2[1024];
                    char dest2[1024];
                    sprintf(ekstensi2,"\\%s",ekstensi);
                    sprintf(dest2,"%s/%s/%s",getcwd(cwd,sizeof(cwd)),ekstensi2,nama);
                    mkdir(ekstensi2,0777);
                    rename(nama,dest2);
                }
                
                
                pthread_exit(NULL);

}

void* solver3 (void* args){
  //  printf("masuk thread 3\n");
    char* dname ;
    dname =  (char *) args;
    int flag=0;
    int lenght = strlen(dname);
                char nama[lenght+1],nama2[lenght+1],ekstensi[10],nmdir[1000];
                strcpy(nama,dname);
                for(z=0;lenght>0;lenght--){
                    if(nama[lenght]=='.'){
                        flag=1;
                        break;
                    }  
                }
                if(flag==0){
                    strcpy(ekstensi,"Uknown");
                }
                else strcpy(ekstensi,nama+lenght+1);

                lenght = strlen(dname);
                for(z=0;lenght>0;lenght--){
                    if(nama[lenght]=='/'){
                        break;
                    }  
                }
                strcpy(nama2,nama+lenght+1);

                int k;
                for(k=0;k<strlen(ekstensi);k++){
                    ekstensi[k]=tolower(ekstensi[k]);
                }
                char cwd[1024];
                sprintf(nmdir,"%s/%s",truepath,ekstensi);
                mkdir(nmdir,0777);

                char dest[1024];
                sprintf(dest,"%s/%s",nmdir,nama2);

                
                if(rename(nama,dest)!=0){
                    char ekstensi2[1024];
                    char dest2[1024];
                    sprintf(ekstensi2,"\\%s",ekstensi);
                    sprintf(dest2,"%s/%s/%s",getcwd(cwd,sizeof(cwd)),ekstensi2,nama2);
                    printf("dest2 = %s\n",dest2);
                    mkdir(ekstensi2,0777);
                    rename(nama,dest2);
                }
                pthread_exit(NULL);

}

void* solver2 (void* args){
   // printf("masuk thread\n");
    char* dname;
    dname = (char *) args;
    int flag=0;
    int lenght = strlen(dname);
                char nama[lenght+1],ekstensi[10],nmdir[1000];
                strcpy(nama,dname);
                for(z=0;lenght>0;lenght--){
                    if(nama[lenght]=='.'){
                        flag=1;
                        break;
                    }  
                }
                if(flag==0){
                    strcpy(ekstensi,"Uknown");
                }
                else strcpy(ekstensi,nama+lenght+1);
                int k;
                for(k=0;k<strlen(ekstensi);k++){
                    ekstensi[k]=tolower(ekstensi[k]);
                }
                char cwd[1024];
                sprintf(nmdir,"%s/%s",truepath,ekstensi);
                mkdir(nmdir,0777);
                char dest[1024];
                sprintf(dest,"%s/%s/%s",truepath,ekstensi,nama);
               // printf("%s\n",dest);
                rename(nama,dest);
                pthread_exit(NULL);

}
```
Terakhir, pada fungsi solver yang dijalankan oleh thread. Secara umum, pertama-tama  nama file yang diterima dari argumen akan dibaca dari belakang. Nama akan dibaca dari belakang sampai ditemukan karakter '.' yang menandakan string setelah karakter '.' adalah ekstensi dari file tersebut. Setelah ekstensi dari file didapat, akan dilakukan iterasi untuk merubah ekstensi menjadi huruf kecil semua sehingga program berjalan tidak case sensitive. Selanjutnya akan digunakan fungsi mkdir untukk membuat direktori dengan nama ekstensi yang di dapat tadi. Dari situ kita bisa melakukan rename untuk 'memindahkan' file tersebut ke dalam direktori yang dibuat. 

## Penjelasan Penyelesaian Soal nomor 4
### 4a
Pada nomor 4a  kita diminta untuk mebuat program perkalian matrix antara sebuah matrix 4x2 dan 2x5. Isi matrix adalah angka 1-20 di definiskan dalam kodingan kemudian menampilkanya ke layar. Program harus menggunakan thread. Soal ini berhungan dengan soal 4b dimana hasil dari 4a akan dipakai oleh 4b maka dari itu pada progrma ini juga mengimplementasikan shared memory
Fungsi utama pada program adalah mult dimana fungsi ini akan malakukan perkalian pada setiap baris matrix pertama dan dengan setipa baris matrix kedua. Fungsi ini menerima inputan berupa array yang memeiliki data bertipe integer yang berisi panjang kolom matrix pertama, panjang baris matrix kedua, kemudian elemen selanjutnya adalah elemen pada baris pertama matrix pertama sebanyak panjang kolom matrix pertama, kemudian dilanjutkan kolom pertama pada matrix kedua sebanyak jumlah baris matrix kedua .
```
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
```
Kemudain  untuk membuat isi matrixnya kami gunakan fungsi rand%20 + 1
```
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
```
kemudian untuk menjawab nomor 4b kami menggunakna shared memory dimana memory yang di share adalah array pointer to integer shareHasil
```
key_t exchangeKey = 1111;

int shmid = shmget(exchangeKey,22 * sizeof(int),0666| IPC_CREAT);

//Attach SharedMemory

int *sharedHasil = (int *) shmat(shmid,(void*)0,0);

int max = baris1*kolom2;

sharedHasil[0]=baris1;

sharedHasil[1]=kolom2;


```
Kemudian kami membuat variable array void data untuk menampung setiap elemen pada baris i matrix pertama dan baris j pada matrix kedua. 
Kemudain setelah itu thread akan dibuat dan menjalankan fungsi mult dengan passing variable data untuk setiap i dan j.
```
pthread_t *threads;

threads = (pthread_t*)malloc(max*sizeof(pthread_t));

int threadCount = 0;

int* data = NULL;


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

```
Kemudian thread sati persatu dijoin return value dari threadnya yang kemudian ditampung ke variable void *k . Kemudain hasilnya dicetak sesuai format.
```

printf("Hasil:\n");

for (i = 0; i < max; i++)

{

void *k;

pthread_join(threads[i], &k);

int *p = (int *)k;

sharedHasil[i+2]=*p;

printf("%d ",*p);

if ((i + 1) % kolom2 == 0)

printf("\n");

}

printf("\n");

return 0;

}
```

### 4b 
Pada nomor 4b kita diminta mendapatkan hasil 4 a dan mencetaknya kemudian untuk setiap elemen n pada matrix hasil lakukan penjumlahan 1-n. implementasikan shared memory dan thread.
Untuk fungsi menjumlahkan 1-n digunakan fungsi sum. Fungsi ini akan berjalan pada thread. PDengan argumen yang diharapkan adalah integer elemen hasil dari perkalian matrix. Untuk argumen yang diberikan lakukan penjumlahan dari 1 sampai argumen itu. Kemudian kembalikan hasil perkalianya.
```
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
```
Yang pertama dilakukan adalaha mengambil shared momory yang sudah disiapkan oleh program 4a. Shared memorynya akan ditampung di variable pointer to integer sharedhasil
```
int main()

{

key_t exchangeKey = 1111;

int shmid = shmget(exchangeKey,22 * sizeof(int),0666| IPC_CREAT);

int *sharedHasil = (int *) shmat(shmid,(void*)0,0);
```
Kemudain print shared memory yang didapatkan.
```
int i,j;

int count=0;

int max=sharedHasil[0]*sharedHasil[1];


printf("{+]Matrix Hasil:\n");

for (i = 0; i < sharedHasil[0]*sharedHasil[1]; i++)

{

printf("%d ",sharedHasil[i+2]);

if ((i + 1) % sharedHasil[1] == 0)

printf("\n");

}

printf("\n");


```
kemudain untuk setiap elemen pada matrixnya akan di hitunng sum nya menggunakan fungsi sum dengan menggunakan thread.
```

pthread_t *threads;
threads = (pthread_t*)malloc((max)*sizeof(pthread_t));


for(i=0;i<max;i++){
int* data= malloc(sizeof(*data));
*data=sharedHasil[i+2];
pthread_create(&threads[count++], NULL, sum, (void*)(data));

}
```
kemudian threadnya di join dan return valuenya ditampung ke varaible void* k kemudian dicetak sesuai format.
```

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
```
### 4c
Pada nomor 4c kita diminta mengimplementasikan perintah ls | wc -l menggunakan pipes.
Pertama adalah deklarasikan variable yang dibutuhkan. Deklarasikan file discriptor untuk pipes yaitu int fd[2] untuk mengimplementasikan pipes. fd[0] akan menjadi read end pipes dan fd[1] akan menjadi write end pipes. 
Kemudian lakukan pipes pada fd. Kemudian lakukan fork.
```
int main(){

pid_t pid;

int status;

int fd[2];

pipe(fd);

pid=fork();

if(pid<0){

perror("Fork Gagal");

exit(EXIT_FAILURE);

}
```
Pada proses analk hasil dari stdout akan diduplikasi  ke write end file discriptor fd[1] emnggunakan dup2. Kemudian proses akan mengeksekusi ls terlebih dahulu.
```
else if(pid==0){

close(fd[0]);

dup2(fd[1],STDOUT_FILENO);

close(fd[1]);

char *argv[]={"ls",NULL};

execv("/bin/ls",argv);

}

```
Kemudian si parrent akan menunggu childnya selesai terlebih dahulu. Ketika childnya selesai maka, parrent akan membaca file discriptor fd dari read end pipes fd[0] kemudian menduplikasi menggunakan perintah dup2 ke stdin. Kemudian exec wc -l. Maka parrent akan mengeksekusi wc -l dengan input dari ls.
```
else{

while(wait(&status)>0);

close(fd[1]);

dup2(fd[0],STDIN_FILENO);

close(fd[0]);

char *argv1[]={"wc","-l",NULL};

execv("/usr/bin/wc",argv1);

}

return 0;

}
```

## Penjelasan Penyelesaian Soal nomor 3
Pada soal nomor 3 kita diminta untuk membuat program yang dapat mengkategorikan file-file dalam sebuah direktori. File-file tersebut akan dikategorikan dan dimasukkan ke dalam direktori baru berdasarkan ekstensi dari file tersebut. Program ini dapat menerima 3 jenis argumen / berjalan dalam 3 mode. 

Mode 1 yaitu -f, mode -f akan mengkategorikan file-file yang diminta oleh user. Mode 2 yaitu -d, mode -d akan mengkategorikan file-file dalam direktori yang diminta oleh user. Terakhir yaitu mode \*. Mode \* akan mengkategorikan file-file dalam direktori dimana file program ini berada.

```
int main (int arg,char *argmode[]){
    sprintf(truepath,"%s",getcwd(cwd2,sizeof(cwd2)));
    if(argmode[1][0]=='*'){
        categorize1();
    }
    else if(argmode[1][1]=='d'){
        char path[1024];
        strcpy(path,argmode[2]);
        printf("%s\n",path);
        categorize2(path);
    }
    else {
        int l;
        for(l=2;argmode[l]!=NULL;l++){
            int err;
            err = pthread_create(&(tid[i]),NULL,&solver3,argmode[l]);
            if(err!=0){
                printf("error\n");
            }
            i++;
        }
    }
    int iter;
    for(iter=0;iter<=i;iter++){
        pthread_join(tid[iter],NULL);
    }
    return(0);
}
```
Pada fungsi main, jika argumen * maka akan memanggil fungsi categorize1. Jika argumen d maka akan memanggil fungsi categorize2 dan terakhir jika argumen f maka akan langsung membuat thread-thread tiap argumen yang diterima. 

```
void categorize1(){
    d = opendir(".");
        if(d){
        while((dir = readdir(d))!=NULL){
            if(dir->d_type != DT_DIR){ 
                int err;
                err = pthread_create(&(tid[i]),NULL,&solver1,dir->d_name);
                if(err!=0){
                    printf("error\n");
                }
                i++;
            }
        }
    closedir(d);
        }
}

void categorize2(char* path){ 
    chdir(path);
    d = opendir(path);
    
        if(d){
        while((dir = readdir(d))!=NULL){
            if(dir->d_type != DT_DIR){ 
                int err;
                err = pthread_create(&(tid[i]),NULL,&solver2,dir->d_name);
                if(err!=0){
                    printf("error\n");
                }
                i++;
            }
        }
        closedir(d);
        }
}
```
Pada fungsi categorize 1 dan 2, akan dibuka direktori sesuai yang diminta. Lalu akan dibaca semua file di dalamnya. Jika file yang dibaca bukan merupakan sebuah direktori maka nama file tersebut akan di parsing sebagai sebuah argumen ke dalam sebuah thread. Hal ini akan terjadi terhadap semua file yang dibaca dalam direktori yang diminta. 

```
void* solver1 (void* args){
   //printf("masuk thread\n");
    char* dname ;
    dname =  (char *) args;
 //  printf("%s\n",dname);
    int flag=0;
    int lenght = strlen(dname);
                char nama[lenght+1],ekstensi[10],nmdir[1000];
                strcpy(nama,dname);
                for(z=0;lenght>0;lenght--){
                    if(nama[lenght]=='.'){
                        flag=1;
                        break;
                    } 
                }
                if(flag==0){
                    strcpy(ekstensi,"Uknown");
                }
                else strcpy(ekstensi,nama+lenght+1);

                int k;
                for(k=0;k<strlen(ekstensi);k++){
                    ekstensi[k]=tolower(ekstensi[k]);
                }

                
                char dest[1024];
                char cwd[1024];
                
                sprintf(dest,"%s/%s/%s",getcwd(cwd,sizeof(cwd)),ekstensi,nama);
                sprintf(nmdir,"%s/%s",truepath,ekstensi);
                mkdir(nmdir,0777);
                if(rename(nama,dest)!=0){
                    char ekstensi2[1024];
                    char dest2[1024];
                    sprintf(ekstensi2,"\\%s",ekstensi);
                    sprintf(dest2,"%s/%s/%s",getcwd(cwd,sizeof(cwd)),ekstensi2,nama);
                    mkdir(ekstensi2,0777);
                    rename(nama,dest2);
                }
                
                
                pthread_exit(NULL);

}

void* solver3 (void* args){
  //  printf("masuk thread 3\n");
    char* dname ;
    dname =  (char *) args;
    int flag=0;
    int lenght = strlen(dname);
                char nama[lenght+1],nama2[lenght+1],ekstensi[10],nmdir[1000];
                strcpy(nama,dname);
                for(z=0;lenght>0;lenght--){
                    if(nama[lenght]=='.'){
                        flag=1;
                        break;
                    }  
                }
                if(flag==0){
                    strcpy(ekstensi,"Uknown");
                }
                else strcpy(ekstensi,nama+lenght+1);

                lenght = strlen(dname);
                for(z=0;lenght>0;lenght--){
                    if(nama[lenght]=='/'){
                        break;
                    }  
                }
                strcpy(nama2,nama+lenght+1);

                int k;
                for(k=0;k<strlen(ekstensi);k++){
                    ekstensi[k]=tolower(ekstensi[k]);
                }
                char cwd[1024];
                sprintf(nmdir,"%s/%s",truepath,ekstensi);
                mkdir(nmdir,0777);

                char dest[1024];
                sprintf(dest,"%s/%s",nmdir,nama2);

                
                if(rename(nama,dest)!=0){
                    char ekstensi2[1024];
                    char dest2[1024];
                    sprintf(ekstensi2,"\\%s",ekstensi);
                    sprintf(dest2,"%s/%s/%s",getcwd(cwd,sizeof(cwd)),ekstensi2,nama2);
                    printf("dest2 = %s\n",dest2);
                    mkdir(ekstensi2,0777);
                    rename(nama,dest2);
                }
                pthread_exit(NULL);

}

void* solver2 (void* args){
   // printf("masuk thread\n");
    char* dname;
    dname = (char *) args;
    int flag=0;
    int lenght = strlen(dname);
                char nama[lenght+1],ekstensi[10],nmdir[1000];
                strcpy(nama,dname);
                for(z=0;lenght>0;lenght--){
                    if(nama[lenght]=='.'){
                        flag=1;
                        break;
                    }  
                }
                if(flag==0){
                    strcpy(ekstensi,"Uknown");
                }
                else strcpy(ekstensi,nama+lenght+1);
                int k;
                for(k=0;k<strlen(ekstensi);k++){
                    ekstensi[k]=tolower(ekstensi[k]);
                }
                char cwd[1024];
                sprintf(nmdir,"%s/%s",truepath,ekstensi);
                mkdir(nmdir,0777);
                char dest[1024];
                sprintf(dest,"%s/%s/%s",truepath,ekstensi,nama);
               // printf("%s\n",dest);
                rename(nama,dest);
                pthread_exit(NULL);

}
```
Terakhir, pada fungsi solver yang dijalankan oleh thread. Secara umum, pertama-tama  nama file yang diterima dari argumen akan dibaca dari belakang. Nama akan dibaca dari belakang sampai ditemukan karakter '.' yang menandakan string setelah karakter '.' adalah ekstensi dari file tersebut. Setelah ekstensi dari file didapat, akan dilakukan iterasi untuk merubah ekstensi menjadi huruf kecil semua sehingga program berjalan tidak case sensitive. Selanjutnya akan digunakan fungsi mkdir untukk membuat direktori dengan nama ekstensi yang di dapat tadi. Dari situ kita bisa melakukan rename untuk 'memindahkan' file tersebut ke dalam direktori yang dibuat. 
