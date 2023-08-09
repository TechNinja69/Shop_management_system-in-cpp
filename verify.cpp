#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

struct val
{
	char username[20],password[20];
};

class validation
{
	private:
	struct val v[10];
	ifstream fin;
	char str[10];
	int count,i,size=0;
	bool choose();
	void input(int);
	public:
	void process();
	validation()
	{
		fin.open("verify.txt");
		for(i=0;!fin.eof();i++)
		{
			fin>>v[i].username>>v[i].password;
		}
		count = i-1;
	}
	
	~validation()
	{
		fin.close();
		ofstream fout("verify.txt",ios::app);
		for(i=count;i<count+size;i++)
		{
			fout<<v[i].username<<"\t"<<v[i].password<<endl;
		}
		fout.close();
	}
};

bool validation::choose()
{
	char ch;
	cout<<"Do you want to enter more(y/n):"<<endl;
	gets(str);
	if(strlen(str)==1)
	{
		if(str[0]=='n' || str[0]=='n' || str[0]=='y' || str[0]=='Y')
		{
			ch = str[0];
		}
		else
			throw 'n';
	}
	else 
		throw 'a';
	if(ch=='n' || ch=='n')
	return false;
	else
	return true; 
}

void validation::input(int j)
{
	cout<<"Enter username: "<<endl;
	gets(str);
	for(i=0;i<count;i++)
	{
		if(strcmp(v[i].username,str)==0)
		{
			throw "This username is already here";
		}
	}
	for(i=0;i<strlen(str);i++)
	{
		if(str[i]==' ')
		{
			throw 1;
			break;
		}	
	}
	strcpy(v[j].username,str);
	cout<<"Enter password: "<<endl;
	gets(v[j].password);
	for(i=0;i<strlen(v[j].password);i++)
	{
		if(v[j].password[i]==' ')
		{
			throw 1;
			break;
		}	
	}
}

void validation::process()
{
	for(i=count;true;i++)
	{
		try
		{
			input(i);
			size++;
		}
		catch(int i)
		{
			cout<<"Space not allowed:"<<endl;
		}
		if(!choose())
			break;
	}
}

int main()
{
	try
	{
		validation valid;
		valid.process();
	}
	catch(char ch)
	{
		cout<<"Invalid choose:"<<endl;
	}
	catch(const char* ch)
	{
		cout<<ch<<endl;
	}
	return 0;
}