/*
** displayer.c for philosophes in /home/steel_c/Code/philosophes/philo_tmp/src
**
** Made by steel christopher
** Login   <steel_c@epitech.net>
**
** Started on  Fri Mar 21 11:49:32 2014 steel christopher
** Last update Sun Mar 23 20:11:22 2014 steel christopher
*/

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#include "philo.h"

static void	display_philo(t_philo *philo, t_bool first, t_bool last)
{
  static char	sprites[4][8] =
    {
      "<(-_-)>\0",
      "<('-')>\0",
      "<(^O^)>\0",
      "_______\0"
    };
  char		*spacing[2];

  spacing[0] = (first ? "\r" : " ");
  spacing[1] = (last ? " " : " ");
  printf("%s%s%s", spacing[0], &sprites[(int)philo->state][0], spacing[1]);
}

static t_bool	display_group(t_philo *group)
{
  t_bool	are_active_members;
  unsigned int	i;

  are_active_members = FALSE;
  i = 0;
  while (group && i < NB_PHILO)
    {
      if (group->state != LEFT)
	are_active_members = TRUE;
      display_philo(group, (!i ? TRUE : FALSE),
		    (i + 1 < NB_PHILO ? TRUE : FALSE));
      group = group->next;
      ++i;
    }
  return (are_active_members);
}

void		*display_routine(void *data)
{
  t_philo	*group;
  t_bool	are_active_members;

  group = (t_philo *)data;
  are_active_members = TRUE;
  while (are_active_members)
    {
      are_active_members = display_group(group);
      usleep(TICK_DURATION / 100);
    }
  printf("\n");
  pthread_exit(NULL);
  return (NULL);
}
