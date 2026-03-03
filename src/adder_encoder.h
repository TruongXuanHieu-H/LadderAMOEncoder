#ifndef ADDER_ENCODER_H
#define ADDER_ENCODER_H

#include "encoder.h"

namespace SINGLELADDERAMO
{
    typedef std::vector<int>::iterator vec_int_it;

    class AdderEncoder : public BaseEncoder
    {
    public:
        AdderEncoder(ClauseContainer *cc, VarHandler *vh);
        virtual ~AdderEncoder();

        virtual void encode_and_solve_ladder_amo(int n, int w, int initCondLength, int initCond[]) override;
    };

}

#endif
