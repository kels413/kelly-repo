#include "shell.h"
void startMyshell(void);
/**
 * startMyshell - Start the custom shell
 *
 * Description: This function starts the custom shell. It reads user input,
 * processes commands, and executes them until the user exits the shell.
 */
void	startMyshell(void)
{
	char	*prompt = NULL, **args, *envp[] = {NULL};
	size_t	size_prompt;
	ssize_t	numRead;
	int		stat;
	int		my_stat;

	size_prompt = 0;
	stat = 0;
	while (1)
	{
		numRead = readUserInput(&prompt, &size_prompt);
		if (numRead == -1)
			getPromptFail(prompt);
		args = funcTokenize(prompt, " \n\t");
		if (args[0])
		{
			if (!_strcmp(args[0], "exit"))
			{
				if (args[1])
				{
					my_stat = _atoi(args[1]);
					exitCustom(my_stat, args, prompt, &stat);
				}
				else
				{
					free(prompt);
					freeArgs(args);
					exit(stat);
				}
			}
			else if (!_strcmp(args[0], "env"))
			{
				printEnviron();
				stat = 0;
			}
			else
				executeCommands(args, envp, &stat);
		}
		freeArgs(args);
		free(prompt);
		prompt = NULL;
	}
}
