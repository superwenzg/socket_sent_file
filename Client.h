#ifndef _CLIENT_H
#define _CLIENT_H
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

class socks
{
#define Server_ip "127.0.0.1"
#define Sizeof_int sizeof(int)*8
#define Server_port 6666
#define buffer_size 1024
public:
	socks()
	{
		//---------------------------------
		//初始化socket函数中的固有结构体及属性
		//---------------------------------
		Client_addr_size=sizeof(Serv_addr);
		memset(&Serv_addr,0,sizeof(Serv_addr));
		memset(&Client_addr,0,sizeof(Client_addr));
	}
	void destory()
	{
		close(Client_sock);
	}
	int Link_to_the_server();
	int Get_base_information(string F_dir);
	int Get_core_information();
private:
	int Client_sock;
	struct sockaddr_in Serv_addr;
	struct sockaddr_in Client_addr;
	socklen_t Client_addr_size;

	//------------------------------------------
	//the features that not belong to the socks
	//------------------------------------------	
	FILE *F_pointer;
	int File_length;
};

int socks::Link_to_the_server()
{
	//-------------------------------------
	//Creaet the Client_sock to the server
	//-------------------------------------
	Client_sock= socket(PF_INET,SOCK_STREAM,0);
	Serv_addr.sin_family=AF_INET;
	Serv_addr.sin_addr.s_addr=inet_addr(Server_ip);
	Serv_addr.sin_port=htons(Server_port);

	if( connect(Client_sock,(struct sockaddr*)&Serv_addr,sizeof(Serv_addr)) == -1 )
	{
		return -1;
	}
	return 1;
}

int socks::Get_base_information(string F_dir)
{
	//----------------------------------------------
	//define all the number that the function need
	//----------------------------------------------
	F_pointer=NULL;
	int Get_base_information_flag;
	int File_classfic_length;
	char *buffer;

	//--------------------
	//init all the number
	//--------------------
	File_classfic_length=0;
	buffer=new char[1024];

	//--------------------------------------
	//get the length of file that will recv
	//--------------------------------------
	//1
	Get_base_information_flag=recv(Client_sock, &File_length, sizeof(File_length), 0);
	if(Get_base_information_flag==-1)
	{
		return -1;
	}

	//------------------------------
	//get the classfication of file
	//------------------------------
	//2 the length of classfication
	Get_base_information_flag=recv(Client_sock, &File_classfic_length, sizeof(File_classfic_length), 0);
	if(Get_base_information_flag==-1)
	{
		return -1;
	}

	//3
	Get_base_information_flag=recv(Client_sock, buffer, File_classfic_length, 0);
	if(Get_base_information_flag==-1)
	{
		return -1;
	}

	//----------------------
	//init the file_pointer
	//----------------------
	string File_name=F_dir;
	File_name+="/_1_2_3.";
	string File_classfic;
	File_classfic=buffer;

	File_name+=File_classfic;
	F_pointer=fopen( (char*)File_name.data(),"wb+");
	
	return 1;
}

int socks::Get_core_information()
{
	//------------------------
	//define all the features 
	//------------------------
	int File_length_temp;
	int Write_data_length;
	int Server_flag=1025;
	int Cnt;
	char Buffer[1024];

	//----------------------
	//init all the features 
	//----------------------
	File_length_temp=File_length;
	Cnt=1;

	cout<<"\t Get File Length:"<<File_length<<endl;

	//---------------------
	//get data from server
	//---------------------
	while(  true  )
	{
		Server_flag=recv(Client_sock,Buffer,1024,0);
		
		cout<<"\t cnt:"<<Cnt++<<"\t Data_length: "<<Server_flag<<endl;
		
		if(Server_flag <0 )
		{
			return -1;
		}

		fwrite(Buffer,Server_flag,1,F_pointer);
		
		if(Server_flag<1024)
			break;
	}

	return 1;
}

#endif