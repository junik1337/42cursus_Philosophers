/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_functions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassir <ayassir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:30:53 by ayassir           #+#    #+#             */
/*   Updated: 2022/06/24 20:07:29 by ayassir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

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

time_t	ft_get_time(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	sleep_time(int time)
{
	long	current_time;

	current_time = ft_get_time();
	while ((ft_get_time() - current_time) < time)
		usleep(100);
}

void	ft_print_message(t_info *info, char *msg, sem_t *message)
{
	sem_wait(message);
	info->curtime = ft_get_time() - info->data->curtime;
	printf("%ld\t%d\t%s", info->curtime, info->p_number, msg);
	sem_post(message);
}

void	ft_kill_process(t_data *data, pid_t *list_pid)
{
	int		i;
	int		status;

	i = 0;
	waitpid(-1, &status, 0);
	while (i < data->number_of_philos)
	{
		if (WEXITSTATUS(status) == 2)
			kill(list_pid[i], SIGINT);
		i++;
	}
	i = 0;
	while (i < data->number_of_philos)
	{
		if (WEXITSTATUS(status) == 3)
			waitpid(-1, &status, 0);
		i++;
	}
}
