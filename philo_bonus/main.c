/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:52:59 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/25 13:00:57 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

// utiliser un sem_t par philo pour time et meal et pas un general a tous qui
// va les ralentir (peut etre negligeable ?)

// Utile de sem_post dans eating() si un philo est mort et que print_action()
// return 1 ? Ou inutile vis a vis de helgrind + performance + resultat?

// cree un sem_t pour le cas ou les threads ne se cree pas tous et qu'il faut
// sortir sans message "X is dead" et ecrire le message seulement si cette valeur
// est a 0

// 3 1 300 300 parfois le 1 meurt a 300 au liee de 1 ( bloque par sem_wait 
// de sa deuxieme fourchette)

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
	return (create_childs(&data));
		return (4);
	destroy_semaphore_until(&data, ALL_SEM);
	return (0);
}
