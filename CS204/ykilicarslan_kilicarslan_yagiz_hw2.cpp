/***************************
Yagiz Kilicarslan 28126

In this code, a list of numbers are sequentially appended or deleted
according to the mode of order which can be Ascending or Descending.
To do this, we used Linked Lists which are crated with node structs
in which the value of integers are stored as well as a pointer to
be linked with a next node. With the usage of dynamically allocated
memory, deletion of unwanted nodes deallocate memory, allowing us to 
contain and operate with large number of nodes.
****************************/

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

/******************
stuct node: creates a node with integer value
and node pointer. Nodes that are connected with
next pointer form Linked Lists. 
Constructers:
	node(): value = NULL, next = NULL	This is default constructor
	node(V,N): value = V, next = N 

*******************/
struct node {
	int value;
	node* next;

	node(){  // Default Constructor
	};

	node(int V, node* N){  // Constructor
		value = V;
		next = N;
	};
};

/**********************************
add2list: takes last node (tail) and number 
as parameters, creates a node with value = number
and next = NULL then connects this node to the tail node

**********************************/
void add2list(node* &tail, int number){ // add new node to end of list
	node *temp = new node(number, NULL); // create new node
	tail->next = temp; // add to tail	
}

/*********************************
ListContent: takes head node as parameter. Prints every 
node that is in the Linked List.

**********************************/
void ListContent(node* &head){
	node *ptr = head;
	while(ptr->next != NULL){ // goes to the next node until that node is grounded
		cout << ptr->next->value << " ";
		ptr = ptr->next;
	}
	cout << endl;
}


/***********************************
deletedNodes: deletes every node including tail(parameter) from the Linked List.
Before deletion of each node, function prints values of these nodes.
If no node is deleted, it prints out None.

************************************/
/* Begin: code taken from ptrfunc.cpp	AND UPDATED*/
void deletedNodes(node* &tail){
	cout << "Deleted Nodes: ";
	int count = 0; // counting deleted nodes
	node *ptr;
	while (tail != NULL){
		ptr = tail->next;
		cout << tail->value << " ";
		delete tail;
		tail = ptr;
		count++;
	}
	if(count == 0){
		cout << "None";
	}
	cout << endl;
}/* End: code taken from ptrfunc.cpp */


int main(){
	
	string input, order; 
	cout << "Please enter the order mode (A/D): "; // asks for order mode
	getline(cin, input); // takes input from console as line 
	istringstream sStream(input); // converts string input to istringstream
	sStream >> order;  // from that istringstream, assigns the first string to 'order' variable 

	while (!(order == "A" || order == "D")){ // asks for a valid order mode until entered by user
		cout << "Please enter the order mode again (A/D): "; // repeats the above explained steps
		getline(cin, input);  
		sStream.clear(); // clears any error flags
		sStream.str(input); // reuses istringstream object after clearing buffer | this is more efficient than creating new objects
		sStream >> order; 
	}

	string line;
	int number;
	bool empty = false;
	cout << "Please enter the numbers in a line: "; // asks for line of numbers
	getline(cin, line); // takes 'line' variable from console as a line of string
	if(line.empty()){ // if line variable is empty
		cout << endl << "The list is empty at the end of the program and nothing is deleted" << endl;
		empty = true;
		return 0; // terminates
	}
	
	istringstream strStream(line); // converts 'line' into istringstream
	

	node *head = new node(NULL, NULL);// creates dynamic pointers with value = NULL, next = NULL 
	node *ptr = new node; 

	bool stop;
	while(strStream >> number){ // Takes each number from stringstream 
		stop = false; 
		ptr = head; // head is assigned to ptr pointer so that head itself is safe or not lost
		cout << endl <<"Next number: " << number << endl;
		
		if (ptr->next == NULL){ // if head is grounded 
			deletedNodes(ptr->next); // starting from next node of ptr, delete all nodes (in this case None) and print their values
			add2list(head, number); // add a new node with value=number and next=NULL to the last node of Linked List (in this case head)
			cout << "Appended: " << number << endl; // print number that is appended to the Linked List
			cout << "List content: " << number << endl; // print out all the Linked List (in this case just the last number)
		}

		else{ // if head is not grounded
			while (ptr->next != NULL && !stop){ // until if not last node or ordered to stop
				if ( (ptr->next->value > number && order == "A") || (ptr->next->value < number && order == "D") ){																						
					deletedNodes(ptr->next); //deletion and print of nodes that are bigger for Ascending order and that are smaller for Descending order 
					ptr->next = NULL; // grounds the node before the deletion 	
					cout << "Appended: " << number << endl;	 
					add2list(ptr,number); // adds the node to the last remaining node
					cout << "List Content: ";
					ListContent(head); // prints linkedList
					stop = true;	// stops the loop
				}
				else if (ptr->next->value == number){  // if node exist in list
					cout << number << " is already in the list!" << endl;
					cout << "List Content: ";
					ListContent(head); 
					stop = true;
				}
				else{
					ptr = ptr->next; // go to next node
				}
			}
			if (!stop){ // if not added or dublicate found 
				cout << "Deleted nodes: None" << endl; // can be replaced with deletedNodes(ptr->next), its trivial 
				cout << "Appended: " << number << endl; 
				add2list(ptr,number); //added to the end of linkedList
				cout << "List Content: ";
				ListContent(head);
			}
		}
	}

	if (!empty){
		cout << endl <<"All the nodes are deleted at the end of the program: ";
		ListContent(head);
	}

	return 0;
}