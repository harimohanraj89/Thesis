//
//  ControlBlock.cpp
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 11/30/12.
//  Copyright (c) 2012 Hariharan Mohanraj. All rights reserved.
//

#include "ControlBlock.h"
#include "Constants.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>

// ===========================
// UTILITY FUNCTIONS
// ===========================
int ControlBlock::ArrayMax(int* argArray, int argLength)
{
    if (argLength < 1)
    {
        std::cout << "Empty array argument to ArrayMax(). 0 returned by default.\n";
        return 0;
    }
    
    int max = argArray[0];
    
    for (int i=1; i<argLength; i++)
    {
        if (argArray[i] > max)
        {
            max = argArray[i];
        }
    }
    
    return max;
}

int ControlBlock::ArrayMin(int* argArray, int argLength)
{
    if (argLength < 1)
    {
        std::cout << "Empty array argument to ArrayMin(). 0 returned by default.\n";
        return 0;
    }
    
    int min = argArray[0];
    
    for (int i=1; i<argLength; i++)
    {
        if (argArray[i] < min)
        {
            min = argArray[i];
        }
    }
    
    return min;
}

void ControlBlock::ClearMasterData()
{
    for (int x=0; x<masterDataSize[0]; x++)
    {
        for (int y=0; y<masterDataSize[1]; y++)
        {
            delete masterData[x][y];
        }
        
        delete masterData[x];
    }
    
    if (masterData != 0)
    {
        delete masterData;
    }
}

void ControlBlock::InitMasterData(int argX, int argY, int argZ)
{
    ClearMasterData();
    
    masterData = new float**[argX];
    
    for (int x=0; x<argX; x++)
    {
        masterData[x] = new float*[argY];
        for (int y=0; y<argY; y++)
        {
            masterData[x][y] = new float[argZ];
            for (int z=0; z<argZ; z++)
            {
                masterData[x][y][z] = -1;
            }
        }
    }
    
    masterDataSize[0] = argX;
    masterDataSize[1] = argY;
    masterDataSize[2] = argZ;
    
    SetSelectionArea(0, masterDataSize[0]-1, 0, masterDataSize[1]-1);
}


// ===========================
// PARAMETER FUNCTIONS
// ===========================


// Slice setter and getter
void ControlBlock::SetSlice(int argSlice) {
    if (argSlice < 0 || argSlice >= masterDataSize[2]) {
        std::cout << "Slice is out of bounds. SetSlice() call ignored.\n";
        return;
    }
    slice = argSlice;
}

int ControlBlock::GetSlice() {
    return slice;
}


// SetSelectionArea() - Overloaded function to define selectionArea

// One-shot assignment

void ControlBlock::SetSelectionArea(int argX1, int argX2, int argY1, int argY2)
{
    // Assign all args to selectionArea
    selectionArea.x1 = argX1;
    selectionArea.x2 = argX2;
    selectionArea.y1 = argY1;
    selectionArea.y2 = argY2;
    
    ClipSelectionArea();
}

// One name-value pair

void ControlBlock::SetSelectionArea(std::string parameterName1, int parameterValue1)
{
    // Match parameterName1 and assign parameterValue1 accordingly
    
    if(parameterName1.compare("x1") == 0)
    {
        selectionArea.x1 = parameterValue1;
    }
    if(parameterName1.compare("x2") == 0)
    {
        selectionArea.x2 = parameterValue1;
    }
    if(parameterName1.compare("y1") == 0)
    {
        selectionArea.y1 = parameterValue1;
    }
    if(parameterName1.compare("y2") == 0)
    {
        selectionArea.y2 = parameterValue1;
    }
    
    ClipSelectionArea();
}

void ControlBlock::SetSelectionArea(std::string parameterName1, int parameterValue1, std::string parameterName2, int parameterValue2)
{
    // Check for duplicate parameter names
    
    if(parameterName1 == parameterName2)
    {
        std::cout << "Duplicate parameter names. SetSelectionArea call ignored.";
        return;
    }
    
    // Match parameterName1 and assign parameterValue1 accordingly
    
    if(parameterName1.compare("x1") == 0)
    {
        selectionArea.x1 = parameterValue1;
    }
    if(parameterName1.compare("x2") == 0)
    {
        selectionArea.x2 = parameterValue1;
    }
    if(parameterName1.compare("y1") == 0)
    {
        selectionArea.y1 = parameterValue1;
    }
    if(parameterName1.compare("y2") == 0)
    {
        selectionArea.y2 = parameterValue1;
    }
    
    // Match parameterName1 and assign parameterValue1 accordingly
    
    if(parameterName2.compare("x1") == 0)
    {
        selectionArea.x1 = parameterValue2;
    }
    if(parameterName2.compare("x2") == 0)
    {
        selectionArea.x2 = parameterValue2;
    }
    if(parameterName2.compare("y1") == 0)
    {
        selectionArea.y1 = parameterValue2;
    }
    if(parameterName2.compare("y2") == 0)
    {
        selectionArea.y2 = parameterValue2;
    }
    ClipSelectionArea();
}

void ControlBlock::SetSelectionArea(std::string parameterName1, int parameterValue1, std::string parameterName2, int parameterValue2, std::string parameterName3, int parameterValue3)
{
    // Check for duplicate parameter names
    
    if(parameterName1 == parameterName2 || parameterName1 == parameterName3 || parameterName2 == parameterName3)
    {
        std::cout << "Duplicate parameter names. SetSelectionArea call ignored.";
        return;
    }
    
    // Match parameterName1 and assign parameterValue1 accordingly
    
    if(parameterName1.compare("x1") == 0)
    {
        selectionArea.x1 = parameterValue1;
    }
    if(parameterName1.compare("x2") == 0)
    {
        selectionArea.x2 = parameterValue1;
    }
    if(parameterName1.compare("y1") == 0)
    {
        selectionArea.y1 = parameterValue1;
    }
    if(parameterName1.compare("y2") == 0)
    {
        selectionArea.y2 = parameterValue1;
    }
    
    // Match parameterName2 and assign parameterValue2 accordingly
    
    if(parameterName2.compare("x1") == 0)
    {
        selectionArea.x1 = parameterValue2;
    }
    if(parameterName2.compare("x2") == 0)
    {
        selectionArea.x2 = parameterValue2;
    }
    if(parameterName2.compare("y1") == 0)
    {
        selectionArea.y1 = parameterValue2;
    }
    if(parameterName2.compare("y2") == 0)
    {
        selectionArea.y2 = parameterValue2;
    }
    
    // Match parameterName3 and assign parameterValue3 accordingly
    
    if(parameterName3.compare("x1") == 0)
    {
        selectionArea.x1 = parameterValue1;
    }
    if(parameterName3.compare("x2") == 0)
    {
        selectionArea.x2 = parameterValue1;
    }
    if(parameterName3.compare("y1") == 0)
    {
        selectionArea.y1 = parameterValue1;
    }
    if(parameterName3.compare("y2") == 0)
    {
        selectionArea.y2 = parameterValue1;
    }
    ClipSelectionArea();
}

void ControlBlock::SetSelectionArea(std::string parameterName1, int parameterValue1, std::string parameterName2, int parameterValue2, std::string parameterName3, int parameterValue3, std::string parameterName4, int parameterValue4)
{
    // Check for duplicate parameter names
    
    if(parameterName1 == parameterName2 || parameterName1 == parameterName3 || parameterName1 == parameterName4 || parameterName2 == parameterName3 || parameterName2 == parameterName4 || parameterName3 == parameterName4)
    {
        std::cout << "Duplicate parameter names. SetSelectionArea call ignored.";
        return;
    }
    
    // Match parameterName1 and assign parameterValue1 accordingly
    
    if(parameterName1.compare("x1") == 0)
    {
        selectionArea.x1 = parameterValue1;
    }
    if(parameterName1.compare("x2") == 0)
    {
        selectionArea.x2 = parameterValue1;
    }
    if(parameterName1.compare("y1") == 0)
    {
        selectionArea.y1 = parameterValue1;
    }
    if(parameterName1.compare("y2") == 0)
    {
        selectionArea.y2 = parameterValue1;
    }
    
    // Match parameterName2 and assign parameterValue2 accordingly
    
    if(parameterName2.compare("x1") == 0)
    {
        selectionArea.x1 = parameterValue2;
    }
    if(parameterName2.compare("x2") == 0)
    {
        selectionArea.x2 = parameterValue2;
    }
    if(parameterName2.compare("y1") == 0)
    {
        selectionArea.y1 = parameterValue2;
    }
    if(parameterName2.compare("y2") == 0)
    {
        selectionArea.y2 = parameterValue2;
    }
    
    // Match parameterName3 and assign parameterValue3 accordingly
    
    if(parameterName3.compare("x1") == 0)
    {
        selectionArea.x1 = parameterValue1;
    }
    if(parameterName3.compare("x2") == 0)
    {
        selectionArea.x2 = parameterValue1;
    }
    if(parameterName3.compare("y1") == 0)
    {
        selectionArea.y1 = parameterValue1;
    }
    if(parameterName3.compare("y2") == 0)
    {
        selectionArea.y2 = parameterValue1;
    }
    
    // Match parameterName4 and assign parameterValue4 accordingly
    
    if(parameterName4.compare("x1") == 0)
    {
        selectionArea.x1 = parameterValue4;
    }
    if(parameterName4.compare("x2") == 0)
    {
        selectionArea.x2 = parameterValue4;
    }
    if(parameterName4.compare("y1") == 0)
    {
        selectionArea.y1 = parameterValue4;
    }
    if(parameterName4.compare("y2") == 0)
    {
        selectionArea.y2 = parameterValue4;
    }
}

int ControlBlock::GetSelectionArea(std::string parameterName) {
    if(parameterName.compare("x1") == 0)
    {
        return selectionArea.x1;
    }
    if(parameterName.compare("x2") == 0)
    {
        return selectionArea.x2;
    }
    if(parameterName.compare("y1") == 0)
    {
        return selectionArea.y1;
    }
    if(parameterName.compare("y2") == 0)
    {
        return selectionArea.y2;
    }
    
    std::cout << "Invalid parameter name. GetSelectionArea() call returning zero by default.\n";
}

void ControlBlock::ClipSelectionArea() {
    selectionArea.x1 = std::min(selectionArea.x1,masterDataSize[0]);
    selectionArea.x1 = std::max(selectionArea.x1,0);
    
    selectionArea.x2 = std::min(selectionArea.x2,masterDataSize[0]);
    selectionArea.x2 = std::max(selectionArea.x2,0);
    
    selectionArea.y1 = std::min(selectionArea.y1,masterDataSize[1]);
    selectionArea.y1 = std::max(selectionArea.y1,0);
    
    selectionArea.y2 = std::min(selectionArea.y2,masterDataSize[1]);
    selectionArea.y2 = std::max(selectionArea.y2,0);
    
    if (selectionArea.x2 < selectionArea.x1) {
        int temp = selectionArea.x2;
        selectionArea.x2 = selectionArea.x1;
        selectionArea.x1 = temp;
    }
    
    if (selectionArea.y2 < selectionArea.y1) {
        int temp = selectionArea.y2;
        selectionArea.y2 = selectionArea.y1;
        selectionArea.y1 = temp;
    }
}

void ControlBlock::SetRangeMin(float value)
{
    rangeMin = std::min(value,rangeMax);
}

void ControlBlock::SetRangeMax(float value)
{
    rangeMax = std::max(value,rangeMin);
}

float ControlBlock::GetRangeMin() {
    return rangeMin;
}

float ControlBlock::GetRangeMax() {
    return rangeMax;
}

// =================================
// SONIFICATION ENGINE CONNECTORS
// =================================

void ControlBlock::SetEngine(SoniEngine* argEngine)
{
    if (argEngine == 0)
    {
        std::cout << "Null argument received in SetEngine(). Setting engine to null.\n";
    }
    engine = argEngine;
    engine->SetControl(this);
}

SoniEngine* ControlBlock::GetEngine()
{
    return engine;
}

// ===========================
// DATA INPUT/OUTPUT FUNCTIONS
// ===========================


// Function to read file into masterData
// -------------------------------------

void ControlBlock::ReadFile(char* argFilename)
{
    char dataLine[MAX_SCORELINE_LENGTH];
    sprintf(dataLine,TEST_DATA_PATH "%s.txt", argFilename);
    
    std::string str;
    int curr;
    
    int nums[4] = {0,0,0,0};
    int exp = 0;
    int pos;
    int index = 4;
    int lineCount = 0;
    int currLine;

    std::cout << "Reading file...\n";
    
    std::ifstream inputFile;

    
    // Calculate line count
    // --------------------
    inputFile.open(dataLine);
    
    if(!inputFile.good())
    {
        std::cout << "Error opening file!\n";
        return;
    }
    
    
    while (getline(inputFile, str))
    {
        lineCount++;
    }
    
    // Check for empty file
    // --------------------
    if (lineCount < 1)
    {
        std::cout << "Empty file! FileRead() call ignored.\n";
        return;
    }
    
    inputFile.close();
    
    
    // Initialize arrays to hold data
    // ------------------------------
    int* X    = new int[lineCount];
    int* Y    = new int[lineCount];
    int* Z    = new int[lineCount];
    int* vals = new int[lineCount];
    
    
    inputFile.open(dataLine);
    
    if(!inputFile.good())
    {
        std::cout << "Error opening file!";
        return;
    }
    
    // Populate arrays with data from file
    // -----------------------------------
    currLine = 0;
    while(getline(inputFile, str))
    {
        pos = str.size() - 1;
        index = 3;
        exp = 0;
        nums[0] = 0;
        nums[1] = 0;
        nums[2] = 0;
        nums[3] = 0;
        
        while (index >= 0 && pos >= 0)
        {
            curr = int(str[pos]);
            if ( curr >= 48 && curr <= 57)   // If curr is a number character
            {
                nums[index] += (curr-48) * pow(10,exp);
                exp++;
            }
            
            if (curr == 44)
            {
                index--;
                exp = 0;
            }
            pos--;
        }

        X[currLine]    = nums[0];
        Y[currLine]    = nums[1];
        Z[currLine]    = nums[2];
        vals[currLine] = nums[3];
        currLine++;
    }
    
    int xMin;
    int xMax;
    int yMin;
    int yMax;
    int zMin;
    int zMax;
    
    xMin = ArrayMin(X,lineCount);
    xMax = ArrayMax(X,lineCount);
    yMin = ArrayMin(Y,lineCount);
    yMax = ArrayMax(Y,lineCount);
    zMin = ArrayMin(Z,lineCount);
    zMax = ArrayMax(Z,lineCount);
    
    InitMasterData(xMax-xMin+1, yMax-yMin+1, zMax-zMin+1);
    
    for (int i=0; i<lineCount; i++)
    {
        masterData[X[i]-1][Y[i]-1][Z[i]-1] = vals[i];
    }
    
    TrimMasterData();
    engine->SetMasterData(masterData,masterDataSize);
    
    delete X;
    delete Y;
    delete Z;
    delete vals;
    
    
}

// Function to trim away all external data
// ---------------------------------------
void ControlBlock::TrimMasterData()
{
    int absThreshold = TRIM_THRESHOLD * pow(2,DATA_BITDEPTH);
    int x;
    bool trimFlag;
    
    // Check whether data exists
    if (masterData == 0)
    {
        std::cout << "Dataset does not exist. TrimData() call ignored.\n";
        return;
    }
    
    // Iterate through each slice of data
    
    for (int z=0; z<masterDataSize[2]; z++)
    {
        // Iterate through each row of slice
        for (int y=0; y<masterDataSize[1]; y++)
        {
            // Trim data from left
            trimFlag = true;
            x=0;
            while(trimFlag)
            {
                if (x >= masterDataSize[0])
                {
                    trimFlag = false;
                } else if (masterData[x][y][z] > absThreshold)
                {
                    trimFlag = false;
                } else
                {
                    masterData[x][y][z] = -1;
                }

                x++;
            }
            
            // Trim data from right
            trimFlag = true;
            x = masterDataSize[0] - 1;
            while(trimFlag)
            {
                if (x < 0)
                {
                    trimFlag = false;
                    
                } else if (masterData[x][y][z] > absThreshold)
                {
                    trimFlag = false;
                    
                } else
                {
                    masterData[x][y][z] = -1;
                }
                
                x--;
            }
            
        }
        
    }
    
    
}

// Function to output current masterData
// -------------------------------------
void ControlBlock::OutputData()
{
    std::cout << "Current master data:\n";
    
    for (int z=0; z<masterDataSize[2]; z++)
    {
        std::cout << "z = " << z+1 << "\n";
        for (int y=0; y<masterDataSize[1]; y++)
        {
            for (int x=0; x<masterDataSize[0]; x++)
            {
                std::cout << masterData[x][y][z] << "\t";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
}


// ===========
// Const/Destr
// ===========

ControlBlock::ControlBlock()
{
    masterDataSize[0] = 0;
    masterDataSize[1] = 0;
    masterDataSize[2] = 0;
    masterData = 0;
}

ControlBlock::~ControlBlock()
{
    ClearMasterData();
}