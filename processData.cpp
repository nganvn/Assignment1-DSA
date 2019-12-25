/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : processData.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : Implementation of main features in the assignment
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#include "processData.h"
#include "dbLib.h"
/* TODO: You can implement methods, functions that support your data structures here.
 * */
using namespace std;

// traverse function

int find_cityName_cityID(TCity&a,void*tmp)
{
    if (a.name==*(string*)tmp)
        return a.id;
    return -1;
}
int find_cityId_lineId(TLine&a,void*tmp)
{
	if (a.city_id==*((int*)tmp))
		return a.id;
	return -1;
}
int find_cityId_stationId(TStation&a,void*tmp)
{
	if (a.city_id==*((int*)tmp))
		return a.id;
	return -1;
}
int find_lineId_stationId(TStation_line&a,void*tmp)
{
	if (a.line_id==(*(int*)tmp))
		return a.station_id;
	return -1;
}
int find_stationName_stationId(TStation&a,void*tmp)
{
	if (a.name==*(string*)tmp)
		return a.id;
	return -1;
}

bool cpStationID(TStation_line &a,int id)
{
	return (id==a.station_id);
}
// traverse function

// support funcition
string getString(const char*& str,char tmp)
{
    string output="";
	while (*str!= ' '&&*str!='\0')
        output+=*str++;
    if (*str=='\0')
        str--;
    str++;
    return output;
}

//
void Initialization() {
    // If you use global variables, please initialize them explicitly in this function.
}

void Finalization() {
    // Release your data before exiting
}

void ProcessRequest(const char* pRequest, void* pData, void* &pOutput, int &N) {
    // TODO: Implement this function for processing a request
    // NOTE: You can add other functions to support this main process.
    //       pData is a pointer to a data structure that manages the dataset
    //       pOutput is a pointer reference. It is set to nullptr and student must allocate data for it in order to save the required output
    //       N is the size of output, must be a non-negative number
    TDataset *tmpData=static_cast<TDataset*>(pData);
    N=1;
    string req=getString(pRequest,' ');
    if (req=="CL")
    {
        if (*pRequest=='\0')
        {
            pOutput=new int(tmpData->_tLine.getSize());
            return;
        }
        void * tmp=new string(pRequest);
        int count = tmpData->_tCity.traverse(find_cityName_cityID,tmp);
        if (count == 0)
        {
            pOutput=new int(-1);
            return;
        }
        count = tmpData->_tLine.traverse(find_cityId_lineId,tmp);
        pOutput=new int(count);
        return;
    }
    if (req=="LSC")
    {
        void * tmp=new string(pRequest); //city name
        tmpData->_tCity.traverse(find_cityName_cityID,tmp);
        N=tmpData->_tStation.traverse(find_cityId_stationId,tmp);
		pOutput=tmp;
        return;
    }
    if (req=="LLC")
    {
        void * tmp=new string(pRequest); //city name
        tmpData->_tCity.traverse(find_cityName_cityID,tmp);
        N=tmpData->_tLine.traverse(find_cityId_lineId,tmp);
        pOutput=tmp;
        return;
    }
    if (req=="LSL")
    {
        if (*pRequest=='\0')
            return;
        void * tmp=new int (stoi(pRequest)); //line id
        N=tmpData->_tStation_line.traverse(find_lineId_stationId,tmp);
        pOutput=tmp;
        return;
    }
    if (req=="FC")
    {
        if (*pRequest=='\0')
            return;
        void * tmp=new string(pRequest);//city name
        int count = tmpData->_tCity.traverse(find_cityName_cityID,tmp);
        if (count == 0)
        {
            pOutput=new int(-1);
            return;
        }
        pOutput=tmp;
        return;
    }
    if (req=="FS")
    {
        void * tmp=new string(pRequest);//station name
        int count = tmpData->_tStation.traverse(find_stationName_stationId,tmp);
        if (count == 0)
        {
            pOutput=new int(-1);
            return;
        }
        pOutput=tmp;
        return;
    }
    if (req=="SLP")
    {
        if (*pRequest=='\0')
            return;
        int station_id=stoi(getString(pRequest,' '));
        if (*pRequest=='\0')
            return;
        int track_id=stoi(getString(pRequest,' '));
		TStation *tmpStation=tmpData->_tStation.findT(station_id);
        TTrack *tmpTrack=tmpData->_tTrack.findT(track_id);
        if (!tmpStation||!tmpTrack)
        {
            pOutput=new int(-1);
            return;
        }
        int pos=tmpTrack->geometry.find(tmpStation->geometry);
        if (pos==-1)
            pOutput=new int(pos);
        else
        {
            int count=0;
            for (int i=0; i<pos; i++)
                count+=tmpTrack->geometry[i]==',';
            pOutput=new int(count);
        }
        return;
    }
    if (req=="IS")
    {
		string csv_description=pRequest;
		int indexMax=tmpData->_tStation.findIndexMax();
		TStation tm;
        tm.id=indexMax+1;
        tm.name=getCell(csv_description);
        string tmp=getCell(csv_description);
        tmp.pop_back();
        tmp.erase(0,6);
        tm.geometry=tmp;
        tmpData->_tStation.push_back(tm);
		pOutput=new int(indexMax+1);
        return;
    }
    if (req=="RS")
    {
        if (*pRequest=='\0')
            return;
		int station_id=stoi(pRequest);
		int tmp=tmpData->_tStation.remove_id(station_id);
		if (tmp==-1)
			pOutput=new int(-1);
		else
		{
			pOutput=new int(0);
			tmpData->_tStation_line.traverseRemove(cpStationID,station_id);
		}
        return;
    }
    if (req=="US")
    {
        if (*pRequest=='\0')
            return;
		int station_id=stoi(getString(pRequest,' '));
		string csv_description=pRequest;
		TStation *tmpS=tmpData->_tStation.findT(station_id);
		if (!tmpS)
			pOutput=new int(-1);
		else
		{
			tmpS->name=getCell(csv_description);
			string tmp=getCell(csv_description);
			tmp.pop_back();
			tmp.erase(0,6);
			tmpS->geometry=tmp;
			ignoreCell(csv_description,3);
			tmpS->city_id=stoi(getCell(csv_description));
			pOutput=new int(0);
		}
        return;
    }
    if (req=="ISL")
    {
        if (*pRequest=='\0')
            return;
		int station_id=stoi(getString(pRequest,' '));
		if (*pRequest=='\0')
            return;
		int line_id=stoi(getString(pRequest,' '));
		if (*pRequest=='\0')
            return;
		int p_i=stoi(getString(pRequest,' '));
		void * tmp=new int (line_id); //line id
		TStation_line tmpSL;
        tmpSL.station_id=station_id;
        tmpSL.line_id=line_id;
        int count=tmpData->_tStation_line.traverse(find_lineId_stationId,tmp);
        if (count == 0 && p_i == 0)
        {
			tmpData->_tStation_line.insert(0,tmpSL);
			pOutput=new int(0);
            return;
        }
		if (p_i>count)
		{
			pOutput=new int(-1);
			return;
		}
		else
		{
			for (int i=0;i<count;i++)
			{
				if (station_id==((int*)tmp)[i])
				{
					pOutput=new int(-1);
					return;
				}
			}
			tmpSL.station_id=((int*)tmp)[p_i];
			TStation_line *tmpSL1=tmpData->_tStation_line.findT(tmpSL);
			int index=tmpData->_tStation_line.findIndex(tmpSL1->id);
			tmpSL.station_id=station_id;
			tmpData->_tStation_line.insert(index,tmpSL);
			pOutput=new int(0);
		}
        return;
    }
    if (req=="RSL")
    {
        if (*pRequest=='\0')
            return;
        int station_id=stoi(getString(pRequest,' '));
        if (*pRequest=='\0')
            return;
        int line_id=stoi(getString(pRequest,' '));
        TStation_line tmp;
        tmp.station_id=station_id;
        tmp.line_id=line_id;
		TStation_line *tmpSL=tmpData->_tStation_line.findT(tmp);
		if (!tmpSL)
			pOutput=new int(-1);
        else
		{
			tmpData->_tStation_line.remove_id(tmpSL->id);
			pOutput=new int(0);
		}
        return;
    }
}

