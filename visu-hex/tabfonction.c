/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabfonction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoly <djoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 14:20:45 by djoly             #+#    #+#             */
/*   Updated: 2016/04/15 14:13:19 by djoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_hex.h"

static int	add_room2(t_lem_env *env, char *s, int i)
{
	char	*t;
	char	*tmp;

	if ((t = ft_strstr(env->str, ft_strjoin(ft_strsub(s, 0, i), "\n")))
		!= NULL)
	{
		if (t != env->str && *(--t) == '\n')
			return (ft_error(env, 1));
	}
	tmp = ft_strjoin(env->str, ft_strsub(s, 0, i));
	tmp = ft_strjoin(tmp, "\n");
	free(env->str);
	env->str = tmp;
	env->nbroom += 1;
	coord(s, i, env);
	return (1);
}

int			test_space(char *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ' ')
			j++;
		if (j > 2)
			return (1);
		i++;
	}
	return (0);
}

int			add_room(t_lem_env *env, char *s)
{
	int		i;

	if (test_space(s))
		exit(ft_putstr("DSL: room sans space pour visu_hex\n"));
	i = ft_strlen(s);
	while (--i >= 0 && env->tmp != 2)
	{
		if (s[i] == ' ')
			env->tmp += 1;
	}
	i++;
	if (env->nbroom == 0)
	{
		env->str = ft_strjoin(ft_strsub(s, 0, i), "\n");
		env->nbroom += 1;
		coord(s, i, env);
	}
	else
	{
		if (add_room2(env, s, i) == 0)
			return (0);
	}
	env->tmp = 0;
	return (1);
}

int			check_nblem(t_lem_env *env, char *s)
{
	if (is_nblem(s))
		env->nblem = ft_atoi(s);
	if (env->nblem <= 0)
		return (ft_error(env, 1));
	env->r.nbline += add_file(env, s);
	return (ft_add_state(env));
}

int			check_room(t_lem_env *env, char *s)
{
	if (is_link(s) && env->fonction[env->r.state + 1](env, s))
		return (ft_add_state(env));
	if (ft_strcmp("##start", s) == 0 && check_start(env, s))
		return (1);
	if (ft_strcmp("##end", s) == 0 && check_end(env, s))
		return (1);
	if (is_room(s) && add_room(env, s))
	{
		env->r.nbline += add_file(env, s);
		return (1);
	}
	return (ft_error(env, 1));
}
