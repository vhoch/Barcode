#include <iostream>
#include <fstream>
#include <string>

#include "BarCodeEAN13.h"
#include "BarCodeDataMatrix.h"
#include "BarCode.h"

using namespace std;

int main(int argc, char *argv[])
{
    int eanArray[12] = {9, 7, 8, 8, 0, 2, 1, 0, 4, 8, 5, 7};

        BarCodeEAN13 eanFromArray(eanArray);
        BarCodeEAN13 eanFromString("330721166750");
        BarCodeDataMatrix *dataMatrix = new BarCodeDataMatrix("101011 100101 110100 101011 100010 111111", 6);

        cout << "EAN-13 Basic tests" << endl;
        cout << "==================" << endl << endl;

        // Constructor 1 + print()
        cout << "Expected output: 9788021048577" << endl;
        cout << "Provided output: ";
        eanFromArray.print();
        cout << endl << endl; //ok

        // Contructor 2 + print()
        cout << "Expected output: 3307211667501" << endl;
        cout << "Provided output: ";
        eanFromString.print();
        cout << endl << endl;

        // digits() + checkSum()
        cout << "Expected output: 9788021048577" << endl;
        cout << "Provided output: ";
        for(int i = 0; i < 12; i++)
            cout << *(eanFromArray.digits() + i);

        cout << eanFromArray.checkSum() << endl << endl;

        // zero() + print()
        eanFromString.zero();
        cout << "Expected output: 0000000000000" << endl;
        cout << "Provided output: ";
        eanFromString.print();
        cout << endl << endl;

        //std::cout << CBarCode::XMLVersion << std::endl;
        //std::cout << CBarCode::Doctype << std::endl;
        //std::cout << CBarCode::SVGHeader << std::endl;

        eanFromArray.exportToSVG(4, 40, 60);
        eanFromString.exportToSVG(5, 500, 60);
        //dataMatrix->exportToSVG(40, 40, 400);

        //std::cout << "</svg>" << std::endl;
}
