/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 14:58:50 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/23 16:58:27 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	eating(t_philo *philo, t_data *data)
{
	if (print_action(philo, data, EATING))
		return (pthread_mutex_unlock(philo->l_fork),
			pthread_mutex_unlock(philo->r_fork), 1);
	pthread_mutex_lock(&data->time);
	philo->t_until_die = get_time();
	pthread_mutex_unlock(&data->time);
	ft_usleep(data, data->input.to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_lock(&data->meal);
	philo->meal_count++;
	pthread_mutex_unlock(&data->meal);
	return (0);
}

int	fork_and_eating(t_philo *philo, t_data *data)
{
	if (philo->pos == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		if (print_action(philo, data, TAKEN_FORK))
			return (pthread_mutex_unlock(philo->r_fork), 1);
		pthread_mutex_lock(philo->l_fork);
		if (print_action(philo, data, TAKEN_FORK))
			return (pthread_mutex_unlock(philo->r_fork),
				pthread_mutex_unlock(philo->l_fork), 1);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		if (print_action(philo, data, TAKEN_FORK))
			return (pthread_mutex_unlock(philo->l_fork), 1);
		pthread_mutex_lock(philo->r_fork);
		if (print_action(philo, data, TAKEN_FORK))
			return (pthread_mutex_unlock(philo->l_fork),
				pthread_mutex_unlock(philo->r_fork), 1);
	}
	return (eating(philo, data));
}

int	sleeping(t_philo *philo, t_data *data)
{
	if (print_action(philo, data, SLEEPING))
		return (1);
	ft_usleep(data, data->input.to_sleep);
	return (0);
}

int	thinking(t_philo *philo, t_data *data)
{
	if (print_action(philo, data, THINKING))
		return (1);
	return (0);
}
