#pragma once
#include <filesystem>
#include <iostream>
#include "fileref.h"
#include "tag.h"

namespace fs = std::filesystem;
using namespace std;


class MetadataParser {
private:
bool isValidFile(string path);

public:

void getMetaData (string songpath,string file);
// string getAlbumArt(string songpath,string file);
void getPseudoMetaData (string songpath);
void startIndexing(string path);

};