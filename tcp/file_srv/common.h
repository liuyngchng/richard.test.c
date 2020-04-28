/**
 * some common structure and function used in client and server.
 **/
#include<iostream>
#pragma pack(1) 		 		//单字节对齐
#define BUF_SIZE 1024
#define NAME_SIZE 128 
#define CMD_SIZE 20 
#define FILE_SIZE 128 

using namespace std;

/**
 * a file sturcture used to send and recieve file
 **/
struct f_file
{
	int size;  					// current transport size
	char buf[BUF_SIZE];  		// file content 
}; 

/**
 * send buf content limited by t_len to i_sockfd. 
 **/
int snd_buf(int i_sockfd, char* buf, size_t t_len)
{ 
	int i_this_snd;
	unsigned int i_snd = 0;
	if (t_len == 0)
		return 0;
	while (i_snd < t_len) {
		do {
			i_this_snd = send(i_sockfd, buf, t_len - i_snd, 0);
		} while ((i_this_snd < 0) && (errno == EINTR)); 
		if (i_this_snd < 0)
			return i_snd;
		i_snd += i_this_snd;
		buf += i_this_snd;
	}
	return t_len;
} 

/**
 * receive stream from i_sockfd to buf limited by t_len
 */
int rcv_buf(int i_sockfd, char* buf, size_t t_len)
{
	int i_this_rd;
	unsigned int i_rd = 0;
	if (t_len == 0)
		return 0;
	while (i_rd < t_len) {
		do {
			i_this_rd = read(i_sockfd, buf, t_len - i_rd);
		} while((i_this_rd < 0) && (errno == EINTR));
		if (i_this_rd < 0)
			return i_this_rd;
		else if (i_this_rd == 0)
			return i_rd;
		i_rd += i_this_rd;
		buf += i_this_rd;
	}
}

/**
 * get filename from file full path
**/
void get_file_name(char path[], char name[])
{
	//cout << "path=" << path << endl;
    int j = strlen(path)-1;
    int i = j;
    for ( ; i >= 0 ; i--) {
        if (path[i] == '/' || path[i] == '\\')
            break;
        else
            name[j-i] = path[i];
    }
    //cout << "temp=" << name << endl;
    j = strlen(name)-1;
    for (i = 0; i <= j/2; i++) {
        char temp = name[i];
        name[i] = name[j-i];
        name[j-i] = temp;
    }
    name[j+2] = '\0';
    cout << "get_file_name="<< name << endl;
}


