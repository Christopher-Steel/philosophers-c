/*
** main.c for philosophes in /home/bailly_m/Projects/Tmp/philo_tmp
**
** Made by bailly maxime
** Login   <bailly_m@epitech.net>
**
** Started on  Thu Mar 13 19:29:39 2014 bailly maxime
** Last update Fri Mar 21 14:07:09 2014 steel christopher
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "philo.h"

static void	sig_handler(int);

/*
** This function does nothing.
** It's sole purpose is for there to be a function to handle
** SIGUSR1 so that we can interrupt the wait function on each
** action.
**
** This system is designed to wait up to a maximum time while
** being interruptable if a neighbour philosopher is getting
** very hungry.
*/
void		sig_handler(__attribute__ ((unused))int unused)
{
}

int		main(void)
{
  t_philo	*group;

  if (NB_PHILO < 2)
    {
      fprintf(stderr, "At least 2 philosophers are required.\n");
      return (EXIT_FAILURE);
    }
  if (signal(SIGUSR1, sig_handler) == SIG_ERR)
    {
      perror("signal() failed");
      return (EXIT_FAILURE);
    }
  group = gather_philo();
  set_table(group);
  delete_all(group);
  return (EXIT_SUCCESS);
}
