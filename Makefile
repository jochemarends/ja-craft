# the sole purpose of this Makefile is to simplify the building
# process of a Windows application inside WSL

CXX := g++.exe
C   := gcc.exe

CMAKE_CONFIG_FLAGS := -GNinja -DCMAKE_CXX_COMPILER=$(CXX) -DCMAKE_CXX_COMPILER_FORCED=True -DCMAKE_C_COMPILER=$(C) -DCMAKE_C_COMPILER_FORCED=True -Dglfw3_DIR=\"C:/Program Files (x86)/GLFW/lib/cmake/glfw3\"
BUILD_DIR := build
EXEC_NAME := ja-craft.exe

.PHONY: build
build:
	mkdir -p $(BUILD_DIR)
	cmd.exe /c "cd $(BUILD_DIR) && cmake $(CMAKE_CONFIG_FLAGS) .. && cmake --build ."

.PHONY: run
run:
	cmd.exe /c ja-craft.exe

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

