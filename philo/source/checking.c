/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 21:22:51 by anajmi            #+#    #+#             */
/*   Updated: 2022/04/15 00:14:12 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_digit(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	check_limit_int(int ac, char **av)
{
	int		i;
	long	check;

	i = 1;
	while (i < ac)
	{
		check = ft_atoi(av[i]);
		if (check == 0 || check == -1)
			return (0);
		if (av[i][0] == '\0' || av[i][0] == ' '
			|| (9 <= av[i][0] && av[i][0] <= 13))
			return (0);
		i++;
	}
	return (1);
}

int	arg_check(int ac, char **av)
{
	int	check[2];

	check[0] = check_digit(ac, av);
	check[1] = check_limit_int(ac, av);
	if (check[0] == 0 || check[1] == 0)
	{
		write(2, "Error\n", 7);
		return (0);
	}
	return (1);
}
