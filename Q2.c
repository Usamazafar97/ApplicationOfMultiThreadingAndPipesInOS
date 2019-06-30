
#include <stdio.h>
//#include <string>
#include <stdlib.h>
#include <sys/wait.h>
#include <pthread.h>
#include <unistd.h>
//#include <iostream>
//using namespace std;

int main()
{
	printf("ProcessID : %d and  Parent ProcessID : % d \n",getpid(),getppid());
	
	int fd[2];
	int fd1[2];
	
	pipe(fd);
	pipe(fd1);
		
	int returnEnd = fork();
	if( returnEnd == 0)
	{
		printf("ProcessID : %d and  Parent ProcessID : % d \n",getpid(),getppid());
		int returnEndChild1 = fork();
		if(returnEndChild1 == 0)
		{
			printf("ProcessID : %d and  Parent ProcessID : % d \n",getpid(),getppid());
			close(fd1[0]);
			close(fd1[1]);
			close(fd[0]);
			
			dup2(fd[1],STDOUT_FILENO);
			//close(fd[1]);
			
			char* array1[] = {(char*)"ps",NULL};
			execvp("ps",array1);
		}
		int returnEndChild2 = fork()	;
		if(returnEndChild2 == 0)
		{
			printf("ProcessID : %d and  Parent ProcessID : % d \n",getpid(),getppid());
			close(fd1[0]);
			//close(fd1[1]);
			
			dup2(fd1[1],STDOUT_FILENO);		
			
			close(fd[1]);
			
			dup2(fd[0],STDIN_FILENO);
			//close(fd[1]);
			
			char* array3[] = {(char*)"sort",NULL};
			execvp("sort",array3);
						
		}
			close(fd[0]);
			close(fd[1]);
			close(fd1[1]);
			
			dup2(fd1[0],STDIN_FILENO);
			
			char* array2[] = {(char*)"less",NULL};
			execvp("less",array2);
			
		
		 wait(NULL);
		 wait(NULL);
		
		exit(0);
	}
	
	close(fd[0]);
	close(fd[1]);
	close(fd1[0]);
	close(fd1[1]);
	
	wait(NULL);
		
		exit(0);
	
}
