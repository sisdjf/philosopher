/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:40:17 by sizitout          #+#    #+#             */
/*   Updated: 2024/07/22 23:24:30 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Le moniteur:
// while (1)
// {
// Il y a un mort ?
// Ils ont tous manges ?
// }

// int	blabla(t_philo *philo)
// {

// }
int	ft_check_dead(t_philo *philo)
{
	int				i;
	unsigned long	time_to_die;

	i = 0;
	time_to_die = (unsigned long)philo->stocks->time_die;
	while (i < philo->stocks->number_philo)
	{
		pthread_mutex_lock(&philo->stocks->last_meal_lock);
		if (time_to_die <= (ft_milliseconde() - philo[i].last_meal))
		{
			pthread_mutex_lock(&philo->stocks->dead_lock);
			if (philo->stocks->dead_philo == 1)
				return (pthread_mutex_unlock
					(&philo->stocks->last_meal_lock), 1);
			pthread_mutex_unlock(&philo->stocks->dead_lock);
			ft_dead(philo);
			printf_mutex("is died", WHITE, ft_milliseconde(), philo);
			pthread_mutex_unlock(&philo->stocks->last_meal_lock);
			return (1);
		}
		pthread_mutex_unlock(&philo->stocks->last_meal_lock);
		i++;
	}
	return (0);
}

int	monitoring(t_philo *philo)
{
	while (1)
	{
		if (ft_check_dead(philo) != 0)
		{
			pthread_mutex_lock(&philo->stocks->printf_mutex);
			pthread_mutex_lock(&philo->stocks->dead_lock);
			philo->stocks->dead_philo = 1;
			pthread_mutex_unlock(&philo->stocks->dead_lock);
			pthread_mutex_unlock(&philo->stocks->printf_mutex);
			return (0);
		}
		pthread_mutex_lock(&philo->stocks->everyone_eat_lock);
		if (philo->stocks->everyone_eat == philo->stocks->number_philo)
		{
			pthread_mutex_lock(&philo->stocks->dead_lock);
			philo->stocks->dead_philo = 1;
			pthread_mutex_unlock(&philo->stocks->dead_lock);
			pthread_mutex_unlock(&philo->stocks->everyone_eat_lock);
			return (0);
		}
		pthread_mutex_unlock(&philo->stocks->everyone_eat_lock);
	}
	return (0);
}

// usleep(10);
//Le usleep sert a afficher la routine dans valgrind pas obliger de mettre
//en bas de cette ligne
// pthread_mutex_unlock(&philo->stocks->everyone_eat_lock);