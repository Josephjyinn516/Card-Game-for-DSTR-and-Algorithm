#pragma once
#include <iostream>
#include <string>
using namespace std;
#include "GameFlowFunctions.hpp"


struct DoublyLinkedListNode
{

	//data
	int QuesID;
	string question;
	string answer;
	int score;

	//link
	DoublyLinkedListNode* next;
	DoublyLinkedListNode* prev;
};

class DoublyLinkedList
{
	DoublyLinkedListNode* head, * tail;
	string listname;
	int size;

public:

	DoublyLinkedList(string listname) {
		this->listname = listname;
		head = tail = nullptr;
		size = 0;
	}


	//create new node for a linked list.
	DoublyLinkedListNode* createNewNode(int QuesID, string question, string answer, int score)
	{
		//reserve the empty slot in memory
		DoublyLinkedListNode* newnode = new DoublyLinkedListNode;

		//insert all the values to the newnode
		newnode->QuesID = QuesID;
		newnode->question = question;
		newnode->answer = answer;
		newnode->score = score;

		//make sure every single new node start from null ptr in both next and prev pointer
		newnode->next = nullptr;
		newnode->prev = nullptr;

		//bring the address back to the insert function
		return newnode;

	}

	void insertEnd(int QuesID, string question, string answer, int score)
	{
		//call the create new node function to built a new node
		DoublyLinkedListNode* newnode = createNewNode(QuesID, question, answer, score);

		//insert to the end of the doubly linked list
		if (head == nullptr)
		{
			head = tail = newnode;
		}
		else
		{
			tail->next = newnode;
			newnode->prev = tail;
			tail = newnode;
		}

		//increse the size
		size++;
	}

	void displayLinkedList() {
		DoublyLinkedListNode* current = head;
		while (current != nullptr) {
			cout << current->QuesID << ". " << current->question << endl << " Score: " << current->score << endl;
			current = current->next;
		}
		cout << "End of discarded question deck..." << endl;
		cout << endl;
	}

	DoublyLinkedListNode* DisplayQuestionBasedOnID(int Option, DoublyLinkedList* Ques, int& QuesID)
	{
		QuesID = QuesIDValidation(QuesID);
		// scenario 1: list is empty, only possible for discarded
		if (head == nullptr)
		{
			cout << "Discarded Question Deck is empty!" << endl;
			cout << " Only able to choose from unanswered question deck... " << endl;
			cin >> QuesID;
			QuesID = QuesIDValidation(QuesID);
			return Ques->DisplayQuestionBasedOnID(Option, Ques, QuesID);
		}

		// scenario 2: if the id match the head value, display the ques
		else if (QuesID == head->QuesID)
		{
			DoublyLinkedListNode* current = head;
			cout << "QuesID: " << current->QuesID << endl << current->question << endl << "Score: " << current->score << endl;
			return current;
		}

		// scenario 3: the id match the tail value, display the ques
		else if (QuesID == tail->QuesID)
		{
			DoublyLinkedListNode* current = tail;
			cout << "QuesID: " << current->QuesID << endl << current->question << endl << "Score: " << current->score << endl;
			return current;
		}

		// scenario 4: the id match the middle value, display the ques
		// scenario 5: id not found, display ques id not in the list
		else
		{
			DoublyLinkedListNode* current = head->next; // start from second item
			while (current != nullptr)
			{
				if (QuesID == current->QuesID)  // scenario 4
				{
					cout << "QuesID: " << current->QuesID << endl << current->question << endl << "Score: " << current->score << endl;
					return current;
				}
				current = current->next;
			}
			// scenario 5: not found
			//5.1 discarded ques not found
			if (Option == 1) {
				cout << QuesID << " is not found in the discarded question deck! Please enter an available question id. " << endl;
				cout << "Enter the id number of discarded question that you wish to answer: ";
				cin >> QuesID;
				QuesID = QuesIDValidation(QuesID);
				return Ques->DisplayQuestionBasedOnID(Option, Ques, QuesID);
			}
			else {
				cout << QuesID << " is not found in the unanswered deck. " << endl;
				/*QuesID = RandomNumGenerator();*/
				return NULL;
			}
		}
	}


	void DeleteQuestionBasedOnID(int QuesID)
	{
		// scenario 1: list is empty (does not happen)
		if (head == nullptr)
		{
			cout << "Question List is empty!" << endl;
			return;
		}

		// scenario 2: if the id match the head value, delete the ques from unanswered deck
		else if (QuesID == head->QuesID)
		{
			DoublyLinkedListNode* current = head;
			head = head->next;
			if (head == nullptr)
				tail = nullptr;
			else
				head->prev = nullptr;

			delete current;
			size--;
			return;
		}

		// scenario 3: the id match the tail value, delete the ques from unanswered deck
		else if (QuesID == tail->QuesID)
		{
			DoublyLinkedListNode* current = tail;
			tail = tail->prev;
			if (tail == nullptr)
				head = nullptr;
			else
				tail->next = nullptr;

			delete current;
			size--;
			return;
		}

		// scenario 4: the id match the middle value, delete the ques from unanswered deck
		// scenario 5: id not found, display ques id not in the list
		else
		{
			DoublyLinkedListNode* current = head->next; // start from second item
			while (current != nullptr)
			{
				if (QuesID == current->QuesID)  // scenario 4
				{
					current->prev->next = current->next;
					current->next->prev = current->prev;
					delete current;
					size--;
					return;
				}
				current = current->next;
			}
			// scenario 5: not found (does not happen as well)
			cout << QuesID << " is not found in the list! " << endl;


		}
	}

	int getSize()
	{
		return size;
	}


	int getID(DoublyLinkedListNode* current)
	{
		return current->QuesID;
	}

	string getQues(DoublyLinkedListNode* current)
	{
		return current->question;
	}

	int getScore(DoublyLinkedListNode* current)
	{
		return current->score;
	}

	string getAnswer(DoublyLinkedListNode* current)
	{
		return current->answer;
	}
};