#include <catch2/catch_test_macros.hpp>

TEST_CASE("Fail test 2", "[bogus]") {
  REQUIRE(false == true);
}
