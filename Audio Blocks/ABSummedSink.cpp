//
//  ABSummedSink.cpp
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 12/18/12.
//  Copyright (c) 2012 Hariharan Mohanraj. All rights reserved.
//

#include "ABSummedSink.h"


std::vector<Buffer> ABSummedSink::GetSink()
{
    return sinkBuffers;
}

Buffer ABSummedSink::GetSink(int argChannel)
{
    // Check whether valid channel
    if (argChannel < 0 || argChannel >= noInputBuffers)
    {
        std::cout << "Invalid channel number. GetSink() call ignored.\n";
        Buffer tempBuffer(bufferSize);
        return tempBuffer;
    }
    
    return sinkBuffers[argChannel];
}

void ABSummedSink::ClearSink()
{
    for(int i=0; i<noInputBuffers; i++)
        sinkBuffers[i].Clear();
}



//===============================================
// Functions to add and remove input buffers must
// also update number of buffers in sinkBuffers.
// Hence the AddInputBuffer() and RemoveInputBuffer()
// functions are redefined inside ABSummedSink.
//===============================================

void ABSummedSink::AddInputBuffer()
{
    Buffer tempBuffer(bufferSize);
    tempBuffer.Clear();
    sinkBuffers.push_back(tempBuffer);
    
    AudioBlockBase::AddInputBuffer();
    AudioBlockBase::AddOutputBuffer();      // Number of output buffers must match number of input buffers
}

void ABSummedSink::RemoveInputBuffer()
{
    int tempNo = noInputBuffers;
    AudioBlockBase::RemoveInputBuffer();    // Allows AudioBlockBase::RemoveInputBuffer() to take care of
    AudioBlockBase::RemoveOutputBuffer();   // warning messages for empty buffer vectors.
    
    if (tempNo != 0)
        sinkBuffers.pop_back();
    
}



// =====================================
// Specialized audio block functionality
// =====================================

void ABSummedSink::FlowSignal(std::vector<Buffer>& argIncomingBuffers)
{
    // Functionality is changed from AudioBlockBase definition
    // - Replaces functionality of Process()
    // - Adds incoming buffers to sinkBuffers
    // - Input buffers are NOT updated
    // - Output buffers are non-existent, so updating not required
    
    
    // Iteratively add argIncomingBuffers to sinkBuffers
    
    for(int i=0; i<noInputBuffers; i++)
    {
        std::cout << i << ": Trying to add.\n";
        sinkBuffers[i].Add(argIncomingBuffers[i]);
        outputBuffers[i].Copy(sinkBuffers[i]);
    }
    
    
    // Push FlowSignal calls are still made so that this block may serve as a trigger to other blocks
    // However, note that these calls will be made multiple times per buffer iteration, as multiple input
    // buffer sets will trigger ABSummedSink::FlowSignal();
    
    for(int i=0; i<noOutputConnections; i++)
        outputAudioBlocks[i]->FlowSignal(outputBuffers,this);
}



ABSummedSink::ABSummedSink()
: AudioBlockBase(1,1)
{
    sinkBufferSize = BUFFER_SIZE;
    
    sinkBuffers.clear();
    sinkBuffers.push_back(Buffer(sinkBufferSize));
    
    bValidInput = 1;
    bValidOutput = 0;
    bMultipleInput = 1;
}

ABSummedSink::ABSummedSink(int argNoInputChannels)
: AudioBlockBase(argNoInputChannels,argNoInputChannels)
{
    sinkBufferSize = BUFFER_SIZE;
    sinkBuffers.clear();
    for(int i=0;i<argNoInputChannels;i++)
        sinkBuffers.push_back(Buffer(sinkBufferSize));
    
    bValidInput = 1;
    bValidOutput = 0;
    bMultipleInput = 1;
}

ABSummedSink::ABSummedSink(int argNoInputChannels, int argBufferSize)
: AudioBlockBase(argBufferSize, argNoInputChannels, argNoInputChannels)
{
    sinkBufferSize = argBufferSize;
    for(int i=0;i<argNoInputChannels;i++)
        sinkBuffers.push_back(Buffer(sinkBufferSize));
    
    bValidInput = 1;
    bValidOutput = 0;
    bMultipleInput = 1;
}