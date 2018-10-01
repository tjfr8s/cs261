###
### @Author - Tyler Freitas
### @Date - 9/20/18
### @Description: # Project Name

#
PROJ = Assignment1
# Program Name
#
PROG = HeronsFormula
# Compiler
#
CXX = gcc
CXXFLAGS = -std=c99
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g
#CXXFLAGS += -O3
#LDFLAGS = -lboost_date_time #
LDFLAGS += -lm

# Valgrind Options
#
VOPT = --tool=memcheck
VOPT += --leak-check=full
VOPT += --show-leak-kinds=all
VOPT += --track-origins=yes

# The object files to be used in the program
#
OBJS = HeronsFormula.o CalculateArea.o

# The source files for the program
#
SRCS = HeronsFormula.c CalculateArea.c

# The header files for the program
#
HEADERS = CalculateArea.h

# Output binary
#
BIN = ${PROJ}.bin

# Compiling the object files using the compilers
#
HeronsFormula: ${OBJS} ${HEADERS}
	${CXX} ${LDFLAGS} ${OBJS} -o ${PROG} 

# Making the object files for the program 
#
${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c ${@:.o=.c}

# Debug the program
#
debug: ${PROG}
	@valgrind ${VOPT} ./${PROG}

${BIN}: ${OBJ} ${HEADERS}
	@echo "CC $@"
	@${CXX} ${CFLAGS} $^ -o $@


# Default Behavior:
# 	1. Remove everything to start from scratch
# 	2. Compile the binary
# 	3. Run it through valgrind for quicker debugging
#
default: clean ${BIN} debug

# Cleaning the object files and program made by the makefile
#
clean:
	rm *o *zip ${PROG}

# Make a zip file of all of the source files, header files and the makefile
#
zip:
	zip ${PROJ} .zip *.c *.hpp makefile
