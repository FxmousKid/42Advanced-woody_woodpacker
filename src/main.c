#include <stdio.h>
#include <stdlib.h>

#include "parser/parser_cli.h"
#include "elf/elf_utils.h"


static bool
check_and_prepare_data(struct s_data *ctx)
{
	int fd = 0;
	
	if ((fd = open(ctx->map.filepath, O_RDONLY)) < 0) {
		ERR_SYS("open(%s, O_RDONLY)", ctx->map.filepath)
		fprintf(stderr, "Failed to open given file: %s\n", strerror(errno));
		return false;
	}

	if (!map_elf(&ctx->map, fd)) {
		ERR_MSG("faile to map file");
		fprintf(stderr, "Failed to map given file\n");
		return false;
	}

	if (!is_elf64(&ctx->map)) {
		ERR_MSG("is_elf64 failed")
		return false;
	}

	return true;
}

int main(int argc, char *argv[])
{
	struct s_data ctx = {0};

	if (!parse_cli(&argc, argv, &ctx))
		return EXIT_FAILURE;

	if (!check_and_prepare_data(&ctx))
		return EXIT_FAILURE;


	return EXIT_SUCCESS;
}
