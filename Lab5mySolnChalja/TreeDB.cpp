//
//  TreeDB.cpp
//  Lab5mySolnChalja
//
//  Created by Manik on 2017-08-23.
//  Copyright © 2017 Manik. All rights reserved.
//

#include "TreeDB.hpp"
#include <sstream>
#include "TreeNode.hpp"
#include "DBentry.hpp"
#include <string>
#include <iomanip>

TreeDB::TreeDB(){
    root = NULL;
    probesCount = 0;
}
TreeDB::~TreeDB(){
    delete root;
}
bool TreeDB::insert(DBentry *newEntry){
    
    TreeNode *newNodePtr; //newNode is now pointing to an object of Treenode
    newNodePtr = new TreeNode(newEntry);//constructor of TreeNode initializes values of entryPtr to contain the information in the newEntry nd sets right and left links to NULL
    //newNode's entryPtr is pointing to newEntry.
    bool inserted = true;
    
    TreeNode *current = root;
    if(root == NULL)
    {
        root = newNodePtr;//root is equal to the memory location where newNodePtr is pointing to. LL and RL are already pointing to NULL in this case
        //inserted is already true
    }
    else
    inserted = insertRecursionFunction(newNodePtr, current);
    if(inserted){
        cout<<"Success"<<endl;
        return true;
    }
    else
        cout<<"Error: entry already exists"<<endl;
    return false;
}
/*
DBentry* TreeDB::find(string name){
    
}*/
bool TreeDB::insertRecursionFunction(TreeNode *newNodePtr, TreeNode *current){
    if(newNodePtr->getEntry()->getName() == current->getEntry()->getName())
    {
        delete newNodePtr;
        return false; // if false is returned that means domain name already exists
    }
    else if(newNodePtr->getEntry()->getName() < current->getEntry()->getName())
    {
        if(current->getLeft()==NULL){
            current->setLeft(newNodePtr);
            cout<<"Left"<<endl;
            return true;
            
        }
        //else recursively look in the left half of the tree
        else
            return insertRecursionFunction(newNodePtr, current->getLeft()); //I had written newNodePtr instead of current here so was getting an error
    }
    
    //Now looking on right side
    
    else if(newNodePtr->getEntry()->getName() > current->getEntry()->getName())
    {
        if(current->getRight()==NULL){
            current->setRight(newNodePtr);
            cout<<"Right"<<endl;
            return true;
            
        }
        //else recursively look in the left half of the tree
        else
            return insertRecursionFunction(newNodePtr, current->getRight());
    }
    
    return false;
}
void TreeDB::printTreeHelper(TreeNode *current){
    
    if (current->getLeft() != NULL)
        printTreeHelper(current->getLeft()); //goes down left subtrees first to get names that come first alphabetically
    
       current->getEntry()->print();
    
    if (current->getRight() != NULL)
        printTreeHelper(current->getRight()); //goes down right subtree for names that come later
    
    /*if (current->getLeft()!=NULL){
        printTreeHelper(current->getLeft());
    }
    else if(current->getRight()!=NULL){
        printTreeHelper(current->getRight());
    }
    else
        current->getEntry()->print();
    return;*/
    
}

void TreeDB::printAll(){
    if(root == NULL)
        return;
    printTreeHelper(root);
}
DBentry* TreeDB::findRecursionFunction(string name, TreeNode* current){
    DBentry* found=NULL;
    if(current->getEntry()->getName() == name)
        found = current->getEntry();
    else if(name<current->getEntry()->getName())
        return findRecursionFunction(name, current->getLeft());
    else if(name>current->getEntry()->getName())
        return findRecursionFunction(name, current->getRight());
    return found;
}
DBentry* TreeDB::find(string name){
    DBentry* found = NULL; //will remain NULL if nothing matching is found
    if(name == root->getEntry()->getName())
    {
        found = root->getEntry();
    }
    else
        found = findRecursionFunction(name, root);
    if(found!=NULL)
        found->print();// insert : in between name:ipaddress:active
    return found;
}


