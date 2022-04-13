/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:52:01 by anajmi            #+#    #+#             */
/*   Updated: 2022/04/13 01:06:26 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

int	check_nbr(long nbr, int sign)
{
	if (sign * nbr > INT32_MAX)
		return (-1);
	else if (sign * nbr < INT32_MIN)
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
/*
int	main(void)
{
	int		val;
	char 	str[] = "9223372036854775807";
	// char 	str[] = "9223372036854775807";
	// char 	str[] = "4294967299";

	val = ft_atoi(str);
	printf("String value = %s, Int value = %d\n", str, val);
	val = atoi(str);
	printf("String value = %s, Int value = %d\n", str, val);
	return (0);
}
*/
