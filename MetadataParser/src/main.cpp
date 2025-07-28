#include <iostream>
#include "MetaDataparser.hpp"
#include <thread>
#include <memory>

int main(int, char**){
unique_ptr<MetadataParser>indexer=make_unique<MetadataParser>();


std::string path = "/home/mayur/music/"; // Path to the directory to index
thread indexerThread(&MetadataParser::startIndexing,indexer.get(),path); //.get() to get raw pointer


indexerThread.join();
}
