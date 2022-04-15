/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 00:15:20 by anajmi            #+#    #+#             */
/*   Updated: 2022/04/15 00:15:49 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printing(t_profile *profile, char *color, char *str)
{
	pthread_mutex_lock(profile->mutex_print);
	printf("%s%zu %zu %s\n\033[0m", color, timing(), profile->id, str);
	if (profile->is_die)
		return ;
	pthread_mutex_unlock(profile->mutex_print);
}

void	*visor(void *param)
{
	t_profile	*profile;
	size_t		i;

	profile = (t_profile *)param;
	while (1)
	{
		i = 0;
		while (i < profile[0].data->nb_philo)
		{
			if (timing() - profile[i].last_eat >= profile[0].data->tdie
				&& -1 <= profile[i].nbr_to_eat
				&& profile[i].nbr_to_eat < profile->data->nbr_to_eat
				&& !profile->is_eat)
			{
				profile[i].is_die = 1;
				printing(&profile[i], C_RED, DIE);
				return (0);
			}
			if (profile[i].nbr_to_eat > profile->data->nbr_to_eat)
				return (0);
			i++;
		}
	}
	return (0);
}

void	*race(void	*param)
{
	t_profile	*profile;

	profile = (t_profile *)param;
	if (profile->id % 2 == 0)
		msleep(10);
	while (1)
	{
		pthread_mutex_lock(profile->rfork);
		printing(profile, C_CYAN, TFORK);
		pthread_mutex_lock(profile->lfork);
		printing(profile, C_CYAN, TFORK);
		printing(profile, C_BLUE, ISEAT);
		profile->is_eat = 1;
		msleep(profile->data->teat);
		profile->last_eat = timing();
		profile->is_eat = 0;
		pthread_mutex_unlock(profile->rfork);
		pthread_mutex_unlock(profile->lfork);
		if (-1 < profile->nbr_to_eat)
			profile->nbr_to_eat++;
		printing(profile, C_GREEN, ISLEP);
		msleep(profile->data->tsleep);
		printing(profile, C_YELOW, ISTHI);
	}
	return (0);
}
