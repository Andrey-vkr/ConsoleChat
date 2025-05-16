#pragma once
#include <vector>
#include <memory>
#include "Message.h"


class Chat
{
private:
	bool running = false;
	std::vector<User> users;
	std::vector<Message> messages;
	std::shared_ptr<User> currentUser;
	void login();
	void signUp();
	void showChat() const;
	void showAllUsers() const;
	void addMessage();

	std::vector<User>& getUsers()
	{
		return users;
	}

	std::vector<Message>& getMessages()
	{
		return messages;
	}

	std::shared_ptr<User> findUserByLogin(const std::string& login) const;
	std::shared_ptr<User> findUserByName(const std::string& name) const;

public:
	void startChat();

	bool isChatRunning() const
	{
		return running;
	}

	std::shared_ptr<User> getCurrentUser() const
	{
		return currentUser;
	}

	void showRegistration();
	void showMessages();
};

