app = policyDB
src = ../../1PolicyDB/src
cpps = $(src)/Policy.cpp $(src)/PolicyDatabase.cpp
objects = Policy.o PolicyDatabase.o
main = $(src)/main.cpp
lib = policy
libfile = lib$(lib).a

$(app): $(objects) $(libfile)
	g++ $(main) -L. -l$(lib) -o $(app)

all: $(app)

run: $(app)
	./$(app)

clean:
	rm -f $(app) $(objects) $(libfile)

%.o: $(src)/%.cpp
	g++ -c $< -o $@

$(libfile): $(objects)
	ar rcs $(libfile) $(objects)