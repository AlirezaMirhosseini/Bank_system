//   BY   : Shapour Discover
//   DATE : 2021-06-07
//   TIME : 23:39
//   
//   Notes:
//
//   1.Boss.username is "shapourdisco" and Boss.password is "alireza8020"
//   2.Enter the amounts in thousands of dollars due to high profit
//   3.To enter the option, you can use its number or the full name of that
//   4.It doesn't matter if you enter option in lowercase or UPPERCASE
//   5.To work properly with the files, you must first log in with 
//   the boss account and create several banks and add several managers to each
//   And create several accounts for clients and the manager agrees with it

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <ctime>
#include <Windows.h>
#include <conio.h>

#pragma warning(disable:4996)

using namespace std;

time_t enter_time = time(0);
struct tm* Enter_Time = localtime(&enter_time);
struct Date {
	int day;
	int month;
	int year;
};
struct Accounts {
	string account_number;
	string owner_username;
	Date open_account;
	int account_type;
	bool requested;
	bool blocked;
	long long int cash;
	long long int debt;
	string bank_name;
	Accounts* next;
};
struct Debt {
	long long int amount;
	string bank_name;
	Date debt_date;
	Date accept_date;
	bool requested;
	int installment_count;
	int remain_installments;
	string recipient_account;
	string payer_account;
};
struct Clients {
	string name;
	string username;
	string password;
	string national_code;
	Debt loan;
	Accounts* account;
	Clients* next;
};
struct Managers {
	string username;
	string password;
	string bank_name;
	Managers* next;
};
struct Banks {
	string name;
	Managers* Manager;
	int found_year;
	Banks* next;
};
void set_Font_Size(int a, int b);
string to_Lower_Case(string str);
string take_password(char character);
void Show_Time();
void Show_Logo();
void Read_File();
void Show_Menu();
void Login_Menu();
void Create_New_client_Menu();
bool IsLeapYear(int _year);
int GetDays(int _year, int _month, int _day);
void Boss_Menu();
void Manager_Menu(int bank_num, int manager_num);
void Client_Menu(int client_num);
void client_accounts(int client_num);
void Exit();
Banks* bank = new Banks;
Clients* client = new Clients;
int main() {
	Show_Logo();
	return 0;
}
void set_Font_Size(int a, int b) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
	lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(hStdOut, 0, lpConsoleCurrentFontEx);
	lpConsoleCurrentFontEx->dwFontSize.X = a;
	lpConsoleCurrentFontEx->dwFontSize.Y = b;
	SetCurrentConsoleFontEx(hStdOut, 0, lpConsoleCurrentFontEx);
}
string to_Lower_Case(string str) {
	int str_len = str.length();
	string final_str = "";
	for (int i = 0; i < str_len; i++) {
		char character = str[i];
		if (character >= 65 && character <= 92)
			final_str += (character + 32);
		else
			final_str += character;
	}
	return final_str;
}
string take_password(char character = '*') {
	string password = "";
	char input_character;
	while (8020) {
		input_character = getch();
		if (input_character == '\r') {
			cout << endl;
			return password;
		}
		else if (input_character == '\b' && password.length() != 0) {
			password.pop_back();
			cout << "\b \b";
			continue;
		}
		else if (input_character == '\b' && password.length() == 0)
			continue;
		password.push_back(input_character);
		cout << character;
	}
}
bool IsLeapYear(int _year) {
	if (_year % 400 == 0 || (_year % 4 == 0) && (_year % 100 != 0))
		return true;
	return false;
}
int GetDays(int _year, int _month, int _day) {
	int monthDayCount[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (IsLeapYear(_year))
		monthDayCount[1]++;
	int days = 0;
	for (int i = 1973; i < _year; i++) {
		if (IsLeapYear(i))
			days += 366;
		else
			days += 365;
	}
	for (int i = 1; i <= 12; i++)
		if (_month == i) {
			for (int j = 0; j < i - 1; j++)
				days += monthDayCount[j];
			break;
		}
	days += _day;
	return days;
}
void Show_Time() {
	cout << "  ";
	time_t now = time(0);
	struct tm* Now = localtime(&now);
	if (Now->tm_hour < 10)
		cout << "0" << Now->tm_hour;
	else
		cout << Now->tm_hour;
	cout << ":";
	if (Now->tm_min < 10)
		cout << "0" << Now->tm_min;
	else
		cout << Now->tm_min;
	cout << ":";
	if (Now->tm_sec < 10)
		cout << "0" << Now->tm_sec;
	else
		cout << Now->tm_sec;
	cout << "     ";
	cout << Now->tm_year + 1900;
	cout << "-";
	if (Now->tm_mon + 1 < 10)
		cout << "0" << Now->tm_mon + 1;
	else
		cout << Now->tm_mon + 1;
	cout << "-";
	if (Now->tm_mday < 10)
		cout << "0" << Now->tm_mday;
	else
		cout << Now->tm_mday;
}
void Show_Logo() {
	system("cls");
	system("color 31");
	set_Font_Size(250, 250);
	cout << "\n Bank System\n";
	Read_File();
	Sleep(4000);
	Show_Menu();
}
void Show_Menu() {
	system("cls");
	system("color 72");
	set_Font_Size(25, 25);
	time_t now = time(0);
	struct tm* Now = localtime(&now);
	cout << "  ";
	Show_Time();
	cout << "                    In the name of GOD\n\n";
	cout << "    << Alireza Mirhosseini >>                                               $$ SHAPOUR DISCOVER $$\n\n";
	cout << "    1.Login\n    2.New Client\n    0.Exit\n\n\n Input : ";
	string input;
	do {
		getline(cin, input);
	} while (to_Lower_Case(input) != "login" &&
		input != "1" &&
		to_Lower_Case(input) != "new client" &&
		input != "2" &&
		to_Lower_Case(input) != "exit" && input != "0");
	if (to_Lower_Case(input) == "login" || input == "1")
		Login_Menu();
	else if (to_Lower_Case(input) == "new client" || input == "2")
		Create_New_client_Menu();
	else if (to_Lower_Case(input) == "exit" || input == "0")
		Exit();
}
void Login_Menu() {
	system("cls");
	system("color ec");
	set_Font_Size(25, 25);
	Show_Time();
	cout << "\n\n  1.Boss login\n  2.Managers login\n  3.Clients login\n  4.Back\n\n\n Input : ";
	string input;
	do { getline(cin, input); } while (to_Lower_Case(input) != "boss login" &&
		input != "1" &&
		to_Lower_Case(input) != "managers login" &&
		input != "2" &&
		to_Lower_Case(input) != "clients login" &&
		input != "3" &&
		to_Lower_Case(input) != "back" &&
		input != "4");
	if (to_Lower_Case(input) == "back" || input == "4")
		Show_Menu();
	cout << "\n\n\n Enter your username : ";
	string _username, _password;
	getline(cin, _username);
	cout << " Enter your password : ";
	_password = take_password();
	if (to_Lower_Case(input) == "boss login" || input == "1") {
		if (_username == "shapourdisco" && _password == "alireza8020")
			Boss_Menu();
		else {
			cout << "\n Invalid!\n";
			cin.ignore();
			Sleep(1500);
			Login_Menu();
		}
	}
	else if (to_Lower_Case(input) == "managers login" || input == "2") {
		int bank_num = 0, manager_num = 0;
		bool found_manager = 0;
		for (Banks* B_node = bank; B_node != NULL; B_node = B_node->next, bank_num++) {
			manager_num = 0;
			for (Managers* M_node = B_node->Manager; M_node != NULL; M_node = M_node->next, manager_num++)
				if (M_node->username == _username && M_node->password == _password) {
					found_manager = 1;
					break;
				}
			if (found_manager)
				break;
		}
		if (found_manager)
			Manager_Menu(bank_num, manager_num);
		else {
			cout << "\n Manager not found!\n";
			Sleep(1500);
			Login_Menu();
		}
	}
	else if (to_Lower_Case(input) == "clients login" || input == "3") {
		int client_num = 0;
		bool found_client = 0;
		for (Clients* C_node = client; C_node != NULL; C_node = C_node->next, client_num++) {
			if (C_node->username == _username && C_node->password == _password) {
				found_client = 1;
				break;
			}
		}
		if (found_client)
			Client_Menu(client_num);
		else {
			cout << "\n Client not found!\n";
			Sleep(1500);
			Login_Menu();
		}
	}
	else {
		Sleep(1500);
		Login_Menu();
	}
}
void Create_New_client_Menu() {
	system("cls");
	system("color f9");
	set_Font_Size(25, 25);
	Clients* last_client = client;
	Clients* C_node = new Clients;
	cout << "\n Enter your Fullname       : ";
	getline(cin, C_node->name);
	cout << " Enter your Username       : ";
	cin >> C_node->username;
	cout << " Enter your National code  : ";
	cin >> C_node->national_code;
	string str1, str2;
	do {
		cout << " Enter your Password       : ";
		str1 = take_password();
		cout << " Enter your Password again : ";
		str2 = take_password();
		if (str1 != str2)
			cout << " \n\n   Error!!! Passwords must be the same    :((    try again\n\n" << endl;
	} while (str1 != str2);
	C_node->password = str1;
	C_node->loan.requested = 0;
	C_node->loan.remain_installments = 0;
	C_node->account = NULL;
	C_node->next = NULL;
	if (client == NULL) {
		client = C_node;
	}
	else {
		for (; last_client->next != NULL; last_client = last_client->next);
		last_client->next = C_node;
	}
	Login_Menu();
}
void Boss_Menu() {
	system("cls");
	system("color 61");
	set_Font_Size(25, 25);
	cout << "\n";
	Show_Time();
	cout << "                                     Hello Boss !\n\n" << endl;
	cout << "     1.Add Bank\n";
	cout << "     2.Add Manager to a Bank\n";
	cout << "     3.List of Banks\n";
	cout << "     4.Hired Managers in a bank\n";
	cout << "     5.back\n";
	cout << "     0.Exit\n\n\n";
	cout << "  Command : ";
	string command;
	getline(cin, command);
	if (command == "1" || to_Lower_Case(command) == "add bank") {
		system("cls");
		Banks* last_bank = bank;
		Banks* B_node = new Banks;
		cout << "\n Enter name of the Bank   : ";
		cin >> B_node->name;
		cout << " Enter its Establish year : ";
		cin >> B_node->found_year;
		B_node->Manager = NULL;
		B_node->next = NULL;
		if (bank == NULL)
			bank = B_node;
		else {
			for (; last_bank->next != NULL; last_bank = last_bank->next);
			last_bank->next = B_node;
		}
		cout << "\n  Bank added successfully! now add it manager!!!";
		cin.ignore();
		Sleep(3000);
		Boss_Menu();
	}
	else if (command == "2" || to_Lower_Case(command) == "add manager to a bank") {
		system("cls");
		Show_Time();
		cout << endl;
		Banks* B_Node = bank;
		for (int i = 0; B_Node != NULL; B_Node = B_Node->next, i++)
			cout << " " << i + 1 << "." <<
			B_Node->name << "          Founded in " <<
			B_Node->found_year << endl;
		cout << "\n Which bank do you want to add a manager to ? (Enter name of the Bank) : ";
		string B_name;
		cin >> B_name;
		bool B_found = 0;
		Banks * B_node = bank;
		for (; B_node != NULL; B_node = B_node->next) {
			if (B_name == B_node->name) {
				B_found = true;
				break;
			}
		}
		if (B_found) {
			Managers* last_manager = B_node->Manager;
			Managers* M_node = new Managers;
			cout << " Enter Username of manager : ";
			cin >> M_node->username;
			string str1, str2;
			do {
				cout << " Enter Password of manager : ";
				str1 = take_password();
				cout << " Enter the Password again  : ";
				str2 = take_password();
				if (str1 != str2)
					cout << " \n\n   Error!!! Passwords must be the same    :((    try again\n\n" << endl;
			} while (str1 != str2);
			M_node->password = str1;
			M_node->bank_name = B_node->name;
			M_node->next = NULL;
			if (B_node->Manager == NULL)
				B_node->Manager = M_node;
			else {
				for (; last_manager->next != NULL; last_manager = last_manager->next);
				last_manager->next = M_node;
			}
			cout << "\n\n   Manager added successfully!\n\n";
		}
		else
			cout << " Not found!\n\n";
		cin.ignore();
		Sleep(3000);
		Boss_Menu();
	}
	else if (command == "3" || to_Lower_Case(command) == "list of banks") {
		system("cls");
		cout << "\n\n  ";
		Show_Time();
		cout << endl;
		Banks* B_node = bank;
		for (int i = 0; B_node != NULL; B_node = B_node->next, i++)
			cout << " " << i + 1 << "." <<
			B_node->name << "          Founded in " <<
			B_node->found_year << endl;
		cout << "\n\n 0.Back\n\n Command : ";
		string command;
		do { cin >> command; } while (command != "0" && to_Lower_Case(command) != "back");
		if (command == "0" || to_Lower_Case(command) == "back")
			Boss_Menu();
	}
	else if (command == "4" || to_Lower_Case(command) == "hired managers in a bank") {
		system("cls");
		cout << "\n Enter name of the bank : ";
		string B_name;
		cin >> B_name;
		bool B_found = 0;
		Banks* B_node = bank;
		for (; B_node != NULL; B_node = B_node->next) {
			if (B_name == B_node->name) {
				B_found = true;
				break;
			}
		}
		if (B_found) {
			Managers* the_manager = B_node->Manager;
			for (int i = 0; the_manager != NULL; the_manager = the_manager->next, i++) {
				cout << " " << i + 1 << "." <<
					the_manager->username << "          " <<
					the_manager->bank_name << endl;
			}
		}
		else
			cout << " Not found!\n";
		cin.ignore();
		Sleep(3000);
		Boss_Menu();
	}
	else if (command == "5" || to_Lower_Case(command) == "back")
		Login_Menu();
	else if (command == "0" || to_Lower_Case(command) == "exit")
		Exit();
	else {
		cout << "\n\n Invalid!";
		//cin.ignore();
		Sleep(1500);
		Boss_Menu();
	}
}
void Manager_Menu(int bank_num, int manager_num) {
	system("cls");
	system("color 8b");
	set_Font_Size(25, 25);
	Banks* B_node = bank;
	for (int i = 0; i < bank_num; i++)
		B_node = B_node->next;
	Managers * the_manager = B_node->Manager;
	for (int i = 0; i < manager_num; i++)
		the_manager = the_manager->next;
	cout << "\n                                    Hello " << the_manager->username << " Welcome !" << endl;
	Show_Time();
	cout << "\n\n";
	cout << " Employed in " << the_manager->bank_name << " bank.\n" << endl;
	cout << "     1.Account creation requests\n";
	cout << "     2.Loan requests\n";
	cout << "     3.Back\n";
	cout << "     0.Exit\n";
	cout << "\n Command : ";
	string command;
	getline(cin, command);
	if (to_Lower_Case(command) == "exit" || command == "0")
		Exit();
	else if (to_Lower_Case(command) == "back" || command == "3")
		Login_Menu();
	else if (to_Lower_Case(command) == "account creation requests" || command == "1") {
		int i = 0;
		string type[3] = { "Short term","Long term","Special" };
		for (Clients* C_node = client; C_node != NULL; C_node = C_node->next)
			for (Accounts* C_A_node = C_node->account; C_A_node != NULL; C_A_node = C_A_node->next)
				if (C_A_node->requested && C_A_node->bank_name == the_manager->bank_name) {
					i++;
					cout << " " << i << "." <<
						C_A_node->owner_username << "    Inventory:" <<
						C_A_node->cash << "    Type:" <<
						type[C_A_node->account_type - 1] << endl;
					break;
				}
		if (i) {
			cout << "\n\n Choose a username for allowing : ";
			string C_username;
			cin >> C_username;
			bool C_allowed = 0;
			Clients* C_node = client;
			Accounts* C_A_node = C_node->account;
			for (C_node = client; C_node != NULL; C_node = C_node->next) {
				for (C_A_node = C_node->account; C_A_node != NULL; C_A_node = C_A_node->next)
					if (C_node->username == C_username && C_A_node->requested) {
						C_A_node->requested = 0;
						C_allowed = 1;
						break;
					}
				if (C_allowed)
					break;
			}
			if (C_allowed) {
				C_A_node->account_number = "6037";
				srand(time(0));
				for (int i = 0; i < 12; i++)
					C_A_node->account_number += (rand() % 10) + 48;
				cout << "\n\n Account number is : " <<
					C_A_node->account_number[0] <<
					C_A_node->account_number[1] <<
					C_A_node->account_number[2] <<
					C_A_node->account_number[3] << "-" <<
					C_A_node->account_number[4] <<
					C_A_node->account_number[5] <<
					C_A_node->account_number[6] <<
					C_A_node->account_number[7] << "-" <<
					C_A_node->account_number[8] <<
					C_A_node->account_number[9] <<
					C_A_node->account_number[10] <<
					C_A_node->account_number[11] << "-" <<
					C_A_node->account_number[12] <<
					C_A_node->account_number[13] <<
					C_A_node->account_number[14] <<
					C_A_node->account_number[15] << endl;
				cout << "\n    Account added successfully  :))";
				cin.ignore();
				Sleep(3000);
				Manager_Menu(bank_num, manager_num);
			}
			else {
				cout << "\n\n    Invalid  :((  try again...";
				cin.ignore();
				Sleep(3000);
				Manager_Menu(bank_num, manager_num);
			}
		}
		else {
			system("cls");
			cout << "\n\n There is no request!\n\n";
			cout << " 0.Back\n\n";
			cout << " Command : ";
			string cmd;
			do {
				cin >> cmd;
			} while (cmd != "0" && to_Lower_Case(cmd) != "back");
			cin.ignore();
			Manager_Menu(bank_num, manager_num);
		}
	}
	else if (to_Lower_Case(command) == "loan requests" || command == "2") {
		system("cls");
		int i = 0;
		Show_Time();
		time_t LOAN = time(0);
		struct tm* loan = localtime(&LOAN);
		cout << "\n\n";
		for (Clients* C_node = client; C_node != NULL; C_node = C_node->next) {
			if (C_node->loan.requested && C_node->loan.bank_name == the_manager->bank_name) {
				i++;
				cout << " " << i << "." << C_node->username <<
					"\n   Amount of the loan : " << C_node->loan.amount <<
					"\n   Reciever account   : " << C_node->loan.recipient_account <<
					"\n   Payer account      : " << C_node->loan.payer_account <<
					"\n   Request date       : " <<
					C_node->loan.debt_date.year << "-" <<
					C_node->loan.debt_date.month << "-" <<
					C_node->loan.debt_date.day <<
					"\n   Installment number : " << C_node->loan.installment_count << endl;
			}
		}
		if (!i) {
			cout << " There is no request!\n\n";
			cout << " 0.Back\n\n";
			cout << " Command : ";
			string cmd;
			do {
				cin >> cmd;
			} while (cmd != "0" && to_Lower_Case(cmd) != "back");
			cin.ignore();
			Manager_Menu(bank_num, manager_num);
		}
		cout << "\n Choose a username for allowing : ";
		string L_username;
		cin >> L_username;
		Clients* Client_node = client;
		for (Client_node = client; Client_node != NULL; Client_node = Client_node->next) {
			if (L_username == Client_node->username) {
				Client_node->loan.requested = 0;
				Accounts* R_L_account = Client_node->account;
				for (R_L_account = Client_node->account; R_L_account != NULL; R_L_account = R_L_account->next)
					if (R_L_account->account_number == Client_node->loan.recipient_account)
						break;
				R_L_account->cash += Client_node->loan.amount;
				Client_node->loan.accept_date.year = loan->tm_year + 1900;
				Client_node->loan.accept_date.month = loan->tm_mon + 1;
				Client_node->loan.accept_date.day = loan->tm_mday;
			}
		}
		cout << "\n\n              Loan was given successfully! ";
		cin.ignore();
		Sleep(2000);
		Manager_Menu(bank_num, manager_num);
	}
	else {
		cout << "\n\n Invalid!";
		Sleep(2000);
		Manager_Menu(bank_num, manager_num);
	}
}
void Client_Menu(int client_num) {
	system("cls");
	system("color 71");
	set_Font_Size(20, 20);
	Clients* this_client = client;
	for (int i = 0; i < client_num; i++)
		this_client = this_client->next;
	Accounts * last_account = this_client->account;
	for (Accounts* my_account = this_client->account; my_account != NULL; my_account = my_account->next) {
		if (my_account->blocked) {
			if (my_account->cash >= my_account->debt) {
				my_account->cash -= my_account->debt;
				my_account->debt = 0;
				my_account->blocked = 0;
			}
			else {
				my_account->debt -= my_account->cash;
				my_account->cash = 0;
			}
			break;
		}
	}
	cout << "\n\n\n    Hello " << this_client->name <<
		" , welcome!" << "      ";
	Show_Time();
	cout << "\n\n   1.Create Account\n";
	cout << "   2.My Accounts\n";
	cout << "   3.Withdraw funds\n";
	cout << "   4.Deposit money\n";
	cout << "   5.Transfer funds\n";
	cout << "   6.Applying for loan\n";
	cout << "   7.Back\n";
	cout << "   0.Exit\n";
	cout << "\n\n Command : ";
	string command;
	getline(cin, command);
	if (to_Lower_Case(command) == "exit" || command == "0")
		Exit();
	else if (to_Lower_Case(command) == "create account" || command == "1") {
		system("cls");
		time_t Create_account = time(0);
		struct tm* create_account = localtime(&Create_account);
		bool B_A_node = 0;
		for (Accounts* client_A_node = this_client->account; client_A_node != NULL; client_A_node = client_A_node->next)
			if (client_A_node->blocked) {
				B_A_node = 1;
				break;
			}
		if (B_A_node) {
			cout << "\n Sorry you have a blocked account!   :((";
			Sleep(3000);
			Client_Menu(client_num);
		}
		if (!B_A_node) {
			cout << endl;
			Banks* B_Node = bank;
			for (int i = 0; B_Node != NULL; B_Node = B_Node->next, i++)
				cout << " " << i + 1 << "." <<
				B_Node->name << "          Founded in " <<
				B_Node->found_year << endl;
			Accounts * C_A_node = new Accounts;
			cout << "\n Which bank do you want to create an account in ? (name of bank) : ";
			bool B_found = 0;
			do {
				cin >> C_A_node->bank_name;
				for (Banks* B_node = bank; B_node != NULL; B_node = B_node->next)
					if (C_A_node->bank_name == B_node->name) {
						B_found = 1;
						break;
					}
				if (!B_found)
					cout << "\n\n Bank not found!   try again : ";
			} while (!B_found);
			cout << " How much money do you want to deposit into your account ?       : ";
			cin >> C_A_node->cash;
			cout << " Type (1.Short term, 2.Long term, 3.Special ..Enter its number ) : ";
			cin >> C_A_node->account_type;
			C_A_node->blocked = 0;
			C_A_node->open_account.year = create_account->tm_year + 1900;
			C_A_node->open_account.month = create_account->tm_mon + 1;
			C_A_node->open_account.day = create_account->tm_mday;
			C_A_node->requested = 1;
			C_A_node->debt = 0;
			C_A_node->owner_username = this_client->username;
			C_A_node->next = NULL;
			if (this_client->account == NULL)
				this_client->account = C_A_node;
			else {
				for (; last_account->next != NULL; last_account = last_account->next);
				last_account->next = C_A_node;
			}
			cout << "\n Creation request was sent for bank managers!";
			cin.ignore();
			Sleep(3000);
			Client_Menu(client_num);
		}
	}
	else if (to_Lower_Case(command) == "my accounts" || command == "2") {
		client_accounts(client_num);
		cout << "\n\n 0.Back\n";
		string command_A;
		cout << "\n Command : ";
		cin >> command_A;
		cin.ignore();
		if (command_A == "0" || to_Lower_Case(command_A) == "back")
			Client_Menu(client_num);
	}
	else if (to_Lower_Case(command) == "withdraw funds" || command == "3") {
		bool B_A_node = 0;
		for (Accounts* client_A_node = this_client->account; client_A_node != NULL; client_A_node = client_A_node->next)
			if (client_A_node->blocked) {
				B_A_node = 1;
				break;
			}
		if (B_A_node) {
			cout << "\n Sorry you have a blocked account!   :((";
			Sleep(3000);
			Client_Menu(client_num);
		}
		if (!B_A_node) {
			client_accounts(client_num);
			cout << "\n\n  Choose one of your accounts (Enter the account number) : ";
			string A_number;
			cin >> A_number;
			Accounts* the_account = this_client->account;
			bool A_found = 0;
			for (; the_account != NULL; the_account = the_account->next)
				if (A_number == the_account->account_number) {
					A_found = 1;
					break;
				}
			if (A_found) {
				cout << "\n How much money do you want to withdraw from your account ?       : ";
				int W_money;
				do {
					cin >> W_money;
					if (W_money > the_account->cash)
						cout << "\n Entered amount is not available in your account! try again : ";
				} while (W_money > the_account->cash);
				the_account->cash -= W_money;
				cout << "\n Withdrawed!  Have a good day...\n";
				cin.ignore();
				Sleep(3000);
				Client_Menu(client_num);
			}
			else {
				cout << "\n Account not found!\n";
				cin.ignore();
				Sleep(3000);
				Client_Menu(client_num);
			}
		}
	}
	else if (to_Lower_Case(command) == "deposit money" || command == "4") {
		client_accounts(client_num);
		cout << "\n\n  Choose one of your accounts (Enter the account number) : ";
		string A_number;
		cin >> A_number;
		Accounts* the_account = this_client->account;
		bool A_found = 0;
		for (; the_account != NULL; the_account = the_account->next)
			if (A_number == the_account->account_number) {
				A_found = 1;
				break;
			}
		if (A_found) {
			cout << "\n How much money do you want to deposit into your account ?       : ";
			int D_money;
			cin >> D_money;
			the_account->cash += D_money;
			cout << "\n Deposited!  Have a good day...\n";
			cin.ignore();
			Sleep(3000);
			Client_Menu(client_num);
		}
		else {
			cout << "\n Account not found!\n";
			cin.ignore();
			Sleep(3000);
			Client_Menu(client_num);
		}
	}
	else if (to_Lower_Case(command) == "transfer funds" || command == "5") {
		bool B_A_node = 0;
		for (Accounts* client_A_node = this_client->account; client_A_node != NULL; client_A_node = client_A_node->next)
			if (client_A_node->blocked) {
				B_A_node = 1;
				break;
			}
		if (B_A_node) {
			cout << "\n Sorry you have a blocked account!   :((";
			Sleep(3000);
			Client_Menu(client_num);
		}
		if (!B_A_node) {
			client_accounts(client_num);
			cout << "\n\n  Choose one of your accounts (Enter the account number) : ";
			string A_number;
			cin >> A_number;
			Accounts* sender_account = this_client->account;
			bool A_found = 0;
			for (; sender_account != NULL; sender_account = sender_account->next)
				if (A_number == sender_account->account_number) {
					A_found = 1;
					break;
				}
			if (A_found) {
				cout << "\n How much money do you want to withdraw from your account ?       : ";
				int W_money;
				do {
					cin >> W_money;
					if (W_money > sender_account->cash)
						cout << "\n Entered amount is not available in your account! try again...\n";
				} while (W_money > sender_account->cash);
				sender_account->cash -= W_money;
				string recipient_account_number;
				Clients* C_node = client;
				Accounts* C_A_node = C_node->account;
				do {
					cout << "\n Enter recipient account number : ";
					cin >> recipient_account_number;
					bool A_found = 0;
					for (C_node = client; C_node != NULL; C_node = C_node->next) {
						for (C_A_node = C_node->account; C_A_node != NULL; C_A_node = C_A_node->next)
							if (C_A_node->account_number == recipient_account_number) {
								A_found = 1;
								break;
							}
						if (A_found)
							break;
					}
					if (!A_found)
						cout << "\n Account not found! try again...\n";
				} while (!A_found);
				C_A_node->cash += W_money;
				cout << "\n Transfered!  Have a good day...\n";
				cin.ignore();
				Sleep(3000);
				Client_Menu(client_num);
			}
			else {
				cout << "\n Account not found!\n";
				cin.ignore();
				Sleep(3000);
				Client_Menu(client_num);
			}
		}
	}
	else if (to_Lower_Case(command) == "applying for loan" || command == "6") {
		time_t now = time(0);
		struct tm* Now = localtime(&now);
		bool B_A_node = 0;
		for (Accounts* client_A_node = this_client->account; client_A_node != NULL; client_A_node = client_A_node->next)
			if (client_A_node->blocked) {
				B_A_node = 1;
				break;
			}
		if (B_A_node) {
			cout << "\n Sorry you have a blocked account!   :((";
			Sleep(3000);
			Client_Menu(client_num);
		}
		if (!B_A_node) {
			client_accounts(client_num);
			cout << "\n\n";
			bool B_found = 0;
			do {
				cout << " Enter name of the bank               : ";
				cin >> this_client->loan.bank_name;
				for (Banks* B_node = bank; B_node != NULL; B_node = B_node->next)
					if (B_node->name == this_client->loan.bank_name) {
						B_found = 1;
						break;
					}
				if (!B_found)
					cout << " Bank not found!   try again...";
			} while (!B_found);
			cout << " Enter the amount of loan             : ";
			cin >> this_client->loan.amount;
			cout << " Enter number of installment          : ";
			cin >> this_client->loan.installment_count;
			this_client->loan.remain_installments = this_client->loan.installment_count;
			this_client->loan.requested = 1;
			this_client->loan.debt_date.year = Now->tm_year + 1900;
			this_client->loan.debt_date.month = Now->tm_mon + 1;
			this_client->loan.debt_date.day = Now->tm_mday;
			bool P_found = 0;
			bool R_found = 0;
			string P_account;
			string R_account;
			do {
				cout << " Enter Payer account (account number) : ";
				cin >> P_account;
				cout << " Enter the Recipient account          : ";
				cin >> R_account;
				for (Accounts* A_node = this_client->account; A_node != NULL; A_node = A_node->next) {
					if (P_account == A_node->account_number)
						P_found = 1;
					if (R_account == A_node->account_number)
						R_found = 1;
				}
				if (!P_found || !R_found)
					cout << " Wrong!!!  Enter accounts again...";
			} while (!P_found || !R_found);
			this_client->loan.payer_account = P_account;
			this_client->loan.recipient_account = R_account;
			cout << "\n\n Request was sent for managers!";
			cin.ignore();
			Sleep(1500);
			Client_Menu(client_num);
		}
	}
	else if (to_Lower_Case(command) == "back" || command == "7")
		Login_Menu();
	else {
		cout << "\n\n Invalid!";
		Sleep(1500);
		Client_Menu(client_num);
	}
}
void client_accounts(int client_num) {
	system("cls");
	system("color bd");
	set_Font_Size(20, 20);
	Clients* this_client = client;
	for (int i = 0; i < client_num; i++)
		this_client = this_client->next;
	string type[3] = { "Short term","Long term","Special" };
	Show_Time();
	cout << endl;
	Accounts * the_account = this_client->account;
	for (int i = 0; the_account != NULL; the_account = the_account->next, i++)
		if (!the_account->requested) {
			cout << " " << i + 1 << '.' <<
				type[the_account->account_type - 1];
			if (the_account->account_type == 2)
				cout << " ";
			if (the_account->account_type == 3)
				cout << "   ";
			cout << "    Account Number:" <<
				the_account->account_number[0] <<
				the_account->account_number[1] <<
				the_account->account_number[2] <<
				the_account->account_number[3] << "-" <<
				the_account->account_number[4] <<
				the_account->account_number[5] <<
				the_account->account_number[6] <<
				the_account->account_number[7] << "-" <<
				the_account->account_number[8] <<
				the_account->account_number[9] <<
				the_account->account_number[10] <<
				the_account->account_number[11] << "-" <<
				the_account->account_number[12] <<
				the_account->account_number[13] <<
				the_account->account_number[14] <<
				the_account->account_number[15] <<
				"    Inventory:" << the_account->cash <<
				"    Account creation date:" << the_account->open_account.year <<
				"-" << the_account->open_account.month <<
				"-" << the_account->open_account.day << "    Bank:" << the_account->bank_name;
			if (the_account->blocked)
				cout << "    Blocked\n";
			else
				cout << '\n';
		}
}
void Read_File() {
	int C_size = 0;
	int C_A_size = 0;
	ifstream clients_file;
	clients_file.open("Clients.txt", ios::in);
	clients_file >> C_size;
	client = NULL;
	for (int i = 0; i < C_size; i++) {
		Clients* C_node = new Clients;
		getline(clients_file, C_node->name);
		clients_file >> C_node->username;
		clients_file >> C_node->password;
		clients_file >> C_node->national_code;
		clients_file >> C_node->loan.remain_installments;
		clients_file >> C_node->loan.requested;
		if (C_node->loan.requested || C_node->loan.remain_installments > 0) {
			clients_file >> C_node->loan.amount;
			clients_file >> C_node->loan.installment_count;
			clients_file >> C_node->loan.payer_account;
			clients_file >> C_node->loan.recipient_account;
			clients_file >> C_node->loan.bank_name;
			clients_file >> C_node->loan.debt_date.year;
			clients_file >> C_node->loan.debt_date.month;
			clients_file >> C_node->loan.debt_date.day;
			clients_file >> C_node->loan.accept_date.year;
			clients_file >> C_node->loan.accept_date.month;
			clients_file >> C_node->loan.accept_date.day;
		}
		C_node->account = NULL;
		clients_file >> C_A_size;
		C_node->next = NULL;
		if (!C_A_size)
			C_node->account = NULL;
		for (int j = 0; j < C_A_size; j++) {
			Accounts* C_A_node = new Accounts;
			clients_file >> C_A_node->requested;
			if (!C_A_node->requested)
				clients_file >> C_A_node->account_number;
			clients_file >> C_A_node->owner_username;
			clients_file >> C_A_node->bank_name;
			clients_file >> C_A_node->account_type;
			clients_file >> C_A_node->cash;
			clients_file >> C_A_node->blocked;
			clients_file >> C_A_node->debt;
			clients_file >> C_A_node->open_account.year >>
				C_A_node->open_account.month >>
				C_A_node->open_account.day;
			C_A_node->next = NULL;
			if (C_node->account == NULL)
				C_node->account = C_A_node;
			else {
				Accounts* last_account = C_node->account;
				for (; last_account->next != NULL; last_account = last_account->next);
				last_account->next = C_A_node;
			}
		}
		if (client == NULL)
			client = C_node;
		else {
			Clients* last_client = client;
			for (; last_client->next != NULL; last_client = last_client->next);
			last_client->next = C_node;
		}
	}
	int B_size = 0;
	int B_M_size = 0;
	ifstream banks_file;
	banks_file.open("Banks.txt", ios::in);
	banks_file >> B_size;
	bank = NULL;
	for (int i = 0; i < B_size; i++) {
		Banks* B_node = new Banks;
		banks_file >> B_node->name;
		banks_file >> B_node->found_year;
		B_node->Manager = NULL;
		banks_file >> B_M_size;
		B_node->next = NULL;
		if (!B_M_size)
			B_node->Manager = NULL;
		for (int j = 0; j < B_M_size; j++) {
			Managers* B_M_node = new Managers;
			banks_file >> B_M_node->username;
			banks_file >> B_M_node->password;
			banks_file >> B_M_node->bank_name;
			B_M_node->next = NULL;
			if (B_node->Manager == NULL)
				B_node->Manager = B_M_node;
			else {
				Managers* last_manager = B_node->Manager;
				for (; last_manager->next != NULL; last_manager = last_manager->next);
				last_manager->next = B_M_node;
			}
		}
		if (bank == NULL)
			bank = B_node;
		else {
			Banks* last_bank = bank;
			for (; last_bank->next != NULL; last_bank = last_bank->next);
			last_bank->next = B_node;
		}
	}
	time_t now = time(0);
	struct tm* Now = localtime(&now);
	for (Clients* the_client = client; the_client != NULL; the_client = the_client->next) {
		for (Accounts* C_account = the_client->account; C_account != NULL; C_account = C_account->next) {
			int past_days = GetDays(Now->tm_year + 1900, Now->tm_mon + 1, Now->tm_mday) -
				GetDays(C_account->open_account.year, C_account->open_account.month, C_account->open_account.day);
			double profit = 0;
			if (C_account->account_type == 1)
				profit = 0.1;
			else if (C_account->account_type == 2)
				profit = 0.3;
			else if (C_account->account_type == 3)
				profit = 0.5;
			for (int i = 0; i < past_days; i++)
				C_account->cash += int(C_account->cash * profit);
		}
		if (!the_client->loan.requested && the_client->loan.remain_installments > 0) {
			int past_month = 0;
			if ((Now->tm_year + 1900) > (the_client->loan.accept_date.year))
				past_month += 12 - the_client->loan.accept_date.month;
			if ((Now->tm_year + 1900) > (the_client->loan.accept_date.year + 1))
				past_month += ((Now->tm_year + 1900) - (the_client->loan.accept_date.year + 1)) * 12;
			past_month += Now->tm_mon + 1;
			Accounts * C_A_node = the_client->account;
			for (C_A_node = the_client->account; C_A_node != NULL; C_A_node = C_A_node->next)
				if (C_A_node->account_number == the_client->loan.payer_account)
					break;
			while (past_month > the_client->loan.accept_date.month && the_client->loan.remain_installments > 0) {
				long long int this_cash = C_A_node->cash;
				this_cash -= (the_client->loan.amount / the_client->loan.installment_count);
				if (this_cash < 0) {
					C_A_node->blocked = 1;
					C_A_node->cash = 0;
					C_A_node->debt += (-1) * this_cash;
					break;
				}
				else {
					C_A_node->cash = this_cash;
				}
				past_month--;
				the_client->loan.remain_installments--;
			}
		}
	}
}
void Exit() {
	system("cls");
	system("color bd");
	set_Font_Size(422, 422);
	cout << "Bye\n\n\n\n\n";
	ofstream clients_file;
	clients_file.open("Clients.txt", ios::trunc);
	int counter = 0;
	for (Clients* C_node = client; C_node != NULL; C_node = C_node->next, counter++);
	clients_file << counter;
	while (client != NULL) {
		clients_file << client->name << '\n' <<
			client->username << " " <<
			client->password << " " <<
			client->national_code << '\n' <<
			client->loan.remain_installments << " " <<
			client->loan.requested << " ";
		if (client->loan.requested || client->loan.remain_installments > 0)
			clients_file << client->loan.amount << " " <<
			client->loan.installment_count << " " <<
			client->loan.payer_account << " " <<
			client->loan.recipient_account << " " <<
			client->loan.bank_name << " " <<
			client->loan.debt_date.year << " " <<
			client->loan.debt_date.month << " " <<
			client->loan.debt_date.day << " " <<
			client->loan.accept_date.year << " " <<
			client->loan.accept_date.month << " " <<
			client->loan.accept_date.day << " ";
		int account_count = 0;
		for (Accounts* A_node = client->account; A_node != NULL; A_node = A_node->next, account_count++);
		clients_file << account_count << " ";
		while (client->account != NULL) {
			clients_file << client->account->requested << " ";
			if (!client->account->requested)
				clients_file << client->account->account_number << " ";
			clients_file <<
				client->account->owner_username << " " <<
				client->account->bank_name << " " <<
				client->account->account_type << " " <<
				client->account->cash << " " <<
				client->account->blocked << " " <<
				client->account->debt << " " <<
				client->account->open_account.year << " " <<
				client->account->open_account.month << " " <<
				client->account->open_account.day << " ";
			client->account = client->account->next;
		}
		client = client->next;
	}
	ofstream banks_file;
	banks_file.open("Banks.txt", ios::trunc);
	counter = 0;
	for (Banks* B_node = bank; B_node != NULL; B_node = B_node->next, counter++);
	banks_file << counter;
	while (bank != NULL) {
		banks_file << bank->name << " " << bank->found_year << " ";
		int managers_count = 0;
		for (Managers* M_node = bank->Manager; M_node != NULL; M_node = M_node->next, managers_count++);
		banks_file << managers_count << " ";
		while (bank->Manager != NULL) {
			banks_file << bank->Manager->username << " " << bank->Manager->password << " " << bank->Manager->bank_name << " ";
			bank->Manager = bank->Manager->next;
		}
		bank = bank->next;
	}
	exit(0);
}