// List.h
#ifndef __LIST_H
#define __LIST_H

#include<iostream>

//------------------------------------------------
// Class List - Arbitrary size Lists
// Permits insertion and removal only from the front of the List
//------------------------------------------------
class List {
protected:
	//--------------------------------------------
	// inner class Node a single element for the Nodeed List
	//--------------------------------------------
	class Node {
		int   _value;
		Node* _next;
	public:
		// constructor
		Node(int, Node*);
		Node(const Node&);
		// data areas
		int   value() const; // getter only
		Node* next() const;  // getter
		void  next(Node*);   // setter
	}; //end of class Node

public:
	// constructors
	List();
	List(const List&);
	List(List&&);
	~List();
	// operations
	List& operator = (const List& other);
	List& operator = (List&& lst);
	friend std::ostream& operator << (std::ostream& out,const List& lst);
	friend std::istream& operator >> (std::istream& in, List& lst);
	void insert(int key);
	void remove(int key);
	void add(int value);
	int  firstElement() const;
	bool search(const int&) const;
	bool isEmpty() const;
	void removeFirst();
	void clear();

protected:
	// data field
	Node* head;
};

std::ostream& operator << (std::ostream& out,const List& lst);
std::istream& operator >> (std::istream& in,List& lst);
#endif //__LIST_H

