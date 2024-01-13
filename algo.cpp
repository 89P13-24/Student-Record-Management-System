								/* This is a Student Record Management Program...*/

#include<iostream>
#include<fstream>
#include<string>
#include<bits/stdc++.h>

#include "comp.h"
#include "algo.h"

using namespace std;


// This function is to insert a record to its suitable place.(by using its roll no.)

void db::insert(record* temp){

	if(temp == nullptr)
		return;
	vector<int> v = hash_func(temp->roll_no);
	
	if(v[0] == 0){
		btech[v[1]][v[2]] = temp;
	}else if(v[0] == 4){
		mtech[v[1]][v[2]] = temp;
	}else{
		phd[v[1]][v[2]] = temp;
	}

} 

// This function is used to print details of a particular student

void db::print_record(record* p){
	cout<<"Roll_no:\t"<<p->roll_no<<endl;
	cout<<"Name:\t\t"<<p->name<<" "<<p->lname<<endl;
	cout<<"Department:\t"<<p->dept<<endl;
	cout<<"e-mail:\t\t"<<p->email<<endl;
	cout<<endl;	
}

/* This function is used to print the details of a subdivision. for example:-to print the records of each student in btech this 
		function will traverse through each department and then print its records using print_record function...
*/

void db::print_map(map<int ,map<int,record*> > m){
	map<int ,map<int,record*>>::iterator it = m.begin();	//	Iterator for the map- btech
	while(it != m.end()){
		//cout<<"Department:\t"<<it->first<<endl;
		map<int , record*>::iterator itr = it->second.begin();		// Iterator for each department in btech
		while(itr != it->second.end()){
			print_record(itr->second);
			++itr;
		}
		++it;
	}
}

//	This function prints all the data in the database..

void db::print_all(){
	cout<<"\n\t\t\t\tB.Tech students:-\n"<<endl;
	print_map(btech);
	cout<<"\t\t\t\tM.Tech students:-\n"<<endl;
	print_map(mtech);
	cout<<"\t\t\t\tPHD students:-\n"<<endl;
	print_map(phd);
}

//	This function is used to search a record using student's roll no.
//	If the record is present, it returns a pointer to that record else returns a null pointer...

record* db::search(int r){
	vector<int> v = hash_func(r);
	record* temp = nullptr;
	if(v[0] == 0)
		 temp = btech[v[1]][v[2]];
	else if(v[0] == 4)
		temp = mtech[v[1]][v[2]];
	else
		temp = phd[v[1]][v[2]];
	
	return temp;
}

//	This function ,as the name suggests, is to delete a record..
//	Since this function is important function and can impact our database only Admin has the power to use it.. 

void db::delete_record(int r){
	vector<int> v = hash_func(r);

	if(v[0] == 0)
		 btech[v[1]].erase(v[2]);
	else if(v[1] == 4)
		mtech[v[1]].erase(v[2]);
	else
		phd[v[1]].erase(v[2]);
}

