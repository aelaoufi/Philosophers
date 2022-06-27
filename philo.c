/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:12:11 by aelaoufi          #+#    #+#             */
/*   Updated: 2022/06/27 20:18:14 by aelaoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize(t_philo *vars, char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		if (av[5])
			vars[i].meals_to_eat = ft_atoi(av[5]);
		else
			vars[i].meals_to_eat = -1;
		vars[i].ate = 0;
		vars[i].last_meal = 0;
		vars[i].numphilo = ft_atoi(av[1]);
		vars[i].time_to_die = ft_atoi(av[2]);
		vars[i].time_to_eat = ft_atoi(av[3]);
		vars[i].time_to_sleep = ft_atoi(av[4]);
		i++;
	}
}

void	print_msg(t_philo *vars, char *msg)
{
	pthread_mutex_lock((vars->lock_msg));
	printf("%lld philo %d %s\n", (gettime() - vars->time), vars->id + 1, msg);
	if (ft_strncmp("is dead", msg, 7) != 0)
		pthread_mutex_unlock((vars->lock_msg));
}

void	*routine(void *vars)
{
	t_philo	*var;
	int		i;

	var = (t_philo *)vars;
	i = 0;
	while (1)
	{
		if (check_life(vars, i) == 0)
			return (0);
		pthread_mutex_lock(&(var->forks[var->id]));
		print_msg(var, "has taken the left fork");
		pthread_mutex_lock(&(var->forks[(var->id + 1) % var->numphilo]));
		print_msg(var, "has taken the right fork");
		print_msg(var, "is eating");
		var->ate += 1;
		var->last_meal = gettime() - var->time;
		ft_usleep(var->time_to_eat);
		pthread_mutex_unlock(&(var->forks[var->id]));
		pthread_mutex_unlock(&(var->forks[(var->id + 1) % var->numphilo]));
		print_msg(var, "is sleeping");
		ft_usleep(var->time_to_sleep);
		print_msg(var, "is thinking");
	}
	return (0);
}

void	create_philo(pthread_mutex_t *forks, t_philo *vars)
{
	int				i;
	long long		time;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*routini;

	i = 0;
	time = gettime();
	lock = malloc(sizeof(pthread_mutex_t));
	routini = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(routini, NULL);
	pthread_mutex_init(lock, NULL);
	while (i < vars->numphilo)
	{
		vars[i].routine = routini;
		vars[i].time = time;
		vars[i].lock_msg = lock;
		vars[i].id = i;
		vars[i].forks = forks;
		pthread_create(&(vars->th), NULL, routine, &vars[i]);
		usleep(100);
		i++;
	}	
}

int	main(int ac, char **av)
{
	pthread_mutex_t	*forks;
	t_philo			*vars;
	int				numphilo;
	int				i;

	if (check_args(ac, av) == -1)
		return (0);
	numphilo = ft_atoi(av[1]);
	vars = malloc(sizeof(t_philo) * numphilo);
	initialize(vars, av);
	forks = foks(numphilo);
	create_philo(forks, vars);
	while (1)
	{
		i = 0;
		while (i < vars->numphilo)
		{
			if (check_death(vars, i) == 0)
				return (0);
			i++;
		}
		if (vars->meals_to_eat != -1 && number_of_meals(vars) == 0)
			return (0);
	}
	return (0);
}
