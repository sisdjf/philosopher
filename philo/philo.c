/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:21:39 by sizitout          #+#    #+#             */
/*   Updated: 2024/07/22 23:32:56 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_one(void *args)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)args;
	pthread_mutex_lock(&philo->fork_l);
	pthread_mutex_lock(&philo->stocks->printf_mutex);
	printf("%zu %d has taken a fork\n", (ft_milliseconde()
			- philo->stocks->start_time), philo[0].id);
	pthread_mutex_unlock(&philo->stocks->printf_mutex);
	ft_usleep(philo->stocks->time_die);
	pthread_mutex_unlock(&philo->fork_l);
	pthread_mutex_lock(&philo->stocks->printf_mutex);
	printf("%zu %d died\n", (ft_milliseconde() - philo->stocks->start_time),
		philo[0].id);
	pthread_mutex_unlock(&philo->stocks->printf_mutex);
	return (NULL);
}

void	one_philo(t_philo *philo)
{
	if (pthread_create(&philo[0].thread, NULL, &routine_one, &philo[0]) != 0)
	{
		ft_exit(philo->stocks, philo, 1);
		printf("Failed to create thread\n");
		return ;
	}
	if (pthread_join(philo[0].thread, NULL) != 0)
	{
		ft_exit(philo->stocks, philo, 1);
		printf("Failed to create join\n");
		return ;
	}
}

int	main(int argc, char **argv)
{
	static t_stock	stock = {0};
	t_philo			*philo;

	if (stock_args(&stock, argc, argv) != 0)
		return (printf("Error parsing\n"), 1);
	ft_init_mutex(&stock);
	stock.start_time = ft_milliseconde();
	philo = malloc(sizeof(t_philo) * stock.number_philo);
	stock.philos = philo;
	if (!philo)
		return (1);
	init_philo(&stock, philo);
	if (stock.number_philo == 1)
	{
		one_philo(philo);
		free(stock.philos);
		return (0);
	}
	create_philo(&stock, philo);
	wait_thread(&stock);
	ft_exit(&stock, philo, stock.number_philo);
	return (0);
}
