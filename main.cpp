// Gabriel Nakamoto <gabriel@nakamoto.ca>
// December 2024
// rem -> 'remember' (note taking app)
//
//
// Flags:
//
// 	* 	= required
// 	|	= standalone
//
//		*-t 	-> title
//		*-b		-> body
// 		|-v 	-> view entries
//
//
// Formatting:
//
// 		date -> title
//
//			multi
//			line
//			indented
// 			content
//
// 	* indent at certain character amount
// 	** title then body in "brackets"
//
// 	Since brackets didnt work I gues flags

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <cstring>
#include <chrono>

namespace fs = std::filesystem;

const fs::path filepath = fs::path(getenv("HOME")) / ".remsource";

std::string getDate()
{
	using namespace std::chrono;

	auto now = system_clock::now();
	auto currentTime = system_clock::to_time_t(now);

	return std::ctime(&currentTime);
}

void viewNotes()
{
	std::ifstream file(filepath);

	std::string line;
	while (std::getline(file, line))
	{
		std::cout << line << '\n';
	}
	file.close();
}

// automatic move operator I think
std::vector<std::string> parseBody(const std::string &text)
{
	// new line after ~60 characters (add to config if I make one)

	std::istringstream 	buffer(text);
	std::string 			word;
	std::string 			context{};
	std::vector<std::string> 	body;

	int chars = 0;

	while (buffer >> word)
	{
		if (context.size() + word.size() > 60)
		{
			body.push_back(context);
            context.clear();
		}

		context += word + " ";
	}

    if(! context.empty())
    {
        body.push_back(context);
    }

	return body;
}

void addEntry(const std::string &title, const std::string &body)
{
	// std::ios::app -> append flag
	std::ofstream file(filepath, std::ios::app);

	if (! file.good())
	{
		std::cout << "Failed to open file\n";
		exit(1);
	}

	std::string date = getDate();

    // remove new line
	date.erase(date.size() - 1);

	// date -> title
	//
	// 		body
	// 		body
	// 		body

	file << date << " -> " << '[' + title << ']' << '\n' << '\n';

	std::vector<std::string> content = parseBody(body);

	for (auto &line : content)
	{
		file << '\t' << line << '\n';
	}

    file << '\n';
}

void parseEntry(int n, char **args)
{
	std::string title 	= "";
	std::string body 	= "";

	int index = 2;
	for (; index < n && strcmp(args[index], "-b"); ++index)
	{
		title += std::string(args[index])+ " ";
	}
    title.erase(title.size() - 1);

	if (index == n)
	{
		std::cout << "No body!\n";
		exit(1);
	}

    ++index;
	for (; index < n; ++index)
	{
        body += std::string(args[index]) + " ";
	}

	addEntry(title, body);
}

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		std::cout << "Usage rem <flags> <note>\n";
		return 1;
	} else
	{
		if (strcmp(argv[1],"-v") == 0)
		{
			viewNotes();
		} else if (strcmp(argv[1], "-t") == 0){
			parseEntry(argc, argv);
		}
	}
	return 0;
}
