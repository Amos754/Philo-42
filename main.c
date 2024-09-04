/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:18:57 by marechaloli       #+#    #+#             */
/*   Updated: 2024/09/04 11:10:18 by marechaloli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_args(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
		{
			if (args[i][j] == '-')
				msg_exit("Negative number are forbidden.", 0);
			if (!((args[i][j] <= '9' && args[i][j] >= '0') || (args[i][j] == '+'
				&& (args[i][j + 1] >= '0' && args[i][j + 1] <= '9'))
				|| (args[i][j] >= 9 && args[i][j] <= 13) || args[i][j] == 32))
				msg_exit("Non numerical argument detected.", 0);
		}
	}
}

void	waiting_time(long time, t_pars *parsed)
{
	long long	actual_time;

	actual_time = get_time();
	pthread_mutex_lock(&parsed->acces);
	while ((!((get_time() - actual_time) >= time)) && parsed->dead == false)
	{
		pthread_mutex_unlock(&parsed->acces);
		usleep(100);
		pthread_mutex_lock(&parsed->acces);
	}
	pthread_mutex_unlock(&parsed->acces);
}

void	*life_cycle(void *arg)
{
	t_philo	*philo;
	t_pars	*parsed;

	philo = (t_philo *)arg;
	parsed = philo->parsed;
	if (philo->philo_id % 2 == 0)
		usleep(1500);
	pthread_mutex_lock(&parsed->acces);
	while (parsed->dead == false && parsed->philos_full == false)
	{
		pthread_mutex_unlock(&parsed->acces);
		eating_process(philo);
		pthread_mutex_lock(&parsed->acces);
		action_tracker("is sleeping", philo, philo->philo_id);
		pthread_mutex_unlock(&parsed->acces);
		waiting_time(parsed->time_s, parsed);
		action_tracker("is thinking", philo, philo->philo_id);
		pthread_mutex_lock(&parsed->acces);
	}
	pthread_mutex_unlock(&parsed->acces);
	return (NULL);
}

void	start_simulation(t_pars *parsed)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = parsed->philo;
	parsed->ref_time = get_time();
	while (i < parsed->nb_philo)
	{
		if (pthread_create(&philo[i].philo_thread, NULL, life_cycle, &philo[i]))
			msg_exit("Error while creating a philo.", 0);
		pthread_mutex_lock(&parsed->acces);
		philo[i].last_meal = get_time();
		pthread_mutex_unlock(&parsed->acces);
		i++;
	}
	status(parsed);
	end_of_dinner(parsed);
}

int	main(int ac, char **av)
{
	t_pars	parsed;

	if (ac < 5 || ac > 6)
		msg_exit("You should give 4 or 5 arguments.\n", 1);
	check_args(av);
	init(&parsed, av);
	start_simulation(&parsed);
	return (0);
}
