
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>


char* readCommands()
{
	char *line = (char *)malloc(sizeof(char) * 1024); //  Buffer Allocation 
	char read;
	int position = 0 ;
	int bufferSize = 1024;
	if (!line){ // Fail
		printf("\n Buffer Could Not Allocated."); // yer ayrılamadı , allocate edilemedi. 
		exit(1); 
	}
	while(1){
		read=getchar();
		if (read == EOF || read == '\n'){   //okunan sona ulaştıysa veya okunan null pointe geldiiyse return olsun. 
			line[position] = '\0';
			return line;		// okunan tüm satır line değişkenine atandı. ve geri döndürüldü.
		}
		else{
			line[position] = read;
		}
		position ++;
		
		if (position >= bufferSize){		   // bize verilen bellek aşılırsa verilen alanı artırıyoruz. yeniden allocate yapıyoruz.
			bufferSize += 1024;
			line = realloc(line, sizeof(char) * bufferSize);
			if (!line){ // Fail
			printf("\nBuffer Could Not Allocated");
			exit(1); 
			}
		}
	}

}

int main(){
	system("clear"); 				// girişte cmd'yi temizlemek için koyuldu
	char commandString[1000], *Temp[100];
				
	while (1) {
		printf("myshell>>");
		
		char* hbRead; 				// have been read (okunan) 
		hbRead = readCommands();		// okuma fonksiyonu çağrıldı.
		if (strlen(hbRead) != 0) { 		//yazılanların boyutu 0 değilse. Yani bir komut girilmişse;
			strcpy(commandString, &hbRead);	//okunan stringi strye kopyaladık. 
		} else { 				//string boyutu 0dır ve hiçibir şey yazılmamış demektir.
			continue;	
		}
	
		int i;
		for (i = 0; i < 100; i++) {
			Temp[i] = strsep(&commandString, " "); 	//alınan stringi " " boşluklarına göre ayırır. Temp değişkenine atıyor.

			if (Temp[i] == NULL) 			// stringin sonuna ulaştığımızı null öperatöründen anlayıp çıkıyoruz.
				break;
			if (strlen(Temp[i]) == 0)
				i--;
		}
		whichCommand(Temp); 			// parçalara ayrılan yani parse edilen stringin hangi komut oldugunu anlamak için kullanılan method. 

	}
	return 0;
}

int whichCommand(char** seperated){
	
	int which =0;
	
	if(!strcmp(seperated[0],"exit")){
		which = 1;
	}else if(!strcmp(seperated[0],"cat")){
		which = 2;
	}else if(!strcmp(seperated[0],"clear")){
		which = 3;
	}else if(!strcmp(seperated[0],"ls")){
		which = 4;
	}else if(!strcmp(seperated[0],"bash")){
		which = 5;
	}else if(!strcmp(seperated[0],"execx")){
		which = 6;
	}else if(!strcmp(seperated[0],"writef")){
		which = 7;
	}
	
	switch (which) {
	case 1:
		exit(0);
	case 2:
		Cat(seperated); // ne yazdırmak istiyorsa bir sonraki parametrede saklandıgı için seperated[1] gönderildi.
		return 1;
	case 3:
		Clear();
		return 1;
	case 4: 
		system("ls");
		return 1;
	case 5:
		Bash(seperated);
		return 1;
	case 6:
		execx(seperated);
		return 1;
	case 7:
		writef(seperated);
		return 1;
	default:
		printf("Yanlis komut girdiniz.\n");
		break;
	
	}
}

void writef(char** parsed){

	int pid = fork();
	
	if (pid == -1) {
		printf("\n fork basarisiz oldu.");
		return;
	} else if (pid == 0){
		execve("writef", parsed,NULL);
		exit(0); 
	} else {
		wait(NULL);
		return;
	}

}

void execx(char** parsed){

	int pid = fork();
	
	if (pid == -1) {
		printf("\n fork basarisiz oldu.");
		return;
	} else if (pid == 0){
		execve("execx", parsed,NULL);
		exit(0); 
	} else {
		wait(NULL);
		return;
	}
	
}

void Bash(char** parsed){
	
	int pid = fork();  		//Child process oluşturuldu ileride beklemesi için

	if (pid == -1) {
		printf("\n fork basarisiz oldu.");
		return;
	} else if (pid == 0){
		execvp(parsed[0], parsed);
		exit(0); // exit yaparak normal bashe döndük ama oradan da exit dediğimiz anda bu arkada bekliyor olacak. 
	} else {
		// oluşturulan child için bekliyor olacak. 
		wait(NULL);
		return;
	}
}

void Clear(){
	system("clear");
}

void Cat(char** str){
	int i=1;
	printf("Cat: ");
	while(str[i] != '\0'){
	printf("%s ",str[i]);
	i++;
	}
	printf("\n");
}

