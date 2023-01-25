/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 14:43:29 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/25 14:24:50 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	handle_t_creat_failed(t_data *data)
{
	sem_wait(data->exit);
	data->t_exit = true;
	sem_post(data->exit);
	sem_wait(data->writing);
	printf("%s\n", THREADS_CREATE);
	sem_post(data->writing);
	sem_wait(data->stop);
	data->philo_dead = true;
	sem_post(data->stop);
	return (1);
}

int	wait_all_child(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	waitpid(data->pid_check, &status, 0);
	while (i < data->input.n_philo)
	{
		waitpid(data->pid[i], &status, 0);
		i++;
	}
	return (WEXITSTATUS(status));
}

int	kill_all_process(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->input.n_philo)
	{
		kill(data->pid[i], SIGKILL);
		i++;
	}
	return (0);
}

int	create_thread(t_data *data, t_philo *philo)
{
	routine((void *)philo);
	// kill_all_process(data);
		// coment gerer ce retour d'erreur pour tous les childs ?
	// destroy_semaphore_until(data, ALL_SEM);
	(void)data;
	// pthread_detach(philo->thread);
		// return (2);
		// coment gerer ce retour d'erreur pour tous les childs ?
	return (0);
}

int	create_checker(t_data *data)
{
	data->pid_check = fork();
	if (data->pid_check == -1)
		return (1);
		// erreur
	if (data->pid_check == 0)
	{
		check(data);
	}
	return (0);
}

int	create_childs(t_data *data)
{
	int	i;

	i = 0;
	if (create_checker(data))
		return (1);
	data->t_start = get_time();
	while (i < data->input.n_philo)
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			return (2);
		// erreur
		if (data->pid[i] == 0)
		{
			if (create_thread(data, &data->philo[i]))
				return (3);
				// erreur
		}
		i += 2;
		if (i >= data->input.n_philo && i % 2 == 0)
		{
			ft_usleep(data, 10);
			i = 1;
		}
		// ft_usleep(data, 10);
	}
	return (wait_all_child(data), 0);
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_create(&data->checker, NULL, check_dead, (void *)data))
		return (handle_t_creat_failed(data));
	data->t_start = get_time();
	while (i < data->input.n_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, routine,
				(void *)&data->philo[i]))
			return (handle_t_creat_failed(data));
		i += 2;
		if (i >= data->input.n_philo && i % 2 == 0)
		{
			ft_usleep(data, 2);
			i = 1;
		}
	}
	return (join_threads(data));
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_join(data->checker, NULL))
		return (err_msg(THREADS_JOIN, 3));
	while (i < data->input.n_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL))
			return (err_msg(THREADS_JOIN, 4));
		i++;
	}
	return (0);
}
