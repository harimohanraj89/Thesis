//
//  TwoDArray.h
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 11/30/12.
//  Copyright (c) 2012 Hariharan Mohanraj. All rights reserved.
//

#ifndef __SoniScan_2_0__TwoDArray__
#define __SoniScan_2_0__TwoDArray__

#include <iostream>
#include <vector>

// DEVELOPER NOTES IN PROGRESS
// Change noRows and noCols to vector sizetype.


template <class el_type> class TwoDArray
{
private:
    // Vector of vectors to store elements of the 2D array
    // "elements" is in the format rowVector<columnVectors>
    
    std::vector<std::vector<el_type>> elements;
    
    // Metadata for "elements"
    // noRows : number of rows existing in "elements"       - int
    // noCols : number of columns existing in "elements"    - int
    
    int noRows;
    int noCols;
    
    
public:
    // GetNoRows() - returns the number of rows in "elements"
    int GetNoRows();
    
    // GetNoCols() - returns the number of cols in "elements"
    int GetNoCols();
    
    // GetRow(n) - returns a vector containing elements in row of index n
    std::vector<el_type> GetRow(int);

    // GetCol(n) - returns a vector containing elements in col of index n
    std::vector<el_type> GetCol(int);

    // Get(x,y) - returns the value of the element at cartesian coordinate position (x,y)
    el_type Get(int, int);
    
    // GetP(x,y) - returns a pointer to the element at cartesian coordinate position (x,y)
    el_type* GetP(int, int);
    
    // Set(p,x,y) - sets the value of the element at cartesian coordinate poisition (x,y) to p
    void Set(el_type, int, int);
    
    // PushCol(v) - appends vector v as the last column of "elements"
    void PushCol(std::vector<el_type>);
    
    // PopCol() - pops the last column of "elements"
    void PopCol();
    
    // PushRow(v) - appends vector v as the last row of "elements"
    void PushRow(std::vector<el_type>);
    
    // PopRow() - pops the last row of "elements"
    void PopRow();

    // Clear() - empties the contents of "elements"
    void Clear();
};


template <class el_type> int TwoDArray<el_type>::GetNoRows()
{
    return noRows;
}

template <class el_type> int TwoDArray<el_type>::GetNoCols()
{
    return noCols;
}


template <class el_type> std::vector<el_type> TwoDArray<el_type>::GetRow(int argIndex)
{
    std::vector<el_type> emptyVec;
    
    // Checking whether input arguments are within range of "elements"
    if(argIndex < 0 || argIndex >= noRows)
    {
        std::cout << "Index is out of range. Returning -1.\n";
        return emptyVec;
    }

    for(int i=0; i<noCols; i++)
    {
        emptyVec.push_back(elements[i][argIndex]);
    }
    return emptyVec;

}

template <class el_type> std::vector<el_type> TwoDArray<el_type>::GetCol(int argIndex)
{
    // Checking whether input arguments are within range of "elements"
    if(argIndex < 0 || argIndex >= noCols)
    {
        std::cout << "Index is out of range. Returning -1.\n";
        std::vector<el_type> emptyVec;
        return emptyVec;
    }
    
    return elements[argIndex];
}


template <class el_type> el_type TwoDArray<el_type>::Get(int x, int y)
{
    std::vector<float> selectedColumn;
    //float selectedElement;
    
    // Checking whether input arguments are within range of "elements"
    if(x < 0 || x >= noCols)
    {
        std::cout << "X value is out of range. Returning -1.\n";
        return -1.0;
    }
    
    if(y < 0 || y >= noRows)
    {
        std::cout << "Y value is out of range. Returning -1.\n";
        return -1.0;
    }
    
    // Extracting selected element from "elements"
    //selectedColumn = elements.at(x);
    //selectedElement = selectedColumn.at(y);
    return elements.at(x).at(y);
}

template <class el_type> el_type* TwoDArray<el_type>::GetP(int x, int y)
{
    std::vector<float> selectedColumn;
    //float selectedElement;
    
    // Checking whether input arguments are within range of "elements"
    if(x < 0 || x >= noCols)
    {
        std::cout << "X value is out of range. Returning -1.\n";
        return 0;
    }
    
    if(y < 0 || y >= noRows)
    {
        std::cout << "Y value is out of range. Returning -1.\n";
        return 0;
    }
    
    // Extracting selected element from "elements"
    //selectedColumn = elements.at(x);
    //selectedElement = selectedColumn.at(y);
    return &elements.at(x).at(y);
}

template <class el_type> void TwoDArray<el_type>::Set(el_type value, int x, int y)
{
    // Checking whether input arguments are within range of "elements"
    if(x < 0 || x >= noRows)
    {
        std::cout << "X value is out of range. set call ignored.\n";
    }
    
    if(y < 0 || y >= noCols)
    {
        std::cout << "Y value is out of range. set call ignored.\n";
    }
    
    (elements[x])[y] = value;
    
}

template <class el_type> void TwoDArray<el_type>::PushCol(std::vector<el_type> v)
{
    // Check whether dimensions agree
    
    if(v.size() != noRows && noCols != 0)
    {
        std::cout << "Array dimensions don't agree. Push call ignored.\n";
        return;
    }
    
    // If dimensions agree, push column, update noCols
    elements.push_back(v);

    if (noCols == 0)
        noRows = v.size();
    
    noCols = elements.size();
    
}

template <class el_type> void TwoDArray<el_type>::PopCol()
{
    // Check whether columns exist
    if (noCols == 0)
    {
        std::cout << "Empty array. PopCol call ignored.\n";
        return;
    }
    
    // If not empty, perform pop, update noCols
    elements.pop_back();
    noCols = elements.size();
}

template <class el_type> void TwoDArray<el_type>::PushRow(std::vector<el_type> v)
{
    // Check whether dimensions agree
    
    if(v.size() != noCols && noRows !=0)
    {
        std::cout << "Array dimensions don't agree. Push call ignored.\n";
        return;
    }
    
    // If dimensions agree, push row, update noRows
    int count;
    for(count = 0; count < noCols; count++)
    {
        elements[count].push_back(v[count]);
    }
    noRows = elements[1].size();
}

template <class el_type> void TwoDArray<el_type>::PopRow()
{
    
    // Check whether rows exist
    if (noCols == 0)
    {
        std::cout <<"Empty array. PopRow call ignored.\n";
        return;
    }
    
    
    
    
    if (noRows == 0)
    {
        std::cout <<"Empty array. PopRow call ignored.\n";
        return;
    }
    
    // If not empty, perform pop, update noRows
    
    // Popping the last row of "elements" will still leave a vector containing empty vectors.
    // Hence, upon popping the last row (emptying the array), the empty vectors will have to
    // be popped and noCols reset.
    if(noRows == 1)
    {
        while(noCols > 0)
        {
            this->PopCol();     //PopCol() takes care of noCols
        }
        noRows = 0;
    }
    
    int count;
    for(count = 0; count < noCols; count++)
    {
        elements[count].pop_back();
    }
    noRows = elements[0].size();

    
    
}

template <class el_type> void TwoDArray<el_type>::Clear()
{
    while(noCols > 0)
        PopCol();
    
    noRows = 0;
    noCols = 0;
}

#endif /* defined(__SoniScan_2_0__TwoDArray__) */
