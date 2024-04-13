BUILD_TYPE=Debug
SOURCE_PATH=./
BUILD_PATH=./build
INSTALLATION_PATH=./build/Maze.app/Contents/MacOS
TEST_TARGET=tests
BUILD_TARGET=Maze

DIST_DIR:=archive
OPEN_COMMAND:=open

OS_NAME := $(shell uname -o 2>/dev/null || echo "Unknown")

ifeq ($(OS_NAME), GNU/Linux) # place here all differ variables
    OPEN_COMMAND := xdg-open
	INSTALLATION_PATH:=./build/
endif

init_cmake:
	cmake -S ${SOURCE_PATH} -B ${BUILD_PATH}

test: init_cmake
	cmake --build ${BUILD_PATH} --target ${TEST_TARGET} -j 4
	${BUILD_PATH}/${TEST_TARGET}

install: uninstall init_cmake
	cmake --build ${BUILD_PATH} --target ${BUILD_TARGET} -j 4

uninstall:
	@rm -rf build
	@rm -rf cmake-build-debug

run:
	${INSTALLATION_PATH}/${BUILD_TARGET}

style:
	@find .. -type f -name "*.cc" -exec clang-format -i -style=Google {} \;
	@find .. -type f -name "*.h" -exec clang-format -i -style=Google {} \;
	@echo "style apply is finished"
style_check:
	@find .. -type f -name "*.cc" -exec clang-format -n -style=Google {} \;
	@find .. -type f -name "*.h" -exec clang-format -n -style=Google {} \;
	@echo "style check is finished"

dvi:
	@$(OPEN_COMMAND) dvi-folder/README.html

dist: clean_dist
	mkdir -p ${DIST_DIR}
	cp -rf res ${DIST_DIR}/res
	cp -rf tests ${DIST_DIR}/tests
	cp -rf src ${DIST_DIR}/src
	cp -rf Makefile ${DIST_DIR}
	cp -rf CMakeLists.txt ${DIST_DIR}
	tar -czvf archive.tar.gz ${DIST_DIR}
	rm -rf ${DIST_DIR}

dist_unpack:
	tar -xzvf archive.tar.gz

clean: clean_project clean_static_lib clean_log clean_exec clean_obj clean_gcov clean_lcov clean_lcov_report clean_dist clean_qt_cmake_temp_files
	@echo "Clean finished"

clean_dist:
	@rm -rf archive
	@rm -rf archive.tar.gz

clean_project:

clean_after_building:
	@rm -rf ${OBJ_DIR}
clean_static_lib:
	@find . -type f -name "*.a" -exec rm {} \;
clean_log:
	@find . -type f -name "*.log" -exec rm {} \;
clean_exec:
	@find . -type f -name "*.out" -exec rm {} \;
clean_obj:
	@find . -type f -name "*.o" -exec rm {} \;
clean_gcov:
	@find . -type f -name "*.gcda" -exec rm {} \;
	@find . -type f -name "*.gcno" -exec rm {} \;
clean_lcov:
	@find . -type f -name "*.info" -exec rm {} \;
clean_lcov_report:
	@rm -rf report
clean_qt_cmake_temp_files:
	@rm -f *.txt.user