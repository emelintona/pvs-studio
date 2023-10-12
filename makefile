W = -c --all-warnings --extra-warnings -W
SRC=$(wildcard *.c)

test: $(SRC)
	g++ $^ $(W)
