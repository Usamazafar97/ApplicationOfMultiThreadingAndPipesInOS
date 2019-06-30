
//grep -invw color colorfile.txt >color.txt 

//---------------------------------Code For Part B --------------------------------------

#include <unistd.h>
#include<errno.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include<fcntl.h>
#include<sys/types.h>

int main()
{
	int fds[2];
	pipe(fds);
	pid_t pid = fork();
	
	if ( pid == 0 ) //Child Process
	{
		dup2(fds[1],STDOUT_FILENO);
		close(fds[0]);
		char* argv[] = {(char*)"grep",(char*)"-o",(char*)"color",(char*)"colorfile.txt",NULL};
		if(execvp(argv[0],argv) < 0)		
			exit(0); //Run grep command otherwise safely exit;		
	}
	else
	{
		int myFD;
		dup2(fds[0],STDIN_FILENO);
		close(fds[1]);
		fopen( "newfile.txt" , "w" );
		char* argv1[] = {(char*)"wc",(char*)"-w",NULL};
		myFD = open("newfile.txt",O_WRONLY /*For Writing only */);
		dup2(myFD,STDOUT_FILENO);
		if(execvp(argv1[0],argv1) < 0)		
			exit(0); //Run WC command otherwise safely exit;
	}
	
	int ReturnStatus;
	pid_t waitPid = waitpid(pid,&ReturnStatus ,0);
	
	return waitPid == pid && WIFEXITED(status) ? WEXITSTATUS(status) : -1;
}