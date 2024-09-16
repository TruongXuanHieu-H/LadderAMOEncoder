#include "ladder_encoder.h"
#include <iostream>
#include <math.h>
#include "utils.h"

namespace SINGLESTAIR
{

    LadderEncoder::LadderEncoder(ClauseContainer *clause_container, VarHandler *var_handler) : Encoder(clause_container, var_handler)
    {
    }

    LadderEncoder::~LadderEncoder() {};

    bool is_debug_mode = false;

    int LadderEncoder::get_aux_var(int first, int last)
    {

        auto pair = aux_vars.find({first, last});

        if (pair != aux_vars.end())
            return pair->second;

        if (first == last)
            return first;

        int new_aux_var = vh->get_new_var();
        aux_vars.insert({{first, last}, new_aux_var});
        return new_aux_var;
    }

    void LadderEncoder::encode_and_solve_staircase(int n, int w, int initCondLength, int initCond[])
    {
        (void)initCondLength;
        (void)initCond;

        for (int gw = 0; gw < ceil((float)n / w); gw++)
        {
            encode_window(gw, n, w);
        }

        for (int gw = 0; gw < ceil((float)n / w) - 1; gw++)
        {
            glue_window(gw, n, w);
        }

        if (is_debug_mode)
            std::cout << "\nPrint dimacs:\n";
        if (is_debug_mode)
            cc->print_dimacs();
        if (is_debug_mode)
            std::cout << "\nStaircase visualization:\n";
        for (int l = 1; l <= (int)n - w + 1; l++)
        {
            for (int i = 0; i < l - 1; i++)
            {
                if (is_debug_mode)
                    std::cout << "\t";
            }
            for (int ll = l; ll <= l + w - 1; ll++)
            {
                if (is_debug_mode)
                    std::cout << ll;
                if (ll < l + w - 1)
                {
                    if (is_debug_mode)
                        std::cout << " +\t";
                }
                else
                {
                    if (is_debug_mode)
                        std::cout << "\t<= 1\n";
                }
            }
        }
    }

    /*
     * Encode each window separately.
     * The first window only has lower part.
     * The last window only has upper part.
     * Other windows have both upper part and lower part.
     *
     * window: index of window (0, 1, 2,...)
     * n : number of variables
     * w : width of window
     */
    void LadderEncoder::encode_window(int window, int n, int w)
    {
        if (window == 0)
        {
            // Encode the first window, which only have lower part
            int lastVar = window * (int)w + w;

            for (int i = w - 1; i >= 1; i--)
            {
                int var = window * (int)w + i;
                cc->add_clause({-var, get_aux_var(var, lastVar)});
            }

            for (int i = w; i >= 2; i--)
            {
                int var = window * (int)w + i;
                cc->add_clause({-get_aux_var(var, lastVar), get_aux_var(var - 1, lastVar)});
            }

            for (int i = 1; i < (int)w; i++)
            {
                int var = window * (int)w + i;
                int main = get_aux_var(var, lastVar);
                int sub = get_aux_var(var + 1, lastVar);
                cc->add_clause({var, sub, -main});
            }

            for (int i = 1; i < (int)w; i++)
            {
                int var = window * (int)w + i;
                cc->add_clause({-var, -get_aux_var(var + 1, lastVar)});
            }
        }
        else if (window == ceil((float)n / w) - 1)
        {
            // Encode the last window, which only have upper part and may have width lower than w
            int firstVar = window * (int)w + 1;

            if ((window + 1) * w > n)
            {
                int real_w = n % w; // width < w
                // Upper part
                for (int i = 2; i <= real_w; i++)
                {
                    int reverse_var = window * (int)w + i;
                    cc->add_clause({-reverse_var, get_aux_var(firstVar, reverse_var)});
                }

                for (int i = real_w - 1; i > 0; i--)
                {
                    int reverse_var = window * (int)w + real_w - i;
                    cc->add_clause({-get_aux_var(firstVar, reverse_var), get_aux_var(firstVar, reverse_var + 1)});
                }

                for (int i = 0; i < (int)real_w - 1; i++)
                {
                    int var = window * (int)w + real_w - i;
                    int main = get_aux_var(firstVar, var);
                    int sub = get_aux_var(firstVar, var - 1);
                    cc->add_clause({sub, var, -main});
                }

                for (int i = real_w; i > 1; i--)
                {
                    int reverse_var = window * (int)w + i;
                    cc->add_clause({-reverse_var, -get_aux_var(firstVar, reverse_var - 1)});
                }
            }
            else
            {
                // Upper part
                for (int i = 2; i <= (int)w; i++)
                {
                    int reverse_var = window * (int)w + i;
                    cc->add_clause({-reverse_var, get_aux_var(firstVar, reverse_var)});
                }

                for (int i = w - 1; i >= 1; i--)
                {
                    int reverse_var = window * (int)w + w - i;
                    cc->add_clause({-get_aux_var(firstVar, reverse_var), get_aux_var(firstVar, reverse_var + 1)});
                }

                for (int i = 0; i < (int)w - 1; i++)
                {
                    int var = window * (int)w + w - i;
                    int main = get_aux_var(firstVar, var);
                    int sub = get_aux_var(firstVar, var - 1);
                    cc->add_clause({sub, var, -main});
                }

                for (int i = (int)w; i > 1; i--)
                {
                    int reverse_var = window * (int)w + i;
                    cc->add_clause({-reverse_var, -get_aux_var(firstVar, reverse_var - 1)});
                }
            }
        }
        else
        {
            // Encode the middle windows, which have both upper and lower path, and always have width w

            // Upper part
            int firstVar = window * (int)w + 1;
            for (int i = 2; i <= (int)w; i++)
            {
                int reverse_var = window * (int)w + i;
                cc->add_clause({-reverse_var, get_aux_var(firstVar, reverse_var)});
            }

            for (int i = w - 1; i >= 1; i--)
            {
                int reverse_var = window * (int)w + w - i;
                cc->add_clause({-get_aux_var(firstVar, reverse_var), get_aux_var(firstVar, reverse_var + 1)});
            }

            for (int i = 0; i < (int)w - 1; i++)
            {
                int var = window * (int)w + w - i;
                int main = get_aux_var(firstVar, var);
                int sub = get_aux_var(firstVar, var - 1);
                cc->add_clause({sub, var, -main});
            }

            for (int i = (int)w; i > 1; i--)
            {
                int reverse_var = window * (int)w + i;
                cc->add_clause({-reverse_var, -get_aux_var(firstVar, reverse_var - 1)});
            }

            // Lower part
            int lastVar = window * (int)w + w;
            for (int i = w - 1; i >= 1; i--)
            {
                int var = window * (int)w + i;
                cc->add_clause({-var, get_aux_var(var, lastVar)});
            }

            for (int i = w; i >= 2; i--)
            {
                int var = window * (int)w + i;
                cc->add_clause({-get_aux_var(var, lastVar), get_aux_var(var - 1, lastVar)});
            }

            for (int i = 1; i < (int)w; i++)
            {
                int var = window * (int)w + i;
                int main = get_aux_var(var, lastVar);
                int sub = get_aux_var(var + 1, lastVar);
                cc->add_clause({var, sub, -main});
            }

            // Can be disable
            // for (int i = 1; i < (int)w; i++)
            // {
            //     int var = window * (int)w + i;
            //     cc->add_clause({-var, -GetEncodedAuxVar(auxStartVarLP + var + 1)});
            // }
        }
    }

    /*
     * Glue adjacent windows with each other.
     * Using lower part of the previous window and upper part of the next window
     * as anchor points to glue.
     *
     *
     * window: index of window (0, 1, 2,...)
     * n : number of variables
     * w : width of window
     */
    void LadderEncoder::glue_window(int window, int n, int w)
    {
        /*  The stair look like this:
         *      Window 1        Window 2        Window 3        Window 4
         *      1   2   3   |               |               |
         *          2   3   |   4           |               |
         *              3   |   4   5       |               |
         *                  |   4   5   6   |               |
         *                  |       5   6   |   7           |
         *                  |           6   |   7   8       |
         *                  |               |   7   8   9   |
         *                  |               |       8   9   |   10
         *                  |               |           9   |   10  11
         *
         *
         */
        if ((window + 2) * w > n)
        {
            int real_w = n % w;
            for (int i = 1; i <= real_w; i++)
            {
                int first_reverse_var = (window + 1) * (int)w + 1;
                int last_var = window * (int)w + w;

                int reverse_var = (window + 1) * (int)w + i;
                int var = window * (int)w + i + 1;

                cc->add_clause({-get_aux_var(var, last_var), -get_aux_var(first_reverse_var, reverse_var)});
            }
        }
        else
        {
            for (int i = 1; i < (int)w; i++)
            {
                int first_reverse_var = (window + 1) * (int)w + 1;
                int last_var = window * (int)w + w;

                int reverse_var = (window + 1) * (int)w + i;
                int var = window * (int)w + i + 1;

                cc->add_clause({-get_aux_var(var, last_var), -get_aux_var(first_reverse_var, reverse_var)});
            }
        }
    }
}
