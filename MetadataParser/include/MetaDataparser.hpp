#pragma once
#include <filesystem>
#include <iostream>
#include "fileref.h"
#include "tag.h"
#include "DbManager.hpp"

namespace fs = std::filesystem;
using namespace std;


class MetadataParser {
private:
IDbFactory* m_dbInserter;
IDbFactory* m_dbSelector;

bool isValidFile(string path);

public:
MetadataParser();
~MetadataParser();

void getMetaData (string songpath,string file);
// string getAlbumArt(string songpath,string file);
void getPseudoMetaData (string songpath);
void startIndexing(string path);

};