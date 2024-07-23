/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 00:21:34 by sizitout          #+#    #+#             */
/*   Updated: 2024/07/22 23:32:04 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(char *str)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	if (res > INT_MIN && res < INT_MAX)
		return (sign * res);
	else
		return (0);
}

int	ft_number(char *argv)
{
	int	i;

	i = 0;
	if (ft_atoi(argv) == 0)
		return (0);
	while (argv[i])
	{
		if (argv[i] == '-')
			return (0);
		if (argv[i] < '0' || argv[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
// boucler sur argv, appeler ft_number pour faire les checks sur chaque argument
// si erreur - return (1)

int	blabla(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (1);
	while (i < argc)
	{
		if (!ft_number(argv[i]))
			return (1);
		i++;
	}
	return (0);
}

int	stock_args(t_stock *stock, int argc, char **argv)
{
	blabla(argc, argv);
	if (ft_atoi(argv[1]) > 200 || ft_atoi(argv[1]) <= 0)
		return (EXIT_FAILURE);
	stock->number_philo = ft_atoi(argv[1]);
	if (ft_atoi(argv[2]) <= 0 || ft_atoi(argv[2]) > INT_MAX)
		return (EXIT_FAILURE);
	stock->time_die = ft_atoi(argv[2]);
	if (ft_atoi(argv[3]) <= 0 || ft_atoi(argv[3]) > INT_MAX)
		return (EXIT_FAILURE);
	stock->time_eat = ft_atoi(argv[3]);
	if (ft_atoi(argv[4]) <= 0 || ft_atoi(argv[4]) > INT_MAX)
		return (EXIT_FAILURE);
	stock->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		stock->number_meals = ft_atoi(argv[5]);
	else
		stock->number_meals = -1;
	return (0);
}
