/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DBLIB_H
#define DSA191_A1_DBLIB_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <math.h>

#include "dsaLib.h"

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */
struct TCity {
    // The structure to store city information
    int id;
    string name;
    bool operator == (TCity &obj)
    {
        return id==obj.id;
    }
};
struct TLine {
    // The structure to store line information
    int id;
    int city_id;
    bool operator == (TLine &obj)
    {
        return id==obj.id;
    }
};
struct TTrack {
    // The structure to store track information
    int id;
    string geometry;
    int city_id;
    bool operator == (TTrack &obj)
    {
        return id==obj.id;
    }
	bool operator == (int id)
    {
        return this->id==id;
    }
};

struct TStation {
    int id;
    string name;
    int city_id;
    string geometry;
    bool operator == (TStation &obj)
    {
        return id==obj.id;
    }
	bool operator == (int id)
    {
        return this->id==id;
    }
	int operator >(int id)
	{
		if (this->id>id)
			return this->id;
		return id;
	}
};
struct TSystem {
    int id;
    int city_id;
    bool operator == (TSystem &obj)
    {
        return id==obj.id;
    }
};
struct TStation_line {
    int id;
    int station_id;
    int line_id;
    bool operator == (TStation_line &obj)
    {
        return station_id==obj.station_id&&line_id==obj.line_id;
    }
	bool operator == (int id)
    {
        return this->id==id;
    }
};
struct TTrack_line {
    int id;
};

class TDataset {
    // This class can be a container that help you manage your tables
public:
    L1List<TCity> _tCity;
    L1List<TLine> _tLine;
    L1List<TTrack> _tTrack;
    L1List<TStation> _tStation;
    L1List<TSystem> _tSystem;
    L1List<TStation_line> _tStation_line;
    L1List<TTrack_line> _tTrack_line;
    TDataset()
    {
        loadData_tCity();
        loadData_tLine();
        loadData_tTrack();
        loadData_tStation();
        loadData_tSystem();
        loadData_tStation_line();
        loadData_tTrack_line();
    }
    void loadData_tCity();
    void loadData_tLine();
    void loadData_tTrack();
    void loadData_tStation();
    void loadData_tSystem();
    void loadData_tStation_line();
    void loadData_tTrack_line();
    int getLines();
    int getCity_id(string);
};

// Please add more or modify as needed

string getCell(string &);
void ignoreCell(string &,int);


void LoadData(void* &);
void ReleaseData(void* &);


#endif //DSA191_A1_DBLIB_H
