#include "Chat.h"
#include <iostream>


void Chat::startChat()
{
	running = true;
}

std::shared_ptr<User> Chat::findUserByLogin(const std::string& login) const
{
	for (auto& user : users)
	{
		if (login == user.getLogin())
			return std::make_shared<User>(user);
	}
	return nullptr;
}

std::shared_ptr<User> Chat::findUserByName(const std::string& name) const
{
	for (auto& user : users)
	{
		if (name == user.getName())
			return std::make_shared<User>(user);
	}
	return nullptr;
}

void Chat::login()
{
	std::string login, password;
	char operation;

	do
	{
		std::cout << "Логин: ";
		std::cin >> login;
		std::cout << "Пароль: ";
		std::cin >> password;

		currentUser = findUserByLogin(login);

		if (currentUser == nullptr || (password != currentUser->getPassword()))
		{
			currentUser = nullptr;

			std::cout << "Неверный логин" << std::endl;
			std::cout << "Для выхода: нажмите  |0|" << std::endl
				<< "Для повтора: нажмите |любую клавишу|" << std::endl;
			std::cin >> operation;

			if (operation == '0')
				break;
		}

	} while (!currentUser);
}

void Chat::signUp()
{
	std::string login, password, name;

	std::cout << "Логин: ";
	std::cin >> login;
	std::cout << "Пароль: ";
	std::cin >> password;
	std::cout << "Имя: ";
	std::cin >> name;

	User user = User(login, password, name);
	users.push_back(user);
	currentUser = std::make_shared<User>(user);
}

void Chat::showChat() const
{
	std::string from;
	std::string to;

	std::cout << "___________________________________" << std::endl;
	std::cout << "                 Чат               " << std::endl
		<< "___________________________________" << std::endl;

	for (auto& message : messages)
	{

		if (currentUser->getLogin() == message.getFrom() || currentUser->getLogin() == message.getTo() || message.getTo() == "all")
		{
			from = (currentUser->getLogin() == message.getFrom()) ? "(текущего пользователя)" : findUserByLogin(message.getFrom())->getName();

			if (message.getTo() == "all")
			{
				to = "(all)";
			}
			else
			{
				to = (currentUser->getLogin() == message.getTo()) ? "(текущего пользователя)" : findUserByLogin(message.getTo())->getName();
			}

			std::cout << "Сообщение от " << from << " :" << std::endl;
			std::cout << "текст сообщения: " << message.getText() << std::endl;

			std::cout << "___________________________________" << std::endl;
			std::cout << std::endl;
		}
	}
}

void Chat::showRegistration()
{
	currentUser = nullptr;

	char operation;

	do
	{
		std::cout << "Для ввода логина: нажмите-       |1|" << std::endl;
		std::cout << "Для регистрации в чате: нажмите- |2|" << std::endl;
		std::cout << "Для выхода из чата: нажмите-     |0|" << std::endl;
		std::cout << "Введите значение: ";
		std::cin >> operation;
		std::cout << "___________________________________" << std::endl;
		switch (operation)
		{
		case '1':
			login();
			break;
		case '2':
		{
			signUp();
		}
		break;
		case '0':
			running = false;
			break;

		default:
			std::cout << "Повторите попытку" << std::endl;
			break;
		}

	} while (!currentUser && running);
}

void Chat::showMessages()
{
	char operation;
	std::cout << "___________________________________" << std::endl;
	std::cout << "Добро пожаловать в чат  " << currentUser->getName() << std::endl;

	while (currentUser)
	{
		std::cout << "Просмотр чата:           нажмите |1| " << std::endl
			<< "Добавить сообщение:      нажмите |2| " << std::endl
			<< "Пользователи:            нажмите |3| " << std::endl
			<< "Для выхода:              нажмите |0| " << std::endl;

		std::cout << std::endl << "_ ";
		std::cin >> operation;

		switch (operation)
		{
		case '1':
			showChat();
			break;
		case '2':
			addMessage();
			break;
		case '3':
			showAllUsers();
			break;
		case'0':
			currentUser = nullptr;
			break;
		default:
			std::cout << "Повторите попытку" << std::endl;
			break;
		}
	}
}

void Chat::showAllUsers() const
{
	std::cout << "___________________________________" << std::endl;
	std::cout << "Пользователи:" << std::endl;
	for (auto& user : users)
	{
		std::cout << user.getName();

		if (currentUser->getLogin() == user.getLogin())
			std::cout << "(текущий пользователь)";

		std::cout << std::endl;
	}
}

void Chat::addMessage()
{
	std::string to, text;
	std::cout << "___________________________________" << std::endl;
	std::cout << "Отправить сообщение" << std::endl
		<< "Конкретному пользователю:        |введите его имя|" << std::endl
		<< "Всем пользователям:              |введите- all|   " << std::endl;
	std::cin >> to;
	std::cout << "текст сообщения: ";
	std::cin.ignore();
	getline(std::cin, text);

	if (!(to == "all" || findUserByName(to)))
	{
		std::cout << "Ошибка. Нет такого имени " << to << std::endl;
		std::cout << std::endl;
	}
	else if (to == "all")
	{
		messages.push_back(Message{ currentUser->getLogin(), "all",text });
	}
	else
	{
		messages.push_back(Message{ currentUser->getLogin(),findUserByName(to)->getLogin(),text });
	}
}

