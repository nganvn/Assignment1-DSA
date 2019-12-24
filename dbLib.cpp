/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#include "dbLib.h"

/* TODO: You can implement methods, functions that support your data structures here.
 * */
 void LoadData(void* &pData)
{
    pData =new TDataset;
}
void ReleaseData(void* &pData)
{
    delete static_cast<TDataset*>(pData);
}



string getCell(string &str)
{
    char keyCheck = ',';
    int i=0;
    if (str[0]=='"')
    {
        keyCheck = '"';
        i=1;
    }
    string s="";
    while (str[i]!=keyCheck && str[i]!='\0')
        s.push_back(str[i++]);
    if (keyCheck=='"')
        i++;
    if (str[i]=='\0')
        i--;
    str.erase(0,i+1);
    return s;
}
void ignoreCell(string &str,int numberCell)
{
    for (int i=0;i<numberCell;i++)
        getCell(str);
}

void TDataset::loadData_tCity()
{
    ifstream inFile;
    string line;
    inFile.open("cities.csv");
    getline(inFile,line,'\n');
    while (getline(inFile,line,'\n'))
    {
        TCity tm;
        tm.id=stoi(getCell(line));
        tm.name=getCell(line);
        _tCity.push_back(tm);
    }
    inFile.close();
}
void TDataset::loadData_tLine()
{
    ifstream inFile;
    string line;
    inFile.open("lines.csv");
    getline(inFile,line,'\n');
    while (getline(inFile,line,'\n'))
    {
        TLine tm;
        tm.id=stoi(getCell(line));
        tm.city_id=stoi(getCell(line));
        _tLine.push_back(tm);
    }
    inFile.close();
}
void TDataset::loadData_tTrack()
{
    ifstream inFile;
    inFile.open("tracks.csv");
    string line;
    getline(inFile,line,'\n');
    while (getline(inFile,line,'\n'))
    {
        TTrack tm;
        tm.id=stoi(getCell(line));
        int tmp1=line.find('(');
        int tmp2=line.rfind(')');
        if (line.find('(')>=0)
        {
            tm.geometry=line.substr(tmp1+1,tmp2-tmp1-1);
            line.erase(0,tmp2+2);
        }
        else
        {
            ignoreCell(line,1);
        }
        ignoreCell(line,4);
        tm.city_id=stoi(getCell(line));
        _tTrack.push_back(tm);
    }
    inFile.close();
}
void TDataset::loadData_tStation()
{
    ifstream inFile;
    inFile.open("stations.csv");
    string line;
    getline(inFile,line,'\n');
    while (getline(inFile,line,'\n'))
    {
        TStation tm;
        tm.id=stoi(getCell(line));
        tm.name=getCell(line);
        string tmp=getCell(line);
        tmp.pop_back();
        tmp.erase(0,6);
        tm.geometry=tmp;
        ignoreCell(line,3);
        tm.city_id=stoi(getCell(line));
        _tStation.push_back(tm);
    }
    inFile.close();
}
void TDataset::loadData_tSystem()
{
    ifstream inFile;
    inFile.open("systems.csv");
    string line;
    getline(inFile,line,'\n');
    while (getline(inFile,line,'\n'))
    {
        TSystem tm;
        tm.id=stoi(getCell(line));
        tm.city_id=stoi(getCell(line));
        _tSystem.push_back(tm);
    }
    inFile.close();
}
void TDataset::loadData_tStation_line()
{
    ifstream inFile;
    inFile.open("station_lines.csv");
    string line;
    getline(inFile,line,'\n');
    while (getline(inFile,line,'\n'))
    {
        TStation_line tm;
        tm.id=stoi(getCell(line));
        tm.station_id=stoi(getCell(line));
        tm.line_id=stoi(getCell(line));
//        printf("%d %d %d\n",tm.id,tm.station_id,tm.line_id);
        _tStation_line.push_back(tm);
    }
    inFile.close();
}
void TDataset::loadData_tTrack_line()
{
    ifstream inFile;
    inFile.open("station_lines.csv");
    string line;
    getline(inFile,line,'\n');
    while (getline(inFile,line,'\n'))
    {
        TTrack_line tm;
        tm.id=stoi(getCell(line));
        _tTrack_line.push_back(tm);
    }
    inFile.close();
}

int TDataset::getLines()
{
    return _tCity.getSize()+_tLine.getSize()
           + _tTrack.getSize()+_tStation.getSize()
           + _tSystem.getSize()+_tStation_line.getSize()
           + _tTrack_line.getSize();

}
