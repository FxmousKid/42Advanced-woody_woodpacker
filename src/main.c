#include "parser/parser_cli.h"

#include "stdio.h"
#include "stdlib.h"

int main(int argc, char *argv[])
{
	if (!parse_cli(argc, argv))
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}
