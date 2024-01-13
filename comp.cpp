#include<iostream>
#include<fstream>
#include<string>
#include<bits/stdc++.h>
#include"algo.h"
#include"comp.h"
using namespace std;


//	This function is used to write a record to the global database i.e our "data.txt" file...
// This done used file stream commands..
// These commands have simpler syntax and are self explanatory...

void write(record* Data , std::ofstream& fnew){
	
	fnew<<Data->roll_no<<"\t"<<Data->name<<"\t"<<Data->lname<<"\t"<<Data->dept<<"\t"<<Data->email<<"\t"<<Data->password<<endl;
}

//	This function is used to write an entire subdivision to the database..

void write_map(map<int ,map<int,record*> > m , std::ofstream& fnew){
	map<int ,map<int,record*>>::iterator it = m.begin();
	while(it != m.end()){
		
		map<int , record*>::iterator itr = it->second.begin();
		while(itr != it->second.end()){
			write(itr->second , fnew);
			++itr;
		}
		++it;
	}
}

/*	This is another crucial function for our program...
	What does this function does is that if there are changes in our data and need to be updated to the global 
		database then this function writes those changes globally...
		This is achieved by making chnages in the file "data.txt" .. 
*/

void update_database(db g){
	ofstream fnew("/home/ishan/project/data.txt");
	write_map(g.btech , fnew);
	
	write_map(g.mtech , fnew);
	
	write_map(g.phd , fnew);
	fnew.close();
}


/*	This is a crucial function for the program as it takes roll no as a input 
	and checks whether the roll no is present or not
	and then if not present it creates a record for that student...		*/

record* info(db g){
	
	int r;
	string n,d,e,p,nl; 
	cout<<"Enter your roll_no"<<endl;

	cin>>r;
	if(!valid_roll_no(r)){
		cout<<"Enter a valid Roll no."<<endl;
		return nullptr;
	}
		
	record* get = g.search(r);
	cin.ignore();
	if(get != nullptr){
		cout<<"Student Already exists..."<<endl;
		cout<<"Please login to continue.."<<endl;
		return nullptr;
	}
	
    ofstream fout("/home/ishan/project/data.txt" , ios::app);
	cout<<"Enter your First name"<<endl;
	getline(cin,n);
	cout<<"Enter your Last name"<<endl;
	getline(cin,nl);
	cout<<"Enter your department"<<endl;
	getline(cin,d);
	cout<<"Enter your e-mail"<<endl;
	getline(cin,e);
	cout<<"Create your password"<<endl;
	getline(cin,p);
	record* info = new record(r,n,nl,d,e,p);
	return info; 
}



// This function loads the entire database in a local database that is in our program through the file "data.txt" ... 

void initialization(db* g){
	ifstream fin("/home/ishan/project/data.txt");
	int rl = -1;
	string fname,lname,dept,email,password;
    while(1){
    	fin>>rl>>fname>>lname>>dept>>email>>password;
    	if(fin.eof())
    		break;
    	record* temp = new record(rl,fname,lname,dept,email,password);
    	g->insert(temp);
    }
    fin.close();

}


//	Here I am creating a vector function to extract branch and type of degree from roll no. for using in my hash map

vector<int> hash_func(int roll_no){				
    vector<int> v;
    int deg = roll_no%10000000;
    v.push_back(deg/1000000);
    int dept;
    dept = roll_no%1000000;
    dept = dept/1000;
    v.push_back(dept);

    v.push_back(roll_no%1000);
    return v;
} 


//	Validity of the input i.e the roll no is checked through this function 

bool valid_roll_no(int r){
	string s = to_string(r);
	int l = s.length();
	if(l==9)
		return true;
	return false;	
}


