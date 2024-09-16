#ifndef DUPLEX_NSC_ENCODER_H
#define DUPLEX_NSC_ENCODER_H

#include "encoder.h"
#include <map>

namespace SINGLESTAIR
{
  class LadderEncoder : public Encoder
  {
  public:
    LadderEncoder(ClauseContainer *clause_container, VarHandler *var_handler);
    virtual ~LadderEncoder();

    virtual void encode_and_solve_staircase(int n, int w, int initCondLength, int initCond[]) override;
    void encode_window(int window, int n, int w);
    void glue_window(int window, int n, int w);
    int get_aux_var(int first, int last);

    std::map<std::pair<int, int>, int> aux_vars;
  };
}

#endif
