#include "agent.h"

using namespace std;

int send_file(char* file);

int get_file(char* file_name);

int main(int argc, char** argv){
	
	char cmd[CMD_SIZE] = {0}, file[FILE_SIZE] = {0};
	cout << "input your cmd:" << endl;
	cin >> cmd >> file;
	cout <<"cmd = " << cmd << ";file = " << file << endl; 
	if (strcmp(cmd, "put") == 0) {
		send_file(file);
	} else if (strcmp(cmd, "get") == 0) {					//download a file from server	
		get_file(file);
	} else {
		cout << "illegal operation" << endl;
	}
	return 0;
}
