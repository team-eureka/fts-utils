#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "flash_ts.h"
#include "fts.h"

int main (int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s KEY VALUE\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int fts_dev;
	if ((fts_dev = open(FTS_DEVICE, O_RDONLY)) == -1) {
		perror("Failed to open " FTS_DEVICE);
		exit(EXIT_FAILURE);
	}

	struct flash_ts_io_req cmd;
	strncpy(cmd.key, argv[1], FLASH_TS_MAX_KEY_SIZE - 1);
	strncpy(cmd.val, argv[2], FLASH_TS_MAX_VAL_SIZE - 1);

	if (ioctl(fts_dev, FLASH_TS_IO_SET, &cmd) == -1) {
		perror("Failed to write fts entry");
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}

