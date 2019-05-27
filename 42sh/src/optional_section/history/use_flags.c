/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** use flag
*/

#include "mysh.h"

void disp_flags(shell_t *shell, char ***history, char **args, int nb_flag)
{
    if (nb_flag == 0)
        display_history(shell->history, shell);
    if (shell->hist_flag[10] == 1) {
        history_flag_maj_m(history, shell);
        return;
    }
    if (shell->hist_flag[4] == 1)
        shell->history_pointer = history_flag_c(*history);
    if (shell->hist_flag[2] == 1)
        history_flag_r(*history, shell);
    if (shell->hist_flag[7] == 1 && shell->hist_flag[2] != 1)
        history_flag_h(*history, shell);
    if (shell->hist_flag[3] == 1)
        fill_history_file(*history, shell->env_dup, shell);
}

void priorities_flags(shell_t *shell, char ***history, char **args, int nb_flag)
{
    if (args[1][0] >= '0' && args[1][0] <= '9')
        display_history(*history, shell);
    else
        disp_flags(shell, history, args, nb_flag);
}

int which_flag(shell_t *shell, char ***history, char **args)
{
    int nb_flag = 0;

    for (int i = 0; i < 13; i++)
        shell->hist_flag[i] > 0 ? nb_flag++ : 0;
    if (shell->hist_flag[12] == 0)
        disp_flags(shell, history, args, nb_flag);
    else
        priorities_flags(shell, history, args, nb_flag);
    return (0);
}
