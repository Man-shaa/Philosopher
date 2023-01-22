/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 20:16:42 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/22 17:25:27 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	create_data(t_data *data, int ac, char **av)
{
	data->checker = 0;
	data->philo_dead = 0;
	data->t_start = 0;
	init_input(&data->input, ac, av);
	init_philo(data);
	init_mutex(data);
}

void	init_input(t_input *input, int ac, char **av)
{
	input->n_philo = ft_atoi(av[1]);
	input->to_die = ft_atoi(av[2]);
	input->to_eat = ft_atoi(av[3]);
	input->to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		input->n_meal = ft_atoi(av[5]);
	else
		input->n_meal = 0;
}

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->input.n_philo)
	{
		data->philo[i].meal_count = 0;
		data->philo[i].data_mem = 0;
		data->philo[i].pos = i;
		data->philo[i].t_until_die = 0;
		data->philo[i].thread = 0;
		data->philo[i].data_mem = data;
		i++;
	}
}
