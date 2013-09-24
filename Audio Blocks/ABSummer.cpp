//
//  Summer.cpp
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 12/17/12.
//  Copyright (c) 2012 Hariharan Mohanraj. All rights reserved.
//

#include "ABSummer.h"

void ABSummer::Process(std::vector<Buffer>& argTargetBuffers)
{
        // Define the Process() function for Summer class
        // Sums the input buffers and copies the value to all
        // buffers present in argTargetBuffers
    
    
    Buffer tempBuffer(bufferSize);
    
    // Generate the summed buffer
    for (int i=0; i<noInputBuffers; i++)
        tempBuffer.Add(inputBuffers[i]);
    
    // Assign the summed buffer to all output buffers (default one output buffer, but assigned to all just in case)
    for (int i=0; i<noOutputBuffers; i++)
        argTargetBuffers[i].Copy(tempBuffer);
}


ABSummer::ABSummer()    // Default to 2 input channels, 1 output channel, default buffer size
: AudioBlockBase(2,1)
{
    bValidInput = 1;
    bValidOutput = 1;
    bMultipleInput = 0;
}

ABSummer::ABSummer(int argNoInputChannels)  // Set number of input channels to argNoInputChannels
: AudioBlockBase(argNoInputChannels,1)  // Default to 1 output channel, default buffer size
{
    bValidInput = 1;
    bValidOutput = 1;
    bMultipleInput = 0;
}

ABSummer::ABSummer(int argNoInputChannels, int argBufferSize)   // Set buffer size to argBufferSize
: AudioBlockBase(argBufferSize, argNoInputChannels, 1)      // Set number of input channels to argNoInputChannels
{                                                           // Default to 1 output channel
    bValidInput = 1;
    bValidOutput = 1;
    bMultipleInput = 0;
}