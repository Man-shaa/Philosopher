/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:52:50 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/29 11:39:15 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Verifie si str est compose uniquement de chiffre
// Return 0 si c'est le cas, sinon 1
int	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i])
		return (1);
	return (0);
}

// Verifie que tous les arguments recus sont positifs et dans la range d'un int
// Return 0 si tous sont conformes, sinon 1
int	is_positive_int(int ac, char **av)
{
	int		i;
	long	res;

	i = 1;
	while (i < ac)
	{
		if (!av[i][0])
			return (err_msg(INT, 1));
		if (is_num(av[i]))
			return (err_msg(NUMBER, 1));
		res = ft_atoi(av[i]);
		if (res < 0 || res > 2147483647)
			return (err_msg(INT, 1));
		i++;
	}
	return (0);
}

// Verifie que les arguments recus sont conformes
// return 0 si tout est bon, sinon un int positif non nul
int	parsing(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (err_msg(TUTO, 1));
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[1]) > 200)
		return (err_msg(N_PHILO, 2));
	if (is_positive_int(ac, av))
		return (3);
	return (0);
}
