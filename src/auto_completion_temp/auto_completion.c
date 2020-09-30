

#include "auto_completion.h"


char        auto_is_dir(char *path, char *filename)
{
    t_stat  sb;
    char    full_path[PATH_MAX];

	if (!path || !filename)
		return (FALSE);
    ft_strcpy(full_path, path);
    ft_strcat(full_path, "/");
    ft_strcat(full_path, filename);
    lstat(full_path, &sb);
    if (sb.st_mode & S_IFDIR)
        return (TRUE);
    else
        return (FALSE);
}
char        is_completed(t_auto *auto_com)
{
    //return (ft_strnequ(auto_com->word, (char*)auto_com->list->content, \
    //        ft_strlen(auto_com->word)));
    //return (ft_strnequ(auto_com->word, (char*)auto_com->list->content, \
    //        auto_com->list->content_size));
	return (auto_com->status & AUTO_STAT_COMPLETED);
}


int         is_separator(char c)
{
    return (c == '&' || c == ';' || c == '|');
}
int         auto_is_command(t_l *l)
{
    int     curr;

    curr = l->x + (l->y * l->co) - l->pmpt - 1;
    while (curr != 0 && !ft_iswhite(l->line[curr]) && \
        !is_separator(l->line[curr]))
        --curr;    
    if (curr == 0)
        return (1);
    else if (ft_iswhite(l->line[curr]))
    {
        while (curr != 0 && ft_iswhite(l->line[curr]))
            --curr;
        if (curr == 0)
            return (1);
        else
            return (0);
    }
    return (0);
}

char        is_ready_to_print(t_auto *auto_com)
{
    if (auto_com->list && auto_com->status & AUTO_STAT_LIST)
        return (TRUE);
    else
        return (FALSE);
}

int			auto_complete(t_l *l)
{
	if (l->auto_com->status & AUTO_STAT_NEW_POS)
		reset_auto(l);
	if (auto_is_command(l))
		l->auto_com->status |= AUTO_STAT_COMMAND;
	
	if (auto_is_root(l))
		NULL;
		NULL;
		NULL;
		NULL;
		NULL;
		NULL;
		NULL;
		NULL;
		NULL;
}