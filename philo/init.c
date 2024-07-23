/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:21:47 by sizitout          #+#    #+#             */
/*   Updated: 2024/07/22 23:03:37 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_stock *stock, t_philo *philo)
{
	int	i;

	i = 0;
	stock->start_time = ft_milliseconde();
	stock->dead_philo = 0;
	while (i < stock->number_philo)
	{
		philo[i].id = i + 1;
		pthread_mutex_init(&philo[i].fork_l, NULL);
		if (i == stock->number_philo - 1)
			philo[i].fork_r = &philo[0].fork_l;
		else
			philo[i].fork_r = &philo[i + 1].fork_l;
		philo[i].stocks = stock;
		philo[i].meals = 0;
		philo[i].last_meal = ft_milliseconde();
		i++;
	}
	return (0);
}

int	create_philo(t_stock *stock, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < stock->number_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
		{
			ft_exit(stock, stock->philos, i);
			return (printf("Failed to create thread\n"), 1);
		}
		i++;
	}
	if (monitoring(philo) != ft_dead(philo))
		return (0);
	return (0);
}

int	wait_thread(t_stock *stock)
{
	int	i;

	i = 0;
	while (i < stock->number_philo)
	{
		if (pthread_join(stock->philos[i].thread, NULL) != 0)
		{
			ft_exit(stock, stock->philos, i);
			return (printf("Failed to join to thread\n"), 1);
		}
		i++;
	}
	return (0);
}

int	ft_init_mutex(t_stock *stock)
{
	if (pthread_mutex_init(&stock->printf_mutex, NULL) != 0)
		return ((printf("Failed to initialize mutex\n")), 1);
	if (pthread_mutex_init(&stock->dead_lock, NULL) != 0)
		return ((printf("Failed to initialize mutex\n")), 1);
	if (pthread_mutex_init(&stock->meal_lock, NULL) != 0)
		return ((printf("Failed to initialize mutex\n")), 1);
	if (pthread_mutex_init(&stock->everyone_eat_lock, NULL) != 0)
		return ((printf("Failed to initialize mutex\n")), 1);
	if (pthread_mutex_init(&stock->last_meal_lock, NULL) != 0)
		return ((printf("Failed to initialize mutex\n")), 1);
	return (0);
}
