/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 14:58:50 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/22 20:57:22 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	eating(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(philo->r_fork);
	print_action(philo, data, TAKEN_FORK);
	pthread_mutex_lock(philo->l_fork);
	print_action(philo, data, TAKEN_FORK);
	print_action(philo, data, EATING);
	ft_usleep(data, data->input.to_eat);
	philo->meal_count++;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

int	sleeping(t_philo *philo, t_data *data)
{
	print_action(philo, data, SLEEPING);
	ft_usleep(data, data->input.to_sleep);
	return (0);
}

int	thinking(t_philo *philo, t_data *data)
{
	print_action(philo, data, THINKING);
	return (0);
}
