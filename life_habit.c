/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_habit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:49:11 by marechaloli       #+#    #+#             */
/*   Updated: 2024/09/04 02:46:48 by marechaloli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	death_checker(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->parsed->nb_philo && philo->parsed->dead == false)
	{
		pthread_mutex_lock(&philo->parsed->acces);
		if ((get_time() - philo[i].last_meal) >= philo->parsed->time_d)
		{
			action_tracker("died", philo, i + 1);
			philo->parsed->dead = true;
		}
		i++;
		pthread_mutex_unlock(&philo->parsed->acces);
		usleep(100);
	}
}

void	status(t_pars *parsed)
{
	t_philo	*philo;
	int		i;

	philo = parsed->philo;
	while (parsed->philos_full == false)
	{
		death_checker(philo);
		if (parsed->dead == true)
			break ;
		i = 0;
		pthread_mutex_lock(&parsed->acces);
		while (parsed->nb_meal != -1 && i < parsed->nb_philo
			&& philo[i].meal_counter >= parsed->nb_meal)
			i++;
		if (i == parsed->nb_philo)
			parsed->philos_full = true;
		pthread_mutex_unlock(&parsed->acces);
	}
}

void	end_of_dinner(t_pars *parsed)
{
	int		i;
	t_philo	*philo;

	philo = parsed->philo;
	i = 0;
	if (parsed->nb_philo == 1)
		pthread_mutex_unlock(&parsed->fork[philo[0].left_fork_id]);
	while (i <= parsed->nb_philo)
	{
		pthread_join(philo[i].philo_thread, NULL);
		pthread_mutex_destroy(&parsed->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&parsed->acces);
	pthread_mutex_destroy(&parsed->info);
}

void	eating_process(t_philo *philo)
{
	t_pars	*parsed;

	parsed = philo->parsed;
	pthread_mutex_lock(&parsed->fork[philo->left_fork_id]);
	pthread_mutex_lock(&parsed->acces);
	action_tracker("has taken a fork", philo, philo->philo_id);
	pthread_mutex_unlock(&parsed->acces);
	pthread_mutex_lock(&parsed->fork[philo->right_fork_id]);
	pthread_mutex_lock(&parsed->acces);
	action_tracker("has taken a fork", philo, philo->philo_id);
	action_tracker("is eating", philo, philo->philo_id);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&parsed->acces);
	waiting_time(parsed->time_e, parsed);
	pthread_mutex_lock(&parsed->acces);
	philo->meal_counter++;
	pthread_mutex_unlock(&parsed->acces);
	pthread_mutex_unlock(&parsed->fork[philo->left_fork_id]);
	pthread_mutex_unlock(&parsed->fork[philo->right_fork_id]);
}
