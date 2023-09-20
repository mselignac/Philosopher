/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 01:32:00 by mseligna          #+#    #+#             */
/*   Updated: 2022/04/05 16:23:08 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <pthread.h>

# define R_FORK " has taken a fork on his right 🍴\n"
# define L_FORK " has taken a fork on his left 🍴\n"
# define EAT " is eating 🍕\n"
# define SLEEP " is sleeping 🐑\n"
# define THINK " is thinking 🤔\n"
# define DIED " died 💀\n"
# define INT_MAX 2147483647

typedef struct s_philo
{
	int			id;
	int			last_meal;
	int			n_meals;
	int			r_fork;
	int			l_fork;
	pthread_t	th;
	void		*dat;
}			t_philo;

typedef struct s_data
{
	t_philo				*phils;
	int					nb;
	long int			t_die;
	int					t_eat;
	int					t_sleep;
	int					meals;
	int					dead;
	pthread_mutex_t		*forks;
	pthread_mutex_t		t_meal;
	pthread_mutex_t		n_meals;
	pthread_mutex_t		death;
	pthread_mutex_t		timer;
	struct timeval		time;
	long long unsigned	t_start;

}				t_data;

int			count_args(int argc);
int			check_args(int argc, char **argv);
long long	ft_atoi(const char *str);
void		init_time(t_data *data);
void		init_mutex(t_data *data);
int			init_philo(t_data *data);
int			get_time(t_data *data);
int			print_error(int i);
void		print_act(t_data *data, t_philo *philo, char *str);
void		print_death(t_data *data, int id);
int			launch_cycles(t_data *data);
void		set_dead_and_meals(t_data *data, t_philo *philo, int *d, int *m);
void		clear_threads_and_mutex(t_data *data);
int			if_dead(t_data *data);

#endif