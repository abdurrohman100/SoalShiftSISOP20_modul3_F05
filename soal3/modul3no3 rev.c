#include<string.h>
#include<pthread.h>
#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<ctype.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid[2000];
DIR *d;
int i=0,z;
struct dirent *dir;
char truepath[1024],cwd2[1024];




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