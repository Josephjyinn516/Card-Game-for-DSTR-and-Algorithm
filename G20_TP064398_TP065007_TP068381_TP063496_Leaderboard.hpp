#include <iostream>
#include <string>

class LeaderboardNode {
public:
    std::string name;
    int score;
    LeaderboardNode* next;
    LeaderboardNode* prev;

    LeaderboardNode(std::string n, int s) : name(n), score(s), next(nullptr), prev(nullptr) {}
};

class Leaderboard {
private:
    LeaderboardNode* head;
    LeaderboardNode* tail;

public:
    Leaderboard() : head(nullptr), tail(nullptr) {}

    // Function to insert a new student into the leaderboard
    void insertStudent(const std::string& name, int score) {
        LeaderboardNode* newNode = new LeaderboardNode(name, score);
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Function to sort the leaderboard
    void sortLeaderboard() {
        if (!head) return;
        for (LeaderboardNode* i = head; i != nullptr; i = i->next) {
            for (LeaderboardNode* j = i->next; j != nullptr; j = j->next) {
                if (i->score < j->score) {
                    std::swap(i->name, j->name);
                    std::swap(i->score, j->score);
                }
            }
        }
    }

    // Function to search for a student by name
    LeaderboardNode* searchStudent(const std::string& name) {
        LeaderboardNode* current = head;
        while (current) {
            if (current->name == name) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    // Function to display the strongest students
    void displayTopStrongest(int topN) {
        LeaderboardNode* current = head;
        for (int i = 0; i < topN && current; ++i) {
            std::cout << i + 1 << ". " << current->name << " - " << current->score << std::endl;
            current = current->next;
        }
    }

    // Function to display the weakest students
    void displayTopWeakest(int topN) {
        LeaderboardNode* current = tail;
        for (int i = 0; i < topN && current; ++i) {
            std::cout << i + 1 << ". " << current->name << " - " << current->score << std::endl;
            current = current->prev;
        }
    }

    // Function to display the leaderboard
    void displayLeaderboard() {
        LeaderboardNode* current = head;
        while (current) {
            std::cout << current->name << " - " << current->score << std::endl;
            current = current->next;
        }
    }

};
