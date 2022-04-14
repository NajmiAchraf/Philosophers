/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:33:35 by anajmi            #+#    #+#             */
/*   Updated: 2022/04/14 02:15:57 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

size_t	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

size_t	timing(void)
{
	static size_t	t;

	if (!t)
		t = get_time();
	return (get_time() - t);
}

void	msleep(size_t time)
{
	size_t	t;

	t = get_time();
	while (1)
	{
		if (get_time() - t >= time)
			break ;
		usleep(1000);
	}
}

void	printing(t_profile *profile, char *color, char *str)
{
	printf("%s%zu %zu %s\n\033[0m", color, timing(), profile->id, str);
	// printf("%zu\n", timing());
}

void	*visor(void *param)
{
	t_profile	*profile;
	int			i;

	profile = (t_profile *)param;
	while (1)
	{
		i = 0;
		while (i < profile[0].data->nb_philo)
		{
			if (timing() - profile[i].last_eat >= profile[0].data->tdie)
			{
				printing(&profile[i], C_RED, DIE);
				return (0);
			}
			i++;
		}
	}
	return (0);
}

int	fill_data(t_data *data, int ac, char *av[])
{
	if (ac == 5 || ac == 6)
	{
		data->nb_philo = ft_atoi(av[1]);
		data->tdie = ft_atoi(av[2]);
		data->teat = ft_atoi(av[3]);
		data->tsleep = ft_atoi(av[4]);
		if (ac == 6)
			data->nb_teat = ft_atoi(av[5]);
		return (1);
	}
	return (0);
}

void	*race(void	*param)
{
	t_profile	*profile;

	profile = (t_profile *)param;
	if (profile->id % 2 == 0)
		msleep(15);
	while (1)
	{
		pthread_mutex_lock(profile->rfork);
		printing(profile, C_CYAN, TFORK);
		pthread_mutex_lock(profile->lfork);
		printing(profile, C_CYAN, TFORK);
		printing(profile, C_BLUE, ISEAT);
		msleep(profile->data->teat);
		profile->last_eat = timing();
		pthread_mutex_unlock(profile->rfork);
		pthread_mutex_unlock(profile->lfork);
		printing(profile, C_GREEN, ISLEP);
		msleep(profile->data->tsleep);
		printing(profile, C_YELOW, ISTHI);
	}
	return (0);
}

int	initialisation(t_data *data)
{
	t_profile	*profile;
	pthread_t	super;
	int			i;

	profile = malloc(data->nb_philo * sizeof(t_profile));
	if (!profile)
		return (0);
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
		profile[i].data = data;
		profile[i].id = i + 1;
		profile[i].last_eat = 0;
	}

	while (++i < data->nb_philo)
		pthread_mutex_init(&profile[i].fork, NULL);
	i = -1;
	while (++i < data->nb_philo)
		pthread_create(&profile[i].philo, NULL, race, &profile[i]);
	i = -1;
	while (++i < data->nb_philo)
		pthread_detach(profile[i].philo);
	pthread_create(&super, NULL, visor, profile);
	pthread_join(super, NULL);
	while (--i >= 0)
		pthread_mutex_destroy(&profile[i].fork);
	return (1);
}

int	distribute(t_profile *profile, t_data *data)
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
		profile[i].data = data;
		profile[i].id = i + 1;
		profile[i].last_eat = 0;
	}
	return (1);
}

int	initialization(t_profile *profile)
{
	int	i;

	i = -1;
	while (++i < profile[0].data->nb_philo)
	{
		if (!pthread_mutex_init(&profile[i].fork, NULL))
			return (0);
	}
	i = -1;
	while (++i < profile[0].data->nb_philo)
	{
		if (!pthread_create(&profile[i].philo, NULL, race, &profile[i]))
			return (0);
	}
	i = -1;
	while (++i < profile[0].data->nb_philo)
	{
		if (!pthread_detach(profile[i].philo))
			return (0);
	}
	return (1);
}

int	main(int ac, char *av[])
{
	t_data		*data;
	// t_profile	*profile;
	// pthread_t	super;
	// int			i;

	data = malloc(sizeof(t_data));
	if (!data || !fill_data(data, ac, av) || !initialisation(data))
		return (0);
	// if (!data || !fill_data(data, ac, av))
	// 	return (0);
	// profile = malloc(data->nb_philo * sizeof(t_profile));
	// if (!profile || distribute(profile, data) || !initialization(profile))
	// 	return (0);
	// printing(&profile[2], C_YELOW, ISTHI);
	// if (!pthread_create(&super, NULL, visor, profile))
	// 	return (0);
	// if (!pthread_join(super, NULL))
	// 	return (0);
	// while (--i >= 0)
	// {
	// 	if (!pthread_mutex_destroy(&profile[i].fork))
	// 		return (0);
	// }
	return (0);
}
