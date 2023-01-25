/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:33:07 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/25 21:52:00 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/philo.h"

int	check(t_data *data)
{
	if (data->philo_dead == true)
		return (1);
	return (0);
}

void	routine(t_data *data, t_philo *philo)
{
	ft_usleep(data, 200);
	if (data->input.n_meal)
	{
		while (data->philo_dead == false && philo->meal_count < data->input.n_meal)
		{
			if (life_loop(data, philo))
			{
				destroy_semaphore(data);
				exit (1);
			}

		}
	}
	while (data->philo_dead == false)
	{
		if (life_loop(data, philo))
		{
			destroy_semaphore(data);
			exit (1);
		}
	}
	destroy_semaphore(data);
	exit (0);
}

int	someone_is_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->input.n_philo)
	{
		if (kill(data->pid[i], SIGUSR1) == -1)
			return (printf("reception mort !!!!!\n\n"), 1);
		i++;
	}
	return (0);
}

int	should_die(t_data *data, t_philo *philo)
{
	long long	time;

	time = get_time_from_start(philo->t_until_die);
	(void)time;
	if (someone_is_dead(data))
	{
		data->philo_dead = true;
		sem_wait(data->stop);
		printf("%lld	%d is dead\n", get_time_from_start(data->t_start), philo->pos + 1);
		return (1);
	}
	return (0);
}

int	life_loop(t_data *data, t_philo *philo)
{
	if (should_die(data, philo))
		return (1);
	if (eating(data, philo))
		return (2);
	if (should_die(data, philo))
		return (1);
	if (sleeping(data, philo))
		return (3);
	if (should_die(data, philo))
		return (1);
	if (thinking(data, philo))
		return (4);
	if (should_die(data, philo))
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
