/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 17:30:46 by mseligna          #+#    #+#             */
/*   Updated: 2022/04/05 15:44:50 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atoi(const char *str)
{
	int			i;
	long long	nb;
	int			sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '+' && (str[i + 1]) == '-')
		return (0);
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		nb = nb * 10 + (str[i++] - '0');
	nb *= (long long)sign;
	return (nb);
}

int	print_error(int i)
{
	char	*tab[5];
	int		len;
	int		j;

	j = 0;
	len = 0;
	tab[0] = "Error: Wrong number of arguments\n";
	tab[1] = "Error: Arguments value must be between 1 and 2147483647\n";
	tab[2] = "Error: Memory allocation failed\n";
	tab[3] = "Error: Creation of thread failed\n";
	tab[4] = NULL;
	while (tab[i][len])
		len++;
	write(2, &tab[i][j++], len);
	return (1);
}

void	print_act(t_data *data, t_philo *philo, char *str)
{
	int	dead;

	pthread_mutex_lock(&data->death);
	dead = data->dead;
	if (dead == 0)
		printf("%d %d%s", get_time(data), philo->id + 1, str);
	pthread_mutex_unlock(&data->death);
}

void	print_death(t_data *data, int id)
{
	data->dead++;
	if (data->dead == 1)
		printf("%d %d%s", get_time(data), id + 1, DIED);
}

void	set_dead_and_meals(t_data *data, t_philo *philo, int *d, int *m)
{
	pthread_mutex_lock(&data->n_meals);
	*m = philo->n_meals;
	pthread_mutex_unlock(&data->n_meals);
	pthread_mutex_lock(&data->death);
	*d = data->dead;
	pthread_mutex_unlock(&data->death);
}
