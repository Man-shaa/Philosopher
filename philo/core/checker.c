/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:11:37 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/23 17:14:10 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
		printf("%lld	%d is dead\n", get_time_from_start(data->t_start),
			*i + 1);
		pthread_mutex_unlock(&data->writing);
		return (1);
	}
	ft_usleep(data, 1);
	(*i)++;
	return (0);
}
