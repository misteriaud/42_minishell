.DEFAULT_GOAL			:= all
NAME					:= minishell

FILES					:=	main.c \
							memory.c bzero.c t_alloc.c t_node.c \
							lexer.c parser.c parser_utils.c \
							prompt_heredoc.c \
							history.c \
							get_file.c \
							prompt.c \
							init_env.c get_variable.c drop_variables.c print_env.c paths.c package_env.c \
							raw.c \
							run_process.c redirect_in.c redirect_out.c \
							split_array.c split_lst.c size.c compare.c merge.c error.c secure_atoi.c is_char.c is_set.c t_str.c fill.c \
							init_built_in.c search_built_in.c echo.c cd.c pwd.c unset.c export.c exit.c env.c

SHELL					:= /bin/zsh
OS						:= $(shell uname -s)

STD						:= -std=c99
#OPT					:= -O3
CFLAGS					:= -Wall -Wextra -Werror -Wpedantic -lreadline -g -D_POSIX_C_SOURCE
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
						$(CC) $^ -lreadline -o $@

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
