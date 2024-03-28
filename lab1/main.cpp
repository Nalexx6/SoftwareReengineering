
#include "cli/Commands.h"
#include "db/service/ProductsService.h"

using namespace std;


int main() {
    char response = 'y';

    Commands command;

    while(response == 'y') {
        cout << "Please select the mode:\n"
                "0 - interactive\n"
                "1 - demo\n"
                "2 - benchmark\n";
        short key;
        cin >> key;
        switch (key) {
            case 0:
                command.interactive();
                break;
            case 1:
                command.demo();
                break;
            case 2:
                command.benchmark();
                break;
            default:
                break;
        }

        cout<<"Press y, if you want to continue in another mode, n, if you don`t\n";
        char r_1;
        cin>>r_1;
        response = r_1;
    }
    return 0;
}