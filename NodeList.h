#ifndef NEWFILE_H
#define	NEWFILE_H
#include "Node.h"
#include "Resistor.h"
#include <iostream>
using namespace std;
 
class NodeList
{
private:
    Node*head;
    
public:
    NodeList();
    ~NodeList();
    
    Node* find_node(int nodeID);
    Node* find_or_insert_node(int nodeID);
    bool checkForDuplicateResistance(string name);
    bool change_resistance(string name, double &resistance);
    int delete_resistor(string name);
    void delete_all_resistor();
    Node* find_head_of_NodeList();
    int initialize_node_list(); 
    void solve();
    void print_voltage_for_each_node();
    double find_voltage(int nodeID);
    double find_voltage_for_one_term(int new_ID, double connected_resistance);
    bool checking_solve() const;
    Node* checkForExistingNode(int nodeID);
    bool checkExisitingResistor(string resistorName);
    void deleteAllNodes();
};
            
#endif	/* NEWFILE_H */
