//
//  ABAmper.cpp
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 12/28/12.
//  Copyright (c) 2012 Hariharan Mohanraj. All rights reserved.
//

#include "ABAmper.h"
#include "../Constants.h"

ABAmper* ABAmper::GetAudioBlock()
{
    return this;
}

float ABAmper::GetAmplitude()
{
        // Function to return current amplitude factor
    
    return amplitudeFactor;
}

void ABAmper::SetAmplitude(float argAmpFactor)
{
        // Function to set amplitude factor to argAmpFactor
    
    amplitudeFactor = argAmpFactor;
}


void ABAmper::Process()
{
        // Process() functionality
        // Implementation of multiplying input signal by amplitude factor
        // and sending to output
    currInternalPtr = internalBuffer;
    currOutputPtr   = outputBuffer;
    
    currInputPtr = inputBuffer;
    
    for (int counter=0; counter<BUFFER_SIZE; counter++)
        *currOutputPtr++ = *currInternalPtr++ * amplitudeFactor;
}



ABAmper::ABAmper()
{
    amplitudeFactor = 1.0;
}

ABAmper::ABAmper(float argAmpFactor)
{
    amplitudeFactor = argAmpFactor;
}
