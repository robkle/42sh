NAME = 42sh

FT_PRINTF_PATH = ft_printf/

LIBFT_PATH = libft/

FLAGS = -Wall -Werror -Wextra -g #add -g for visual debugger

INC = -I ./includes/ -I ./includes/line_edition \
		-I ./includes/line_edition/auto_completion \
		-I ./libft/includes -I ./ft_printf//includes

SRCS = src/main.c \
src/lexer/lexical_analysis.c \
src/lexer/get_token_info.c \
src/lexer/get_the_last_token.c \
src/lexer/lexer_helper1.c \
src/lexer/lexer_helper2.c \
src/lexer/interpret.c \
src/lexer/jump_single_or_double_quote.c \
src/lexer/create_non_quoted_string.c \
src/lexer/check_syntax.c \
src/lexer/clear_token.c \
src/parser/syntax_analysis.c \
src/parser/AST/and_or.c \
src/parser/AST/ast_tool.c \
src/parser/AST/cmd_name.c \
src/parser/AST/cmd_suffix.c \
src/parser/AST/word.c \
src/parser/AST/command.c \
src/parser/AST/complete_command.c \
src/parser/AST/file_name.c \
src/parser/AST/io_files.c \
src/parser/AST/io_here.c \
src/parser/AST/io_file_branch.c \
src/parser/AST/io_redirect.c \
src/parser/AST/list.c \
src/parser/AST/pipe_sequence.c \
src/parser/AST/pipeline.c \
src/parser/AST/simple_command.c \
src/signal/sig_handler.c \
src/signal/eof_handler.c \
src/executor/executor.c \
src/executor/children.c \
src/executor/check_path.c \
src/executor/heredoc.c \
src/executor/execute_ast/execute_complete_command.c \
src/executor/execute_ast/execute_list.c \
src/executor/execute_ast/execute_and_or.c \
src/executor/execute_ast/execute_pipeline.c \
src/executor/execute_ast/execute_pipe_sequence.c \
src/executor/execute_ast/execute_command.c \
src/executor/execute_ast/execute_simple_command.c \
src/executor/execute_ast/execute_cmd_name.c \
src/executor/execute_ast/execute_cmd_suffix.c \
src/executor/execute_ast/execute_io_redirect.c \
src/executor/handle_redirect.c \
src/executor/redirects_great.c \
src/executor/redirects_less.c \
src/builtin/builtins.c \
src/builtin/ft_cd.c \
src/builtin/ft_cd_pathfinder.c \
src/builtin/access.c \
src/builtin/ft_setenv.c \
src/builtin/ft_unset.c \
src/builtin/ft_type.c \
src/builtin/ft_intern_var.c \
src/line_edition/add_key/add_key.c \
src/line_edition/copy_paste/paste_screen.c \
src/line_edition/copy_paste/paste_background.c \
src/line_edition/copy_paste/clipping.c \
src/line_edition/copy_paste/cutting.c \
src/builtin/ft_jobs.c \
src/builtin/ft_fg.c \
src/builtin/builtin_utils.c \
src/line_edition/ctrl_left_right.c \
src/line_edition/ctrl_up_down.c \
src/line_edition/ft_get_line.c \
src/line_edition/history.c \
src/line_edition/home_end_key.c \
src/line_edition/left_right_bs_key.c \
src/line_edition/term_attr.c \
src/line_edition/up_down_key.c \
src/line_edition/carriage_return.c \
src/line_edition/get_prompt/get_prompt.c \
src/line_edition/line_edition_utilities.c \
src/utilities/tool_for_checking.c \
src/utilities/get_var.c \
src/utilities/ft_arraydel.c \
src/utilities/error.c \
src/utilities/ft_strjoin_and_free.c \
src/utilities/set_oldpwd.c \
src/utilities/increment_shell_level.c \
src/executor/print_binary_tree.c \
src/jobs/ft_tcgetsetpgrp.c \
src/jobs/job_utils.c \
src/jobs/foreground_and_background.c \
src/jobs/stopped_and_terminated_jobs.c \
src/jobs/continuing_stopped_jobs.c \
src/jobs/lauch_process.c \
src/auto_completion/auto_status.c \
src/auto_completion/auto_completion.c \
src/auto_completion/auto_dir.c \
src/auto_completion/auto_file.c \
src/auto_completion/auto_is_dir.c \
src/auto_completion/auto_file_one_case.c \
src/auto_completion/auto_file_multiple_cases.c \
src/auto_completion/auto_open_path.c \
src/auto_completion/auto_make_list.c \
src/auto_completion/auto_print_list.c \
src/auto_completion/auto_get_list.c \
src/auto_completion/auto_lstdel_strdel.c


OBJS_NAME = main.o \
lexical_analysis.o \
get_token_info.o \
get_the_last_token.o \
lexer_helper1.o \
lexer_helper2.o \
syntax_analysis.o \
and_or.o \
ast_tool.o \
cmd_name.o \
cmd_suffix.o \
word.o \
command.o \
complete_command.o \
file_name.o \
io_file_branch.o \
io_files.o \
io_here.o \
io_redirect.o \
list.o \
pipe_sequence.o \
pipeline.o \
simple_command.o \
tool_for_checking.o \
get_var.o \
ft_arraydel.o \
error.o \
ft_strjoin_and_free.o \
sig_handler.o \
executor.o \
builtins.o \
execute_complete_command.o \
execute_list.o \
execute_and_or.o \
execute_pipeline.o \
execute_pipe_sequence.o \
execute_command.o \
execute_simple_command.o \
execute_cmd_name.o \
execute_cmd_suffix.o \
execute_io_redirect.o \
ft_cd.o \
ft_cd_pathfinder.o \
access.o \
ft_setenv.o \
ft_unset.o \
ft_jobs.o \
ft_fg.o \
children.o \
check_path.o \
heredoc.o \
add_key.o \
clipping.o \
cutting.o \
paste_screen.o \
paste_background.o \
ctrl_left_right.o \
ctrl_up_down.o \
history.o \
home_end_key.o \
left_right_bs_key.o \
term_attr.o \
up_down_key.o \
ft_get_line.o \
interpret.o \
eof_handler.o \
carriage_return.o \
set_oldpwd.o \
handle_redirect.o \
redirects_great.o \
redirects_less.o \
clear_token.o \
get_prompt.o \
increment_shell_level.o \
check_syntax.o \
jump_single_or_double_quote.o \
ft_type.o \
builtin_utils.o \
create_non_quoted_string.o \
print_binary_tree.o \
ft_tcgetsetpgrp.o \
job_utils.o \
foreground_and_background.o \
stopped_and_terminated_jobs.o \
continuing_stopped_jobs.o \
lauch_process.o \
ft_intern_var.o \
auto_status.o \
auto_completion.o \
auto_dir.o \
auto_file.o \
auto_is_dir.o \
auto_file_one_case.o \
auto_file_multiple_cases.o \
auto_open_path.o \
auto_make_list.o \
auto_print_list.o \
auto_get_list.o \
auto_lstdel_strdel.o \
line_edition_utilities.o

OBJS_PATH = obj/

OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAME))


.PHONY: all, clean, fclean, re
all: $(NAME)

$(NAME):
	@make -s -C ./libft
	@make -s -C ./ft_printf
	@gcc -c $(FLAGS) $(INC) $(SRCS)
	@mkdir -p $(OBJS_PATH)
	@mv $(OBJS_NAME) $(OBJS_PATH)
	@gcc $(FLAGS) $(OBJS) -L$(LIBFT_PATH) -lft -L$(FT_PRINTF_PATH) -lftprintf -ltermcap -o $(NAME)
#	 @gcc $(FLAGS) $(SRCS) libft/libft.a $(INC) -ltermcap #debug for ihwang

clean:
	@make -s -C ./libft clean
	@make -s -C ./ft_printf clean
	@/bin/rm -rf $(OBJS_NAME)
	@/bin/rm -rf $(OBJS_PATH)

fclean: clean
	@make -s -C ./libft fclean
	@make -s -C ./ft_printf fclean
	@/bin/rm -f $(NAME)

re: fclean all
