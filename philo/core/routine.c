/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:47:47 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/23 17:10:28 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check(t_data *data)
{
	pthread_mutex_lock(&data->stop);
	if (data->philo_dead)
	{
		pthread_mutex_unlock(&data->stop);
		return (1);
	}
	pthread_mutex_unlock(&data->stop);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data_mem;
	int		i;

	philo = (t_philo *)arg;
	data_mem = philo->data_mem;
	i = 0;
	if (data_mem->input.n_meal)
	{
		while (!check(data_mem)
			&& philo->meal_count
			< data_mem->input.n_meal)
			if (life_loop(philo, data_mem))
				return (NULL);
	}
	else
	{
		while (!check(data_mem))
			if (life_loop(philo, data_mem))
				return (NULL);
	}
	return (NULL);
}

int	should_stop(t_data *data)
{
	pthread_mutex_lock(&data->stop);
	if (data->philo_dead == 1)
	{
		pthread_mutex_unlock(&data->stop);
		return (1);
	}
	pthread_mutex_unlock(&data->stop);
	return (0);
}

int	life_loop(t_philo *philo, t_data *data)
{
	if (should_stop(data))
		return (2);
	if (fork_and_eating(philo, philo->data_mem))
		return (1);
	if (should_stop(data))
		return (2);
	if (sleeping(philo, philo->data_mem))
		return (1);
	if (should_stop(data))
		return (2);
	if (thinking(philo, philo->data_mem))
		return (1);
	if (should_stop(data))
		return (2);
	return (0);
}

void	one_philo(t_data *data)
{
	data->t_start = get_time();
	printf("0	1%s", TAKEN_FORK);
	ft_usleep(data, data->input.to_die);
	printf("%ld	1%s", data->input.to_die, PHILO_DIED);
}
