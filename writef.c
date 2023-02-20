#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<time.h>


int main(int argc, char* argv[]){ // argv filename olacak ve yoksa oluştuurlacak varsa içine yazılacak. argv[1]

FILE *myFile;

int timeOfExec =0;

int pid,ppid;
pid = getpid();
ppid = getppid();

char timeNow[100];
time_t t = time(NULL);
struct tm * p = localtime(&t);
strftime(timeNow,100,"%A, %B %d %Y",p);


if(!strcmp(argv[0],"execx")){ // execx ile çağrıldıysa kaç kere yazılmak istendiğine ulaşmak için tanımlandı.
	myFile = fopen(argv[5],"a"); 
	timeOfExec = atoi(argv[2]);
	for(int i=0; i<timeOfExec; i++){
		fprintf(myFile,"time: %s pid: %d ppid: %d \n",timeNow,pid,ppid);
	}
	}else if(!strcmp(argv[0],"writef") && !strcmp(argv[1],"-f") && (argv[2] != NULL)){
		myFile = fopen(argv[2],"a");
		fprintf(myFile,"time: %s pid: %d ppid: %d \n",timeNow,pid,ppid);
	}else{
	printf("Yanlış komut girdiniz..");
	}
fclose(myFile);
return 0;

}
