#include <vector>

void run(std::istream &input, std::ostream &output) {
    byte tmp;

    std::vector <byte> input_v;

    while (input >> std::noskipws >> tmp) {
        input_v.push_back(tmp);
    }

    if (input_v.empty()) {
        std::cout << "Null input" << std::endl;

        return;
    }

    std::vector <byte> compressed;

    CustomEncode(input_v, compressed);

    std::vector <byte> expected_data;

    CustomDecode(compressed, expected_data);

    AnalysisCompress(input_v, compressed, expected_data);
}

int main() {
    run(std::cin, std::cout);

    return EXIT_SUCCESS;
}