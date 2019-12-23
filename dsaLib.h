/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dsaLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DSALIB_H
#define DSA191_A1_DSALIB_H
#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

class DSAException
{
    int     _error;
    string  _text;
public:

    DSAException() : _error(0), _text("Success") {}
    DSAException(int err) : _error(err), _text("Unknown Error") {}
    DSAException(int err, const char* text) : _error(err), _text(text) {}

    int getError()
    {
        return _error;
    }
    string& getErrorText()
    {
        return _text;
    }
};

template <class T>
struct L1Item
{
    T data;
    L1Item<T> *pNext;
    L1Item() : pNext(NULL) {}
    L1Item(T &a) : data(a), pNext(NULL) {}
};

template <class T>
class L1List
{
    L1Item<T>   *_pHead;// The head pointer of linked list
    L1Item<T>   *_pTail;// The tail pointer of linked list

    size_t      _size;// number of elements in this list
public:
    L1List() : _pHead(NULL), _size(0) {}
    ~L1List();

    void    clean();
    bool    isEmpty()
    {
        return _pHead == NULL;
    }
    size_t  getSize()
    {
        return _size;
    }

    T&      at(int );// give the reference to the element i-th in the list
    T&      operator[](int );// give the reference to the element i-th in the list

    bool    find(T& , int& );// find an element similar to a in the list. Set the found index to idx, set idx to -1 if failed. Return true if success.
    int     findIndex(int);
	T*   	findT(int);
	T*   	findT(T&);
	int 	findIndexMax();
    int     insert(int , T& );// insert an element into the list at location i. Return 0 if success, -1 otherwise
    int     remove(int );// remove an element at position i in the list. Return 0 if success, -1 otherwise.
	int     remove_id(int );
    void    clear();

    int     push_back(T& );// insert to the end of the list
    int     insertHead(T& );// insert to the beginning of the list

    int     removeHead();// remove the beginning element of the list
    int     removeLast();// remove the last element of the list

    void    reverse();

    void    traverse(void (*op)(T&))
    {
        // TODO: Your code goes here
        L1Item<T> *tmp = _pHead;
        while (tmp)
        {
            (*op)(tmp->data);
            tmp=tmp->pNext;
        }
    }
    int    traverse(int (*op)(T&,void*), void *& pParam)
    {
        L1Item<T> *tmpCur = _pHead;
        int *output=new int[5000];
        int size_output=0;
        while (tmpCur)
        {
            int temp = (*op)(tmpCur->data,pParam);
            if (temp!=-1)
                output[size_output++]=temp;
            tmpCur=tmpCur->pNext;
        }
		if (size_output==0)
			output[size_output++]=-1;
        pParam=output;
		return size_output;

    }
	void traverseRemove(bool (*op)(T&,int),int id)
    {
        L1Item<T> *pCur = _pHead;
        while (pCur)
        {
            if (op(pCur->data,id))
			{
				if (pCur==_pHead)
					removeHead();
				else
				{
					if (pCur==_pTail)
						removeLast();
					else
					{
						L1Item<T> *pTmp=pCur->pNext;
						pCur->pNext=pCur->pNext->pNext;
						delete pTmp;
						_size--;
						cout << id << '\n';
					}
				}
			}
            pCur=pCur->pNext;
        }
    }
};

template <class T>
T& L1List<T>::at(int i)
{
    L1Item<T> *pCur=_pHead;
    while (i>0)
    {
        pCur=pCur->pNext;
        i--;
    }
    return pCur->data;
}
template <class T>
T&  L1List<T>::operator[](int i)
{
    L1Item<T> *pCur=_pHead;
    while (i>0)
    {
        pCur=pCur->pNext;
        i--;
    }
    return pCur->data;
}
template <class T>
int L1List<T>::findIndex(int a)
{
    L1Item<T> *pCur=_pHead;
    for (int i=0; i<_size; i++)
    {
        if(pCur->data==a)
            return i;
		pCur=pCur->pNext;
    }
    return -1;
}
template <class T>
T* L1List<T>::findT(int a)
{
    L1Item<T> *pCur=_pHead;
    for (int i=0; i<_size; i++)
    {
        if(pCur->data==a)
            return &pCur->data;
		pCur=pCur->pNext;

    }
    return NULL;
}
template <class T>
T* L1List<T>::findT(T& a)
{
    L1Item<T> *pCur=_pHead;
    for (int i=0; i<_size; i++)
    {
        if(pCur->data==a)
			return &pCur->data;
		pCur=pCur->pNext;

    }
	return NULL;
}
template <class T>
int L1List<T>::findIndexMax()
{
    L1Item<T> *pCur=_pHead;
	int IndexMax=0;
    for (int i=0; i<_size; i++)
    {
        IndexMax=pCur->data>IndexMax;
		pCur=pCur->pNext;
    }
	return IndexMax;
}
template <class T>
int L1List<T>::insert(int i, T& a)
{
    if (i<0||i>_size)
        return -1;
    if (i==0)
    {
        insertHead(a);
        return 0;
    }
    if (i==_size)
    {
        push_back(a);
        return 0;
    }
    L1Item<T> *pNew= new L1Item<T>(a);
    L1Item<T> *pCur=_pHead;
    for (int j=1; j<i-1; j++)
        pCur=pCur->pNext;
    pNew->pNext=pCur->pNext;
    pCur->pNext=pNew;
    _size++;
    return 0;
}
template <class T>
int L1List<T>::remove(int i)
{
    if (isEmpty()||i<0||i>=_size)
        return -1;
    if (i==0)
    {
        removeHead();
        return 0;
    }
    if (i==_size-1)
    {
        removeLast();
        return 0;
    }
    L1Item<T> *pCur=_pHead;
    for (int j=1; j<i-1; j++)
        pCur=pCur->pNext;
    L1Item<T> *pTmp=pCur->pNext;
    pCur->pNext=pCur->pNext->pNext;
    delete pTmp;
    _size--;
}
template <class T>
int L1List<T>::remove_id(int id)
{
    if (isEmpty())
        return -1;
	L1Item<T> *pCur=_pHead;
	while (pCur)
    {
		if (pCur->data==id)
			break;
		pCur=pCur->pNext;
	}
	if (!pCur)
		return -1;
	if (pCur==_pHead)
	{
        removeHead();
        return 0;
    }
	if (pCur==_pTail)
    {
        removeLast();
        return 0;
    }
    L1Item<T> *pTmp=pCur->pNext;
    pCur->pNext=pCur->pNext->pNext;
    delete pTmp;
    _size--;
}

/// Insert item to the end of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::push_back(T &a)
{
    // TODO: Your code goes here
    L1Item<T> *pNew= new L1Item<T>(a);
    _size++;
    if (isEmpty())
    {
        _pHead=pNew;
        _pTail=pNew;
    }
    else
    {
        _pTail->pNext=pNew;
        _pTail=pNew;
    }
    return 0;

}
template <class T>
void L1List<T>::clear()
{
    L1Item<T> *pCur=_pHead;
    while (pCur)
    {
        L1Item<T> *pTmp=pCur;
        pCur=pCur->pNext;
        delete pTmp;
    }
    _pHead=NULL;
    _pTail=NULL;
    _size=0;
}
/// Insert item to the front of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::insertHead(T &a)
{
    // TODO: Your code goes here
    L1Item<T> *pNew= new L1Item<T>(a);
    if (isEmpty())
    {
        _pHead=pNew;
    }
    else
    {
        pNew->pNext=_pHead;
        _pHead=pNew;
    }
    _size++;
    return 0;
}

/// Remove the first item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeHead()
{
    // TODO: Your code goes here
    if (isEmpty())
        return 0;
    L1Item<T> *pCur=_pHead;
    _pHead=_pHead->pNext;
    delete pCur;
    _size--;
    return -1;
}

/// Remove the last item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeLast()
{
    // TODO: Your code goes here
    if (isEmpty())
        return 0;
    L1Item<T> *pCur=_pHead;
    for(int i=1; i<_size-1; i++)
        pCur=pCur->pNext;
    delete pCur->pNext;
    pCur->pNext=NULL;
    _size--;
    return -1;
}
template <class T>
L1List<T>::~L1List()
{
    clear();
}
#endif //DSA191_A1_DSALIB_H
