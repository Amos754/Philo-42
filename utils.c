/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:18:47 by marechaloli       #+#    #+#             */
/*   Updated: 2024/09/04 02:04:03 by marechaloli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	msg_exit(char *error, int option)
{
	int	i;

	i = -1;
	write(1, "\033[1;31mERROR :\033[0m ", 20);
	while (error[++i])
		write(1, &error[i], 1);
	if (option == 1)
	{
		write(1, "Ex : \033[0;95m./philo\033[0m", 24);
		write(1, " [nb_philo][time_die][time_eat][time_sleep]<nb_meal>", 53);
	}
	write(1, "\n", 1);
	exit(EXIT_FAILURE);
}

int	ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long int	result;
	long int	tmp;

	result = 0;
	i = 0;
	tmp = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - '0');
		if (tmp > result && sign > 0)
			return (-1);
		else if (tmp > result && sign < 0)
			return (0);
		tmp = result;
	}
	return ((int)(result * sign));
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	action_tracker(char *msg, t_philo *philo, int id)
{
	pthread_mutex_lock(&philo->parsed->info);
	if (philo->parsed->dead == false)
		printf("%lld  %d  %s\n", get_time() - philo->parsed->ref_time,
			id, msg);
	pthread_mutex_unlock(&philo->parsed->info);
}
