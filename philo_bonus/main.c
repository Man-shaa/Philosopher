/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:52:59 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/29 19:02:23 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

// cree un sem_t pour le cas ou les threads ne se cree pas tous et qu'il faut
// sortir sans message "X is dead" et ecrire le message seulement si cette valeur
// est a 0

// 3 60 300 300 bloque a l'infini par l'attente de la 2eme fourchette

int	main(int ac, char **av)
{
	t_data	data;

	if (parsing(ac, av))
		return (1);
	if (create_data(&data, ac, av))
		return (2);
	if (init_semaphores(&data))
		return (3);
	if (data.input.n_philo == 1)
		return (one_philo(&data), 0);
	if (create_childs(&data))
		return (destroy_semaphore(&data), 4);
	destroy_semaphore(&data);
	return (0);
}
