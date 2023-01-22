/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 17:23:45 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/22 21:07:21 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_mutex(t_data *data)
{
	int				i;

	i = 0;
	if (pthread_mutex_init(&data->writing, NULL))
		return (err_msg(MUTEX_INIT, 1));
	if (pthread_mutex_init(&data->stop, NULL))
		return (pthread_mutex_destroy(&data->writing), err_msg(MUTEX_INIT, 2));
	while (i < data->input.n_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL))
			return (destroy_until(data, i), err_msg(MUTEX_INIT, 3));
		i++;
	}
	i = 0;
	while (i < data->input.n_philo)
	{
		data->philo[i].l_fork = &data->fork[i];
		if (i == data->input.n_philo - 1)
			data->philo[i].r_fork = &data->fork[0];
		else
			data->philo[i].r_fork = &data->fork[i + 1];
		i++;
	}
	return (0);
}

int	destroy_until(t_data *data, int n)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->writing);
		return (1);
	pthread_mutex_destroy(&data->stop);
		return (2);
	while (i < n)
	{
		pthread_mutex_destroy(&data->fork[i]);
			return (3);
		i++;
	}
	return (0);
}

int	destroy_all_mutex(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->writing);
	pthread_mutex_destroy(&data->stop);
	while (i < data->input.n_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	return (0);
}
