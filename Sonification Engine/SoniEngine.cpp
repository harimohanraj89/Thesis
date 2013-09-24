//
//  SoniEngine.cpp
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


#include "SoniEngine.h"
#include <math.h>

// ===========================
// ControlBlock functions
// ===========================

void SoniEngine::SetControl(ControlBlock* incomingControlBlock) {
    control = incomingControlBlock;
}

void SoniEngine::SetMasterData(float*** argMasterData, int argMasterDataSize[]) {
    masterData = argMasterData;
    for (int i=0; i<3; i++) {
        masterDataSize[i] = argMasterDataSize[i];
    }
}

// ===========================
// Mode Getter-Setter
// ===========================

int SoniEngine::GetMode()
{
    return mode;
}

void SoniEngine::SetMode(int argMode)
{
    switch (argMode)
    {
        case 0:
        {
            int flag = 0;
            if (mode != 0)
                flag = 1;
            
            mode = 0;
            if (flag)
            {
                // Make sure to reset connections and clear all blocks
                UpdateBlocks();
            }
            break;
        }
        case 1:
        {
            int flag = 0;
            if (mode != 1)
                flag = 1;
            
            mode = 1;
            if (flag)
            {
                // Make sure to reset connections and clear all blocks
                UpdateBlocks();
            }
            break;
        }
            
        default:
        {
            std::cout << argMode << " is not a valid mode. SetMode() call ignored.\n";
            break;
        }
    }
}

// ===========================
// Mode Getter-Setter
// ===========================

float SoniEngine::GetGain() {
    return gain;
}

void SoniEngine::SetGain(float argGain) {
    float lGain;
    argGain > 1 ? lGain = 1 : lGain = argGain;
    lGain < 0 ? lGain = 1 : lGain = lGain;
    gain = lGain;
}

// ===========================
// Pushing and Popping blocks
// ===========================

// Sine blocks
// ---------------
void SoniEngine::PushSine()
{
    if (numSines == MAX_NUM_SINEGENS)
    {
        std::cout << "Maximum number of sine blocks. PushSine() call ignored.\n";
        return;
    }

    sines[numSines] = new ABSineGen();
    numSines++;
}

void SoniEngine::PopSine()
{
    if (numSines == 0)
    {
        std::cout << "No sine blocks to pop. PopSine() call ignored.\n";
        return;
    }
    
    
    delete sines[numSines-1];
    sines[numSines-1] = 0;
    numSines--;
}

void SoniEngine::PushSine(int argNumBlocks)
{
    if (argNumBlocks > MAX_NUM_SINEGENS)
    {
        std::cout << "Argument exceeds maximum number of sine blocks. PushSine() call ignored.\n";
        return;
    }
    
    if (argNumBlocks < 0)
    {
        std::cout << "Argument must be positive. PushSine() call ignored.\n";
        return;
    }
    
    while (numSines > argNumBlocks)
        PopSine();
    while (numSines < argNumBlocks)
        PushSine();
}

// Amper blocks
// ---------------
void SoniEngine::PushAmper()
{
    if (numAmpers == MAX_NUM_AMPERS)
    {
        std::cout << "Maximum number of amper blocks. PushAmper() call ignored.\n";
        return;
    }
    
    ampers[numAmpers] = new ABAmper();
    numAmpers++;
}

void SoniEngine::PopAmper()
{
    if (numAmpers == 0)
    {
        std::cout << "No amper blocks to pop. PopAmper() call ignored.\n";
        return;
    }

    delete ampers[numAmpers-1];
    ampers[numAmpers-1] = 0;
    numAmpers--;
}

void SoniEngine::PushAmper(int argNumBlocks)
{
    if (argNumBlocks > MAX_NUM_AMPERS)
    {
        std::cout << "Argument exceeds maximum number of amper blocks. PushAmper() call ignored.\n";
        return;
    }
    
    if (argNumBlocks < 0)
    {
        std::cout << "Argument must be positive. PushAmper() call ignored.\n";
        return;
    }
    
    while (numAmpers > argNumBlocks)
        PopAmper();
    while (numAmpers < argNumBlocks)
        PushAmper();
}

// Panner blocks
// ---------------
void SoniEngine::PushPanner()
{
    if (numPanners == MAX_NUM_AMPERS)
    {
        std::cout << "Maximum number of panner blocks. PushPanner() call ignored.\n";
        return;
    }
    panners[numPanners] = new ABStereoPanner();
    numPanners++;
}

void SoniEngine::PopPanner()
{
    if (numPanners == 0)
    {
        std::cout << "No panner blocks to pop. PopPanner() call ignored.\n";
        return;
    }
    
    delete panners[numPanners-1];
    panners[numPanners-1] = 0;
    numPanners--;
}

void SoniEngine::PushPanner(int argNumBlocks)
{
    if (argNumBlocks > MAX_NUM_PANNERS)
    {
        std::cout << "Argument exceeds maximum number of panner blocks. PushPanner() call ignored.\n";
        return;
    }
    
    if (argNumBlocks < 0)
    {
        std::cout << "Argument must be positive. PushPanner() call ignored.\n";
        return;
    }
    
    while (numPanners > argNumBlocks)
        PopPanner();
    while (numPanners < argNumBlocks)
        PushPanner();
}

// Two D Ampers
// --------------

void SoniEngine::PushTwoDAmperRow()
{
    for(int j=0; j<numCols; j++)
    {
        twoDAmpers[numRows][j] = new ABAmper();
    }
    
    // Update numRows
    numRows++;
}

void SoniEngine::PopTwoDAmperRow()
{
    for(int j=0; j<numCols; j++)
    {
        delete twoDAmpers[numRows-1][j];
        twoDAmpers[numRows-1][j] = 0;
    }
    
    // Update numRows
    numRows--;
}

void SoniEngine::PushTwoDAmperCol()
{
    for(int i=0; i<numRows; i++)
    {
        twoDAmpers[i][numCols] = new ABAmper();
    }
    
    // Update numCols and display
    numCols++;
}

void SoniEngine::PopTwoDAmperCol()
{
    for(int i=0; i<numRows; i++)
    {
        delete twoDAmpers[i][numCols-1];
        twoDAmpers[i][numCols-1] = 0;
    }
    
    // Update numCols
    numCols--;
}

void SoniEngine::PushTwoDAmper(int argNoRows, int argNoCols)
{
    // Error checking
    
    if (argNoRows > MAX_NUM_SINEGENS)
    {
        std::cout << "Row argument exceeds maximum number of rows. PushRowsCols() call ignored.\n";
        return;
    }
    
    if (argNoCols > MAX_NUM_PANNERS)
    {
        std::cout << "Col argument exceeds maximum number of cols. PushRowsCols() call ignored.\n";
        return;
    }
    
    if (argNoRows < 0)
    {
        std::cout << "Row argument must be positive. PushRowsCols() call ignored.\n";
        return;
    }
    
    if (argNoCols < 0)
    {
        std::cout << "Col argument must be positive. PushRowsCols() call ignored.\n";
        return;
    }
    
    while (numRows > argNoRows)
        PopTwoDAmperRow();
    while (numRows < argNoRows)
        PushTwoDAmperRow();
    
    while (numCols > argNoCols)
        PopTwoDAmperCol();
    while (numCols < argNoCols)
        PushTwoDAmperCol();
}

// Channels
// --------------
void SoniEngine::PushChannel()
{
    if (numChannels == MAX_NUM_CHANNELS)
    {
        std::cout << "Maximum number of channels. PushChannel() call ignored.\n";
        return;
    }
    
    PushSine();
    PushAmper();
    PushPanner();
    
    numChannels++;
    std::cout << "Number of channels: " << numChannels << "\n";
}

void SoniEngine::PopChannel()
{
    if(numChannels == 0)
    {
        std::cout << "No channels to pop. PopChannel() call ignored.\n";
        return;
    }
    
    PopSine();
    PopAmper();
    PopPanner();
    numChannels--;
    std::cout << "Number of channels: " << numChannels << "\n";
}

void SoniEngine::PushChannel(int argNoChannels)
{
    if (argNoChannels > MAX_NUM_CHANNELS)
    {
        std::cout << "Argument exceeds maximum number of channels. PushChannel() call ignored.\n";
        return;
    }
    
    if (argNoChannels < 0)
    {
        std::cout << "Argument must be positive. PushChannel() call ignored.\n";
        return;
    }
    
    PushSine(argNoChannels);
    PushAmper(argNoChannels);
    PushPanner(argNoChannels);
    
    numChannels = argNoChannels;
}


// Rows and Columns
// -------------------

void SoniEngine::PushRow()
{
    // Check for max num sine gens
    if (numRows == MAX_NUM_SINEGENS)
    {
        std::cout << "Maximum number of sine gens. PushRow() call ignored.\n";
        return;
    }
    
    // Perform push of sine gen and row of ampers
    PushSine();
    PushTwoDAmperRow();
}

void SoniEngine::PopRow()
{
    // Check for no sine gens
    if (numRows == 0)
    {
        std::cout << "Nothing to pop. PopRow() call ignored.\n";
        return;
    }
    
    // Perform pop of sine gen and row of ampers
    PopSine();
    PopTwoDAmperRow();
}

void SoniEngine::PushCol()
{
    // Check for max num panners
    if (numCols == MAX_NUM_PANNERS)
    {
        std::cout << "Maximum number of panners. PushCol() call ignored.\n";
        return;
    }
    
    // Perform push of panner and column of ampers
    PushPanner();
    PushTwoDAmperCol();
}

void SoniEngine::PopCol()
{
    // Check for no sine gens
    if (numCols == 0)
    {
        std::cout << "Nothing to pop. PopCol() call ignored.\n";
        return;
    }
    
    // Perform pop of panner and col of ampers
    PopPanner();
    PopTwoDAmperCol();
}

void SoniEngine::PushRowsCols(int argNoRows, int argNoCols)
{
    // Error checking
    std::cout << argNoRows << "\t" << argNoCols;
    if (argNoRows > MAX_NUM_SINEGENS)
    {
        std::cout << "Row argument exceeds maximum number of rows. PushRowsCols() call ignored.\n";
        return;
    }
    
    if (argNoCols > MAX_NUM_PANNERS)
    {
        std::cout << "Col argument exceeds maximum number of cols. PushRowsCols() call ignored.\n";
        return;
    }
    
    if (argNoRows < 0)
    {
        std::cout << "Row argument must be positive. PushRowsCols() call ignored.\n";
        return;
    }
    
    if (argNoCols < 0)
    {
        std::cout << "Col argument must be positive. PushRowsCols() call ignored.\n";
        return;
    }
    
    // Perform pushes/pops to reach argument values
    
    // Rows
    PushSine(argNoRows);
    PushPanner(argNoCols);
    PushTwoDAmper(argNoRows,argNoCols);
}

// ===========================
// Getters
// ===========================

// Get blocks
// ------------
ABSineGen* SoniEngine::GetSine(int argIndex)
{
    if (argIndex < 0)
    {
        std::cout << "Invalid index! GetSine() call returned null pointer.\n";
        return 0;
    }
    
    if (argIndex >= numSines)
    {
        std::cout << "Index too high! Not enough blocks. GetSine() call returned null pointer.\n";
        return 0;
    }
    
    return sines[argIndex];
}

ABAmper* SoniEngine::GetAmper(int argIndex)
{
    if (argIndex < 0)
    {
        std::cout << "Invalid index! GetAmper() call returned null pointer.\n";
        return 0;
    }
    
    if (argIndex >= numAmpers)
    {
        std::cout << "Index too high! Not enough blocks. GetAmper() call returned null pointer.\n";
        return 0;
    }
    
    return ampers[argIndex];
}

ABStereoPanner* SoniEngine::GetPanner(int argIndex)
{
    if (argIndex < 0)
    {
        std::cout << "Invalid index! GetPanner() call returned null pointer.\n";
        return 0;
    }
    
    if (argIndex >= numPanners)
    {
        std::cout << "Index too high! Not enough blocks. GetPanner() call returned null pointer.\n";
        return 0;
    }
    
    return panners[argIndex];
}


// Get number of blocks
// -------------------------
int SoniEngine::GetNumSines()
{
    return numSines;
}

int SoniEngine::GetNumAmpers()
{
    return numAmpers;
}

int SoniEngine::GetNumPanners()
{
    return numPanners;
}

int SoniEngine::GetNumRows()
{
    return numRows;
}

int SoniEngine::GetNumCols()
{
    return numCols;
}

// ===========================
// Output Buffer getter-setter
// ===========================

void SoniEngine::SetOutputBuffers(sample* argOutputBufferL, sample* argOutputBufferR)
{
    outputBufferL = argOutputBufferL;
    outputBufferR = argOutputBufferR;
    for (int i=0; i<numPanners; i++)
    {
        panners[i]->SetNextBuffer(outputBufferL);
        panners[i]->SetNextBufferR(outputBufferR);
    }
}

sample* SoniEngine::GetOutputBufferL()
{
    return outputBufferL;
}

sample* SoniEngine::GetOutputBufferR()
{
    return outputBufferR;
}
// ===========================
// Updates
// ===========================

void SoniEngine::GlobalUpdate()
{
    
}

void SoniEngine::UpdateBlocks()
{
    switch (mode)
    {
        case 0:
        {
            std::cout << "Updating for mode 0...\n";
            PushChannel(lineData.size());
            UpdateSines();
            UpdateAmpers();
            UpdatePanners();
            UpdateChannelConnections();
            std::cout << "Updated.\nNum Sines:   " << numSines << "\nNum Ampers:  " << numAmpers << "\n";
            std::cout << "Num Panners: " << numPanners << "\nNum Rows:    " << numRows << "\nNum Cols:    " << numCols << "\n";
            
            break;
        }
            
        case 1:
        {
            std::cout << "Updating for mode 1...\n";
            PushRowsCols(control->GetSelectionArea("x2") - control->GetSelectionArea("x1") + 1, control->GetSelectionArea("y2") - control->GetSelectionArea("y1") + 1);
            UpdateSines();
            UpdateTwoDAmpers();
            UpdatePanners();
            UpdateMatrixConnections();
            std::cout << "Updated.\nNum Sines:   " << numSines << "\nNum Ampers:  " << numAmpers << "\n";
            std::cout << "Num Panners: " << numPanners << "\nNum Rows:    " << numRows << "\nNum Cols:    " << numCols << "\n";
            break;
        }
            
        default:
        {
            std::cout << "CRITICAL ERROR: Mode is out of bounds.\n";
            break;
        }
    }
}


// Connection update functions
// ---------------------------
void SoniEngine::UpdateChannelConnections()
{
    if (numSines != numAmpers || numAmpers != numPanners)
    {
        std::cout << "CRITICAL ERROR: Block numbers mismatch in UpdateChannelConnections().\n";
        return;
    }
    
    // Function to update connections in channel mode
    for (int i=0; i<numChannels; i++)
    {
        sines[i]->ClearNextBuffers();
        sines[i]->SetNextBuffer(ampers[i]->GetInputBuffer());
        ampers[i]->SetNextBuffer(panners[i]->GetInputBuffer());
        panners[i]->SetNextBuffer(outputBufferL);
        panners[i]->SetNextBufferR(outputBufferR);
    }
}

void SoniEngine::UpdateMatrixConnections()
{
    if (numSines != numRows || numPanners != numCols)
    {
        std::cout << "CRITICAL ERROR: Block numbers mismatch in UpdateMatrixConnections().\n";
        return;
    }
    
    // Function to update connections in matrix mode
    for (int i=0; i<numRows; i++)
    {
        sines[i]->ClearNextBuffers();
        sines[i]->SetNextBuffer(0);
        
        for (int j=0; j<numCols; j++)
        {
            sines[i]->PushNextBuffer(twoDAmpers[i][j]->GetInputBuffer());
            twoDAmpers[i][j]->SetNextBuffer(panners[j]->GetInputBuffer());
            if (i == 0)
            {
                panners[j]->SetNextBuffer(outputBufferL);
                panners[j]->SetNextBuffer(outputBufferR);
            }
        }
        
    }
}


// Update block properties
// -----------------------
void SoniEngine::UpdateSines()
{
    // Updates frequencies of all existing sine blocks
    // Currently starts at 330Hz and proceeds in increments of fourths
    std::cout << "Updating sine freqs...\n";
    float freq;
    for (int i=0; i<numSines; i++)
    {
        freq = pow(INIT_FREQ, (numSines-i-1.0)/(numSines-1.0) ) * pow(FINAL_FREQ, i/(numSines-1.0) );
        std::cout << "Freq : " << freq << "\n";
        sines[i]->SetFrequency( freq );
    }
}

void SoniEngine::UpdateAmpers()
{
    // Updates amplitudes of all exisiting amper blocks
    
    for (int i=0; i<numAmpers; i++)
        ampers[i]->SetAmplitude(lineData[i]);
}

void SoniEngine::UpdatePanners()
{
    // Updates pan angles of all exisiting panner blocks
    // Currently pans existing blocks uniformly from -1 to +1
    float angle;
    if (numPanners == 1)
    {
        panners[0]->SetPanAngle(0);
        return;
    }
    
    for (int i=0; i<numPanners; i++) {
        angle = 2.0*i/(numPanners) - 1 + 1.0/numPanners;
        std::cout << "Angle: " << angle << "\n";
        panners[i]->SetPanAngle( angle );
    }
}

void SoniEngine::UpdateTwoDAmpers()
{
    float amplitude;
    // Updates amplitudes of all existing 2D amper blocks
    for (int i=0;i<numRows;i++)
    {
        for(int j=0; j<numCols; j++)
        {
            amplitude = (masterData[control->GetSelectionArea("x1")+j][control->GetSelectionArea("y1")+i][control->GetSlice()]) / pow(2,DATA_BITDEPTH);
            twoDAmpers[i][j]->SetAmplitude(gain * amplitude);
        }
    }
}


// Update base data functions
// --------------------------
void SoniEngine::UpdateData(std::vector<float> argData)
{
    lineData = argData;
    UpdateBlocks();
}

void SoniEngine::UpdateFrame(TwoDArray<float> argIncomingFrame)
{
    frameData = argIncomingFrame;
    UpdateBlocks();
}


// Buffer cycle function
// ---------------------
void SoniEngine::BufferCycle()
{
    // Performs one buffer cycle of all blocks
    int i;
    
    // Internal Copy
    for (i=0; i<numSines; i++)
        sines[i]->InternalCopy();
    
    for (i=0; i<numAmpers; i++)
        ampers[i]->InternalCopy();
    
    for (i=0; i<numPanners; i++)
        panners[i]->InternalCopy();
    
    // Buffer Flush
    for (i=0; i<numSines; i++)
        sines[i]->BufferFlush();
    
    for (i=0; i<numAmpers; i++)
        ampers[i]->BufferFlush();
    
    for (i=0; i<numPanners; i++)
        panners[i]->BufferFlush();
    
    // Output Copy
    for (i=0; i<numSines; i++)
        sines[i]->OutputCopy();
    
    for (i=0; i<numAmpers; i++)
        ampers[i]->OutputCopy();
    
    for (i=0; i<numPanners; i++)
        panners[i]->OutputCopy();
    
    // Process
    for (i=0; i<numSines; i++)
        sines[i]->Process();
    
    for (i=0; i<numAmpers; i++)
        ampers[i]->Process();
    
    for (i=0; i<numPanners; i++)
        panners[i]->Process();
    
}

// ===============================
// Constructors and Destructors
// ===============================

SoniEngine::SoniEngine()
{
    
    // Start with zero blocks (initialize all pointers to null)
    int i;
    int j;
    
    for (i=0; i<MAX_NUM_SINEGENS; i++)
        sines[i] = 0;
    for (i=0; i<MAX_NUM_AMPERS; i++)
        ampers[i] = 0;
    for (i=0; i<MAX_NUM_PANNERS; i++)
        panners[i] = 0;
    
    for(i=0; i<MAX_NUM_SINEGENS; i++)
        for(j=0; j<MAX_NUM_PANNERS; j++)
            twoDAmpers[i][j] = 0;
    
    // Set all numBlocks to 0
    numSines = 0;
    numAmpers = 0;
    numPanners = 0;
    numChannels = 0;
    numRows = 0;
    numCols = 0;
    
    // Set mode to 0 by default
    mode = 0;
    gain = 0.1;
}

SoniEngine::~SoniEngine()
{
    while (numSines > 0)
        PopSine();
    while (numAmpers > 0)
        PopAmper();
    while (numPanners > 0)
        PopPanner();
}
