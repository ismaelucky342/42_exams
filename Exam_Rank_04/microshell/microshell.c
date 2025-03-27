/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 22:14:54 by ismherna          #+#    #+#             */
/*   Updated: 2025/03/27 22:14:56 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

void	ft_putstr_fd2(char *str, char *arg)
{
    while (*str)
        write(2, str++, 1);
    if (arg)
        while (*arg)
            write(2, arg++, 1);
    write(2, "\n", 1);
}

void	ft_execute(char *argv[], int i, int tmp_fd, char *env[])
{
    argv[i] = NULL;
    dup2(tmp_fd, STDIN_FILENO);
    close(tmp_fd);
    execve(argv[0], argv, env);
    ft_putstr_fd2("error: cannot execute ", argv[0]);
    exit(1);
}

void	handle_cd(char *argv[])
{
    if (!argv[1] || argv[2])
        ft_putstr_fd2("error: cd: bad arguments", NULL);
    else if (chdir(argv[1]) != 0)
        ft_putstr_fd2("error: cd: cannot change directory to ", argv[1]);
}

void	handle_pipe(char *argv[], int i, int *tmp_fd, char *env[])
{
    int	fd[2];

    pipe(fd);
    if (fork() == 0)
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        ft_execute(argv, i, *tmp_fd, env);
    }
    else
    {
        close(fd[1]);
        close(*tmp_fd);
        *tmp_fd = fd[0];
    }
}

void	handle_command(char *argv[], int i, int *tmp_fd, char *env[])
{
    if (fork() == 0)
        ft_execute(argv, i, *tmp_fd, env);
    else
    {
        close(*tmp_fd);
        while (waitpid(-1, NULL, WUNTRACED) != -1)
            ;
        *tmp_fd = dup(STDIN_FILENO);
    }
}

int	main(int argc, char *argv[], char *env[])
{
    int	i, tmp_fd;

    (void)argc;
    tmp_fd = dup(STDIN_FILENO);
    while (*argv && *(argv + 1))
    {
        argv++;
        i = 0;
        while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
            i++;
        if (strcmp(argv[0], "cd") == 0)
            handle_cd(argv);
        else if (i != 0 && (!argv[i] || strcmp(argv[i], ";") == 0))
            handle_command(argv, i, &tmp_fd, env);
        else if (i != 0 && strcmp(argv[i], "|") == 0)
            handle_pipe(argv, i, &tmp_fd, env);
        argv += i;
    }
    close(tmp_fd);
    return (0);
}