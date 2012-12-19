#include "InputParser.h"

InputParser::InputParser(std::string inputFile)
{
	mInputFile.open(inputFile);
	mInputFile.unsetf(std::ios::skipws);
	iit = spirit::istream_iterator(mInputFile);
	endiit = spirit::istream_iterator();
	// Begin the parsing process and put the first "graph" into the
	// corresponding class attributes.
}

InputParser::~InputParser(void)
{
	mInputFile.close();
}

void InputParser::changeInputFile(std::string inputFile)
{
	mInputFile.close();
	mInputFile.open(inputFile);
	mInputFile.unsetf(std::ios::skipws);
	iit = spirit::istream_iterator(mInputFile);
	// Begin the parsing process and put the first "graph" into the
	// corresponding class attributes.
}

bool InputParser::parse_vertex(spirit::istream_iterator first, spirit::istream_iterator last, std::vector<int>& v)
{
	using qi::int_;
	using qi::phrase_parse;
	using qi::_1;
	using ascii::space;

	bool r = phrase_parse(first, last,

		//  Begin grammar - Integers list (one or more) separated by a dash.
		(
		int_ % '-'
		)
		,
		//  End grammar

		space, v);

	if (first != last) // fail if we did not get a full match
		return false;
	return r;
}

void InputParser::getParsedGraph(void)
{
	// TODO
}
