#include "utils/debug.h"

int	get_logfd(void)
{
	static int fd = 0;

	if (fd == 0)
		fd = open(LOGFILE_PATH, O_RDWR | O_CREAT | O_TRUNC, 0644);

	if (fd < 0) {
		printf("Could not create logfile\n");
		exit(2);
	}

	return fd;
}

/**
 * @brief prints on logfile a system error msg with location
 */
void	_write_perr(const char *location)
{
	dprintf(get_logfd(), ": %s [%s]\n", strerror(errno), location);
}

/**
 * @brief prints on logfile a custom error msg with location
 */
void	_write_err(const char *location)
{
	dprintf(get_logfd(), " [%s]\n", location);
}

/**
 * @brief prints a hex dump of a buffer to stdout
 *
 * @param label "SEND" or "RECV" prefix
 * @param buf pointer to data
 * @param len number of bytes
 */
void	debug_hex(const char *label, const void *buf, size_t len)
{
	const uint8_t	*p = buf;

	printf("[%s] %zu bytes: ", label, len);
	for (size_t i = 0; i < len; i++)
		printf("%02x ", p[i]);
	printf("\n");
}

void	debug_send(bool debug_mode, const void *buf, size_t len)
{
	if (debug_mode)
		debug_hex("SEND", buf, len);
}

void	debug_recv(bool debug_mode, const void *buf, size_t len)
{
	if (debug_mode)
		debug_hex("RECV", buf, len);
}
