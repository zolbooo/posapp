#include "db.h"

using namespace std;

int main()
{
	sqlite3 *db = init_db();
	sqlite3_close(db);
	return 0;
}
