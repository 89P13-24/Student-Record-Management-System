#include<iostream>
#include<fstream>
#include<string>
#include<bits/stdc++.h>

#include "algo.h"
#include "comp.h"
#include "start.h"

using namespace std;

/*	This is a user interactive function 
	Our program starts through this function only..
	fmain function creates the basic structure of our program...
*/
void fmain(){
	cout<<"\t\t\t\tWelcome to IITG Student Record Database"<<endl;		
	db g;												// Creates a new database named g
	
	initialization(&g);									// reads data from database i.e. data.txt	
														// More description in comp.cpp								
	string p ,new_p; 									// To store password
    string admin_p;
    int choice = 0;
    int breakpoint = 0;
    
    int flag = 0;										//	To check whether changes have been made or not..
    while(1){
			
		cout<<"\nEnter\n1:To ADD a new student"<<endl;	
		cout<<"2:Login as student"<<endl;
		cout<<"3:Login as Admin"<<endl;
	 	cout<<"4:To exit"<<endl;
	 	
		
		cin>>choice;
		record* node1 = new record ;						//	Using Dynamic memory to store records 
		record* Data = new record;		

		cin.ignore();										//	Crucial while handling strings as it helps to clear out buffer input...
		int s =1;
		
		string branch;
	
		
    	
	   	switch (choice) {
			case 1 :
				node1 = info(g);
				g.insert(node1);
				if(node1 != nullptr){
					flag = 1;								// Captures the change in data..
					cout<<"Please DO NOT share this password "<<endl;	
					cout<<"You have successfully registered"<<endl;
					cout<<"You can also change this password afterwards..."<<endl;
				}
				break;
			
			case 2 :
				int u;
				cout<<"Enter your roll_no "<<endl;
				cin>>u;
				
				//	Necessary to check the validity of the input for propewr functioning of the prrogram..
				
				if(!valid_roll_no(u)){									
					cout<<"Please enter a valid Roll no."<<endl;
					break;
				}
				cout<<"Enter your password"<<endl;

				cin>>p;
				Data = g.search(u);			// This helps to check whether the record is present or not 
											// More description in algo.h
				if(Data != nullptr){
					if(Data->password == p){
						cout<<"\n\t\t\tWelcome "<<Data->name<<" "<<Data->lname<<"\n"<<endl;
						/*	I have provided only certain options to change in the database
							because student cannot change its roll no 
							since roll no uniquely identifies each student and change in the rollno can create ambiguity.. 	
						*/
						
						cout<<"Enter\n1:To see your details"<<endl;
						cout<<"2:To change your password"<<endl;
						cout<<"3:To change your e-mail id"<<endl;
						cout<<"4:To update your branch"<<endl;
						cout<<"5:To Logout"<<endl;
						
						cin>>choice;
						if(choice == 1)
							g.print_record(Data);
						else if(choice == 2){
							while(s<=3){	
								cout<<"Enter your NEW password"<<endl;			// User needs to enter password twice to avoid mistakes in it..
								cin>>p;
								cout<<"Enter your password again"<<endl;
								cin>>new_p;
								if(p!=new_p){
									cout<<"Passwords did not match"<<endl;			// 3 tries are given for every wrong input...
									s++;
									continue;
								}else{
									Data->password = p ;
									g.insert(Data);						//	This is important to reflect changes globally...
									cout<<"Password changed successfully..."<<endl;
									flag = 1;							// 	Tells the program that changes have been made...
									break;
								}
							}
						}else if(choice == 3){
							cout<<"Enter your new email-id"<<endl;
							cin>>branch;
							Data->email = branch;
							g.insert(Data);
							cout<<"e-mail changed successfully..."<<endl;
							flag = 1;
						}
						else if(choice == 4){
							cout<<"Since your department has been changed you need to enter your details again.."<<endl;
							g.delete_record(u);	
							Data = new record;		
							Data = info(g);
							g.insert(Data);
							if(Data != nullptr)
								cout<<"Department changed successfully..."<<endl;
							flag = 1;
						}
						else if(choice == 5)
							cout<<"Thank You..."<<endl;
						else
							cout<<"Please enter a valid choice..."<<endl;
					}
					else{
						cout<<"Not registered as student or Invalid password"<<endl;
						}
					
				}							/*	If the password is incorrect or record is not found
												then the below error message is displayed...
												*/
				else{
					cout<<"Not registered as student or Invalid password"<<endl;
					}
					
				break;
				
			case 3 :										// This segment is for Admin interface...
				
				cout<<"Enter your Admin Password"<<endl;		//	Admin needs to enter a password to login which I have set by default
				getline(cin,admin_p);
				if(admin_p != g.ad_p){
					cout<<"Unauthorized Access..."<<endl;
					}
				else{
							// These are the various options given to admin...
					cout<<"\n\t\tWelcome to Department of Data Science and Artificial Intelligence Student's Database\n"<<endl;
					cout<<"Enter\n1:To search record of a student"<<endl;
					cout<<"2:To get record of all the students"<<endl;
					cout<<"3:To delete a record"<<endl;
					cout<<"4:To Logout"<<endl;
					cin>>choice;
					int roln;
					if(choice == 1){
						cout<<"Enter the roll no. of the student"<<endl;		//	Searching by roll no for proper and unique results..
						cin>>roln;											
						if(!valid_roll_no(roln)){
							cout<<"Please enter a valid Roll no."<<endl;
							break;
						}
						
						node1 = g.search(roln);
						if(node1 != nullptr)
							g.print_record(node1);
						else
							cout<<"Student NOT in the database"<<endl;
					}else if(choice == 2)
						g.print_all();					//	Description of this function is given in algo.cpp
						
						//	Admin has the rights to delete any record 
					else if(choice == 3){
						cout<<"Enter the roll no. of the student"<<endl;
						cin>>roln;
						if(!valid_roll_no(roln)){
							cout<<"Please enter a valid Roll no."<<endl;
							break;
						}
						node1 = g.search(roln);
						if(node1 != nullptr){				
							g.delete_record(roln);		// This function deletes a record in local database..
							cout<<"Record deleted successfully"<<endl;
							flag = 1;
						}
						else
							cout<<"Student NOT in the database"<<endl;
					
					}else if(choice == 4)					// Logout condition for Admin...
						cout<<"Thank you"<<endl;
					    			
				}
				break;
			
			case 4:
				breakpoint = 1;		// If user wants to exit from the program
				break;
				
			default:
				cout<<"Please enter a valid choice.."<<endl;
				break;		
				
		}
		if(breakpoint == 1)		// Breaking condition if value of breakpoint changed
			break;
	}	
    if(flag == 1)		// Writes changes in the global database if any....
    	update_database(g);
    
}

