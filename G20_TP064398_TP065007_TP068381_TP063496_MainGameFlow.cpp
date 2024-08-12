

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
//#include <vector>
using namespace std;
#include "AnsweredQues.hpp"
#include "DiscardedQues.hpp"
#include "StudentScore.hpp"
#include "GameFlowFunctions.hpp"
#include "Leaderboard.hpp"
#include "BinaryTree.hpp"
#include "StackLL.hpp"
#include "RandomNumGenerate.hpp"


// Function to read questions from a file and insert them into a doubly linked list
void readQuesintoLinkedList(const string& file, DoublyLinkedList* Ques) {
    int QuesID = 1;
    string ques;
    string answer;
    string scoreStr;

    ifstream inputFile(file);

    if (inputFile.is_open()) {
        string line;

        while (getline(inputFile, line)) {
            stringstream ss(line);

            // Extract data from each tab-separated value
            getline(ss, ques, '\t');
            getline(ss, answer, '\t');
            getline(ss, scoreStr, '\t');

            // Insert each line into the linked list
            Ques->insertEnd(QuesID, ques, answer, stoi(scoreStr));

            QuesID++;
        }
        inputFile.close();
    }
    else {
        cout << "Error opening file!" << endl;
    }
}

// Function to create a dynamic variable
int* createDynamicVariable(int num) {
    int* a = new int(num);
    return a;
}

void displayFileContent(const string& filename) {
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error opening the file!" << filename << endl;
        return;
    }

    string line;

    cout << "File content: " << endl;
    while (getline(inputFile, line)) {
        cout << line << endl;
    }

    inputFile.close();
}

// Function to read the file content and store it in a vector
vector<string> readStudentNames(const string& filename) {
    ifstream inputFile(filename);
    vector<string> studentNames;
    if (!inputFile.is_open()) {
        cerr << "Error opening the file: " << filename << endl;
        return studentNames;
    }

    string line;
    while (getline(inputFile, line)) {
        studentNames.push_back(line);
    }

    inputFile.close();
    return studentNames;
}

int countRecordsInFile(const string& filename) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Error opening the file: " << filename << endl;
        return 0;
    }

    string line;
    int count = 0;
    while (getline(inputFile, line)) {
        cout << "Student number: " << line << endl;
        ++count;
    }

    inputFile.close();
    return count;
}

void searchStudentByName(Leaderboard& leaderboard) {
    std::string name;
    while (true) {
        std::cout << "Search Student Name\nPlease input valid student name (press '0' back to main): ";
        std::cin >> name;
        if (name == "0") return;
        LeaderboardNode* student = leaderboard.searchStudent(name);
        if (student) {
            std::cout << "Student Found: " << student->name << " - " << student->score << std::endl;
            std::cout << "Press '1' to continue search or '0' to go back to main: ";
            int choice;
            std::cin >> choice;
            if (choice == 0) return;
        } else {
            std::cout << "Error: Student not found. Please try again." << std::endl;
        }
    }
}

void displayTopStrongestStudents(Leaderboard& leaderboard) {
    int topN;
    while (true) {
        std::cout << "Strongest Namelist\nWARNING: Min is 1 and Max is 20\nTop _____ from Namelist (press '0' back to main): ";
        std::cin >> topN;
        if (topN == 0) return;
        if (topN < 1 || topN > 20) {
            std::cout << "Error: Invalid number. Please enter a number between 1 and 20." << std::endl;
        } else {
            leaderboard.displayTopStrongest(topN);
            std::cout << "Press '1' to continue input strongest or '0' to go back to main: ";
            int choice;
            std::cin >> choice;
            if (choice == 0) return;
        }
    }
}

void displayTopWeakestStudents(Leaderboard& leaderboard) {
    int topN;
    while (true) {
        std::cout << "Weakest Namelist\nWARNING: Min is 1 and Max is 30\nTop _____ from Namelist (press '0' back to main): ";
        std::cin >> topN;
        if (topN == 0) return;
        if (topN < 1 || topN > 30) {
            std::cout << "Error: Invalid number. Please enter a number between 1 and 30." << std::endl;
        } else {
            leaderboard.displayTopWeakest(topN);
            std::cout << "Press '1' to continue input weakest or '0' to go back to main: ";
            int choice;
            std::cin >> choice;
            if (choice == 0) return;
        }
    }
}

int main() {
    RandomNumberGenerator rng;

    // Create all data structures
    DoublyLinkedList* UnansweredQues = new DoublyLinkedList("Unanswered Questions");
    DoublyLinkedList* DiscardedQues = new DoublyLinkedList("Discarded Questions");
    AnsweredQuestionsStack ansQues("Answered Questions Stack");
    QueueLinkedList StudentScores;
    Leaderboard leaderboard;


    // Insert unanswered questions into the data structure
    readQuesintoLinkedList("C:\\Data Structures\\asm_leaderboard\\asm_leaderboard\\DSTRquestions.txt", UnansweredQues);

    // Read student names into a vector
    vector<string> studentNames = readStudentNames("C:\\Data Structures\\asm_leaderboard\\asm_leaderboard\\student.txt");
    int studentNum = studentNames.size();

    int Option;
    int* Optionptr = nullptr;

    int QuesID;
    int* QuesIDptr = nullptr;

    string ques;
    int score;
    int randomNum;

    string CorrectAnswer;
    DoublyLinkedListNode* current;
    string StudentAnswer;

    // Start game
    cout << " _______  _______  __   __  _______ " << endl;
    cout << "|       ||   _   ||  |_|  ||       |" << endl;
    cout << "|    ___||  |_|  ||       ||    ___|" << endl;
    cout << "|   | __ |       ||       ||   |___ " << endl;
    cout << "|   ||  ||       ||       ||    ___|  " << endl;
    cout << "|   |_| ||   _   || ||_|| ||   |___ " << endl;
    cout << "|_______||__| |__||_|   |_||_______|\n\n" << endl;

    cout << " _______  _______  _______  ______    _______ " << endl;
    cout << "|       ||       ||   _   ||    _ |  |       |" << endl;
    cout << "|  _____||_     _||  |_|  ||   | ||  |_     _|" << endl;
    cout << "| |_____   |   |  |       ||   |_||_   |   |" << endl;
    cout << "|_____  |  |   |  |       ||    __  |  |   |" << endl;
    cout << " _____| |  |   |  |   _   ||   |  | |  |   |" << endl;
    cout << "|_______|  |___|  |__| |__||___|  |_|  |___|\n\n" << endl;

  
    //create stack (need name and score only)
    StackLinkedList stack1("student names and score");

    for (int round = 0; round < 3; ++round) {
        for (int i = 0; i < studentNum; ++i) {
            // Display round and student's turn
            cout << "Round " << (round + 1) << ", " << studentNames[i] << "'s turn:" << std::endl;

            // Display remaining questions
            cout << "Unanswered Questions Deck (left " << UnansweredQues->getSize() << " questions)" << std::endl << std::endl;

            // Display answered and discarded questions
            cout << "Answered Questions Deck: " << std::endl;
            ansQues.displayAnsweredQuesStack();
            cout << std::endl << "Discarded Questions Deck: " << std::endl;
            DiscardedQues->displayLinkedList();
            cout << std::endl;

            // Get user's option
            int Option;
            cout << "Name: " << studentNames[i] << std::endl;
            cout << "Your Option? (Enter 1 for discarded questions, 2 for unanswered questions): ";

            cin >> Option;
            //Option = 2;
            
            Option = OptionValidation(Option);

            // Handle the selected option
            int QuesID, score;
            std::string ques, CorrectAnswer, StudentAnswer;
            DoublyLinkedListNode* current;
         
            if (Option == 1) {
                if (DiscardedQues->getSize() == 0) {
                    cout << "Discarded question deck is empty..." << std::endl;
                    cout << "Automatically draw question from unanswered questions deck..." << std::endl;
                    Option = 2;
                }
            }

            if (Option == 1) {
                cout << "Enter the ID number of the discarded question that you wish to answer: ";
                cin >> QuesID;
                //QuesID = QuesIDValidation(QuesID);
                current = DiscardedQues->DisplayQuestionBasedOnID(Option, DiscardedQues, QuesID);
                
                ques = DiscardedQues->getQues(current);
                CorrectAnswer = DiscardedQues->getAnswer(current);
                score = DiscardedQues->getScore(current);
            }
            else {
                int randomNum = rng.generate();
                QuesID = randomNum;
                /*QuesID = QuesIDValidation(QuesID);*/
                current = UnansweredQues->DisplayQuestionBasedOnID(Option, DiscardedQues, QuesID);
                ques = UnansweredQues->getQues(current);
                CorrectAnswer = UnansweredQues->getAnswer(current);
                score = UnansweredQues->getScore(current);
            }

            // Get student's answer
            cout << "Your Answer: ";
            cin >> StudentAnswer;
            //StudentAnswer = "A";
 

            // Check if the answer is correct
            if (StudentAnswer == CorrectAnswer) {
                cout << " _______  ___   __    _  _______  _______    __"<< std::endl;
                cout << "|  _    ||   | |  |  | ||       ||       |  |  |" << std::endl;
                cout << "| |_|   ||   | |   |_| ||    ___||   _   |  |  |" << std::endl;
                cout << "|       ||   | |       ||   | __ |  | |  |  |  |" << std::endl;
                cout << "|  _   | |   | |  _    ||   ||  ||  |_|  |  |__|" << std::endl;
                cout << "| |_|   ||   | | | |   ||   |_| ||       |   __ " << std::endl;
                cout << "|_______||___| |_|  |__||_______||_______|  |__|\n\n" << std::endl;


                if (Option == 1) {
                    DiscardedQues->DeleteQuestionBasedOnID(QuesID);
                }
                else {
                    UnansweredQues->DeleteQuestionBasedOnID(QuesID);
                }
                StudentScores.enqueue(studentNames[i], ques, score, round);
                ansQues.Push(QuesID, ques, CorrectAnswer, score);
                stack1.push(studentNames[i], score);
            }
            else {
                cout << " _     _  ______    _______  __    _  _______    __" << std::endl;
                cout << "| | _ | ||    _ |  |       ||  |  | ||       |  |  |" << std::endl;
                cout << "| || || ||   | ||  |   _   ||   |_| ||    ___|  |  |" << std::endl;
                cout << "|       ||   |_||_ |  | |  ||       ||   | __   |  |" << std::endl;
                cout << "|       ||    __  ||  |_|  ||  _    ||   ||  |  |__|" << std::endl;
                cout << "|   _   ||   |  | ||       || | |   ||   |_| |   __ " << std::endl;
                cout << "|__| |__||___|  |_||_______||_|  |__||_______|  |__|\n\n" << std::endl;
                //Record the score as 0 for student
                StudentScores.enqueue(studentNames[i], ques, 0, round);
                if (Option != 1) {
                    DiscardedQues->insertEnd(QuesID, ques, CorrectAnswer, score);
                    UnansweredQues->DeleteQuestionBasedOnID(QuesID);
                    stack1.push(studentNames[i], score);
                }
            }

            cout << "Round " << (round + 1) << " ended for " << studentNames[i] << "." << std::endl;
        }
    }



    cout << "Game Ended...\n\n\n" << endl;
    cout << " ___      _______  _______  ______   _______  ______" << endl;
    cout << "|   |    |       ||   _   ||      | |       ||    _ |" << endl;
    cout << "|   |    |    ___||  |_|  ||  _    ||    ___||   | ||" << endl;
    cout << "|   |    |   |___ |       || | |   ||   |___ |   |_||_" << endl;
    cout << "|   |___ |    ___||       || |_|   ||    ___||    __  |" << endl;
    cout << "|       ||   |___ |   _   ||       ||   |___ |   |  | |" << endl;
    cout << "|_______||_______||__| |__||______| |_______||___|  |_|\n\n" << endl;

    cout << " _______  _______  _______  ______    ______ " << endl;
    cout << "|  _    ||       ||   _   ||    _ |  |      |" << endl;
    cout << "| |_|   ||   _   ||  |_|  ||   | ||  |  _    | " << endl;
    cout << "|       ||  | |  ||       ||   |_||_ | | |   |" << endl;
    cout << "|  _   | |  |_|  ||       ||    __  || |_|   |" << endl;
    cout << "| |_|   ||       ||   _   ||   |  | ||       |" << endl;
    cout << "|_______||_______||__| |__||___|  |_||______| \n\n" << endl;


    StudentScores.displayQueue();

    cout << "\n\n\nSearch and Sort\n\n\n" << endl;
    leaderboard.sortLeaderboard();

    // Display leaderboard options and handle user interaction
    StudentScores.displayLeaderboardOptions(StudentScores);

    cout << "     ______    ___   __    _   _______   ______     __   __" << endl;
    cout << "    | _    |  |   | |  |  | | |   _   | |    _ |   |  | |  |" << endl;
    cout << "    | |_|   | |   | |   |_| | |  |_|  | |   | ||   |  |_|  |" << endl;
    cout << "    |       | |   | |       | |       | |   |_||_  |       |" << endl;
    cout << "    |  _   |  |   | |  _    | |       | |    __  | |_     _|" << endl;
    cout << "    | |_|   | |   | | | |   | |   _   | |   |  | |   |   |" << endl;
    cout << "    |_______| |___| |_|  |__| |__| |__| |___|  |_|   |___|\n\n" << endl;
    cout << "     _______   ______     _______   _______" << endl;
    cout << "    |       | |    _ |   |       | |       |" << endl;
    cout << "    |_     _| |   | ||   |    ___| |    ___|" << endl;
    cout << "      |   |   |   |_||_  |   |___  |   |___" << endl;
    cout << "      |   |   |    __  | |    ___| |    ___|" << endl;
    cout << "      |   |   |   |  | | |   |___  |   |___" << endl;
    cout << "      |___|   |___|  |_| |_______| |_______|\n\n\n" << endl;



    //create another stack for adding scores in sorted order
    StackLinkedList stack2("Stack2");

    // create a stack2 with sorted linked list
    while (!stack1.isEmpty()) {
        string current = stack1.pop();

        //split string into name and score with delimiter of tab
        string name = current.substr(0, current.find("\t")); //get name
        int score = stoi(current.substr(current.find("\t") + 1, current.length())); //get score

        stack2.insertIntoSortedLinkedList(name, score); //insert into sorted linked list
    }

    //DISPLAY FROM HIGHEST RANK TO LOWEST RANK
    stack2.displayTop30();

    //--------------------------------------------------------
    //create a binary tree
    //BinarySearchTreeClass newtree("BinarySearchTree");
    BinaryTreeChart newtree("BinaryTree");
    //for every node in stack2, insert into binary tree (only insert 30 times)
    int i = 1;
    int end = 31; //end is 31 because we want to insert 30 nodes
    while (!stack2.isEmpty() && i < end) {
        string current = stack2.pop(); //pop from stack2

        //split string into name and score with delimiter of tab
        string name = current.substr(0, current.find("\t")); //get name
        int score = stoi(current.substr(current.find("\t") + 1, current.length())); //get score

        newtree.insert(name, score, i); //insert into binary tree
        i++;
    }

    //DISPLAY BINARY TREE
    //inorder
    cout << "Inorder Traversal: " << endl;
    newtree.inorder();
    cout << endl << endl;

    //preorder
    cout << "Preorder Traversal: " << endl;
    newtree.preorder();
    cout << endl << endl;

    //postorder
    cout << "Postorder Traversal: " << endl;
    newtree.postorder();
    cout << endl << endl;

    //SEARCH FUNCTION: search for a name in binary tree
    string searchName;
    bool flagToContinue = true;

    cout << endl << string(110, '=') << endl;

    while (flagToContinue) {
        //prompt user to enter a name to search
        cout << "Enter a name to search (or type '1' to exit): ";
        getline(cin, searchName);

        //validate input: check if input is valid and if it is not empty string && if user typed 1 to exit
        while (cin.fail() || searchName.empty() || searchName == "1") {
            //if user typed 1 to exit
            if (searchName == "1") {
                flagToContinue = false; //exit loop
         
                break; //break while loop
                
            }


            //otherwise if validation failed
            cin.clear(); //clear input buffer to restore cin to a usable state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer
            cout << endl << "Invalid input. please enter a name: "; //prompt user to enter a valid input
            getline(cin, searchName); //get input
        };

   

        //if user not typed 1 to exit
        if (searchName != "1") {
            //print search result
            cout << endl << "----Search Result----" << endl;

            //check if name exists in binary tree
            if (newtree.doesNameExist(searchName)) {
                cout << "Name found in the tree." << endl;

                //search for a name in binary tree if it exists
                cout << newtree.searchName(searchName) << endl;
            }
            else {
                cout << "Name not found in the tree." << endl;
            }

            cout << endl;
        }
        else {
            cout << endl << "You are exiting search function." << endl;
        }

        cout << string(110, '=') << endl; //print line

        //clear input buffer
        cin.clear();

        searchName = ""; //reset searchName
    }


    delete UnansweredQues;
    delete DiscardedQues;
    delete Optionptr;
    delete QuesIDptr;

    return 0;
}

