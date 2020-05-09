#include <sys/types.h>
#include <udt.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <string>
#include <iostream>
#include <fstream>
#include "trans.h"

/**
 * send file to server.
 */
int send_file(char* path);

/**
 * get file from server.
 */
int get_file(char* file_name);
