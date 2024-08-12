#pragma once
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct queuenode {
    string name;
    string questions[3]; // Array to store question sentences for 3 rounds
    int score[3];  // Array to store scores for 3 rounds
    int totalScore; // Total score for the student
    queuenode* nextadd;
};

class QueueLinkedList {
    queuenode* front, * rear;
    int queuesize;

public:
    QueueLinkedList() {
        front = rear = nullptr;
        queuesize = 0;
    }
    //queuenode* Front() const {
    //    return front;
    //}

    //queuenode* Rear() const {
    //    return rear;
    //}

    ~QueueLinkedList() {
        while (front != nullptr) { // loops continues as long as there is a node in the linked list
            queuenode* temp = front; //temp is assigned to point to the current 'front' node
            front = front->nextadd; //front pointer is moved to the next node in the list ('front->newnode')
            delete temp; //the current node that front' was pointing to is deleted to free the memory
        }
        rear = nullptr; //set rear to null
    }

    queuenode* CreateNewNode(const std::string& name) {
        queuenode* newnode = new (std::nothrow) queuenode;
        if (newnode != nullptr) {
            newnode->name = name;
            for (int i = 0; i < 3; ++i) {
                newnode->questions[i] = ""; // Initialize with an empty string
                newnode->score[i] = 0;
            }
            newnode->totalScore = 0;
            newnode->nextadd = nullptr;
        }
        return newnode;
    }

    void enqueue(string name, string question, int score, int round) {
        queuenode* current = front;
        while (current != nullptr && current->name != name) { // check if the name stored in the current node is not equal to the target name
            current = current->nextadd; //if both condition are true, the loop continues, and the pointer 'current' is updated to point to the next node in the list using 'current->nextadd'
        }

        if (current == nullptr) {
            current = CreateNewNode(name);
            if (front == nullptr)
                front = rear = current;
            else {
                rear->nextadd = current;
                rear = current;
            }
            queuesize++;
        }

        current->questions[round] = question;
        current->score[round] = score;
        current->totalScore += score;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    void dequeue() {
        if (isEmpty()) {
            std::cout << "Student Score is empty, unable to delete!" << endl;
            exit(1);
        }
        queuenode* current = front;
        front = front->nextadd;
        if (front == nullptr)
            rear = nullptr;
        std::cout << "Dequeue item: " << current->name << endl;
        delete current;
        queuesize--;
    }

    int getSize() {
        return queuesize;
    }

////KONG JUN HINN TP064398////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void sortQueue() {
        if (front == nullptr || front->nextadd == nullptr) {
            return;
        }

        bool swapped;
        queuenode* ptr1;
        queuenode* lptr = nullptr;

        do {
            swapped = false;
            ptr1 = front;

            while (ptr1->nextadd != lptr) {
                if (ptr1->totalScore < ptr1->nextadd->totalScore) {
                    swap(ptr1->name, ptr1->nextadd->name);
                    for (int i = 0; i < 3; ++i) {
                        swap(ptr1->questions[i], ptr1->nextadd->questions[i]);
                        swap(ptr1->score[i], ptr1->nextadd->score[i]);
                    }
                    swap(ptr1->totalScore, ptr1->nextadd->totalScore);
                    swapped = true;
                }
                ptr1 = ptr1->nextadd;
            }
            lptr = ptr1;
        } while (swapped);
    }

    string truncateString(const string& str, size_t width) {
        if (str.size() > width) {
            return str.substr(0, width - 3) + "...";
        }
        return str;
    }

    void displayQueue() {
        sortQueue();

        queuenode* current = front;
        int rank = 1;

        // Set the width for each column
        const int nameWidth = 15;
        const int roundWidth = 32;
        const int scoreWidth = 3;

        // Header of the table
        std::cout << left << setw(6) << "Rank"
            << left << setw(nameWidth) << "Name"
            << left << setw(roundWidth) << "Round 1"
            << left << setw(roundWidth) << "Round 2"
            << left << setw(roundWidth) << "Round 3"
            << left << setw(scoreWidth) << "Total"
            << endl;

        std::cout << "-------------------------------------------------------------------------------" << endl;

        while (current != nullptr) {
            std::cout << left << setw(6) << rank
                << left << setw(nameWidth) << current->name;
            for (int i = 0; i < 3; ++i) {
                string question = truncateString(current->questions[i], roundWidth - 10) + "[" + to_string(current->score[i]) + "]";
                std::cout << left << setw(roundWidth) << question;
            }
            std::cout << left << setw(scoreWidth) << current->totalScore << endl;
            current = current->nextadd;
            rank++;
        }
    }

    void printDivider(char ch, int length) {
        std::cout << std::string(length, ch) << std::endl;
    }

    void printCentered(std::string text, int width) {
        int padding = (width - text.length()) / 2;
        std::cout << std::string(padding, ' ') << text << std::string(padding, ' ') << std::endl;
    }

    void searchStudent(string name) {
        queuenode* current = front;
        while (current != nullptr) {
            if (current->name == name) {
                // Calculate the maximum width for question display
                int maxWidth = 0;
                for (int i = 0; i < 3; ++i) {
                    maxWidth = std::max(maxWidth, (int)current->questions[i].length());
                }

                // Set the width for formatting with some padding
                int width = maxWidth + 5;

                // Print student information
                cout << "========================================" << endl;
                cout << "           Student Found                " << endl;
                cout << "========================================" << endl;
                cout << " Name: " << current->name << endl;
                cout << "----------------------------------------" << endl;

                for (int i = 0; i < 3; ++i) {
                    cout << " Round " << (i + 1) << ":" << endl;
                    cout << "   Question: \"" << current->questions[i] << "\"" << endl;
                    cout << "   Score: " << current->score[i] << endl;
                    cout << "----------------------------------------" << endl;
                }

                cout << " Overall Score: " << current->totalScore << endl;
                cout << "========================================" << endl;
                return;
            }
            current = current->nextadd;
        }
        cout << "Student not found!" << endl;
    }

    void displayTopStrongest(int topN) {
        if (isEmpty()) {
            cout << "No students in the queue!" << endl;
            return;
        }
        if (topN < 1 || topN > 20) {
            cout << "Invalid number! Please enter a number between 1 and 20." << endl;
            return;
        }

        // Array to hold top N strongest students
        queuenode* topStrongest[20] = { nullptr };

        queuenode* current = front;
        while (current != nullptr) {
            for (int i = 0; i < topN; ++i) {
                if (topStrongest[i] == nullptr || current->totalScore > topStrongest[i]->totalScore) {
                    for (int j = topN - 1; j > i; --j) {
                        topStrongest[j] = topStrongest[j - 1];
                    }
                    topStrongest[i] = current;
                    break;
                }
            }
            current = current->nextadd;
        }

        // Display the table header
        const int nameWidth = 15;
        const int scoreWidth = 10;
        cout << left << setw(6) << "Rank"
            << left << setw(nameWidth) << "Name"
            << left << setw(scoreWidth) << "Total Score" << endl;
        cout << "------------------------------------" << endl;

        // Display top N strongest students
        for (int i = 0; i < topN && topStrongest[i] != nullptr; ++i) {
            cout << left << setw(6) << (i + 1)
                << left << setw(nameWidth) << topStrongest[i]->name
                << left << setw(scoreWidth) << topStrongest[i]->totalScore << endl;
        }
    }

    void displayTopWeakest(int topN) {
        if (isEmpty()) {
            cout << "No students in the queue!" << endl;
            return;
        }
        if (topN < 1 || topN > 30) {
            cout << "Invalid number! Please enter a number between 1 and 30." << endl;
            return;
        }

        // Array to hold top N weakest students
        queuenode* topWeakest[30] = { nullptr };

        queuenode* current = front;
        while (current != nullptr) {
            for (int i = 0; i < topN; ++i) {
                if (topWeakest[i] == nullptr || current->totalScore < topWeakest[i]->totalScore) {
                    for (int j = topN - 1; j > i; --j) {
                        topWeakest[j] = topWeakest[j - 1];
                    }
                    topWeakest[i] = current;
                    break;
                }
            }
            current = current->nextadd;
        }

        // Display the table header
        const int nameWidth = 15;
        const int scoreWidth = 10;
        cout << left << setw(6) << "Rank"
            << left << setw(nameWidth) << "Name"
            << left << setw(scoreWidth) << "Total Score" << endl;
        cout << "------------------------------------" << endl;

        // Display top N strongest students
        for (int i = 0; i < topN && topWeakest[i] != nullptr; ++i) {
            cout << left << setw(6) << (i + 1)
                << left << setw(nameWidth) << topWeakest[i]->name
                << left << setw(scoreWidth) << topWeakest[i]->totalScore << endl;
        }
    }

    void displayLeaderboardOptions(QueueLinkedList& studentScores) {
        int option;
        do {
            cout << "Leaderboard Options:" << endl;
            cout << "1. Search by Name" << endl;
            cout << "2. Strongest Namelist" << endl;
            cout << "3. Weakest Namelist" << endl;
            cout << "Enter your choice (press '0' proceed to next section): ";
            cin >> option;

            switch (option) {
            case 1: {
                string name;
                int searchOption;
                do {
                    cout << "Search Student Name" << endl;
                    cout << "Please input valid student name (press '0' to go back to main): ";
                    cin.ignore();
                    getline(cin, name);
                    if (name == "0") break;
                    studentScores.searchStudent(name);
                    cout << "Press '1' to continue searching or '0' to go back to main: ";
                    cin >> searchOption;
                } while (searchOption != 0);
                break;
            }
            case 2: {
                int topN;
                int strongestOption;
                do {
                    cout << "Strongest Namelist" << endl;
                    cout << "WARNING: Min is 1 and Max is 20" << endl;
                    cout << "Top _____ from Namelist (press '0' to go back to main): ";
                    cin >> topN;
                    if (topN == 0) break;
                    studentScores.displayTopStrongest(topN);
                    cout << "Press '1' to continue input strongest student or '0' to go back to main: ";
                    cin >> strongestOption;
                } while (strongestOption != 0);
                break;
            }
            case 3: {
                int topN;
                int weakestOption;
                do {
                    cout << "Weakest Namelist" << endl;
                    cout << "WARNING: Min is 1 and Max is 30" << endl;
                    cout << "Top _____ from Namelist (press '0' to go back to main): ";
                    cin >> topN;
                    if (topN == 0) break;
                    studentScores.displayTopWeakest(topN);
                    cout << "Press '1' to continue input weakest student or '0' to go back to main: ";
                    cin >> weakestOption;
                } while (weakestOption != 0);
                break;
            }

            case 0:
                cout << "Move to next process . . ." << endl;
                break;
            default:
                cout << "Invalid option! Please try again." << endl;
                break;
            }
        } while (option != 0);
    }
};



/*#pragma once
#include <iostream>
using namespace std;
//queue data struc, first in first out, student queue for their turn
//SCORE have to be EACH ROUND with the QUES ID that are chose to answer for diplaying leaderboard


struct queuenode
{
    string name;
    //string data;
    int quesid;
    int score;
    queuenode* nextadd;
};

class QueueLinkedList
{
    queuenode* front, * rear;
    int queuesize;

public:
    {
        front = rear = nullptr;
        queuesize = 0;
    }
    queuenode* CreateNewNode(string name)
    {
        queuenode* newnode = new queuenode;
        newnode->name = name;
        newnode->nextadd = nullptr;
        return newnode;
    }
    void enqueue(string name, int quesid, int score)
        queuenode* newnode = CreateNewNode(name);
        //insert to end of the list
        if (front == nullptr)
            front = rear = newnode;
        else
        {
            rear->nextadd = newnode;
            rear = newnode;
        }
        queuesize++;
    }
    bool isEmpty()
    {
        if (front == nullptr)
            return true;
        return false;
    }
    void dequeue() //delete from the front
    {
        if (isEmpty())
        {
            std::cout << "Student Score is empty, unable to delete!" << endl;
            exit(1);
        }
        queuenode* current = front;
        front = front->nextadd;
        if (front == nullptr)
            rear = nullptr;
        std::cout << "Dequeue item: " << current->quesid << endl;
        delete current;
        queuesize--;
    }
    int getSize()
    {
        return queuesize;
    }
    void displayQueue()
    {
        queuenode* current = front;

        while (current != nullptr)
        {
            std::cout << current->name << ", ";
            current = current->nextadd;
        }
        std::cout << endl << "Queue ended here!" << endl;
    }
};*/


//struct QueueNode {
//
//    string name;
//
//    int score1;
//    int
//	
//
//    QueueNode* next;
//};
//
//template <typename string>
//class Queue {
//    QueueNode* queueHead; //queue’s first node (head)
//    QueueNode* queueTail; //queue’s last node (tail)
//    int size;
//
//public:
//    Queue() 
//    {
//        queueHead = queueTail = nullptr;
//        size = 0;
//
//    }
//    ~Queue() 
//    {
//        while (!isEmpty()) {
//            deleteQueue();
//        }
//    } 
//    void addQueue(string name, int score) 
//    {
//        
//    } 
//    char deleteQueue(); //deletes the first node and returns its info
//    bool isEmpty();//true if queue is empty, false otherwise
//    //int size() {} //returns the number of elements stored in the queue
//};
