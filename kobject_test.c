#include <unistd.h>
#include <sys/types.h>
#include <linux/fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/*
int pdfd0, pdfd1, pdfd2;

void *Threadn_fn1(void *arg)
{
  	pdfd0  = open("/sys/kernel/kobject_example/foo", O_RDWR); 
   	if(pdfd0<0) { perror("Error in opening foo"); exit(1); }
}

void *Threadn_fn2(void *arg)
{
   	pdfd1  = open("/sys/kernel/kobject_example/baz", O_RDWR); 
   	if(pdfd1<0) { perror("Error in opening baz"); exit(1); }
}

void *Threadn_fn3(void *arg)
{
   	pdfd2  = open("/sys/kernel/kobject_example/bar", O_RDWR); 
   	if(pdfd2<0) { perror("Error in opening bar"); exit(1); }
}

pthread_attr_t      pthread_attr1, pthread_attr2, pthread_attr3;
struct sched_param  param1, param2, param3;
pthread_t           fooThread1_id, bazThread2_id, barThread3_id;
*/

int main()
{
	char *rd_buf;
    int  ret;
    int pdfd0, pdfd1, pdfd2;    
    rd_buf = (char *)malloc(4);
    
    //---------------OPEN----------------
  	pdfd0  = open("/sys/kernel/kobject_example/foo", O_RDWR); 
   	if(pdfd0<0) { perror("Error in opening foo"); exit(1); }
   	pdfd1  = open("/sys/kernel/kobject_example/baz", O_RDWR); 
   	if(pdfd1<0) { perror("Error in opening baz"); exit(1); }
   	pdfd2  = open("/sys/kernel/kobject_example/bar", O_RDWR); 
   	if(pdfd2<0) { perror("Error in opening bar"); exit(1); }

/*
    pthread_attr_init(&pthread_attr1);
    pthread_attr_init(&pthread_attr2);
    pthread_attr_init(&pthread_attr3);
    param1.sched_priority = 2;
    param2.sched_priority = 1;
    param3.sched_priority = 1;

    pthread_attr_setschedpolicy(&pthread_attr1, SCHED_FIFO);
    if(ret>0) { printf("error in pthread_attr_setschedpolicy\n");  exit(2); }
//  pthread_setschedparam(&pthread_attr1, &param1);
//  pthread_attr_setinheritsched(&pthread_attr1, PTHREAD_EXPLICIT_SCHED);

    pthread_attr_setschedpolicy(&pthread_attr2, SCHED_FIFO);
    if(ret>0) { printf("error in pthread_attr_setschedpolicy\n");  exit(2); }
//  pthread_setschedparam(&pthread_attr2, &param2);
//  pthread_attr_setinheritsched(&pthread_attr2, PTHREAD_EXPLICIT_SCHED);

    pthread_attr_setschedpolicy(&pthread_attr3, SCHED_FIFO);    
    if(ret>0) { printf("error in pthread_attr_setschedpolicy\n");  exit(2); }
//  pthread_setschedparam(&pthread_attr3, &param3);
//  pthread_attr_setinheritsched(&pthread_attr3, PTHREAD_EXPLICIT_SCHED);
  
	ret = pthread_create(&fooThread1_id, &pthread_attr1, Threadn_fn1, (void*)pdfd0);
   	if(ret>0) { printf("error in fooThread1 creation\n"); exit(4); }
	ret = pthread_create(&bazThread2_id, &pthread_attr2, Threadn_fn2, (void*)pdfd1);
   	if(ret>0) { printf("error in bazThread2 creation\n");  exit(4); }
	ret = pthread_create(&barThread3_id, &pthread_attr3, Threadn_fn3, (void*)pdfd2);
   	if(ret>0) { printf("error in barThread3 creation\n");  exit(4); }

	pthread_attr_destroy(&pthread_attr1);
   	pthread_attr_destroy(&pthread_attr2);
   	pthread_attr_destroy(&pthread_attr3);
*/

    //-------------------WRITE----------------
	write(pdfd0, "77", 2);
	write(pdfd1, "85", 2);
	write(pdfd2, "44", 2);
    //-------------------SEEK-----------------
    lseek(pdfd0, 0, SEEK_SET);
    lseek(pdfd1, 0, SEEK_SET);
    lseek(pdfd2, 0, SEEK_SET);
    //-------------------READ-----------------
	read(pdfd0, rd_buf, 2);
    printf("the value in foo is %s\n",rd_buf);       
	read(pdfd1, rd_buf, 2);
    printf("the value in baz is %s\n",rd_buf);
	read(pdfd2, rd_buf, 2);
    printf("the value in bar is %s\n",rd_buf);	

/*  
    pthread_join(fooThread1_id,NULL);
    pthread_join(bazThread2_id,NULL);
    pthread_join(barThread3_id,NULL);
*/
    exit(0);
}
