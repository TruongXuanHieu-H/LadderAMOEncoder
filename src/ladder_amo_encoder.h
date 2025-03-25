#ifndef LADDER_AMO_H
#define LADDER_AMO_H

#include "utils.h"

#include "clause_cont.h"
#include "cadical_clauses.h"
#include "scl_encoder.h"
#include "duplex_encoder.h"
#include "product_encoder.h"
#include "reduced_encoder.h"
#include "naive_encoder.h"
#include "seq_encoder.h"
#include "card_encoder.h"
#include "bdd_encoder.h"

namespace SINGLELADDERAMO
{
    enum EncodeType
    {
        naive,
        reduced,
        seq,
        BDD,
        product,
        duplex,
        scl,
        card,
    };

    const std::unordered_map<EncodeType, std::string> encode_type_map = {
        {naive, "naive"},
        {reduced, "reduced"},
        {seq, "seq"},
        {BDD, "BDD"},
        {product, "product"},
        {duplex, "duplex"},
        {scl, "scl"},
        {card, "card"},
    };

    class LadderAMOEncoder
    {
    public:
        LadderAMOEncoder();
        virtual ~LadderAMOEncoder();

        EncodeType enc_choice = scl;

        bool verbose = true;
        bool check_solution = true;

        bool force_phase = false;
        std::string sat_configuration = "sat";

        int split_limit = 0;

        bool overwrite_lb = false;
        bool overwrite_ub = false;
        int forced_lb = 0;
        int forced_ub = 0;

        void set_n(int n);
        void encode_and_solve_ladder_amo();

    protected:
        int n;
        VarHandler *vh;
        Encoder *enc;
        ClauseContainer *cc;
        CaDiCaL::Solver *solver;

        int SAT_res = 0;

        void encode_and_solve_ladder_amo_problem(int start_w, int stop_w, int step, int prev_res);
        bool encode_and_solve_ladder_amo_problem(int w);

        void setup_solving();
        void cleanup_solving();

        void setup_cadical();
        void setup_encoder();

        void setup_bounds(int &w_from, int &w_to);
        void lookup_bounds(int &lb, int &ub);

        bool calculate_sat_solution(int w);
    };
}

#endif