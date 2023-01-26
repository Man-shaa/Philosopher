/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_semaphores.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:01:54 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/26 14:01:35 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Si un semaphore est toujours open de la precedente exectuion du programme,
// tente de l'ouvrir sans le cree, si ca fonctione le supprime
// ouvre le sempahore en O_CREAT apres la verificatoin
int	init_semaphores(t_data *data)
{
	sem_unlink("/fork_sem");
	data->fork = sem_open("/fork_sem", O_CREAT, 0644, data->input.n_philo);
	if (data->fork == SEM_FAILED)
		return (err_msg(SEM_OPEN, 1));
	sem_unlink("/stop_sem");
	data->stop = sem_open("/stop_sem", O_CREAT, 0644, 1);
	if (data->stop == SEM_FAILED)
		return (err_msg(SEM_OPEN, 2));
	return (0);
}

void	destroy_semaphore(t_data *data)
{
	sem_close(data->fork);
	sem_unlink("/fork_sem");
	sem_close(data->stop);
	sem_unlink("/stop_sem");
}