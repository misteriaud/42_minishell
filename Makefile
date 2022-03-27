.DEFAULT_GOAL			:= all
NAME					:= minishell

FILES					:=	main.c \
							memory.c \
							bzero.c \
							t_alloc.c \
							t_node.c \
							parser.c \
							parser_utils.c \
							history.c \
							get_file.c \
							env.c \
							raw.c

SHELL					:= /bin/zsh
OS						:= $(shell uname -s)

STD						:= -std=c99
#OPT					:= -O3
CFLAGS					:= -Wall -Wextra -Werror -Wpedantic -g
DFLAGS					:= -MMD -MF

REMOVE					:= rm -rvf
MKDIR					:= mkdir -p

SRCDIR					:= src
INCDIR					:= inc
OBJDIR					:= obj
DEPDIR					:= dep

SDIR						:= $(shell find $(SRCDIR) -type d)

vpath %.c $(foreach dir, $(SDIR), $(dir):)

OBJ						:= $(addprefix $(OBJDIR)/, $(FILES:%.c=%.o))
#SRC						:= $(addprefix $(SRCDIR)/, $(FILES))
#OBJ						:= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
DEP						:= $(patsubst $(OBJDIR)/%.o, $(DEPDIR)/%.d, $(OBJ))

ifeq ($(OS),Darwin)
	CC = clang
endif
ifeq ($(OS),Linux)
	CC = gcc
endif

G := \033[3;32m
P := \033[3;35m
R := \033[m

all:					$(NAME) Makefile

$(NAME):				$(OBJ) | Makefile
						$(CC) $^ -o $@

#$(OBJDIR)/%.o:			$(SRCDIR)/%.c | $(OBJDIR) $(DEPDIR)
-include $(DEP)
$(OBJDIR)/%.o:			%.c | $(OBJDIR) $(DEPDIR) Makefile
						@printf "$(P)"
						$(CC) $(STD) $(OPT) $(CFLAGS) -I$(INCDIR) $(DFLAGS) $(DEPDIR)/$*.d -c $< -o $@
						@printf "$(R)"

$(OBJDIR) $(DEPDIR):	;
						@$(MKDIR) $@

clean:					;
						@$(REMOVE) $(OBJDIR) $(DEPDIR)

fclean:					clean
						@$(REMOVE) $(NAME)

re:						fclean all

.PHONY:					all clean fclean re
