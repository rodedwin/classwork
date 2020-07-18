//gcc sample_daemon.c -o sampled
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>

#define OK          0
#define ERR_FORK    1
#define ERR_SETSID  2
#define ERR_CHDIR   3
#define ERR_WTF     4

const char *ERROR_FORMAT;

#define DAEMON_NAME "sampled"

// This is the signal handler. "signal"  is the signal passed to us to handle.
// Input:   <signal> (SIGHUP, SIGTERM)
// Output:  SIGHUP  - does nothing
//          SIGTERM - logs signal and exits program
//	        else    - logs it as an unhandled signal.

static void _signal_handler(const int signal) {
	switch(signal) {
		case SIGHUP:
            // does nothing
			break;
		case SIGTERM:
			syslog(LOG_INFO, "Received SIGTERM, exiting...\n"); // starts logging to syslog
			closelog();                                         // close log
			exit(OK);                                           // exit the program
			break;
		default:
			syslog(LOG_INFO, "Received unhandled signal.\n");   // handles unknown signals
	}
}

// This is where we do the work of the deamon. 
// As is sits, it just counts and sleeps. 
// Need to modify this section for the homework
//
static void _do_work(void) {
	for(int i=0; true; i++) {
		syslog(LOG_INFO, "Iteration: %d.\n", i);
		sleep(1);
	}
}

int main(void) {
	// Open the syslog
	openlog(DAEMON_NAME, LOG_PID | LOG_NDELAY | LOG_NOWAIT, LOG_DAEMON);
	syslog(LOG_INFO, "starting sampled\n");
	
	// Create child process so we dont take over syslogd or initd, fork.
	pid_t pid = fork();

	if(pid < 0) {
		syslog(LOG_ERR, ERROR_FORMAT, strerror(errno));
		return ERR_FORK;
	}

	// We dont care about the parent, exit...
	if(pid > 0) {
		return OK;
	}
	
	// Need to be the leader, if not, exit
	if(setsid() < -1) {
		syslog(LOG_ERR, ERROR_FORMAT, strerror(errno));
		return ERR_SETSID;
	}

	// Close file descriptors
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	// Set umask, this gives us read/write permissions, only read for others.
	umask(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

	// Set up working directory
	if(chdir("/") < 0) {
		syslog(LOG_ERR, ERROR_FORMAT, strerror(errno));
		return ERR_CHDIR;
	}

	// Creating a signal handler
	signal(SIGTERM, _signal_handler);
	signal(SIGHUP, _signal_handler);

	// Do work!!!
	_do_work();

	return ERR_WTF;
}
