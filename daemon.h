#ifndef DAEMON_H
#define DAEMON_H

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

#define EXIT_SUCCESS 0

void deploy_daemon() {
	pid_t pid, sid;

	pid = fork();
	if (pid < 0) {
		exit(EXIT_FAILURE);
	}

	if (pid > 0) {
		exit(EXIT_SUCCESS);
	}

	umask(0);

	sid = setsid();
	if (sid < 0) {
		exit(EXIT_FAILURE);
	}

	if (chdir("/") != 0) {
		exit(EXIT_FAILURE);
	}
}

void write_pid(const char *path) {
	pid_t pid = getpid();
	FILE *file = fopen(path, "w");

	if (file == NULL) {
		return;
	}

	if (fprintf(file, "%d\n", pid) < 0) {
		
	}

	fclose(file);
}

#endif
