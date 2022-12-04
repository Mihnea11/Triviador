#include <vector>
#include <string>

#include "User.h"
#include "Question.h"

namespace sql = sqlite_orm;

int main()
{
    const std::string usersDbFile = "Users.sqlite";
    const std::string questionsDbFile = "Questions.sqlite";
    UsersStorage usersDb = CreateStorage(usersDbFile);
    QuestionsStorage questionsDb = CreateQuestionsStorage(questionsDbFile);

    usersDb.sync_schema();
    questionsDb.sync_schema();

    crow::SimpleApp app;

    CROW_ROUTE(app, "/Users")(
    [&usersDb]()
    {
        std::vector<crow::json::wvalue> usersJson;
        for (const auto& user : usersDb.iterate<User>())
        {
            usersJson.push_back(crow::json::wvalue
            {
                {"Id", user.GetName()},
                {"Email", user.GetEmail()},
                {"Password", user.GetPassword()}
            });
        }

        return crow::json::wvalue{ usersJson };
    });

    CROW_ROUTE(app, "/Questions")(
    [&questionsDb]()
    {
        std::vector<crow::json::wvalue> questionsJson;
        for (const auto& question : questionsDb.iterate<Question>())
        {
            questionsJson.push_back(crow::json::wvalue
            {
                {"Id", question.GetId()},
                {"Difficulty", question.GetDifficulty()},
                {"Text", question.GetText()},
                {"Correct answer", question.GetCorrectAnswer()},
                //{"Incorrect answers", question.GetIncorrectAnswers()},
                {"Is multiple choice", question.GetIsMultipleChoice()},
                {"Score", question.GetScore()}
            });
        }
        
        return crow::json::wvalue{ questionsJson };
    });

    auto& addUser = CROW_ROUTE(app, "/Users").methods(crow::HTTPMethod::PUT);
    auto& addQuestion = CROW_ROUTE(app, "/Questions").methods(crow::HTTPMethod::PUT);
    addUser(UserDatabaseControl(usersDb));
    addQuestion(QuestionDatabaseControl(questionsDb));

    app.port(18080).multithreaded().run();

    return 0;
}