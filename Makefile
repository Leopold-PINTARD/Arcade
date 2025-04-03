##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

.PHONY: all clean fclean re tests_run vg cs

CC				=	g++

%.o: %.cpp
	@echo "Compiling $<"
	$(CC) $(CPPFLAGS) -c $< -o $@
	@echo "Generated $@ successfully"

%.so : %.cpp
	$(CC) $(CPPFLAGS) -shared -o $@ -fPIC $<

NAME			=	arcade

LIB_SRC			=

MAIN_SRC		=	src/Main.cpp

SRC				=

TESTS_SRC		=	tests/dlloadingtests.cpp	\

TEST_LIBS_SRC	=	tests/bar.cpp				\
					tests/nocreate.cpp			\

OBJ				=	$(SRC:.cpp=.o)

MAIN_OBJ		=	$(MAIN_SRC:.cpp=.o)

LIB_OBJ			=	$(LIB_SRC:.cpp=.so)

TEST_LIBS_OBJ	=	$(TEST_LIBS_SRC:.cpp=.so)

INCLUDES		=	-I ./src -I ./

CPPFLAGS		+=	-std=c++20 -Wall -Wextra -Werror $(INCLUDES) -O2 -g

CPPTESTFLAGS	=	--coverage -lcriterion $(CPPFLAGS)

VALGRIND_LOG	=	valgrind.log

VALGRIND_FLAGS	=	--leak-check=full					\
					--show-leak-kinds=definite			\
					--track-origins=yes					\
					--errors-for-leak-kinds=definite	\
					--log-file="$(VALGRIND_LOG)"		\

CPPLINTFLAGS	=															\
    --repository=. 															\
    --filter=-legal/copyright,-build/c++17,+build/c++20,-runtime/references	\
    --recursive

all: $(NAME)

$(NAME):	$(LIB_OBJ) $(OBJ) $(MAIN_OBJ)
	@echo "Building $(NAME)..."
	$(CC) -o $(NAME) $(OBJ) $(MAIN_OBJ)

run: re
	@echo "Running $(NAME)..."
	@echo "-----------------------------------"
	./$(NAME)

vg: $(NAME)
	@echo "Running Valgrind..."
	valgrind $(VALGRIND_FLAGS) ./$(NAME) 4242 tests
	cat $(VALGRIND_LOG)

tests_run:	$(TEST_LIBS_OBJ)
	@echo "Running tests..."
	$(CC) -o unit_tests $(SRC) $(TESTS_SRC) $(CPPTESTFLAGS)
	./unit_tests
	@gcovr --exclude tests/
	@gcovr -e tests --branch

clean:
	@echo "Cleaning up..."
	rm -f $(OBJ) $(MAIN_OBJ) $(LIB_OBJ) $(TEST_LIBS_OBJ)
	rm -f *.gcda
	rm -f *.gcno
	rm -f vgcore.*
	rm -f *.log

fclean: clean
	@echo "Removing binaries..."
	rm -f $(NAME)
	rm -f unit_tests

re: fclean all

cs:	clean
	coding-style . .
	cat coding-style-reports.log
	rm -f coding-style-reports.log

linter: clean
	cpplint $(CPPLINTFLAGS) ./src ./include
