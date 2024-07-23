/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:13:56 by sizitout          #+#    #+#             */
/*   Updated: 2024/07/22 23:51:51 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit(t_stock *stock, t_philo *philo, int i)
{
	int	k;

	k = 0;
	while (k < i)
	{
		pthread_mutex_destroy(&philo[k].fork_l);
		k++;
	}
	pthread_mutex_destroy(&stock->dead_lock);
	pthread_mutex_destroy(&stock->meal_lock);
	pthread_mutex_destroy(&stock->printf_mutex);
	pthread_mutex_destroy(&stock->everyone_eat_lock);
	pthread_mutex_destroy(&stock->last_meal_lock);
	free(philo);
}

int	norminette_dead(t_philo *philo)
{
	if (ft_dead(philo) == 1)
		return (0);
	return (0);
}
