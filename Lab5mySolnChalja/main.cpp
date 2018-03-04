//
//  main.cpp
//  Lab5mySolnChalja
//
//  Created by Manik on 2017-08-21.
//  Copyright © 2017 Manik. All rights reserved.
//

#include <iostream>
#include <sstream>
#include "TreeDB.hpp"
#include "TreeNode.hpp"
#include "DBentry.hpp"
#include <string>
#include <iomanip>



void parser();

using namespace std;
int main() {
    parser();
    int *a;
    *a = 8;
    return 0;
}
void parser(){
    TreeDB entireTree; //object that is the whole tree

    cout<<"> ";
    string command;
    string line;
    getline (cin, line);
    while ( !cin.eof () ) {
    stringstream lineStream(line);
        string command;
        string domainName;
        unsigned int address;
        string status;
        bool insertSuccessful = true;
        bool active = true;
        lineStream>>command;
        lineStream>>domainName;
        lineStream>>address;
        lineStream>>status;
        if(status=="inactive")
            active = false;
    stringstream commandStream(line);
    commandStream>>command;
    if(command == "insert")
    {/*
        DBentry* newEntryPtr = NULL
        DBentry newEntry(domainName,address,active);//Data inside a node of the tree and treeNode will form each node.
        newEntryPtr = &newEntry;*/ // WRONG
        DBentry* newEntryPtr = new DBentry(domainName,address,active);//Data inside a node of the tree and treeNode will form each node. IMPORTANT : Creating a new object with this pointer every time this line is run, so that we don't have a problem with the root pointing to the same object and getting affecting by the change.
        insertSuccessful = entireTree.insert(newEntryPtr);//TRUE IF SUCCESSFUL. NOW PASSING A NEW OBJECT EVERY TIME
    }
    else if(command == "printall")
    {
        entireTree.printAll();
    }
    else if(command == "find")
    {
        DBentry* found = entireTree.find(domainName);
        if(found==NULL)
            cout<<"“Error: entry does not exist"<<endl;
        delete found;
    }
    cout<<"> ";
    getline (cin, line);
    }
}
