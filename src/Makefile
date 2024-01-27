CC = gcc
CFLAGS = -std=c++17 -Wall -Werror -Wextra -lstdc++ -lm
TEST_FLAGS= -lgtest -pthread -lgtest_main

UNAME:=$(shell uname -s)

MODEL_CALC:=Model/model_calculator.h
MODEL_CREDIT:=Model/model_credit.cc
TEST_CALC:=Tests/tests_calc.cc
TEST_CREDIT:=Tests/tests_credit.cc
DIRS:=Model/* View/* Controller/*

all: test install

install:
	mkdir -p build_calculator
	cd build_calculator && qmake .. && make
	cd build_calculator && rm `ls | grep -v "New_Calc"`
	mv build_calculator ~

run_calc:
	~/build_calculator/New_Calc

uninstall:
	rm -rf ~/build_calculator

dist: $(DIRS)
	tar -czf s21_smart_calc.tar ~/build_calculator

dvi:
	@-open Instruction/Instruction.html

test: Model/model_calculator.h Model/model_credit.h Tests/tests_calc.cc Tests/tests_credit.cc
	# @-rm *.gcda *.gcno
	@$(CC) $(TEST_CALC) --coverage -o tests_calc.out $(TEST_FLAGS) $(CFLAGS) -g
	@./tests_calc.out
	@$(CC) $(TEST_CREDIT) --coverage -o tests_credit.out $(TEST_FLAGS) $(CFLAGS) -g
	@./tests_credit.out


gcov_report: test
	# @rm tests.*.gc*
	@lcov --capture  --no-external --directory . --output-file coverage.info
	@genhtml coverage.info --output-directory report
	@open report/index.html


rebuild: clean all


formating:
	cp ../materials/linters/.clang-format ./
	clang-format -i  Controller/* Model/* Tests/* View/*
	rm .clang-format


check_style:
	cp ../materials/linters/.clang-format ./
	clang-format -n Controller/* Model/* Tests/* View/*
	rm .clang-format


clean:
	@-rm -rf report *.gcda *.gcno *.out *.info *.tar