//
//  DBentry.cpp
//  Lab5mySolnChalja
//
//  Created by Manik on 2017-08-23.
//  Copyright © 2017 Manik. All rights reserved.
//

#include "DBentry.hpp"
#include <sstream>
#include "TreeDB.hpp"
#include "TreeNode.hpp"
#include <string>
#include <iomanip>

DBentry::DBentry(){
    name = "";
    IPaddress = 0;
    active = false; 
}
DBentry::DBentry(string _name, unsigned int _IPaddress,
                 bool _active){
    name = _name;
    IPaddress = _IPaddress;
    active = _active;
}
DBentry::~DBentry(){
// since no dynamic declarations for this object
}
void DBentry::setName(string _name){
    name = _name;
}
void DBentry::setIPaddress(unsigned int _IPaddress){
    IPaddress = _IPaddress;
}
void DBentry::setActive (bool _active){
    active = _active; //either true or false
}
string DBentry::getName() const{ // WTF IS THE CONSTANT DOING HERE
    return name;
}
bool DBentry::getActive() const{
    return active;
}
unsigned int DBentry::getIPaddress() const{
    return IPaddress;
}
// prints the entry in the format
// name : IPaddress : active followed by newline
// active is printed as a string (active or inactive)
/*friend DBentry::ostream& operator<< (ostream& out, const DBentry& rhs){
    
}*/
void DBentry::print(){
    string activeOrNot;
    if(active == true)
        activeOrNot = "active";
    else if(active == false)
        activeOrNot = "inactive";
    cout<<name<<" "<<IPaddress<<" "<<activeOrNot<<endl;
}
