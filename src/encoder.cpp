#include "encoder.h"

namespace SINGLELADDERAMO
{
    BaseEncoder::BaseEncoder(ClauseContainer *clause_container, VarHandler *var_handler) : cc(clause_container), vh(var_handler) {};
    BaseEncoder::~BaseEncoder() {};

    void BaseEncoder::encode_ladder_amo(int n, int w)
    {
        encode_and_solve_ladder_amo(n, w, 0, {});
    };
}