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

std::string randomEntitySelector(const bool multiple);
std::string randomPlayerSelector(const bool multiple);
std::vector<std::string> randomEntitySelectors(const bool multiple);
std::vector<std::string> randomPlayerSelectors(const bool multiple);
std::vector<std::string> randomGameProfile();