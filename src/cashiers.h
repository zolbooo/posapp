#pragma once
#include "models.h"
#include "sqlite3.h"

#include <cassert>

Cashier authorize(sqlite3 *db);
