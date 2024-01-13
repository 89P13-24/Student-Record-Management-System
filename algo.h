#ifndef algo_h
#define algo_h



class record{
public:
    int roll_no;
    std::string name;
    std::string lname;
    std::string dept;
    std::string email;
    std::string password;
    std::string user_id;
    record (int r, std::string n , std::string l , std::string d , std::string e , std::string p){
    	this->roll_no = r;
    	this->name = n;
    	this->lname = l;
    	this->dept = d;
    	this-> email = e;
    	this-> password = p;
    }
	record(){}
};

class db{
public:
	    std::string ad_p = "DSAI@2023";
	std::map<int ,std::map<int,record*> > btech;
	std::map<int ,std::map<int,record*> > mtech;
    std::map<int ,std::map<int,record*> > phd;
    //map<int,record*> student;
	void insert(record* temp);
	void print_record(record* p);
	void print_map(std::map<int ,std::map<int,record*> >);
	void print_all();
	void delete_record(int r);
	record* search(int r);
};


#endif
