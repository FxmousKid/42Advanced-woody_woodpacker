#ifndef PARSER_CLI_H
# define PARSER_CLI_H

# include <getopt.h>
# include <stdbool.h>
# include <stdio.h>

# include "utils/debug.h"
# include "structs.h"

bool	parse_cli(int *argc, char *argv[], struct s_data *ctx);

#endif
