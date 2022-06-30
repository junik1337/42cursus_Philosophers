/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_functions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassir <ayassir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 19:49:19 by ayassir           #+#    #+#             */
/*   Updated: 2022/06/26 14:23:00 by ayassir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	closeandfree(t_data *data)
{
	sem_close(data->fork);
	sem_close(data->message);
	sem_unlink("/sem_fork");
	sem_unlink("/sem_message");
	free_space(data, data->info);
	free (data->process);
	exit(1);
}

int	ft_detach_philos(t_data *data)
{
	int			i;

	i = -1;
	while (++i < data->number_of_philos)
	{
		if (pthread_detach(data->info->thread))
			return (0);
		data->info = data->info->next;
	}
	return (1);
}

void	ft_routine_stop(t_data *data, t_info *info)
{
	int			i;

	i = -1;
	while (++i < data->number_of_philos)
	{
		info->loop = 1;
		info = info->next;
	}
}
