
#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class IDBConnection
{
public:
    IDBConnection()          = default;
    virtual ~IDBConnection() = default;
    virtual void open()      = 0;
    virtual void close()     = 0;
    virtual void execQuery() = 0;
};

class ClassThatUsesDB
{
public:
    ClassThatUsesDB()  = default;
    ~ClassThatUsesDB() = default;

public:
    IDBConnection* connection;
    void  openConnection() { connection->open();      }
    void   useConnection() { connection->execQuery(); }
    void closeConnection() { connection->close();     }
};


void connectSomething(IDBConnection* connection)
{
    connection->open();
    connection->close();
    connection->execQuery();
}

class MockDBConnection : public IDBConnection {
public:

    MOCK_METHOD(void, open,      (), (override));
    MOCK_METHOD(void, close,     (), (override));
    MOCK_METHOD(void, execQuery, (), (override));
};


TEST(DBConnectionTest, test1)
{
    //MockDBConnection mockConnection;
    ::testing::NiceMock<MockDBConnection> mockConnection;
    //::testing::NaggyMock<MockDBConnection> mockConnection;
    //::testing::StrictMock<MockDBConnection> mockConnection;

    EXPECT_CALL(mockConnection, open     ).Times(::testing::AtLeast(1));
    EXPECT_CALL(mockConnection, close    ).Times(::testing::AtLeast(1));
    EXPECT_CALL(mockConnection, execQuery).Times(::testing::AtLeast(1));

    connectSomething(&mockConnection);
}


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
