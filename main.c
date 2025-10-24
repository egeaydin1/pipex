# include "pipex.h"
char *path_finder(char **cmd, char **ev)
{
    char **paths;
    char *path;
    char *cmd_path;
    int i;

    i = 0;
    while (ev[i] && ft_strncmp(ev[i], "PATH=", 5) != 0)
        i++;
    if (!ev[i])
        return (NULL);
    paths = ft_split(ev[i] + 5, ':');
    i = 0;
    while (paths[i])
    {
        path = ft_strjoin(paths[i], "/");
        cmd_path = ft_strjoin(path, cmd[0]);
        free(path);
        if (access(cmd_path, X_OK) == 0)
        {
            while (paths[i])
                free(paths[i++]);
            free(paths);
            return (cmd_path);
        }
        free(cmd_path);
        i++;
    }
    while (i >= 0)
        free(paths[i--]);
    free(paths);
    return (NULL);
}
void child(char *infile,char **cmd1, char **ev, int *fd)
{
	int infile_fd;
	char *path;

	infile_fd = open(infile,O_RDONLY);
	if (infile_fd == -1)
	{
		perror(infile);
		exit(1);
	}
	path = path_finder(cmd1, ev);
	dup2(infile_fd,STDIN_FILENO);
	dup2(fd[1],STDOUT_FILENO);
	close(infile_fd);
	close(fd[0]);
	close(fd[1]);
	if (execve(path, cmd1, ev) == -1)
	{
		perror("execve");
		exit(1);
	}
}
void parent(char *outfile,char **cmd2, char **ev, int *fd)
{
	int outfile_fd;
    char *path;

	outfile_fd = open(outfile,O_RDWR | O_TRUNC | O_CREAT, 0664);
	if (outfile_fd == -1)
	{
		perror(outfile);
		exit(1);
	}
	path = path_finder(cmd2, ev);
	dup2(fd[0],STDIN_FILENO);
	dup2(outfile_fd,STDOUT_FILENO);
	close(outfile_fd);
	close(fd[0]);
	close(fd[1]);
	if (execve(path,cmd2, ev) == -1)
	{
		perror("execve");
		exit(1);
	}
}

void fork_and_exec(char **av, char **ev,int *fd)
{   
	char *outfile;
	char *infile;
	char **cmd1;
	char **cmd2;

    pid_t	pid;
	infile = av[1];
	cmd1 = ft_split(av[2],' ');
	cmd2 = ft_split(av[3],' ');
	outfile = av[4];
    if(pipe(fd) == -1)
        error_print("","");
	pid = fork();
	if (pid == -1)
        error_print("ana olmadi la fork","");
	else if (pid == 0)
		child(infile,cmd1,ev,fd);
	close(fd[1]);
	waitpid(pid,NULL,0);
	parent(outfile,cmd2,ev,fd);
}

int main(int ac,char **av,char **ev)
{
    // av1 = infile 
    // av2 = cmd1
    // av3 = cmd2
    // av4 = outfile 
    int fd[2];

    if (ac != 5)
        return(error_print("\033[31mPlease enter 4 argument\e[0m","Example:./pipex <file1> <cmd1> <cmd2> <file2>"));
    fork_and_exec(av,ev,fd);

	
    return (0);
}

