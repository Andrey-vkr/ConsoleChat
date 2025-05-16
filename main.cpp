#include <iostream>
#include "Chat.h"


int main()
{
	setlocale(LC_ALL, "");

	Chat chat;
	chat.startChat();
	while (chat.isChatRunning())
	{
		chat.showRegistration();

		while (chat.getCurrentUser())
		{
			chat.showMessages();
		}
	}

	return 0;
}