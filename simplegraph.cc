3/***********************************************************
CSCI 340 - Assignment 10 - Fall 2020

Programmer: Jonathan Chavez

Z-ID: z1866268

Section: 1

Date Due: December 2, 2020

Purpose: write a C++ program to implement several graph 
algorithms on simple graphs. These graphs are implemented with 
adjacency list representation.
************************************************************/ 

#include "simplegraph.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
#include <vector>

//int size = Getsize();
vector<bool> val;
string line1 = "";
string line2 = "";
bool val2;
//Global variables

using namespace std;

int main(int argc, char** argv) {
  if (argc < 2) {
    cerr << "args: input-file-name\n";
    return 1;
  }

  Graph g(argv[1]);

  g.Print();

  g.Traverse();

  return 0;
}

/**************************************************************
int Graph::Getsize() const

Use: Returns size

Parameters:
        1.) none
Returns: int
***************************************************************/


int Graph::Getsize() const
{
	return size;
}

/**************************************************************
Graph::~Graph(){}

Use: Destructor. Although its empty 
it's actually destructing the member variables

Parameters:
        1.) none
Returns: nothing
***************************************************************/

Graph::~Graph(){}

/**************************************************************
Graph::Graph(const char* filename)

Use: This is the constructor. It reads data in from the input 
file of the graph given in adjacency matrix representation and 
builds the graph with a adjacency list representation. This method 
sets the value of size, builds the vectors labels and adj_list.

Parameters:
        1.) const char* filename

Returns: nothing
***************************************************************/

Graph::Graph(const char* filename)
{
     	ifstream file;
        file.open(filename);

        list <int> numint;
        char letter;

        file >> size;

	val.resize(size);

   for(int i = 0; i < size; i++) //Initialization 
      {
              val[i] = false;
      }
 	//Initializes labels
	for(int i = 0;i < size ; i++)
        {
                file >> letter;
                labels.push_back(letter);
        }

	int one = 0;
	int itr = 0;
	//Initializes adj_list. First by initializing list then inserting list
	// into adj_list.
	while(itr < size)
	{
		itr++;
		file >> letter;

		for(int i = 0; i < size; i++) // This will record the adjencys through the 1 & 0s in the table
		{
			file >> one;
			if(one == 1)
				numint.push_back(i);
		}

		adj_list.push_back(numint); //Pushes bakc list into adj_list
		numint.clear();// This clear the list in order so that it can be used in the next iteration
}
}

/**************************************************************
void Graph::Print() const

Use: This function prints the adjacency list for the graph.

Parameters:
        1.) none

Returns: nothing
***************************************************************/

void Graph::Print() const
{
	cout << endl;
        cout << "Number of vertices in the graph: " << Getsize();
	cout << endl;

	cout << endl;

        cout << "-------- graph -------" << endl;

	for(int i = 0; i < size; i++)
	{
		cout << labels[i] << ": ";

		for(auto x: adj_list[i])// Range based loop easiest way to iterate through a vector full of list: adj_list
			cout << labels[x] << ", ";

		cout << endl;
	}
        cout << "------- end of graph ------" << endl;
}

/**************************************************************
void Graph::Depthfirst(int v)

Use: This private function is used to traverse a graph in the
depth-first traversal/search algorithm starting at the vertex
with the index value of v.

Parameters:
        1.) int v

Returns: nothing
***************************************************************/
void Graph::Depthfirst(int v)
{
	val[v] = true;

	ostringstream oss; // This makes it easier to add different strings together. Will do the same for string line2
	oss << line1 <<  labels[v] <<  " ";
	line1 = oss.str();

	for(auto x : adj_list[v]) //This will iterate through the contents of list that the vector adj_list contains
	{
		if(val[x] == false) // If the index is false this means label has not been visited
		{
			ostringstream oss2; 
			oss2 << line2 << "(" << labels[v] <<  ", " << labels[x] << ") ";
			line2 = oss2.str();
			Depthfirst(x);
		}
	}
}
/**************************************************************
void Graph::Traverse()

Use: his public function is used to traverse a graph and invokes
the above Depthfirst method.

Parameters:
        1.) none

Returns: nothing
***************************************************************/

void Graph::Traverse() 
{
	cout << endl;

	cout << "------- travere of graph ------" << endl;

	Depthfirst(0);

	int val3;
	for(int i = 0; i < size; i++) // Will iterate to other trees if they exist.
	{
		if(val[i] == 0)
		{
			val3 = i;
			Depthfirst(val3);
		}
	}

	cout << line1 << endl; // Will print string demonstrating labels
	cout << line2 << endl; // Will print string demonstrating adj_list

	cout << "--------- end of traverse -------" << endl;
	cout << endl;
}
