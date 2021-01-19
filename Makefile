# 42sh's file struture
# ______[includes] ------------> all header files go here
#  |____[src]
#     |___[cores]
#     |  |___[lexer]
#     |  |___[parser]
#     |  |___[executor]
#     |  |___[line_edition]
#     |___[features]
#     |  |___[buit-in] -------------> all built-in function go here
#     |  |___[job_control]
#     |  |___[history_management]
#     |  |___[alias]
#     |  |___[expansion]
#     |  |___[signal]
#     |___[utility] ---------> all general function go here ex.library for shell
#     |___main.c
#
# HOW TO ADD YOUR PROJECT INTO THIS MAKEFILE:
#	1. Decide your project where it should be in either "cores" or "features" directory 
#	2. Create your pattern like this
#		a, Declare directory of your project ex: ALIAS_DIR := $(FEATURES_DIR)/alias
# 		Since, alias feature should be put in "features" directory so I declare its directory
#		like the above example
#		b, Declare files in the feature, continue with the alias example
#		I declare a variable ALIAS_FILE which will contain all the files of the alias project
#		Ex: ALIAS_FILE += alias_substitution.c
#		Remember there must be a plus equal sign
#		c, Declare the feature and join its working directory with its files
#		Ex: ALIAS := $(addprefix $(ALIAS_DIR)/,$(ALIAS_FILE))
#		What i do here is I declare the ALIAS variable which will contain all the string
#		from alias files and before that, I added ALIAS_DIR in front of every ALIAS files
#		d, Coming back to the first process, since you have decided where your project belonged
#		, put it into its own part
#		Ex: Since I have decide Alias project go to feature directory, I added:
#		FEATURES += $(ALIAS)
#
# WARNING: If you think your function which you will use several time after to the other
#		project, I recommend you to put its file into the UTILITY.
#		Ex: functions which in the man page
CC				:= clang
CFLAGS			:= -Wall -Wextra -Werror -g # g flag for debugger
PROGRAM			:= 42sh
# library dir
LIBFT_DIR		:= ./libft
FT_RPINTF_DIR	:= ./ft_printf
# path
CORE_DIR		:= src/cores
FEATURES_DIR	:= src/features
# header
INCLUDE			:= -Iincludes/ -Ilibft/includes/ -Ift_printf/includes/
# library
LIB				:= -L$(LIBFT_DIR)/ -lft -L$(FT_RPINTF_DIR)/ -lftprintf -ltermcap
############################ Create core files ################################
#Lexer
LEXER_DIR := $(CORE_DIR)/lexer
LEXER_FILE += lexical_analysis.c
LEXER_FILE += lexer_helper1.c
LEXER_FILE += lexer_helper2.c
LEXER_FILE += non_operator_token.c
LEXER_FILE += operator_token.c
LEXER := $(addprefix $(LEXER_DIR)/,$(LEXER_FILE))
#Parser
PARSER_DIR := $(CORE_DIR)/parser
PARSER_FILE += syntax_analysis.c
PARSER_FILE += AST/complete_command.c
PARSER_FILE += AST/list.c
PARSER_FILE += AST/and_or.c
PARSER_FILE += AST/pipeline.c
PARSER_FILE += AST/pipe_sequence.c
PARSER_FILE += AST/command.c
PARSER_FILE += AST/simple_command.c
PARSER_FILE += AST/cmd_name.c
PARSER_FILE += AST/cmd_suffix.c
PARSER_FILE += AST/io_redirect.c
PARSER_FILE += AST/io_files.c
PARSER_FILE += AST/io_file_branch.c
PARSER_FILE += AST/file_name.c
PARSER_FILE += AST/io_here.c
PARSER_FILE += AST/here_end.c
PARSER_FILE += AST/word.c
PARSER_FILE += AST/ast_tool.c
PARSER := $(addprefix $(PARSER_DIR)/,$(PARSER_FILE))
#Executor
EXECUTOR_DIR := $(CORE_DIR)/executor
EXECUTOR_FILE += print_binary_tree.c
EXECUTOR_FILE += executor.c
EXECUTOR_FILE += children.c
EXECUTOR_FILE += check_path.c
EXECUTOR_FILE += heredoc.c
EXECUTOR_FILE += execute_ast/execute_complete_command.c
EXECUTOR_FILE += execute_ast/execute_list.c
EXECUTOR_FILE += execute_ast/execute_and_or.c
EXECUTOR_FILE += execute_ast/execute_and_or_bg.c
EXECUTOR_FILE += execute_ast/execute_pipeline.c
EXECUTOR_FILE += execute_ast/execute_pipe_sequence.c
EXECUTOR_FILE += execute_ast/execute_command.c
EXECUTOR_FILE += execute_ast/execute_simple_command.c
EXECUTOR_FILE += execute_ast/execute_cmd_name.c
EXECUTOR_FILE += execute_ast/execute_cmd_suffix.c
EXECUTOR_FILE += execute_ast/execute_io_redirect.c
EXECUTOR_FILE += handle_redirect.c
EXECUTOR_FILE += redirects_great.c
EXECUTOR_FILE += redirects_less.c
EXECUTOR_FILE += lauch_process.c
EXECUTOR := $(addprefix $(EXECUTOR_DIR)/,$(EXECUTOR_FILE))
#Line Edition
LINE_EDITION_DIR := $(CORE_DIR)/line_edition
LINE_EDITION_FILE += add_key.c
LINE_EDITION_FILE += clipping.c
LINE_EDITION_FILE += ctrl_k.c
LINE_EDITION_FILE += ctrl_l.c
LINE_EDITION_FILE += ctrl_left_right.c
LINE_EDITION_FILE += ctrl_up_down.c
LINE_EDITION_FILE += ft_get_line.c
LINE_EDITION_FILE += home_end_key.c
LINE_EDITION_FILE += left_right_bs_key.c
LINE_EDITION_FILE += reverse_search.c
LINE_EDITION_FILE += reverse_search_utils.c
LINE_EDITION_FILE += term_attr.c
LINE_EDITION_FILE += up_down_key.c
LINE_EDITION_FILE += carriage_return.c
LINE_EDITION_FILE += get_prompt.c
LINE_EDITION_FILE += line_edition_utilities.c
LINE_EDITION_FILE += paste_background.c
LINE_EDITION := $(addprefix $(LINE_EDITION_DIR)/,$(LINE_EDITION_FILE))
# SUM-UP Core
CORE += $(LEXER)
CORE += $(PARSER)
CORE += $(EXECUTOR)
CORE += $(LINE_EDITION)
############################# Create feature files ############################
#Built-in
BUILT_IN_DIR := $(FEATURES_DIR)/builtin
BUILT_IN_FILE += ft_exit.c
BUILT_IN_FILE += ft_echo.c
BUILT_IN_FILE += ft_env.c
BUILT_IN_FILE += ft_pwd.c
BUILT_IN_FILE += ft_cd.c
BUILT_IN_FILE += ft_cd_utilities/ft_cd_pathfinder.c
BUILT_IN_FILE += ft_cd_utilities/access.c
BUILT_IN_FILE += ft_setenv.c
BUILT_IN_FILE += ft_unsetenv.c
BUILT_IN_FILE += ft_jobs.c
BUILT_IN_FILE += ft_fg.c
BUILT_IN_FILE += ft_fc.c
BUILT_IN_FILE += ft_fc_utilities/ft_fc_exec.c
BUILT_IN_FILE += ft_fc_utilities/ft_fc_exec_e.c
BUILT_IN_FILE += ft_fc_utilities/ft_fc_exec_s.c
BUILT_IN_FILE += ft_fc_utilities/ft_fc_utilities.c
BUILT_IN_FILE += ft_fc_utilities/ft_fc_list.c
BUILT_IN_FILE += ft_bg.c
BUILT_IN_FILE += ft_alias.c
BUILT_IN_FILE += ft_unalias.c
BUILT_IN_FILE += ft_alias_utilities/ft_alias_utils.c
BUILT_IN_FILE += ft_hash.c
BUILT_IN := $(addprefix $(BUILT_IN_DIR)/,$(BUILT_IN_FILE))
# Job control
JOB_CONTROL_DIR := $(FEATURES_DIR)/job_control
JOB_CONTROL_FILE += job_utils.c
JOB_CONTROL_FILE += process_utils.c
JOB_CONTROL_FILE += foreground_and_background.c
JOB_CONTROL_FILE += stopped_and_terminated_jobs.c
JOB_CONTROL_FILE += continuing_stopped_jobs.c
JOB_CONTROL := $(addprefix $(JOB_CONTROL_DIR)/,$(JOB_CONTROL_FILE))
# History Management
HISTORY_MANAGEMENT_DIR := $(FEATURES_DIR)/history_management
HISTORY_MANAGEMENT_FILE += history.c
HISTORY_MANAGEMENT_FILE += history_exp.c
HISTORY_MANAGEMENT_FILE += history_input_check.c
HISTORY_MANAGEMENT := $(addprefix $(HISTORY_MANAGEMENT_DIR)/,$(HISTORY_MANAGEMENT_FILE))
# Alias
ALIAS_DIR := $(FEATURES_DIR)/alias
ALIAS_FILE += alias_substitution.c
ALIAS := $(addprefix $(ALIAS_DIR)/,$(ALIAS_FILE))
# Signal
SIGNAL_DIR := $(FEATURES_DIR)/signal
SIGNAL_FILE += sig_handler.c
SIGNAL_FILE += eof_handler.c
SIGNAL := $(addprefix $(SIGNAL_DIR)/,$(SIGNAL_FILE))
# Expansion
EXPANSION_DIR := $(FEATURES_DIR)/expansion
EXPANSION_FILE += handle_expansion.c
EXPANSION_FILE += quote_removal.c
EXPANSION := $(addprefix $(EXPANSION_DIR)/,$(EXPANSION_FILE))
# Auto-complition
AUTO_COMPLETION_DIR := $(FEATURES_DIR)/auto_completion
AUTO_COMPLETION_FILE += auto_status.c
AUTO_COMPLETION_FILE += auto_completion.c
AUTO_COMPLETION_FILE += auto_dir.c
AUTO_COMPLETION_FILE += auto_file.c
AUTO_COMPLETION_FILE += auto_is_dir.c
AUTO_COMPLETION_FILE += auto_file_one_case.c
AUTO_COMPLETION_FILE += auto_file_multiple_cases.c
AUTO_COMPLETION_FILE += auto_open_path.c
AUTO_COMPLETION_FILE += auto_make_list.c
AUTO_COMPLETION_FILE += auto_print_list.c
AUTO_COMPLETION_FILE += auto_get_list.c
AUTO_COMPLETION_FILE += auto_lstdel_strdel.c
AUTO_COMPLETION_FILE += auto_command.c
AUTO_COMPLETION_FILE += auto_add_one_extra_char.c
AUTO_COMPLETION_FILE += auto_add_list_on_spot.c
AUTO_COMPLETION := $(addprefix $(AUTO_COMPLETION_DIR)/,$(AUTO_COMPLETION_FILE))
# SUM-UP FEATUREs
FEATURES += $(BUILT_IN)
FEATURES += $(HISTORY_MANAGEMENT)
FEATURES += $(JOB_CONTROL)
FEATURES += $(ALIAS)
FEATURES += $(SIGNAL)
FEATURES += $(EXPANSION)
FEATURES += $(AUTO_COMPLETION)
########################### Create utility_FILE files ##############################
UTILITY_DIR := src/utility
UTILITY_FILE += tool_for_checking.c
UTILITY_FILE += get_var.c
UTILITY_FILE += ft_strndup.c
UTILITY_FILE += ft_arraydel.c
UTILITY_FILE += ft_strjoin_and_free.c
UTILITY_FILE += increment_shell_level.c
UTILITY_FILE += ft_num_check.c
UTILITY_FILE += ft_strchr_int.c
UTILITY_FILE += ft_swap.c
UTILITY_FILE += ft_strstr_int.c
UTILITY_FILE += ft_lstlen.c
UTILITY_FILE += jump_quote.c
UTILITY_FILE += ft_strncpm.c
UTILITY_FILE += ft_strnequ.c
UTILITY_FILE += ft_getenv.c
UTILITY_FILE += ft_swap_int.c
UTILITY_FILE += ft_strbuilder.c
UTILITY_FILE += ft_strbuilder_char.c
UTILITY_FILE += ft_tcsetpgrp.c
UTILITY_FILE += ft_tcgetpgrp.c
UTILITY := $(addprefix $(UTILITY_DIR)/,$(UTILITY_FILE))
############################ SUM-UP SOURCE FILES ##############################
SRC := src/main.c
SRC += $(UTILITY)
SRC += $(CORE)
SRC += $(FEATURES)
# Create object files from src file
OBJ_DIR			:= objects
SRC_DIR			:= src
OBJECTS			:= $(addprefix $(OBJ_DIR)/,$(SRC:%.c=%.o))

all: lft lftprintf mkdirs $(PROGRAM)
	@echo "\033[92m42sh Created\033[0m"

mkdirs:
	@mkdir -p $(OBJ_DIR)

lft:
	@cd $(LIBFT_DIR) && $(MAKE) -s

lftprintf:
	@cd $(FT_RPINTF_DIR) && $(MAKE) -s

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $(OBJ_DIR)/$(notdir $@)

$(PROGRAM): $(OBJECTS)
	@$(CC) $(CFLAGS) $(addprefix $(OBJ_DIR)/, $(notdir $(OBJECTS))) $(LIB) -o $@

clean:
	@cd $(LIBFT_DIR) && $(MAKE) -s clean
	@cd $(FT_RPINTF_DIR) && $(MAKE) -s clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@cd $(LIBFT_DIR) && $(MAKE) -s fclean
	@cd $(FT_RPINTF_DIR) && $(MAKE) -s fclean
	@rm -rf $(PROGRAM)

re: fclean all

.PHONY: all mkdirs lft lftprintf clean fclean re