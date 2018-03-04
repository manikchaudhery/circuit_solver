#ifndef Rparser_h
#define Rparser_h

using namespace std;
#include <string>
#include <iostream>
#include <iomanip>
#include "Node.h"
#include "Resistor.h"
#include "ResistorList.h"
#include "NodeList.h"

void parser(NodeList *&Nodehead);

void insertR(string line, NodeList *&Nodehead);

void modifyR(string line, NodeList *&Nodehead);

void deleteR(string line, NodeList *&Nodehead);

bool printNode(string line, NodeList *&Nodehead);

void printR(string line, NodeList *&Nodehead);

//sets voltage as if connected to a battery
void setVCommand(string line, NodeList *&Nodehead);

//sets voltage back to 0
void unsetV(string line, NodeList *&Nodehead);

void solveCommand(string line, NodeList *&Nodehead);

void tooManyArgs();
void tooFewArgs();

void invalidArg();
bool outOfRange(int node);

//error checking command
void error_invaild_argument(stringstream& copy_linestream, string& line);

#endif

