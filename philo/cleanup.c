#include "philo.h"

void	cleanup(t_data *data)
{
	unsigned int	i;
	unsigned int	no;

	i = 0;
	no = data->no_of_philosophers;
	while (i < no)
	{
		pthread_mutex_destroy(data->philo[i].fork);
		free(data->philo[i].fork);
		i++;
	}
	free(data->th);
	free(data->philo);
}
