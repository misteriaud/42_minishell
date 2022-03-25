.DEFAULT_GOAL			:= all
NAME					:= minishell
FILES					:=	main.c \
							memory.c \
							bzero.c \
							t_alloc.c \
							t_node.c \
							env.c

SHELL					:= /bin/zsh
OS						:= $(shell uname -s)

STD						:= -std=c99
#OPT					:= -O3
CFLAGS					:= -Wall -Wextra -Werror -Wpedantic
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
endif
ifeq ($(OS),Linux)
endif

G := \033[3;32m
P := \033[3;35m
R := \033[m

all:					$(NAME)

$(NAME):				$(OBJ)
						$(CC) $^ -o $@

#$(OBJDIR)/%.o:			$(SRCDIR)/%.c | $(OBJDIR) $(DEPDIR)
-include $(DEP)
$(OBJDIR)/%.o:			%.c | $(OBJDIR) $(DEPDIR)
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
