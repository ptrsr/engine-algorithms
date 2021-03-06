#include <gtest/gtest.h>
#include <engine/glm.hpp>

#include <string>
#include <list>
#include <vector>

#define CONSOLE_RESET  "\033[0m"
#define CONSOLE_RED    "\033[1;31m"
#define CONSOLE_YELLOW "\033[1;33m"

#define MAX_LOG_PRECISION 5
#define TRIG_DIF 10e-6f

typedef glm::vec<2, unsigned> vec2i;

template <int cols, int rows, typename type>
std::string MatDifOut(glm::mat<cols, rows, type> mat, 
                      glm::mat<cols, rows, bool> faulty,
                      std::string consoleColor) 
{
	std::stringstream ts, ss;

	ts.precision(MAX_LOG_PRECISION);
	ss.precision(MAX_LOG_PRECISION);

	// for adding extra spacing for easier reading later on
	glm::vec<cols, unsigned> maxWidthPerCol = glm::vec<cols, unsigned>(0);
	glm::mat<cols, rows, unsigned> widthPerEntry = glm::mat<cols, rows, unsigned>(0);

	for (unsigned j = 0; j < cols; ++j) {
		for (unsigned i = 0; i < rows; ++i) {
			// put entry in temporary stream
			ts << mat[j][i];
			// count length
			unsigned count = ts.str().size();
			if (count > maxWidthPerCol[j]) {
				// maximum width of each column
				maxWidthPerCol[j] = count;
			}
			// set entry width
			widthPerEntry[j][i] = count; 

			// reset temporary stream
			ts.str("");
		}
	}
	for (unsigned i = 0; i < rows; ++i) {
		ss << "\n|";
		for (unsigned j = 0; j < cols; ++j) {
			if (j != 0) {
				ss << ", ";
			}
			if (faulty[j][i]) {
				ss << consoleColor << mat[j][i] << CONSOLE_RESET;
			} else {
				ss << mat[j][i];
			}
			// add extra spacing
			unsigned spaces = maxWidthPerCol[j] - widthPerEntry[j][i];
			for (unsigned i = 0; i < spaces; ++i) {
				ss << " ";
			}
		}
		ss << "|";
	}
	ss << "\n";
	return ss.str();
}

template <int cols, int rows, typename type>
::testing::AssertionResult CompareMats(glm::mat<cols, rows, type> expected,
                                          glm::mat<cols, rows, type> result,
                                          type maxDelta) 
{
	bool error = false;
	glm::mat<cols, rows, bool> faulty(false);
	for (unsigned j = 0; j < cols; ++j) {
		for (unsigned i = 0; i < rows; ++i) {
			if (std::abs(expected[j][i] - result[j][i]) > maxDelta) {
				faulty[j][i] = true;
				error = true;
			}
		}
	}
	if (error) {
		return ::testing::AssertionFailure() << "\nExpected:"
			       << MatDifOut(expected, faulty, CONSOLE_YELLOW) << "\nResult:"
			       << MatDifOut(result, faulty, CONSOLE_RED);
	}
	return ::testing::AssertionSuccess();
}
