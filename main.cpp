#include <iostream>
#include <string>
#include <string.h>
#include <ctype.h>

using namespace std;
void fill_T(int T[],char key_user[],int n);
void permutes_by_KSA(int S[],int T[]);
void permutes_by_PRGA(int S[],int key_stream[],int z);
void encryption_by_key_stream(int key_stream[],char planText[],int cipherText[],int z);
void decryption_by_key_stream(int key_stream[],int cipherText[],int z);
void print(int matrix[],int n);
int menu();



int main()
{
    int chose,z=0,n=0,S[256],T[256];
    char charcter,key_user[256],planText[256];
    cout<<endl<<"ENTER plan Text : ";
    cin.getline(planText,255);
    z=strlen(planText);
    int key_stream[z];
    int cipherText[z];
    cout<<"ENTER Key : ";
    cin.getline(key_user,255);
    cout<<endl;
    n=strlen(key_user);

    for(int i=0;i<256;i++)
    {
        S[i]=i;
    }
    fill_T(T,key_user,n);
    permutes_by_KSA(S,T);
    permutes_by_PRGA(S,key_stream,z);

    cout<<"The key stream Is : ";
    print(key_stream,z);
    cout<<endl;
    while((chose=menu())!=3)
   {
       switch(chose)
       {
           case 1:
                 encryption_by_key_stream(key_stream,planText,cipherText,z);break;
           case 2:
                 decryption_by_key_stream(key_stream,cipherText,z);break;
       }
   }
    return 0;
}


void fill_T(int T[],char key_user[],int n)
{
    int j=0;
    for(int i=0;i<256;i++)
    {
        if(j==n)
        {
            j=0;
        }
        T[i]= key_user[j];
        j++;
    }
}

void permutes_by_KSA(int S[],int T[])
{
    int j=0;
    for(int i=0;i<256;i++)
    {
        j=((j+S[i]+T[i])%256);
        swap(S[i],S[j]);
    }
}

void permutes_by_PRGA(int S[],int key_stream[],int z)
{
    int j=0,i=0,t;
    for(int r=0;r<z;r++)
    {
        i=((i+1)%256);
        j=((j+S[i])%256);
        swap(S[i],S[j]);
        t=((S[i]+S[j])%256);
        key_stream[r]=S[t];
    }
}

void encryption_by_key_stream(int key_stream[],char planText[],int cipherText[],int z)
{
    for(int i=0;i<z;i++)
    {
        cipherText[i]=(planText[i]^key_stream[i]);
    }
    char charectar;
    cout<<"The Cipher Text Is : ";
    for(int i=0;i<z;i++)
    {
        charectar = cipherText[i];
        cout<<charectar;
    }
    cout<<endl;
}

void decryption_by_key_stream(int key_stream[],int cipherText[],int z)
{
    cout<<"The Plan Text Is : ";
    char charectar;
    for(int i=0;i<z;i++)
    {
        charectar = cipherText[i]^key_stream[i];
        cout<<charectar;
    }
    cout<<endl;
}

void print(int matrix[],int n)
{
    for(int i=0;i<n;i++)
    {
        cout<<matrix[i]<<' ';
    }
    cout<<endl;
}

int menu()
{
    int choice;
        cout<<"                          {  menu }              "<<endl;
        cout<<"              ------  enter 1 for encryption  -------"<<endl;
        cout<<"              ------  enter 2 for decryption  -------"<<endl;
        cout<<"              ------  enter 3 to exit         -------"<<endl;
    cin>>choice;
    return(choice);
}
