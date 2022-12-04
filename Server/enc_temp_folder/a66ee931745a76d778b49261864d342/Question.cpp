#include "Question.h"

Question::Question()
{
	difficulty = std::string();
	text = std::string();
	correctAnswer = std::string();
	//incorrectAnswers = std::vector<std::string>();
	isMultipleChoice = true;
	score = 0;
}

void Question::SetId(int id)
{
	this->id = id;
}

void Question::SetDifficulty(const std::string& difficulty)
{
	this->difficulty = difficulty;
}

void Question::SetText(const std::string& text)
{
	this->text = text;
}

void Question::SetCorrectAnswer(const std::string& correctAnswer)
{
	this->correctAnswer = correctAnswer;
}

//void Question::SetIncorrectAnswers(const std::vector<std::string>& incorrectAnswers)
//{
//	this->incorrectAnswers = incorrectAnswers;
//}

void Question::SetIsMultipleChoice(bool isMultipleChoice)
{
	this->isMultipleChoice = isMultipleChoice;
}

void Question::SetScore(int score)
{
	this->score = score;
}

int Question::GetId() const
{
	return id;
}

std::string Question::GetDifficulty() const
{
	return difficulty;
}

std::string Question::GetText() const
{
	return text;
}

std::string Question::GetCorrectAnswer() const
{
	return correctAnswer;
}

//std::vector<std::string> Question::GetIncorrectAnswers() const
//{
//	return incorrectAnswers;
//}

bool Question::GetIsMultipleChoice() const
{
	return isMultipleChoice;
}

int Question::GetScore() const
{
	return score;
}

QuestionDatabaseControl::QuestionDatabaseControl(QuestionsStorage& storage) : database{ storage }
{
}

crow::response QuestionDatabaseControl::operator()(const crow::request& request) const
{
	auto bodyArgs = ParseUrlArgs(request.body);
	auto end = bodyArgs.end();
	auto questionId = bodyArgs.find("Id");
	auto questionDifficulty = bodyArgs.find("Difficulty");
	auto questionText = bodyArgs.find("Text");
	auto questionCorrectAnswer = bodyArgs.find("Correct answer");
	//auto questionIncorrectAnswers = bodyArgs.find("Incorrect answers");
	auto questionIsMultipleChoice = bodyArgs.find("Is multiple choice");
	auto questionScore = bodyArgs.find("Score");

	if (questionId != end && questionDifficulty != end && questionText != end && questionCorrectAnswer != end &&
		questionIsMultipleChoice != end && questionScore != end)
	{
		Question question;

		question.SetId(std::stoi(questionId->second));
		question.SetDifficulty(questionDifficulty->second);
		question.SetText(questionText->second);
		question.SetCorrectAnswer(questionCorrectAnswer->second);
		//question.SetIncorrectAnswers(CreateVector(questionIncorrectAnswers->second));
		question.SetIsMultipleChoice(CreateBool(questionIsMultipleChoice->second));
		question.SetScore(std::stoi(questionScore->second));

		database.insert(question);
	}

	return crow::response(201);
}
