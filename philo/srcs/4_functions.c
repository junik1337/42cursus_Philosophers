/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_functions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassir <ayassir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:30:53 by ayassir           #+#    #+#             */
/*   Updated: 2022/06/26 11:48:42 by ayassir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

time_t	ft_get_time(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	time_wasted(time_t time)
{
	time_t	current_time;

	current_time = ft_get_time();
	while ((ft_get_time() - current_time) < time)
		usleep(100);
}

int	ft_mutex_init(t_data *data)
{
	int			i;

	i = -1;
	if (pthread_mutex_init(&data->message, NULL))
		return (0);
	while (++i < data->number_of_philos)
	{
		if (pthread_mutex_init(&data->info->fork, NULL))
			return (0);
		data->info->nb_eats = 0;
		data->info = data->info->next;
	}
	return (1);
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
	ft_detach_philos(data);
}
