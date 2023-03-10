/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:27:20 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/24 21:54:21 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (parsing(ac, av))
		return (1);
	if (create_data(&data, ac, av))
		return (2);
	if (data.input.n_philo == 1)
		return (one_philo(&data), 0);
	if (create_threads(&data))
		return (3);
	destroy_until(&data, data.input.n_philo);
	return (0);
}
