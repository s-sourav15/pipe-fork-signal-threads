#include<fstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include<ctype.h>
#include<iostream>
#include<bits/stdc++.h>
#include<arpa/inet.h>

using namespace std;
void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char* argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
	portno=atoi(argv[3]);
    //string s="127.0.0.1";
    char buffer[1024];
        //portno = 15047;
	int clientid=atoi(argv[1]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[2]); 
//htons("127.0.0.1");
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
   

        bzero(buffer,1024);
        //input file name
    while(1){
	string str;
	string client=to_string(clientid);
	string str2;
	string str3=" ";
	string str4;
	str2=client+str3;
	
	//string str2=".txt";
	getline(cin,str);
	str4=str2+str;
	cout<<str;
	if(str=="nullfile"){exit(1);}
else{
	char file[20];
	//str.append(str2,0,4);
	//strcpy(file,str.c_str());

     	write(sockfd,str4.c_str(),50);
	
	cout<<file;
      
    
		char response[20];
		bzero(&response,20);
		//response=0;
		int k=recv(sockfd,&response,20,0);
		if(k==0){close(sockfd); exit(0);}
		string s=response;
		cout<<clientid<<","<<str<<","<<response;
    }}
    close(sockfd);
    return 0;
}



