CXX = clang++
CXXFLAGS = -Wall -Werror -Wextra -std=c++17 
#-fsanitize=address
TEST_FLAG = -lgtest 

PROJECT = s21_matrix_oop.cc
FUNCTIONS = s21_matrix_oop
TESTS = tests/*.cc

all: s21_matrix_oop.a

s21_matrix_oop.a: clean
	$(CXX) -c $(CXXFLAGS) $(PROJECT) 
	ar rc s21_matrix_oop.a *.o
	ranlib s21_matrix_oop.a

test: clean s21_matrix_oop.a
	$(CXX) $(CXXFLAGS) $(TEST_FLAG) $(TESTS)  s21_matrix_oop.a -fprofile-arcs -ftest-coverage -o test
	./test
	
# gcov_report: clean add_coverage test
# 	lcov --no-external  -t "s21_matrix_oop" -o s21_matrix_oop.info -c -d . 
# 	genhtml -o report s21_matrix_oop.info 
# 	open report/index.html

gcov_report: test
# @rm -rf report
# @for function in $(FUNCTIONS); do $(CXX) -c $$function.cc --coverage  -o $$function.o; done;
# @$(CXX) *.o tests/*.cc $(TEST_FLAG) $(LIBS) -fprofile-arcs -o test
# @./test
# @mkdir -p report
# @gcovr -r . --html --html-details --html-details-syntax-highlighting -o report/report.html
# @rm test.info *.gc*
	mkdir -p coverage-html
	gcovr --gcov-executable "/opt/goinfre/ardellen/homebrew/opt/llvm/bin/llvm-cov gcov" \
	--decisions \
	--html-theme github.dark-blue \
	--html-details coverage-html/index.html
	open coverage-html/index.html

add_coverage: 
	$(eval CXXFLAGS += -fno-elide-constructors --coverage)

style_check:
	cp ../materials/linters/.clang-format ./
	clang-format -style=Google -n $(PROJECT)
	clang-format -style=Google -n $(TESTS)

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.cc tests/*cc

leaks:
	@leaks -atExit -- ./test

clean:
	rm -rf *.o project/*.o s21_matrix_oop.a *.gcov *.gcno *.gcda *.info test report