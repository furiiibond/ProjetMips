## Change this variable
MYNAME=LAPIERRE_Jean-Camille_CARRERE_SCOTT
# and perhaps this one
SRCDOC=Devdoc.md
# testfiles are in TESTDIR and IGNORE = list of files to ignore when taring
TESTDIR = testfiles/
IGNORE = old_generate.c.old
## Do not change below please
BIN = emul-mips
PREFIX=MIPS3
CC = gcc
FLAGS = -Wall
C_FILES = $(wildcard *.c)
OBJ_FILES = $(C_FILES:.c=.o)

all: $(OBJ_FILES)
	$(CC) $(FLAGS) -o $(BIN) $^ -lm

%.o: %.c
	$(CC) $(FLAGS) -c $^

clean:
	rm -f *.o *~ $(BIN) *.hex *.s *.pdf

# a useful command to generate a pdf from a .md documentation file
doc : $(SRCDOC)
	pandoc -f markdown -t pdf  $(SRCDOC) -o $(basename $(SRCDOC)).pdf


# A useful command to deliver your project while keeping me sane
tar: clean
	dir=$$(basename $$PWD) && echo "compressing $(dir)" && cd .. && \
	tar cvfz "$(PREFIX)-$(MYNAME).tgz" \
	--transform="s,^$$dir,$(PREFIX)-$(MYNAME)," \
	--exclude="$(IGNORE)" "$$dir" --verbose --show-transformed-names

