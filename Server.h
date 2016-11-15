#ifndef _SERVER_H
#define _SERVER_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

class socks
{
#define Max_user_number 5
#define buffer_size 1024
#define Server_port 6666
#define Sizeof_int sizeof(int)*8
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
		close(Listen_sock);
		close(App_sock);
	}
	int Link_to_the_client();
	int Sent_core_information();
	int Sent_base_information(const char *File_name,const char *File_classfi,int File_classfi_length);
private:
	int Listen_sock;
	int App_sock;
	struct sockaddr_in Serv_addr;
	struct sockaddr_in Client_addr;
	socklen_t Client_addr_size;

	//------------------------------------------
	//the features that not belong to the socks
	//------------------------------------------	
	FILE *F_pointer;
	int File_length;
};

int socks::Link_to_the_client()
{
	//------------------------------------
	//Creaet the Listen_sock to send data
	//------------------------------------
	Listen_sock = socket(PF_INET,SOCK_STREAM,0);
	if(Listen_sock==-1) 
		return -1;

	Serv_addr.sin_family=AF_INET;
	Serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	Serv_addr.sin_port = htons(Server_port);

	//---------------------------
	//绑定socket属性到socket标识符
	//---------------------------
	if( bind(Listen_sock,(struct sockaddr*)&Serv_addr,sizeof(Serv_addr) ) == -1 ) 
	{
		cout<<"Bind fault"<<endl;
		return -1;
	}

	//-----------------------------------
	//Listen_sock use to listen the sock
	//-----------------------------------
	if( listen(Listen_sock,Max_user_number) == -1) 
	{
		cout<<"Listen fault"<<endl;
		return -1;
	}

	//------------------------------
	//make a connection with client
	//-----------------------------
	cout<<"\t To out of the system plus: (Ctrl+c)"<<endl;
	while(true)
	{	
		App_sock=accept(Listen_sock,(struct sockaddr*)&Client_addr,&Client_addr_size);
		if(App_sock == -1)
		{
			continue;
		}
		else
		{
			cout<<"\t Accept successfully"<<endl;
			break;
		}
	}

	
	return 1;
}

int socks::Sent_base_information(const char *File_name,const char *File_classfi,int File_classfi_length)
{
	//--------------
	//open the file
	//--------------
	F_pointer=NULL;
	F_pointer=fopen(File_name,"rb");
	if(!F_pointer)
	{
		cout<<"\t The file is not exists"<<endl;
		return -1;
	}

	//-----------------------
	//get the length of file
	//-----------------------
	fseek(F_pointer,0,SEEK_END);
	File_length=ftell(F_pointer);
	fseek(F_pointer,0,SEEK_SET);


	//----------------------
	//send base information
	//----------------------

	//--------------------------
	//send the length of file
	//--------------------------
	send(App_sock,&File_length,sizeof(File_length),0);

	//----------------------------------
	//send the length of File classfi
	//----------------------------------
	send(App_sock,&File_classfi_length,sizeof(File_classfi_length),0);

	//--------------------------------
	//send the name of file classfi
	//--------------------------------
	send(App_sock,File_classfi,sizeof(File_classfi),0);

	return 1;
}

/*
typedef struct 
{
	char send_buffer[1024];
	int Data_size;
	int final;
}Data;
*/

int socks::Sent_core_information()
{
	//------------------------
	//define all the features 
	//------------------------
	int File_length_temp;
	int Sent_data_length;
	int Client_flag;
	int Cnt;
	char *Buffer;

	//-----------------------
	//init all the featrures
	//-----------------------
	Buffer=(char*) malloc (sizeof (char)*1024);
	Cnt=1;
	File_length_temp=File_length;

	cout<<"\t Init File_length:"<<File_length<<endl;


	while( !feof( F_pointer ) )  
	{  
        Sent_data_length = fread( Buffer, 1, 1024, F_pointer );
        
        cout<<"\t cnt:"<<Cnt++<<"\t Data_length: "<<Sent_data_length<<endl;
		
		send( App_sock,Buffer, Sent_data_length, 0);

		if(Sent_data_length<0)
		{
			return -1;
		}

    }

	return 1;
}
#endif







