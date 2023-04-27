#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main()
{
	std::ifstream map ("Map.csv");
	// Extracting the contents of the map
	std::vector<std::string> mapContent;
	std::string line, word;

	if (map.is_open())
	{
		while (std::getline(map, line))
		{
			std::stringstream stream(line);

			while (std::getline(stream, word, ','))
			{
                std::cout << "Word: " << word << std::endl;
				mapContent.push_back(word);
			}
		}
	}
	else
	{
		std::cout << "Unable to load map file!" << std::endl;
	}

	std::cout << "Number of rows: " << mapContent.size() << std::endl;
	std::cout << "Number of columns: " << mapContent[0].size() << std::endl;
	
    for (int rowCnt = 0; rowCnt < mapContent.size(); rowCnt++)
    {
        std::cout << mapContent[rowCnt];
    }
    return 0;
}






