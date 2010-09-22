#include <QtCore/QString>
#include <QtTest/QtTest>
#include "RedisDB.h"

class RedisDB_UT : public QObject
{
    Q_OBJECT

public:
    RedisDB_UT();

private Q_SLOTS:
    void testRun();
};

RedisDB_UT::RedisDB_UT()
{
}

void RedisDB_UT::testRun()
{
    RedisDB rdb;
    rdb.Run();

    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(RedisDB_UT);

#include "mocs/RedisDB_UT.moc"
