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
void get_file_name(const char path[], char name[])
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

/**
 * save file content from stream represented by sockfd
 * to file name file_name.
**/
int save_f(const char file_path[], int sockfd)
{
	FILE* fp;
	if ((fp = fopen(file_path, "a")) == NULL) {
		cout << "cannot open file" << endl;
		return -1;
	}
	int rd_l;
	char *buf = new char[1500];
	while ((rd_l = recv(sockfd, buf, sizeof(buf), 0)) > 0) {
		int i_len = 0;
		i_len += sizeof(int);
		if (rd_l > 0)
			fwrite(buf, sizeof(char), rd_l, fp);
	}
	fclose(fp);
	return 0;
}

/**
 * send file stream to sockfd
 */
int snd_f(const char file_path[], int sockfd)
{
	FILE* fp;
    if ((fp = fopen(file_path,"rb")) == NULL) {
        cout << "cannot open file" << endl;
        return -1;
    }
    cout << "open file " << file_path << endl;

    int l = 0;
    int sum_l = 0;
    char buf[BUF_SIZE] = {0};
    while (!feof(fp)) {
        l = fread(buf, sizeof(char), sizeof(buf), fp);
        sum_l += l;
        ssize_t w_l = snd_buf(sockfd, buf, l);
        if (w_l < 0) {
            cout << "write file failed " << file_path << endl;
            close(sockfd);
            return -1;
        }
    }
    cout << "uplaod size " << sum_l << endl;
    fclose(fp);
    return 0;

}
