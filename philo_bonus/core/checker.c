/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:53:51 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/25 16:21:31 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// int	has_eaten(t_data *data, t_philo *philo)
// {
// 	sem_wait(data->meal);
// 	if (philo->meal_count < data->input.n_meal)
// 	{
// 		sem_post(data->meal);
// 		return (1);
// 	}
// 	sem_post(data->meal);
// 	return (0);
// }

// void	*check_dead(void *arg)
// {
// 	t_data *data;
// 	int		i;
	
// 	data = (t_data *)arg;
// 	i = 0;
// 	if (data->input.n_meal)
// 	{
// 		while (!check(data) && has_eaten(data, &data->philo[i]))
// 			if (is_philo_dead(data, &i))
// 				return (NULL);
// 	}
// 	else
// 	{
// 		while (!check(data))
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
// 	sem_wait(data->time);
// 	time = get_time_from_start(data->philo[(*i)].t_until_die);
// 	sem_post(data->time);
// 	if (time > data->input.to_die)
// 	{
// 		sem_wait(data->stop);
// 		data->philo_dead = true;
// 		sem_post(data->stop);
// 		sem_wait(data->writing);
// 		printf("%lld	%d is dead\n", get_time_from_start(data->t_start), *i + 1);
// 		sem_post(data->writing);
// 		return (1);
// 	}
// 	(*i)++;
// 	usleep(20);
// 	return (0);
// }
