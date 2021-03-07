# compiler used
COMPILER = g++
# utility
RMDIR = rm -rdf
RM = rm -f

# flags para dependências
DEP_FLAGS = -M -MT $@ -MT $(BIN_PATH)/$(*F).O -MP -MF $@
# libs usadas
LIBS= -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm

# flags
FLAGS  = -std=c++11 -Wall -pedantic -Wextra -Wno-unused-parameter -Werror=init-self
DFLAGS = -ggdb -O0 -DDEBUG
RFLAGS = -O3 -mtune=native

# paths
INCLUDE_PATHS = -I$(INC_PATH) $(addprefix -I,$(SDL INC_PATH))

INC_PATH = include
SRC_PATH = src
BIN_PATH = bin
DEP_PATH = dep

# lista de arquivos com a mesmma extensão
CPP_FILES = $(WILDCARD $(SRC_PATH)/*.cpp)
INC_FILES = $(WILDCARD $(INC_PATH)/*.h)
FILE_NAMES = $(sort $(notdir $(CPP_FILES:.cpp=)) $(notdir $(INC_FILES:.h=)))
DEP_FILES = $(addprefix $(DEP_PATH)/,$(addsuffix .d,$(FILE_NAMES)))
OBJ_FILES = $(addprefix $(BIN_PATH)/,$(notdir $(CPP_FILES:.cpp=.o)))

# nome do exec
EXEC = JOGO

# OS: Windows
ifeq ($(OS),Windows_NT)
RMDIR = rd /s /q
RM = del /q
SDL_PATHS = C:/SDL2/x86_64-mingw32 C:/Tools/msys64/mingw64
SDL_INC_PATH += $(addsuffix /include,$(SDL_PATHS))
LINK_PATH = $(addprefix -L,$(addsuffix /lib,$(SDL_PATHS)))
FLAGS += -mwindows
DFLAGS += -mconsole
LIBS := -lmingw32 -lSDL2main $(LIBS)

EXEC := $(EXEC).exe
else

UNAME_S := $(shell uname -s)

# OS: Mac
ifeq ($(UNAME_S), Darwin)
LIBS = -lm -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_ttf
endif
endif

# regra geral
all: $(EXEC)

# gera o executavel
$(EXEC): $(OBJ_FILES)
	$(COMPILER) -o $@ $^ $(LINK_PATH) $(LIBS) $(FLAGS)


# gera os .o
$(BIN_PATH)/%.o: $(DEP_PATH)/%.d | folders
	$(COMPILER) $(INCLUDE_PATHS) $(addprefix $(SRC_PATH),$(notdir $(<:.d=.cpp))) -c $(FLAGS) -o $@

# gera os .d
$(DEP_PATH)/%.d: $(SRC_PATH)/%.cpp | folders
	$(COMPILER) $(INCLUDE_PATHS) $< $(DEP_FLAGS) $(FLAGS) 

# clean
clean:
	-$(RMDIR) $(DEP_PATH)
	-$(RMDIR) $(BIN_PATH)
	-$(RM) $(EXEC)

# release & debug
release: FLAGS += $(RFLAGS)
release: $(EXEC)
debug: FLAGS += $(DFLAGS)
debug: $(EXEC)

folders:
ifeq ($(OS), Windows_NT)
	@if NOT exist $(DEP_PATH) ( mkdir $(DEP_PATH) )
	@if NOT exist $(BIN_PATH) ( mkdir $(BIN_PATH) )
	@if NOT exist $(INC_PATH) ( mkdir $(INC_PATH) )
	@if NOT exist $(SRC_PATH) ( mkdir $(SRC_PATH) )
else
	@mkdir -p $(DEP_PATH) $(BIN_PATH) $(INC_PATH) $(SRC_PATH)
endif

# regra pra debug
print-% : ; @echo $* = $($*)

help:
ifeq ($(OS), Windows_NT)
	@echo.
endif
	@echo Available targets:
	@echo - release:  Builds the release version
	@echo - debug:    Builds the debug version
	@echo - clean:    Cleans generated files
	@echo - folders:  Generates project directories
	@echo - help:     Shows this help
ifeq ($(OS), Windows_NT)
	@echo.
endif

# extras
.PRECIOUS: $(DEP_FILES)
.PHONY: release debug clean folders help

.SECONDEXPANSION:
-include $$(DEP_FILES)