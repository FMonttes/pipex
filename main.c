/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felipe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 20:44:52 by felipe            #+#    #+#             */
/*   Updated: 2023/12/24 15:26:31 by felipe           ###   ########.fr       */
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
		printf("PID do processo pai: %d\n", getpid());
		
		//char *cmd = "/user/bin/git";
		char *args[] = {"git", "commit", "-m", "teste",  NULL};

		execve("/usr/bin/git" , args, envp);

		printf ("processo pai termina aqui\n");	
	}
}
