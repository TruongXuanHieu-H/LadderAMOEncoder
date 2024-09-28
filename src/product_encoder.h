#ifndef PRODUCT_ENCODER_H
#define PRODUCT_ENCODER_H

#include "encoder.h"

namespace SINGLESTAIR
{
  typedef std::vector<int>::iterator vec_int_it;

  class ProductEncoder : public Encoder
  {
  public:
    ProductEncoder(ClauseContainer *cc, VarHandler *vh);
    virtual ~ProductEncoder();

    virtual void encode_and_solve_staircase(int n, int w, int initCondLength, int initCond[]) override;

  private:
    void encode_amo(vec_int_it it_begin, vec_int_it it_end);
  };

}

#endif
