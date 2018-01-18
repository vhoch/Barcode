#ifndef BARCODEDATAMATRIX_H
#define BARCODEDATAMATRIX_H

#include "BarCode.h"

using namespace std;

class BarCodeDataMatrix : CBarCode
{
    std::size_t m_size;
    bool * * m_data[3][3];

public:
    BarCodeDataMatrix(const std::string& data, std::size_t dataMatrixSize);
    ~BarCodeDataMatrix();
    std::size_t size();

    virtual void zero();
    virtual void print() const;
    virtual bool isValid() const;
    virtual bool parseInput(const std::string& data);
    virtual void exportToSVG(std::size_t scale, std::size_t offsetX, std::size_t offsetY, bool svgHeader = false) const;
};

#endif // BARCODEDATAMATRIX_H
