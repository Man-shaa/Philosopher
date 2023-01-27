/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:58:32 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/27 16:23:33 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*checker(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = (t_data *)philo->data_mem;
	if (data->input.n_meal)
	{
		while (!should_die(data, philo) && philo->meal_count < data->input.n_meal)
			ft_usleep_routine(data, philo, data->input.to_die);
		return (NULL);
	}
	else
	{
		while (!should_die(data, philo))
			ft_usleep_routine(data, philo, data->input.to_die);
		return (NULL);
	}
	return (NULL);
}
