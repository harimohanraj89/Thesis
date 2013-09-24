//
//  Panner.cpp
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 12/11/12.
//  Copyright (c) 2012 Hariharan Mohanraj. All rights reserved.
//

#include "ABStereoPanner.h"
#include <math.h>
#include "../Constants.h"

//===========================
// Getters and Setters
//===========================
ABStereoPanner* ABStereoPanner::GetAudioBlock()
{
    return this;
}


float ABStereoPanner::GetPanAngle()
{
        // Function to return current pan angle
        // ------------------------------------
    
    return panAngle;
}


void ABStereoPanner::SetPanAngle(float argPanAngle)
{
        // Function to set pan angle to argPanAngle
        // ----------------------------------------
    
    // Check whether valid angle
    argPanAngle > 1 ? argPanAngle = 1 : argPanAngle = argPanAngle;
    argPanAngle < -1? argPanAngle = -1: argPanAngle = argPanAngle;
    
    panAngle = argPanAngle;
    FactorCalc();
}

void ABStereoPanner::SetNextBufferR(sample* argBufferR)
{
    nextInputBufferR = argBufferR;
}


//============================
// L and R factor calculation
//============================

void ABStereoPanner::FactorCalc()
{
    float radians = (panAngle+1)*PI/4;
    lFactor = cos(radians);
    rFactor = sin(radians);
}


//===========================
// Process() definition
//===========================

void ABStereoPanner::InternalCopy()
{
    currInputPtr = inputBuffer;
    currInternalPtr = internalBuffer;
    currInternalPtrR   = internalBufferR;
    
    for (counter=0; counter<BUFFER_SIZE; counter++)
    {
        *currInternalPtr++ = *currInputPtr;
        *currInternalPtrR++ = *currInputPtr++;
    }
}

void ABStereoPanner::Process()
{
    // Process function of the StereoPanner block will only pan the first input buffer to the outputs
    // If more than two outputs are present, the panner block will split the L and R channels evenly
    // among first and second halves of channels
    currInternalPtr = internalBuffer;
    currOutputPtr   = outputBuffer;
    
    currInternalPtrR = internalBufferR;
    currOutputPtrR   = outputBufferR;
    
    for (counter=0; counter<BUFFER_SIZE; counter++)
    {
        *currOutputPtr++ = *currInternalPtr++ * lFactor;
        *currOutputPtrR++ = *currInternalPtrR++ * rFactor;
    }
}

void ABStereoPanner::OutputCopy()
{
    currOutputPtr = outputBuffer;
    currNextPtr = nextInputBuffer;
    
    currOutputPtrR = outputBufferR;
    currNextPtrR = nextInputBufferR;
    
    for (counter=0; counter<BUFFER_SIZE; counter++)
    {
        *currNextPtr++ += *currOutputPtr++;
        *currNextPtrR++ += *currOutputPtrR++;
    }
}

//===========================
// Constructors
//===========================

ABStereoPanner::ABStereoPanner()
{
    panAngle = 0;
    FactorCalc();
    
    internalBufferR = new sample[BUFFER_SIZE];
    outputBufferR = new sample[BUFFER_SIZE];
    
    currInternalPtrR = internalBufferR;
    currOutputPtrR = outputBufferR;
    currNextPtrR = nextInputBufferR;
}

ABStereoPanner::ABStereoPanner(float argPanAngle)
{
    if (argPanAngle < -1 || argPanAngle > 1)
    {
        std::cout << "Invalid pan angle. Pan angle set to 0 by default.\n";
        panAngle = 0;
    }else{
        panAngle = argPanAngle;
    }
    FactorCalc();
    
    internalBufferR = new sample[BUFFER_SIZE];
    outputBufferR = new sample[BUFFER_SIZE];
    
    currInternalPtrR = internalBufferR;
    currOutputPtrR = outputBufferR;
    currNextPtrR = nextInputBufferR;
}

ABStereoPanner::~ABStereoPanner()
{
    delete internalBufferR;
    delete outputBufferR;
}