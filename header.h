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

const int DIFFICULTY_TARGET = 3;

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

int randomize(int SET_BEGINNING, int SET_END) {
    random_device rd;
    mt19937 generate(rd());
    uniform_int_distribution<int> distribute(SET_BEGINNING, SET_END);

    return distribute(generate);
}

#endif