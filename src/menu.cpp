#include "menu.h"

void menu(sqlite3 *db)
{
	std::cout << "Welcome to the POS System!" << std::endl;

	bool run = true;
	int choice = 0;
	while (run)
	{
		// Create a category
		std::cout << "1. Create a category" << std::endl;
		// Create a product
		std::cout << "2. Create a product" << std::endl;
		// Purchase
		std::cout << "3. Purchase" << std::endl;
		// Exit
		std::cout << "4. Exit" << std::endl;

		std::cout << "Enter your choice: ";
		std::cin >> choice;
		std::cin.ignore();
		switch (choice)
		{
		case 1:
			create_product_type(db);
			break;
		case 2:
			// create_product(db);
			break;
		case 3:
			// purchase(db);
			break;
		case 4:
			run = false;
			break;
		default:
			std::cout << "Invalid choice." << std::endl;
			break;
		}
	}
}
