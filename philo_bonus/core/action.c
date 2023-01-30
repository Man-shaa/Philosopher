/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:04:16 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/30 13:26:40 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	eating(t_data *data, t_philo *philo)
{
	sem_wait(data->fork);
	if (print_action(philo, data, TAKEN_FORK))
		return (1);
	sem_wait(data->fork);
	if (print_action(philo, data, TAKEN_FORK))
		return (1);
	if (print_action(philo, data, EATING))
		return (1);
	sem_wait(data->time);
	philo->t_until_die = get_time();
	sem_post(data->time);
	ft_usleep_routine(data, philo, data->input.to_eat);
	sem_post(data->fork);
	sem_post(data->fork);
	sem_wait(data->eat);
	philo->meal_count++;
	sem_post(data->eat);
	return (0);
}

int	sleeping(t_data *data, t_philo *philo)
{
	if (print_action(philo, data, SLEEPING))
		return (1);
	ft_usleep_routine(data, philo, data->input.to_sleep);
	return (0);
}

int	thinking(t_data *data, t_philo *philo)
{
	if (print_action(philo, data, THINKING))
		return (1);
	return (0);
}
