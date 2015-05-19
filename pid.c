#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int is_process_dir(const char* dirname);
int get_dir_list(void);

int main(void) {
	return get_dir_list();
}

int get_dir_list(void) {
	struct stat st;
	DIR* dirp;
	struct dirent* dp;
	char *buffer;
	uid_t uid;
	int fd;

	if(!(dirp = opendir("/proc")))
		return 1;
	
	uid = getuid();

	while(dp = readdir(dirp))
		if(is_process_dir(dp->d_name)) {
			fprintf(stdout, "%s", dp->d_name);
			buffer = (char*)malloc(sizeof(char) * 
				(strlen(dp->d_name) + 7));
			strcpy(buffer, "/proc/");
			strcat(buffer, dp->d_name);
			fd = open(buffer, O_RDONLY);
			if(fd < 0) {
				free(buffer);
				continue;
			}
			if(fstat(fd, &st))
				perror("fstat");
			close(fd);
			if(uid == st.st_uid)
				fprintf(stdout, "\t(owned by uid)");

			fprintf(stdout, "\n");
			free(buffer);

		}
	
	closedir(dirp);
	return 0;
}

int is_process_dir(const char* dirname) {
	while(*dirname)
		if(!isdigit(*dirname++)) return 0;
	return 1;
}
