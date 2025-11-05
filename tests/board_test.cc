#include <catch2/catch_test_macros.hpp>

TEST_CASE("Fail test", "[bogus]") {
  REQUIRE(false == true);
}
