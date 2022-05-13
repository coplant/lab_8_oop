#include "Header.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "incorrect command line! "
            "Waited: command in_file out_file"
            << endl;
        exit(1);
    }

    ifstream ifst(argv[1]);
    if (!ifst.is_open()) {
        cout << "No input file found or could not open!" << endl;
        system("pause");
        return 1;
    }

    ofstream ofst(argv[2]);
    if (!ofst.is_open()) {
        cout << "No output file found or could not open!" << endl;
        system("pause");
        return 1;
    }

    cout << "Start" << endl;
    Container C;
    C.In(ifst);
    C.Sort();

    ofst << "Filled and sorted container. " << endl;
    C.Out(ofst);
    C.Out_Only_Truck(ofst);
    C.Clear();
    ofst << "Empty container. " << endl;

    C.Out(ofst);

    cout << "Stop" << endl;
    system("pause");
    return 0;
}