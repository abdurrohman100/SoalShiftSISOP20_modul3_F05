#include<string.h>
#include<pthread.h>
#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<ctype.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid[1024];
DIR *d;
int i=0,z;
struct dirent *dir;


void* solver1 (void* args){
    printf("masuk thread\n");
    char* dname ;
    dname =  (char *) args;
    printf("%s\n",dname);
    int flag=0;
    int lenght = strlen(dname);
                char nama[lenght+1],ekstensi[10];
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
                mkdir(ekstensi,0777);
                char dest[1024];
                sprintf(dest,"/home/feraldy/Modul3/%s/%s",ekstensi,nama);
                rename(nama,dest);
                pthread_exit(NULL);

}

void* solver3 (void* args){
    
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
                sprintf(nmdir,"/home/feraldy/Modul3/%s",ekstensi);
                mkdir(nmdir,0777);
                char dest[1024];
                sprintf(dest,"/home/feraldy/Modul3/%s/%s",ekstensi,nama2);
                rename(nama,dest);
                pthread_exit(NULL);

}

void* solver2 (void* args){
   
    char* dname ;
    dname =  (char *) args;
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
                sprintf(nmdir,"/home/feraldy/Modul3/%s",ekstensi);
                mkdir(nmdir,0777);
                char dest[1024];
                sprintf(dest,"/home/feraldy/Modul3/%s/%s",ekstensi,nama);
                rename(nama,dest);
                pthread_exit(NULL);

}


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
    d = opendir(path);
    chdir(path);
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

int main (int arg,char *argmode[]){
    
    if(argmode[1][0]=='*'){
        categorize1();
    }
    else if(argmode[1][1]=='d'){
        char path[1024];
        strcpy(path,argmode[2]);
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
    for(i;i>=0;i--){
        pthread_join(tid[i],NULL);
    }
    return(0);
}