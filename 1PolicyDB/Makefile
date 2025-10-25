app = policyDB
cpps = src/main.cpp src/Policy.cpp src/PolicyDatabase.cpp

$(app): $(cpps)
	g++ $(cpps) -o $(app)

all: $(app)

run: $(app)
	./$(app)

clean:
	rm -f $(app) test/testout.txt

test: $(app)
	./$(app) < test/testin.txt > test/testout.txt