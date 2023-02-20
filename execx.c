#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(int argc, char* argv[]){

	int timeOfExec=0;
	if(!strcmp(argv[1],"-t")){ //sadece -t kontrol ediliyor çünkü bu komuta geldiyse execx yazdıgı kesindir.
		timeOfExec = atoi(argv[2]);
		if(timeOfExec == 0){
			printf("Yanlış komut girdiniz.. \n");
			return 0;
		}
		if(!strcmp(argv[3],"writef") && !strcmp(argv[4],"-f") && (argv[5] != NULL)){ // eğer writef yazdıysa, yanında -f varsa ve file name null değilse kesin bir file name girilmiştir , writef çağrıldı demektir.
		int pid = fork();
		
		if (pid == -1) {
			printf("\n fork basarisiz oldu.");
			return 1;
		} else if (pid == 0){
			execve("writef", argv,NULL);
			exit(0); 
		} else {
			wait(NULL);
			return 0;
		}
	}else if(!strcmp(argv[3],"ls")){
				for(int i=0; i<timeOfExec; i++){
					system("ls");
					printf("\n");
				}
			}else if(!strcmp(argv[3],"cat")){
			
				for(int i=0; i<timeOfExec; i++){
					printf("Cat: ");
					int k=4;
					while(argv[k] != NULL){
						printf("%s ",argv[k]);
						k++;
					}
					printf("\n");
				}
			}else{
				printf("Yanlış komut girdiniz..\n");
			}
	}else {
		printf("Yanlış komut girdiniz..\n");
	}
	return 0;
		
}
