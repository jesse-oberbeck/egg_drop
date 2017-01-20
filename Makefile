CPPFLAGS+=-Wall -Wextra -Wpedantic
CPPFLAGS+=-Wwrite-strings -Wstack-usage=1024 -Wfloat-equal
CPPFLAGS+=-Waggregate-return -Winline -g

CFLAGS+=-std=c11

LDLIBS+=-lm

BIN=drop
OBJ=egg.o
DEPS=egg.h

$(BIN) : $(OBJ)

.PHONY: debug profile clean

debug: CFLAGS+=-g
debug: $(BIN)

profile: CFLAGS+=-pg
profile: LDFLAGS+=-pg

clean:
	$(RM) $(BIN) $(DEPS)

run:
	./$(BIN)

val:
	valgrind -v ./$(BIN)
