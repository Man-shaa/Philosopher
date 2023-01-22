/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:47:47 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/22 23:13:11 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* TECHNIQUE CHELOU 

int	sub_check(t_data *data, t_philo *philo)
{
	long long	time;

	time = get_time_from_start(philo->t_until_die);
	if (time > data->input.to_die)
	{
		pthread_mutex_lock(&data->stop);
		data->philo_dead = 1;
		pthread_mutex_unlock(&data->stop);
		print_action(philo, data, PHILO_DIED);
		return (0);
	}
	return (1);
}

int	check_death(t_data	*data, int	*stop)
{
	int					i;

	i = 0;
	if (*stop == 1)
		return (0);
	while (i < data->input.n_philo)
	{
		if (sub_check(data, &data->philo[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

*/

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data_mem;

	philo = (t_philo *)arg;
	data_mem = philo->data_mem;
	if (data_mem->input.n_meal)
	{
		while (!data_mem->philo_dead && philo->meal_count < data_mem->input.n_meal)
			life_loop(philo);
	}
	else
	{
		while (!data_mem->philo_dead)
			life_loop(philo);
	}
	return (NULL);
}

int	life_loop(t_philo *philo)
{
	eating(philo, philo->data_mem);
	sleeping(philo, philo->data_mem);
	thinking(philo, philo->data_mem);
	return (0);
}

void	one_philo(t_data *data)
{
	data->t_start = get_time();
	printf("0	1%s", TAKEN_FORK);
	ft_usleep(data, data->input.to_die);
	printf("%ld	1%s", data->input.to_die, PHILO_DIED);
}

// void	*check_dead(void *arg)
// {
// 	int		i;
// 	t_data	*data;

// 	i = 0;
// 	data = (t_data *)arg;
// 	if (data->input.n_meal)
// 	{
// 		while (!data->philo_dead && data->philo[i].meal_count < data->input.n_meal)
// 			if (is_philo_dead(data, &i))
// 				return (NULL);
// 	}
// 	else
// 	{
// 		while (!data->philo_dead)
// 			if (is_philo_dead(data, &i))
// 				return (NULL);
// 	}
// 	return (NULL);
// }

// int	is_philo_dead(t_data *data, int *i)
// {
// 	long long	time;

// 	if (*i == data->input.n_philo - 1)
// 		*i = 0;
// 	time = get_time_from_start(data->philo[(*i)].t_until_die);
// 	if (time > data->input.to_die)
// 	{
// 		printf("HAAAAAAAAAAAAAAAAAAAAA\n\n\n");
// 		pthread_mutex_lock(&data->stop);
// 		data->philo_dead = true;
// 		pthread_mutex_unlock(&data->stop);
// 		print_action(&data->philo[(*i)], data, PHILO_DIED);
// 		return (1);
// 	}
// 	ft_usleep(data, 10);
// 	return (0);
// }
