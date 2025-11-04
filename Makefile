CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude
TARGET = word_search

$(TARGET): src/main.cpp src/trie.cpp src/doc.cpp src/menu.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) $^

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run