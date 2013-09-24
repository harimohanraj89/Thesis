//
//  ABBlockSummer.cpp
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 12/31/12.
//  Copyright (c) 2012 Hariharan Mohanraj. All rights reserved.
//

#include "ABBlockSummer.h"

void ABBlockSummer::Process(std::vector<Buffer>&)
{
    
}

void ABBlockSummer::FlowSignal(std::vector<Buffer>& argIncomingBuffers, AudioBlockBase* argInstigator)
{

    // Performs a buffer iteration
    //
    // - Pushes output buffer to output connections
    // - Processes input through Process() and pushes result into output buffer
    // - Accepts incoming buffers (argIncomingBuffers) into input buffer
    
    
    // Add incoming buffer to summedBuffers
    
    for(int i=0; i<noInputBuffers; i++)
    {
        summedBuffers[i].Add(argIncomingBuffers[i]);
    }
    
    
    // Flip flag for corresponding input block
    
    int noInputBlocks = inputAudioBlock.size();
    
    for(int i=0; i<noInputBlocks; i++)
    {
        if (inputAudioBlock[i] == argInstigator)
        {
            inputFlags[i] = 1;
        }
    }

    
    // DEBUG
    for (int j=0; j<noInputBlocks; j++)
    {
        std::cout << inputFlags[j] << "\t";
    }
    std::cout << "\n";
    
    // Check if any flags are unflipped
    // If flags are unflipped, return, and wait till all flags are flipped before pushing output
    
    for(int i=0; i<noInputBlocks; i++)
    {
        if (inputFlags[i] != 1)
        {
            return;
        }
    }
    
    // IF ALL INPUT FLAGS ARE 1, PROCEED TO PUSH OUTPUT AND RESET flags and summedBuffers
    
    // Push output stream and trigger all output blocks to execute their respective FlowSignal() calls
    for(int i=0; i<noOutputConnections; i++)
        outputAudioBlocks[i]->FlowSignal(summedBuffers, this);
    
    for(int i=0; i<noInputBuffers; i++)
    {
        summedBuffers[i].Clear();
    }
    
    for(int i=0; i<noInputBlocks; i++)
    {
        inputFlags[i] = 0;
    }
}


void ABBlockSummer::AddInputBuffer()
{
    AudioBlockBase::AddInputBuffer();
    AudioBlockBase::AddOutputBuffer();          // Number of output buffers must match number of input buffers
}

void ABBlockSummer::RemoveInputBuffer()
{
    AudioBlockBase::RemoveInputBuffer();
    AudioBlockBase::RemoveOutputBuffer();       // Number of output buffers must match number of input buffers
}

void ABBlockSummer::AddOutputBuffer()
{
    AudioBlockBase::AddInputBuffer();
    AudioBlockBase::AddOutputBuffer();          // Number of output buffers must match number of input buffers
}

void ABBlockSummer::RemoveOutputBuffer()
{
    AudioBlockBase::RemoveInputBuffer();
    AudioBlockBase::RemoveOutputBuffer();       // Number of output buffers must match number of input buffers
}


ABBlockSummer::ABBlockSummer()
: AudioBlockBase(1,1)
{
    Buffer tempBuffer(bufferSize);
    tempBuffer.Clear();
    int i = 0;
    
    summedBuffers.push_back(tempBuffer);
    inputFlags.push_back(i);
    
    
    bValidInput = 1;
    bValidOutput = 1;
    bMultipleInput = 1;
}

ABBlockSummer::ABBlockSummer(int argNoChannels)
: AudioBlockBase(argNoChannels, argNoChannels)
{
    Buffer tempBuffer(bufferSize);
    tempBuffer.Clear();
    int i = 0;
    
    for (int n=0; n<argNoChannels; n++)
    {
        summedBuffers.push_back(tempBuffer);
        inputFlags.push_back(i);
    }
    
    bValidInput = 1;
    bValidOutput = 1;
    bMultipleInput = 1;
}

ABBlockSummer::ABBlockSummer(int argNoChannels, int argBufferSize)
: AudioBlockBase(argBufferSize, argNoChannels, argNoChannels)
{
    Buffer tempBuffer(bufferSize);
    tempBuffer.Clear();
    int i = 0;
    
    for (int n=0; n<argNoChannels; n++)
    {
        summedBuffers.push_back(tempBuffer);
        inputFlags.push_back(i);
    }
    
    bValidInput = 1;
    bValidOutput = 1;
    bMultipleInput = 1;
}