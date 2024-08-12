#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;
#include "DiscardedQues.hpp"

int OptionValidation(int Option) {
	if (Option == 1 || Option == 2) {

		return Option;

	}
	else {

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		std::cout << "Invalid option input, please enter either 1 or 2 for the option." << endl;
		std::cout << "Your Option? (Enter 1 for discarded questions, 2 for Unanswered questions):";
		cin >> Option;
		Option = OptionValidation(Option);
	}
}

int QuesIDValidation(int QuesID) {
	if (cin.fail() || QuesID > 300 || QuesID < 1) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		std::cout << "Invalid ques input, please enter an integer." << endl;
		std::cout << "Enter the id number of discarded question that you wish to answer: ";
		cin >> QuesID;
		QuesID = QuesIDValidation(QuesID);

	}
	else {
		return QuesID;
	}
}

int AnswerChecking(string StudentAnswer, string CorrectAnswer) {

	return StudentAnswer.compare(CorrectAnswer);
}



