//
//  SoniEngine.h
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 12/28/12.
//  Copyright (c) 2012 Hariharan Mohanraj. All rights reserved.
//


// ===============================================================
//
// ************ THIS IS FOR AUDIOBLOCK ARCHITECTURE **************
//
// The SoniEngine class only applies to AudioBlock architecture
// ===============================================================


#ifndef __SoniScan_2_0__SoniEngine__
#define __SoniScan_2_0__SoniEngine__

#include <iostream>
#include <vector>

#include "Constants.h"

#include "ABSineGen.h"
#include "ABStereoPanner.h"
#include "ABAmper.h"
#include "ControlBlock.h"
#include "TwoDArray.h"

class ControlBlock;

class SoniEngine
{
    ABSineGen*      sines[MAX_NUM_SINEGENS];
    ABAmper*        ampers[MAX_NUM_AMPERS];
    ABStereoPanner* panners[MAX_NUM_PANNERS];
    ABAmper* twoDAmpers[MAX_NUM_SINEGENS][MAX_NUM_PANNERS];
    
    int numSines;
    int numAmpers;
    int numPanners;
    int numRows;
    int numCols;

    int numChannels;
    ControlBlock* control;
    
    sample* outputBufferL;
    sample* outputBufferR;
    
    float*** masterData;
    int masterDataSize[3];
    
    TwoDArray<float> frameData;
    std::vector<float> lineData;
    
    int mode;   // Mode number determines the structure of the sonification engine blocks
                // 0    :   Linear channels, for 1D sonification
                //          SignalGen -> Amper -> Panner
                //
                // 1    :   Matrixed channels, for 2D sonification
                //          Linear array of signal gens -> 2D array of ampers -> linear array of panners
                //          Hence, y-axis maps to pitch, x-axis maps to stereo image location
    
    float gain;
    
    
public:
    // ControlBlock functions
    void SetControl(ControlBlock*);
    void SetMasterData(float***, int[]);
    
    // Mode getter-setter
    int GetMode();
    void SetMode(int);
    
    // Gain getter-setter
    float GetGain();
    void SetGain(float);
    
    // Pushes and Pops
    void PushSine();            // Push single sine block
    void PopSine();             // Pop single sine block
    void PushSine(int);         // Push/pop to reach num blocks spec as argument
    
    void PushAmper();           // Push single amper block
    void PopAmper();            // Pop single amper block
    void PushAmper(int);        // Push/pop to reach num blocks spec as argument
    
    void PushPanner();          // Push single panner block
    void PopPanner();           // Pop single panner block
    void PushPanner(int);       // Push/pop to reach num blocks spec as argument
    
    void PushTwoDAmperRow();    // Push row of ampers
    void PopTwoDAmperRow();     // Pop row of ampers
    void PushTwoDAmperCol();    // Push col of ampers
    void PopTwoDAmperCol();     // Pop col of ampers
    void PushTwoDAmper(int,int);//Push/pop rows/cols of ampers to specified arguments
    
    void PushChannel();         // Push channel in mode 0
    void PopChannel();          // Pop channel in mode 0
    void PushChannel(int);      // Push/pop to reach num channels spec as argument in mode 0
    
    void PushRow();             // Push row in mode 1
    void PopRow();              // Pop row in mode 1
    void PushCol();             // Push col in mode 1
    void PopCol();              // Pop col in mode 1
    void PushRowsCols(int,int); // Push/pop rows/cols to reach num rows num cols spec as arguments in mode 1
    
    // Getters
    ABSineGen* GetSine(int);
    ABAmper* GetAmper(int);
    ABStereoPanner* GetPanner(int);
    
    int GetNumSines();
    int GetNumAmpers();
    int GetNumPanners();
    int GetNumRows();
    int GetNumCols();
    
    // Output Buffer getter-setter
    void SetOutputBuffers(sample*, sample*);
    sample* GetOutputBufferL();
    sample* GetOutputBufferR();
    
    
    // Updates
    void GlobalUpdate();
    
    void UpdateBlocks();
    void UpdateChannelConnections();
    void UpdateMatrixConnections();
    
    void UpdateSines();
    void UpdatePanners();
    void UpdateAmpers();
    void UpdateTwoDAmpers();
    
    void UpdateFrame(TwoDArray<float>);
    void UpdateData(std::vector<float>);
    
    void BufferCycle();
    
    // Constructors & Destructors
    SoniEngine();
    ~SoniEngine();
    
};


#endif /* defined(__SoniScan_2_0__SoniEngine__) */
