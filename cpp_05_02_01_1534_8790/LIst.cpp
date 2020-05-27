// list.cpp

#include "List.h"
using namespace std;
//------------------------------------------------
// class Node implementation
//------------------------------------------------
List::Node::Node(int val, List::Node* nxt) : _value(val), _next(nxt) {}
List::Node::Node(const List::Node& src) : _value(src._value), _next(src._next) {}
int List::Node::value() const { return _value; }
List::Node* List::Node::next() const { return _next; }
void List::Node::next(Node* nxt) { _next = nxt; }

//--------------------------------------------
// class List implementation
//--------------------------------------------
List::List() : head(nullptr) {}

List::List(const List& other) {
	Node* src, * trg;
	if (other.head == nullptr)
		head = nullptr;
	else {
		head = new Node(other.head->value(), nullptr);
		if (head == nullptr)
			throw "failed in memory allocation";

		src = other.head;
		trg = head;
		while (src->next() != nullptr) {
			trg->next(new Node(src->next()->value(), nullptr));
			if (trg->next() == nullptr)
				throw "failed in memory allocation";
			src = src->next();
			trg = trg->next();
		}
	}
}

List::List(List&& other) : head(other.head)/* <- Keep the temp list is permanent*/ {
	// Avoid destructing it in the temporary object
	other.head = nullptr;
}

List::~List() {
	clear();
}

List& List::operator=(const List& other)
{
	Node* src, * trg;
	if (other.head == nullptr)
		head = nullptr;
	else {
		head = new Node(other.head->value(), nullptr);
		if (head == nullptr)
			throw "failed in memory allocation";

		src = other.head;
		trg = head;
		while (src->next() != nullptr) {
			trg->next(new Node(src->next()->value(), nullptr));
			if (trg->next() == nullptr)
				throw "failed in memory allocation";
			src = src->next();
			trg = trg->next();
		}
	}
}

List& List::operator=(List&& other)
{
	// Overrides the contents of the target 
	this->clear();
	// Keep the temp list is permanent
	head = other.head;
	// Avoid destructing it in the temporary object
	other.head = nullptr;

	return *this;
}

void List::clear() {
	// empty all elements from the List
	Node* next;
	for (Node* p = head; p != nullptr; p = next) {
		// delete the element pointed to by p
		next = p->next();
		p->next(nullptr);
		delete p;
	}
	// mark that the List contains no elements 
	head = nullptr;
}

bool List::isEmpty() const {
	// test to see if the List is empty
	// List is empty if the head pointer is null
	return head == nullptr;
}

void List::insert(int key)
{
	Node* q , * p;

	if (isEmpty())
		add(key);
	else
	{
		q = p = head;

		for (p = head; p != nullptr && p->value() < key; p = p->next())
			q = p;

		if (p == q)
			add(key);
		else
		{
			p = new Node(key, q->next());
			q->next(p);
		}
	}
}

void List::remove(int key)
{
	Node* p, * q = nullptr;

	if (!search(key))
		throw "value not found\n";

	// loop to find each element
	for (p = head; key != p->value(); p = p->next())
		q = p;

	// reassign the previous node
	q->next(p->next());
	p->next(nullptr);
	// recover memory used by the removed element
	delete p;
}

void List::add(int val) {
	//Add a new value to the front of a Nodeed List
	head = new Node(val, head);
	if (head == nullptr)
		throw "failed in memory allocation";
}

int List::firstElement() const {
	// return first value in List
	if (isEmpty())
		throw "the List is empty, no first Element";
	return head->value();
}

bool List::search(const int& val) const {
	// loop to test each element
	for (Node* p = head; p != nullptr; p = p->next())
		if (val == p->value())
			return true;
	// not found
	return false;
}

void List::removeFirst() {
	// make sure there is a first element
	if (isEmpty())
		throw "the List is empty, no Elements to remove";
	// save pointer to the removed node
	Node* p = head;
	// reassign the first node
	head = p->next();
	p->next(nullptr);
	// recover memory used by the first element
	delete p;
}

ostream& operator<<(ostream& out, const List& lst)
{
	for (List::Node* p = lst.head; p != nullptr; p = p->next())
		out << p->value() << " ";

	return out;
}

std::istream& operator>>(std::istream& in, List& lst)
{
	int current, previous;
	List::Node* p;

	in >> current;
	if (lst.head != nullptr)
		lst.clear();
	lst.head = new List::Node(current, nullptr);
	previous = current - 1;
	for (p = lst.head, in >> current; previous < current; p = p->next(), in >> current)
	{
		previous = current;
		p->next(new List::Node(current, nullptr));
	}

	return in;
}
