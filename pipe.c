#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
int main(int argc, char *argv[])
{
	// TODO: it's all yours
	if (argc <2){	
		errno = EINVAL;
		exit(errno);
	}
	
	//make some kind of error if no args? 
	int pipefds[2];
	int prev_read_fd = -1;//
	//iterate through the arguments
	for (int i =0; i < argc -1; i++){
		
		//int pipefds[2];
		
		//create pipe for all (maybe not last)
		if (i < argc -2){ //from 2 to 1
			if(pipe(pipefds)==-1){
				exit(EXIT_FAILURE);
			}
		}
		
		//check for pipe error to exit
		pid_t child_pid = fork();

		if (child_pid == -1){
			exit(EXIT_FAILURE);
		}//remember to check child error

		if (child_pid ==0){
			if (i>0){
				//!!!!close(pipefds[1]);
				//in child process, not first arg
				//redirect input from pipe. dup time!!
				//dup2(pipefds[0], STDIN_FILENO);
				dup2(prev_read_fd, STDIN_FILENO);
				close(prev_read_fd);
				//close(pipefds[1]); //close write end
			}
			if(i< argc -2){
				//output to the pipe
				dup2(pipefds[1], STDOUT_FILENO);
				close(pipefds[0]);//
				close(pipefds[1]);
			}
			//are there any other fds open i need to close??
			//execute time!!
			//printf("argv is %s\n", argv[i+1]);

			if(execlp(argv[i + 1], argv[i+1], NULL) == -1){
				exit(EXIT_FAILURE);
			}
			exit(EXIT_FAILURE);
		}else{
			//in the parent
			// if(i>0){
			// 	close(pipefds[0]);
			// }
			if(prev_read_fd != -1){
				close(prev_read_fd);
			}
			if(i < argc -2){
				prev_read_fd = pipefds[0];
				close(pipefds[1]);
			}
			//something about waiting? check this
			int status;
			if(waitpid(child_pid, &status, 0) != -1){
				if(WIFEXITED(status)){
					if (WEXITSTATUS(status) !=0){
						exit(WEXITSTATUS(status));
					}
				} else{
					exit(EXIT_FAILURE);
				}
			}else{
				exit(EXIT_FAILURE);
			}
		}
	}

	return 0;
}
