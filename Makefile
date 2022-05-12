.DEFAULT_GOAL			:= all
NAME					:= minishell

FILES					:=	main.c \
							wildcard.c \
							memory.c bzero.c t_alloc.c t_node.c \
							lexer.c parser.c parser_utils.c split_cmd.c \
							prompt_heredoc.c prompt.c \
							init_env.c get_variable.c drop_variables.c print_env.c paths.c package_env.c \
							run_process.c redirect_in.c redirect_out.c exit_status.c \
							split_array.c split_lst.c size.c compare.c merge.c error.c secure_atoi.c \
							is_char.c is_char_2.c is_set.c t_str.c fill.c is_dir.c is_reg.c close_fds.c is_empty_str.c \
							init_built_in.c search_built_in.c echo.c cd.c pwd.c unset.c export.c exit.c env.c \
							status.c

SHELL					:= /bin/zsh
OS						:= $(shell uname -s)

CC						:= gcc
STD						:= -std=c99
CFLAGS					:= -Wall -Wextra -Werror -Wpedantic -g -D_POSIX_C_SOURCE
DFLAGS					:= -MMD -MF

REMOVE					:= rm -rvf
MKDIR					:= mkdir -p

SRCDIR					:= src
INCDIR					:= inc
OBJDIR					:= obj
DEPDIR					:= dep

SDIR					:= $(shell find $(SRCDIR) -type d)

vpath %.c $(foreach dir, $(SDIR), $(dir):)

OBJ						:= $(addprefix $(OBJDIR)/, $(FILES:%.c=%.o))
DEP						:= $(patsubst $(OBJDIR)/%.o, $(DEPDIR)/%.d, $(OBJ))

G := \033[3;32m
P := \033[3;35m
R := \033[m


all:
						@if ! command -v lolcat &> /dev/null; then \
							$(MAKE) --no-print-directory $(NAME); \
						else \
							$(MAKE) --no-print-directory $(NAME) | lolcat --spread=100 --seed=10 --freq=0.02; \
						fi

$(NAME):				$(OBJ) | Makefile
						$(CC) $^ -lreadline -o $@

-include $(DEP)
$(OBJDIR)/%.o:			%.c | $(OBJDIR) $(DEPDIR) Makefile
						@printf "$(P)"
						$(CC) $(STD) $(OPT) $(CFLAGS) -I$(INCDIR) $(DFLAGS) $(DEPDIR)/$*.d -c $< -o $@
						@printf "$(R)"

$(OBJDIR) $(DEPDIR):	;
						@$(MKDIR) $@

clean:					;
						@$(REMOVE) $(OBJDIR) $(DEPDIR) ignoreleak

fclean:					clean
						@$(REMOVE) $(NAME)

re:						fclean all

ignoreleak:
						@echo -e "{\nleak readline\nMemcheck:Leak\n...\nfun:readline\n}\n{\nleak add_history\nMemcheck:Leak\n...\nfun:add_history\n}" > $@

leaks:					$(NAME) ignoreleak
						@valgrind \
						--suppressions=ignoreleak \
						--leak-check=full \
						--show-leak-kinds=all \
						--track-origins=yes \
						--track-fds=yes \
						./$(NAME)

.PHONY:					all clean fclean re leaks
