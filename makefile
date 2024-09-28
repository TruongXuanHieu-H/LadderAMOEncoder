OBJDIR=build
OBJECTS= utils.o ladder_encoder.o bdd.o duplex_encoder.o product_encoder.o naive_encoder.o seq_encoder.o reduced_encoder.o encoder.o clause_cont.o cadical_clauses.o staircase_encoder.o
OBJS = $(patsubst %.o,$(OBJDIR)/%.o,$(OBJECTS))

SRCDIR=src

FLAGS= -Wall -Werror -Wextra -O3 -DNDEBUG
IGNORE_ASSERTVARS= -Wno-unused-but-set-variable
STANDARD= -std=c++11

CADICAL_INC=./cadical/
CADICAL_LIB_DIR=./cadical/
CADICAL_LIB=-lcadical

all : $(OBJDIR)/main.o
	g++ $(FLAGS) $(OBJDIR)/main.o $(OBJS) -L$(CADICAL_LIB_DIR) $(CADICAL_LIB) -o build/staircase_enc

$(OBJDIR)/main.o : main.cpp $(OBJS) $(SRCDIR)/staircase_encoder.h
	g++ $(FLAGS) $(STANDARD) -I$(CADICAL_INC) -c $< -o $@

$(OBJDIR)/staircase_encoder.o : $(SRCDIR)/staircase_encoder.cpp $(SRCDIR)/staircase_encoder.h $(SRCDIR)/ladder_encoder.h $(SRCDIR)/duplex_encoder.h $(SRCDIR)/product_encoder.h $(SRCDIR)/reduced_encoder.h $(SRCDIR)/naive_encoder.h $(SRCDIR)/seq_encoder.h $(SRCDIR)/utils.h $(SRCDIR)/clause_cont.h $(SRCDIR)/cadical_clauses.h
	g++ $(FLAGS) $(STANDARD) -I$(CADICAL_INC) -c $< -o $@

$(OBJDIR)/ladder_encoder.o : $(SRCDIR)/ladder_encoder.cpp $(SRCDIR)/ladder_encoder.h $(SRCDIR)/encoder.h
	g++ $(FLAGS) $(STANDARD) -c $< -o $@

$(OBJDIR)/duplex_encoder.o : $(SRCDIR)/duplex_encoder.cpp $(SRCDIR)/duplex_encoder.h $(SRCDIR)/encoder.h $(SRCDIR)/bdd.h
	g++ $(FLAGS) $(IGNORE_ASSERTVARS) $(STANDARD) -c $< -o $@

$(OBJDIR)/product_encoder.o : $(SRCDIR)/product_encoder.cpp $(SRCDIR)/product_encoder.h $(SRCDIR)/encoder.h
	g++ $(FLAGS) $(STANDARD) -c $< -o $@

$(OBJDIR)/reduced_encoder.o : $(SRCDIR)/reduced_encoder.cpp $(SRCDIR)/reduced_encoder.h $(SRCDIR)/encoder.h $(SRCDIR)/bdd.h
	g++ $(FLAGS) $(IGNORE_ASSERTVARS) $(STANDARD) -c $< -o $@

$(OBJDIR)/naive_encoder.o : $(SRCDIR)/naive_encoder.cpp $(SRCDIR)/naive_encoder.h $(SRCDIR)/encoder.h $(SRCDIR)/bdd.h
	g++ $(FLAGS) $(IGNORE_ASSERTVARS) $(STANDARD) -c $< -o $@

$(OBJDIR)/seq_encoder.o : $(SRCDIR)/seq_encoder.cpp $(SRCDIR)/seq_encoder.h $(SRCDIR)/encoder.h $(SRCDIR)/bdd.h
	g++ $(FLAGS) $(IGNORE_ASSERTVARS) $(STANDARD) -c $< -o $@

$(OBJDIR)/cadical_clauses.o : $(SRCDIR)/cadical_clauses.cpp $(SRCDIR)/cadical_clauses.h $(SRCDIR)/clause_cont.h
	g++ $(FLAGS) $(STANDARD) -I$(CADICAL_INC) -c $< -o $@

$(OBJDIR)/clause_cont.o : $(SRCDIR)/clause_cont.cpp $(SRCDIR)/clause_cont.h $(SRCDIR)/utils.h
	g++ $(FLAGS) $(STANDARD) -c $< -o $@

$(OBJDIR)/encoder.o : $(SRCDIR)/encoder.cpp $(SRCDIR)/encoder.h $(SRCDIR)/clause_cont.h
	g++ $(FLAGS) $(STANDARD) -c $< -o $@

$(OBJDIR)/utils.o : $(SRCDIR)/utils.cpp $(SRCDIR)/utils.h
	g++ $(FLAGS) $(STANDARD) -c $< -o $@

$(OBJDIR)/bdd.o : $(SRCDIR)/bdd.cpp $(SRCDIR)/bdd.h
	g++ $(FLAGS) $(IGNORE_ASSERTVARS) $(STANDARD) -c $< -o $@

#.PHONY : clean
clean:
	rm -f *.a $(OBJDIR)/*.o *~ *.out  $(OBJDIR)/staircase_enc

tar:
	tar cfv staircase_enc.tar main.cpp makefile $(SRCDIR)/*.cpp $(SRCDIR)/*.h cadical/*.a cadical/*.hpp
