/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:58:32 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/27 23:46:26 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_philo_dead(t_philo *philo, t_data *data)
{
	long long	time;

	time = get_time_from_start(philo->t_until_die);
	if (time > data->input.to_die)
	{
		data->philo_dead = true;
		sem_wait(data->writing);
		printf("%lld	%d is dead\n", get_time_from_start(data->t_start),
			philo->pos + 1);
		return (1);
	}
	ft_usleep(data, 1);
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
		while (!data->philo_dead && philo->meal_count < data->input.n_meal)
		{
			if (is_philo_dead(philo, data))
			{
				printf("MORT PAR CHECKER\n\n\n");
				kill_process_until(data, data->input.n_philo);
				return (NULL);
			}
		}
	}
	else
	{
		while (!data->philo_dead)
		{
			if (is_philo_dead(philo, data))
			{
				printf("MORT PAR CHECKER\n\n\n");
				kill_process_until(data, data->input.n_philo);
				return (NULL);
			}
		}
	}
	return (NULL);
}
