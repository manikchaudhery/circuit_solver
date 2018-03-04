//
//  TreeNode.hpp
//  Lab5mySolnChalja
//
//  Created by Manik on 2017-08-23.
//  Copyright © 2017 Manik. All rights reserved.
//

#ifndef TreeNode_hpp
#define TreeNode_hpp

#include <stdio.h>
#include <iostream>
#include "DBentry.hpp"

class TreeNode {
private:
    DBentry* entryPtr;
    TreeNode* left;
    TreeNode* right;
public:
    // A useful constructor
    TreeNode(DBentry* _entryPtr);
    // the destructor
    ~TreeNode();
    // sets the left child of the TreeNode.
    void setLeft(TreeNode* newLeft);
    // sets the right child of the TreeNode
    void setRight(TreeNode* newRight);
    // gets the left child of the TreeNode.
    TreeNode* getLeft() const;
    // gets the right child of the TreeNode
    TreeNode* getRight() const;
    // returns a pointer to the DBentry the TreeNode contains.
    DBentry* getEntry() const;
};
#endif /* TreeNode_hpp */
