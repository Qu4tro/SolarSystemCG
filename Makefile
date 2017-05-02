# Declaration of variables
ENG_SRC = src/engine
ENG_EXE = Engine
GEN_SRC = src/generator
GEN_EXE = Generator

all: engine generator 	

engine: $(ENG_SRC)
	make -C $(ENG_SRC) && mv $(ENG_SRC)/$(ENG_EXE) .

generator: $(GEN_SRC)
	make -C $(GEN_SRC) && mv $(GEN_SRC)/$(GEN_EXE) .

clean:
	rm -f $(GEN_EXE) $(ENG_EXE) $(GEN_SRC)/*.o $(ENG_SRC)/*.o
