/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassir <ayassir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:51:23 by ayassir           #+#    #+#             */
/*   Updated: 2022/06/27 15:00:30 by ayassir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_data_init(t_data *data, int ac, char **av)
{
	data->number_of_philos = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->t_nb_eat = -1;
	data->curtime = ft_get_time();
	data->eats = 0;
	if (ac == 6)
		data->t_nb_eat = ft_atoi(av[5]);
}

int	ft_init_sem(char **av, int ac)
{
	t_info		*info;
	t_data		*data;
	int			i;

	i = -1;
	info = ft_lstnew(1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	ft_data_init(data, ac, av);
	ft_init_struct(data, info);
	ft_lstlast(info);
	while (++i < data->number_of_philos)
	{
		info->data = data;
		info = info->next;
	}
	data->info = info;
	if (!ft_process_semaphore_init(data, info))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if (!ft_check_arguments(av, ac))
			return (write(2, "Error\n", 6), -1);
		if (!ft_init_sem(av, ac))
			return (write(2, "Error\n", 6), -1);
	}
	else
		write(2, "Error\n", 6);
	return (0x0);
}
