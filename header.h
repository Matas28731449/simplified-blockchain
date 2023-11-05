#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include <ctime>

using std::cout;
using std::vector;
using std::string;
using std::getline;
using std::mt19937;
using std::ifstream;
using std::ofstream;
using std::to_string;
using std::stringstream;
using std::istringstream;
using std::random_device;
using std::chrono::seconds;
using std::chrono::system_clock;
using std::chrono::duration_cast;
using std::uniform_int_distribution;

const int DIFFICULTY_TARGET = 2;

string generateHash(string &str) {
    unsigned long hash = 5381;
    for(char c : str) {
        hash = ((hash << 5) + hash) + c;
    }

    stringstream hashStream;
    hashStream << std::hex << std::setfill('0');
    for(int i = 0; i < 32; i ++) {
        hashStream << std::setw(2) << ((hash >> (4 * (31 - i))) & 0xFF);
    }

    return hashStream.str();
}

uint32_t mixHash(uint32_t a, uint32_t b, uint32_t c) {
    uint32_t temp1 = b >> 6 | b << (32 - 6);
    uint32_t temp2 = b >> 11 | b << (32 - 11);
    uint32_t temp3 = b >> 25 | b << (32 - 25);
    uint32_t s1 = temp3 ^ temp2 ^ b;

    temp1 = a >> 2 | a << (32 - 2);
    temp2 = a >> 13 | a << (32 - 13);
    temp3 = a >> 22 | a << (32 - 22);
    uint32_t s0 = temp3 ^ temp2 ^ temp1;

    return a + s0 + b + s1 + c;
}

int randomize(int SET_BEGINNING, int SET_END) {
    random_device rd;
    mt19937 generate(rd());
    uniform_int_distribution<int> distribute(SET_BEGINNING, SET_END);

    return distribute(generate);
}

const uint32_t HASH_CODE[] = {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
    0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};

#endif