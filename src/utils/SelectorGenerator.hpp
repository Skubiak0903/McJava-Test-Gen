#pragma once

#include "./random.hpp"
#include <string>
#include <unordered_map>
#include <vector>
#include <random>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <optional>

void initSelectorGenerator();

std::vector<std::string> randomEntitySelector(const bool multiple);
std::vector<std::string> randomPlayerSelector(const bool multiple);
std::vector<std::string> randomGameProfile();