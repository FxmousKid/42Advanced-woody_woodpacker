#include "parser/parser_cli.h"

/**
 * @brief exits at the parsing level on invalid options / args
 *
 * @param exit_code the exit code
 */
static void
exit_parsing(unsigned char exit_code)
{
	exit(exit_code);
}


static bool
opts_handle(struct s_data *ctx, int opt, char *argv[])
{	
	switch (opt) {
	
	case 'h':
		printf("help str\n");
		return false;

	/* Unknown option */
	case '?':
		ERR_MSG("Unknown option %s", argv[optind]);
		fprintf(stderr, "Check usage with -h, --help\n");
		ctx->exit_code = EXIT_FAILURE;
		return false;

	/* If no option were provided */
	default:
		return false;
	}

	return true;
}


/**
 * @brief parses the options given by the user
 *
 * @param ctx the data to update based on what is parsed
 * @param argc the arg count to give to getopt_long
 * @param argv the args
 *
 * @note this function doesn't return, it either succeeds or exits
 */
static void
parse_options(struct s_data *ctx, int argc, char *argv[])
{
	int		opt;
	extern int	opterr;
	const char	*shortopts = "ah";
	struct option	longopts[] = {
		{"help", no_argument, NULL, 'h'},
		{NULL, no_argument, NULL, 0}
	};

	opterr = 0;
	while ((opt = getopt_long(argc, argv, shortopts, longopts, NULL)) != -1)
		if (!opts_handle(ctx, opt, argv))
			exit_parsing(ctx->exit_code);
}

static bool
parse_arguments(struct s_data *ctx, int argc, char *argv[])
{
	if (argc != 1) {
		ERR_MSG("expected one argument, got %d", argc);
		return false;
	}

	if (strlen(argv[0]) >= PATH_MAX) {
		ERR_MSG("path too long for file : [%s]", argv[0]);
		return false;
	}

	strncpy(ctx->map.filepath, argv[0], sizeof(ctx->map.filepath));

	return true;
}

bool
parse_cli(int *argc, char *argv[], struct s_data *ctx)
{
	parse_options(ctx, *argc, argv);
	*argc -= optind;
	argv += optind;

	if (!parse_arguments(ctx, *argc, argv)) {
		ERR_MSG("Failed to parse arguments");
		return false;
	}
		
	return true;
}
