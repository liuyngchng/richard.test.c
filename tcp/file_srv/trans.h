/**
 * some common structure and function used in client and server.
 **/
#pragma pack(1) 		 		//单字节对齐

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

#ifndef NAME_SIZE
#define NAME_SIZE 128
#endif

#ifndef CMD_SIZE 
#define CMD_SIZE 20
#endif

#ifndef FILE_SIZE 
#define FILE_SIZE 128
#endif 

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
int snd_buf(int i_sockfd, char* buf, size_t t_len);

/**
 * receive stream from i_sockfd to buf limited by t_len
 */
int rcv_buf(int i_sockfd, char* buf, size_t t_len);

/**
 * get filename from file full path
**/
void get_file_name(const char path[], char name[]);

/**
 * save file content from stream represented by sockfd
 * to file name file_name.
**/
int save_f(const char file_path[], int sockfd);

/**
 * send file stream to sockfd
 */
int snd_f(const char file_path[], int sockfd);
