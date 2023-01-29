/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_childs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 14:43:29 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/29 11:59:49 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	kill_process_until(t_data *data, int until)
{
	int	i;

	i = 0;
	while (i < until)
	{
		usleep(100);
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

	i = -1;
	waitpid(-1, &status, 0);
	if (WEXITSTATUS(status) == 1)
	{
		printf("Someone has exited with a death !\n\n");
		while (++i < data->input.n_philo)
			kill(data->pid[i], SIGKILL);
		return (0);
	}
	printf("		Va wait tout le monde\n\n");
	while (++i < data->input.n_philo)
	{
		printf("Attends la fin de %d\n", i);
		waitpid(data->pid[i], NULL, 0);
		printf("%d a termine !\n", i);
	}
	return (0);
}

int	create_childs(t_data *data)
{
	int		i;

	i = 0;
	data->t_start = get_time();
	while (i < data->input.n_philo)
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			return (err_msg(FORK, 1), kill_process_until(data, i), 1);
		if (data->pid[i] == 0)
			child(data, &data->philo[i]);
		i += 2;
		if (i >= data->input.n_philo && i % 2 == 0)
		{
			i = 1;
			if (data->input.to_eat < data->input.to_die)
				ft_usleep(data, data->input.to_eat);
			else
				ft_usleep(data, data->input.to_die / 2);
		}
	}
	wait_all_child(data);
	return (0);
}
