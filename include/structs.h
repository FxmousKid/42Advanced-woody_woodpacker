#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>

# if !defined(PATH_MAX)
#  define PATH_MAX 4096
# endif

struct s_map {
	size_t		size;
	unsigned char	*base;
	char		filepath[PATH_MAX + 1];
};

struct s_data {
	struct s_map	map;
	unsigned char	exit_code;
};

#endif
