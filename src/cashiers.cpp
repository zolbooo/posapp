#include "cashiers.h"

Cashier register_cashier(sqlite3 *db)
{
	sqlite3_stmt *create_cashier_statement = NULL;
	if (sqlite3_prepare_v2(db, "INSERT INTO cashiers (last_name, first_name, username, password) VALUES (?1, ?2, ?3, ?4);", -1, &create_cashier_statement, NULL) != SQLITE_OK)
	{
		std::cerr << "Error preparing create cashier statement: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		exit(1);
	}
	Cashier cashier = read_cashier();
	sqlite3_bind_text(create_cashier_statement, 1, cashier.last_name.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(create_cashier_statement, 2, cashier.first_name.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(create_cashier_statement, 3, cashier.username.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(create_cashier_statement, 4, cashier.password.c_str(), -1, SQLITE_STATIC);
	if (sqlite3_step(create_cashier_statement) != SQLITE_DONE)
	{
		std::cerr << "Error creating cashier: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		exit(1);
	}
	sqlite3_finalize(create_cashier_statement);
	return cashier;
}

Cashier authorize(sqlite3 *db)
{
	if (count_cashiers(db) == 0)
	{
		std::cout << "No cashiers found. Please create a cashier account." << std::endl;
		return register_cashier(db);
	}

	std::string username, password;
	std::cout << "Username: ";
	std::cin >> username;
	std::cout << "Password: ";
	std::cin >> password;

	sqlite3_stmt *authorize_statement = NULL;
	if (sqlite3_prepare_v2(db, "SELECT * FROM cashiers WHERE username = ?1 AND password = ?2;", -1, &authorize_statement, NULL) != SQLITE_OK)
	{
		std::cerr << "Error preparing authorize statement: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		exit(1);
	}
	sqlite3_bind_text(authorize_statement, 1, username.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(authorize_statement, 2, password.c_str(), -1, SQLITE_STATIC);
	if (sqlite3_step(authorize_statement) != SQLITE_ROW)
	{
		std::cerr << "Invalid username or password." << std::endl;
		sqlite3_finalize(authorize_statement);
		sqlite3_close(db);
		exit(1);
	}

	Cashier cashier;
	cashier.cashier_id = sqlite3_column_int(authorize_statement, 0);
	cashier.last_name = std::string(reinterpret_cast<const char *>(sqlite3_column_text(authorize_statement, 1)));
	cashier.first_name = std::string(reinterpret_cast<const char *>(sqlite3_column_text(authorize_statement, 2)));
	cashier.username = std::string(reinterpret_cast<const char *>(sqlite3_column_text(authorize_statement, 3)));
	cashier.password = std::string(reinterpret_cast<const char *>(sqlite3_column_text(authorize_statement, 4)));
	sqlite3_finalize(authorize_statement);
	return cashier;
}
