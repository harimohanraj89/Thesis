//
//  AudioBlockBase.cpp
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 12/5/12.
//  Copyright (c) 2012 Hariharan Mohanraj. All rights reserved.
//

#include <iostream>
#include "AudioBlockBase.h"



sample* AudioBlockBase::GetInputBuffer()
{
    return inputBuffer;
}

AudioBlockBase* AudioBlockBase::GetAudioBlock()
{
    return this;
}


void AudioBlockBase::SetNextBuffer(sample* argBuffer)
{
    nextInputBuffer = argBuffer;
}

void AudioBlockBase::PushNextBuffer(sample* argBuffer)
{
    nextInputBuffers.push_back(argBuffer);
}

void AudioBlockBase::PopNextBuffer()
{
    nextInputBuffers.pop_back();
}

void AudioBlockBase::ClearNextBuffers()
{
    nextInputBuffers.clear();
}

// ================================================
// AudioBlock functionality
// ================================================

void AudioBlockBase::BufferFlush()
{
    // Function to flush the input buffer before the next buffer cycle
    
    currInputPtr = inputBuffer;
    
    for (int counter=0; counter<BUFFER_SIZE; counter++)
        *currInputPtr++ = 0;
}

void AudioBlockBase::InternalCopy()
{
    // Function to copy input buffer into internal buffer
    
    currInputPtr    = inputBuffer;
    currInternalPtr = internalBuffer;
    
    for (int counter=0; counter<BUFFER_SIZE; counter++)
        *currInternalPtr++ = *currInputPtr++;
}

void AudioBlockBase::Process()
{
    // Function to generate output buffer from internal buffer
    
    // In base class, this performs a simple copy. Functionality can be added
    // in children classes, as Process() is a virtual function
    
    currInternalPtr = internalBuffer;
    currOutputPtr   = outputBuffer;
    
    for (int counter=0; counter<BUFFER_SIZE; counter++)
        *currOutputPtr++ = *currInternalPtr++;
}

void AudioBlockBase::OutputCopy()
{
    // Function to ADD output buffer to next block's input buffer
    
    currOutputPtr = outputBuffer;
    currNextPtr   = nextInputBuffer;
    
    if (nextInputBuffer)
        for (int counter=0; counter<BUFFER_SIZE; counter++)
            *currNextPtr++ += *currOutputPtr++;
    
    // Perform output copy to each nextBuffer in nextInputBuffers
    int numNextBuffers = nextInputBuffers.size();
    for (int i=0; i<numNextBuffers; i++)
    {
        currOutputPtr = outputBuffer;
        currNextPtr   = nextInputBuffers[i];
        
        if(nextInputBuffers[i])
            for (int counter=0; counter<BUFFER_SIZE; counter++)
                *currNextPtr++ += *currOutputPtr++;
    }
    
}

// ================================================
// Constructors and Destructors
// ================================================

AudioBlockBase::AudioBlockBase()
{
    
    inputBuffer       = new sample [BUFFER_SIZE];
    internalBuffer    = new sample [BUFFER_SIZE];
    outputBuffer      = new sample [BUFFER_SIZE];
    nextInputBuffer   = 0;
    nextInputBuffers.clear();
    
    currInputPtr      = inputBuffer;
    currInternalPtr   = internalBuffer;
    currOutputPtr     = outputBuffer;
    currNextPtr       = nextInputBuffer;
}


AudioBlockBase::~AudioBlockBase()
{
    delete inputBuffer;
    delete internalBuffer;
    delete outputBuffer;
}

