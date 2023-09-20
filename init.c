/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 20:55:41 by mseligna          #+#    #+#             */
/*   Updated: 2022/04/05 16:24:11 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	count_args(int argc)
{
	return (argc == 5 || argc == 6);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		if ((ft_atoi(argv[i]) <= 0) || (ft_atoi(argv[i]) > INT_MAX))
			return (0);
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb)
		pthread_mutex_init(&data->forks[i++], NULL);
	pthread_mutex_init(&data->death, NULL);
	pthread_mutex_init(&data->n_meals, NULL);
	pthread_mutex_init(&data->t_meal, NULL);
	pthread_mutex_init(&data->timer, NULL);
}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->phils = malloc(sizeof(t_philo) * (data->nb + 1));
	if (!data->phils)
		return (0);
	while (i < data->nb)
	{
		data->phils[i].dat = data;
		data->phils[i].id = i;
		data->phils[i].last_meal = 0;
		data->phils[i].n_meals = 0;
		data->phils[i].l_fork = i;
		i++;
		if (i != data->nb)
			data->phils[i - 1].r_fork = i;
		else
			data->phils[i - 1].r_fork = 0;
	}
	return (1);
}

void	clear_threads_and_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb)
		pthread_join(data->phils[i++].th, NULL);
	i = 0;
	while (i < data->nb)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->phils);
	free(data->forks);
	pthread_mutex_destroy(&data->death);
	pthread_mutex_destroy(&data->n_meals);
	pthread_mutex_destroy(&data->t_meal);
	pthread_mutex_destroy(&data->timer);
}
