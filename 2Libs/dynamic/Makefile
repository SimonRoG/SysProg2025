app = policyDB
src = ../../1PolicyDB/src
cpps = $(src)/Policy.cpp $(src)/PolicyDatabase.cpp
main = $(src)/main.cpp
lib = policy
libfile = lib$(lib).so

$(app): $(libfile)
	g++ $(main) -L. -l$(lib) -o $(app)

all: $(app)

run: $(app)
	LD_LIBRARY_PATH=. ./$(app)

clean:
	rm -f $(app) $(libfile)

$(libfile):
	g++ -fPIC -shared $(cpps) -o $(libfile)

update: $(libfile)