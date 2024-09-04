/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:48:30 by marechaloli       #+#    #+#             */
/*   Updated: 2024/09/04 02:46:56 by marechaloli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_pars *parsed)
{
	int	i;

	if (pthread_mutex_init(&(parsed->acces), NULL))
		msg_exit("Error while initialising mutex.", 0);
	if (pthread_mutex_init(&(parsed->info), NULL))
		msg_exit("Error while initialising mutex.", 0);
	parsed->dead = false;
	parsed->philos_full = false;
	i = parsed->nb_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(parsed->fork[i]), NULL))
			msg_exit("Error while initialising mutex.", 0);
		parsed->philo[i].philo_id = i + 1;
		parsed->philo[i].right_fork_id = (i + 1) % parsed->nb_philo;
		parsed->philo[i].left_fork_id = i;
		parsed->philo[i].meal_counter = 0;
		parsed->philo[i].last_meal = 0;
		parsed->philo[i].parsed = parsed;
	}
}

void	init(t_pars *pars, char **av)
{
	pars->nb_philo = ft_atoi(av[1]);
	if (pars->nb_philo > 250)
		msg_exit("Too many philos.", 0);
	pars->time_d = ft_atoi(av[2]);
	pars->time_e = ft_atoi(av[3]);
	pars->time_s = ft_atoi(av[4]);
	if (av[5])
		pars->nb_meal = ft_atoi(av[5]);
	else
		pars->nb_meal = -1;
	pars->ref_time = get_time();
	init_philo(pars);
}
