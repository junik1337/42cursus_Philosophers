/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_functions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassir <ayassir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:11:23 by ayassir           #+#    #+#             */
/*   Updated: 2022/06/26 11:53:26 by ayassir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	ft_atoi(const char *str)
{
	int			min;
	int			j;
	int			res;

	min = 1;
	j = 0;
	res = 0;
	while ((str[j] == '\t' || str [j] == '\n')
		|| (str[j] == '\v' || str [j] == '\f')
		|| (str[j] == '\r' || str [j] == ' '))
		j++;
	if (str[j] == '-' || str[j] == '+')
	{
		if (str[j] == '-')
			min = -min;
		j++;
	}
	while (str[j] >= '0' && str[j] <= '9')
	{
		res = (res * 10) + (str[j] - '0');
		j++;
	}
	return (res * min);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

t_info	*ft_lstnew(int content)
{
	t_info	*lst;

	lst = (t_info *)malloc(sizeof(t_info));
	if (!lst)
		return (NULL);
	lst->p_number = content;
	lst->t_last_eat = 0;
	lst->nb_eats = 0;
	lst->loop = 0;
	lst->next = NULL;
	return (lst);
}

void	ft_lstadd_front(t_info **lst, t_info *new)
{
	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	*lst = new;
}

void	ft_lstlast(t_info *lst)
{
	t_info	*temp;

	if (!lst)
		return ;
	temp = lst;
	while (temp->next)
		temp = temp->next;
	temp->next = lst;
}
