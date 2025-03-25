/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:32:05 by joafaust          #+#    #+#             */
/*   Updated: 2025/03/25 16:07:33 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define SIM_START "---------------------------------------\n\
|   \033[32mTIME\033[0m   | \033[32mPHILO\033[0m |      \033[32mEVENT\033[0m       |\n\
---------------------------------------\n"

#define SIM_END "---------------------------------------\n"

#define MSG_FORK "|\033[38;5;208m%10ld\033[0m|%4d   | \
\033[35mhas taken a fork\033[0m |\n"
#define MSG_EATING "|\033[38;5;208m%10ld\033[0m|%4d   |    \
\033[35mis eating\033[0m     |\n"
#define MSG_SLEEPING "|\033[38;5;208m%10ld\033[0m|%4d   |   \
\033[35mis sleeping\033[0m    |\n"
#define MSG_THINKING "|\033[38;5;208m%10ld\033[0m|%4d   |   \
\033[35mis thinking\033[0m    |\n"
#define MSG_DEAD "|\033[38;5;208m%10ld\033[0m|%4d   |       \
\033[31mdied\033[0m       |\n"

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
	pthread_mutex_t		turn_lock;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		death_check;
	int					turn; // 1 for odd philosophers, 2 for even philosophers
}						t_simulation;

// Main routine
void					*philosopher_routine(void *arg);
void					*monitor_routine(void *arg);

// Simulation
void					handle_one_philosopher(t_philo *philo);
void					print_action(t_simulation *sim, int id, char *action);
void					start_simulation(t_simulation *sim);
void					init_simul_mutex_params(t_simulation *sim, int argc,
							char **argv);
void					init_simulation(t_simulation *sim, int argc,
							char **argv);

// Philo actions
void					think(t_philo *philo);
void					eat(t_philo *philo);
void					sleep_philo(t_philo *philo);
int						has_eaten_enough(t_philo *philo);

// Util functions
int						ft_atoi(const char *str);
int						ft_strcmp(const char *str1, const char *str2);
long					get_time_in_ms(void);
void					ft_usleep(long milliseconds);
void					wait_for_turn(t_philo *philo);

// Checker for finalizing simulation
void					check_deaths(t_simulation *sim);
void					check_all_eaten(t_simulation *sim);

// Cleanup
void					cleanup_simulation(t_simulation *sim);
