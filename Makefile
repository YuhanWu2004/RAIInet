CXX = g++-11
CXXFLAGS = -std=c++20 -Wall -g -MMD -Werror=vla

# Explicitly define the source files in the correct order
ORDERED_SOURCES = \
	link.cc \
	cell.cc \
	subject.cc \
    ability.cc \
    firewall.cc \
    linkboost.cc \
    scan.cc \
    polarize.cc \
    download.cc \
    brutal.cc\
    protect.cc\
    trade.cc\
    player.cc \
	board.cc \
    textobserver.cc \
    window.cc \
    graphicalobserver.cc \
    main.cc

# Generate object and dependency files
OBJECTS = $(ORDERED_SOURCES:.cc=.o)
DEPENDS = $(OBJECTS:.o=.d)

EXEC = raiinet

# Rule to build the final executable
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC) -lX11

# Compile source files to object files
%.o: %.cc
	$(CXX) -c -o $@ $< $(CXXFLAGS)

# Include dependency files for incremental builds
-include $(DEPENDS)

# Clean up build artifacts
.PHONY: clean
clean:
	rm -f $(OBJECTS) $(DEPENDS) $(EXEC)
	rm -rf gcm.cache
