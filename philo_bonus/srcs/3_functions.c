/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_functions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassir <ayassir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:27:42 by ayassir           #+#    #+#             */
/*   Updated: 2022/06/27 19:14:47 by ayassir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	check_death(t_data *data, t_info *info)
{
	while (info)
	{
		if ((ft_get_time() - info->t_last_eat) > info->data->t_die
			&& info->t_last_eat > 0)
		{
			ft_routine_stop(data, info);
			sem_wait(data->message);
			printf("%ld\t%d\t%s",
				(ft_get_time() - data->curtime), info->p_number, "died\n");
			free_space(data, info);
			exit (2);
		}
		else if (info->nb_eats >= info->data->t_nb_eat && data->t_nb_eat > 0)
		{
			ft_routine_stop(data, info);
			data->eats += 1;
			info->nb_eats = INT32_MIN;
			free_space(data, info);
			exit (3);
		}
		info = info->next;
	}
}

static void	*routine(void *ptr)
{
	t_info				*info;
	int					i;

	info = (t_info *) ptr;
	i = 1;
	if ((info->p_number % 2) == 0)
		usleep (100);
	while (!info->loop)
	{
		sem_wait(info->data->fork);
		ft_print_message(info, "has taken a fork\n", info->data->message);
		sem_wait(info->data->fork);
		ft_print_message(info, "has taken a fork\n", info->data->message);
		ft_print_message(info, "is eating\n", info->data->message);
		info->t_last_eat = ft_get_time();
		sleep_time(info->data->t_eat);
		info->nb_eats++;
		sem_post(info->data->fork);
		sem_post(info->data->fork);
		ft_print_message(info, "is sleeping\n", info->data->message);
		sleep_time(info->data->t_sleep);
		ft_print_message(info, "is thinking\n", info->data->message);
	}
	return (NULL);
}

static int	ft_create_threads(t_data *data)
{
	data->info->t_last_eat = ft_get_time();
	if (pthread_create(&data->info->thread, NULL, &routine,
			data->info))
		return (0);
	if (pthread_detach(data->info->thread))
		return (0);
	check_death(data, data->info);
	exit(0);
}

static int	ft_init_fork(t_data *data)
{
	int			j;

	j = 0;
	data->process = malloc(data->number_of_philos * sizeof(pid_t));
	if (!data->process)
		return (0);
	while (j < data->number_of_philos)
	{
		data->process[j] = fork();
		if (data->process[j] == -1)
			closeandfree(data);
		else if (data->process[j] == 0)
			if (!ft_create_threads(data))
				return (0);
		j++;
		data->info = data->info->next;
	}
	ft_kill_process(data, data->process);
	free (data->process);
	free_space(data, data->info);
	return (1);
}

int	ft_process_semaphore_init(t_data *data, t_info *info)
{
	int			i;

	i = -1;
	(void) info;
	sem_unlink("/sem_fork");
	sem_unlink("/sem_message");
	data->fork = sem_open("/sem_fork", O_CREAT | O_EXCL, 0777,
			data->number_of_philos);
	if (data->fork == SEM_FAILED)
		return (0);
	data->message = sem_open("/sem_message", O_CREAT | O_EXCL, 0644, 1);
	if (data->message == SEM_FAILED)
		return (0);
	if (!ft_init_fork(data))
		return (0);
	sem_close(data->fork);
	sem_close(data->message);
	sem_unlink("/sem_fork");
	sem_unlink("/sem_message");
	return (1);
}
