#include <windows.h>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h> 
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <vector>
#include <conio.h>
#include <ctime>
#include <iterator>
using namespace std;
HANDLE color=GetStdHandle(STD_OUTPUT_HANDLE); 

void gotoxy(short x, short y){
	COORD pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

struct shop{
	string ItemName; 
	float ItemPrice;
	short int ItemStock;
	
	short int OrdQuantity;
	string OrdDescription;
	float OrdPrice, Subtotal;
	
	short int sTotalItems;
	float sTotalAmount;
	time_t sMonth, sDay, sYear, sHour, sMin, sSec;
	
	
}p,c,o,s;

void Sales();
void DisplaySales();

class Menu{
	public:
	int opt, id;
	char YoN;
	void OrderMenu(); // Asks Customer what Menu Should Be the next to be Executed (Pastry Menu | Coffee Menu | Go Back Main Menu)
	void admin(); // Asks Admin what Menu Should Be next to be Executed (Add Menu | Update Menu | Delete Menu | Go Back Main Menu)
	void AddMenu();  // Asks Admin Whether add Menu on Pastry or Coffee Menu | or go back to Main Menu
	void UpdateMenu();  // Asks Admin Whether Update Menu on Pastry or Coffee Menu | or go back to Main Menu
	void DeleteMenu(); // Asks Admin Whether Delete Menu on Pastry or Coffee Menu | or go back to Main Menu
	void adminBack();  // Asks: Back to Main Menu?
}menu;

class Customer{
	public:
		float Change, CustomerCash, TotalPrice;
		int id, quantity;
		
		string ordDescription;
		short int ordQuantity;
		float ordPrice,subtotal;
		
		float OrderPastry();  // Menu for Customer Pastry Order
		float OrderCoffee(); //Menu for Customer Coffee Order
		void OrderOpt(); // Asks Customer if theres additional Order Or Continue to Pay
		float Payment(); // After OrderOpt Payment Before Reciept
		void DisplayCustomerOrder(float CustomerCash, float Change); // Display Customer Receipt
}customer;

class Pastry{
	public:
	string pName;
	float  pPrice;
	char YoN;
	int id, pStock;

	void DisplayMenuPastry(); // Displays Pastry Menu
	void AddMenuPastry(); // Adds New Pastry on the Menu
	void UpdateMenuPastry(int id);  // Update New Pastry on the Menu
	void DeleteMenuPastry(int id);  // Deletes New Pastry on the Menu
}pastry;

class Coffee{
	public:
	string cName;
	float  cPrice;
	char YoN;
	int id, cStock;

	void DisplayMenuCoffee(); // Displays Coffee Menu
	void AddMenuCoffee();  // Adds New Coffee on the Menu
	void UpdateMenuCoffee(int id);  // Update New Coffee on the Menu
	void DeleteMenuCoffee(int id);  // Deletes New Coffee on the Menu
}coffee;

void SplashScreen(); void welcome();
void border();
void cashoutDisply();
void head1(); void head2(); 


///////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
int main()  {
	system("cls");
	SplashScreen();
	welcome();

	int opt;
	gotoxy(45, 24);
	cout << "<1> Menu";
	gotoxy(45, 25);
	cout << "<2> Admin Settings ";
	gotoxy(45, 27);
	cout << "Enter an Option: ";
	cin >> opt;
	
	switch(opt){
		case 1:
			system("cls");
			menu.OrderMenu();
		break;
		
		case 2:
			system("cls");
			menu.admin();
		break;
		
		default:
			main();
		break;
	}
 }
///////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


///ORDER///START//*************************************************************************************///
///====ORDER==MENU===============================================================================//////
void Menu::OrderMenu(){
	head1();
	border();
	gotoxy(35, 14);
	cout << " What would you like to order: " << endl;
	gotoxy(35, 16);
	cout << " <1> Coffee " << endl;
	gotoxy(35, 17);
	cout << " <2> Pastry " << endl;
	gotoxy(35, 18);
	cout << " <3> Main Menu " << endl <<endl ;
	gotoxy(35, 19);
	cout << "Enter an Option: ";
	cin >> opt;
	
	switch(opt){
		case 1:
			system("cls");
			customer.OrderCoffee();
			break;
			
		case 2:
			system("cls");
			customer.OrderPastry();
			break;
			
		case 3:
			system("cls");
			main();
			break;
		default:
			menu.OrderMenu();		
	}
}
///============================================================================================//////

///====PAYMENT=======================================================================//////
float Customer::Payment(){

	system("cls");
	border();
	gotoxy(30,15);
	cout << "Your Total Amount:  " << customer.TotalPrice;
	gotoxy(30,16);
	cout << "Enter Your Cash:  ";
	cin >> CustomerCash ;
		if(CustomerCash < customer.TotalPrice ){
			gotoxy(30,17);
			cout << "Insufficient Amount "<< endl;
			gotoxy(30,18);
			cout << "Please Enter Again"<< endl;
			getch();
			
			customer.Payment();
		}
	Change = CustomerCash - customer.TotalPrice;
	gotoxy(30,18);
	cout << "Your Change: "<< Change ;
	getch();
	system("cls");
	customer.DisplayCustomerOrder(CustomerCash, Change);
	cout << "Press Enter To Proceed";
	getch();
}
///==================================================================================//////

///====Customer===PASTRY===Order=====================================================///
float Customer::OrderPastry(){
	system("cls");
	head2();
	cashoutDisply();
	pastry.DisplayMenuPastry();
	cout << "\nSelect the Id of the Item that you want to Order: ";
	cin >> id;
	cout << "Specify the Quantity: ";
	cin >> quantity;
	float price;

	//==> 1st while:: scans the pastry menu for the customer inputted order.
	//==============> if the user input an id that is not in the menu then the totalamount will just be 0
	ifstream pfromFile("pastry.db");
	int cnt=1;
		while(pfromFile>>p.ItemName>>p.ItemStock>>p.ItemPrice){
			////==> if the id inputted by the customer matches the id in the menu then proceed to transaction 
			if(cnt==id){
				
				if(p.ItemStock == 0){
					system("cls");
					gotoxy(20,4);
					cout << "We have no Stock Available for " << p.ItemName;
					gotoxy(20,5);
					cout << "Sorry for the Inconvinience :(";
					getch();
					system("cls");
					OrderOpt();
				}else if (p.ItemStock < quantity){
					system("cls");
					gotoxy(20,4);
					cout << "We have Insufficient stock Available for " << p.ItemName;
					gotoxy(20,5);
					cout << "Sorry for the Inconvinience :(";
					getch();
					system("cls");
					OrderOpt();
				}
				
				ordDescription = p.ItemName;
				ordQuantity = quantity;
					////==>	OrdToFile1 is opened to add the customers order in the file OrdCustomer
					ofstream OrdtoFile1("OrdCustomer.db", ios::app);
					////==>	OrdFromFile1 is opened to See if the customers order is already in the file OrdCustomer.
					ifstream OrdfromFile1("OrdCustomer.db");
						//==> 2nd while:: Reads the file and proceeds to check if the order of the customers was already ordered 
						//==============> then proceeds to add the quantity and  update the subtotal of that order instead of adding another line of same order in the file
						int flag = false;
						while(OrdfromFile1>>o.OrdDescription>>o.OrdQuantity>>o.OrdPrice>>o.Subtotal){
							if(ordDescription==o.OrdDescription){
									flag = true;
									break;
							}
						}
								///==> created temp file for the updated order
								if(flag==true){
									ofstream OrdtoFile2("Temp.db", ios::app);
										o.OrdQuantity += ordQuantity;								
										OrdtoFile2 << o.OrdDescription << " " << o.OrdQuantity << " " << o.OrdPrice << " " << o.OrdQuantity*o.OrdPrice <<endl;
								//end	
										
										///==> Copies all the record from OrdCustomer to temp file 
										///===>EXCEPT for the current input Order that is already updated and placed in the temp file
											ifstream OrdfromFile2("OrdCustomer.db");
											int i=1;
											while(OrdfromFile2>>o.OrdDescription>>o.OrdQuantity>>o.OrdPrice>>o.Subtotal){
												if(ordDescription!=o.OrdDescription){
												
												OrdtoFile2<<o.OrdDescription<<" "<< o.OrdQuantity << " " << o.OrdPrice << " " << o.Subtotal <<endl;				
												}
											i++;																			
											}
										//end
										///==> close all open files
										OrdtoFile2.close();
										OrdfromFile2.close();
										OrdtoFile1.close();
										OrdfromFile1.close();
										///==> Delete the original OrdCustomer file
										remove("OrdCustomer.db");//Remove Original db file
										///==> Rename the Temporary file
										rename("Temp.db" , "OrdCustomer.db" );//Renaming Temp file
								}else{
									///==> If the Order is new then the order is added to the OrdCustomer File
									OrdtoFile1 << ordDescription << " " << ordQuantity << " " << p.ItemPrice << " "  << p.ItemPrice * quantity << endl;
									OrdtoFile1.close();
									OrdfromFile1.close();
	
								}
				
				TotalPrice += p.ItemPrice * quantity;
			
			break;
			}
			cnt++;
		}
		pfromFile.close();
				///==> Restocks the Inventory || Subtracts the Quantity of the Item Bought by the Customer to the Stock of the Item in the Inventory 
				int newstock = p.ItemStock-quantity;
					ofstream ptoFile("temp.db", ios::app); // Makes a temp file for the new stock of the Item
					ptoFile << p.ItemName << " " << newstock << " " << p.ItemPrice <<endl;
					///==> Copying Contents of the Original File EXEPT for the Item that have a new stock to the Temp File
					pfromFile.open("pastry.db");
					int i=1;
					while(pfromFile>>p.ItemName>>p.ItemStock>>p.ItemPrice){
						if(i!=id){
						
						ptoFile<<p.ItemName<<" "<< p.ItemStock << " " <<p.ItemPrice<<endl;				
						}
					i++;
					}
					ptoFile.close();
					pfromFile.close();
					remove("pastry.db");
					rename("temp.db" , "pastry.db" ); 	
		
	
	gotoxy(90,8);
	cout << "Php "<< TotalPrice<<endl;
		subtotal = 0;
		ordQuantity = 0;
	getch();
	system("cls");
	OrderOpt();
	getch();
}
///====Customer===Coffee===Order====================================================///
float Customer::OrderCoffee(){
	system("cls");
	head2();
	cashoutDisply();
	coffee.DisplayMenuCoffee();
	cout << "\nSelect the Id of the Item that you want to Order: ";
	cin >> id;
	cout << "Specify the Quantity: ";
	cin >> quantity;
	float price;
	ifstream cfromFile("coffee.db");
		int cnt=1;
		while(cfromFile>>c.ItemName>>c.ItemStock>>c.ItemPrice){
			////==> if the id inputted by the customer matches the id in the menu then proceed to transaction 
			if(cnt==id){
				///===> Checks Inventory Stocks
				if(c.ItemStock == 0){
					system("cls");
					gotoxy(20,4);
					cout << "We have no Stock Available for " << c.ItemName;
					gotoxy(20,5);
					cout << "Sorry for the Inconvinience :(";
					getch();
					system("cls");
					OrderOpt();
				}else if (c.ItemStock < quantity){
					system("cls");
					gotoxy(20,4);
					cout << "We have Insufficient stock Available for " << c.ItemName;
					gotoxy(20,5);
					cout << "Sorry for the Inconvinience :(";
					getch();
					system("cls");
					OrderOpt();
				}
		
					ordDescription = c.ItemName;
					ordQuantity = quantity;
					////==>	OrdToFile1 is opened to add the customers order in the file OrdCustomer
					ofstream OrdtoFile1("OrdCustomer.db", ios::app);
					////==>	OrdFromFile1 is opened to See if the customers order is already in the file OrdCustomer.
					ifstream OrdfromFile1("OrdCustomer.db");
						//==> 2nd while:: Reads the file and proceeds to check if the order of the customers was already ordered 
						//==============> then proceeds to add the quantity and  update the subtotal of that order instead of adding another line of same order in the file
						int flag = false;
						while(OrdfromFile1>>o.OrdDescription>>o.OrdQuantity>>o.OrdPrice>>o.Subtotal){
							if(ordDescription==o.OrdDescription){
									flag = true;
									break;
							}
						}
								///==> created temp file for the updated order
								if(flag==true){
									ofstream OrdtoFile2("Temp.db", ios::app);
										o.OrdQuantity += ordQuantity;								
										OrdtoFile2 << o.OrdDescription << " " << o.OrdQuantity << " " << o.OrdPrice << " " << o.OrdQuantity*o.OrdPrice <<endl;
								//end	
										
										///==> Copies all the record from OrdCustomer to temp file 
										///===>EXCEPT for the current input Order that is already updated and placed in the temp file
											ifstream OrdfromFile2("OrdCustomer.db");
											int i=1;
											while(OrdfromFile2>>o.OrdDescription>>o.OrdQuantity>>o.OrdPrice>>o.Subtotal){
												if(ordDescription!=o.OrdDescription){
												
												OrdtoFile2<<o.OrdDescription<<" "<< o.OrdQuantity << " " << o.OrdPrice << " " << o.Subtotal <<endl;				
												}
											i++;																			
											}
										//end
										///==> close all open files
										OrdtoFile2.close();
										OrdfromFile2.close();
										OrdtoFile1.close();
										OrdfromFile1.close();
										///==> Delete the original OrdCustomer file
										remove("OrdCustomer.db");//Remove Original db file
										///==> Rename the Temporary file
										rename("Temp.db" , "OrdCustomer.db" );//Renaming Temp file
								}else{
									///==> If the Order is new then the order is added to the OrdCustomer File
									OrdtoFile1 << ordDescription << " " << ordQuantity << " " << c.ItemPrice << " "  << c.ItemPrice * quantity << endl;
									OrdtoFile1.close();
									OrdfromFile1.close();
	
								}
				
				TotalPrice += c.ItemPrice * quantity;
			
			break;
			}
			cnt++;
		}
		cfromFile.close();		
				///==> Restocks the Inventory || Subtracts the Quantity of the Item Bought by the Customer to the Stock of the Item in the Inventory 		
				int newstock = c.ItemStock-quantity;
					ofstream ctoFile("temp.db", ios::app);
					ctoFile << c.ItemName << " " << newstock << " " << c.ItemPrice <<endl;
					///==> Copying Contents of the Original File EXEPT for the Item that have a new stock to the Temp File
					cfromFile.open("coffee.db");
					int i=1;
					while(cfromFile>>c.ItemName>>c.ItemStock>>c.ItemPrice){
						if(i!=id){
						
						ctoFile<<c.ItemName<<" "<< c.ItemStock << " " <<c.ItemPrice<<endl;				
						}
					i++;
					}
					ctoFile.close();
					cfromFile.close();
					remove("coffee.db");
					rename("temp.db" , "coffee.db" );
		
	gotoxy(90,8);
	cout << "Php "<< TotalPrice <<endl;
		subtotal = 0;
		ordQuantity = 0;
	getch();
	system("cls");
	OrderOpt();
	getch();
}
///=================================================================================///
///====OPTION===================================================================///
void Customer::OrderOpt(){
	int opt;
	gotoxy(10,5);
	cout << "\tWhat else? " << endl;
	cout << "\t\t <1> Add Order from Coffee Menu" << endl;
	cout << "\t\t <2> Add Order from Pastry Menu" << endl;
	cout << "\t\t <3> Pay" << endl;
	cout << "\t  >> Enter an Option: ";
	cin >> opt;

	switch(opt){
		case 1:
			customer.OrderCoffee();
			break;
		case 2:
			customer.OrderPastry();
			break;
		case 3:
			customer.Payment();
			///==> Sales
			
			remove("OrdCustomer.db"); ///==> Deletes the OrdCustomer File for the next new Customer Transaction	
			customer.TotalPrice = 0; ///==> Resets the Value of the TotalPrice Variable for the Next new Customer Transaction
			main();
			break;
		default:
			customer.OrderOpt();
	}
}
///=============================================================================///
///ORDER///END//*************************************************************************************///


///SALES///START//*************************************************************************************///
void Sales(int TotalItems, float Total){
	time_t now = time(0);
	tm *ltm = localtime(&now);
	s.sTotalItems = TotalItems;
	s.sTotalAmount = Total; 
	s.sMonth = 1+ltm->tm_mon; s.sDay = ltm->tm_mday; s.sYear = 1900+ltm->tm_year;
	s.sHour = ltm->tm_hour; s.sMin = ltm->tm_min; s.sSec = 1+ltm->tm_sec;
	ofstream SalesToFile("Sales.db", ios::app);
	SalesToFile << s.sTotalItems << " " << s.sTotalAmount << " " << s.sHour << " " << s.sMin << " " << s.sSec << " " <<  s.sMonth << " " <<  s.sDay << " " <<  s.sYear << endl;
	SalesToFile.close();
}
void DisplaySales(){
	
		ifstream SalesfromFile("Sales.db");
		///==> Time and Date Of Order
		time_t now = time(0);
		tm *ltm = localtime(&now);          
								                       
		cout << "\n\n\t    _____________________________________________________________________________		" << endl;
		cout << "\t / \\                                                                              \\.	" << endl;
		cout << "\t |   |                                 Moon Cafe+                                  |.	" << endl;
		cout << "\t  \\_ |                               Sales Record                                  |.	" << endl;
		cout << "\t     |                                                                             |.	" << endl;
		cout << "\t     | --------------------------------------------------------------------------- |.	" << endl;
		cout << "\t     |" <<setw(6) << "   Transaction No." << setw(15) << "No. of Items" << setw(15) << "Total Amount" << setw(10) <<"Time" << setw(13) <<"Date" << "      |.	" << endl;	
		cout << "\t     | --------------------------------------------------------------------------- |.	" << endl;
	
	int i = 1; 
	float TotalSales = 0;
	while(SalesfromFile>>s.sTotalItems>>s.sTotalAmount>>s.sHour>>s.sMin>>s.sSec>>s.sMonth>>s.sDay>>s.sYear){
		TotalSales += s.sTotalAmount;
		cout<< "\t     |"<<setw(10) <<  i <<setw(18)<< s.sTotalItems << setw(12) << s.sTotalAmount << " Php"  << setw(10) << s.sHour << ":" << s.sMin << ":" << s.sSec << setw(6) <<s.sMonth<< "/" <<s.sDay<< "/" <<s.sYear<< "   |.	"<< endl;
	i++;
	}
		cout << "\t     | --------------------------------------------------------------------------- |.	" << endl;
		cout << "\t     |"<<setw(35) << "TOTAL SALES:" << setw(6) << TotalSales << " Php"  << setw(34) << "|." << endl;
		cout << "\t     |                                                                             |.	" << endl;
		cout << "\t     |   __________________________________________________________________________|___	" << endl;
		cout << "\t     |  /                                                                             /." << endl;
		cout << "\t     \\_/_____________________________________________________________________________/. " << endl;
	SalesfromFile.close();
	getch();
	
}
///SALES///END//*************************************************************************************///


///ADMIN///START//*************************************************************************************///
///====ADMIN====================================================================================//////
void Menu::admin(){
	system("cls");
	border();
	gotoxy(35, 14);
	cout << "Admin Settings: " << endl;
	gotoxy(35, 15);
	cout << "\t <1> Add Menu " << endl;
	gotoxy(35, 16);
	cout << "\t <2> Update Menu " << endl;
	gotoxy(35, 17);
	cout << "\t <3> Delete Menu " << endl;
	gotoxy(35, 18);
	cout << "\t <4> Sales " << endl <<endl;
	gotoxy(35, 19);
	cout << "\t <5> Back to Menu " << endl <<endl;
	gotoxy(35, 21);
	cout << " Enter an Option: ";
	cin >> opt;
	
	switch(opt){
		case 1:
			system("cls");
			menu.AddMenu();
			system("cls");
			menu.admin();
		break;
		
		case 2:
			system("cls");
			menu.UpdateMenu();
			
		break;
		
		case 3:
			system("cls");
			menu.DeleteMenu();
		break;
		case 4:
			system("cls");
			DisplaySales();
		case 5:
			system("cls");
			main();
		default:
			menu.admin();
		break;
	}
	
}
///============================================================================================//////

///UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU///
///=======Update===MENU===============================================================///

void Menu::UpdateMenu(){
	system("cls");
	border();
	gotoxy(35, 14);
	cout << " Update Menu: " << endl;
	gotoxy(35, 16);
	cout << "\t <1> Pastry Menu " << endl;
	gotoxy(35, 17);
	cout << "\t <2> Coffee Menu " << endl;
	gotoxy(35, 18);
	cout << "\t <3> Back to Menu " << endl  << endl;
	gotoxy(35, 20);
	cout << "Enter an Option: ";
	cin >> opt;
	
	switch(opt){
		case 1: //update pastry menu
			system("cls");
			cout<<"\n\n\t\t\tUpdate Pastry Database\n\n";
			pastry.DisplayMenuPastry();
			cout<<"\t\tPlease type the id:  ";
			cin>>id;
			pastry.UpdateMenuPastry(id);
			system("cls");
			pastry.DisplayMenuPastry();
			getch();
			menu.UpdateMenu();
			
		break;
		
		case 2: //update coffee menu
			system("cls");
			cout<<"\n\n\t\t\tUpdate Coffee Database\n\n";
			coffee.DisplayMenuCoffee();
			cout<<"\t\tPlease type the id:  ";
			cin>>id;
			coffee.UpdateMenuCoffee(id);
			system("cls");
			coffee.DisplayMenuCoffee();
			getch();
			menu.UpdateMenu();
		break;
		
		case 3:
			system("cls");
			menu.admin();
		break;
		
		default:
			menu.UpdateMenu();
		break;
	}
	
}

///=======Update===PASTRY===MENU==============================================///
void Pastry::UpdateMenuPastry(int id){
	system("CLS");
	ifstream pfromFile("pastry.db");
		border();
		gotoxy(30, 14);
		cout << "Database Update: ";
		int cnt=1;
		while(pfromFile>>p.ItemName>>p.ItemStock>>p.ItemPrice){
			if(cnt==id){
			gotoxy(30, 16);
			cout<<"<1> Pastry Name ==>  "<<p.ItemName<<endl;
			gotoxy(30, 17);
			cout<<"<2> Price ==>  "<<p.ItemPrice<<endl;
			gotoxy(30, 18);
			cout<<"<3> Stock ==>  "<<p.ItemStock<<endl;
			break;
			}
			cnt++;
		}
		pfromFile.close();
		
		int info;
		gotoxy(30, 19);
		cout<<"Select info that you want to update:  ";
		cin>>info;
		system("cls");
		border();
			if(info==1){
					gotoxy(30, 15);
					cout<<"New Coffee name:  ";
					cin>>pName;
						
						pfromFile.open("pastry.db");
							int flag = false;
							while(pfromFile>>p.ItemName>>p.ItemStock>>p.ItemPrice){
								if(pName==p.ItemName){
										flag = true;
										break;
								}
							}
						if(flag==true){
						system("cls");
						gotoxy(20,10);
						cout << "Menu is Already Taken!";
						getch();
						pfromFile.close();
						system("cls");
						menu.UpdateMenu();
					}else{
						ofstream ptoFile("pTemp.db", ios::app);
						ptoFile << pName << " " << p.ItemStock << " " << p.ItemPrice <<endl;
						pfromFile.open("pastry.db");
							int i=1;
							while(pfromFile>>p.ItemName>>p.ItemStock>>p.ItemPrice){
								if(pName!=p.ItemName){
								ptoFile<<p.ItemName<<" "<< p.ItemStock << " " <<p.ItemPrice<<endl;				
								}
							i++;
							}
						ptoFile.close();
						pfromFile.close();
						remove("pastry.db");//Remove Original db file
						rename("pTemp.db" , "pastry.db" );//Renaming Temp file
						gotoxy(30, 18);
						cout<<"Update Successful!";	
						Sleep(500);
						getch();
						pastry.DisplayMenuPastry();
						menu.adminBack();
					}
					
			}else if(info==2){
					gotoxy(30, 16);
					cout<<"New Price:  ";
					cin>>p.ItemPrice;	
			}else if(info==3){
					gotoxy(30, 17);
					cout<<"Restock:  ";
					cin>>p.ItemStock;
			}else{
					menu.UpdateMenu();
			}
			pfromFile.close();			
			/*Creating Temporary File*/
			ofstream ptoFile("pTemp.db", ios::app);
			ptoFile << p.ItemName << " " << p.ItemStock << " " << p.ItemPrice <<endl;
			/* End Creating Temporary File*/
			
			/*Copying of records from original db except the selected record*/
			pfromFile.open("pastry.db");
			int i=1;
			while(pfromFile>>p.ItemName>>p.ItemStock>>p.ItemPrice){
				if(i!=id){
				
				ptoFile<<p.ItemName<<" "<< p.ItemStock << " " <<p.ItemPrice<<endl;				
				}
			i++;
			}
			
			/*End*/
			ptoFile.close();
			pfromFile.close();
			

			remove("pastry.db");//Remove Original db file
			rename("pTemp.db" , "pastry.db" );//Renaming Temp file
			Sleep(500);
			gotoxy(30, 18);
			cout<<"Update Successful!";	
			getch();


	
}
///==========================================================================///

///=======Update===COFFEE===MENU============================================///
void Coffee::UpdateMenuCoffee(int id){
	system("CLS");
	ifstream cfromFile("coffee.db");
		border();
		gotoxy(30, 14);
		cout << "Database Update: ";
		int cnt=1;
		while(cfromFile>>c.ItemName>>c.ItemStock>>c.ItemPrice){
			if(cnt==id){
			gotoxy(30, 16);
			cout<<"<1> Coffee Name ==>  "<<c.ItemName<<endl;
			gotoxy(30, 17);
			cout<<"<2> Price ==>  "<<c.ItemPrice<<endl;
			gotoxy(30, 18);
			cout<<"<3> Stock ==>  "<<c.ItemStock<<endl;
			break;
			}
			cnt++;
		}
		cfromFile.close();
		
		int info;
		gotoxy(30, 19);
		cout<<"Select info that you want to update:  ";
		cin>>info;
		system("cls");
		border();
			if(info==1){
					gotoxy(30, 15);
					cout<<"New Coffee name:  ";
					cin>>cName;
						
						cfromFile.open("coffee.db");
							int flag = false;
							while(cfromFile>>c.ItemName>>c.ItemStock>>c.ItemPrice){
								if(cName==c.ItemName){
										flag = true;
										break;
								}
							}
						if(flag==true){
						system("cls");
						gotoxy(20,10);
						cout << "Menu is Already Taken!";
						getch();
						cfromFile.close();
						system("cls");
						menu.UpdateMenu();
					}else{
						ofstream ctoFile("cTemp.db", ios::app);
						ctoFile << cName << " " << c.ItemStock << " " << c.ItemPrice <<endl;
						cfromFile.open("coffee.db");
							int i=1;
							while(cfromFile>>c.ItemName>>c.ItemStock>>c.ItemPrice){
								if(cName!=c.ItemName){
								ctoFile<<c.ItemName<<" "<< c.ItemStock << " " <<c.ItemPrice<<endl;				
								}
							i++;
							}
						ctoFile.close();
						cfromFile.close();
						remove("coffee.db");//Remove Original db file
						rename("cTemp.db" , "coffee.db" );//Renaming Temp file
						gotoxy(30, 18);
						cout<<"Update Successful!";	
						Sleep(500);
						getch();
						coffee.DisplayMenuCoffee();
						menu.adminBack();
					}
					
			}else if(info==2){
					gotoxy(30, 16);
					cout<<"New Price:  ";
					cin>>c.ItemPrice;	
			}else if(info==3){
					gotoxy(30, 17);
					cout<<"Restock:  ";
					cin>>c.ItemStock;
			}else{
					menu.UpdateMenu();
			}
			
			cfromFile.close();	
			/*Creating Temporary File*/
			ofstream ctoFile("cTemp.db", ios::app);
			ctoFile << c.ItemName << " " << c.ItemStock << " " << c.ItemPrice <<endl;
			/* End Creating Temporary File*/
			
			/*Copying of records from original db except the selected record*/
			cfromFile.open("coffee.db");
			int i=1;
			while(cfromFile>>c.ItemName>>c.ItemStock>>c.ItemPrice){
				if(i!=id){
				ctoFile<<c.ItemName<<" "<< c.ItemStock << " " <<c.ItemPrice<<endl;				
				}
			i++;
			}
			
			/*End*/
			ctoFile.close();
			cfromFile.close();

			remove("coffee.db");//Remove Original db file
			rename("cTemp.db" , "coffee.db" );//Renaming Temp file
			gotoxy(30, 18);
			cout<<"Update Successful!";	
			Sleep(500);
			getch();
			
}
///=========================================================================///
///UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU///

///DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD///
///=======Delete===MENU================================================================///
void Menu::DeleteMenu(){
	system("cls");
	border();
	gotoxy(35, 14);
	cout << "Delete Menu: " << endl;
	gotoxy(35, 16);
	cout << "\t <1> Pastry Menu " << endl;
	gotoxy(35, 17);
	cout << "\t <2> Coffee Menu " << endl;
	gotoxy(35, 18);
	cout << "\t <3> Back to Menu " << endl  << endl;
	gotoxy(35, 20);
	cout << "Enter an Option: ";
	cin >> opt;
	
	switch(opt){
		case 1: //delete pastry menu
			system("cls");
			pastry.DeleteMenuPastry(id);
			menu.adminBack();
		break;
		
		case 2: //delete coffee menu
			system("cls");
			coffee.DeleteMenuCoffee(id);
			menu.adminBack();
		break;
		
		case 3:
			system("cls");
			menu.admin();
		break;
		
		default:
			menu.UpdateMenu();
		break;
	}
	
}

///=======DELETE==PASTRY==========================================================///
void Pastry::DeleteMenuPastry(int id){
		pastry.DisplayMenuPastry();
		cout << "\tEnter Id of the Pastry Item to Delete: ";
		cin >> id;
			/*Creating Temporary File*/
			ofstream ptoFile("Temp.db", ios::app);
			
			/* End Creating Temporary File*/
	
			/*Copying of records from original db except the selected record*/
			ifstream pfromFile("pastry.db");
			int i=1;
			while(pfromFile>>p.ItemName>>p.ItemStock>>p.ItemPrice){
				if(i!=id){
				
				ptoFile<<p.ItemName<< " " << p.ItemStock << " " <<p.ItemPrice<<endl;				
				}
			i++;
			}
			
			/*End*/
			ptoFile.close();
			pfromFile.close();
			

			remove("pastry.db");//Remove Original db file
			rename("Temp.db" , "pastry.db" );//Renaming Temp file
			Sleep(500);
			gotoxy(30, 18);
			cout<<"Delete Successful!";	
			system("cls");
			pastry.DisplayMenuPastry();
}
///==============================================================================///

///=======DELETE==COFFEE=========================================================///
void Coffee::DeleteMenuCoffee(int id){
		coffee.DisplayMenuCoffee();
		cout << "\tEnter Id of the Coffee Item to Delete: ";
		cin >> id;
			/*Creating Temporary File*/
			ofstream ctoFile("Temp.db", ios::app);
			/* End Creating Temporary File*/
	
			/*Copying of records from original db except the selected record*/
			ifstream cfromFile("coffee.db");
			int i=1;
			while(cfromFile>>c.ItemName>>c.ItemStock>>c.ItemPrice){
				if(i!=id){
				
				ctoFile<<c.ItemName<< " " << c.ItemStock << " " <<c.ItemPrice<<endl;				
				}
			i++;
			}
			
			/*End*/
			ctoFile.close();
			cfromFile.close();
			

			remove("coffee.db");//Remove Original db file
			rename("Temp.db" , "coffee.db" );//Renaming Temp file
			Sleep(500);
			gotoxy(30, 18);
			cout<<"Delete Successful!";	
			system("cls");
			coffee.DisplayMenuCoffee();
}
///=============================================================================///
///DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD///

///AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA///
///=======ADD==MENU==================================================================///
void Menu::AddMenu(){
	system("cls");
	border();
	gotoxy(35, 14);
	cout << "Add Menu: " << endl;
	gotoxy(35, 16);
	cout << "\t <1> Pastry Menu " << endl;
	gotoxy(35, 17);
	cout << "\t <2> Coffee Menu " << endl;
	gotoxy(35, 18);
	cout << "\t <3> Back to Menu " << endl  << endl;
	gotoxy(35, 20);
	cout << "Enter an Option: ";
	cin >> opt;
	
	switch(opt){
		case 1: //add pastry menu
			system("cls");
			pastry.AddMenuPastry();
			system("cls");
			pastry.DisplayMenuPastry();
			menu.adminBack();
		break;
		
		case 2: //add coffee menu
			system("cls");
			coffee.AddMenuCoffee();
			system("cls");
			coffee.DisplayMenuCoffee();
			menu.adminBack();
		break;
		
		case 3:
			system("cls");
			menu.admin();
		break;
		
		default:
			menu.AddMenu();
		break;
	}
	
}
///=================================================================================///

///=======ADD==PASTRY==========================================================///
void Pastry::AddMenuPastry(){
	system("cls");
	ofstream pToFile("pastry.db", ios::app);
	gotoxy(20,4);
	cout << "Add Pastry" ;
	gotoxy(20,5);
	cout << "\tEnter Pastry Name: " ;
	cin >> pName;
	gotoxy(20,6);
	cout << "\tEnter Stocks: " ;
	cin >> pStock;
	gotoxy(20,7);
	cout << "\tEnter Price: " ;
	cin >> pPrice;
	
	
	ifstream pfromFile("pastry.db");
	int flag = false;
	while(pfromFile>>p.ItemName>>p.ItemStock>>p.ItemPrice){
		if(pName==p.ItemName){
				flag = true;
				break;
		}
	}
		if(flag==true){
			gotoxy(20,10);
			cout << "Menu is Already Taken!";
			getch();
			system("cls");
			menu.AddMenu();
		}else{
			pToFile << pName << " " << pStock << " " << pPrice <<  endl;
			pToFile.close();
			system("cls");
			gotoxy(20,5);
			cout << "########################################" << endl;	gotoxy(20,6);
			cout << "##                                    ##" << endl;	gotoxy(20,7);
			cout << "## You Have Successfully added A Menu ##" << endl;	gotoxy(20,8);
			cout << "##                                    ##" << endl;	gotoxy(20,9);
			cout << "########################################" << endl;
			getch();
		}		
	}
///============================================================================///

///=======ADD====COFFEE========================================================///
void Coffee::AddMenuCoffee(){
	system("cls");
	ofstream cToFile("coffee.db", ios::app);
	gotoxy(20,4);
	cout << "Add Coffee" ;
	gotoxy(20,5);
	cout << "\tEnter Coffee Name: " ;
	cin >> cName;
	gotoxy(20,6);
	cout << "\tEnter Stocks: " ;
	cin >> cStock;
	gotoxy(20,7);
	cout << "\tEnter Price: " ;
	cin >> cPrice;
	
	
	ifstream cfromFile("coffee.db");
	int flag = false;
	while(cfromFile>>c.ItemName>>c.ItemStock>>c.ItemPrice){
		if(cName==c.ItemName){
				flag = true;
				break;
		}
	}
		if(flag==true){
			gotoxy(20,10);
			cout << "Menu is Already Taken!";
			getch();
			system("cls");
			menu.AddMenu();
		}else{
			cToFile << cName << " " << cStock << " " << cPrice <<  endl;
			cToFile.close();
			system("cls");
			gotoxy(20,5);
			cout << "########################################" << endl;	gotoxy(20,6);
			cout << "##                                    ##" << endl;	gotoxy(20,7);
			cout << "## You Have Successfully added A Menu ##" << endl;	gotoxy(20,8);
			cout << "##                                    ##" << endl;	gotoxy(20,9);
			cout << "########################################" << endl;
			getch();
		}		
	}
///============================================================================///
///AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA///

void Menu::adminBack(){
	cout << " >>Back to Main Menu? [Y or N]>> ";
	cin >> YoN;
	if((YoN == 'Y') || (YoN == 'y')){
		menu.admin();
	}else{
		system("cls");
		exit(0);
	}	
}
///ADMIN////END//****************************************************************************************///

//////////////////////////////////////////////////////////////////////////////////////////
///====Display===Order===Menu=========================================================///
void Customer::DisplayCustomerOrder(float CustomerCash, float Change){
	ifstream ofromFile("OrdCustomer.db");
		///==> Time and Date Of Order
		time_t now = time(0);
		tm *ltm = localtime(&now);          
								                       
		cout << "\n\n\t    __________________________________________________________		" << endl;
		cout << "\t / \\                                                          \\.	" << endl;
		cout << "\t |   |                        Moon Cafe+                       |.	" << endl;
		cout << "\t  \\_ |                   211 Danarra St Cor.                   |.	" << endl;
		cout << "\t     |             Metropolitan Ave. QC La Paz 1200            |.	" << endl;
		cout << "\t     |                                                         |.	" << endl;
		cout << "\t     | " <<setw(5)  << 1+ltm->tm_mon << "-" << ltm->tm_mday << "-" << 1900+ltm->tm_year << setw(31) <<  ltm->tm_hour << " : " << 1+ltm->tm_min << " : " << 1+ltm->tm_sec << "  |." << endl;
		cout << "\t     | ------------------------------------------------------- |.	" << endl;
		
		cout << "\t     |" <<setw(9) << " Quantity" << setw(18) << "Description" << setw(12) << "Price" << setw(13) <<"Subtotal" << "     |.	" << endl;
	
		cout << "\t     | ------------------------------------------------------- |.	" << endl;
	
	int i = 1, TotalItem=0;
	float total=0;
	while(ofromFile>>o.OrdDescription>>o.OrdQuantity>>o.OrdPrice>>o.Subtotal){
		total += o.Subtotal;
		TotalItem +=o.OrdQuantity;
		cout<<"\t     |"<<setw(5) << o.OrdQuantity <<setw(22)<< o.OrdDescription << setw(8) << o.OrdPrice << " Php"  << setw(9) << o.Subtotal << " Php" << "     |.	"<< endl;
	i++;
	}
		cout << "\t     | ======================================================= |.	" << endl;
		cout << "\t     |" <<setw(5) << TotalItem << "  Total Items" << setw(41) << "|." << endl;
		
		cout << "\t     |"<<setw(41) << "TOTAL AMOUNT:" << setw(7) << total << " Php"  << setw(7) << "|." << endl;
		cout << "\t     |"<<setw(41) << "CASH:" << setw(7) << CustomerCash << " Php"  << setw(7) << " |." << endl;
		
		cout << "\t     | ....................................................... |.	" << endl;		
		cout << "\t     |"<<setw(41) << "CHANGE:" << setw(7) << Change << " Php"  << setw(7)  << "|." << endl;
		cout << "\t     |                                                         |.	" << endl;
		cout << "\t     |                                                         |.	" << endl;				
		cout << "\t     |                        Thank You!                       |.	" << endl;
		cout << "\t     |                     Please Come Again!                  |.	" << endl;
		cout << "\t     |   ______________________________________________________|___	" << endl;
		cout << "\t     |  /                                                         /." << endl;
		cout << "\t     \\_/_________________________________________________________/. " << endl;
	ofromFile.close();
	Sales(TotalItem, total);
	
}

void Pastry::DisplayMenuPastry(){
	ifstream pfromFile("pastry.db");
	gotoxy(0,4);
	cout << "  .-=~=-." ; 
	gotoxy(20,4);
	cout << "  _.--==> Pastry Menu <==--._ ";
	gotoxy(60,4);                                                    
	cout <<"  .-=~=-. " << endl;
	cout << "  (__  _)-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-(__  _) " << endl;
	cout << "  (__  _)" <<setw(5) << "#" << setw(18) << "Pastry Name" << setw(10) << "Stock" << setw(16) <<"Price" << "    (__  _) " << endl;
	gotoxy(0,7);
	cout << "  (__  _)-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-(__  _)" << endl;
	
	int i = 1;
	while(pfromFile>>p.ItemName>>p.ItemStock>>p.ItemPrice){
		cout<<"  (__  _)"<<setw(5) << i <<setw(18)<< p.ItemName << setw(8) << p.ItemStock << setw(12) << p.ItemPrice << " Pesos " << "   (__  _) "<< endl;
	i++;
	}
		cout << "  (_ ___)-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-(_ ___)" << endl;
		cout << "  `-._.-'                                                     `-._.-'" << endl;
	pfromFile.close();
}

void Coffee::DisplayMenuCoffee(){
	ifstream cfromFile("coffee.db");
	
	gotoxy(0,4);
	cout << "  .-=~=-." ; 
	gotoxy(20,4);
	cout << "   _.--==> Coffee Menu <==--._ ";
	gotoxy(60,4);                                                    
	cout <<"  .-=~=-. " << endl;
	cout << "  (__  _)-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-(__  _) " << endl;
	cout << "  (__  _)" <<setw(5) << "#" << setw(18) << "Coffee Name" << setw(10) << "Stock" << setw(16) <<"Price" << "    (__  _) " << endl;
	gotoxy(0,7);
	cout << "  (__  _)-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-(__  _)" << endl;
	
	int i = 1;
	while(cfromFile>>c.ItemName>>c.ItemStock>>c.ItemPrice){
		cout<<"  (__  _)"<<setw(5) << i <<setw(18)<< c.ItemName << setw(8) << c.ItemStock << setw(12) << c.ItemPrice << " Pesos " << "   (__  _) "<< endl;
	i++;
	}
		cout << "  (_ ___)-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-(_ ___)" << endl;
		cout << "  `-._.-'                                                     `-._.-'" << endl;
	cfromFile.close();
}
///===================================================================================///
/////////////////////////////////////////////////////////////////////////////////////////
 
///================LAYOUT====DESIGN===================================================///
void head1(){
	cout << "\n\n";
	cout << "\t\t	   __    __)      _____)     __     __)  __    __) " << endl;
	cout << "\t\t\t  (, /|  /|      /          (, /|  /    (, /   /   " << endl;
	cout << "\t\t\t    / | / |      )__          / | /       /   /    " << endl;
	cout << "\t\t\t ) /  |/  |_   /           ) /  |/       /   /     " << endl;
	cout << "\t\t\t(_/   '       (_____)     (_/   '       (___(_     " << endl <<endl;
}

void head2(){
	cout << "";
	cout << "\t       _     _     _     _     _     _     _     _  " << endl;
	cout << "\t      / \\   / \\   / \\   / \\   / \\   / \\   / \\   / \\ " << endl;
	cout << "\t     ( M ) ( o ) ( o ) ( n ) ( C ) ( a ) ( f ) ( e )" << endl;
	cout << "\t      \\_/   \\_/   \\_/   \\_/   \\_/   \\_/   \\_/   \\_/ " << endl;

	
}

void SplashScreen(){
//	system("Color 3E");
	system("Color F3");
//	system("Color 73"); COLOR for Recipt
	gotoxy(0,4);
	cout << "	   *                                  +                         *     " <<endl;
	cout << "              +          aaaaaaaaaaaaaaaa               *                      " <<endl;
	cout << "                      aaaaaaaaaaaaaaaaaaaaaaaa                           +  " <<endl;
	cout << "    .*             aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa           +                   " <<endl;
	cout << "                 aaaaaaaaaaaaaaaaa           aaaaaa                                " <<endl;
	cout << "               aaaaaaaaaaaaaaaa                  aaaa                             " <<endl;
	cout << "              aaaaaaaaaaaaa aa                      aa           *           +     " <<endl;
	cout << "*            aaaaaaaa      aa                        a                             " <<endl;
	cout << "            aaaaaaa aa aaaa               :::     :::::::::: ::::::::::                                              " <<endl;
	cout << "         *  aaaaaaaaa     aaa           :+: :+:   :+:        :+:                              +              " <<endl;
	cout << "            aaaaaaaaaaa aaaaaaa        +:+   +:+  +:+        +:+                *                        " <<endl;
	cout << "            aaaaaaa    aaaaaaaaaa     +#++:++#++: :#::+::#   +#++:++#                                                   " <<endl;
	cout << "            aaaaaa a aaaaaa aaaaaa    +#+     +#+ +#+        +#+                                                   " <<endl;
	cout << "             aaaaaaa  aaaaaaa         #+#     #+# #+#        #+#          +                                 " <<endl;
	cout << "   *.        aaaaaaaa                 ###     ### ###        ##########                a                            " <<endl;
	cout << "              aaaaaaaaaa                            aa                            " <<endl;
	cout << "               aaaaaaaaaaaaaaaa         *        aaaa                            " <<endl;
	cout << "                 aaaaaaaaaaaaaaaaa           aaaaaa         *.                     " <<endl;
	cout << "     *             aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa                          *.     " <<endl;
	cout << "                      aaaaaaaaaaaaaaaaaaaaaaaa                   ~~MOON CAFE       *        . " <<endl;
	cout << "   +              *      aaaaaaaaaaaaaaaa         .              +.             " <<endl;


	Sleep(2000);
	
	cout << "\t\t\t.*  +\n\t\t\t\t*.\n+ . \t\t\t\t\t\t *.\n";Sleep(300);
	cout << "*\t *   . _   _   _   _     _   _   _     _   _     _   _   _   _   _   _   _   _   _   _   _   .* "<<endl;Sleep(300);
	cout << "\t.  ,  / \\ / \\ / \\ / \\   / \\ / \\ / \\   / \\ / \\   / \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\ ,+"<<endl;Sleep(300); 
	cout << ".* \t .  +( y | o | u | r ) ( c | u | p ) ( o | f ) ( i | n | s | p | i | r | a | t | i | o | n ) *\t .*"<<endl;Sleep(300);
	cout << "+\t,  .  \\_/ \\_/ \\_/ \\_/   \\_/ \\_/ \\_/   \\_/ \\_/   \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/  .\t   *"<<endl;
}

void welcome(){
	
		Sleep(2000);
		system("cls");
		gotoxy(20,5);
		cout << "  \n";
		cout << "           ___           ___                         ___           ___           ___           ___     " <<endl;
		cout << "          /\\  \\         /\\__\\                       /\\__\\         /\\  \\         /\\  \\         /\\__\\   		 " <<endl;
		cout << "         _\\:\\  \\       /:/ _/_                     /:/  /        /::\\  \\       |::\\  \\       /:/ _/_  		 " <<endl;
		cout << "        /\\ \\:\\  \\     /:/ /\\__\\                   /:/  /        /:/\\:\\  \\      |:|:\\  \\     /:/ /\\__\\  		" <<endl;
		cout << "       _\\:\\ \\:\\  \\   /:/ /:/ _/_   ___     ___   /:/  /  ___   /:/  \\:\\  \\   __|:|\\:\\  \\   /:/ /:/ _/_ 		" <<endl;
		cout << "      /\\ \\:\\ \\:\\__\\ /:/_/:/ /\\__\\ /\\  \\   /\\__\\ /:/__/  /\\__\\ /:/__/ \\:\\__\\ /::::|_\\:\\__\\ /:/_/:/ /\\__\\	    " <<endl;
		cout << "      \\:\\ \\:\\/:/  / \\:\\/:/ /:/  / \\:\\  \\ /:/  / \\:\\  \\ /:/  / \\:\\    /:/  / \\:\\~~\\  \\/__/ \\:\\/:/ /:/  / 	" <<endl;
		cout << "       \\:\\ \\::/  /   \\::/_/:/  /   \\:\\  /:/  /   \\:\\  /:/  /   \\:\\  /:/  /   \\:\\  \\        \\::/_/:/  / 		 " <<endl;
		cout << "        \\:\\/:/  /     \\:\\/:/  /     \\:\\/:/  /     \\:\\/:/  /     \\:\\/:/  /     \\:\\  \\        \\:\\/:/  / 		 " <<endl;
		cout << "         \\::/  /       \\::/  /       \\::/  /       \\::/  /       \\::/  /       \\:\\__\\        \\::/  /  		 " <<endl;
		cout << "          \\/__/         \\/__/         \\/__/         \\/__/         \\/__/         \\/__/         \\/__/   		 " <<endl;
		gotoxy(50,18);
		cout << "to";
		gotoxy(47,20);
		cout << "Moon Cafe";
		Sleep(1500);
}  

void border(){
gotoxy(20,10);	
cout << "      _______________________________________________" << endl;gotoxy(20,11);
cout << "     /\\                                              \\" << endl;gotoxy(20,12);
cout << " (O)===)><><><><><><><><><><><><><><><><><><><><><><><)==(O)" << endl;gotoxy(20,13);
cout << "     \\/''''''''''''''''''''''''''''''''''''''''''''''/" << endl;gotoxy(20,14);
cout << "      )                                              )" << endl;gotoxy(20,15);
cout << "     (                                              (" << endl;gotoxy(20,16);
cout << "      )                                              )" << endl;gotoxy(20,17);
cout << "     (                                              (" << endl;gotoxy(20,18);
cout << "      )                                              )" << endl;gotoxy(20,19);
cout << "     (                                              (" << endl;gotoxy(20,20);
cout << "      )                                              )" << endl;gotoxy(20,21);
cout << "     (                                               (" << endl;gotoxy(20,22);
cout << "     /\\''''''''''''''''''''''''''''''''''''''''''''''\\    " << endl;gotoxy(20,23);
cout << " (O)===)><><><><><><><><><><><><><><><><><><><><><><><)==(O)" << endl;gotoxy(20,24);
cout << "     \\/______________________________________________/" << endl;
}

void cashoutDisply(){
	
gotoxy(75,3);
cout << "    ______________________________		" << endl;gotoxy(75,4);
cout << "  / \\                             \\.	" << endl;gotoxy(75,5);
cout << " |   |     ++ TOTAL AMOUNT ++     |.	" << endl;gotoxy(75,6);
cout << "  \\_ |                            |.	" << endl;gotoxy(75,7);
cout << "     |                            |.	" << endl;gotoxy(75,8);
cout << "     |                            |.	" << endl;gotoxy(75,9);
cout << "     |                            |.	" << endl;gotoxy(75,10);
cout << "     |                            |.	" << endl;gotoxy(75,11);
cout << "     |   _________________________|___	" << endl;gotoxy(75,12);
cout << "     |  /                            /." << endl;gotoxy(75,13);
cout << "     \\_/____________________________/. " << endl;gotoxy(75,14);
	
}
