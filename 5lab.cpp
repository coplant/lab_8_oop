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

    Container C; //Объявление контейнера

    C.In(ifst); //Ввод элементов контейнера

    C.Sort(); //Сортировка контейнера

    ofst << "Filled and sorted container. " << endl;

    C.Out(ofst); //Вывод контейнера

    C.Out_Only_Truck(ofst); //Вывод только грузовиков

    C.Clear(); //Очистка контейнера

    ofst << "Empty container. " << endl;

    C.Out(ofst); //Вывод контейнера

    cout << "Stop" << endl;

    system("pause");
    return 0;
}