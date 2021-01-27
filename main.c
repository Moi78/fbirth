#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <time.h>

#include <sys/types.h>
#include <linux/stat.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/fcntl.h>
#include <dirent.h>

struct statx;
struct statx_timestamp;

int main(int argc, char* argv[]) {
	if(argc <= 1) {
		printf("[fbirth] Error : No file specified.\n");
		printf("----------------------- fbirth usage -----------------------\n");
		printf("fbirth file_path : Displays the specified file creation date\n");
		return -1;
	}

	char* filepath = argv[1];

	struct statx statxbuffer;

	int result = statx(AT_FDCWD, filepath, AT_SYMLINK_NOFOLLOW, STATX_BTIME, &statxbuffer);
	if(result != 0) {
		const char* error_str = strerror(errno);
		printf("[fbirth] Error : %s\n", error_str);
		return -1;
	}

	time_t t = (time_t)statxbuffer.stx_btime.tv_sec;
	struct tm timeFromStamp = *localtime(&t);

	printf(
		"File birth date : %02d/%02d/%02d at %02d:%02d:%02d \n",
		timeFromStamp.tm_mday,
		timeFromStamp.tm_mon + 1,
		timeFromStamp.tm_year + 1900,
		timeFromStamp.tm_hour,
		timeFromStamp.tm_min,
		timeFromStamp.tm_sec
	);

	return 0;
}
