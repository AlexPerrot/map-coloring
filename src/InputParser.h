#ifndef INPUTPARSER_H
#define INPUTPARSER_H

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/support_istream_iterator.hpp> // STL istream_iterator isn't forward-only so Qi won't work

#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
#include <vector>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace spirit = boost::spirit;

class InputParser
{
public:
	InputParser(std::string inputFile);

	~InputParser(void);

	void changeInputFile(std::string inputFile);
	void getParsedGraph(void); //  [12/19/2012 cbadiola] Change this method return type accordingly to our needs

private:
	std::vector<int> v;
	std::ifstream mInputFile;
	spirit::istream_iterator iit, endiit;
	// Add a container for the last parsed graph construction.

	bool parse_vertex(spirit::istream_iterator first, spirit::istream_iterator last, std::vector<int>& v);
};

#endif // !INPUTPARSER_H