#pragma once

#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <limits>
#include <sstream>
#include <iomanip>

// ------------------- szablon -------------------
template <typename T>
void shuffleVector(std::vector<T>& vec) {
    static std::mt19937 rng(std::random_device{}());
    std::shuffle(vec.begin(), vec.end(), rng);
}


// ------------------- zwykłe funkcje -------------------
int randomInt(int min = -1000, int max = 1000);
float randomFloat(float min = -1000.0f, float max = 1000.0f);
double randomDouble(double min = -1000.0, double max = 1000.0);
bool randomBool();
std::string randomString(size_t length = 8);
std::string randomResourceString(size_t length = 8);
std::string randomPrefixString(size_t length = 8);
std::string randomFakePlayer(size_t length = 8);
std::string randomMessage(size_t length = randomInt(2,7));
std::string randomBlockPos();
std::string randomChoice(const std::vector<std::string>& choices);
std::string randomText(const std::vector<char>& letters, size_t length = 8);
char randomTimeLetter();
std::string randomColor();
std::string randomHexColor();
std::string randomVec3();
std::string randomRotation();
std::string randomColumnPos();
std::string randomVec2();
std::string randomUUID();
std::string randomIntRange(int min = -1000, int max = 1000);
std::string randomFloatRange(float min = -1000.0f, float max = 1000.0f);

std::string randomAdvancement();

std::string randomEntityType();
std::string randomBlockType();
std::string randomItemType();
std::string randomParticleType();
std::string randomDataComponentType();
std::string randomStat();

std::string randomItemTag();
std::string randomBlockTag();

std::string randomNbtTag(size_t maxObjects = 5);
std::string randomNumberValue();
std::string randomStringValue();
std::string randomListValue();
std::string randomTextValue();