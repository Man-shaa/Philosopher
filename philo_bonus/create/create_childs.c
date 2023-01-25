/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_childs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 14:43:29 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/25 21:49:18 by msharifi         ###   ########.fr       */
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
		if (i > until && i % 2 == 0)
			i = 1;
	}
	return (0);
}

int	wait_all_child(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < data->input.n_philo)
	{
		waitpid(data->pid[i], &status, 0);
		if (WEXITSTATUS(status) == 1)
		{
			printf("recu instruction kill\n\n");
			return (kill_process_until(data, data->input.n_philo));
		}
		i++;
	}
	destroy_semaphore(data);
	return (WEXITSTATUS(status));
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
			i = 1;
		ft_usleep(data, 3);
	}
	return (wait_all_child(data), 0);
}
