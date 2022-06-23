/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:12:07 by aelaoufi          #+#    #+#             */
/*   Updated: 2022/06/17 15:27:19 by aelaoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include<stdlib.h>
# include<unistd.h>
# include<stdio.h>
# include <pthread.h>
#include <time.h>
#include <sys/time.h>

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
	int				dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*lock_msg;
	
}              t_philo;

typedef struct s_watch
{
	int	death;
}				t_watch;



int	ft_atoi(char *str);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

#endif