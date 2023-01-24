/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 14:43:29 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/24 21:15:53 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	handle_t_creat_failed(t_data *data)
{
	sem_wait(data->exit);
	data->t_exit = true;
	sem_post(data->exit);
	sem_wait(data->writing);
	printf("%s\n", THREADS_CREATE);
	sem_post(data->writing);
	sem_wait(data->stop);
	data->philo_dead = true;
	sem_post(data->stop);
	return (1);
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_create(&data->checker, NULL, check_dead, (void *)data))
		return (handle_t_creat_failed(data));
	data->t_start = get_time();
	while (i < data->input.n_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, routine,
				(void *)&data->philo[i]))
			return (handle_t_creat_failed(data));
		i += 2;
		if (i >= data->input.n_philo && i % 2 == 0)
		{
			ft_usleep(data, 2);
			i = 1;
		}
	}
	return (join_threads(data));
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_join(data->checker, NULL))
		return (err_msg(THREADS_JOIN, 3));
	while (i < data->input.n_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL))
			return (err_msg(THREADS_JOIN, 4));
		i++;
	}
	return (0);
}
