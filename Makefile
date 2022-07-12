NAME := test-main

D_SRC := ./
D_OBJ := ./obj
D_INC := ./include

SRC := main.cpp

OBJ := $(addprefix $(D_OBJ)/, $(SRC:.cpp=.o))

DEP := $(OBJ:.o=.d)

INC := -I$(D_INC)

LIB :=

CXX := c++
CXXFLAGS := -std=c++98 -Wall -Wextra -Werror

ifeq ($(DEBUG), 1)
CXXFLAGS += -g -fsanitize=address
endif

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(INC) -o $@ $(OBJ) $(LIB)

$(OBJ): | $(D_OBJ)

$(D_OBJ):
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
