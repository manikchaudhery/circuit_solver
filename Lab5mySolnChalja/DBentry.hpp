//
//  DBentry.hpp
//  Lab5mySolnChalja
//
//  Created by Manik on 2017-08-23.
//  Copyright © 2017 Manik. All rights reserved.
//

#ifndef DBentry_hpp
#define DBentry_hpp

#include <stdio.h>
#include <sstream>
#include <string>
#include <iomanip>
#include <iostream>

using namespace std;

class DBentry {
private:
    string name;
    unsigned int IPaddress;
    bool active;
public:
    // constructors
    DBentry();
    DBentry (string _name, unsigned int _IPaddress,
             bool _active);
    // the destructor
    ~DBentry();
    // sets the domain name, which we will use as a key.
    void setName(string _name);
    // sets the IPaddress data.
    void setIPaddress(unsigned int _IPaddress);
    // sets whether or not this entry is active.
    void setActive (bool _active);
    // returns the name.
    string getName() const;
    // returns the IPaddress data.
    unsigned int getIPaddress() const;
    // returns whether or not this entry is active.
    bool getActive() const;
    // prints the entry in the format
    // name : IPaddress : active followed by newline
    // active is printed as a string (active or inactive)
    friend ostream& operator<< (ostream& out, const DBentry& rhs);
    void print();
};

#endif /* DBentry_hpp */
