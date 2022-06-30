NAME := unit-test

D_CRIT := $(wildcard $(shell brew --prefix)/Cellar/criterion/*)

D_SRC := ./
D_OBJ := ./obj
D_INC := ../include

SRC := vector/constructor.cpp
SRC += vector/destructor.cpp

OBJ := $(addprefix $(D_OBJ)/, $(SRC:.cpp=.o))
INC := -I$(D_INC)
INC += -I$(D_CRIT)/include/

LIB := -L$(D_CRIT)/lib/ -lcriterion

CXX := c++
CXXFLAGS := -std=c++11

ifeq ($(DEBUG), 1)
CXXFLAGS += -g -fsanitize=address
endif

.PHONY: test
test: all
	./$(NAME)

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(INC) -o $@ $(OBJ) $(LIB)

$(OBJ): | $(dir $(OBJ))

$(dir $(OBJ)):
	@mkdir -p $(dir $(OBJ))

$(D_OBJ):
	@mkdir -p $(D_OBJ)

$(D_OBJ)/%.o: $(D_SRC)/%.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

.PHONY: clean
clean:
	$(RM) -r $(D_OBJ)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all

.PHONY: lint
lint:
	find $(D_SRC) $(D_INC) -name '*.cpp' -o -name '*.hpp' | xargs clang-format -i

.PHONY: compile_flags
compile_flags:
	$(foreach flag,$(INC),$(shell echo "$(flag)" >> compile_flags.txt;))
	@echo "done"
