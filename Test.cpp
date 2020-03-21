#include <cassert>
#include <iostream>

#include "Ops.h"

void test_is_blank()
{
  assert(is_blank(""));
  assert(is_blank(" "));
  assert(is_blank("\n"));
  assert(is_blank("\n\r"));
  assert(is_blank("\t"));
  assert(is_blank("    \n     \t   "));

  assert(!is_blank("Hello"));
}

void test_starts_with()
{
  assert((starts_with<char>("Hello world", "He")));
  assert((starts_with<char>("Hello world", "H")));
  assert((starts_with<char>("Hello world", "Hello ")));
  assert((starts_with<char>("Hello world", "")));
  assert((starts_with<char>("Hello world", "Hello world")));

  assert((!starts_with<char>("Hello world", "Her")));
  assert((!starts_with<char>("Hello world", "world")));
}

void test_ends_with()
{
  assert((ends_with<char>("Hello world", "rld")));
  assert((ends_with<char>("Hello world", "d")));
  assert((ends_with<char>("Hello world", " world")));
  assert((ends_with<char>("Hello world", "")));
  assert((ends_with<char>("Hello world", "Hello world")));

  assert((!ends_with<char>("Hello world", "rad")));
  assert((!ends_with<char>("Hello world", "Hello")));
}

void test_trim_start()
{
  assert(trim_start("  hello") == "hello");
  assert(trim_start("hello") == "hello");
  assert(trim_start("\thello") == "hello");
  assert(trim_start("\nhello") == "hello");
  assert(trim_start("\rhello") == "hello");
  assert(trim_start("\r\nhello") == "hello");

  assert(trim_start("") == "");
  assert(trim_start("\n\r") == "");
  assert(trim_start("\t") == "");
}

void test_trim_end()
{
  assert(trim_end("hello  ") == "hello");
  assert(trim_end("hello") == "hello");
  assert(trim_end("hello\t") == "hello");
  assert(trim_end("hello\n") == "hello");
  assert(trim_end("hello\r") == "hello");
  assert(trim_end("hello\r\n") == "hello");

  assert(trim_end("") == "");
  assert(trim_end("\n\r") == "");
  assert(trim_end("\t") == "");
}

void test_trim()
{
  assert(trim("  hello  ") == "hello");
  assert(trim("hello") == "hello");
  assert(trim("hello\t") == "hello");
  assert(trim(" hello\n") == "hello");
  assert(trim("hello\r ") == "hello");
  assert(trim("  hello\r\n") == "hello");

  assert(trim("") == "");
  assert(trim("\n\r") == "");
  assert(trim("\t") == "");
}

void test_join()
{
  auto samples = std::vector<std::string_view>{"Nice", "to", "see", "you"};
  auto joined = string_join(samples.cbegin(), samples.cend(), ' ');
  assert(joined.length() == 15);
  assert(joined == "Nice to see you");
}

void test_split()
{
  std::string_view sample = "How can I help you";
  auto result = string_split(sample.cbegin(), sample.cend(), ' ');
  assert(result.size() == 5);
  assert(result[0] == "How");
  assert(result[1] == "can");
  assert(result[2] == "I");
  assert(result[3] == "help");
  assert(result[4] == "you");
}

void test_build_string()
{
  using namespace std::literals;
  auto result = build_string("This "s, "is "sv, "a string");
  assert(result.length() == 16);
  assert(result == "This is a string");
}

void test_replace_all()
{
  std::string test = "";
  replace_all<char>(test, "he", "llo");
  assert(test == "");

  test = "Hello world";
  replace_all<char>(test, "llo", "re");
  assert(test == "Here world");

  test = "Hello world";
  replace_all<char>(test, "rld", "rd");
  assert(test == "Hello word");

  test = "Hello world";
  replace_all<char>(test, " ", "--");
  assert(test == "Hello--world");

  test = "Hello world";
  replace_all<char>(test, "l", "@");
  assert(test == "He@@o wor@d");
}

int main(int argc, char **argv)
{
  std::cout << "Tests starting.\n";

  test_is_blank();
  test_starts_with();
  test_ends_with();

  test_trim_start();
  test_trim_end();
  test_trim();

  test_join();
  test_split();

  test_build_string();
  test_replace_all();

  std::cout << "Tests passed!!";
}