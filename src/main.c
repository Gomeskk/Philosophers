/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:31:54 by joafaust          #+#    #+#             */
/*   Updated: 2025/03/25 14:46:13 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	main(int argc, char **argv)
{
	t_simulation	sim;

	if (argc < 5 || argc > 6)
	{
		printf("Usage:\n");
		printf("./philo num_philos time_to_die time_to_eat time_to_sleep");
		printf(" [must_eat]\n");
		return (1);
	}
	printf("%s", SIM_START);
	init_simulation(&sim, argc, argv);
	start_simulation(&sim);
	cleanup_simulation(&sim);
	printf("%s", SIM_END);
	return (0);
}
