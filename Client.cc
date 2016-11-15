#include "Client.h"

void menu()
{
	cout<<"\t System of filed send(client)"<<endl;
	cout<<"\t Input the dir u want to put the file"<<endl;
	cout<<"\t\t:";
}


int main()
{
	string F_dir;
	menu();
 	cin>>F_dir;
	//------------------
	//Client socks init
	//------------------
	socks Client_socks;

	//-------------------
	//Link to the server
	//-------------------
	if ( Client_socks.Link_to_the_server()== -1)
	{
		cout<<"\t 1.Link_to_the_server error"<<endl;
		Client_socks.destory();
		return 0;
	}
	else
	{
		cout<<"\t 1.Link_to_the_server clear"<<endl;
	}


	//-----------------------------
	//create connect to the server
	//-----------------------------
	if( Client_socks.Get_base_information(F_dir)==-1)
	{
		cout<<"\t 2.Get_base_information fault"<<endl;
		Client_socks.destory();
		return 0;
	}
	else
	{
		cout<<"\t 2.Get_base_information clear"<<endl;
	}

	//--------------------
	if( Client_socks.Get_core_information()==-1)
	{
		cout<<"\t 3.Get_core_information fault"<<endl;
		Client_socks.destory();
		return 0;
	}
	else
	{
		cout<<"\t 3.Get_core_information clear"<<endl;
	}

	//------------------
	//destory the socks
	//------------------
	Client_socks.destory();
	return 0;
}

