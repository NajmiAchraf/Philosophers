/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:33:35 by anajmi            #+#    #+#             */
/*   Updated: 2022/04/15 00:17:49 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	fill_data(t_data *data, int ac, char *av[])
{
	if (ac == 5 || ac == 6)
	{
		data->nb_philo = ft_atoi(av[1]);
		data->tdie = ft_atoi(av[2]);
		data->teat = ft_atoi(av[3]);
		data->tsleep = ft_atoi(av[4]);
		data->nbr_to_eat = 0;
		if (ac == 6)
			data->nbr_to_eat = ft_atoi(av[5]);
		return (1);
	}
	return (0);
}

static int	distribute(t_profile *profile, t_data *data)
{
	int	i;

	i = data->nb_philo;
	while (--i > 0)
	{
		profile[i].rfork = &profile[i].fork;
		profile[i].lfork = &profile[i - 1].fork;
	}
	profile[i].rfork = &profile[i].fork;
	profile[i].lfork = &profile[data->nb_philo - 1].fork;
	i = data->nb_philo;
	while (--i >= 0)
	{
		profile[i].mutex_print = &data->mutex_print;
		profile[i].data = data;
		if (data->nbr_to_eat > 0)
			profile[i].nbr_to_eat = 0;
		else
			profile[i].nbr_to_eat = -1;
		profile[i].id = i + 1;
		profile[i].last_eat = 0;
		profile[i].is_eat = 0;
		profile[i].is_die = 0;
	}
	return (1);
}

static int	initialization(t_profile *profile)
{
	size_t	i;

	i = -1;
	while (++i < profile[0].data->nb_philo)
		pthread_mutex_init(&profile[i].fork, NULL);
	i = -1;
	while (++i < profile[0].data->nb_philo)
		pthread_create(&profile[i].philo, NULL, race, &profile[i]);
	i = -1;
	while (++i < profile[0].data->nb_philo)
		pthread_detach(profile[i].philo);
	return (1);
}

int	main(int ac, char *av[])
{
	t_data			*data;
	t_profile		*profile;
	pthread_t		super;
	int				i;

	data = malloc(sizeof(t_data));
	if (!data || !arg_check(ac, av) || !fill_data(data, ac, av))
		return (0);
	pthread_mutex_init(&data->mutex_print, NULL);
	profile = malloc(data->nb_philo * sizeof(t_profile));
	if (!profile || !distribute(profile, data) || !initialization(profile))
		return (0);
	pthread_create(&super, NULL, visor, profile);
	pthread_join(super, NULL);
	pthread_mutex_destroy(&data->mutex_print);
	i = data->nb_philo;
	while (--i >= 0)
		pthread_mutex_destroy(&profile[i].fork);
	return (0);
}
