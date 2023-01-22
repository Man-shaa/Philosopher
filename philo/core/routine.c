/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:47:47 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/22 16:56:54 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data_mem;

	philo = (t_philo *)arg;
	data_mem = philo->data_mem;
	life_loop(philo);
	return (NULL);
}

int	life_loop(t_philo *philo)
{
	eating(philo, philo->data_mem);
	sleeping(philo, philo->data_mem);
	thinking(philo, philo->data_mem);
	return (0);
}
