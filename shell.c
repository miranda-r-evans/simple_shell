#include "shell.h"

int main(void)
{
	int status = 0;
	int bytes_read;
	int i;
	size_t buf_size = 1;
	char *buf = NULL;
	char *tmp;
	char **args = NULL;
	char **args_ptr;
	extern char **environ;
	char *path_str;
	char **path_var;
	char **path_ptr;
	pid_t pid;

	/*signal(SIGINT,SIG_IGN);*/

	buf = malloc(1);
	if (buf == NULL)
		exit(EXIT_FAILURE);

	while (1)
	{
		path_str = _strdup(get_array_element(environ, "PATH"));
		path_var = make_array(path_str, ':');
		path_ptr = path_var;

		if (isatty(STDIN_FILENO) == 1)
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		bytes_read = getline(&buf, &buf_size, stdin);

		if (bytes_read == -1)
			exit(EXIT_FAILURE);

		buf[bytes_read - 1] = '\0';

		if (buf[0] != '/')
		{
			tmp = malloc(buf_size);
			if (tmp == NULL)
				exit(EXIT_FAILURE);
			_strconcat(&tmp, "/", buf);
			free(buf);
			buf = tmp;
		}

		args = make_array(buf, ' ');

		args[0] = malloc(PATH_MAX);
		if (args[0] == NULL)
			exit(EXIT_FAILURE);

		_strconcat(&args[0], buf, "");

		i = built_ins(args, &status);
		if (i == DO_EXECVE)
		{
			while (*path_ptr != NULL && access(args[0], X_OK) != 0)
			{
				_strconcat(&args[0], *path_ptr, buf);
				path_ptr++;
			}
			pid = fork();

			if (pid == -1)
			{
				exit(EXIT_FAILURE);
			}
			if (pid == 0)
			{
				execve(args[0], args, environ);
				exit(EXIT_FAILURE);
			}
			wait(&status);
		}
		args_ptr = args;
		while (*args_ptr != NULL)
		{
			if (*args_ptr < buf || *args_ptr > buf + (buf_size - 1))
				free(*args_ptr);

			args_ptr++;
		}
		free(args);
		free(path_str);
		free(path_var);

		if (i == EXIT_SHELL_CODE || i == EXIT_SHELL)
			break;
	}
	free(buf);

	if (i == EXIT_SHELL_CODE)
		return (status);

	return (0);
}
