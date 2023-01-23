/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:47:47 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/23 16:06:45 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data_mem;
	int		i;
	int		stop;

	stop = 0;
	philo = (t_philo *)arg;
	data_mem = philo->data_mem;
	i = 0;
	if (data_mem->input.n_meal)
	{
		while (stop == false && philo->meal_count < data_mem->input.n_meal)
			if (life_loop(philo, data_mem, &stop))
				return (NULL);
	}
	else
	{
		while (stop == false)
			if (life_loop(philo, data_mem, &stop))
				return (NULL);
	}
	return (NULL);
}

int	should_stop(t_data *data, int *stop)
{
	pthread_mutex_lock(&data->stop);
	*stop = data->philo_dead;
	pthread_mutex_unlock(&data->stop);
	if (*stop == true)
		return (1);
	return (0);
}

int	life_loop(t_philo *philo, t_data *data, int *stop)
{
	if (should_stop(data, stop))
		return (2);
	if (eating(philo, philo->data_mem))
		return (1);
	if (should_stop(data, stop))
		return (2);
	if (sleeping(philo, philo->data_mem))
		return (1);
	if (should_stop(data, stop))
		return (2);
	if (thinking(philo, philo->data_mem))
		return (1);
	if (should_stop(data, stop))
		return (2);
	return (0);
}

int	has_eaten(t_data *data, int i)
{
	pthread_mutex_lock(&data->meal);
	if (data->philo[i].meal_count < data->input.n_meal)
	{
		pthread_mutex_unlock(&data->meal);
		return (0);
	}
	pthread_mutex_unlock(&data->meal);
	return (1);
}

void	*check_dead(void *arg)
{
	int		i;
	t_data	*data;

	i = 0;
	data = (t_data *)arg;
	if (data->input.n_meal)
	{
		while (!data->philo_dead && !has_eaten(data, i))
			if (is_philo_dead(data, &i))
				return (NULL);
	}
	else
	{
		while (!data->philo_dead)
			if (is_philo_dead(data, &i))
				return (NULL);
	}
	return (NULL);
}

int	is_philo_dead(t_data *data, int *i)
{
	long long	time;

	if (*i == data->input.n_philo - 1)
		*i = 0;
	pthread_mutex_lock(&data->time);
	time = get_time_from_start(data->philo[(*i)].t_until_die);
	pthread_mutex_unlock(&data->time);
	if (time > data->input.to_die)
	{
		pthread_mutex_lock(&data->stop);
		data->philo_dead = true;
		pthread_mutex_unlock(&data->stop);
		pthread_mutex_lock(&data->writing);
		ft_usleep(data, 4);
		printf("%lld	%d is dead\n", get_time_from_start(data->t_start), *i + 1);
		pthread_mutex_unlock(&data->writing);
		return (1);
	}
	ft_usleep(data, 1);
	(*i)++;
	return (0);
}

void	one_philo(t_data *data)
{
	data->t_start = get_time();
	printf("0	1%s", TAKEN_FORK);
	ft_usleep(data, data->input.to_die);
	printf("%ld	1%s", data->input.to_die, PHILO_DIED);
}
