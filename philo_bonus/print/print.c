/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:32:45 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/24 16:15:04 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	err_msg(char *s1, int ret_val)
{
	if (s1)
	{
		write(STDERR_FILENO, s1, ft_strlen(s1));
		write(STDERR_FILENO, "\n", 1);
	}
	return (ret_val);
}

int	print_action(t_philo *philo, t_data *data, char *action)
{
	sem_wait(data->writing);
	sem_wait(data->stop);
	if (data->philo_dead == true)
	{
		sem_post(data->stop);
		sem_post(data->writing);
		return (1);
	}
	sem_post(data->stop);
	printf("%lld	%d%s", get_time_from_start(data->t_start),
		philo->pos + 1, action);
	sem_post(data->writing);
	return (0);
}
