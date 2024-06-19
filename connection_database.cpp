#include <iostream>
#include <pqxx/pqxx>
#include <string>
using namespace std;
int main() {
    try {
        // Connect to the database
        pqxx::connection c("user=postgres password=divine host=127.0.0.1 port=5432 dbname=testdb target_session_attrs=read-write");
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 1;
    }
}