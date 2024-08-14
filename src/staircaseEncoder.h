#ifndef STAIRCASE_ECODER_H
#define STAIRCASE_ECODER_H

#include "utils.h"
#include "clause_cont.h"
#include <map>

namespace SATABP
{
  class StaircaseEncoder
  {
  public:
    StaircaseEncoder(ClauseContainer *clause_container, VarHandler *var_handler);
    virtual ~StaircaseEncoder();

    void encode_and_solve_staircase(int n, int w, int initCondLength, int initCond[]);
    void encode_window(int window, int n, int w);
    void glue_window(int window, int n, int w);
    int get_aux_var(int first, int last);

    ClauseContainer *cc;
    VarHandler *vh;
    std::map<std::pair<int, int>, int> aux_vars;
  };
}

#endif
