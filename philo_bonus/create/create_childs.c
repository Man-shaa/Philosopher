/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_childs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 14:43:29 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/25 17:55:32 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
			kill_all_process(data);
		}
		i++;
	}
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
			return (1);
		// erreur + stop tous les precedents
		if (data->pid[i] == 0)
			routine(data, &data->philo[i]);
		i += 2;
		if (i >= data->input.n_philo && i % 2 == 0)
			i = 1;
		ft_usleep(data, 3); //utile ?
	}
	return (wait_all_child(data), 0);
}
