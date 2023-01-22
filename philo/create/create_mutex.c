/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 17:23:45 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/22 20:12:56 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_mutex(t_data *data)
{
	int				i;
	pthread_mutex_t	fork[200];

	i = 0;
	if (pthread_mutex_init(&data->writing, NULL))
		return (err_msg(MUTEX_INIT, 1));
	if (pthread_mutex_init(&data->stop, NULL))
		return (err_msg(MUTEX_INIT, 2));
	while (i < data->input.n_philo)
	{
		if (pthread_mutex_init(&fork[i], NULL))
			return (err_msg(MUTEX_INIT, 3));
		i++;
	}
	i = 0;
	while (i < data->input.n_philo)
	{
		data->philo[i].l_fork = &fork[i];
		if (i == data->input.n_philo - 1)
			data->philo[i].r_fork = &fork[0];
		else
			data->philo[i].r_fork = &fork[i + 1];
		i++;
	}
	return (0);
}

int	destroy_all_mutex(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(&data->writing))
		return (err_msg(MUTEX_DES, 1));
	if (pthread_mutex_destroy(&data->stop))
		return (err_msg(MUTEX_DES, 2));
	// while (i < data->input.n_philo)
	// {
	// 	if (pthread_mutex_destroy(&data->fork[i]))
	// 		return (err_msg(MUTEX_DES, 3));
	// 	i++;
	// }
	return (0);
}
