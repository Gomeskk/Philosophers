/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:52:35 by joafaust          #+#    #+#             */
/*   Updated: 2025/03/22 13:55:40 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_atoi(const char *str)
{
	int			i;
	int			neg;
	long int	num;

	i = 0;
	neg = 1;
	num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			neg = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * neg);
}
void	wait_for_turn(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->sim->turn_lock);
		if ((philo->id % 2 == 1 && philo->sim->turn == 1) || (philo->id % 2 == 0
				&& philo->sim->turn == 2))
		{
			pthread_mutex_unlock(&philo->sim->turn_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->sim->turn_lock);
		usleep(100);//avoid busy waiting
	}
}

void	switch_turn(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->turn_lock);
	if (philo->id % 2 == 1)
		philo->sim->turn = 2;//even philosophers eat
	else
		philo->sim->turn = 1;//odd philosophers eat
	pthread_mutex_unlock(&philo->sim->turn_lock);
}
