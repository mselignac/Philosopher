/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:47:19 by mseligna          #+#    #+#             */
/*   Updated: 2022/04/05 15:45:24 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	print_act(data, &data->phils[0], R_FORK);
	pthread_mutex_lock(&data->t_meal);
	data->phils[0].last_meal = get_time(data);
	pthread_mutex_unlock(&data->t_meal);
	usleep(data->t_die * 1000);
	print_death(data, 0);
	return (NULL);
}

int	if_dead(t_data *data)
{
	int	i;
	int	last_meal;
	int	meals;

	i = 0;
	while (i < data->nb)
	{
		pthread_mutex_lock(&data->t_meal);
		last_meal = data->phils[i].last_meal;
		pthread_mutex_unlock(&data->t_meal);
		if (last_meal + data->t_die + 1 <= get_time(data))
		{
			pthread_mutex_lock(&data->n_meals);
			meals = data->phils[i].n_meals;
			pthread_mutex_unlock(&data->n_meals);
			if (meals == data->meals)
				return (1);
			pthread_mutex_lock(&data->death);
			print_death(data, data->phils[i].id);
			pthread_mutex_unlock(&data->death);
			return (0);
		}
		i++;
	}
	return (2);
}

int	get_args(t_data *data, char **argv)
{
	init_time(data);
	data->dead = 0;
	data->nb = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		data->meals = ft_atoi(argv[5]);
	else
		data->meals = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * (data->nb + 1));
	if (!data->forks)
		return (0);
	init_mutex(data);
	if (!(init_philo(data)))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!(count_args(argc)))
		return (print_error(0));
	if (!(check_args(argc, argv)))
		return (print_error(1));
	if (!(get_args(&data, argv)))
		return (print_error(2));
	if (data.nb == 1)
		pthread_create(&data.phils[0].th, NULL, &one_philo, &data);
	else
	{
		if (!(launch_cycles(&data)))
			return (print_error(3));
	}
	clear_threads_and_mutex(&data);
	return (0);
}
