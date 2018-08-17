#  ______ _
# |  ____| |
# | |__  | | __ _  __ _ ___
# |  __| | |/ _` |/ _` / __|
# | |    | | (_| | (_| \__ \
# |_|    |_|\__,_|\__, |___/
#                  __/ |
#                 |___/

CXXFLAGS = -march=native -mtune=native -O3 -pipe -Wall -Wredundant-decls \
-Wcast-align -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum \
-Wswitch-default -Wextra -Werror -Winvalid-pch -Wredundant-decls \
-Wmissing-prototypes -Wformat=2 -Wmissing-format-attribute -Wformat-nonliteral \
-fPIC -g -fstack-protector -fvisibility=hidden \
-Wno-unused-function -Wno-unused-label -Wpointer-arith -Wreturn-type \
-Wsign-compare -Wmultichar -Wformat-nonliteral -Winit-self -Wuninitialized \
-Wno-deprecated -Wformat-security -Weffc++ -fsanitize=address -fPIE \
-fno-omit-frame-pointer -std=c++17

LDFLAG = $(CXXFLAGS) -lncurses

#  _____      _   _
# |  __ \    | | | |
# | |__) |_ _| |_| |__  ___
# |  ___/ _` | __| '_ \/ __|
# | |  | (_| | |_| | | \__ \
# |_|   \__,_|\__|_| |_|___/

ccsrc = $(wildcard *.cc)

obj = $(ccsrc:.cc=.o)

#   _____                      _ _
#  / ____|                    (_) |
# | |     ___  _ __ ___  _ __  _| | ___ _ __
# | |    / _ \| '_ ` _ \| '_ \| | |/ _ \ '__|
# | |___| (_) | | | | | | |_) | | |  __/ |
#  \_____\___/|_| |_| |_| .__/|_|_|\___|_|
#                       | |
#                       |_|

CXX=g++
EXEC = Toolbox_out
RM=rm

#  __  __
# |  \/  |
# | \  / | __ _  ___ _ __ ___  ___
# | |\/| |/ _` |/ __| '__/ _ \/ __|
# | |  | | (_| | (__| | | (_) \__ \
# |_|  |_|\__,_|\___|_|  \___/|___/

all: $(EXEC)

$(EXEC): $(obj)
	$(CXX) $(LDFLAG) -o $@ $^

%.o: %.c
	$(CXX) $(CXXFLAGS) -o $@ -c $<

.PHONY: clean

clean:
		rm -f $(obj) $(exe)
