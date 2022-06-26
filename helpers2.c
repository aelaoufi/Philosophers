/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:28:01 by aelaoufi          #+#    #+#             */
/*   Updated: 2022/06/26 19:06:55 by aelaoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(int k)
{
	long long	res;

	res = gettime() + k;
	while (gettime() < res)
		usleep(300);
}

pthread_mutex_t	*foks(int num)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * num);
	i = 0;
	while (i < num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

int	number_of_meals(t_philo	*vars)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (i < vars->numphilo)
	{
		if (vars[i].ate < vars[i].meals_to_eat)
			return (1);
		i++;
	}
	return (0);
}

int	check_death(t_philo *vars, int i)
{
	if ((gettime() - vars[i].time) - vars[i].last_meal
		>= vars->time_to_die)
	{
		print_msg(vars, "is dead");
		return (0);
	}
	return (1);
}
