NAME := unit-test

# criterion directory
D_CRIT := $(wildcard $(shell brew --prefix)/Cellar/criterion/*)

D_SRC := ./
D_OBJ := ./obj
D_INC := ../include

SRC := vector/constructor.cpp
SRC += vector/push_back.cpp
SRC += vector/iterator.cpp
SRC += vector/assign.cpp

OBJ := $(addprefix $(D_OBJ)/, $(SRC:.cpp=.o))
OBJ_SUBDIR := $(addprefix $(D_OBJ)/, vector)

DEP := $(OBJ:.o=.d)

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
	./$(NAME) --jobs 1 --verbose=0

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(INC) -o $@ $(OBJ) $(LIB)

$(OBJ): | $(OBJ_SUBDIR)

$(OBJ_SUBDIR):
	@mkdir -p $@

$(D_OBJ)/%.o: $(D_SRC)/%.cpp
	$(CXX) $(CXXFLAGS) -MMD $(INC) -c $< -o $@

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

FLAG_FILE := compile_flags.txt
append_flags = $(foreach flag,$(1),$(shell echo "$(flag)" >> $(FLAG_FILE);))

.PHONY: $(FLAG_FILE)
$(FLAG_FILE):
	$(call append_flags,$(INC))
	$(call append_flags,$(CXXFLAGS))
	@echo "done"

-include $(DEP)
