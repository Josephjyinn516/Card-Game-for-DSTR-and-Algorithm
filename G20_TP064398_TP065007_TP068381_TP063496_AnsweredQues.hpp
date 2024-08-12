#pragma once
#include <iostream>
using namespace std;
//stack data struc, last in first out (latest answered question are shown)

//Define structure for the stack node
struct StackNode //singly linked list 
{
	int QuesID;
	string question;
	string answer;
	int score;
	//string data; 
	StackNode* next;

	StackNode(int id, string ques, string ans, int sc) : QuesID(id), question(ques), answer(ans), score(sc), next(nullptr) {}
};

//flow: 

//functions

//Define custom stack class
class AnsweredQuestionsStack
{/*
private: */
	StackNode* top, * bottom;
	int size;
	string ques = "";

public:
	//Constructor
	AnsweredQuestionsStack(string ques)
	{
		top = bottom = nullptr;
		size = 0;
		this->ques = ques;
	}
	//AnsweredQuestionsStack() : top(nullptr), size(0) {} 

	//Destrcutor to free up memory
	~AnsweredQuestionsStack()
	{
		while (top != nullptr)
		{
			StackNode* temp = top;
			top = top->next;
			delete temp;
		}
	}

	//Check if the stack is empty
	bool isEmpty() const
	{
		return top == nullptr;
	}

	//Push a new node onto the stack
	void Push(int QuesID, string question, string answer, int score)
	{
		StackNode* newNode = new StackNode(QuesID, question, answer, score);
		newNode->next = top;
		top = newNode;
		size++;
	}

	//Pop the top node from the stack
	void Pop()
	{
		if (isEmpty())
		{
			std::cout << "Answered Question Stack is empty. Cannot pop. " << endl;
			return;
		}
		StackNode* temp = top;
		top = top->next;
		delete temp;
		size--;
	}

	//Get the top node from the stack
	StackNode* getTop() const
	{
		return top;
	}

	int getSize()
	{
		return size;
	}

	void clear() {
		while (!isEmpty()) {
			Pop();
		}
	}

	StackNode* search(int QuesID) const {
		StackNode* current = top;
		while (current != nullptr) {
			if (current->QuesID == QuesID) {
				return current;
			}
			current = current->next;
		}
		return nullptr; // Not found
	}

	bool contains(int QuesID) const {
		return search(QuesID) != nullptr;
	}

	//Display all the nodes in the answered ques stack
	void displayAnsweredQuesStack()
	{
		StackNode* current = top;
		while (current != nullptr) {
			std::cout << "QuesID: " << current->QuesID << endl << current->question << endl << "Score: " << current->score << endl;
			current = current->next;
		}
	}

};

/*
class StackLinkedList
{
	//1. list properties
	Node* top, * bottom;
	int size;
	string stackname = "";
public:
	//2. constructor (stack name, size, top = empty)
	StackLinkedList(string stackname, int size, bool top)
	{
		top = bottom = nullptr;
		size = 0;
		this->stackname = stackname;
	}
	//3. isEmpty() - check whether stack is still empty?
	bool isEmpty()
	{
		if (top == nullptr)
		{
			return true;
		}
		return false;
	}

	//4. Push() --> change to InsertToEnd()
	void InsertToEnd(string data)
	{
		Node* newnode = new Node;
		newnode->data = data;
		newnode->next = nullptr;

		if (isEmpty())
		{
			top = bottom = newnode;
		}
		else
		{
			newnode->next = top;
			top = newnode;
		}
		std::cout << "Added item: " << newnode->data << endl;
		size++;
	}
	//5. Pop()
	void Pop()
	{
		if (isEmpty())
		{
			std::cout << "Stack is underflow! " << endl;
			return;
		}

		Node* current = top;
		top = top->next;
		if (top == nullptr)
			bottom = nullptr;
		std::cout << "Deleted: Data of " << current->data << " from the deck";
		delete current;
		size--;
	}
	//6. Peek()
	string Peek()
	{
		return top->data;
	}
	//7. GetSize()
	int getSize()
	{
		return size;
	}
	//8. Destructor()
	~StackLinkedList()
	{
		std::cout << "Stack of Answered Questions " << stackname << " is delete from the stack of answered cards";
	}

	//
};*/

/*
void InsertToEnd() {

}*/