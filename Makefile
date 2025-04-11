##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

.PHONY: all clean fclean re tests_run vg cs core games graphicals run	\
		linter format
.PHONY: all clean fclean re tests_run vg cs core games graphicals run	\
		linter format

%.o: %.cpp
	@echo "Compiling $<"
	$(CC) $(CPPFLAGS) -c $< -o $@ -fPIC -fPIC
	@echo "Generated $@ successfully"

%.so : %.cpp
	$(CC) $(CPPFLAGS) -shared -o $@ -fPIC $<

CC					=	g++
CC					=	g++

NAME				=	arcade

# Sources
SFML_GFX_LIB_SRC	=	src/graphic_libs/SFML.cpp	\
						src/log/Log.cpp				\

SDL2_GFX_LIB_SRC	=	src/graphic_libs/SDL2.cpp	\
						wrapper/sdl2/SDL2.cpp		\
						wrapper/sdl2/SDL2_draw.cpp	\
						wrapper/sdl2/SDL2_event.cpp	\
						wrapper/sdl2/SDL2_sound.cpp	\
						wrapper/sdl2/SDL2_window.cpp\
						src/log/Log.cpp				\

MINESWEEPER_SRC	=	src/game_libs/minesweeper/Grid.cpp	\
					src/game_libs/minesweeper/MINESWEEPER.cpp	\
					src/log/Log.cpp				\

MAIN_SRC			=	src/Main.cpp
SFML_GFX_LIB_SRC	=	src/graphic_libs/SFML.cpp							\
						src/log/Log.cpp										\

SDL2_GFX_LIB_SRC	=	src/graphic_libs/SDL2.cpp							\
						wrapper/sdl2/SDL2.cpp								\
						wrapper/sdl2/SDL2_draw.cpp							\
						wrapper/sdl2/SDL2_event.cpp							\
						wrapper/sdl2/SDL2_sound.cpp							\
						wrapper/sdl2/SDL2_window.cpp						\
						src/log/Log.cpp										\

NCURSES_GFX_LIB_SRC	=	src/graphic_libs/NCURSES.cpp						\
						src/log/Log.cpp										\
						wrapper/ncurses/Ncurses.cpp							\
						wrapper/ncurses/NcursesDrawPrimitives.cpp			\
						wrapper/ncurses/NcursesInputHandling.cpp			\
						wrapper/ncurses/NcursesWindowManagement.cpp			\
						wrapper/ncurses/NcursesMouseHandling.cpp			\

MAIN_SRC			=	src/Main.cpp

SRC						=	src/log/Log.cpp										\

TESTS_SRC				=	tests/dlloadingtests.cpp							\

TEST_LIBS_SRC			=	tests/bar.cpp										\
						tests/foo.cpp										\
							tests/foo.cpp				\
						tests/nocreate.cpp									\

# Object files
OBJ						=	$(SRC:.cpp=.o)

MAIN_OBJ				=	$(MAIN_SRC:.cpp=.o)

SFML_GFX_LIB_OBJ	=	$(SFML_GFX_LIB_SRC:.cpp=.o)

SDL2_GFX_LIB_OBJ	=	$(SDL2_GFX_LIB_SRC:.cpp=.o)

MINESWEEPER_OBJ		=	$(MINESWEEPER_SRC:.cpp=.o)
SFML_GFX_LIB_OBJ	=	$(SFML_GFX_LIB_SRC:.cpp=.o)

SDL2_GFX_LIB_OBJ	=	$(SDL2_GFX_LIB_SRC:.cpp=.o)

NCURSES_GFX_LIB_OBJ	=	$(NCURSES_GFX_LIB_SRC:.cpp=.o)

TEST_LIBS_OBJ			=	$(TEST_LIBS_SRC:.cpp=.so)

# Flags
INCLUDES				=	-I ./src -I ./ -I ./include

LIB_FLAGS			=	-lsfml-graphics -lsfml-window -lsfml-system	\
						-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer	\
						-ldl										\

LIB_FLAGS			=	-lsfml-graphics -lsfml-window -lsfml-system	\
						-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer	\
						-ldl -lncurses								\

CPPFLAGS			+=	-std=c++20 -Wall -Wextra -Werror $(INCLUDES) -O2 -g	\
$(LIB_FLAGS) -fno-gnu-unique -fPIC
CPPFLAGS			+=	-std=c++20 -Wall -Wextra -Werror $(INCLUDES) -g	\
$(LIB_FLAGS) -fno-gnu-unique -fPIC

CPPTESTFLAGS			=	--coverage -lcriterion $(CPPFLAGS)

VALGRIND_LOG			=	valgrind.log

VALGRIND_FLAGS		=	--leak-check=full									\
						--show-leak-kinds=definite							\
						--track-origins=yes									\
						--errors-for-leak-kinds=definite					\
						--log-file="$(VALGRIND_LOG)"						\
VALGRIND_FLAGS		=	--leak-check=full									\
						--show-leak-kinds=definite							\
						--track-origins=yes									\
						--errors-for-leak-kinds=definite					\
						--log-file="$(VALGRIND_LOG)"						\

CPPLINTFLAGS		=														\
CPPLINTFLAGS		=														\
    --repository=. 															\
	--filter=-legal/copyright,-build/c++17,+build/c++20,-runtime/references,$\
-build/include_subdir,-build/c++11											\
    --recursive

all: core games graphicals

core:	$(OBJ) $(MAIN_OBJ)
	@echo "Building arcade..."
	$(CC) -o arcade $(OBJ) $(MAIN_OBJ)

games: $(MINESWEEPER_OBJ)
	@echo "Building Minesweeper..."
	$(CC) $(CPPFLAGS) -shared -o ./lib/MINESWEEPER.so $(MINESWEEPER_OBJ)

graphicals: $(SFML_GFX_LIB_OBJ) $(SDL2_GFX_LIB_OBJ)
	@echo "Building SFML graphic library..."
	$(CC) $(CPPFLAGS) -shared -o ./lib/SFML.so $(SFML_GFX_LIB_OBJ)
	@echo "Building SDL2 graphic library..."
	$(CC) $(CPPFLAGS) -shared -o ./lib/SDL2.so $(SDL2_GFX_LIB_OBJ)
all: core games graphicals

core:	$(OBJ) $(MAIN_OBJ)
	@echo "Building arcade..."
	$(CC) -o arcade $(OBJ) $(MAIN_OBJ)

games:

graphicals: $(SFML_GFX_LIB_OBJ) $(SDL2_GFX_LIB_OBJ) $(NCURSES_GFX_LIB_OBJ)
	@echo "Building SFML graphic library..."
	$(CC) $(CPPFLAGS) -shared -o ./lib/arcade_sfml.so $(SFML_GFX_LIB_OBJ)
	@echo "Building SDL2 graphic library..."
	$(CC) $(CPPFLAGS) -shared -o ./lib/arcade_sdl2.so $(SDL2_GFX_LIB_OBJ)
	@echo "Building NCURSES graphic library..."
	$(CC) $(CPPFLAGS) -shared -o ./lib/arcade_ncurses.so $(NCURSES_GFX_LIB_OBJ)

run: re
	@echo "Running $(NAME)..."
	@echo "-----------------------------------"
	./$(NAME)

vg: $(NAME)
	@echo "Running Valgrind..."
	valgrind $(VALGRIND_FLAGS) ./arcade
	cat $(VALGRIND_LOG)

tests_run:	$(TEST_LIBS_OBJ)
	@echo "Running tests..."
	$(CC) -o unit_tests $(SRC) $(TESTS_SRC) $(CPPTESTFLAGS)
	./unit_tests
	@gcovr --exclude tests/
	@gcovr -e tests --branch

clean:
	@echo "Cleaning up..."
	rm -f $(OBJ) $(MAIN_OBJ) $(TEST_LIBS_OBJ)
	rm -f $(SFML_GFX_LIB_OBJ)
	rm -f $(SDL2_GFX_LIB_OBJ)
	rm -f $(MINESWEEPER_OBJ)
	rm -f $(OBJ) $(MAIN_OBJ) $(TEST_LIBS_OBJ)
	rm -f $(SFML_GFX_LIB_OBJ)
	rm -f $(SDL2_GFX_LIB_OBJ)
	rm -f $(NCURSES_GFX_LIB_OBJ)
	rm -f ./lib/arcade_sfml.so
	rm -f ./lib/arcade_sdl2.so
	rm -f ./lib/arcade_ncurses.so
	rm -f *.gcda
	rm -f *.gcno
	rm -f vgcore.*
	rm -f *.log
	rm -f ./lib/*.so
## rm -f ./lib/*.so

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
