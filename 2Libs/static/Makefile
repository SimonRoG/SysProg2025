app = policyDB
src = ../../1PolicyDB/src
cpps = $(src)/Policy.cpp $(src)/PolicyDatabase.cpp
objects = Policy.o PolicyDatabase.o
main = $(src)/main.cpp
lib = policy
libfile = lib$(lib).a

$(app): $(main) $(libfile) $(cpps)
	g++ $(main) -L. -l$(lib) -o $(app)

all: $(objects) $(libfile) $(app)

run: $(app)
	./$(app)

clean:
	rm -f $(app)

%.o: $(src)/%.cpp
	g++ -c $< -o $@

$(libfile): $(objects)
	ar rcs $(libfile) $(objects)