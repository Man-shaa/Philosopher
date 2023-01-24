/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_semaphores.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:01:54 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/24 20:49:05 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Si un semaphore est toujours open de la precedente exectuion du programme,
// tente de l'ouvrir sans le cree, si ca fonctione le supprime
void	init_sem_to_null(t_data *data)
{
	data->fork = sem_open("fork_sem", data->input.n_philo);
	if (data->fork != SEM_FAILED)
	{
		sem_close(data->fork);
		sem_unlink("fork_sem");
	}
	data->writing = sem_open("write_sem", 1);
	if (data->writing != SEM_FAILED)
	{
		sem_close(data->writing);
		sem_unlink("write_sem");
	}
	data->stop = sem_open("stop_sem", 1);
	if (data->stop != SEM_FAILED)
	{
		sem_close(data->stop);
		sem_unlink("stop_sem");
	}
	init_sem_to_null_2(data);
}

void	init_sem_to_null_2(t_data *data)
{
	data->meal = sem_open("meal_sem", 1);
	if (data->meal != SEM_FAILED)
	{
		sem_close(data->meal);
		sem_unlink("meal_sem");
	}
	data->time = sem_open("time_sem", 1);
	if (data->time != SEM_FAILED)
	{
		sem_close(data->time);
		sem_unlink("time_sem");
	}
	data->exit = sem_open("exit_sem", 1);
	if (data->exit != SEM_FAILED)
	{
		sem_close(data->exit);
		sem_unlink("exit_sem");
	}
}

// cree tous les semaphores necessaires au programme
int	init_semaphores(t_data *data)
{
	init_sem_to_null(data);
	data->fork = sem_open("fork_sem", O_CREAT, 0644, data->input.n_philo);
	if (data->fork == SEM_FAILED)
		return (err_msg(SEM_OPEN, 1));
	data->writing = sem_open("write_sem", O_CREAT, 0644, 1);
	if (data->writing == SEM_FAILED)
		return (destroy_semaphore_until(data, 1), err_msg(SEM_OPEN, 2));
	data->stop = sem_open("stop_sem", O_CREAT, 0644, 1);
	if (data->stop == SEM_FAILED)
		return (destroy_semaphore_until(data, 2), err_msg(SEM_OPEN, 3));
	data->meal = sem_open("meal_sem", O_CREAT, 0644, 1);
	if (data->meal == SEM_FAILED)
		return (destroy_semaphore_until(data, 3), err_msg(SEM_OPEN, 4));
	data->time = sem_open("time_sem", O_CREAT, 0644, 1);
	if (data->time == SEM_FAILED)
		return (destroy_semaphore_until(data, 4), err_msg(SEM_OPEN, 4));
	data->exit = sem_open("exit_sem", O_CREAT, 0644, 1);
	if (data->exit == SEM_FAILED)
		return (destroy_semaphore_until(data, 5), err_msg(SEM_OPEN, 4));
	return (0);
}

// detruit x semaphores en fontion de [until]
void	destroy_semaphore_until(t_data *data, int until)
{
	if (until >= 1 && data->fork != SEM_FAILED)
	{
		sem_close(data->fork);
		sem_unlink("fork_sem");
	}
	if (until >= 2 && data->writing != SEM_FAILED)
	{
		sem_close(data->writing);
		sem_unlink("write_sem");
	}
	if (until >= 3 && data->stop != SEM_FAILED)
	{
		sem_close(data->stop);
		sem_unlink("stop_sem");
	}
	if (until > 3)
		destroy_semaphore_until2(data, until);
}

void	destroy_semaphore_until2(t_data *data, int until)
{
	if (until >= 4 && data->meal != SEM_FAILED)
	{
		sem_close(data->meal);
		sem_unlink("meal_sem");
	}
	if (until >= 5 && data->time != SEM_FAILED)
	{
		sem_close(data->time);
		sem_unlink("time_sem");
	}
	if (until >= 6 && data->time != SEM_FAILED)
	{
		sem_close(data->exit);
		sem_unlink("exit_sem");
	}
}