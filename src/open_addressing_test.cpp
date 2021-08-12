//#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_RUNNER
#include "../lib/catch.hpp"
#include "open_addressing.hpp"

typedef OpenAddressing<int> OpenAddressingTest;
typedef OpenAddressingTest* OpenAddressingPointerTest;

OpenAddressingPointerTest linear_probing, quadratic_probing, double_hashing;

int HashFunctionLinearProbing(int key, int i)
{
    return (key + i) % 11; 
}

int HashFunctionQuadraticProbing(int key, int i)
{
    return (key + i + 3 * i * i) % 11; 
}

int HashFunctionDoubleHashing(int key, int i)
{
    return (key + i * (1 + key % 10)) % 11; 
}

int main( int argc, char* argv[] ) {
    // global setup...

    linear_probing = new OpenAddressingTest(11, HashFunctionLinearProbing);
    quadratic_probing = new OpenAddressingTest(11, HashFunctionQuadraticProbing);
    double_hashing = new OpenAddressingTest(11, HashFunctionDoubleHashing);

    int result = Catch::Session().run( argc, argv );

    // global clean-up...

    return result;
}

TEST_CASE("linear_probing are tested", "[linear_probing]") {
    CHECK(linear_probing->HashInsert(10, 1) == 10);
    CHECK(linear_probing->HashInsert(22, 2) == 0);
    CHECK(linear_probing->HashInsert(31, 3) == 9);
    CHECK(linear_probing->HashInsert(4, 4) == 4);
    CHECK(linear_probing->HashInsert(15, 5) == 5);
    CHECK(linear_probing->HashInsert(28, 6) == 6);
    CHECK(linear_probing->HashInsert(17, 7) == 7);
    CHECK(linear_probing->HashInsert(88, 8) == 1);
    CHECK(linear_probing->HashInsert(59, 9) == 8);
}

TEST_CASE("quadratic_probing are tested", "[quadratic_probing]") {
    CHECK(quadratic_probing->HashInsert(10, 1) == 10);
    CHECK(quadratic_probing->HashInsert(22, 2) == 0);
    CHECK(quadratic_probing->HashInsert(31, 3) == 9);
    CHECK(quadratic_probing->HashInsert(4, 4) == 4);
    CHECK(quadratic_probing->HashInsert(15, 5) == 8);
    CHECK(quadratic_probing->HashInsert(28, 6) == 6);
    CHECK(quadratic_probing->HashInsert(17, 7) == 3);
    CHECK(quadratic_probing->HashInsert(88, 8) == 2);
    CHECK(quadratic_probing->HashInsert(59, 9) == 7);
}

TEST_CASE("double_hashing insert are tested", "[double_hashing insert]") {
    CHECK(double_hashing->HashInsert(10, 1) == 10);
    CHECK(double_hashing->HashInsert(22, 2) == 0);
    CHECK(double_hashing->HashInsert(31, 3) == 9);
    CHECK(double_hashing->HashInsert(4, 4) == 4);
    CHECK(double_hashing->HashInsert(15, 5) == 5);
    CHECK(double_hashing->HashInsert(28, 6) == 6);
    CHECK(double_hashing->HashInsert(17, 7) == 3);
    CHECK(double_hashing->HashInsert(88, 8) == 7);
    CHECK(double_hashing->HashInsert(59, 9) == 2);
}

TEST_CASE("double_hashing search are tested", "[double_hashing search]") {
    CHECK(double_hashing->HashSearch(10) == 10);
    CHECK(double_hashing->HashSearch(22) == 0);
    CHECK(double_hashing->HashSearch(31) == 9);
    CHECK(double_hashing->HashSearch(4) == 4);
    CHECK(double_hashing->HashSearch(15) == 5);
    CHECK(double_hashing->HashSearch(28) == 6);
    CHECK(double_hashing->HashSearch(17) == 3);
    CHECK(double_hashing->HashSearch(88) == 7);
    CHECK(double_hashing->HashSearch(59) == 2);
}

TEST_CASE("double_hashing HashGet are tested", "[double_hashing HashGet]") {
    CHECK(double_hashing->HashGet(10) == 1);
    CHECK(double_hashing->HashGet(0) == 2);
    CHECK(double_hashing->HashGet(9) == 3);
    CHECK(double_hashing->HashGet(4) == 4);
    CHECK(double_hashing->HashGet(5) == 5);
    CHECK(double_hashing->HashGet(6) == 6);
    CHECK(double_hashing->HashGet(3) == 7);
    CHECK(double_hashing->HashGet(7) == 8);
    CHECK(double_hashing->HashGet(2) == 9);
}

TEST_CASE("double_hashing HashDelete are tested", "[double_hashing HashDelete]") {
    double_hashing->HashDelete(10);
    double_hashing->HashDelete(0);
    double_hashing->HashDelete(9);
    double_hashing->HashDelete(4);
    double_hashing->HashDelete(5);
    double_hashing->HashDelete(6);
    double_hashing->HashDelete(3);
    double_hashing->HashDelete(7);
    double_hashing->HashDelete(2);
}

TEST_CASE("double_hashing search after HashDelete are tested", 
        "[double_hashing search after HashDelete]") {
    CHECK(double_hashing->HashSearch(10) == -1);
    CHECK(double_hashing->HashSearch(22) == -1);
    CHECK(double_hashing->HashSearch(31) == -1);
    CHECK(double_hashing->HashSearch(4) == -1);
    CHECK(double_hashing->HashSearch(15) == -1);
    CHECK(double_hashing->HashSearch(28) == -1);
    CHECK(double_hashing->HashSearch(17) == -1);
    CHECK(double_hashing->HashSearch(88) == -1);
    CHECK(double_hashing->HashSearch(59) == -1);
}
