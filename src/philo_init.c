/*
** philo_init.c for philosophes in /home/steel_c/Code/philosophes/philo_tmp/src
**
** Made by steel christopher
** Login   <steel_c@epitech.net>
**
** Started on  Fri Mar 21 13:35:40 2014 steel christopher
** Last update Sun Mar 23 20:09:59 2014 steel christopher
*/

#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>

#include "philo.h"

static void	*philo_routine(void *);
static t_bool	wait_for_threads_join(t_philo *, pthread_t *);

void		*philo_routine(void *data)
{
  t_philo	*philo;
  static void	(*fn[2])(t_philo *) =
    {
      &think,
      &eat
    };

  philo = (t_philo *)data;
  while (philo->food)
    {
      fn[philo->state](philo);
      usleep(TICK_DURATION);
    }
  if (DISPLAY_MODE == 0)
    printf("Philosopher [%d] left the table.\n", philo->id);
  philo->state = LEFT;
  pthread_exit(NULL);
  return (NULL);
}

t_bool		set_table(t_philo *group)
{
  t_philo	*cur;
  pthread_t	disp;
  int		i;

  cur = group;
  i = 0;
  while (cur && i < NB_PHILO)
    {
      if (pthread_create(&cur->thread, NULL, &philo_routine, (void *)cur) != 0)
	{
	  perror("pthread_create() failed for philosopher thread");
	  cur = remove_philo(cur, 0);
	}
      else
	cur = cur->next;
      ++i;
    }
  if (DISPLAY_MODE == 1 &&
      pthread_create(&disp, NULL, &display_routine, (void *)group) != 0)
    {
      perror("pthread_create() failed for displayer thread");
      return (wait_for_threads_join(group, NULL));
    }
  return (wait_for_threads_join(group, (DISPLAY_MODE == 1 ? &disp : NULL)));
}

t_bool		wait_for_threads_join(t_philo *group, pthread_t *disp)
{
  t_philo	*cursor;
  t_bool	success;
  int		i;

  cursor = group;
  success = TRUE;
  i = 0;
  while (cursor && i < NB_PHILO)
    {
      if (pthread_join(cursor->thread, NULL) != 0)
	{
	  fprintf(stderr, "failed to join with thread %d : ", i);
	  perror("pthread_join() failed");
	  success = FALSE;
	}
      cursor = cursor->next;
      ++i;
    }
  if (disp && pthread_join(*disp, NULL) != 0)
    {
      fprintf(stderr, "failed to join with displayer thread : ");
      perror("pthread_join() failed");
      success = FALSE;
    }
  return (success);
}

t_philo		*gather_philo(void)
{
  t_philo	*prev_table;
  t_philo	*table;
  int		i;

  prev_table = NULL;
  table = NULL;
  i = 0;
  while (i < NB_PHILO)
    {
      if ((table = add_philo(table, create_philo(i + 1))) == NULL)
	{
	  delete_all(prev_table);
	  prev_table = NULL;
	  break ;
	}
      prev_table = table;
      ++i;
    }
  return (prev_table);
}
