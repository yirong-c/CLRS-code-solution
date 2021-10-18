//#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_RUNNER
#include "../../lib/catch.hpp"
#include "chained_hash.hpp"

typedef ChainedHash<void*> ChainedHashTest;
typedef ChainedHashTest::Element ElementTest;
typedef ElementTest* ElementTestPointer;

ChainedHashTest* chained_hash;
ElementTestPointer element5, element28, element19, element15, element20, element33,
    element12, element17, element10;

int HashFunction(int key)
{
    return key % 9;
}

int main( int argc, char* argv[] ) {
    // global setup...

    chained_hash = new ChainedHashTest(9, HashFunction);
    element5 = new ElementTest(5);
    element28 = new ElementTest(28);
    element19 = new ElementTest(19);
    element15 = new ElementTest(15);
    element20 = new ElementTest(20);
    element33 = new ElementTest(33);
    element12 = new ElementTest(12);
    element17 = new ElementTest(17);
    element10 = new ElementTest(10);
    chained_hash->ChainedHashInsert(element5);
    chained_hash->ChainedHashInsert(element28);
    chained_hash->ChainedHashInsert(element19);
    chained_hash->ChainedHashInsert(element15);
    chained_hash->ChainedHashInsert(element20);
    chained_hash->ChainedHashInsert(element33);
    chained_hash->ChainedHashInsert(element12);
    chained_hash->ChainedHashInsert(element17);
    chained_hash->ChainedHashInsert(element10);
    chained_hash->ChainedHashDelete(element20);
    chained_hash->ChainedHashDelete(element33);
    int result = Catch::Session().run( argc, argv );

    // global clean-up...

    return result;
}

TEST_CASE("ChainedHash are tested", "[ChainedHash]") {
    CHECK(chained_hash->ChainedHashSearch(5) == element5);
    CHECK(chained_hash->ChainedHashSearch(28) == element28);
    CHECK(chained_hash->ChainedHashSearch(19) == element19);
    CHECK(chained_hash->ChainedHashSearch(15) == element15);
    CHECK(chained_hash->ChainedHashSearch(0) == NULL);
    CHECK(chained_hash->ChainedHashSearch(100) == NULL);
    CHECK(chained_hash->ChainedHashSearch(20) == NULL);
    CHECK(chained_hash->ChainedHashSearch(33) == NULL);
    CHECK(element5->list_element_ != NULL);
    CHECK(element28->list_element_ != NULL);
    CHECK(element20->list_element_ == NULL);
    CHECK(element33->list_element_ == NULL);
}
