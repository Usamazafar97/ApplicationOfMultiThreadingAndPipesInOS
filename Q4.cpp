int main(int argc , char * argv[])
{
	int pipefd[2];
	pid_t cpid;
	char buf;
	
	pipe(pipefd);
	cpid = fork();
	if(cpid == 0)
	{
		close(pipefd[1]);
		
		while(read(pipefd[0],&buf,1)>0)
			write(STDOUT_FILENO,&buf,1);
		
		write(STDOUT_FILENO,"\n",1);
		close(pipefd[0]);
	}
	else
	{
		close(pipefd[0]);
		write(pipefd[1],argv[1],strlen(argv[1]));
		close(pipefd[1]);
		wait((int*)NULL);
	}
}