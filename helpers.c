/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:52:20 by aelaoufi          #+#    #+#             */
/*   Updated: 2022/06/30 23:36:50 by aelaoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		return (-1);
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	if (str[i])
		return (-1);
	return (res);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (!n)
		return (0);
	while (s1[i] && (unsigned char)s1[i] == (unsigned char)s2[i] && (i < n - 1))
		i++;
	return ((unsigned char )s1[i] - (unsigned char )s2[i]);
}

int	check_life(t_philo *vars, int i)
{
	if ((gettime() - vars[i].time) - vars[i].last_meal >= vars->time_to_die)
	{
		pthread_mutex_lock((vars->routine));
		return (0);
	}
	return (1);
}

int	check_args(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
	{
		printf("Wrong number of arguments");
		return (-1);
	}
	while (i < ac)
	{
		if (ft_atoi(av[i]) == -1 || ft_atoi(av[i]) == 0)
		{
			printf("Enter the right arguments");
			return (-1);
		}
		i++;
	}
	return (0);
}
