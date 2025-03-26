/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:31:54 by joafaust          #+#    #+#             */
/*   Updated: 2025/03/26 14:27:37 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	numeric(char **argv, int i, int j)
{
	while (argv[j])
	{
		while (argv[j][i])
		{
			if (argv[j][i] < '0' || argv[j][i] > '9' || ft_strlen(argv[j]) > 10)
				return (0);
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}

static int	parse_args(int argc, char **argv, t_simulation *sim)
{
	if ((argc == 5 || argc == 6) && numeric(argv, 0, 1))
	{
		sim->num_philos = ft_atoi(argv[1]);
		sim->time_to_die = ft_atoi(argv[2]);
		sim->time_to_eat = ft_atoi(argv[3]);
		sim->time_to_sleep = ft_atoi(argv[4]);
		sim->must_eat_count = -1;
		if (argc == 6)
			sim->must_eat_count = ft_atoi(argv[5]);
		if (sim->num_philos <= 0 || sim->time_to_die <= 0
			|| sim->time_to_eat <= 0 || sim->time_to_sleep <= 0
			|| (sim->must_eat_count != -1 && sim->must_eat_count <= 0))
			return (0);
		return (1);
	}
	return (0);
}

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
	if (!parse_args(argc, argv, &sim))
	{
		printf("Invalid arguments. Please check the input values.\n");
		return (1);
	}
	init_simulation(&sim, argc, argv);
	printf("%s", SIM_START);
	start_simulation(&sim);
	cleanup_simulation(&sim);
	printf("%s", SIM_END);
	return (0);
}
