#include "db.h"
#include "cashiers.h"

#include <iostream>

using namespace std;

int main()
{
	sqlite3 *db = init_db();

	Cashier cashier = authorize(db);
	cout << "Welcome to the POS System!" << endl;

	sqlite3_close(db);
	return 0;
}
