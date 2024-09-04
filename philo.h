/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:47:51 by marechaloli       #+#    #+#             */
/*   Updated: 2024/09/04 02:22:26 by marechaloli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <stdbool.h>

typedef struct s_philo
{
	pthread_t		philo_thread;
	int				philo_id;
	int				left_fork_id;
	int				right_fork_id;
	long long		last_meal;
	int				meal_counter;
	struct s_pars	*parsed;
}	t_philo;

typedef struct s_pars
{
	pthread_mutex_t	acces;
	pthread_mutex_t	fork[250];
	pthread_mutex_t	info;
	int				nb_philo;
	long			time_d;
	long			time_e;
	long			time_s;
	int				nb_meal;
	long long		ref_time;
	bool			dead;
	bool			philos_full;
	t_philo			philo[250];
}	t_pars;

void		msg_exit(char *error, int option);
int			ft_strlen(char *str);
int			ft_atoi(const char *str);
long long	get_time(void);
void		init(t_pars *pars, char **av);
void		init_philo(t_pars *parsed);
void		action_tracker(char *msg, t_philo *philo, int id);
void		waiting_time(long time, t_pars *parsed);
void		eating_process(t_philo *philo);
void		status(t_pars *parsed);
void		end_of_dinner(t_pars *parsed);

#endif