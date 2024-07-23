/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:21:44 by sizitout          #+#    #+#             */
/*   Updated: 2024/07/23 00:03:35 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

// DATARACE   (mutex mes variables)  -   DEADLOCKS

typedef struct s_stock	t_stock;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	pthread_mutex_t		*fork_r;
	pthread_mutex_t		fork_l;
	unsigned long		last_meal;
	int					meals;
	t_stock				*stocks;
}						t_philo;

typedef struct s_stock
{
	int					number_philo;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					number_meals;
	int					dead_philo;
	size_t				start_time;
	int					everyone_eat;
	pthread_mutex_t		printf_mutex;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		everyone_eat_lock;
	pthread_mutex_t		last_meal_lock;
	t_philo				*philos;

}						t_stock;

//parsing
long					ft_atoi(char *str);
int						ft_number(char *argv);
int						stock_args(t_stock *stock, int argc, char **argv);
int						blabla(int argc, char **argv);
//init
int						init_philo(t_stock *stock, t_philo *philo);
int						create_philo(t_stock *stock, t_philo *philo);
int						wait_thread(t_stock *stock);
int						ft_init_mutex(t_stock *stock);
//clear
void					ft_exit(t_stock *stock, t_philo *philo, int i);
int						norminette_dead(t_philo *philo);
//routine
int						eating(t_philo *philo);
int						sleeping(t_philo *philo);
void					*routine(void *args);
int						mutex_unlock(t_philo *philo);
int						printf_mutex(char *message, char *color, long time,
							t_philo *philo);

//utils
int						printf_mutex(char *message, char *color, long time,
							t_philo *philo);
int						ft_dead(t_philo *philo);
size_t					ft_milliseconde(void);
int						ft_usleep(size_t milli);
int						need_to_eat(t_stock *stock, t_philo *philo);
//monitor
int						ft_check_dead(t_philo *philo);
int						monitoring(t_philo *philo);
// one philo
void					*routine_one(void *args);
void					one_philo(t_philo *philo);

# define RESET "\033[0m"

# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

# define BBLACK "\033[40m"
# define BRED "\033[41m"
# define BGREEN "\033[42m"
# define BYELLOW "\033[43m"
# define BBLUE "\033[44m"
# define BMAGENTA "\033[45m"
# define BCYAN "\033[46m"
# define BWHITE "\033[47m"

# define CBLACK "\033[5;30m"
# define CRED "\033[5;31m"
# define CGREEN "\033[5;32m"
# define CYELLOW "\033[5;33m"
# define CBLUE "\033[5;34m"
# define CMAGENTA "\033[5;35m"
# define CCYAN "\033[5;36m"
# define CWHITE "\033[5;37m"

# define IBLACK "\033[3;30m"
# define IRED "\033[3;31m"
# define IGREEN "\033[3;32m"
# define IYELLOW "\033[3;33m"
# define IBLUE "\033[3;34m"
# define IMAGENTA "\033[3;35m"
# define ICYAN "\033[3;36m"
# define IWHITE "\033[3;37m"
#endif
