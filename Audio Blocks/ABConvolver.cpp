//
//  ABConvolver.cpp
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 12/19/12.
//  Copyright (c) 2012 Hariharan Mohanraj. All rights reserved.
//

#include "ABConvolver.h"


void ABConvolver::Process(std::vector<Buffer>& argTargetBuffers)
{
    if (noOutputBuffers == 0)
        return;
    
    Buffer tempOverflowBuffer(memoryBuffers[0]);
    Buffer tempIRBuffer(impulseResponses[0]);
    
    for (int ch=0; ch<noOutputBuffers; ch++)
    {
        for(int i=0; i<bufferSize; i++)
        {
            tempOverflowBuffer.Add(impulseResponses[ch], inputBuffers[0].Get(i), i);
        }
        argTargetBuffers[ch].Clear();
        
        tempOverflowBuffer.Add(memoryBuffers[ch]);
        
        argTargetBuffers[ch].Add(tempOverflowBuffer,0);
        
        memoryBuffers[ch].Clear();
        memoryBuffers[ch].Copy(tempOverflowBuffer,bufferSize);
    }
}


int ABConvolver::GetImpulseResponseLength()
{
    return impulseResponseLength;
}

void ABConvolver::SetImpulseResponseLength(int argImpRespLength)
{
    if (noOutputBuffers != 0)
    {
        std::cout << "Output buffers still exist. Impulse response length can only be changed when output buffers are cleared. SetImpulseResponseLength() call ignored.\n";
        return;
    }
    
    if (argImpRespLength <= 0)
    {
        std::cout << "Invalid impulse response length. SetImpulseResponseLength() call ignored.\n";
        return;
    }
    
    impulseResponseLength = argImpRespLength;
    memoryBufferLength = impulseResponseLength + bufferSize - 1;
}


void ABConvolver::SetImpulseResponse(Buffer argIR, int argIndex)
{
    // Check if valid index
    
    if (argIndex < 0 || argIndex >= noOutputBuffers)
    {
        std::cout << "Invalid impulse response index. SetImpulseResponse() call ignored.\n";
        return;
    }
    
    // Check for size mismatch
    
    if (argIR.Size() != impulseResponseLength)
    {
        std::cout << "Size mismatch. SetImpulseResponse() call ignored.\n";
        return;
    }
    
    // Assign impulse response at argIndex to argIR
    
    impulseResponses[argIndex].Copy(argIR);
    
}

std::vector<Buffer> ABConvolver::GetImpulseResponses()
{
    return impulseResponses;
}




void ABConvolver::AddOutputBuffer()
{
    Buffer emptyBuffer(impulseResponseLength);
    Buffer emptyBuffer2(memoryBufferLength);
    
    impulseResponses.push_back(emptyBuffer);
    memoryBuffers.push_back(emptyBuffer2);
    
    AudioBlockBase::AddOutputBuffer();
}

void ABConvolver::RemoveOutputBuffer()
{
    int tempNo = noOutputBuffers;
    
    AudioBlockBase::RemoveOutputBuffer();
    
    if (tempNo != 0)
    {
        impulseResponses.pop_back();
        memoryBuffers.pop_back();
    }
}


ABConvolver::ABConvolver()
: AudioBlockBase(1,1)
{
    Buffer emptyBuffer(bufferSize);
    Buffer emptyBuffer2(bufferSize);
    Buffer emptyBuffer3(2*bufferSize - 1);
    
    inputBuffers.push_back(emptyBuffer);
    
    outputBuffers.push_back(emptyBuffer);
    impulseResponses.push_back(emptyBuffer2);
    memoryBuffers.push_back(emptyBuffer3);
    
    impulseResponseLength = bufferSize;
    memoryBufferLength =  2*bufferSize - 1;
    
    bValidInput = 1;
    bValidOutput = 1;
    bMultipleInput = 0;

}

ABConvolver::ABConvolver(int argImpulseResponseLength)
: AudioBlockBase(1,1)
{
    Buffer emptyBuffer(bufferSize);
    Buffer emptyBuffer2(argImpulseResponseLength);
    Buffer emptyBuffer3(bufferSize + argImpulseResponseLength - 1);
    
    inputBuffers.push_back(emptyBuffer);

    outputBuffers.push_back(emptyBuffer);
    impulseResponses.push_back(emptyBuffer2);
    memoryBuffers.push_back(emptyBuffer3);

    impulseResponseLength = argImpulseResponseLength;
    memoryBufferLength = argImpulseResponseLength + bufferSize - 1;
    
    bValidInput = 1;
    bValidOutput = 1;
    bMultipleInput = 0;
}

ABConvolver::ABConvolver(int argImpulseResponseLength, int argNoOutputChannels)
: AudioBlockBase(1, argNoOutputChannels)
{
    Buffer emptyBuffer(bufferSize);
    Buffer emptyBuffer2(argImpulseResponseLength);
    Buffer emptyBuffer3(bufferSize + argImpulseResponseLength - 1);
    
    inputBuffers.push_back(emptyBuffer);
    for(int i=0; i<argNoOutputChannels; i++)
    {
        outputBuffers.push_back(emptyBuffer);
        impulseResponses.push_back(emptyBuffer2);
        memoryBuffers.push_back(emptyBuffer3);
    }
    
    impulseResponseLength = argImpulseResponseLength;
    memoryBufferLength = argImpulseResponseLength + bufferSize - 1;

    bValidInput = 1;
    bValidOutput = 1;
    bMultipleInput = 0;
}

ABConvolver::ABConvolver(int argImpulseResponseLength, int argNoOutputChannels, int argBufferSize)
: AudioBlockBase(argBufferSize, 1, argNoOutputChannels)
{
    Buffer emptyBuffer(bufferSize);
    Buffer emptyBuffer2(argImpulseResponseLength);
    Buffer emptyBuffer3(argBufferSize + argImpulseResponseLength - 1);
    
    inputBuffers.push_back(emptyBuffer);
    for(int i=0; i<argNoOutputChannels; i++)
    {
        outputBuffers.push_back(emptyBuffer);
        impulseResponses.push_back(emptyBuffer2);
        memoryBuffers.push_back(emptyBuffer3);
    }
    
    impulseResponseLength = argImpulseResponseLength;
    memoryBufferLength = argImpulseResponseLength + bufferSize - 1;
    
    bValidInput = 1;
    bValidOutput = 1;
    bMultipleInput = 0;
}