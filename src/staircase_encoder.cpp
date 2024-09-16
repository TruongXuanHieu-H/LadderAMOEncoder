#include "staircase_encoder.h"

#include <iostream>
#include <assert.h>
#include <chrono>

namespace SINGLESTAIR
{
    StaircaseEncoder::StaircaseEncoder() {};

    StaircaseEncoder::~StaircaseEncoder()
    {
    }

    void StaircaseEncoder::set_n(int n)
    {
        this->n = n;
    }

    void StaircaseEncoder::encode_and_solve_stair()
    {
        int w_from, w_to;
        setup_bounds(w_from, w_to);
        encode_and_solve_stair_problem(w_from, w_to, 1, 10);
    }

    void StaircaseEncoder::setup_bounds(int &w_from, int &w_to)
    {
        lookup_bounds(w_from, w_to);

        if (overwrite_lb)
        {
            std::cout << "c LB " << w_from << " is overwritten with " << forced_lb << "." << std::endl;
            w_from = forced_lb;
        }
        if (overwrite_ub)
        {
            std::cout << "c UB " << w_to << " is overwritten with " << forced_ub << "." << std::endl;
            w_to = forced_ub;
        }
        if (w_from > w_to)
        {
            int tmp = w_from;
            w_from = w_to;
            w_to = tmp;
            std::cout << "c Flipped LB and UB to avoid LB > UB ";
            std::cout << "(LB = " << w_from << ", UB = " << w_to << ")." << std::endl;
        }

        assert((w_from <= w_to) && (w_from >= 1));
    }

    void StaircaseEncoder::lookup_bounds(int &lb, int &ub)
    {
        lb = 2;
        ub = n - 1;
    }

    void StaircaseEncoder::encode_and_solve_stair_problem(int start_w, int stop_w, int step, int prev_res)
    {
        for (int w = start_w; (w > 0 && w != stop_w); w += step)
        {
            bool error = encode_and_solve_stair_problem(w);
            if (error)
                break;
            if (SAT_res != prev_res)
                break; // reached UNSAT->SAT or SAT->UNSAT point
            prev_res = SAT_res;
        }
    }

    void StaircaseEncoder::setup_solving()
    {
        setup_cadical();

        vh = new VarHandler(1, n);

        // Do not split clauses, so split_clause is set to 0
        cc = new CadicalClauseContainer(vh, 0, solver);

        setup_encoder();
    }

    void StaircaseEncoder::cleanup_solving()
    {
        delete enc;
        delete cc;
        delete vh;
        delete solver;
    }

    void StaircaseEncoder::setup_cadical()
    {
        std::cout << "c Initializing CaDiCaL ";
        solver = new CaDiCaL::Solver;
        std::cout << "(version " << solver->version() << ")." << std::endl;
    }

    void StaircaseEncoder::setup_encoder()
    {
        switch (enc_choice)
        {
        case naive:
            break;
        case reduced:
            break;
        case seq:
            break;
        case BDD:
            break;
        case product:
            break;
        case duplex:
            break;
        case ladder:
            std::cout << "c Initializing a Ladder encoder with n = " << n << "." << std::endl;
            enc = new LadderEncoder(cc, vh);
            break;
        default:
            break;
        }
    }

    bool StaircaseEncoder::encode_and_solve_stair_problem(int w)
    {
        std::cout << "c Staircase problem with n = " << n << " and w = " << w << std::endl;
        if (n < 1)
        {
            std::cout << "c The input elements is too small, there is nothing to encode here." << std::endl;
            SAT_res = 0; // should break loop
            return 0;
        }
        if (w < 2)
        {
            std::cout << "c There is always at least 1 distance between any pair of elements. There is nothing to encode here." << std::endl;
            SAT_res = 10; // check solution can not be invoked
            return 0;
        }

        setup_solving();
        std::cout << "c Encoding starts with w = " << w << ":" << std::endl;

        auto t1 = std::chrono::high_resolution_clock::now();
        enc->encode_staircase(n, w);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto encode_duration = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count();

        std::cout << "c\tEncoding duration: " << encode_duration << "s" << std::endl;
        std::cout << "c\tNumber of clauses: " << cc->size() << std::endl;
        std::cout << "c\tNumber of irredundant clauses: " << solver->irredundant() << std::endl;
        std::cout << "c\tNumber of variables: " << vh->size() << std::endl;
        std::cout << "c SAT Solving starts:" << std::endl;

        t1 = std::chrono::high_resolution_clock::now();
        SAT_res = solver->solve();
        t2 = std::chrono::high_resolution_clock::now();
        auto solving_duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        std::cout << "c\tSolving duration: " << solving_duration << " ms" << std::endl;
        std::cout << "c\tAnswer: " << std::endl;
        if (SAT_res == 10)
        {
            std::cout << "s SAT (w = " << w << ")" << std::endl;
        }
        else if (SAT_res == 20)
            std::cout << "s UNSAT (w = " << w << ")" << std::endl;
        else
        {
            std::cout << "s Error at w = " << w << ", SAT result: " << SAT_res << std::endl;
            cleanup_solving();
            return 1;
        }

        cleanup_solving();

        std::cout << "c" << std::endl
                  << "c" << std::endl;
        return 0;
    }
}