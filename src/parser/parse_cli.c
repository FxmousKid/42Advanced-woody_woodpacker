#include "parser/parser_cli.h"

bool	parse_cli(int argc, char *argv[])
{
	if (argc != 2) {
		ERR_MSG("expected argc = 2, got %d", argc);
		return false;
	}

	printf("argv[1] = %s\n", argv[1]);

	return true;
}
