/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:32:05 by joafaust          #+#    #+#             */
/*   Updated: 2025/03/19 12:33:31 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	long				last_meal_time;
	int					meals_eaten;
	struct s_simulation	*sim;
}						t_philo;

typedef struct s_simulation
{
	int					num_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat_count;
	int					stop;
	long				start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_lock;
	t_philo				*philos;
}						t_simulation;

long					get_time_in_ms(void);
void					print_action(t_simulation *sim, int id, char *action);
void					*philosopher_routine(void *arg);
void					*monitor_routine(void *arg);
void					start_simulation(t_simulation *sim);
void					init_simulation(t_simulation *sim, int argc,
							char **argv);
void					cleanup_simulation(t_simulation *sim);