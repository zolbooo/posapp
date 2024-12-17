#pragma once
#include "sqlite3.h"

#include <iostream>
#include <cassert>
#include <string>

struct Cashier
{
	int cashier_id = -1;
	std::string last_name;
	std::string first_name;
	std::string username;
	std::string password;
};

// Product Type Struct
struct ProductType
{
	int type_id = -1;
	std::string type_name;
};

// Product Struct
struct Product
{
	int product_id = -1;
	std::string product_name;
	int type_id = -1;
	double price = 0.0;
};

// Purchase Struct
struct Purchase
{
	int purchase_id = -1;
	int product_id = -1;
	int quantity = 0;
	double total_price = 0.0;
};

Cashier read_cashier();
int count_cashiers(sqlite3 *db);

ProductType read_product_type();
Product read_product();
Purchase read_purchase();
