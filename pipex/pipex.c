#include "pipex.h"


int main(int argc, char *const argv[], char *const envp[])
{
	// el 0 es reading el 1 es writing, para usar uno cerrar el otro
	char *ma[] = {"grep", "1", NULL};
	char *ma2[] = {"wc", "-l", NULL};
	int	fd[2];
	pid_t	childpid;
	int a = pipe(fd);
	int f = open("pruebas.txt", O_RDONLY);

	dup2(f, STDIN_FILENO);
	close(f);

	childpid = fork();
	if(childpid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execve("/bin/grep", ma, envp);
	}
	else
	{
		char c;

		close(fd[1]);

		/*
		while (read(fd[0], &c, 1) > 0)
			write(1, &c, 1);
		*/

		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(childpid, NULL, 0);
		execve("/bin/wc", ma2, envp);

	}

	return (0);
}