#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <math.h>
extern char **getln();

//function that calculates 16 to the power of num passed
int power (int num){
	int total = 1;
	for (int i = 0; i<num-1;i++){
		total = total *16;
	}
	return total;
}

int main() {
	int i;
	char **args; 
	
	while(1) {
		int total = 0;
		int fileArgs = 0;
		char temp[50];
		int opened = 0;
		int numOfArgs = 0;
		int status = 0;
		int posn = 0;
		pid_t pidT;
		printf("Shell$ ");
		args = getln();
		//gets number of args incase its needed
		for(i = 0; args[i] !=NULL;i++){
			numOfArgs = numOfArgs + 1;
		}
		//checks if a command is entered
		if (args[0] != NULL){
			if (strcmp(args[0],"exit")==0){
				exit(0);
			}
			//loops to check for &,>, or <
			for (i = 0; args[i] !=NULL;i++){
				if (strcmp(args[i],"&") == 0){
					printf("background process\n");
				}
				else if(strcmp(args[i],"<") == 0){
					printf("read in\n");
				}
				else if (strcmp(args[i],">") == 0 && args[i+1] != NULL){
					opened = 1;
					fileArgs = i;
					freopen(args[i+1], "a+",stdout);
					break;
				}

			}
			//if sending output to a file, remove the > and name of file from the arguments
			if (opened == 1){
				args[fileArgs] = NULL;
				args[fileArgs+1] = NULL;
			}

			if (strcmp(args[0],"add") == 0){
				pidT = fork();
				int num = 0;
				int hex = 0;
				if (pidT <0){
					perror("Fork has Failed....");
				}
				else if(pidT == 0){
					printf("Output:");
					for (i = 1; args[i] !=NULL;i++){
						//if a decimal number
						if (atoi(args[i]) !=0){
							num = atoi(args[i]);
							total = total + num;
						}
						else{
							strcpy(temp,args[i]);
							int totalOG = total;
							//if hexidecimal
							if (temp[0] =='0' && temp[1] == 'x'){
								for (int j = strlen(temp)-1; j>1;j--){
									if (temp[j] == '0'){
									}
									else if (temp[j] == '1'){
										hex = 1 * power(j-1);
										total = totalOG + hex;
									}
									else if (temp[j] == '2'){
										hex = 2 * power(j-1);
										total = totalOG + hex;										
									}
									else if (temp[j] == '3'){
										hex = 3 * power(j-1);
										total = totalOG + hex;										
									}
									else if (temp[j] == '4'){
										hex = 4 * power(j-1);
										total = totalOG + hex;										
									}
									else if (temp[j] == '5'){
										hex = 5 * power(j-1);
										total = totalOG + hex;										
									}
									else if (temp[j] == '6'){
										hex = 6 * power(j-1);
										total = totalOG + hex;										
									}
									else if (temp[j] == '7'){
										hex = 7 * power(j-1);
										total = totalOG + hex;										
									}
									else if (temp[j] == '8'){
										hex = 8 * power(j-1);
										total = totalOG + hex;										
									}
									else if (temp[j] == '9'){
										hex = 9 * power(j-1);
										total = totalOG + hex;										
									}
									else if (temp[j] == 'a' ||temp[j] == 'A' ){
										hex = 10 * power(j-1);
										total = totalOG + hex;										
									}
									else if (temp[j] == 'b' ||temp[j] == 'B' ){
										hex = 11 * power(j-1);
										total = totalOG + hex;										
									}
									else if (temp[j] == 'c' ||temp[j] == 'C' ){
										hex = 12 * power(j-1);
										total = totalOG + hex;										
									}
									else if (temp[j] == 'd' ||temp[j] == 'D' ){
										hex = 13 * power(j-1);
										total = totalOG + hex;										
									}
									else if (temp[j] == 'e' ||temp[j] == 'E' ){
										hex = 14 * power(j-1);
										total = totalOG + hex;										
									}
									else if (temp[j] == 'f' ||temp[j] == 'F' ){
										hex = 15 * power(j-1);
										total = totalOG + hex;										
									}
									//if not reset total value
									else{
										total = totalOG;
									}
								}
							}
						}
					}
					//loop to print output
					for (i = 1; args[i] != NULL; i++){
						printf("%s ",args[i]);
						if (args[i+1] != NULL){
							printf("+ ");
						}				
					}
					printf("= %d\n", total);
					exit(0);
				}
				wait(&status);
			}

			//multiplying command, assumes that there will be at least 1 argument to work.
			else if (strcmp(args[0],"muls") == 0 && args[1] !=NULL){
				pidT = fork();
				int numMulti = 0;
				total = 1;
				//if (strcmp(args[i],'')
				if (pidT <0){
					perror("Fork has Failed....");
				}
				else if(pidT == 0){
					printf("multiplying:");
					for (i = 1; args[i] !=NULL;i++){
						numMulti = atoi(args[i]);
						total = total * numMulti;
					}
					for (i = 1; args[i] != NULL; i++){
						printf("%s ",args[i]);
						if (args[i+1] != NULL){
							printf("* ");
						}				
					}
					printf("total is: %d\n", total);
					exit(0);	
				}
				wait(&status);
			}
			else if (strcmp(args[0],"args") == 0 && args[1] != NULL){
				printf("Arguments: ");
				for(i = 1; args[i] != NULL; i++) {
					//strcpy(temp,args[i]);
					printf("%s ", args[i]);
					//printf("temp: %d", temp[i]);
					if (strcmp(args[i],"\"") == 0){
						posn = 0;
						for (int j = i+1; args[j] !=NULL;j++){
							printf("%s ", args[j]);
							if (strcmp(args[j],"\"")==0){
								i = j;
								posn = 1;
								break;
							}
							else{
							}
						}
						total = total+posn;
					}
					else{
						//printf("%d",i);
						total = total +1;
					}	
				}
				printf("argc = %d\n", total);
			}
			else{
				//run execvp for commands 
				pid_t pid = fork();
				if (pid <0){
					perror("Fork has Failed....");
				}
				else if(pid == 0){
					execvp(*args,args);
					exit(0);
				}
				wait(&status);
				
			}
			//close the file output and restore back to normal output
			if(opened == 1){
				freopen("/dev/tty", "w",stdout);
				opened = 0;
			}

		}

	}
	return 1;
}
