
#include <iostream>
#include "CodingChallange.h"
#include "Question.h"

using namespace std;

enum class QuestionModes { ASK, INSERT };
void handleQuestion(vector<Question>& questions, const QuestionModes& questionmode);

int main()
{
	int decision = 0;
	vector<Question> questions;

	while (true) {
		try
		{
			cout << "\nType 1 for asking and 2 for a new Question:\n";
			cin >> decision;
			bool wrongInput = cin.fail();
			cin.clear();
			cin.ignore(10000, '\n');
			if (wrongInput) {
				wrongInput = false;
				throw 1;
			}
			else if (decision != 1 && decision != 2) {
				throw 2;
			}
			else if (decision == 1) {
				handleQuestion(questions, QuestionModes::ASK);
			}
			else if (decision == 2) {
				handleQuestion(questions, QuestionModes::INSERT);
			}
		}
		catch (int err)
		{
			if (err == 1) {
				cout << "\nPlease enter only digits";
			}
			else if (err == 2) {
				cout << "\nPlease enter only 1 or 2";
			}
		}
	}
	return 0;
}



void handleQuestion(vector<Question>& questions, const QuestionModes& questionmode)
{
	string input = "";
	string question = "";
	vector<string> answers;
	bool questionLoop = true;
	string questionOrAnswer = questionmode == QuestionModes::ASK ? "question" : "answer";
	string askOrInsert = questionmode == QuestionModes::ASK ? "ask" : "insert";

	while (questionLoop)
	{
		try {
			cout << "\nEnter the question you want to " << askOrInsert << ":\n";
			getline(cin, input);
			if (input.empty()) {
				throw 1;
			}
			else {
				question = input.substr(0, input.find('?')+1);
				input.erase(0, input.find('?') + 2);
			}
			if (question.size() >= 255) {
			throw 2;
			}
			else if (questionmode == QuestionModes::INSERT) {	
				while (input.size() > 0)
				{
					answers.push_back(input.substr(input.find("\"") + 1, input.find("\"", 1) - 1));
					input.erase(0, input.find("\"", 1) + 2);
				}
				if (answers.size() == 0) {
					throw 3;
				}
				for (int i = 0; i < answers.size(); i++)
				{
					if (answers.at(i).size() >= 255) {
						throw 2;
					}
				}
				Question questionInstance;
				questionInstance.text = question;
				questionInstance.answers = answers;
				questions.push_back(questionInstance);
				questionLoop = false;
			}
			
			else if(questionmode == QuestionModes::ASK) {
				if (questions.size() != 0) {
					for (int i = 0; i < questions.size(); i++)
					{
						if (question == questions.at(i).text) {
							for (int j = 0; j < questions.at(i).answers.size(); j++)
							{
								cout << questions.at(i).answers.at(j) << endl;
							}
							break;
						}
						else if(questions.size()-1 == i) {
							cout << "The answer to life, universe and everything is 42";
						}
					}
				}
				else {
					cout << "The answer to life, universe and everything is 42";
				}
				questionLoop = false;
			}
		}
		catch (int err) {
			if (err == 1) {
				cout << "\nPlease enter no empty question";
			}
			else if (err == 2) {
				cout << "\nThe " << questionOrAnswer << " can't be longer than 255 letters";
			}
			else if (err == 3) {
				cout << "\nAt least one answer is necessary";
			}
		}
	}
}

