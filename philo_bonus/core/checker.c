/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:58:32 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/29 11:58:19 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_philo_dead(t_philo *philo, t_data *data)
{
	long long	time;

	sem_wait(data->time);
	time = get_time_from_start(philo->t_until_die);
	sem_post(data->time);
	if (time > data->input.to_die)
	{
		data->philo_dead = true;
		sem_wait(data->writing);
		printf("%lld	%d %sis dead%s\n", get_time_from_start(data->t_start),
			philo->pos + 1, DEAD, DEFAULT);
		return (1);
	}
	ft_usleep_routine(data, philo, 1);
	return (0);
}

int	has_eaten(t_data *data, t_philo *philo)
{
	sem_wait(data->eat);
	if (philo->meal_count >= data->input.n_meal)
	{
		sem_post(data->eat);
		return (1);
	}
	sem_post(data->eat);
	return (0);
}

void	*check_dead(void *arg)
{
	int		i;
	t_philo	*philo;
	t_data	*data;

	i = 0;
	philo = (t_philo *)arg;
	data = philo->data_mem;
	if (data->input.n_meal)
	{
		while (!should_die(data, philo) && !has_eaten(data, philo))
		{
			if (is_philo_dead(philo, data))
			{
				// sem_wait(data->writing);
				printf("MORT PAR CHECKER\n\n\n");
				// sem_post(data->writing);
				kill_process_until(data, data->input.n_philo);
				return (NULL);
			}
		}
	}
	else
	{
		while (!should_die(data, philo))
		{
			if (is_philo_dead(philo, data))
			{
				// sem_wait(data->writing);
				printf("MORT PAR CHECKER\n\n\n");
				// sem_post(data->writing);
				kill_process_until(data, data->input.n_philo);
				return (NULL);
			}
		}
	}
	// sem_wait(data->writing);
	printf("FIN CHECKER !\n");
	// sem_post(data->writing);
	return (NULL);
}
