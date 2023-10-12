W = -c --all-warnings --extra-warnings -W
SRC=$(wildcard src/*.cc)

test: $(SRC)
	g++ $^ $(W)
