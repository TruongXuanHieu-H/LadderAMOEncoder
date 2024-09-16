#ifndef ENCODER_H
#define ENCODER_H

#include "clause_cont.h"

namespace SINGLESTAIR
{
    class Encoder
    {
    public:
        Encoder(ClauseContainer *clause_container, VarHandler *var_handler);
        virtual ~Encoder();

        Encoder(Encoder const &) = delete;
        Encoder &operator=(Encoder const &) = delete;

        virtual void encode_and_solve_staircase(int n, int w, int initCondLength, int initCond[]) = 0;

        ClauseContainer *cc;
        VarHandler *vh;

        void encode_staircase(int n, int w);
    };
}

#endif