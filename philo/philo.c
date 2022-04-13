/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:33:35 by anajmi            #+#    #+#             */
/*   Updated: 2022/04/13 03:46:02 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

/*
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
*/

/* size_t	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

size_t	debug()
{
	static size_t	t;

	if (!t)
		t = get_time();
	return (get_time() - t);
}

void	take_fork(t_vars *pt)
{
	printf("%d ms philo[%d] has taken a fork", debug(), debug());
} */

int	remplir_data(t_data *data, int ac, char *av[])
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
	int			id;
	t_profile 	*profile;

	profile = param;
	id = profile->id;
	printf("hello id = %d\n", id);
	return 0;
}


int	initialisation(t_data *data)
{
	t_profile	*profile;
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
	}

	while (++i < data->nb_philo)
		pthread_mutex_init(&profile[i].fork, NULL);
	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_create(&profile[i].philo, NULL, race, &profile[i]);
		usleep(50);
	}
	i = -1;
	while (++i < data->nb_philo)
		pthread_detach(profile[i].philo);
	while (--i >= 0)
		pthread_mutex_destroy(&profile[i].fork);
	return (1);
}

int	main(int ac, char *av[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data || !remplir_data(data, ac, av))
		return (0);
	initialisation(data);
	return (0);
}
