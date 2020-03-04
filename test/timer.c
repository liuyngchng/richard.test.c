#include <stdio.h>
#include <signal.h>
#include <sys/time.h>	        //itimerval结构体的定义
#include <unistd.h> 
int handle_count=0;
void set_time(void)
{
   struct itimerval itv;
   itv.it_interval.tv_sec=0;	        //单位为秒,     自动装载，之后每10秒响应一次
   itv.it_interval.tv_usec=100*1000;    //单位为微秒.
   itv.it_value.tv_sec=1;               //第一次定时的时间
   itv.it_value.tv_usec=0;
   setitimer(ITIMER_REAL,&itv,NULL);
}
 
void alarm_handle(int sig)
{
   handle_count++;
   time_t t = time(NULL);
   printf("%ld,have handle count is %d\n",t,handle_count);
}
 
int main(void)
{
	struct itimerval itv;
   	signal(SIGALRM,alarm_handle);
   	set_time();
   	char *buf;
    gets(buf);
    //while(1)
	//{
   	//	getitimer(ITIMER_REAL,&itv);
	//	printf("pass second is %d\n",(int)itv.it_value.tv_sec);
   	//	sleep(1);
   	//}	
   	return 0;
}
