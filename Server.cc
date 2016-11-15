#include "server.h"

void menu()
{
    cout<<"\t System of filed send(server)"<<endl;
    cout<<"\t Input the dir of file"<<endl;
    cout<<"\t\t:";
}

int main()
{
    //-----------------------------
    //solve the File name problems
    //-----------------------------
    
    char F_dir[1024];
    char F_classfic[25];
    int F_classfic_length;
    int j=0;
    int temp=0;

    menu();

    cin>>F_dir;
    for(int i=0;i<sizeof(F_dir);i++)
    {
        if(F_dir[i]=='.')
        {
            temp=i+1;
            break;
        }
    }
    for(int i=temp;i<sizeof(F_dir);i++)
    {
        if(F_dir[i]=='\0')
            break;
        F_classfic[j]=F_dir[i];
        j++;
    }
    F_classfic_length=j;
    
    //------------------------
    //Create the Server socks
    //------------------------
    socks Server_socks;
    
    //------------------------
    //Init the socks features
    //------------------------
    if( Server_socks.Link_to_the_client()== -1)
    {
        cout<<"\t 1.Link_to_the_client error"<<endl;
        Server_socks.destory();
        return 0;
    }
    else
    {
        cout<<"\t 1.Link_to_the_client clear"<<endl;
    }
    
    //-------------------------------------------------
    //Connect to the client and send  base infromation
    //-------------------------------------------------
    if( Server_socks.Sent_base_information(F_dir,F_classfic,F_classfic_length) == -1)
    {
        cout<<"\t 2.Sent_base_information error"<<endl;
        Server_socks.destory();
        return 0;
    }
    else
    {
        cout<<"\t 2.Sent_base_information clear"<<endl;
    }

    //----------------------
    //send core information
    //----------------------
    if( Server_socks.Sent_core_information()== -1)
    {
        cout<<"\t 3.Sent_core_information error"<<endl;
        Server_socks.destory();
        return 0;
    }
    else
    {
        cout<<"\t 3.Sent_core_information clear"<<endl;
    }
    
    //------------------
    //destory the socks
    //------------------
    Server_socks.destory();
    return 0;
}
