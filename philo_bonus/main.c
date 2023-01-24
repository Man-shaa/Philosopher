/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:52:59 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/24 21:29:14 by msharifi         ###   ########.fr       */
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

void	test(t_data *data)
{
	pid_t	pid1;
	pid_t	pid2;

	pid1 = fork();
	if (pid1 == 0)
	{
		sem_wait(data->meal);
		printf("Child 1 a reussie a decrementer\n\n");
		sleep(2);
		printf("Child 1 a termine\n\n");
		sem_post(data->meal);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		sem_wait(data->meal);
		printf("Child 2 a reussie a decrementer\n\n");
		sleep(1);
		sem_post(data->meal);
	}
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int ac, char **av)
{
	t_data	data;

	// if (parsing(ac, av))
	// 	return (1);
	if (create_data(&data, ac, av))
		return (2);
	if (init_semaphores(&data))
		return (3);
	test(&data);
	
	// if (data.input.n_philo == 1)
	// 	return (one_philo(&data), 0);
	// return (create_threads(&data));
	// destroy_semaphore_until(&data, ALL_SEM);
	return (0);
}
