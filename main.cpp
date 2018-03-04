#include <cstdlib>
#include <iostream>

#include "Rparser.h"
#include "Node.h"
#include "Resistor.h"
#include "NodeList.h"
#include "ResistorList.h"

#define MIN_ITERATION_CHANGE 0.0001


using namespace std;

int main()
{
    //creating pointer and object NodeList
    NodeList *Nodehead = new NodeList();
    
    //calling the parser function to perform all
    //operations
    parser(Nodehead);
    
    //deleting the dynamically allocated memory
    delete Nodehead;
    return 0;
    
}
