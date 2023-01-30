/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 14:36:03 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/30 13:29:21 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Return time_of_day en microsecondes
long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

// Return le temps passe depuis le debut du programme en microsecondes
long long	get_time_from_start(long long time_to_wait)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (time_to_wait > 0)
		return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - time_to_wait);
	return (0);
}

// fonction usleep avec plus de precision, attend time_in_ms milliseconds
void	ft_usleep(t_data *data, long int time_in_ms)
{
	long int	start_time;
	int			i;

	i = 0;
	start_time = get_time_from_start(data->t_start);
	while (get_time_from_start(data->t_start) < start_time + time_in_ms)
	{
		if (data->philo_dead == true)
			return ;
		usleep(time_in_ms / 20);
	}
}

// fonction usleep avec plus de precision, attend time_in_ms milliseconds
// Et check si le philo est mort pdt son temps de usleep
void	ft_usleep_routine(t_data *data, t_philo *philo, long int time_in_ms)
{
	long int	start_time;
	int			i;

	i = 0;
	start_time = get_time_from_start(data->t_start);
	while (get_time_from_start(data->t_start) < start_time + time_in_ms)
	{
		if (should_die(data, philo))
			return ;
		usleep(time_in_ms / 30);
	}
}
