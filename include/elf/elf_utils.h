#ifndef ELF_UTILS_H
# define ELF_UTILS_H

# include <sys/stat.h>
# include <sys/mman.h>

# include <fcntl.h>
# include <elf.h>
# include <stdbool.h>

# include "utils/debug.h"
# include "structs.h"



/**
 * @brief 
 *
 * @param map the mapped file
 * @param offset 
 * @param size 
 *
 * @return
 *  @retval true on success
 *  @retval false otherwise

 */
bool	m_inbounds(struct s_map *map, size_t offset, size_t size);


/**
 * @brief unmaps the mapped ELF file
 *
 * @param map the mapped file
 */
void	unmap_elf(struct s_map *map);

/**
 * @brief maps a ELF file 
 *
 * @param map 
 * @param fd 
 *
 * @return
 *  @retval true on sucess
 *  @retval false otherwise

 */
bool	map_elf(struct s_map *map, int fd);

/*
 * @brief checks if the file at path is a 64 bits ELF
 *
 * @param map 
 *
 * @return
 *  @retval true if mapped file is a elf 64bit
 *  @retval false otherwise
 */
bool	is_elf64(struct s_map *map);

#endif
