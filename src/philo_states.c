/*
** philo_states.c for philosophes in /home/bailly_m/Projects/Tmp/philo_tmp
**
** Made by bailly maxime
** Login   <bailly_m@epitech.net>
**
** Started on  Sat Mar 15 17:07:15 2014 bailly maxime
** Last update Sun Mar 23 20:00:37 2014 steel christopher
*/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include "philo.h"

void			think(t_philo *philo)
{
  if (philo->id % 2)
    pthread_mutex_lock(&philo->chopstick);
  else
    pthread_mutex_lock(&philo->next->chopstick);
  philo->state = THINK;
  if (DISPLAY_MODE != 1)
    printf("[%d]: thinking...\n", philo->id);
  usleep(THINK_TIME * TICK_DURATION);
}

void			eat(t_philo *philo)
{
  pthread_t		*thread;
  pthread_mutex_t	*chopstick;
  int			id;

  thread = (philo->id % 2 ? &philo->next->thread : &philo->prev->thread);
  chopstick = (philo->id % 2 ? &philo->next->chopstick : &philo->chopstick);
  id = (philo->id % 2 ? philo->next->id : philo->prev->id);
  if (pthread_mutex_trylock(chopstick))
    {
      if (DISPLAY_MODE != 1)
	printf("[%d]: asking %d for his chopstick\n", philo->id, id);
      pthread_kill(*thread, SIGUSR1);
      pthread_mutex_unlock(chopstick);
      pthread_mutex_lock(chopstick);
    }
  if (DISPLAY_MODE != 1)
    printf("[%d]: eating...\n", philo->id);
  --philo->food;
  philo->state = EAT;
  usleep(EAT_TIME * TICK_DURATION);
  pthread_mutex_unlock(&philo->chopstick);
  pthread_mutex_unlock(&philo->next->chopstick);
  if (DISPLAY_MODE != 1)
    printf("[%d]: resting...\n", philo->id);
  philo->state = REST;
}

