/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 14:58:50 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/22 17:06:28 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	eating(t_philo *philo, t_data *data)
{
	print_action(philo, data, EATING);
	ft_usleep(data, data->input.to_eat);
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