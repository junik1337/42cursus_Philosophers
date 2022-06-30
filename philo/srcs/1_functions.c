/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_functions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassir <ayassir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:29:17 by ayassir           #+#    #+#             */
/*   Updated: 2022/06/27 19:16:11 by ayassir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	is_list_alpha(char *str)
{
	int		i;
	int		space;

	space = 0;
	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		else if (str[i] == ' ')
			space++;
		i++;
	}
	if (space == (int) ft_strlen(str))
		return (0);
	return (1);
}

int	ft_check_arguments(char **av, int ac)
{
	int		i;
	int		size;

	i = 1;
	size = ac - 1;
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0
		|| ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0)
		return (0);
	while (size-- > 0)
		if (is_list_alpha(av[i++]) == 0)
			return (0);
	if (ac == 6)
	{
		if (ft_atoi(av[5]) <= 0)
			return (0);
		is_list_alpha(av[5]);
	}
	return (1);
}

void	ft_lstadd_back(t_info **lst, t_info *new)
{
	t_info		*temp;

	if (!(*lst))
	{
		ft_lstadd_front(lst, new);
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	ft_init_struct(t_data *data, t_info *info)
{
	int			i;

	i = 0;
	while (++i < data->number_of_philos)
		ft_lstadd_back(&info, ft_lstnew(i + 1));
	ft_lstlast(info);
}

int	ft_detach_philo(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->number_of_philos)
	{
		if (pthread_detach(data->info->thread))
			return (0);
		data->info = data->info->next;
	}
	return (1);
}
