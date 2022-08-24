#pragma once  //  NOLINT

#include "Node.hpp"

template<typename T = byte>
void AnalysisCompress(std::vector <T> input_data, std::vector <T> &compressed, std::vector <T> &expected_data);

#include "UtilsDefinition.hpp"
