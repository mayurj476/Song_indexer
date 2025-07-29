#pragma once
#include <filesystem>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include "fileref.h"
#include "tag.h"
#include "DbManager.hpp"

namespace fs = std::filesystem;
using namespace std;


class MetadataParser {
private:
IDbFactory* m_dbInserter;
IDbFactory* m_dbSelector;

condition_variable m_cv;
mutex m_mutex;
bool m_indexingComplete = false;

bool isValidFile(string path);

public:
MetadataParser();
~MetadataParser();

void getMetaData (string songpath,string file);
// string getAlbumArt(string songpath,string file);
void getPseudoMetaData (string songpath);
void startIndexing(string path);
void listaudioFiles();

};