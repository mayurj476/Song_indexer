#include "DbManager.hpp"

IDbFactory* Dbmanager::getDabase(string path,DbType type)
{

    switch (type)
    {
    case DbType::INSERTER:
        return DbInserter::getDbInserter(path);
    case DbType::SELECTOR:
        return DbSelector::getDbSelector(path);
    default:
        return nullptr;
    }

}
