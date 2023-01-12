#include "Database.h"

std::vector<Question> Database::SeparateQuestions(const crow::json::rvalue& questionsJson)
{
	std::vector<Question> questions;

	for (const auto& question : questionsJson["results"])
	{
		std::string text = question["question"].s();
		std::string correctAnswer = question["correct_answer"].s();

		text = curl_unescape(text.c_str(), text.length());
		correctAnswer = curl_unescape(correctAnswer.c_str(), correctAnswer.length());

		Question currentQuestion;

		currentQuestion.SetText(text);
		currentQuestion.SetAnswer(correctAnswer);
		try
		{
			std::stod(correctAnswer);

			currentQuestion.SetIsNumerical(true);
			questions.push_back(currentQuestion);
		}
		catch (std::exception)
		{
			std::string incorrectAnswers = "";

			for (const auto& wrongAnswer : question["incorrect_answers"])
			{
				std::string incorrectAnswer = wrongAnswer.s();
				incorrectAnswer = curl_unescape(incorrectAnswer.c_str(), incorrectAnswer.length());

				incorrectAnswers += incorrectAnswer + ",";
			}

			incorrectAnswers.pop_back();
			currentQuestion.SetIncorrectAnswers(incorrectAnswers);

			questions.push_back(currentQuestion);
		}
	}

	return questions;
}

void Database::AddQuestions(Storage& database)
{
	if (database.count<Question>() == 0)
	{
		std::string easyQuestionsUrl = "https://opentdb.com/api.php?amount=50&difficulty=easy&encode=url3986";
		std::string mediumQuestionsUrl = "https://opentdb.com/api.php?amount=50&difficulty=medium&encode=url3986";
		std::string hardQuestionsUrl = "https://opentdb.com/api.php?amount=50&difficulty=hard&encode=url3986";

		cpr::Response easyRequest = cpr::Get(cpr::Url{ easyQuestionsUrl });
		cpr::Response mediumRequest = cpr::Get(cpr::Url{ mediumQuestionsUrl });
		cpr::Response hardRequest = cpr::Get(cpr::Url{ hardQuestionsUrl });

		auto easyQuestions = SeparateQuestions(crow::json::load(easyRequest.text));
		auto mediumQuestions = SeparateQuestions(crow::json::load(mediumRequest.text));
		auto hardQuestions = SeparateQuestions(crow::json::load(hardRequest.text));

		database.insert_range(easyQuestions.begin(), easyQuestions.end());
		database.insert_range(mediumQuestions.begin(), mediumQuestions.end());
		database.insert_range(hardQuestions.begin(), hardQuestions.end());
	}
}

//------------------------------------- LOGIN -------------------------------------

Database::LoginUserHandler::LoginUserHandler(Storage& storage) : database{ storage }
{
}

crow::response Database::LoginUserHandler::operator()(const crow::request& request)	const
{
	auto arguments = ParseUrlArgs(request.body);
	auto username = arguments.find("Username")->second;
	auto password = arguments.find("Password")->second;

	username = curl_unescape(username.c_str(), username.length());
	password = curl_unescape(password.c_str(), password.length());

	for (const auto& user : database.iterate<User>())
	{
		if (username == user.GetName() && password == user.GetPassword())
		{
			return crow::response(200);
		}

		if (username == user.GetName() && password != user.GetPassword())
		{
			return crow::response(409, "Invalid password");
		}
	}

	return crow::response(409, "Username not found");
}


//------------------------------------ REGISTER ------------------------------------


Database::RegisterUserHandler::RegisterUserHandler(Storage& storage) : database{ storage }
{
}

crow::response Database::RegisterUserHandler::operator()(const crow::request& request) const
{
	auto arguments = ParseUrlArgs(request.body);
	auto username = arguments.find("Username")->second;

	username = curl_unescape(username.c_str(), username.length());

	for (const auto& user : database.iterate<User>())
	{
		if (username == user.GetName())
		{
			return crow::response(409, "Username already used");
		}
	}

	auto email = arguments.find("Email")->second;
	auto password = arguments.find("Password")->second;
	auto imagePath = arguments.find("Image path")->second;

	email = curl_unescape(email.c_str(), email.length());
	password = curl_unescape(password.c_str(), password.length());
	imagePath = curl_unescape(imagePath.c_str(), imagePath.length());

	User user;
	user.SetName(username);
	user.SetEmail(email);
	user.SetPassword(password);
	user.SetImagePath(imagePath);

	database.replace(user);

	return crow::response(200);
}

//-------------------------------------- USER --------------------------------------

Database::UserHandler::UserHandler(Storage& storage) : database{ storage }
{
}

crow::response Database::UserHandler::operator()(const crow::request& request, const std::string& userId) const
{
	auto arguments = ParseUrlArgs(request.body);
	auto end = arguments.end();

	auto email = arguments.find("Email");
	auto password = arguments.find("Password");
	auto imagePath = arguments.find("Image path");

	User user = database.get<User>(userId);

	if (email != end)
	{
		user.SetEmail(curl_unescape(email->second.c_str(), email->second.length()));
	}
	if (password != end)
	{
		user.SetPassword(curl_unescape(password->second.c_str(), password->second.length()));
	}
	if (imagePath != end)
	{
		user.SetImagePath(curl_unescape(imagePath->second.c_str(), imagePath->second.length()));

	}

	database.update(user);

	return crow::response(200);
}

//-------------------------------------- ROOM --------------------------------------

Database::RoomHandler::RoomHandler(std::vector<Room>& rooms) : m_rooms{ rooms }
{
}

crow::response Database::RoomHandler::operator()(const crow::request& request, const std::string& roomCode) const
{
	if (request.method == crow::HTTPMethod::Post)
	{
		auto arguments = ParseUrlArgs(request.body);
		auto end = arguments.end();

		auto startGamePair = arguments.find("Game start");

		if (startGamePair != end)
		{
			int startGame = std::stoi(startGamePair->second);
			
			for (auto& room : m_rooms)
			{
				if (room.GetRoomCode() == roomCode)
				{
					room.SetStartGame(startGame);
				}
			}
		}
	}

	try
	{
		auto foundRoom = std::find(m_rooms.begin(), m_rooms.end(), roomCode);
		if (foundRoom == m_rooms.end())
		{
			return crow::response(409, "Invalid code");
		}
		if (foundRoom->GetMaxUsers() == foundRoom->GetUsers().size())
		{
			return crow::response(409, "Room full");
		}

		auto arguments = ParseUrlArgs(request.body);
		auto end = arguments.end();

		auto usernamePair = arguments.find("User name");
		auto imagePathPair = arguments.find("Image path");

		if (usernamePair != end && imagePathPair != end)
		{
			std::string username = usernamePair->second;
			std::string imagePath = imagePathPair->second;

			username = curl_unescape(username.c_str(), username.length());
			imagePath = curl_unescape(imagePath.c_str(), imagePath.length());


			User newUser;
			newUser.SetName(username);
			newUser.SetImagePath(imagePath);

			foundRoom->AddUser(newUser);
		}

		return crow::response(200);
	}
	catch (std::exception)
	{
		return crow::response(409, "Invalid code");
	}
}

Database::LeaveRoomHandler::LeaveRoomHandler(std::vector<Room>& rooms) : m_rooms{ rooms }
{
}

crow::response Database::LeaveRoomHandler::operator()(const crow::request& request, const std::string& roomCode) const
{
	auto foundRoom = std::find(m_rooms.begin(), m_rooms.end(), roomCode);
	auto arguments = ParseUrlArgs(request.body);

	auto username = arguments.find("User name")->second;
	username = curl_unescape(username.c_str(), username.length());

	if (username == foundRoom->GetOwner().GetName())
	{
		m_rooms.erase(foundRoom);
		return crow::response(204);
	}
	else
	{
		foundRoom->RemoveUser(username);
	} 
	return crow::response(200);
}

//-------------------------------------- GAME --------------------------------------

Database::GameHandler::GameHandler(std::vector<Game>& games) : m_games{ games }
{
}

crow::response Database::GameHandler::operator()(const crow::request& request, const std::string& gameCode) const
{
	auto foundGame = std::find(m_games.begin(), m_games.end(), gameCode);
	auto arguments = ParseUrlArgs(request.body);
	auto end = arguments.end();

	if (foundGame->GetGameState() == Game::JOINING)
	{
		auto usernameFound = arguments.find("Player name");
		auto regionsCountFound = arguments.find("Regions count");

		if (regionsCountFound != end)
		{
			int regionsCount = std::stoi(curl_unescape(regionsCountFound->second.c_str(), regionsCountFound->second.length()));
			foundGame->SetRegionsNumber(regionsCount);
		}

		if (usernameFound != end)
		{
			std::string username = curl_unescape(usernameFound->second.c_str(), usernameFound->second.length());
			foundGame->AddPlayer(username);
		}

		if (foundGame->IsFull() == true)
		{
			foundGame->SetGameState(Game::BASE_FIGHT);
		}
	}
	else if (foundGame->GetGameState() == Game::BASE_FIGHT)
	{

	}
	else if (foundGame->GetGameState() == Game::BASE_SELECTION)
	{

	}
	else if (foundGame->GetGameState() == Game::DUELS)
	{

	}
	else if (foundGame->GetGameState() == Game::REGION_SELECTION)
	{

	}
	else if (foundGame->GetGameState() == Game::ENDING)
	{

	}

	return crow::response(200);
}
