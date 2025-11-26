# ЛАБОРАТОРНА РОБОТА 2

## Створення статичних і динамічних бібліотек для POSIX сумісних (сертифікованих) операційних систем

**Виконав:** Семен Прохода ІП-з31

### Завдання до роботи

**Варіант 5:** Інформаційна система Страхової компанії.

1.  Створити два репозіторія:
    -   з статичною бібліотекою
    -   з динамічною бібліотекою
2.  Створити Makefile відповідно

### Лістинг програми

[**_GitHub_**](https://github.com/SimonRoG/SysProg2025/blob/main/2Libs/readme.md)

#### Створення статичних бібліотек: [`satic/Makefile`](static/Makefile)

```make
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
```

-   `make all` - для побудови програми 
-   `make run` - для запуску програми
-   `make clean` - для прибиряння

#### Створення динамічних бібліотек: [`dynamic/Makefile`](dynamic/Makefile)

```make
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
```

-   `make all` - для побудови програми 
-   `make run` - для запуску програми (рекомендованно)
-   `make clean` - для прибиряння
-   `make update` - для оновлення бібліотеки

### Висновок

У ході виконання лабораторної роботи було створено статичні та динамічні бібліотеки. Також було створено Makefile-и для автоматизації процесу побудови бібліотек, лінкування програм з бібліотеками та оновлення бібліотек.