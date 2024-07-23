/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:45:47 by sizitout          #+#    #+#             */
/*   Updated: 2024/07/22 22:51:40 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_dead(t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&philo->stocks->dead_lock);
	i = philo->stocks->dead_philo;
	pthread_mutex_unlock(&philo->stocks->dead_lock);
	return (i);
}

size_t	ft_milliseconde(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		printf("Error gettimeofday\n");
		return (1);
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_usleep(size_t milli)
{
	size_t	time;

	time = ft_milliseconde();
	while ((ft_milliseconde() - time) < milli)
		usleep(1000);
	return (0);
}

int	need_to_eat(t_stock *stock, t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&stock->meal_lock);
	i = philo->meals;
	pthread_mutex_unlock(&stock->meal_lock);
	if (i == stock->number_meals)
		return (1);
	return (0);
}

// int main()
// {
//     struct timeval	time;
//     gettimeofday(&time, NULL);
//     printf("seconde : %ld \n milli : %ld", time.tv_sec, time.tv_usec);
// }