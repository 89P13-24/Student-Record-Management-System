#ifndef COMP_H
#define COMP_H

#include "algo.h"


record* info(db g);
void initialization(db* g);

bool valid_roll_no(int r);

void write(record* Data , std::ofstream& fnew);
void write_map(std::map<int ,std::map<int,record*> > m , std::ofstream& fnew);
void update_database(db g);
std::vector<int> hash_func(int roll_no);



#endif
