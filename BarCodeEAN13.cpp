#include "BarCodeEAN13.h"

#include <iostream>
#include <cstring>

#define ARRAY_SIZE 12

using namespace std;

const string BarCodeEAN13::ParityEncodings[10] = {"111111", "110100", "110010", "110001", "101100", "100110", "100011", "101010", "101001", "100101"};
const string BarCodeEAN13::EndBar = "101";
const string BarCodeEAN13::MiddleBar = "01010";
const string BarCodeEAN13::LeftOddCoding[10] = {"0001101", "0011001", "0010011", "0111101", "0100011", "0110001", "0101111", "0111011", "0110111", "0001011"};
const string BarCodeEAN13::LeftEvenCoding[10] = {"0100111", "0110011", "0011011", "0100001", "0011101", "0111001", "0000101", "0010001", "0001001", "0010111"};
const string BarCodeEAN13::RightCoding[10] = {"1110010", "1100110", "1101100", "1000010", "1011100", "1001110", "1010000", "1000100", "1001000", "1110100"};

const string CBarCode::XMLVersion	= "<?xml version=\"1.0\" standalone=\"no\"?>";
const string CBarCode::Doctype		= "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">";
const string CBarCode::SVGHeader	= "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">";

BarCodeEAN13::BarCodeEAN13(const int* eanCode)
{
    for (int i=0; i < ARRAY_SIZE; i++) {
        m_digits[i] = eanCode[i];
    }

    m_checksum = computeCheckSum();

    encode();
}

BarCodeEAN13::BarCodeEAN13(const std::string& eanCode)
{
    for (int i=0; i < ARRAY_SIZE; i++) {
        m_digits[i] = eanCode[i] - '0';
    }

    m_checksum = computeCheckSum();

    encode();
}

void BarCodeEAN13::zero()
{
    for (int i = 0; i < ARRAY_SIZE; i++) {
        m_digits[i] = 0;
    }
    m_checksum = computeCheckSum();
}
void BarCodeEAN13::print() const
{
    for (int i : m_digits) {
        std::cout << i;
    }

    std::cout << m_checksum;
}
bool BarCodeEAN13::isValid() const
{
    for (int i : m_digits) {
        if (i > 9 || i < 0) {
            return false;
        }
    }

    if (m_checksum != BarCodeEAN13::computeCheckSum()) {
        return false;
    }

    return true;
}
bool BarCodeEAN13::parseInput(const std::string& data)
{
    zero();

    int data_size = (sizeof(data)/sizeof(data[0]));

    if (data_size > ARRAY_SIZE) {
        data_size = ARRAY_SIZE;
    }

    for (int i = 0; i < data_size; i++) {
        if (isdigit(data[i])) {
            m_digits[i] = data[i] - '0';
        } else if (data[i] == ' ') {
            continue;
        } else {
            m_checksum = computeCheckSum();
            return false;
        }
    }
    cout << "---------------" << endl;
    for (int i = 0; i < 12; i++)
        cout << m_digits[i];
    cout << "---------------" << endl;
    m_checksum = computeCheckSum();
    if (data_size < ARRAY_SIZE)
        return false;
    return true;
}

void BarCodeEAN13::exportToSVG(std::size_t scale, std::size_t offsetX, std::size_t offsetY, bool svgHeader) const
{
    int width = scale * (3+42+5+42+3);
    int height = width * 0.65;
    int anotherheight = height * 0.9;
    int current_width = offsetX;
    std::string color;
    int current_index = 0;

    if (svgHeader) {
        std::cout << CBarCode::XMLVersion << std::endl;
        std::cout << CBarCode::Doctype << std::endl;
        std::cout << CBarCode::SVGHeader << std::endl;
    }

    if (isValid()) {
        for (char ch : m_code) {
            if (current_width < (offsetX + width)) {
                if (ch == '0') {
                    color = "white";
                } else if (ch == '1') {
                    color = "black";
                } else {
                    continue;
                }

                if (current_index < 3 || (current_index > 44 && current_index < 50) || current_index > 91) {
                    std::cout << "<rect x=\"" << current_width
                              << "\" y=\"" << offsetY
                              << "\" width=\"" << scale
                              << "\" height=\"" << height
                              << "\" fill=\"" << color
                              << "\" />"
                              << std::endl;
                } else {
                    std::cout << "<rect x=\"" << current_width
                              << "\" y=\"" << offsetY
                              << "\" width=\"" << scale
                              << "\" height=\"" << anotherheight
                              << "\" fill=\"" << color
                              << "\" />"
                              << std::endl;
                }
                current_width += scale;
                current_index++;
            }
        }
    }

    if (svgHeader) {
        std::cout << "</svg>" << std::endl;
    }
}

const int* BarCodeEAN13::digits()
{
    return m_digits;
}
int BarCodeEAN13::checkSum()
{
    return m_checksum;
}

int BarCodeEAN13::computeCheckSum() const
{
    int help = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if ((i+1) % 2 == 0) {
            help += m_digits[i] * 3;
        } else {
            help += m_digits[i];
        }
    }

    int checksum = (10 - (help % 10)) % 10;

    return checksum;
}

void BarCodeEAN13::encode()
{
    std::string encoding = ParityEncodings[m_digits[0]];

    m_code += EndBar + " ";


    int index = 1;
    for (char digit : encoding) {
        int intDigit = digit - '0';
        if (intDigit == 0) {
            m_code += LeftEvenCoding[m_digits[index]];
        } else {
            m_code += LeftOddCoding[m_digits[index]];
        }
        m_code += " ";
        index++;
    }

    m_code += MiddleBar + " ";

    while (index < ARRAY_SIZE) {
        m_code += RightCoding[m_digits[index]];
        m_code += " ";
        index++;
    }

    m_code += RightCoding[m_checksum] + " ";

    m_code += EndBar;
}

