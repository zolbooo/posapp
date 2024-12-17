#include "models.h"

Cashier read_cashier()
{
	Cashier cashier;
	std::cout << "Enter last name: ";
	std::getline(std::cin, cashier.last_name);
	std::cout << "Enter first name: ";
	std::getline(std::cin, cashier.first_name);
	std::cout << "Enter username: ";
	std::getline(std::cin, cashier.username);
	std::cout << "Enter password: ";
	std::getline(std::cin, cashier.password);
	return cashier;
}

int count_cashiers(sqlite3 *db)
{
	sqlite3_stmt *count_all_cashiers_statement = NULL;
	if (sqlite3_prepare_v2(db, "SELECT COUNT(*) FROM cashiers;", -1, &count_all_cashiers_statement, NULL) != SQLITE_OK)
	{
		std::cerr << "Error preparing count all cashiers statement: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		exit(1);
	}
	int total_cashiers = 0;
	assert(sqlite3_step(count_all_cashiers_statement) == SQLITE_ROW);
	total_cashiers = sqlite3_column_int(count_all_cashiers_statement, 0);
	sqlite3_finalize(count_all_cashiers_statement);
	return total_cashiers;
}

ProductType read_product_type()
{
	ProductType type;
	std::cout << "Enter type name: ";
	std::getline(std::cin, type.type_name);
	return type;
}

ProductType create_product_type(sqlite3 *db)
{
	ProductType type = read_product_type();
	sqlite3_stmt *insert_product_type_statement = NULL;
	if (sqlite3_prepare_v2(db, "INSERT INTO product_categories (name) VALUES (?) RETURNING category_id;", -1, &insert_product_type_statement, NULL) != SQLITE_OK)
	{
		std::cerr << "Error preparing insert product type statement: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		exit(1);
	}
	sqlite3_bind_text(insert_product_type_statement, 1, type.type_name.c_str(), -1, SQLITE_STATIC);
	if (sqlite3_step(insert_product_type_statement) != SQLITE_ROW)
	{
		std::cerr << "Error inserting product type: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		exit(1);
	}
	type.type_id = sqlite3_column_int(insert_product_type_statement, 0);
	sqlite3_finalize(insert_product_type_statement);
	return type;
}

Product read_product()
{
	Product product;
	std::cout << "Enter product name: ";
	std::getline(std::cin, product.product_name);
	std::cout << "Enter type ID: ";
	std::cin >> product.type_id;
	std::cout << "Enter price: ";
	std::cin >> product.price;
	std::cin.ignore();
	return product;
}

Purchase read_purchase()
{
	Purchase purchase;
	std::cout << "Enter product ID: ";
	std::cin >> purchase.product_id;
	std::cout << "Enter quantity: ";
	std::cin >> purchase.quantity;
	purchase.total_price = purchase.quantity * 1000;
	std::cin.ignore();
	return purchase;
}