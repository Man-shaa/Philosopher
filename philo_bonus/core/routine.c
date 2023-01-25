/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:33:07 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/25 16:19:37 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/philo.h"

int	check(t_data *data)
{
	sem_wait(data->stop);
	if (data->philo_dead == true)
	{
		sem_post(data->stop);
		return (1);
	}
	sem_post(data->stop);
	sem_wait(data->exit);
	if (data->t_exit == true)
	{
		sem_post(data->exit);
		return (1);
	}
	sem_post(data->exit);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = (t_data *)philo->data_mem;
	if (data->input.n_meal)
	{
		while (!check(data) && philo->meal_count < data->input.n_meal)
			if (life_loop(data, philo))
			{
				return (NULL);
			}
	}
	else
	{
		while (!check(data))
			if (life_loop(data, philo))
			{
				return (NULL);
			}
	}
	return (NULL);
}

int	life_loop(t_data *data, t_philo *philo)
{
	if (data->philo_dead == true)
		return (1);
	if (eating(data, philo))
		return (2);
	if (data->philo_dead == true)
		return (1);
	if (sleeping(data, philo))
		return (3);
	if (data->philo_dead == true)
		return (1);
	if (thinking(data, philo))
		return (4);
	if (data->philo_dead == true)
		return (1);
	return (0);
}

void	one_philo(t_data *data)
{
	data->t_start = get_time();
	printf("0	1%s", TAKEN_FORK);
	ft_usleep(data, data->input.to_die);
	printf("%ld	1%s", data->input.to_die, PHILO_DIED);
}
