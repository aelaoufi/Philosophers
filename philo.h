/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:12:07 by aelaoufi          #+#    #+#             */
/*   Updated: 2022/06/27 19:58:16 by aelaoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<stdlib.h>
# include<unistd.h>
# include<stdio.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		th;
	int				id;
	int				ate;
	int				numphilo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long long		time;
	long long		last_meal;
	int				meals_to_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*lock_msg;
	pthread_mutex_t	*routine;

}			t_philo;

int				ft_atoi(char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				number_of_meals(t_philo	*vars);
pthread_mutex_t	*foks(int num);
void			create_philo(pthread_mutex_t *forks, t_philo *vars);
void			*routine(void *vars);
void			print_msg(t_philo *vars, char *msg);
void			initialize(t_philo *vars, char **av);
long long		gettime(void);
void			ft_usleep(int k);
int				check_death(t_philo *vars, int i);
int				check_life(t_philo *vars, int i);
int				check_args(int ac, char **av);

#endif