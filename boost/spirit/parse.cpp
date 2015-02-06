#include <boost/spirit/include/qi_parse.hpp>
#include <boost/spirit/include/qi_numeric.hpp>
#include <iostream>

using namespace std;

namespace qi = boost::spirit::qi;
int main() {
  std::string s("123");
  int result = 0;
  qi::parse(s.begin(), s.end(), qi::int_, result);
  cout << result << endl;
}
