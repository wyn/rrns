#include "RedisDB.h"
#include "stdio.h"
#include "credis.h"

RedisDB::RedisDB()
{
}

void RedisDB::Run()
{
    REDIS rh;
    char *val;

    /* create handle to a Redis server running on localhost, port 6379,
     with a 2 second response timeout */
    rh = credis_connect("localhost", 6379, 2000);

    /* ping server */
    credis_ping(rh);

    /* set value of key "kalle" to "kula" */
    credis_set(rh, "kalle", "kula");

    /* get value of key "kalle" */
    credis_get(rh, "kalle", &val);
    printf("get kalle returned: %s\n", val);

    /* close connection to redis server */
    credis_close(rh);

}
