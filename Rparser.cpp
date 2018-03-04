#include <iostream>
#include <sstream>
#include <string>
#include "Rparser.h"

using namespace std;

void parser(NodeList *&Nodehead)
{
    
    string line, command;
    double resistance = 0.0;
    double voltage = 0.0;
    int node1 = 0;
    int node2 = 0;
    int nodesOfResistor[2] = {0,0};
    int nodeID = 0;
    double unsetVolatage = 0;
    
    cout<<"> ";
    getline (cin, line);
    
    while ( !cin.eof () ) {
        
        int numberOfWords=0;
        stringstream lineStream(line);
        
        while(lineStream >>command){
            numberOfWords++;
        }
        
        stringstream commandStream(line);
        commandStream>>command;
        
        if((command!="insertR" && command!="modifyR" && command!="printR" && command!="printNode" && command!="deleteR" && command!="printNode" && command!="solve"&& command!="setV" && command!="unsetV"))
            
        {
            cout<<"Error: invalid command"<<endl;
        }
        if(command == "insertR")
        {
            // parse an insertR command
            insertR(line, Nodehead);
        }
        else if(command == "modifyR")
        {
            modifyR(line, Nodehead);
            
        }
        
        else if(command == "printR")
        {
            printR(line, Nodehead);
        }
        
        else if(command == "printNode")
        {
            printNode(line, Nodehead);
        }
        
        else if(command == "deleteR")
        {
            deleteR(line, Nodehead);
        }
        
        else if(command == "setV")
        {
            setVCommand(line, Nodehead);
        }
        
        else if(command == "unsetV")
        {
            unsetV(line, Nodehead);
        }
        
        else if(command == "solve")
        {
            solveCommand(line, Nodehead);
        }
        
        
        cout << "> ";
        getline(cin, line);
    }// End input loop until EOF.
    
}

void insertR(string line, NodeList *&Nodehead)
{
    //storing the string line into another stringstream
    stringstream linestream(line);
    string resistorName, command;
    
    int node1, node2;
    double resistance;
    
    //reading the values from linestream
    linestream>>command;
    linestream>>resistorName;
    
    //since all is an invalid command
    if(resistorName=="all"){
        cout<<"Error: resistor name cannot be the keyword \"all\"" <<endl;
        return;
    }
    
    linestream>>resistance;
    linestream>>node1;
    linestream>>node2;
    
    //inserting the nodes in the nodelist
    //inserting the resistor in each of the
    //specified node's resistor list
    
    int endpoints[2];
    endpoints[0] = node1;
    endpoints[1] = node2;
    
    bool duplicateResistor = Nodehead->checkExisitingResistor(resistorName);
    
    if(duplicateResistor)
    {
        cout<<"Error: resistor " <<resistorName<<" already exists"<<endl;
        return;
    }
    
    else
    {
        int print_once = 0;
        
        Nodehead -> find_or_insert_node(node1) -> get_resistorList().insert_resistor_at_end(resistance, resistorName,  endpoints, print_once);
        
        Nodehead -> find_or_insert_node(node2) -> get_resistorList().insert_resistor_at_end(resistance, resistorName,  endpoints, print_once);
    }
}

void modifyR(string line, NodeList *&Nodehead)
{
    string name_resistor, command;
    double resistance = 0;
    //    storing the string line into another stringstream
    stringstream linestream_copy(line);
    
    linestream_copy>>command;
    linestream_copy>>name_resistor;
    linestream_copy>>resistance;
    
    double changed_resistance = resistance;
    
    
    //change the requested resistor's resistance
    bool find = Nodehead->change_resistance(name_resistor, resistance);
    
    if(!find)
    {
        cout << "Error: resistor " <<  name_resistor << " not found" << endl;
    }
    
    else
    {
        cout << "Modified: resistor " << name_resistor << " from " << fixed <<setprecision(2) <<resistance << " Ohms to " << fixed <<setprecision(2) << changed_resistance << " Ohms"<<  endl;
    }
}

void deleteR(string line, NodeList *&Nodehead)
{
    string name_resistor, command;
    stringstream linestream(line);
    
    linestream>>command;
    linestream>>name_resistor;
    
    //    special case for all
    if(name_resistor == "all")
    {
        Nodehead->delete_all_resistor();
        cout << "Deleted: all resistors" << endl;
    }
    else
    {
        int checking = Nodehead->delete_resistor(name_resistor);
        if(checking != 0)
        {
            cout << "Deleted: resistor " << name_resistor << endl;
        }
        else
        {
            cout << "Error: resistor " <<  name_resistor << " not found" << endl;
        }
        
    }
}

bool printNode(string line, NodeList *&Nodehead)
{
    
    stringstream linestream(line);
    string command, checkForAll; // checkForAll checks to see if node is "all"
    int nodeId = 0;
    bool fail = true;
    linestream>>command;
    linestream>>nodeId; // reading expected integer data type
    
    if (linestream.fail()) {// if data type was not of integer type
        
        if (linestream.eof())
            
        { // if encountered an end of file instead of expected integer
            tooFewArgs();
            linestream.clear();
            return false;
        }
        else
        {
            // if NOT an EOF
            linestream.clear();
            linestream>>checkForAll;
            if (checkForAll != "all")
                //other than an integer type number, command can only be all
                
                invalidArg();
            
            else if (checkForAll == "all")
            {
                char peekCharacter = linestream.peek();
                while (peekCharacter == ' ' || peekCharacter == '\t') {
                    peekCharacter = linestream.get();
                }
                
                if (peekCharacter != EOF) {
                    tooManyArgs();
                    linestream.clear();
                    return false;
                }
                cout << "Print:" << endl;
                Node *ptr = NULL;//head for NodeList(node type)
                for(ptr = Nodehead->find_head_of_NodeList(); ptr != NULL ; ptr = ptr->getNextNode())
                {
                    int counter = 0;
                    
                    Nodehead->find_node(ptr->get_NodeID())->get_resistorList().find_number_of_resistor_inserted(counter);
                    
                    Nodehead->find_node(ptr->get_NodeID())->print(ptr->get_NodeID(), counter);
                    
                    Nodehead->find_node(ptr->get_NodeID())->get_resistorList().find_number_of_resistor_inserted_print_statement();
                }
                return true; // cout << "Error: too many arguments" << endl;
            }
        }
    }
    else
    {
        char peekCharacter = linestream.peek();
        
        if (peekCharacter != ' ' && peekCharacter != EOF && peekCharacter != '\t') {
            invalidArg();
            linestream.clear();
            return false;
        }
        
        else
        {
            bool inRange = outOfRange(nodeId);
            if (inRange == false)
                return false;
            
            else {
                while (peekCharacter == ' ' || peekCharacter == '\t') {
                    peekCharacter = linestream.get();
                }
            }
            if (peekCharacter != EOF) {
                tooManyArgs();
                linestream.clear();
                return false;
            }
            
            int counter1 = 0;
            //find how many resistors inside one nodeID
            
            Node* checkExisting = Nodehead->checkForExistingNode(nodeId);
            //checking to see if the node exists or not
            if(checkExisting != NULL)
            {
                
                cout << "Print: " << endl;
                
                Nodehead->find_node(nodeId)->get_resistorList().find_number_of_resistor_inserted(counter1);
                
                Nodehead->find_node(nodeId)->print(nodeId, counter1);
                
                Nodehead->find_node(nodeId)->get_resistorList().find_number_of_resistor_inserted_print_statement();
            }
            else
                cout<<"Error: node "<< nodeId <<" not found" <<endl;
            return true;
        }
    }
    return false;
}

void printR(string line, NodeList *&Nodehead)
{
    string command, resistorName;
    stringstream linestream(line);
    linestream>>command;
    linestream>>resistorName;
    
    bool flag1 = Nodehead->checkForDuplicateResistance(resistorName);//for printing the resistor
    
    if(!flag1)
    {
        cout << "Error: resistor " <<  resistorName << " not found" << endl;
    }
}


void setVCommand(string line, NodeList *&Nodehead)
{
    double voltage = 0;
    int nodeID = 0;
    stringstream linestream(line);
    string command;
    
    linestream>>command;
    linestream>>nodeID;
    linestream>>voltage;
    
    if(!Nodehead->find_node(nodeID))
    {
        cout<<"Error: node "<< nodeID <<" not found" <<endl;
        return;
    }
    else
    {
        Nodehead->find_node(nodeID)->set_voltage(voltage);
    }
    cout << "Set: node " << nodeID << " to " << voltage << " Volts" << endl;
    
}

void unsetV(string line, NodeList *&Nodehead)
{
    int nodeID;
    stringstream linestream(line);
    string command;
    
    linestream>>command;
    linestream>>nodeID;
    
    if(!Nodehead->find_node(nodeID))
    {
        cout<<"Error: node "<< nodeID <<" not found" <<endl;
        return;
    }
    else
    {
        Nodehead->find_node(nodeID)->unset_voltage();
    }
    cout << "Unset: the solver will determine the voltage of node " << nodeID << endl;
}

void solveCommand(string line, NodeList *&Nodehead)
{
    //helps iterate through the list of nodes
    Node* traverseNodes = NULL;
    bool flag = true;
    
    
    traverseNodes = Nodehead->find_head_of_NodeList();
    
    //while not hitting the end of the list
    while(traverseNodes != NULL)
    {
        //checking if node has been set to a voltage
        bool checkIfSet = traverseNodes->get_set_bool();
        
        //if node has been set to a voltage
        //solve according to that node's voltage
        if(checkIfSet)
        {
            Nodehead->solve();
            Nodehead->print_voltage_for_each_node();
            flag = false;
        }
        traverseNodes = traverseNodes->getNextNode();
    }
    if(flag)
    {
        cout << "Error: no nodes have their voltage set" << endl;
    }
}
void tooManyArgs() {
    cout << "Error: too many arguments" << endl;
}

void tooFewArgs() {
    cout << "Error: too few arguments" << endl;
}

void invalidArg() {
    cout << "Error: invalid argument" << endl;
}
bool outOfRange(int node) {
    
    if (node < 0) {
        return false;
    } else
        return true;
}
