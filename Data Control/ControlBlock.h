//
//  ControlBlock.h
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 11/30/12.
//  Copyright (c) 2012 Hariharan Mohanraj. All rights reserved.
//

#ifndef __SoniScan_2_0__ControlBlock__
#define __SoniScan_2_0__ControlBlock__

#include <iostream>
#include <vector>
#include <string>
#include "SoniEngine.h"

class SoniEngine;

struct rect
{
    // Typedef for a struct to specify a rectangle
    // Contains coordinates of upper-left and
    // lower-right corners of the rectangle
    
    // X bounds of cube
    int x1;
    int x2;
    
    // Y bounds of cube
    int y1;
    int y2;
};

class ControlBlock
{
private:
    // Private members:
    // masterData    :   2D vector object containing entire dataset loaded for sonification
    // selectionArea :   Struct of type "rect" defining the selected area of "data" for sonification
    // rangeMin      :   Type float, specifying the lower bound of the range within which sonified data
    //                   will be scaled
    // rangeMax      :   Type float, specifying the upper bound of the range within which sonified data
    //                   will be scaled
    // shift         :   Type float, specifying the uniform shift applied to the data after the "range" operation
    // volume        :   Type float, specifying the final multiplier applied to the data after "range" and
    //                   "shift" operations
    
    // Master Data
    float*** masterData;
    int masterDataSize[3];
    
    // Selection
    int slice;
    rect selectionArea;
    
    // Processing
    float rangeMin;
    float rangeMax;
    
    // Sonification engine connection
    SoniEngine* engine;
    
    // Utility functions
    int ArrayMax(int*,int);
    int ArrayMin(int*,int);
    void ClearMasterData();
    void InitMasterData(int,int,int);
    void TrimMasterData();
    
    char dataFilename[MAX_SCORELINE_LENGTH];
    
public:
    //Public members:
    
    // Get-Set Data Selection
    void SetSlice(int);
    int GetSlice();
    
    void SetSelectionArea(int,int,int,int);
    void SetSelectionArea(std::string, int);
    void SetSelectionArea(std::string, int, std::string, int);
    void SetSelectionArea(std::string, int, std::string, int, std::string, int);
    void SetSelectionArea(std::string, int, std::string, int, std::string, int, std::string, int);
    int GetSelectionArea(std::string);
    void ClipSelectionArea();
    
    // Get-Set Processing Parameters
    void SetRangeMin(float);
    void SetRangeMax(float);
    float GetRangeMin();
    float GetRangeMax();
    
    
    // Get-Set Engine connectors
    SoniEngine* GetEngine();
    void SetEngine(SoniEngine*);
    
    // Data interface functions
    void ReadFile(char*);
    void OutputData();
    
    // Const/Destr
    ControlBlock();
    ~ControlBlock();

};

#endif /* defined(__SoniScan_2_0__ControlBlock__) */