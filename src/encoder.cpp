#include "encoder.h"

namespace SINGLESTAIR
{
    Encoder::Encoder(ClauseContainer *clause_container, VarHandler *var_handler) : cc(clause_container), vh(var_handler) {};
    Encoder::~Encoder() {};

    void Encoder::encode_staircase(int n, int w)
    {
        encode_and_solve_staircase(n, w, 0, {});
    };
}