##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

.PHONY: all clean fclean re tests_run vg cs core games graphicals run	\
		linter format

%.o: %.cpp
	@echo "Compiling $<"
	$(CC) $(CPPFLAGS) -c $< -o $@ -fPIC
	@echo "Generated $@ successfully"

%.so : %.cpp
	$(CC) $(CPPFLAGS) -shared -o $@ -fPIC $<

CC					=	g++

# Sources
SFML_GFX_LIB_SRC	=	src/graphic_libs/SFML.cpp	\
						src/log/Log.cpp				\

MAIN_SRC			=	src/Main.cpp

SRC					=	src/log/Log.cpp

TESTS_SRC			=	tests/dlloadingtests.cpp	\

TEST_LIBS_SRC		=	tests/bar.cpp				\
						tests/nocreate.cpp			\

# Object files
OBJ					=	$(SRC:.cpp=.o)

MAIN_OBJ			=	$(MAIN_SRC:.cpp=.o)

SFML_GFX_LIB_OBJ	=	$(SFML_GFX_LIB_SRC:.cpp=.o)

TEST_LIBS_OBJ		=	$(TEST_LIBS_SRC:.cpp=.so)

# Flags
INCLUDES			=	-I ./src -I ./ -I ./include

LIB_FLAGS			=	-lsfml-graphics -lsfml-window -lsfml-system	\
						-ldl										\

CPPFLAGS			+=	-std=c++20 -Wall -Wextra -Werror $(INCLUDES) -O2 -g	\
$(LIB_FLAGS) -fno-gnu-unique -fPIC

CPPTESTFLAGS		=	--coverage -lcriterion $(CPPFLAGS)

VALGRIND_LOG		=	valgrind.log

VALGRIND_FLAGS		=	--leak-check=full									\
						--show-leak-kinds=definite							\
						--track-origins=yes									\
						--errors-for-leak-kinds=definite					\
						--log-file="$(VALGRIND_LOG)"						\

CPPLINTFLAGS		=														\
    --repository=. 															\
	--filter=-legal/copyright,-build/c++17,+build/c++20,-runtime/references,$\
-build/include_subdir,-build/c++11											\
    --recursive

all: core games graphicals

core:	$(OBJ) $(MAIN_OBJ)
	@echo "Building arcade..."
	$(CC) -o arcade $(OBJ) $(MAIN_OBJ)

games:

graphicals: $(SFML_GFX_LIB_OBJ)
	@echo "Building SFML graphic library..."
	$(CC) $(CPPFLAGS) -shared -o ./lib/SFML.so $(SFML_GFX_LIB_OBJ)

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
	rm -f $(OBJ) $(MAIN_OBJ) $(SFML_GFX_LIB_OBJ) $(TEST_LIBS_OBJ)
	rm -f *.gcda
	rm -f *.gcno
	rm -f vgcore.*
	rm -f *.log
	rm -f ./lib/*.so

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

format: clean
	find . -type f \( -name "*.cpp" -o -name "*.hpp" \) ! -path "./tests/*"	\
	-exec clang-format -i {} +
