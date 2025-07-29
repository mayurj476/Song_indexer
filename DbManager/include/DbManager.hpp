#pragma once
#include "DbInserter.hpp"
#include "DbSelector.hpp"


class Dbmanager
{
private:
public:
enum class DbType
{
    INSERTER,
    SELECTOR
};
  static IDbFactory* getDabase(string path, DbType type);
    Dbmanager();
    ~Dbmanager();
};


