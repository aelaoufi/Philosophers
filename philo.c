/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:12:11 by aelaoufi          #+#    #+#             */
/*   Updated: 2022/06/13 19:01:14 by aelaoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long gettime()
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(int k)
{
	long long res;
	res = gettime() + k;
	while (gettime() < res)
		usleep(50);
}

void	initialize(t_philo *vars, char **av)
{
	int i;

	i = 0;
	while(i < ft_atoi(av[1]))
	{
		if (av[5])
			vars[i].meals_to_eat = ft_atoi(av[5]);
		else
			vars[i].meals_to_eat = -1;
		vars[i].time = gettime();
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
	// if (ft_strncmp("is sleeping", msg, 11) == 0)
	// {
	// 	vars[vars->id].last_meal = gettime() - vars->time;
	// 	// printf("philo no : %d last meal : %lld\n", vars->id + 1, vars[vars->id].last_meal);
	// }
	
	printf("%lld philo %d %s\n", (gettime() - vars->time), vars->id + 1, msg);
	if (ft_strncmp("is dead", msg, 7) != 0)
		pthread_mutex_unlock((vars->lock_msg));
}

void	*routine(void *vars)
{
	t_philo	*var;
	int l;
	int r;
	

	var = (t_philo *)vars;
	l = var->id;
	r = (var->id + 1) % var->numphilo;
	// if (var->id % 2 == 0)
	// 	usleep(100);
	while (1)
	{
		pthread_mutex_lock(&(var->forks[l]));
		print_msg(var,"has taken the left fork");
		pthread_mutex_lock(&(var->forks[r]));
		print_msg(var,"has taken the right fork");
		//printf("gettime %lld\n", gettime());
		print_msg(var,"is eating");
		var->ate += 1;
		var->last_meal = gettime() - var->time;
		ft_usleep(var->time_to_eat);
		pthread_mutex_unlock(&(var->forks[var->id]));
		pthread_mutex_unlock(&(var->forks[(var->id + 1) % var->numphilo]));
		print_msg(var,"is sleeping");
		ft_usleep(var->time_to_sleep);
		print_msg(var,"is thinking");
	}
	return (0);
}

void	create_philo(pthread_mutex_t *forks, t_philo *vars)
{
	int	i;
	pthread_mutex_t lock;
	
	i = 0;
	pthread_mutex_init(&lock, NULL);
	while (i < vars->numphilo)
	{
		vars[i].lock_msg = &lock;
		vars[i].id = i;
		vars[i].forks = forks;
		pthread_create(&(vars->th), NULL, routine, &vars[i]);
		usleep(100);
		i++;
	}
	// i = 0;
	// while (i < vars->numphilo)
	// {
	// 	pthread_join(vars->th, NULL);
	// 	usleep(200);
	// 	i++;
	// }
	
	
}
pthread_mutex_t *foks(int num)
{
	pthread_mutex_t *forks;
	int i;
	
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
	int i;
	int num;

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

int	main(int ac, char **av)
{
	pthread_mutex_t	*forks;
	t_philo			*vars;
	int				numphilo;

	numphilo =  ft_atoi(av[1]);
	vars = malloc(sizeof(t_philo) * numphilo);
	initialize(vars, av);
	forks = foks(numphilo);
	create_philo(forks, vars);
	while (1)
	{
		int i = 0;
		while (i < vars->numphilo)
		{
			if ((gettime() - vars[i].time) - vars[i].last_meal >= vars->time_to_die)
			{
				print_msg(vars,"is dead");
				return (0);
			}
			i++;
		}
		if (vars->meals_to_eat != -1 && number_of_meals(vars) == 0)
			exit(0);
	}
	//n7sb period li ma9sach fiha - period to death - chi wahed mat lock msg - (ch7al mn mrra kna optional)
	return (0);
}


