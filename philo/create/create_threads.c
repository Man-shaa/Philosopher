/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 14:43:29 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/29 20:05:17 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	data->t_start = get_time();
	if (pthread_create(&data->checker, NULL, check_dead, (void *)data))
		return (err_msg(THREADS, 1));
	while (i < data->input.n_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, &routine,
				(void *)&data->philo[i]))
			return (err_msg(THREADS, 2));
		i += 2;
		if (i >= data->input.n_philo && i % 2 == 0)
		{
			i = 1;
			if (data->input.to_eat < data->input.to_die)
				ft_usleep(data, data->input.to_eat);
			else
				ft_usleep(data, data->input.to_die / 2);
		}
		usleep(30);
	}
	return (join_threads(data));
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_join(data->checker, NULL))
		return (err_msg(THREADS, 3));
	while (i < data->input.n_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL))
			return (err_msg(THREADS, 4));
		i++;
	}
	return (0);
}
