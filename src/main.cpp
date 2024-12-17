#include "db.h"
#include "menu.h"
#include "cashiers.h"

#include <iostream>

using namespace std;

int main()
{
	sqlite3 *db = init_db();
	Cashier cashier = authorize(db);
	menu(db);
	sqlite3_close(db);
	return 0;
}
