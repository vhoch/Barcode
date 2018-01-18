#ifndef BARCODEEAN13_H
#define BARCODEEAN13_H

#include <string>
#include "BarCode.h"

using namespace std;


class BarCodeEAN13 : public CBarCode
{
    int m_digits[12];
    int m_checksum;
    std::string m_code;

    static const string ParityEncodings[10];
    static const string EndBar;
    static const string MiddleBar;
    static const string LeftOddCoding[10];
    static const string LeftEvenCoding[10];
    static const string RightCoding[10];

    static const std::string XMLVersion;
    static const std::string Doctype;
    static const std::string SVGHeader;


public:

    BarCodeEAN13(const int* eanCode);
    BarCodeEAN13(const std::string& eanCode);

    virtual void zero();
    virtual void print() const;
    virtual bool isValid() const;
    virtual bool parseInput(const std::string& data);
    virtual void exportToSVG(std::size_t scale, std::size_t offsetX, std::size_t offsetY, bool svgHeader = false) const;
    const int* digits();
    int checkSum();

private:
    int computeCheckSum() const;
    void encode();
};

#endif // BARCODEEAN13_H
