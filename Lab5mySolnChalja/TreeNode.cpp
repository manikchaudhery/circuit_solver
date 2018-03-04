//
//  TreeNode.cpp
//  Lab5mySolnChalja
//
//  Created by Manik on 2017-08-23.
//  Copyright © 2017 Manik. All rights reserved.
//

#include "TreeNode.hpp"
#include "TreeDB.hpp"
#include "DBentry.hpp"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

TreeNode::TreeNode(DBentry* _entryPtr){
    entryPtr = _entryPtr;
    left = NULL;
    right = NULL;
}
TreeNode::~TreeNode(){
    //delete entryPtr;
}
void TreeNode::setLeft(TreeNode* newLeft){
    left = newLeft;
}
void TreeNode::setRight(TreeNode* newRight){
    right = newRight;
}
TreeNode* TreeNode::getLeft() const{
    return left;
}
TreeNode* TreeNode::getRight() const{
    return right;
}
DBentry* TreeNode::getEntry() const{
    return entryPtr; 
}
