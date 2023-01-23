#include "main.h"


int main()
{
	HashTable::Hashtable<std::string, std::string, 1> earth;

	earth.Put("china", "pekin");
	earth.Put("greece", "athens");
	earth.Put("Russia", "Moscow");
	earth.Put("kazakhstan", "astana");
	earth.Put("japan", "tokyo");
	earth.Put("latvia", "riga");
	earth.Put("liechtenstein", "vaduz");
	earth.Put("maldives", "male");
	earth.Put("spain", "madrid");
	earth.Put("syria", "damascus");

	

	for (int i = 0; i != 5; ++i)
	{
		std::cout << "Enter the Country or Capial: ";
		std::string input;
		std::cin >> input;

		HashTable::Node<std::string, std::string> *tmp = earth.Get(input, input);

		if (tmp != nullptr)
		{
			if (HashTable::isCountry)
			{
				std::cout << tmp->getCapital() << std::endl;
				HashTable::isCountry = false;
			}
			else if (HashTable::isCapital)
			{
				std::cout << tmp->getCountry() << std::endl;
				HashTable::isCapital = false;
			}
		}
		else
		{
			std::cout << "The invalid input, you can input only capial of the county or the country" << std::endl;
		}
	}

	return 0;
}
