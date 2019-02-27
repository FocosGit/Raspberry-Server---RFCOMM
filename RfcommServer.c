/*
 * cd /home/facility/facilityshare/Biblioteca_de_Programas/Facility
compilation step
# gcc -o RfcommServer.exe RfcommServer.c -lbluetooth -lpthread

* to run: ./RfcommServer.exe
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <pthread.h>
#include <signal.h>

int s,client ;
char Server_Id[] = "B8:27:EB:55:A9:A3";

void 	ctrl_c_handler(int signal);
void 	close_sockets();
void 	*readMsg();
void 	*sendMsg();

int 	client;

int main(int argc,char **argv)
{
    struct sockaddr_rc loc_addr = { 0 }, rem_addr = { 0 };
    char buf[1024] = { 0 };
    int s,  bytes_read = 1;
    socklen_t opt = sizeof(rem_addr);

    (void) 	signal(SIGINT,ctrl_c_handler);


pthread_t readT, writeT;
char *message1 = "Read thread\n";
char *message2 = "Write thread\n";
int iret1, iret2;

//allocate socket
s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);


// bind socket to port 1 of the first available
// local bluetooth adapter
loc_addr.rc_family 	= AF_BLUETOOTH;
loc_addr.rc_bdaddr 	= *BDADDR_ANY;
loc_addr.rc_channel = (uint8_t) 1;

printf("\n  bind \n");
bind(s, (struct sockaddr *)&loc_addr, sizeof(loc_addr));
printf("Binding success\n");

//put socket into listen mode
listen(s,1) ;
printf("socket in listen mode\n");
//accept one connection

client = accept(s, (struct sockaddr *)&rem_addr, &opt);

ba2str( &rem_addr.rc_bdaddr, buf );
fprintf(stderr, "accepted connection from %s\n", buf);
memset(buf, 0, sizeof(buf));


/* Create independent threads each of which will execute function */
iret1 = pthread_create(&readT,NULL,readMsg,(void*) message1);
iret2 = pthread_create(&writeT,NULL,sendMsg,(void*) message2);

pthread_join(readT,NULL);
pthread_join(writeT,NULL);

close_sockets() ;
return 0 ;
}

void *sendMsg()
{
char msg[25] ;
int status ;

do	{
	memset(msg,0,sizeof(msg));
	fgets(msg,24,stdin);
	if(strncmp("EXIT",msg,4)==0 || strncmp("exit",msg,4)==0)break;
	status = send(client,msg,strlen(msg),0);
	fprintf(stdout,"Status = %d\n",status);
	}	while(status > 0);
}

void *readMsg()
{
int bytes_read;
char buf[1024] = { 0 };
do	{
	strcpy(buf, "");
	//read data from the client
	bytes_read = read(client, buf, sizeof(buf));
	printf("Bytes read = %d, conteudo=%s.\n",bytes_read, buf);
	}	while(bytes_read > 0);
}

void close_sockets()
{
//close connection
close(client);
close(s) ;
printf("sockets closed\n");
}

void ctrl_c_handler(int signal)
{
printf("Catched signal: %d ... !!\n", signal);
close_sockets();
exit(0);
//(void) signal(SIGINT, SIG_DFL);
}
