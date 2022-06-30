/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassir <ayassir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 11:44:26 by ayassir           #+#    #+#             */
/*   Updated: 2022/06/26 11:19:15 by ayassir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct s_data {
	pthread_mutex_t			message;
	struct s_info			*info;
	time_t					curtime;
	int						number_of_philos;
	int						t_nb_eat;
	int						t_sleep;
	int						t_die;
	int						t_eat;
	int						eats;
	int						id;
}				t_data;

typedef struct s_info{
	pthread_mutex_t			fork;
	pthread_t				thread;
	time_t					t_last_eat;
	time_t					curtime;
	t_data					*data;
	int						p_number;
	int						nb_eats;
	int						loop;
	struct s_info			*next;
}				t_info;

t_info	*ft_lstnew(int content);
size_t	ft_strlen(const char *str);
time_t	ft_get_time(void);
void	simple_error(void);
void	ft_lstadd_back(t_info **lst, t_info *new);
void	ft_lstadd_front(t_info **lst, t_info *new);
void	ft_lstlast(t_info *lst);
void	ft_init_struct(t_data *data, t_info *info);
void	time_wasted(time_t time);
void	free_space(t_data *data, t_info *info);
int		ft_dead_thread(t_data *data, t_info *info, int type);
int		ft_detach_philos(t_data *data);
int		ft_check_arguments(char **av, int ac);
int		ft_atoi(const char *str);
int		ft_init_info(t_data *data, char **av, int i);
int		ft_pthread_mutex_init(t_data *data);
int		ft_mutex_init(t_data *data);
void	ft_routine_stop(t_data *data, t_info *info);
#endif