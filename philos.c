/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:13:21 by mseligna          #+#    #+#             */
/*   Updated: 2022/04/04 20:18:53 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	hold_on(t_data *data, int time)
{
	int	start;
	int	now;
	int	dead;

	start = get_time(data);
	now = start;
	pthread_mutex_lock(&data->death);
	dead = data->dead;
	pthread_mutex_unlock(&data->death);
	while (now < (start + time) && dead == 0)
	{
		if (!if_dead(data))
			return ;
		usleep(50);
		now = get_time(data);
	}
}

void	even_cycle(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->forks[philo->r_fork]);
	print_act(data, philo, R_FORK);
	pthread_mutex_lock(&data->forks[philo->l_fork]);
	print_act(data, philo, L_FORK);
	pthread_mutex_lock(&data->t_meal);
	philo->last_meal = get_time(data);
	pthread_mutex_unlock(&data->t_meal);
	print_act(data, philo, EAT);
	pthread_mutex_lock(&data->n_meals);
	philo->n_meals++;
	pthread_mutex_unlock(&data->n_meals);
	hold_on(data, data->t_eat);
	pthread_mutex_unlock(&data->forks[philo->r_fork]);
	pthread_mutex_unlock(&data->forks[philo->l_fork]);
	print_act(data, philo, SLEEP);
	hold_on(data, data->t_sleep);
	print_act(data, philo, THINK);
}

void	odd_cycle(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->forks[philo->l_fork]);
	print_act(data, philo, L_FORK);
	pthread_mutex_lock(&data->forks[philo->r_fork]);
	print_act(data, philo, R_FORK);
	pthread_mutex_lock(&data->t_meal);
	philo->last_meal = get_time(data);
	pthread_mutex_unlock(&data->t_meal);
	print_act(data, philo, EAT);
	pthread_mutex_lock(&data->n_meals);
	philo->n_meals++;
	pthread_mutex_unlock(&data->n_meals);
	hold_on(data, data->t_eat);
	pthread_mutex_unlock(&data->forks[philo->l_fork]);
	pthread_mutex_unlock(&data->forks[philo->r_fork]);
	print_act(data, philo, SLEEP);
	hold_on(data, data->t_sleep);
	print_act(data, philo, THINK);
}

void	*routine(void *arg)
{
	t_data	*data;
	t_philo	*philo;
	int		meals;
	int		dead;

	dead = 0;
	meals = 0;
	philo = (t_philo *)arg;
	data = (t_data *)philo->dat;
	set_dead_and_meals(data, philo, &dead, &meals);
	while ((data->meals < 0 || meals < data->meals) && dead == 0)
	{
		if (philo->id % 2 == 0)
			even_cycle(philo, data);
		else
			odd_cycle(philo, data);
		usleep(100);
		set_dead_and_meals(data, philo, &dead, &meals);
		if (!(if_dead(data)))
			return (NULL);
	}
	return (NULL);
}

int	launch_cycles(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb)
	{
		if (!if_dead(data))
			return (1);
		if (pthread_create(&data->phils[i].th, NULL, &routine, &data->phils[i]))
			return (0);
		i += 2;
		if (i >= data->nb && i % 2 == 0)
			i = 1;
	}
	return (1);
}
