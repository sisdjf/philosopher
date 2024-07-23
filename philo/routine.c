/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:57:57 by sizitout          #+#    #+#             */
/*   Updated: 2024/07/22 23:54:05 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_philo *philo)
{
	norminette_dead(philo);
	if (philo->id % 2 == 0 || philo->stocks->number_philo % 2 != 0)
	{
		pthread_mutex_lock(philo->fork_r);
		printf_mutex("has taken a fork", YELLOW, ft_milliseconde(), philo);
		pthread_mutex_lock(&philo->fork_l);
		printf_mutex("has taken a fork", YELLOW, ft_milliseconde(), philo);
	}
	else
	{
		pthread_mutex_lock(&philo->fork_l);
		printf_mutex("has taken a fork", YELLOW, ft_milliseconde(), philo);
		pthread_mutex_lock(philo->fork_r);
		printf_mutex("has taken a fork", YELLOW, ft_milliseconde(), philo);
	}
	pthread_mutex_lock(&philo->stocks->last_meal_lock);
	philo->last_meal = ft_milliseconde();
	pthread_mutex_unlock(&philo->stocks->last_meal_lock);
	pthread_mutex_lock(&philo->stocks->meal_lock);
	philo->meals++;
	pthread_mutex_unlock(&philo->stocks->meal_lock);
	printf_mutex("is eating", MAGENTA, ft_milliseconde(), philo);
	ft_usleep(philo->stocks->time_eat);
	mutex_unlock(philo);
	return (1);
}

int	mutex_unlock(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
	}
	else
	{
		pthread_mutex_unlock(philo->fork_r);
		pthread_mutex_unlock(&philo->fork_l);
	}
	return (0);
}

int	sleeping(t_philo *philo)
{
	if (ft_dead(philo) == 1)
		return (0);
	pthread_mutex_lock(&philo->stocks->printf_mutex);
	printf("%s%ld %d is sleeping%s\n", GREEN, (ft_milliseconde()
			- philo->stocks->start_time), philo->id, RESET);
	pthread_mutex_unlock(&philo->stocks->printf_mutex);
	ft_usleep(philo->stocks->time_sleep);
	pthread_mutex_lock(&philo->stocks->printf_mutex);
	if (ft_dead(philo) == 1)
		return (pthread_mutex_unlock(&philo->stocks->printf_mutex), 0);
	printf("%s%ld %d is thinking%s\n", RED, (ft_milliseconde()
			- philo->stocks->start_time), philo->id, RESET);
	pthread_mutex_unlock(&philo->stocks->printf_mutex);
	return (1);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2 == 0)
		usleep(500);
	while (ft_dead(philo) == 0)
	{
		eating(philo);
		if (need_to_eat(philo->stocks, philo) == 1)
		{
			pthread_mutex_lock(&philo->stocks->everyone_eat_lock);
			philo->stocks->everyone_eat++;
			pthread_mutex_unlock(&philo->stocks->everyone_eat_lock);
			break ;
		}
		sleeping(philo);
	}
	return (NULL);
}

int	printf_mutex(char *message, char *color, long time, t_philo *philo)
{
	pthread_mutex_lock(&philo->stocks->printf_mutex);
	if (ft_dead(philo) == 1)
		return (pthread_mutex_unlock(&philo->stocks->printf_mutex),
			EXIT_FAILURE);
	printf("%s%ld %d %s%s\n", color, time - philo->stocks->start_time,
		philo->id, message, RESET);
	pthread_mutex_unlock(&philo->stocks->printf_mutex);
	return (EXIT_SUCCESS);
}
