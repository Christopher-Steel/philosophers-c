/*
** philo_creation.c for  in /home/bailly_m/Projects/Tmp/philo_tmp
**
** Made by bailly maxime
** Login   <bailly_m@epitech.net>
**
** Started on  Sat Mar 15 11:25:47 2014 bailly maxime
** Last update Sun Mar 23 20:12:21 2014 steel christopher
*/

#include	<stdlib.h>
#include	<stdio.h>
#include	"philo.h"

t_philo		*create_philo(int id)
{
  t_philo	*new_philo;

  if (!(new_philo = malloc(sizeof(*new_philo))))
    return (NULL);
  if (pthread_mutex_init(&new_philo->chopstick, NULL))
    return (NULL);
  new_philo->id = id;
  new_philo->food = INITIAL_FOOD;
  new_philo->state = REST;
  new_philo->next = new_philo;
  new_philo->prev = new_philo;
  return (new_philo);
}

t_philo		*add_philo(t_philo *list, t_philo *philo)
{
  t_philo	*cursor;

  if (!philo)
    return (list);
  if (!list)
    return (philo);
  cursor = list;
  while (cursor->next && cursor->next != list)
    cursor = cursor->next;
  philo->next = list;
  philo->prev = cursor;
  cursor->next = philo;
  list->prev = philo;
  return (list);
}

t_philo		*remove_philo(t_philo *list, int ndx)
{
  int		i;
  t_philo	*cursor;
  t_philo	*next;

  if (!list)
    return (list);
  cursor = list;
  i = 0;
  while (cursor->next && cursor->next != list && i < ndx)
    {
      cursor = cursor->next;
      ++i;
    }
  if (i != ndx)
    return (list);
  next = cursor->next;
  next->prev = cursor->prev;
  cursor->prev->next = next;
  free(cursor);
  if (!i)
    return (next);
  return (list);
}

void		delete_all(t_philo *list)
{
  t_philo	*cursor;
  t_philo	*tmp;

  if (!list)
    return ;
  cursor = list;
  if (cursor->prev)
    cursor->prev->next = NULL;
  while (cursor)
    {
      tmp = cursor;
      cursor = tmp->next;
      free(tmp);
    }
}
