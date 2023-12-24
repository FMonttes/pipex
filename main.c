/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felipe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 20:44:52 by felipe            #+#    #+#             */
/*   Updated: 2023/12/24 15:49:57 by felipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int ac, char **av, char **envp)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		printf("PID do processo filho: %d\n", getpid());

	//	char *cmd = "/user/bin/git";
		char *args[] = {"git", "add", ".", NULL};

		execve("/usr/bin/git", args, envp);

		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
		printf("\nestou no processo pai\n");

		pid_t pid_commit = fork();
		if (pid_commit == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid_commit == 0)
		{
			printf("\nestou no processo filho do commit\n");

			char *args[] = {"git", "commit", "-m", "comitando apenas com um codigo com fork", NULL};
			execve("/usr/bin/git", args, envp);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
			printf("\n estou em outro processo pai\n");

			pid_t pid_push = fork();
			
			if (pid_push == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			else if (pid_push == 0)
			{
				printf("\n estou em outro processo filho\n");

				char *args[] = {"git", "push", NULL};
				execve("/usr/bin/git", args, envp);
				perror("execve");
				exit(EXIT_FAILURE);
			}
			else
			{
				wait(NULL);
				printf("TODOS OS PROCESSOS TERMINA AQUI");
			}
		}
	}	
}














