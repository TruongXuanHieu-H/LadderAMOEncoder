#include "bdd_encoder.h"

#include <numeric>   //iota
#include <algorithm> //generate
#include <cmath>     //floor,ceil
#include <deque>
#include <assert.h>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
#include <regex>

namespace SINGLELADDERAMO
{

    BDDEncoder::BDDEncoder(ClauseContainer *clause_container, VarHandler *var_handler) : Encoder(clause_container, var_handler)
    {
    }

    BDDEncoder::~BDDEncoder() {};

    void BDDEncoder::encode_and_solve_ladder_amo(int n, int w, int initCondLength, int initCond[])
    {
        std::string command = "python3 bdd_ladder_amk.py " + std::to_string(n) + " " + std::to_string(w) + " 1";

        FILE *pipe = popen(command.c_str(), "r");
        assert(pipe);

        char buffer[1024];
        std::string result;

        while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
        {
            result += buffer;
        }

        pclose(pipe);

        std::stringstream ss(result);
        std::string temp = "";
        std::regex numberPattern(R"(-?\d+)");

        while (std::getline(ss, temp))
        {
            std::sregex_iterator it_line(temp.begin(), temp.end(), numberPattern);
            std::sregex_iterator end_line;
            std::vector<int> literals;

            while (it_line != end_line)
            {
                int literal = std::stoi(it_line->str());
                if (literal == 0)
                    break;
                literals.push_back(literal);
                it_line++;
            }
            cc->add_clause(literals);
        }

        (void)initCondLength;
        (void)initCond;
    }
}
