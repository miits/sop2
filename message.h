#ifndef SOP_MESSAGE_H
#define SOP_MESSAGE_H
#include <time.h>

typedef struct msgbuf
{
	long mtype;
	int error;
	int pid;
	int number[3];
	char tab1[30];
	char tab2[30];
	char tab3[30];
	char tab4[30];
	char tab5[30];
	struct tm time[2];
}msgbuf;

msgbuf msg1;
msgbuf msg2;

int msqid1;
int msqid2;

#endif //SOP_MESSAGE_H
