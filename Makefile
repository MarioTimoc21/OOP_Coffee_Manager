CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = Main

SRC = src/Reports.cpp src/Events.cpp src/Orders.cpp src/Stock.cpp src/Product.cpp src/Menu.cpp src/Employees.cpp main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)