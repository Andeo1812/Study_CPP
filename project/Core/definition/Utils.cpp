#include <iostream>
#include <vector>

#include "Utils.hpp"

void AnalysisCompress(std::vector <byte> input_data, std::vector <byte> &compressed, std::vector <byte> &expected_data) {
    std::cout << "Size before compress: " << input_data.size() << " bytes" << std::endl;
    std::cout << "After compress: " << compressed.size() << " bytes" << std::endl;

    std::cout << "Compression ratio - " << (double) compressed.size() / (double) input_data.size() << std::endl;

    if (input_data == expected_data) {
        std::cout << "SUCCESS" << std::endl;
    } else {
        std::cout << "FALSE" << std::endl;
    }
}
