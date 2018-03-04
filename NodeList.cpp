#include "Node.h"
#include "NodeList.h"
#include "ResistorList.h"
using namespace std;
#include <cmath>        // std::abs

 #define MIN_ITERATION_CHANGE 0.0001

NodeList::NodeList()
{
    head = NULL;
}

NodeList::~NodeList()
{
    //deleting all resistors first
    delete_all_resistor();
    
    //delete all nodes at the end of run
    deleteAllNodes();
    
}

void NodeList::deleteAllNodes()
{
    // do not delete anything if head is pointing to NULL
    if(head == NULL)
    {
        return;
    }
    Node* temp = head->getNextNode();
    
    //deleting everything except head Node
    while(temp!=NULL) // as I am considering tail->next = NULL
    {
        //making head point to where temp was pointing
        head->set_next_node(temp->getNextNode());
        
        //making temp's pointer to nothing
        temp->set_next_node(NULL);
        
        //now deleting temp
        delete temp;
        temp = head->getNextNode();
    }
    //now delete head
    delete head;
    return;
    
}

 Node* NodeList::find_head_of_NodeList()
 {
     return head;
 }
 

Node* NodeList::find_node(int nodeID)
{
    Node *ptr = NULL;
    for(ptr = head; ptr != NULL ; ptr = ptr->getNextNode())
    {
        if(nodeID == ptr->get_NodeID())
        {
            return ptr;
        }
        if(nodeID < ptr->get_NodeID())
        {
            return NULL;
        }
    }
    
    head = NULL;
    return NULL;
}

Node* NodeList::checkForExistingNode(int nodeID)
{
    Node *ptr = NULL;
    
    for(ptr = head; ptr != NULL ; ptr = ptr->getNextNode())
    {
        if(nodeID == ptr->get_NodeID())
        {
            return ptr;
        }
    }
    return NULL;
}

Node* NodeList::find_or_insert_node(int nodeID)
{
    Node* pointer;
    
    pointer = checkForExistingNode(nodeID);
    
    if(pointer!=NULL)
    {
        return pointer;
    }
    //head = NULL;
    Node* previous = NULL;//insert the correct position in the node list
    Node* current = head;

    while(current != NULL && nodeID > current->get_NodeID())//not the end of list and ID larger the current checking position
    {
//        cout << "inside the updating process" << endl;
        previous = current;
        current = current-> getNextNode();//update the curr position
    }
    
    Node *newNode = new Node(nodeID, current);//connect the position to next

    if(previous == NULL)
    {
//        cout << "NodeList_inside1"<< endl;
        head  = newNode;//empty list and NodeID smaller than first node
    }
    else
    {
//        cout << "NodeList_inside2" << endl;
        previous-> set_next_node(newNode);
    }
    return newNode;
}


bool NodeList::checkForDuplicateResistance(string name)
{
    Node *ptr = head;
    
    //traversing the whole nodeList
    while(ptr != NULL)
    {
        //getting the resistorList of current Node
        Resistor *ptr1 = ptr->get_resistorList().get_head_ResistorList();
        
        //traversing the resistor List
        while(ptr1 != NULL)
        {
            if(name == ptr1->getName())
            {
                //resistor name found and printing
                ptr1->print();
                return true;
            }
            //otherwise keep traversing in resistor list
            ptr1 = ptr1 -> get_resistor_next();
        }
        //go to next node and check its resistors
        ptr = ptr->getNextNode();
    }
   return false;
}
bool NodeList::checkExisitingResistor(string resistorName)
{
    Node *ptr = head;
    
    //traversing the whole nodeList
    while(ptr != NULL)
    {
        //getting the resistorList of current Node
        Resistor *ptr1 = ptr->get_resistorList().get_head_ResistorList();
        
        //traversing the resistor List
        while(ptr1 != NULL)
        {
            //resistor name found
            if(resistorName == ptr1->getName())
            {
                return true;
            }
            //otherwise keep traversing
            ptr1 = ptr1 -> get_resistor_next();
        }
        ptr = ptr->getNextNode();
    }
    return false;
}

  bool NodeList::change_resistance(string name, double& resistance)
 {
    //looking in the list of nodes for resistor
     
    Node *ptr = head;
    double resistance1 = resistance;
    bool found = false;//check find the resistor or not
    bool flag = false;
    while(ptr != NULL)
    {
        
        Resistor *ptr1 = ptr ->get_resistorList().get_head_ResistorList();;
        
        while(ptr1 != NULL)
        {
            //if resistor located
            if(name == ptr1->getName())
            {  
                if(!flag)
                {
                        resistance = ptr1->getResistance();
                        flag = true; //resistor name changed
                }
                
                ptr1->setResistance(resistance1);
                found = true;
                break;
            }
            ptr1 = ptr1 -> get_resistor_next();
        }
        ptr = ptr->getNextNode();
    }
    return found;
 }
 
 
 int NodeList::delete_resistor(string name)
 {
    Node *ptr = NULL;//head for NodeList(node type)
    int checking = 0;
    if(head == NULL)
    {
        return checking;
    }
    else
    {
        for(ptr = head; ptr != NULL ; ptr = ptr->getNextNode())
        {
            Resistor* prev = NULL;
            Resistor* ptr1 = NULL;//pointer for ResistorList(resistor type)
                for(ptr1 =  ptr -> get_resistorList().get_head_ResistorList(); ptr1 != NULL; ptr1 = ptr1 -> get_resistor_next())
                {    
                    Resistor* copy_for_ptr1 = NULL;
                    copy_for_ptr1 = ptr1;
                  if(name == copy_for_ptr1->getName())
                  {
                      checking++;
                      if(prev != NULL)
                      {
                          prev -> set_next_resistor(copy_for_ptr1 -> get_resistor_next()); //not at the start of link list
                      }
                      else
                      {
                          ptr->get_resistorList().set_head_ResistorList(copy_for_ptr1 -> get_resistor_next());//start of link list
                      }
                      delete copy_for_ptr1;
                      break;
                   }
                  prev = ptr1;//update the prev pointer          
                }
        }       
        return checking;
    }
 }
 
 void NodeList::delete_all_resistor()
 {
    Node *ptr = NULL;//head for NodeList(node type)
   
     //empty list
     //no nodes in the list
    if(head == NULL)
    {
         return;
    }
    
    else
    {
        for(ptr = head; ptr != NULL; ptr = ptr->getNextNode())
        {

            Resistor *ptr1 = NULL;//pointer for ResistorList(resistor type)
            
//            cout << ptr->get_NodeID() << endl;
                ptr1 =  ptr -> get_resistorList().get_head_ResistorList();
            
            while(ptr1 != NULL)
                {

                    //cout << "prev " << prev << " ptr1 " << ptr1->getName(); 
                   
                    Resistor* ptr2 =  ptr1;//ptr2 is used to copy ptr1 and delete the memory of ResistorList

                          //find the head of ResistorList first, then let the head point to the next
                    
//                    ptr -> get_resistorList().set_head_ResistorList(ptr->get_resistorList().get_head_ResistorList()->set_next_resistor_and_return(ptr2 -> get_resistor_next()));//start of link list
                    //setting ptr2
                    ptr -> get_resistorList().set_head_ResistorList(ptr2 -> get_resistor_next());//start of link list
                    //cout << " ptr2_in_the_head " << ptr2->getName() << endl; 
                      
                      delete ptr2;
                      ptr2 = NULL;
                      ptr1 = ptr->get_resistorList().get_head_ResistorList();
               }                   
         }
        
        return;  
     }       
 }
 
 



//calculate the current per term
double NodeList::find_voltage_for_one_term(int new_ID, double connected_resistance)
{
    Node* ptr1 = NULL;
    double current = 0;
    double connected_node_volt = 0;
    for(ptr1 = head; ptr1 != NULL; ptr1 = ptr1->getNextNode())
    {        
        if(new_ID == ptr1->get_NodeID())
        {                                                
             connected_node_volt = ptr1->get_voltage();//get the voltage for that new nodeID
             current = connected_node_volt/connected_resistance;//add the current each time                                          
        }
    }
    return current;

}
 

    
    
 void NodeList::solve()
 { 
     
     double iteration_change = 0;
     bool beginning = true;
     double sum_resistance = 0;
     double sum_current = 0;
     double new_voltage = 0;
     double difference = 0;

     while(MIN_ITERATION_CHANGE < iteration_change || beginning == true)
     {
         Node *nodeTraverser;
         beginning = false; 
         double max_iteration_change = 0;
         
            for(nodeTraverser = head; nodeTraverser != NULL; nodeTraverser = nodeTraverser->getNextNode())            
            {
            
                Resistor* resistorList_ptr = NULL;

                //if the node's voltage has not been set yet
                //returns false
                
                if(!nodeTraverser->get_set_bool())
                {
                        int nodeID = nodeTraverser->get_NodeID();
                    
                    //iterate throught the resistor list of that particular node
                        for(resistorList_ptr = nodeTraverser->get_resistorList().get_head_ResistorList(); resistorList_ptr != NULL; resistorList_ptr =  resistorList_ptr->get_resistor_next())
                        
                        {
                            //getting the sum of all the resistances
                               sum_resistance = sum_resistance + 1/(resistorList_ptr->getResistance());
                            
                            int new_ID = resistorList_ptr->get_NodeID(nodeID);//find another new NodeI

                             
                               double  current_per_term = find_voltage_for_one_term(new_ID, resistorList_ptr->getResistance());
                            
                            sum_current = sum_current + current_per_term;
                               
                        }
                        new_voltage = (1/sum_resistance)*sum_current;

                        difference = new_voltage - nodeTraverser->get_voltage();
                        
                        if(abs(difference) > max_iteration_change)
                        {
                            max_iteration_change = abs(difference);
                        }
                        
                        nodeTraverser->set_voltage_without_bool(new_voltage);
                        sum_resistance = 0;
                        sum_current = 0;
                }
                
             }
          iteration_change = max_iteration_change;
//          cout<<iteration_change<<endl;
          
     }
                  
 }
  

 

 
 void NodeList::print_voltage_for_each_node()
 {
     Node* ptr = NULL;
     cout << "solve" << endl;
     for(ptr = head; ptr != NULL; ptr = ptr->getNextNode())
     {
         cout << "  " <<"Node " <<  ptr->get_NodeID() << ": " << ptr->get_voltage() << " V"<<endl;
//         cout <<  "  " << ptr->get_set_bool() << endl;
     }  
 }
