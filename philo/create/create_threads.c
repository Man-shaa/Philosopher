/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 14:43:29 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/23 14:39:32 by msharifi         ###   ########.fr       */
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
			return (err_msg(THREADS, 1));
		i += 2;
		if (i >= data->input.n_philo && i % 2 == 0)
		{
			i = 1;
			ft_usleep(data, 2);
		}
	}
	return (join_threads(data));
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_join(data->checker, NULL))
		return (err_msg(THREADS, 1));
	while (i < data->input.n_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL))
			return (err_msg(THREADS, 1));
		i++;
	}
	return (0);
}
