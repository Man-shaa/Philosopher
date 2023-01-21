/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:27:20 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/21 20:25:43 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	print_philo(t_data data);
void	print_input(t_input input);

int	main(int ac, char **av)
{
	t_data	data;

	if (parsing(ac, av))
		return (1);
	if (create_data(&data, ac, av))
		return (2);
	print_input(data.input);
	// if (data.input.n_philo == 1)
	// {
	// 	one_philo(&data);
	// 	free_data(data);
	// 	return (0);
	// }
	// if (create_threads(&data))
	// 	return (free_data(data), 4);
	// free_data(data);
	return (0);
}

void	print_philo(t_data data)
{
	int		i;
	t_philo	*philo;

	philo = data.philo;
	i = 0;
	printf("\n");
	while (i < data.input.n_philo)
	{
		printf("********** Philo number [%d] **********\n\n", philo[i].pos);
		printf("  Pos : [%d]\n", philo[i].pos);
		printf("  Meal count : [%d]\n", philo[i].meal_count);
		i++;
		printf("\n");
	}
}

void	print_input(t_input input)
{
	printf ("\n************************* INPUT *************************\n\n");
	printf("   n_philo : [%d]\n", input.n_philo);
	printf("   to_die : [%ld]\n", input.to_die);
	printf("   to_eat : [%ld]\n", input.to_eat);
	printf("   to_sleep : [%ld]\n", input.to_sleep);
	printf("   n_meal : [%d]\n\n", input.n_meal);
}
