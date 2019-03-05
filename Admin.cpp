#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>
#include<queue>
#include<fstream>
#include<iostream>
#include<pthread.h>
#include <cstdlib>
#include<csignal>
#include<signal.h>
#include<sstream>
using namespace std;
int addr[1024];
char buf[20];
int fd[2];
int ll=0;
int pn;
int f[2];
int t;

//void(*hand_pt)(int);
//typedef void handler(int);
class active{
public:
int sock,flag;
active(int Sock,int Flag){ //add portno
sock=Sock;
flag=Flag;}
active(){}
};
active act[1024];
queue<active> a;
class readyQueue{
public:
int sock;
string file;
string cid;
int pno;
readyQueue(string Cid,string File,int Sock,int Pno){
//readyQueue(int Sock,string File){
sock=Sock;
file=File;
cid=Cid;
pno=Pno;
}
readyQueue(){}

};

readyQueue rq[1024];
queue<readyQueue> q;


void *threadA(void *){

close(fd[1]);
while(1){
read(fd[0],buf,20);
if(*buf=='t'||*buf=='T'){
readyQueue rus=q.front();
while(!q.empty()){
close(rus.sock);
q.pop();

}

exit(0);
break;
}
//cout<<"the buffer is"<<*buf;
if(*buf=='x'||*buf=='X'){


//cout<<"opening";
//for(int i=0;i<ll;i++){

while(!q.empty()){
int sum=0;
ifstream f;
readyQueue rm=q.front();
if(rm.file!="nullfile"){
f.open(rm.file);
//cout<<rm.file;
if(!f){cout<<"file not opened";}
	int num;
	f>>num;
	//cot<<num;
	while(num>0){
	int n;	
	f>>n;
	sum+=n;
	num--;
	
}
	string str=to_string(sum);
	
//cout<<q.front();
	//cout<<"sock"<<rm.sock<<endl;
	send(rm.sock,str.c_str(),20,0);
	
	q.pop();
}
usleep(t*1000);}
}
}}
int sockfd, newsockfd,portno;
struct sockaddr_in serv_addr, cli_addr;
socklen_t clilen;
     	char buffer[1024];
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void *threadCC(void *){
while(1){
	int clisocket;
	clilen = sizeof(cli_addr);
	//cout<<"before"<<endl;
	clisocket = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (clisocket < 0) 
        error("ERROR on accept");
	//newsockfd=accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        addr[ll]=clisocket;
	//cout<<endl;
	
	//cout<<"here";
	
			
        //g.push(newsockfd);
	ll++;

}
}


void *threadC(void *){
while(1){
        char buf1[50];
	//cout<<ll;
        int j;
	for(int i=0;i<ll;i++)
{				
	
	//cout<<ll;
	//int j;
	//cout<<endl;
       
	j=read(addr[i],buf1,50);
	if(j<0)
       {error("receive fail");}
	string file=buf1;
	bzero(buf1,50);
	//cout<<buf1;


	//char line[50] = "test one two three.";
	//string s;
	//s+=line;

    	string arr[2];
    	int j = 0;
    	stringstream ssin(file);
    	while (ssin.good() && j < 2){
        	ssin >> arr[j];
        	++j;
    	}
    	
	int client;

	client=ntohs(cli_addr.sin_port);
	if(arr[1]!="nullfile"){
	rq[i]=readyQueue(arr[0],arr[1],addr[i],client);
	act[i]=active(addr[i],1);	
	q.push(rq[i]);
	a.push(act[i]);
	//readyQueue rr=q.front();
	//cout<<"message"<<rq[i].file;
}	
	else{
	act[i]=active(addr[i],0);
	a.push(act[i]);
}						//write thread  printing and binding error sigrtmin
}	
}
}
void handler(int sig){
	//cout<<"handler working";
	close(f[1]);
	while(!q.empty()){
	
	readyQueue r=q.front();
	string cli=r.cid;
	string name=r.file;
	int s=r.sock;
	int p=r.pno;
	
	string pn=to_string(p);
	string so=to_string(s);
	string str= ",";
	string space=" ";
	string str1=cli+str;
	string str2=str1+space;
	string str3=str2+name;
	string str4=str3+str;
	string str5=str4+space;
	string str6=str5+so;
	string str7=str6+str;
	string str8=str7+space;
	string str9=str8+pn;
	//string str=s+g;
	write(f[0],str9.c_str(),50);
	q.pop();
	
}
	//if(q.empty){cout<<"EMPTY READY QUEUE";}

}




int main(int argc, char* argv[]){

char* command;
char val;
command=&val;

//hand_pt=&handler;
pipe(fd);
pipe(f);
int pid=fork();
int x;
if(pid==0){
cout<<"Computer, "<<pid<<", "<<getpid()<<endl;
	x=getpid();
	
     	//signal(SIGRTMIN,handler);
	pn=atoi(argv[1]);
	t=atoi(argv[2]);
	//cout<<"the command is "<<com<<endl;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
     	if (sockfd < 0) 
        	error("ERROR opening socket");
     	bzero((char *) &serv_addr, sizeof(serv_addr));
     	portno = pn;
     	serv_addr.sin_family = AF_INET;
     	serv_addr.sin_addr.s_addr = INADDR_ANY;
     	serv_addr.sin_port = htons(portno);
	//cout<<"check";

     	if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     	listen(sockfd,5);
     	
	cout<<"computer process server socket ready"<<endl;

     	pthread_t threads[4];
     	pthread_create(&threads[1],NULL,threadCC,NULL);
       
        pthread_create(&threads[2],NULL,threadC,NULL);
	pthread_create(&threads[3],NULL,threadA,NULL);
	//close(newsockfd);
	//pthread_join(threads[1],NULL);
	//pthread_join(threads[2],NULL);
	pthread_join(threads[3],NULL);

}
else{
cout<<"Admin, "<<pid<<", "<<getpid()<<endl;
sleep(1);
while(1){
	cout<<"admin command:";
	cin>>command;
	if(*command=='x'||*command=='X'){

	close(fd[0]);
	write(fd[1],command,5);}
	else if(*command=='t'||*command=='T'){
	close(fd[0]);
	write(fd[1],command,5);
	exit(0);
}
	else if(*command=='q'||*command=='Q'){
	//cout<<"kill"<<endl;
	cout<<x;	
	kill(x,SIGRTMIN);
	
	close(f[1]);
	//readyQueue res;
	char Res[50];	
	
	read(f[0],Res,50);
	cout<<Res;
	break;}
	
	}
}


return 0;}
