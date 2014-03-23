##
## Makefile for libc in /home/bailly_m/Projects/Tmp/libc_tmp
##
## Made by bailly maxime
## Login   <bailly_m@epitech.net>
##
## Started on  Fri Feb 28 11:44:48 2014 bailly maxime
## Last update Fri Mar 21 18:56:32 2014 steel christopher
##


CFLAGS		= 	-Wall -Werror -Wextra -I$(INCLDIR)
LDFLAGS		= 	-lpthread

MKDIR		= 	mkdir -p
RM		= 	rm -rf

SRCDIR		= 	src
OBJDIR		= 	obj
INCLDIR		= 	include

SRC		=	main.c \
			philo_alloc.c \
			philo_init.c \
			philo_states.c \
			displayer.c

OBJ		=	$(addprefix $(OBJDIR)/, $(notdir $(SRC:%.c=%.o)))

ifeq ($(DEBUG), true)
CFLAGS		+=	-g3
endif

EXEC		=	philo

$(EXEC)		:		$(OBJ)
			$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS) $(CFLAGS)

all		:	$(EXEC)

$(OBJDIR)/%.o	:	$(SRCDIR)/%.c
			@if [ ! -d "./$(OBJDIR)" ]; then $(MKDIR) $(OBJDIR); fi
			$(CC) $(CFLAGS) -o $@ -c $<

clean		:
			$(RM) $(OBJ)

fclean		:	clean
			$(RM) $(EXEC)

dclean		:
			$(RM) $(EXEC) $(OBJDIR)

re		:	fclean all

prepare		:
			@if [ ! -d "./$(SRCDIR)" ]; then $(MKDIR) $(SRCDIR); fi
			@if [ ! -d "./$(INCLDIR)" ]; then $(MKDIR) $(INCLDIR); fi

.PHONY		:	all clean fclean dclean re prepare
