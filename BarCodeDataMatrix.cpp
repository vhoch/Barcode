#include "BarCodeDataMatrix.h"

#include <iostream>

using namespace std;

BarCodeDataMatrix::BarCodeDataMatrix(const std::string& data, std::size_t dataMatrixSize)
{
    if (dataMatrixSize == 0) {
        //m_size = std::nullptr_t;
    } else {
        m_size = dataMatrixSize;
        //m_data = new bool[m_size][m_size];
        bool **m_data [m_size][m_size];
        //parseInput(data);
    }
}

BarCodeDataMatrix::~BarCodeDataMatrix()
{
    delete **m_data;
}

void BarCodeDataMatrix::zero()
{
    for (size_t row = 0; row < size(); row++) {
        for (size_t column = 0; column < size(); column++) {
            **m_data[row][column] = false;
        }
    }
}

void BarCodeDataMatrix::print() const
{
    for (int row = 0; row < m_size; row++) {
        for (int column = 0; column < m_size; column++) {
            if (**m_data[row][column] == true)
                std::cout << '#';
            else
                std::cout << ' ';
        }
    }
}

bool BarCodeDataMatrix::isValid() const
{
    if (m_data == nullptr)
        return false;
    else if ((sizeof(m_data)/sizeof(m_data[0])) != m_size)
        return false;
    else if ((sizeof(m_data[0])/sizeof(m_data[0][0])) != m_size)
        return false;
    else
        return true;

}

bool BarCodeDataMatrix::parseInput(const string &data)
{
    zero();

    int data_size = (sizeof(data)/sizeof(data[0]));

    int row = 0;
    int column = 0;
    bool store_value;

    for (int i = 0; i < data_size; i++) {
        if (data[i] == '1' || data[i] == '0') {

            if (data[i] == '1')
                store_value = true;
            else
                store_value = false;
            **m_data[row][column] = store_value;
            column++;
        } else if (data[i] == ' ') {
            continue;
        } else {
            return false;
        }

        if (column >= m_size) {
            row++;
            column = 0;
            if (row >= m_size) {
                return true;
            }
        }
    }
}

void BarCodeDataMatrix::exportToSVG(size_t scale, size_t offsetX, size_t offsetY, bool svgHeader) const
{
    int width = scale * m_size;

    if (svgHeader) {
        std::cout << CBarCode::XMLVersion << std::endl;
        std::cout << CBarCode::Doctype << std::endl;
        std::cout << CBarCode::SVGHeader << std::endl;
    }

    size_t current_offsetX = offsetX;
    size_t current_offsetY = offsetY;
    string color;

    std::cout << m_size;
    for (int row = 0; row < m_size; row++) {
        for (int column = 0; column < m_size; column++) {
            if (**m_data[row][column] == true)
                color = "black";
            else
                color = "white";

            std::cout << "<rect x=\""   <<  current_offsetX
                      << "\" y=\""      <<  current_offsetY
                      << "\" width=\""  <<  scale
                      << "\" height=\"" <<  scale
                      << "\" fill=\""   <<  color
                      << "\" />"
                      << std::endl;

            current_offsetX += scale;
        }
        current_offsetY += scale;
    }

    if (svgHeader) {
        std::cout << "</svg>" << std::endl;
    }
}

std::size_t BarCodeDataMatrix::size()
{
    return m_size;
}

