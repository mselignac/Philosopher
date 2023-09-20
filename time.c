/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 23:45:24 by mseligna          #+#    #+#             */
/*   Updated: 2022/04/05 16:25:25 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_time(t_data *data)
{
	gettimeofday(&data->time, NULL);
	data->t_start = (data->time.tv_sec * 1000) + (data->time.tv_usec / 1000);
}

int	get_time(t_data *data)
{
	long long unsigned	time;

	pthread_mutex_lock(&data->timer);
	gettimeofday(&data->time, NULL);
	time = ((data->time.tv_sec * 1000) + (data->time.tv_usec / 1000));
	time -= data->t_start;
	pthread_mutex_unlock(&data->timer);
	return (time);
}
