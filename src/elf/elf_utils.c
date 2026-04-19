#include "elf/elf_utils.h"

bool	m_inbounds(struct s_map *map, size_t offset, size_t size)
{
	if (offset > map->size || size > map->size)
		return false;
	return (offset + size <= map->size);
}


void	unmap_elf(struct s_map *map)
{
	if (map->base && map->base != MAP_FAILED)
		if (munmap(map->base, map->size) < 0)
			ERR_SYS("munmap");

	map->size = 0;
	map->base = NULL;
}

bool	map_elf(struct s_map *map, int fd)
{
	struct stat st = {0};

	if (fstat(fd, &st) < 0) {
		ERR_SYS("fstat(%d, &st)", fd)
		fprintf(stderr, "fstat error : %s\n", strerror(errno));
		return false;
	}

	map->size = st.st_size;
	map->base = mmap(NULL, map->size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (map->base == MAP_FAILED) {
		ERR_SYS("mmap(NULL, %lu, PROT_READ, 0, %d ,0)", map->size, fd);
		fprintf(stderr, "Failed to map file : %s\n", strerror(errno));
		return false;
	}

	return true;

}

bool is_elf64(struct s_map *map)
{
	const unsigned char *elf_id = (const unsigned char *)map->base;

	if (memcmp(elf_id, ELFMAG, SELFMAG)) {
		unmap_elf(map);
		ERR_MSG("File is not an ELF")
		fprintf(stderr, "File is not an ELF file\n");
		return false;
	}

	if (elf_id[EI_CLASS] != ELFCLASS64) {
		unmap_elf(map);
		ERR_MSG("File is not 64 bit ELF")
		fprintf(stderr, "File is not a 64 bit ELF file\n");
		return false;
	}

	return true;
}
