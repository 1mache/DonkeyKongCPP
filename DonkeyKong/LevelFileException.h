#pragma once
#include <exception>
#include <string>

class LevelFileException : std::exception
{
	std::string message;
public:
	LevelFileException(const std::string& _message) : message(_message) {};

	const char* what() const noexcept override {
		return message.c_str();
	}
};