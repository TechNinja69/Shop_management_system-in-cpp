#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

struct product
{
	char p_name[20],c_name[20];
	int quan;
	float MRP,b_price,price;
};

struct customer
{
	char name[20],mob_no[10],gen;
	int p_no;
	double t_price;
	product pr[20];
};

double amountReturn=0;

class validation
{
	ifstream fin;
	char user[20],pass[20],username[20],password[20];
	public:
	int isverify();
	validation()
	{
		fin.open("verify.txt");
	}
	~validation()
	{
		fin.close();
	}
};

int validation::isverify()
{
	cout<<"Enter username: "<<endl;
	gets(user);
	fflush(stdin);
	cout<<"Enter password: "<<endl;
	gets(pass);
	fflush(stdin);
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

class StoreCredit
{
	ifstream fin;
	ofstream fout;
	double amt1,amt2;
	public:
	StoreCredit()
	{
		fin.open("credit_debit.data");
		fin>>amt1>>amt2;
		fin.close();
	}
	~StoreCredit()
	{
		fout.open("credit_debit.data");
		fout<<amt1<<endl<<amt2+amountReturn;
		cout<<"Today you have sold "<<amountReturn<<" rupees product"<<endl;
		fout.close();
	}
};

class Customer
{
	protected:
	ifstream fin;
	ofstream fout;
	struct product p[100];
	struct customer c[20];
	virtual bool choose()=0;
	int count,c_no;
	public:
	Customer();
	~Customer();
};
Customer::Customer()
{
	fin.open("Product.data");
	fout.open("Customer.data",ios::app);
	int i;
	for(i=0;fin.eof()==0;i++)
	{
		fin>>p[i].p_name>>p[i].c_name>>p[i].quan>>p[i].b_price>>p[i].MRP;
	}
	count=i-1;
	c_no=0;
}
Customer::~Customer()
{
	fin.close();
	fout.close();
	fout.open("Product.data");
	for(int i=0;i<count;i++)
	{
		if(p[i].quan>0)
		{
			fout<<p[i].p_name<<"\t"<<p[i].c_name<<"\t"<<p[i].quan<<"\t"<<p[i].b_price<<"\t"<<p[i].MRP<<endl;
		}
	}	
	fout.close();
}
class CustomerEntry:private Customer
{
	private:
	char str[20];
	bool choose();
	void customerDetails(int);
	void productBuyed(int,int);
	void debit();
	public:
	void processing();
	~CustomerEntry();
};

CustomerEntry::~CustomerEntry()
{
	for(int i=0;i<=c_no;i++)
	{
		if(c[i].p_no>0)
		{
			fout<<"********************************CUSTOMER_DETAILS********************************"<<endl<<"Name: "<<c[i].name<<endl<<"Mob_no: "<<c[i].mob_no<<endl<<"Gender: "<<c[i].gen<<endl<<endl;
			cout<<"********************************CUSTOMER_DETAILS********************************"<<endl<<"Name: "<<c[i].name<<endl<<"Mob_no: "<<c[i].mob_no<<endl<<"Gender: "<<c[i].gen<<endl<<endl;
			for(int j=0;j<=c[i].p_no;j++)
			{
				if(c[i].pr[j].MRP>0)
				{
					fout<<"PRODUCT: "<<j+1<<"......"<<endl<<"PRODUCT NAME: "<<c[i].pr[j].p_name<<endl<<"COMPANY NAME: "<<c[i].pr[j].c_name<<endl<<"QUANTITY: "<<c[i].pr[j].quan<<endl<<"PRICE PER "<<c[i].pr[j].p_name<<": "<<c[i].pr[j].MRP<<endl<<"PRICE OF "<<c[i].pr[j].p_name<<": "<<c[i].pr[j].price<<endl<<endl;
					cout<<"PRODUCT: "<<j+1<<"......"<<endl<<"PRODUCT NAME: "<<c[i].pr[j].p_name<<endl<<"COMPANY NAME: "<<c[i].pr[j].c_name<<endl<<"QUANTITY: "<<c[i].pr[j].quan<<endl<<"PRICE PER "<<c[i].pr[j].p_name<<": "<<c[i].pr[j].MRP<<endl<<"PRICE OF "<<c[i].pr[j].p_name<<": "<<c[i].pr[j].price<<endl<<endl;
				}
			}
			fout<<"TOTAL PRICE: "<<c[i].t_price<<endl<<endl;
			cout<<"TOTAL PRICE: "<<c[i].t_price<<endl<<endl;
		}
	}
}

bool CustomerEntry::choose()
{
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

void CustomerEntry::customerDetails(int i)
{
	cout<<"Enter customer details (no spaces allowed/you can use underscore):"<<endl;
	cout<<"Enter customer\'s name:"<<endl;
	gets(c[i].name);
	strupr(c[i].name);
	cout<<"Enter mobile number:"<<endl;
	gets(str);
	if(strlen(str)==10)
	{
		if(atoi(str)!=0)
			strcpy(c[i].mob_no,str);
	}
	else
		throw "given number is not an mobile number";
	cout<<"Enter gender(M/F):"<<endl;
	fflush(stdin);
	gets(str);
	if(strlen(str)==1)
	{
		strupr(str);
		if(str[0]=='M' || str[0]=='F' || str[0]=='m' || str[0]=='f')
		{
			c[i].gen = str[0];
		}
		else
		{
			throw "given character is not a specified character";
		}
	}
	else
		throw "given character is not a specified character";
}

void CustomerEntry::productBuyed(int i,int j)
{
	cout<<"Enter the name of the product: "<<endl;
	gets(c[i].pr[j].p_name);
	strupr(c[i].pr[j].p_name);
	cout<<"Enter the company of the "<<c[i].pr[j].p_name<<": "<<endl;
	gets(c[i].pr[j].c_name);
	strupr(c[i].pr[j].c_name);
	cout<<"how many "<<c[i].pr[j].p_name<<" you want: "<<endl;
	gets(str);
	if(atoi(str)==0)
		throw 1;
	else
		c[i].pr[j].quan = atoi(str);
	int flag=0;
	for(int k=0;k<count-1;k++)
	{
		
		if(strcmp(c[i].pr[j].p_name,p[k].p_name)==0 && strcmp(c[i].pr[j].c_name,p[k].c_name)==0 && c[i].pr[j].quan<=p[k].quan)
		{
			c[i].pr[j].MRP = p[k].MRP;
			c[i].pr[j].price = c[i].pr[j].quan * p[k].MRP;
			c[i].t_price = c[i].t_price + c[i].pr[j].price;
			p[k].quan = p[k].quan-c[i].pr[j].quan;
			flag=1;
			break;
		}
	}
	if(flag==0)
	{
		cout<<"sorry "<<c[i].pr[j].p_name<<" in "<<c[i].pr[j].c_name<<" company is not available"<<endl;
		c[i].pr[j].MRP = 0;
	}
	else
	{
		c[i].p_no++;
		cout<<"Successfully order placed"<<endl;
	}
}

void CustomerEntry::processing()
{
	int i,j;
	for(i=0;true;i++)
	{
		customerDetails(i);
		for(j=0;true;j++)
		{
			productBuyed(i,j);
			cout<<"Do you want to enter more product(y/n):"<<endl;
			if(!choose())
			break;
		}
		amountReturn = amountReturn + c[i].t_price;
		cout<<"More customer(y/n):"<<endl;
		if(!choose())
		break;
	}
	c_no=i+1;
}

int main()
{
	validation valid;
	if(!valid.isverify())
	{
		cout<<"Invalid username or password"<<endl;
		return 0;
	}
	try
	{
		CustomerEntry com;
		com.processing();
		StoreCredit amt;
	}
	catch(const char* str)
	{
		cout<<str<<endl;
	}
	catch(char ch)
	{
		cout<<"Invalid choose:"<<endl;
	}
	catch(int num)
	{
		cout<<"Invalid Quantity"<<endl;
	}	
	return 0;
}