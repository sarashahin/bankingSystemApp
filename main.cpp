#include <iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include <map>


using namespace std;

int minBalance = 1500;
class insufficAmount{};
class Account
{
  private:
        long accountNum;
        string firstName, lastName;
        float balance;
        static long nextAccNum;
  public:
        Account(){};
        Account(string firName, string lasName, float balance);
        long getAccountNum(){return accountNum;}
        string getFirstName(){return firstName;}
        string getLastName(){return lastName;}
        float getBalance(){return balance;}

        void deposit(float amount);
        void withdraw(float amount);

        static void setLastAccNum(long accountNum);
        static long getLastAccNum();

        friend ofstream &operator << (ofstream &ofs, Account &acc);
        friend ifstream &operator >> (ifstream &ifs, Account &acc);
        friend ostream &operator << (ostream &os, Account &acc);
};
long Account :: nextAccNum = 0;

class Bank
{
  private:
        map<long, Account> accounts;
  public:
        Bank();
        Account openAcc(string firName, string lasName, float balance);
        Account balanceEnquiry(long accountNum);
        Account deposit(long accountNum, float amount);
        Account withdraw(long accountNum, float amount);
        void closeAcc(long accountNum);
        void showAccs();
        ~ Bank();
};

int main() {
  Bank b;
  Account acc;

  int choice;
  string firName, lasName;
  float balance;
  float amount;
  long accountNum;

  cout << " **Banking System **"<< endl;

  do
  {
    cout << "\n\tSelect the below option :";
    cout << "\n\t1 open Account " ;
    cout << "\n\t2 Balance Enquiry ";
    cout << "\n\t3 Deposit " ;
    cout << "\n\t4 Withdraw" ;
    cout << "\n\t5 Close Account" ;
    cout << "\n\t6 Show all Accounts" ;
    cout << "\n\t7 Quit ";
    cout << "\nEnter the Choice : ";
    cin>> choice;

    switch (choice)
    {
      case 1 :
          cout << "Enter first name "<< endl;
          cin >> firName;
          cout << "Enter last name "<< endl;
          cin >> lasName;
          cout << "Enter Balance "<< endl;
          cin >> balance;
          acc = b.openAcc(firName, lasName, balance);
          cout << endl<< "Account is created "<< endl;
          cout << acc;
          break;
      case 2:
          cout<<"Enter Account Number:";
          cin>>accountNum;
          acc=b.balanceEnquiry(accountNum);
          cout<<endl<<"Your Account Details"<<endl;
          cout<<acc;
          break;
      case 3:
          cout<<"Enter Account Number:";
          cin>>accountNum;
          cout<<"Enter Balance:";
          cin>>amount;
          acc=b.deposit(accountNum, amount);
          cout<<endl<<"Amount is Deposited"<<endl;
          cout<<acc;
          break;
      case 4:
          cout<<"Enter Account Number:";
          cin>>accountNum;
          cout<<"Enter Balance:";
          cin>>amount;
          acc=b.withdraw(accountNum, amount);
          cout<<endl<<"Amount Withdrawn"<<endl;
          cout<<acc;
          break;
      case 5:
          cout<<"Enter Account Number:";
          cin>>accountNum;
          b.closeAcc(accountNum);
          cout<<endl<<"Account is Closed"<<endl;
          cout<<acc;
      case 6:
          b.showAccs();
          break;
      case 7: break;
          default:
          cout<<"\nEnter corret choice";
          exit(0);
    }
  }
  while(choice != 7); 
  return 0;
}

Account::Account(string firName, string lasName, float balance)
{
 nextAccNum++;
 accountNum = nextAccNum;
 firstName = firName;
 lastName = lasName;
 this->balance = balance;
}

void Account::deposit(float amount)
{
 balance += amount;
}

void Account::withdraw(float amount)
{
 if(balance - amount< minBalance)
 throw insufficAmount();
 balance -= amount;
}

void Account::setLastAccNum(long accountNum)
{
 nextAccNum = accountNum;
}

long Account::getLastAccNum()
{
 return nextAccNum;
}

ofstream & operator << (ofstream &ofs, Account &acc)
{
  ofs<<acc.accountNum <<endl;
  ofs<<acc.firstName <<endl;
  ofs<<acc.lastName<<endl;
  ofs<<acc.balance<<endl;
  return ofs;
}

ifstream &operator >>(ifstream &ifs, Account &acc)
{
  ifs>>acc.accountNum;
  ifs>>acc.firstName;
  ifs>>acc.lastName;
  ifs>>acc.balance;
  return ifs;

}

ostream & operator<<(ostream &os,Account &acc)
{
  os<<"First Name:"<<acc.getFirstName()<<endl;
  os<<"Last Name:"<<acc.getLastName()<<endl;
  os<<"Account Number:"<<acc.getAccountNum()<<endl;
  os<<"Balance:"<<acc.getBalance()<<endl;
  return os;
}

Bank :: Bank()
{
  Account account;
  ifstream infile;
  infile.open("Bank.data");
  if(!infile)
  {
  //cout<<"Error in Opening! File Not Found!!"<<endl;
  return;
  }
  while(!infile.eof())
  {
    infile>>account;
    accounts.insert(pair<long,Account>(account.getAccountNum(),account));
  }

  Account::setLastAccNum(account.getAccountNum());
  infile.close();
}

Account Bank::openAcc(string firname,string lasname,float balance)
{
  ofstream outfile;
  Account account(firname, lasname, balance);
  accounts.insert(pair<long,Account>(account.getAccountNum(),account));

  outfile.open("Bank.data", ios::trunc);
  map<long,Account>::iterator itr;
  for(itr=accounts.begin();itr!=accounts.end();itr++)
  {
    outfile<<itr->second;
  }
  outfile.close();
  return account;
}

Account Bank::balanceEnquiry(long accountNum)
{
  map<long,Account>::iterator itr=accounts.find(accountNum);
  return itr->second;
}

Account Bank::deposit(long accountNum,float amount)
{
  map<long,Account>::iterator itr=accounts.find(accountNum);
  itr->second.deposit(amount);
  return itr->second;
}

Account Bank::withdraw(long accountNum,float amount)
{
  map<long,Account>::iterator itr=accounts.find(accountNum);
  itr->second.withdraw(amount);
  return itr->second;
}

void Bank::closeAcc(long accountNum)
{
  map<long,Account>::iterator itr=accounts.find(accountNum);
  cout<<"Account Deleted"<<itr->second;
  accounts.erase(accountNum);
}

void Bank::showAccs()
{
  map<long,Account>::iterator itr;
  for(itr=accounts.begin();itr!=accounts.end();itr++)
 {
  cout<<"Account "<<itr->first<<endl<<itr->second<<endl;
 }
}

Bank::~Bank()
{
  ofstream outfile;
  outfile.open("Bank.data", ios::trunc);
  map<long,Account>::iterator itr;
  for(itr=accounts.begin();itr!=accounts.end();itr++)
  {
    outfile<<itr->second;
  }
  outfile.close();
}



 
