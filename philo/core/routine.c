/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:47:47 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/22 20:12:49 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data_mem;

	philo = (t_philo *)arg;
	data_mem = philo->data_mem;
	if (data_mem->input.n_meal)
	{
		while (!data_mem->philo_dead && philo->meal_count < data_mem->input.n_meal)
			life_loop(philo);
	}
	else
	{
		while (!data_mem->philo_dead)
			life_loop(philo);
	}
	return (NULL);
}

int	life_loop(t_philo *philo)
{
	eating(philo, philo->data_mem);
	sleeping(philo, philo->data_mem);
	thinking(philo, philo->data_mem);
	return (0);
}
