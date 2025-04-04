# Ladder AMO Encoder

This repository provides some SAT-based encodings for Ladder AMO constraints, including:
- BDD (Abío, Ignasi, et al. "A new look at BDDs for pseudo-Boolean constraints." Journal of Artificial Intelligence Research 45 (2012): 443-480.)
- Cardinality Network (Asín, Roberto, et al. "Cardinality networks: a theoretical and empirical study." Constraints 16 (2011): 195-221.)
- Duplex (Fazekas, Katalin, et al. "Duplex encoding of staircase at-most-one constraints for the antibandwidth problem." International Conference on Integration of Constraint Programming, Artificial Intelligence, and Operations Research. Cham: Springer International Publishing, 2020.)
- Naive (Pure pairwise encoding, including duplicated clauses.)
- Product (Chen, Jingchao. "A new SAT encoding of the at-most-one constraint." Proc. constraint modelling and reformulation (2010): 8.)
- Reduced (The optimized version of Pairwise encoding, where all duplicated clauses are terminated.)
- SCL (Truong, Hieu Xuan, Tuyen Van Kieu, and Khanh Van To. "Sequential Counter Encoding for Staircase At-Most-One Constraints.")
- Seq (Sinz, Carsten. "Towards an optimal CNF encoding of boolean cardinality constraints." International conference on principles and practice of constraint programming. Berlin, Heidelberg: Springer Berlin Heidelberg, 2005.)

Note that, BDD utilitizes the [pblib](https://pypi.org/project/pypblib/) library and Cardinality Network employs the [PySAT](https://pypi.org/project/pysat/) library.


Use `make clean && make` to clean build the `ladder_amo_enc` in the default `build` sub-directory (also can use `make` to simplifier the build process, but may cause some runtime errors). 

Main syntax: `./ladder_amo_enc <number_of_elements> [option_1, option_2, ...]`

Use `./ladder_amo_enc --help` to see all the avaiable options.

The architecture of this tool is constructed by:
- Input handler: Read the config and input.
- SAT solver: CaDiCaL version 1.2.1.
- Encoding handler: Create corresponding encoder based on the given configs, call the solver and export the output.
- Encoders: The encode strategies.
