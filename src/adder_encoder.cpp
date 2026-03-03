#include "adder_encoder.h"

#include "pblib/pb2cnf.h"
#include "pblib/pbconstraint.h"
#include "pblib/PBConfig.h"
#include <numeric>

namespace SINGLELADDERAMO
{

    AdderEncoder::AdderEncoder(ClauseContainer *clause_container, VarHandler *var_handler) : BaseEncoder(clause_container, var_handler)
    {
    }

    AdderEncoder::~AdderEncoder() {};

    void AdderEncoder::encode_and_solve_ladder_amo(int n, int w, int initCondLength, int initCond[])
    {
        PBConfig config = std::make_shared<PBConfigClass>();
        config->pb_encoder = PB_ENCODER::ADDER;
        PB2CNF pb2cnf(config);

        for (int i = 1; i <= n - w + 1; i++)
        {
            std::vector<int32_t> literals(w);
            std::vector<int64_t> weights(w);
            std::iota(literals.begin(), literals.end(), i);
            std::fill(weights.begin(), weights.end(), 1);

            std::vector<std::vector<int32_t>> clauses;

            int next_aux_var = pb2cnf.encodeLeq(weights, literals, 1, clauses, vh->get_new_var()) + 1;
        
            vh->set_next_to_assign(next_aux_var);
            for (const auto &clause : clauses)
                cc->add_clause(clause);
        }

        (void)initCondLength;
        (void)initCond;
    }
}
