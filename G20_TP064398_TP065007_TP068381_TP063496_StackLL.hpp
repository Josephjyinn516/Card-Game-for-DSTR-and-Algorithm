#pragma once
#include <iostream>
#include <string>
using namespace std;

/*
how the student score is saved
dont need to include quesid
need to count score of student
need to generate rank for student
every student name will be unique
every student name will duplicate 3 times because each of them will answer 3 questions

//your teammate code
struct queuenode
{
    string name;
    int quesid;
    int score;
    queuenode* nextadd;
};
*/


struct CalculateStudentScore
{
    string nameOfStudent;
    double scoreOfStudent; //to store the total score of student
    CalculateStudentScore* nextAddress;
};

class StackLinkedList {
    CalculateStudentScore* top, * bottom;
    string stackName;
    int size;

public:
    //1. constructor
    StackLinkedList(string stackName) {
        top = bottom = nullptr;
        size = 0;
        this->stackName = stackName;
    };

    //2. destructor
    ~StackLinkedList() {
        cout << "Stack of " << this->stackName << " is deleted." << endl;
    }

    //3. check if stack is empty
    bool isEmpty() {
        return top == nullptr;
    }

    //4. create new node function
    CalculateStudentScore* createNewNode(string name, double score) {
        CalculateStudentScore* newNode = new CalculateStudentScore;
        newNode->nameOfStudent = name;
        newNode->scoreOfStudent = score;
        newNode->nextAddress = nullptr;
        return newNode;
    }

    //5. push function - add new value to top of stack
    void push(string name, double score) {
        //5.1 create new node
        CalculateStudentScore* newNode = createNewNode(name, score);

        //5.2 check if stack is empty
        if (isEmpty()) {
            top = bottom = newNode;
        }

        //5.3 if stack not empty
        else {
            //5.4 check if the student name is already in the stack
            CalculateStudentScore* temp = top;
            while (temp != nullptr) {
                if (temp->nameOfStudent == name) { //if the student name is already in the stack
                    temp->scoreOfStudent += score; //add the score to the student
                    return; //exit the function
                }
                temp = temp->nextAddress; //move to next node
            }

            newNode->nextAddress = top; //point the new node to the top
            top = newNode; //make the new node as the top
        }
        size++;
    }

    //6. pop function - remove value from top of stack
    string pop() {
        //6.1 if stack is empty
        if (isEmpty()) {
            cout << "Stack is underflow" << endl;
            return "";
        }

        //6.2 if stack not empty
        CalculateStudentScore* current = top;
        top = top->nextAddress;
        if (top == nullptr) {
            bottom = nullptr;
        }

        //6.3 delete the current node
        //combine name and score into a string with delimiter of tab
        string combinedData = current->nameOfStudent + "\t"
            + to_string(current->scoreOfStudent);
        delete current;
        size--;
        return combinedData;
    }

    //7. display function - display all the values in the stack
    void display() {
        CalculateStudentScore* current = top;
        cout << "List of students in stack " << stackName << " is shown as below:" << endl;

        //7.1 check if stack is empty
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return;
        }

        //7.2 if stack not empty
        else {
            int rankCounter = 1;
            while (current != nullptr) { //loop until the end of the stack
                cout << current->nameOfStudent << ", score: " << current->scoreOfStudent << " " << endl;
                current = current->nextAddress; //move to next node
                rankCounter++;
            }
            cout << endl;
            cout << "List ends here!" << endl << endl;
        }
    }

    //8. peek function - get the score of top of stack
    int peek() {
        if (isEmpty()) {
            return NULL;
        }
        return top->scoreOfStudent;
    }

    //9. get size of stack
    int getSize() {
        return size;
    }

    //10. insert a node into a sorted linked list
    void insertIntoSortedLinkedList(string name, double score) {
        // 10.1 create new node
        CalculateStudentScore* newNode = createNewNode(name, score);

        // 10.2 if stack is empty
        if (isEmpty()) {
            top = bottom = newNode;
        }

        // 10.3 if stack not empty
        else {
            CalculateStudentScore* current = top;
            CalculateStudentScore* prev = nullptr;

            while (current != nullptr && current->scoreOfStudent > score) { //find the correct position to insert the new node based on score
                prev = current;
                current = current->nextAddress;
            }

            // insert at the beginning
            if (prev == nullptr) {
                newNode->nextAddress = top;
                top = newNode;
            }

            // insert in the middle or end
            else {
                prev->nextAddress = newNode;
                newNode->nextAddress = current;
            }

            // update bottom if inserted at the end
            if (newNode->nextAddress == nullptr) {
                bottom = newNode;
            }
        }
        size++;
    }

    //11. display until rank 30
    void displayTop30() {
        CalculateStudentScore* current = top;

        //7.1 check if stack is empty
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return;
        }

        //7.2 if stack not empty
        else {
            cout << "Top 30 students are shown as below:" << endl;
            int rankCounter = 1;
            while (current != nullptr) { //loop until the end of the stack
                if (rankCounter > 30) {
                    break; // exit the loop if rankCounter exceeds 30
                }
                cout << "Rank " << rankCounter << ": " << current->nameOfStudent << ", score: " << current->scoreOfStudent << " " << endl;
                current = current->nextAddress; //move to next node
                rankCounter++;
            }
            cout << endl;
        }
    }
};