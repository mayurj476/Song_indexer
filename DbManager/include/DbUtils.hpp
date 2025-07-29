#pragma once
#include<iostream>
using namespace std;

struct tableData
{
   int Id;
   string trackPath;
   string trackName;
   string FileName;
   string artist;
   string genre;
   string album;
   string albumart;
   int length;
   int year;
   bool isFav;
   
};

struct songinfo{
string fullpath;
string trackname;
string fileName;
string albumart;


};



const string DATABASE_PATH="SongsDataBase.db";