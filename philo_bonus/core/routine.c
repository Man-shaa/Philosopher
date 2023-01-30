/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:33:07 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/30 13:39:32 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/philo.h"

int	child(t_data *data, t_philo *philo)
{
	while (!should_die(data, philo)
		&& (!data->input.n_meal || philo->meal_count < data->input.n_meal))
	{
		if (life_loop(data, philo))
		{
			usleep(1000);
			destroy_semaphore(data);
			exit (1);
		}
	}
	if (should_die(data, philo))
	{
		usleep(1000);
		destroy_semaphore(data);
		exit (1);
	}
	pthread_detach(philo->thread);
	destroy_semaphore(data);
	exit (0);
}

// Verifie si philo est mort, si oui set data->philo_dead a true
// Return 1 si le philo est mort, sinon return 0
int	should_die(t_data *data, t_philo *philo)
{
	long long	time;

	sem_wait(data->time);
	time = get_time_from_start(philo->t_until_die);
	sem_post(data->time);
	sem_wait(data->dead);
	if (data->philo_dead == true)
		return (sem_post(data->dead), 1);
	sem_post(data->dead);
	if (time > data->input.to_die)
	{
		sem_wait(data->dead);
		data->philo_dead = true;
		sem_post(data->dead);
		sem_wait(data->writing);
		printf("%lld	%d is dead\n", get_time_from_start(data->t_start),
			philo->pos + 1);
		return (1);
	}
	return (0);
}

int	life_loop(t_data *data, t_philo *philo)
{
	if (pthread_create(&philo->thread, NULL, check_dead, philo))
		return (err_msg(TCREAT, 2));
	if (should_die(data, philo))
		return (pthread_detach(philo->thread), 1);
	if (eating(data, philo))
		return (pthread_detach(philo->thread), 3);
	if (should_die(data, philo))
		return (pthread_detach(philo->thread), 1);
	if (sleeping(data, philo))
		return (pthread_detach(philo->thread), 4);
	if (should_die(data, philo))
		return (pthread_detach(philo->thread), 1);
	if (thinking(data, philo))
		return (pthread_detach(philo->thread), 5);
	if (should_die(data, philo))
		return (pthread_detach(philo->thread), 1);
	pthread_detach(philo->thread);
	return (0);
}

void	one_philo(t_data *data)
{
	data->pid[0] = fork();
	if (data->pid[0] == 0)
	{
		data->t_start = get_time();
		printf("0	1%s", TAKEN_FORK);
		ft_usleep(data, data->input.to_die);
		printf("%ld	1%s", data->input.to_die, PHILO_DIED);
	}
	waitpid(data->pid[0], NULL, 0);
	destroy_semaphore(data);
}
