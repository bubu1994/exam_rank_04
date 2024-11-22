
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

/*This is my main for testing picoshell.
ultimate test: ./a.out cat "|" cat "|" ls

The main of the exam is much shorter lol
*/

int picoshell(char **cmds[]);

int get_s(char **av)
{
    int i = 0;
    int res = 0;

    while (av[i])
    {
        if (!strcmp(av[i], "|"))
            res++;
        i++;
    }
    return (res + 1);
}

int get_n(char **av_suivi)
{
    int i = 0;

    while (av_suivi[i])
    {
        if (!strcmp(av_suivi[i], "|"))
            break ;
        i++;
    }
    return (i);
}

char **new_cmd(char **av, int *index, int ac)
{
    char **new = malloc(sizeof(char *) * (get_n(av + *index) + 1));
    int k = 0;

    while (*index < ac)
    {
        if (!strcmp(av[*index], "|"))
            break ;
        new[k] = strdup(av[*index]);
        k++;
        (*index)++;
    }
    (*index)++;
    new[k] = NULL;
    return (new);
}

char ***parse_argv(char **av, int ac)
{
    char ***res = malloc(sizeof(char **) * (get_s(av) + 1));
    int index = 1;
    int k_res = 0;


    while (index < ac)
    {
        res[k_res] = new_cmd(av, &index, ac);
        k_res++;
    }
    res[k_res] = NULL;
    return (res);
}

void free_commands(char ***cmds)
{
    if (!cmds)
        return;

    for (int i = 0; cmds[i]; i++) {
        for (int j = 0; cmds[i][j]; j++) {
            free(cmds[i][j]);
        }
        free(cmds[i]);
    }
    free(cmds);
}

void display_cmds(char ***cmds)
{
    if (!cmds)  
        return ;
    for (int i = 0; cmds[i]; i++)
    {
        printf("cmds[%d]: ", i);
        for (int j = 0; cmds[i][j]; j++) {
            printf("%s ", cmds[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return (0);

    char ***cmds = parse_argv(argv, argc);

    int res = picoshell(cmds);
	if (res)
		printf("pico ret: %d\n", res);

    free_commands(cmds);
    return (0);
}