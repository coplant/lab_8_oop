#include "Header.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "incorrect command line! "
            "Waited: command in_file out_file"
            << endl;
        exit(1);
    }

    ifstream ifst(argv[1]);
    ofstream ofst(argv[2]);

    cout << "Start" << endl;

    Container C; 

    C.In(ifst); 

    ofst << "Filled container. " << endl;

    C.Out(ofst); 

    C.Clear(); 

    ofst << "Empty container. " << endl;

    C.Out(ofst); 

    cout << "Stop" << endl;

    system("pause");
    return 0;
}