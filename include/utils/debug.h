#ifndef DEBUG_H
# define DEBUG_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <stdint.h>
# include <stdbool.h>
# include <unistd.h>

# ifndef LOGFILE_PATH
#  define LOGFILE_PATH	"server.log"
# endif

# define STRINGIFY(x) #x
# define TOSTRING(x) STRINGIFY(x)
# define DBG __FILE__ " @ " TOSTRING(__LINE__)
# define ERR_SYS(...) do {dprintf(get_logfd(), "[ERROR] "); dprintf(get_logfd(), __VA_ARGS__); _write_perr(DBG); } while (0);
# define ERR_MSG(...) do {dprintf(get_logfd(), "[ERROR] "); dprintf(get_logfd(), __VA_ARGS__); _write_err(DBG); } while (0);

int		get_logfd(void);
void		_write_perr(const char *location);
void		_write_err(const char *location);


/**
 * @brief prints a hex dump of a buffer to stdout (debug mode only)
 *
 * @param label "SEND" or "RECV" prefix
 * @param buf pointer to data
 * @param len number of bytes
 */
void		debug_hex(const char *label, const void *buf, size_t len);

/**
 * @brief wrapper: logs sent bytes in debug mode
 */
void		debug_send(bool debug_mode, const void *buf, size_t len);

/**
 * @brief wrapper: logs received bytes in debug mode
 */
void		debug_recv(bool debug_mode, const void *buf, size_t len);

#endif
