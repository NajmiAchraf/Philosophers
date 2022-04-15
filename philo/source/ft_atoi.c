/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:52:01 by anajmi            #+#    #+#             */
/*   Updated: 2022/04/15 00:14:16 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_nbr(long nbr, int sign)
{
	if (sign * nbr > MAXINT)
		return (-1);
	else if (sign * nbr < MININT)
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	long	nbr;
	int		sign;
	int		a;

	a = 0;
	nbr = 0;
	sign = 1;
	while (str[a] == ' ' || (9 <= str[a] && str[a] <= 13))
		a++;
	if (str[a] == '-' || str[a] == '+')
	{
		if (str[a] == '-')
			sign *= (-1);
		a++;
	}
	while ('0' <= str[a] && str[a] <= '9')
	{
		nbr *= 10;
		nbr += str[a] - '0';
		if (check_nbr(nbr, sign) <= 0)
			return (check_nbr(nbr, sign));
		a++;
	}
	return (nbr * sign);
}