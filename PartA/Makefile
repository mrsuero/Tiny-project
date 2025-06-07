# Tên trình biên dịch
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude

# Danh sách file nguồn
SRCS = main.cpp \
       source/linear.cpp \
       source/matrix.cpp \
       source/possym.cpp \
       source/vector.cpp

# Tên file thực thi
TARGET = main

# Luật build chính
all: $(TARGET)

# Luật biên dịch
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Luật dọn dẹp
clean:
	rm -f $(TARGET)
