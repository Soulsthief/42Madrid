/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 08:07:13 by dmontoro          #+#    #+#             */
/*   Updated: 2023/08/10 10:48:54 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left);
	if (*philo->fork[1] == 0)
	{
		*philo->fork[1] = 1;
		pthread_mutex_unlock(&philo->left);
		pthread_mutex_lock(philo->right);
		if (*philo->fork[0] == 0)
		{
			*philo->fork[0] = 1;
			pthread_mutex_unlock(philo->right);
			printf("%ld : Philo %d has taken a fork\n", ft_time() - philo->t_start, philo->id);
			printf("%ld : Philo %d has taken a fork\n", ft_time() - philo->t_start, philo->id);
			return (1);
		}
		pthread_mutex_unlock(philo->right);
		pthread_mutex_lock(&philo->left);
		*philo->fork[1] = 0;
		pthread_mutex_unlock(&philo->left);
		return (0);
	}
	pthread_mutex_unlock(&philo->left);
	return (0);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left);
	*philo->fork[0] = 0;
	pthread_mutex_unlock(&philo->left);
	pthread_mutex_lock(philo->right);
	*philo->fork[1] = 0;
	pthread_mutex_unlock(philo->right);
}

//returns 1 if it has eaten n times
int	eat(t_philo *philo)
{
	philo->eaten++;
	pthread_mutex_lock(&philo->data_mutex);
	philo->last_eat = ft_time();
	pthread_mutex_unlock(&philo->data_mutex);
	print_and_wait('e', philo->id, philo->t_start, philo->t_eat);
	if (philo->eaten == philo->n_eat)
	{
		pthread_mutex_lock(philo->full_mutex);
		*philo->full = *philo->full + 1;
		pthread_mutex_unlock(philo->full_mutex);
		return 1;
	}
	return 0;
}

void	think(t_philo *philo)
{
	if(check_dead(philo))
		return ;
	print_and_wait('t', philo->id, philo->t_start, 0);
}

void	sleep_(t_philo *philo)
{
	if(check_dead(philo))
		return ;
	print_and_wait('s', philo->id, philo->t_start, philo->t_sleep);
}
