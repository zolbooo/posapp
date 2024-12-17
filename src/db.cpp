#include "db.h"

#include <iostream>

using namespace std;

auto init_sql = "CREATE TABLE IF NOT EXISTS cashiers (\n"
	"cashier_id INTEGER PRIMARY KEY AUTOINCREMENT,\n"
	"last_name TEXT NOT NULL,\n"
	"first_name TEXT NOT NULL,\n"
	"username TEXT NOT NULL UNIQUE,\n"
	"password_hash TEXT NOT NULL\n"
");\n"
"CREATE TABLE IF NOT EXISTS product_categories (\n"
	"category_id INTEGER PRIMARY KEY AUTOINCREMENT,\n"
	"name TEXT NOT NULL\n"
");\n"
"CREATE TABLE IF NOT EXISTS products (\n"
	"product_id INTEGER PRIMARY KEY AUTOINCREMENT,\n"
	"name TEXT NOT NULL,\n"
	"barcode TEXT NOT NULL UNIQUE,\n"
	"category_id INTEGER NOT NULL,\n"
	"unit_price REAL NOT NULL,\n"
	"storage_quantity INTEGER NOT NULL,\n"
	"FOREIGN KEY (category_id) REFERENCES product_categories(category_id)\n"
");\n"
"CREATE TABLE IF NOT EXISTS purchases (\n"
	"purchase_id INTEGER PRIMARY KEY AUTOINCREMENT,\n"
	"date DATETIME NOT NULL,\n"
	"cashier_id INTEGER NOT NULL,\n"
	"total_amount REAL NOT NULL,\n"
	"payment_method TEXT NOT NULL,\n"
	"payment_amount REAL NOT NULL,\n"
	"FOREIGN KEY (cashier_id) REFERENCES cashiers(cashier_id)\n"
");\n"
"CREATE TABLE IF NOT EXISTS purchase_products (\n"
	"id INTEGER PRIMARY KEY AUTOINCREMENT,\n"
	"purchase_id INTEGER NOT NULL,\n"
	"product_id INTEGER NOT NULL,\n"
	"quantity REAL NOT NULL,\n"
	"subtotal REAL NOT NULL,\n"
	"FOREIGN KEY (purchase_id) REFERENCES purchases(purchase_id),\n"
	"FOREIGN KEY (product_id) REFERENCES products(product_id)\n"
");\n"
;

sqlite3 *init_db() {
	sqlite3 *db;
	if (sqlite3_open("app.sqlite3", &db) != SQLITE_OK)
	{
		cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
		exit(1);
	}
	if (sqlite3_exec(db, init_sql, nullptr, nullptr, nullptr) != SQLITE_OK)
	{
		cerr << "Can't initialize database: " << sqlite3_errmsg(db) << endl;
		exit(1);
	}
	return db;
}
