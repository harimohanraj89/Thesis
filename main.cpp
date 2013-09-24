//
//  main.cpp
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 11/30/12.
//  Copyright (c) 2012 Hariharan Mohanraj. All rights reserved.
//

#include <iostream>
#include <fstream>

#include <stdio.h>
#include <math.h>
#include <vector>
#include <string>

#include "ControlBlock.h"
#include "SoniEngine.h"

using namespace std;

int main(void);
int main(void)
{   
    
//================================================================================
    
    // ================================
    // FILE AND STRING TESTING GROUNDS
    // ================================
    
    int parameterInput;
    char charInput[128];
    int batchFlag = 0;
    strcpy(charInput,"test_a");
    
    ControlBlock control;
    SoniEngine engine;
    
    control.SetEngine(&engine);
    char dataLine[MAX_SCORELINE_LENGTH];
    sprintf(dataLine,TEST_DATA_PATH TEST_DATA_FILENAME_1 ".txt");
    control.ReadFile("test_a");
    
    // ================================
    // TESTING GROUNDS
    // ================================

    cout << "\nHere we go...\n";
    
    engine.SetMode(1);
    engine.UpdateBlocks();

    // ================================
    // USER INTERFACE
    // ================================
    
    char userInput;
    
    do
    {
        cout << "Enter input: ";
        
        cin >> userInput;
        
        switch (userInput)
        {
                
        }
        
    }while (userInput != 'x' && userInput != 'p');
    
}

