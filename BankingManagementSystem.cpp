#include <iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include <stdio.h>
#include <conio.h>
using namespace std;

class account
{
    char name[100], fathername[100], address[100], type[10];
    float balance;
    int acno;
public:
    void open_account();    //create account
    void deposit_money();   //deposit money
    void withdraw_money();  //subtract withdrawn amount from balance
    void display_account(); //display account info
    void modify_account();  //modify account info
    void write_account();   //write record to binary file
    void display_sp(int);  //display acc details given by user
    void modify_acc(int); //modify record of file
    void delete_account(int); //delete record of file
    void display_all();  //display all account details
    int retacno() const; //retrieve the account number
    void report() const; //function to show data in tabular format
};

void account::open_account()
{
    cout<<"\nEnter the Account No :";
    cin>>acno;
    cout << "\nEnter your Full Name :" << endl;
    cin.ignore();
    cin.getline(name, 100);
    cout << "\nEnter your Father Name :" << endl;
    cin.ignore();
    cin.getline(fathername, 100);
    cout << "\nEnter your Address :" << endl;
    cin.ignore();
    cin.getline(address, 100);
    cout << "\nChoose the type of account savings(s) or current(c):" << endl;
    cin.ignore();
    cin.getline(type, 10);
    cout << "\nEnter amount you want to deposit :" << endl;
    cin >> balance;

    cout << "\nYour account is created successfully!" << endl;
}

void account::deposit_money()
{
    int dep;
    cout << "\nEnter the amount you want to deposit:" << endl;
    cin >> dep;

    balance = balance + dep;
    cout << "\nYour current balance is :" << balance << endl;
}

void account::withdraw_money()
{
    float wd;
    cout << "\nEnter amount you want to withdraw :" << endl;
    cin >> wd;

    balance = balance - wd;
    cout << "\nYour remaining balance is:" << balance << endl;
}

void account::display_account()
{
    cout<<"\nAccount Nhumber :"<<acno<<endl;
    cout << "\nName of Account Holder :" << name << endl;
    cout << "\nFather Name :" << fathername << endl;
    cout << "\n Address :" << address << endl;
    cout << "\nType of Account :" << type << endl;
    cout << "\nCurrent/Total Balance" << balance << endl;
}

void account::modify_account()
{
    cout<<"\nAccount no :"<<acno;
    cout<<"\nModify Account Holder Name :";
    cin.ignore();
    cin.getline(name,100);
    cout<<"\nModify Type of Account :";
    cin>>type;
    cin.getline(type,10);
    cout<<"\nModify Account Balance :";
    cin>>balance;
}

int account::retacno() const
{
    return acno;
}

void account::report() const
{
    cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<balance<<endl;
}  


void account:: write_account()
{
    account ac;
    ofstream outFile;
    outFile.open("account.dat"); //Generic data file 
    ac.open_account();
    outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
    outFile.close();
}

void account::display_sp(int n)
{
    account ac;
    bool flag=false;
    ifstream inFile;
    inFile.open("account.dat");
    if(!inFile)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    cout<<"\nBALANCE DETAILSn";
        while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
    {
        if(ac.retacno()==n)
        {
            ac.display_account();
            flag=true;
        }
    }
    inFile.close();
    if(flag==false)
        cout<<"\n\nAccount number does not exist";
}

void account::modify_acc(int n)
{
    bool found=false;
    account ac;
    fstream File;
    File.open("account.dat");
    if(!File)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    while(!File.eof() && found==false)
    {
        File.read(reinterpret_cast<char *> (&ac), sizeof(account));
        if(ac.retacno()==n)
        {
            ac.display_account();
            cout<<"\n\nEnter The New Details of account"<<endl;
            ac.modify_account();
            int pos=(-1)*static_cast<int>(sizeof(account));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *> (&ac), sizeof(account));
            cout<<"\n\n\t Record Updated";
            found=true;
          }
    }
    File.close();
    if(found==false)
        cout<<"\n\n Record Not Found ";
}

void account::delete_account(int n)
{
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat");
    if(!inFile)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    outFile.open("Temp.doc");
    inFile.seekg(0,ios::beg);
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
    {
        if(ac.retacno()!=n)
        {
            outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.doc","account.dat");
    cout<<"\n\n\tRecord Deleted ..";
}



int main()
{
    account b;
    int ch,num;
    char option;

    cout << "\n<------------------------------------------------------>" << endl;
    cout << "\n<----------------Welcome to our services--------------->" << endl;
    cout << "\n<------------------------------------------------------>" << endl;
    do
    {
        system("cls");
        cout<<"\nMain Menu";
        cout << "\n1.) Open Account" << endl;
        cout << "\n2.) Deposit Money" << endl;
        cout << "\n3.) Withdraw Money" << endl;
        cout << "\n4.) Balance Enquiry"<<endl;
        cout << "\n5.) Close Account" << endl;
        cout << "\n6.) Modify Existing Account" << endl;
        cout << "\n7.) Exit"<<endl;
        cout << "\n Select your option in (1-8)"<<endl;  

        cin >> ch;
        system("cls");
        switch (ch)
        {
        case 1:
            cout << "\n1.) Open Account" << endl;
            b.open_account();
            break;
        case 2:
            cout << "\n2.) Deposit Money" << endl;
            b.deposit_money();
            break;
        case 3:
            cout << "\n3.) Withdraw Money" << endl;
            b.withdraw_money();
            break;
        case 4:
            cout << "\n4.) Display Account" << endl;
            cout<<"\nEnter account number"<<endl;
            cin>>num;
            b.display_account();
            break;
        case 6:
            cout<<"\nEnter account number to delete :"<<endl;
            cin>>num;
            b.delete_account(num);
            break;
        case 7:
            cout<<"\nEnter account number to modify accout :"<<endl;
            cin>>num;
            b.modify_account();
        case 8:
            if (ch == 8)
            {
                exit(1);
            }
        default:
            cout << "\nPlease Try again and choose correct option !" << endl;
            break;
        }
        cout << "\n Do you want to continue banking without exit? Press(Y/N) !" << endl;
        option = getch();

        if ((option == 'n') || (option == 'N'))
        {
            exit(0);
        }
    }while (option == 'y' || option == 'Y');
    return 0;
}
