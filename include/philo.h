/*
** philo.h for philosophes in /home/bailly_m/Projects/Tmp/philo_tmp
**
** Made by bailly maxime
** Login   <bailly_m@epitech.net>
**
** Started on  Thu Mar 13 18:39:59 2014 bailly maxime
** Last update Sun Mar 23 20:17:16 2014 steel christopher
*/

#ifndef			PHILO_H_
# define		PHILO_H_

# include		<pthread.h>

# define		FALSE		0
# define		TRUE		!FALSE

# define		NB_PHILO	7
# define		EAT_TIME	16
# define		THINK_TIME	8
# define		INITIAL_FOOD	10
# define		TICK_DURATION	10000

/*
** 0 = each philosopher prints his new state when he changes it
** 1 = a displayer thread shows ascii representations of kirby
**     philosophers to show their states
*/
# define		DISPLAY_MODE	0

typedef char		t_bool;

typedef enum   		e_state
  {
    REST = 0,
    THINK,
    EAT,
    LEFT
  }			t_state;

typedef			struct s_philo	t_philo;
struct		       	s_philo
{
  unsigned int		id;
  unsigned int		food;
  t_state		state;
  pthread_t		thread;
  pthread_mutex_t	chopstick;
  t_philo		*next;
  t_philo		*prev;
};

void			*display_routine(void *);

t_philo			*gather_philo(void);
t_bool			set_table(t_philo *);

t_philo			*create_philo(int);
t_philo			*add_philo(t_philo *, t_philo *);
t_philo			*remove_philo(t_philo *, int);
void			delete_all(t_philo *);

void			think(t_philo *);
void			eat(t_philo *);
void			rest(t_philo *);

#endif			/* PHILO_H_ */
