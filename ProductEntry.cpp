#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

struct product
{
	char p_name[20],c_name[20];
	int quan;
	float MRP,b_price;
};


class validation
{
	ifstream fin;
	char password[20],username[20],user[20],pass[20];
	void input();
	public:
	bool isverify();
	validation()
	{
		fin.open("verify.txt");
	}
	
	~validation()
	{
		fin.close();
	}
};
bool validation::isverify()
{
	input();
	int flag=0;
	while(fin.eof()==0)
	{
		fin>>username>>password;
		if(strcmp(user,username)==0 && strcmp(pass,password)==0)
		{
			flag=1;
			break;
		}		
	}
	if(flag==1)
		return true;
	else
		return false;
}
void validation::input()
{
	cout<<"Enter username: "<<endl;
	gets(user);
	cout<<"Enter password: "<<endl;
	gets(pass);
}

double amountInvested=0;

class StoreDebit
{
	ifstream fin;
	ofstream fout;
	double amt1,amt2;
	public:
	StoreDebit()
	{
		fin.open("credit_debit.data");
		fin>>amt1>>amt2;
		fin.close();
	}
	~StoreDebit()
	{
		fout.open("credit_debit.data");
		fout<<amt1+amountInvested<<endl<<amt2;
		cout<<"Today you have bought "<<amountInvested<<endl;
		fout.close();
	}
};

class Product
{
	protected:
	ofstream fout;
	ifstream fin;
	struct product p[100];
	virtual bool choose()=0;
	int count;
	public:
	Product()
	{
		fin.open("Product.data");
		for(count=0;fin.eof()==0;count++)
			fin>>p[count].p_name>>p[count].c_name>>p[count].quan>>p[count].b_price>>p[count].MRP;
	}
	~Product()
	{
		fout.close();
		fout.open("product.data");
		for(int i=0;i<count-1;i++)
		{
			if(p[i].quan>0)
				fout<<p[i].p_name<<"\t"<<p[i].c_name<<"\t"<<p[i].quan<<"\t"<<p[i].b_price<<"\t"<<p[i].MRP<<endl;
		}
		fout.close();
	}
};

class ProductEntry : private Product
{
	private:
	char product_name[20],company_name[20],str[20]; // p_name:product name | c_name:company name
	int p_quan; // p_quan:product quantity
	double price,rs; // b_price:base price | s_price:selling price
	void input();
	void Entry();
	bool choose();
	public:
	void processing();
};

void ProductEntry::input()
{
	cout<<"Enter product name:"<<endl;
	gets(product_name);
	strupr(product_name);
	cout<<"Enter the company of the "<<product_name<<": "<<endl;
	gets(company_name);
	strupr(company_name);
	cout<<"Enter no of "<<product_name<<" :"<<endl;
	gets(str);
	if(atoi(str)==0)
		throw 1;
	else
		p_quan = atoi(str);
}

void ProductEntry::Entry()
{
	int flag=0,i;
	for(i=0;i<count-1;i++)
	{
		if(strcmp(product_name,p[i].p_name)==0 && strcmp(company_name,p[i].c_name)==0)
		{
			p[i].quan = p[i].quan+p_quan;
			flag=1;
			break;
		}
	}
	if(flag==0)
	{
		cout<<"Enter base price of "<<product_name<<" :"<<endl;
		gets(str);
		if(atoi(str)==0)
			throw 2;
		else
			price = atoi(str);
		cout<<"Enter MRP of the "<<product_name<<" :"<<endl;
		gets(str);
		if(atoi(str)==0)
			throw 3;
		else
			rs = atoi(str);
		strcpy(p[i].p_name,product_name);
		strcpy(p[i].c_name,company_name);
		p[i].quan = p_quan;
		p[i].b_price = price;
		p[i].MRP = rs;
		count++;
	}
	amountInvested=amountInvested+(p_quan*p[i].b_price);
}

bool ProductEntry::choose()
{
	cout<<"Do you want to enter more product(y/n):"<<endl;
	char ch;
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

void ProductEntry::processing()
{
	while(true)
	{
		input();
		Entry();
		if(!choose())
		break;
	}
}

int main()
{
	validation val;
	if(!val.isverify())
	{
		cout<<"Invalid username or password"<<endl;
		return 0;
	}
	ProductEntry p;
	try
	{
		p.processing();
		StoreDebit amt;
	}
	catch(char c)
	{
		cout<<"Invalid choose"<<endl;
	}
	catch(int a)
	{
		cout<<"Invalid input"<<endl;
	}
	return 0;
}