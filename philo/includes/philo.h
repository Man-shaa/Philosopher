/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:25:28 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/22 17:03:42 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

// actions
# define EATING			" is eating\n"
# define SLEEPING		" is sleeping\n"
# define THINKING		" is thinking\n"
# define TAKEN_FORK		" has taken a fork\n"
# define PHILO_DIED		" died\n"

// error
# define MALLOC			"Error caused by a malloc"
# define MUTEX			"Error caused by a mutex init"
# define TUTO			"./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"
# define N_PHILO		"[number_of_philosophers] must be a non null \
positive integer"
# define INT			"All parameters must be a positive integer"
# define NUMBER			"All parameters must be numbers"
# define THREADS		"Error while creating/joining threads"
# define PHILO			"Error while creating t_philo structure (malloc)"
# define FORK			"Error while creating fork mutex"

// colors
# define DEFAULT		"\033[0m"
# define DEAD			"\033[4;31m"
# define RED			"\033[0;31m"
# define GREEN			"\033[0;32m"
# define BLUE			"\033[0;34m"
# define CYAN			"\033[0;36m"

typedef struct s_philo
{
	int			pos;
	int			meal_count;
	pthread_t	thread;
	long long	t_until_die;
	void		*data_mem;
}				t_philo;

typedef struct s_input
{
	long	to_die;
	long	to_eat;
	long	to_sleep;
	int		n_meal;
	int		n_philo;
}				t_input;

typedef struct s_data
{
	int				philo_dead;
	long long		t_start;
	pthread_t		checker;
	pthread_mutex_t	stop;
	pthread_mutex_t	writing;
	pthread_mutex_t	fork[200];
	t_input			input;
	t_philo			philo[200];
}				t_data;

// *********************************** CORE ***********************************

// actions.c
int			eating(t_philo *philo, t_data *data);
int			sleeping(t_philo *philo, t_data *data);
int			thinking(t_philo *philo, t_data *data);

// routine.c
void		*routine(void *arg);
int			life_loop(t_philo *philo);

// time.c
long long	get_time(void);
long long	get_time_from_start(long long time);
void		ft_usleep(t_data *data, long int time_in_ms);

// *********************************** CREATE *********************************

// create_data.c
void		create_data(t_data *data, int ac, char **av);
void		init_input(t_input *input, int ac, char **av);
void		init_philo(t_data *data);

// create_threads.c
int 		create_threads(t_data *data);
int			join_threads(t_data *data);

// *********************************** FREE ***********************************

// free.c

// ********************************** PARSING *********************************

// parsing.c
int			is_num(char *str);
int			is_positive_int(int ac, char **av);
int			parsing(int ac, char **av);

// *********************************** PRINT **********************************

// print.c
int			err_msg(char *s1, int ret_val);
int			print_action(t_philo *philo, t_data *data, char *action);

// *********************************** UTILS **********************************

// utils.c
int			ft_strlen(char *str);
long		ft_atoi(const char *str);
void		*ft_calloc(size_t n, size_t size);

#endif