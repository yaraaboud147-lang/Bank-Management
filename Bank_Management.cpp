#include <iostream>
#include <string>
#include <vector>
using namespace std;
 class Account 
{
protected :
 int accountNumber;
 string ownername ;
 double balance ;
 double *history;
int historySize;
int index;
static double totalBankCapital;
public:
Account(int a,string o, double b, int size){
 accountNumber=a;
 ownername=o;
 balance=b;
 historySize=size;
 index=0;
 history = new double[historySize];
 totalBankCapital += balance;
 }
 Account(const Account& ac){
  accountNumber=ac.accountNumber;
 ownername=ac.ownername;
 balance=ac.balance;
 historySize=ac.historySize;
 index=ac.index;
 history = new double[historySize];
 for(int i=0;i<historySize;i++){
  history[i] = ac.history[i];
 }}
 void deposit(double amount){
  balance +=amount;
  totalBankCapital += amount;
  if(index<historySize){
   history[index]=amount;
   index++;
  }
  
 }
 virtual bool withdraw(double amount){
 if(balance<amount)
  {
   return false;
  }
  else{
  balance-=amount;
  totalBankCapital -= amount;
  if (index < historySize) {
    history[index] = -amount; 
    index++;
}

  
  return true;
 
  }
  
 }
 virtual void display (){
 cout << "accountNumber=" <<accountNumber<< endl;
  cout << "ownername=" <<ownername<< endl;
  cout << "balance=" <<balance<< endl;
}
static void showbankcapitl(){
 cout << totalBankCapital<< endl;
 }
 
 void printHistory() {
    cout << "--- Transaction History for " << ownername << " ---" << endl;
    for (int i = 0; i < index; i++) {
        if (history[i] > 0)
            cout <<i <<"Deposit: + "<< history[i] << endl;
        else
            cout << i << " Withdrawal: " << history[i] << endl;
    }
}

 virtual ~Account() {
    totalBankCapital -= balance;
    delete[] history; }
 };
double Account ::totalBankCapital=0;

 class SavingsAccount:public Account{
  private:
   double interestRate;
  public:
  SavingsAccount(int a,string o, double b, int size,double rate):Account(a,o,b,size),interestRate(rate){}
  
   bool withdraw(double amount) override{
   
   if((balance-amount)<100){
   cout << "no" << endl;
    return false ;
   }
  else{
  balance-=amount;
  cout << balance << endl;
  totalBankCapital -= amount;
  if (index < historySize) {
    history[index] = -amount; // حطينا ناقص لتبيّن إنها سحب مو إيداع
    index++;
}
  
  return true;}}
   void display () override{
 cout << "accountNumber=" <<accountNumber<< endl;
  cout << "ownername=" <<ownername<< endl;
  cout << "balance=" <<balance<< endl;
  cout << "===============" << endl;
}
void addInterest() {
    double interest = balance * interestRate;
    balance += interest;
    totalBankCapital += interest; // تحديث سيولة البنك
}


  
 };
 class CheckingAccount:public Account{
  private:
   double overdraftLimit;
  public:
  CheckingAccount(int a,string o, double b, int size,double lim):Account(a,o,b,size),overdraftLimit(lim){}
  
   bool withdraw(double amount) override{
   if(amount>(balance+overdraftLimit)){
    cout << "no" << endl;
    return false;
   }
   else 
   {
   balance -=amount;
   cout <<  balance << endl;
   totalBankCapital -= amount;
   if (index < historySize) {
    history[index] = -amount; // حطينا ناقص لتبيّن إنها سحب مو إيداع
    index++;
}
   return true; 
   
   }
   }
  
  void display () override{
 cout << "accountNumber=" <<accountNumber<< endl;
  cout << "ownername=" <<ownername<< endl;
  cout << "balance=" <<balance<< endl;
  cout << "===============" << endl;
}
 };
 
int main(){
 vector<Account*> a;
 a.push_back(new SavingsAccount(1234,"yuri",5000,4,0.5) );
 a.push_back(new CheckingAccount(1234,"yara",2000,4,2000) );
  for(int i=0;i<a.size();i++){
  a[i]->withdraw(500);
  a[i]->deposit(100);
   a[i]->display(); 
   a[i]->showbankcapitl();
   a[i]->printHistory();

  
  }
  for (int i = 0; i < a.size(); i++) {
    delete a[i];
}
a.clear();

  
  
  
  
}
  
  
  
  
  
  

