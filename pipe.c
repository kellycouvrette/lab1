#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	// TODO: it's all yours
	
	//make some kind of error if no args? 
	int pipefds[2];

	//iterate through the arguments
	for (int i =0; i < argc -1; i++){
		//create pipe for all (maybe not last)
		if (i < argc -2){
			if(pipe(pipefds)==-1){
				exit;
			}
		}
		//check for pipe error to exit
		pid_t child_pid = fork();

		if (child_pid == -1){
			exit;
		}//remember to check child error

		if (child_pid ==0){
			if (i>0){
				//in child process, not first arg
				//redirect input from pipe. dup time!!
				dup2(pipefds[0], STDIN_FILENO);
				close(pipefds[1]); //close write end
			}
			if(i< argc -2){
				//output to the pipe
				dup2(pipefds[1], STDOUT_FILENO);
			}
			//are there any other fds open i need to close??
			//execute time!!
			execlp(argv[i+1], argv[i+1], NULL);
			exit;
		}else{
			//in the parent
			if(i>0){
				close(pipefds[0]);
			}
			if(i < argc -2){
				close(pipefds[1]);
			}
			//something about waiting? check this
			int status;
			waitpid(child_pid, &status, 0);
		}
	}

	return 0;
}
