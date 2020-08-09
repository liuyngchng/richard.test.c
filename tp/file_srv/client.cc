#include "agent.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef _WIN32
#include <sys/time.h>
#else
#include <time.h>
#include <windows.h>
#include <winsock.h>
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include "log4c.h"

using namespace std;

int send_file(char* file);

int get_file(char* file_name);

int main(int argc, char** argv){
	log4c_category_t* mycat = NULL;	
	log4c_init();
	mycat = log4c_category_get("com.demo.client");
	char cmd[CMD_SIZE] = {0}, file[FILE_SIZE] = {0};
	cout << "input your cmd:" << endl;
	cin >> cmd >> file;
	cout <<"cmd=" << cmd << ";file=" << file << endl;
	log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
      "some error from app1 at line %d in file %s ",
      __LINE__, __FILE__); 
	if (strcmp(cmd, "put") == 0) {
		send_file(file);
	} else if (strcmp(cmd, "get") == 0) {					//download a file from server	
		get_file(file);
	} else {
		cout << "illegal operation" << endl;
	}
	return 0;
}
