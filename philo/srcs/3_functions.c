/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_functions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassir <ayassir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:27:42 by ayassir           #+#    #+#             */
/*   Updated: 2022/06/27 19:30:27 by ayassir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_print_message(t_info *info, char *msg, pthread_mutex_t message)
{
	pthread_mutex_lock(&message);
	info->curtime = ft_get_time() - info->data->curtime;
	printf("%ld\t%d\t%s", info->curtime, info->p_number, msg);
	pthread_mutex_unlock(&message);
}

void	free_space(t_data *data, t_info *info)
{
	int		i;

	i = 0;
	while (i < data->number_of_philos)
	{
		free (info);
		info = info->next;
		i++;
	}
	free (data);
}

void	check_death(t_data *data, t_info *info)
{
	while (info)
	{
		if ((ft_get_time() - info->t_last_eat) > data->t_die
			&& info->t_last_eat > 0)
		{
			ft_routine_stop(data, info);
			pthread_mutex_lock(&data->message);
			printf("%ld\t%d\t%s",
				(ft_get_time() - info->data->curtime), info->p_number, "died\n");
			return ;
		}
		else if (info->nb_eats >= data->t_nb_eat && data->t_nb_eat > 0)
		{
			data->eats += 1;
			info->nb_eats = INT32_MIN;
			if (data->eats == info->data->number_of_philos)
			{
				ft_routine_stop(data, info);
				return ;
			}
		}
		info = info->next;
	}
}

void	*routine(void *ptr)
{
	t_info				*info;

	info = (t_info *) ptr;
	while (!info->loop)
	{
		pthread_mutex_lock(&info->fork);
		ft_print_message(info, "has taken a fork\n", info->data->message);
		pthread_mutex_lock(&info->next->fork);
		ft_print_message(info, "has taken a fork\n", info->data->message);
		info->t_last_eat = ft_get_time();
		ft_print_message(info, "is eating\n", info->data->message);
		info->nb_eats++;
		time_wasted(info->data->t_eat);
		pthread_mutex_unlock(&info->next->fork);
		pthread_mutex_unlock(&info->fork);
		ft_print_message(info, "is sleeping\n", info->data->message);
		time_wasted(info->data->t_sleep);
		ft_print_message(info, "is thinking\n", info->data->message);
	}
	return (NULL);
}

int	ft_pthread_mutex_init(t_data *data)
{
	int				i;

	if (!ft_mutex_init(data))
		return (0);
	i = -1;
	while (++i < data->number_of_philos)
	{
		if (pthread_create(&data->info->thread, NULL, &routine,
				data->info))
			return (0);
		data->info = data->info->next;
		usleep(60);
	}
	if (data->number_of_philos == 1)
	{
		data->info->t_last_eat = ft_get_time();
		time_wasted(data->t_die);
	}
	check_death(data, data->info);
	free_space(data, data->info);
	return (1);
}
