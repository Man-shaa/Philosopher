/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_childs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 14:43:29 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/26 15:24:58 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	kill_process_until(t_data *data, int until)
{
	int	i;

	i = 0;
	while (i < until)
	{
		kill(data->pid[i], SIGKILL);
		i += 2;
		if (i >= until && i % 2 == 0)
			i = 1;
	}
	return (0);
}

// int	wait_all_child(t_data *data, int n)
// {
// 	int	status;
// 	int	i;

// 	i = 0;
// 	if (n == 0)
// 	{
// 		while (data->pid[i] != waitpid(data->pid[i], &status, WNOHANG))
// 		{
// 			if (i == data->input.n_philo - 1)
// 				i = -1;
// 			i++;
// 			usleep(200);
// 		}
// 		// if (WEXITSTATUS(status) == 0)
// 		// 	wait_all_child(data, 0);
// 		// else
// 		// {
// 		if (WEXITSTATUS(status) == 1)
// 		{
// 			printf("%d has exited\n", i + 1);
// 			destroy_semaphore(data);
// 			kill_process_until(data, data->input.n_philo);
// 			return (1);
// 		}
// 		else
// 		{
// 			destroy_semaphore(data);
// 			kill_process_until(data, data->input.n_philo);
// 			return (0);
// 		}
// 		// }
// 	}
// 	else
// 	{
// 			destroy_semaphore(data);
// 			kill_process_until(data, data->input.n_philo);
// 			return (0);
// 	}
// 	return (0);
// }

int	wait_all_child(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->input.n_philo)
	{
		waitpid(data->pid[i], &status, 0);
		if (WEXITSTATUS(status) == 1)
		{
			kill_process_until(data, data->input.n_philo);
			return (1);
		}
		i++;
	}
	return (0);
}

int	create_childs(t_data *data)
{
	int	i;

	i = 0;
	data->t_start = get_time();
	while (i < data->input.n_philo)
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			return (err_msg(FORK, 1), kill_process_until(data, i), 1);
		if (data->pid[i] == 0)
			routine(data, &data->philo[i]);
		i += 2;
		if (i >= data->input.n_philo && i % 2 == 0)
		{
			i = 1;
			ft_usleep(data, data->input.to_eat);
		}
	}
	return (wait_all_child(data), 0);
}
