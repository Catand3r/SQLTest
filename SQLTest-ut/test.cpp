#include "PersonManager.h"
#include "isqlengine.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

class MockISQLEngine : public ISQLEngine
{
  public:
    MockISQLEngine() : ISQLEngine("testing")
    {
    }

    MOCK_METHOD(bool, open, (), (override));
    MOCK_METHOD(bool, exec, (const std::string &query, QueryResult &result), (override));
    MOCK_METHOD(int, getLastRC, (), (const, override));
    MOCK_METHOD(bool, isOpen, (), (const, override));
};

TEST(PersonManagerTest, test)
{
    MockISQLEngine mockDB;

    PersonManager pm(mockDB);

    EXPECT_CALL(mockDB, isOpen()).WillOnce(testing::Return(false));
    EXPECT_CALL(mockDB, open()).WillOnce(testing::Return(true));
    EXPECT_CALL(mockDB, exec("INSERT INTO persons (name, age) VALUES ('Alice', 30)", testing::_))
        .WillOnce(testing::Return(true));
    EXPECT_TRUE(pm.addPerson("Alice", 30));
}
