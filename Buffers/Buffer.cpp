//
//  Buffer.cpp
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 12/6/12.
//  Copyright (c) 2012 Hariharan Mohanraj. All rights reserved.
//

#include "Buffer.h"
#include <math.h>
#include "../Constants.h"

//DEVELOPER'S NOTES: FIND A BETTER WAY TO PERFORM SIZE CHECK ON ARRAYS

sample* Buffer::Get()
{
    return bufferContents;
}

void Buffer::Get(sample argDestArray[], int argDestArraySize)
{
    // Check whether destination array is big enough to hold contents of buffer
    if(argDestArraySize < bufferSize)
        std::cout << "Destination array too small. Overflow ignored.\n";
    
    int i, len;
    
    // Set copy length equal to min(argDestArraySize, bufferSize)
    argDestArraySize < bufferSize? len = argDestArraySize : len = bufferSize;
    
    for(i=0; i<len; i++)                        // Copy samplewise into destination array
        argDestArray[i] = bufferContents[i];
}

sample Buffer::Get(int argIndex)
{
    // Check whether argIndex lies within valid boundaries
    
    if (argIndex < 0 || argIndex > bufferSize)
    {
        std::cout << "Invalid index. Zero (0) returned.\n";
        return 0;
    }
    
    return *(bufferContents+argIndex);
}

int Buffer::Size()
{
    return bufferSize;
}


// Functions to set values of buffer
void Buffer::Set(sample argInputArray[], int argInputArraySize)
{
    // Check whether argInputArraySize matches bufferSize
    
    if (argInputArraySize != bufferSize)
    {
        std::cout << "Array dimensions don't match with buffer size. Set() call ignored.\n";
        return;
    }
    
    for(int i=0; i<bufferSize; i++)
        bufferContents[i] = argInputArray[i];
}

void Buffer::Set(sample argValue, int argIndex)
{
    // Check whether argIndex lies within valid boundaries
    
    if (argIndex < 0 || argIndex >= bufferSize)
    {
        std::cout << "Invalid index. Set() call ignored.\n";
        return;
    }
    
    bufferContents[argIndex] = argValue;
}

// Utility functions for buffer

void Buffer::Clear()    // Function to set all buffer values to 0
{
    for(int i=0; i<bufferSize; i++)
        bufferContents[i] = 0;
}

void Buffer::Clear(int argValue)    // Function to set all buffer values to argValue
{
    for(int i=0; i<bufferSize; i++)
        bufferContents[i] = argValue;
}

void Buffer::Copy(Buffer& argSourceBuffer) // Function to copy contents of sourceBuffer to buffer
{
    // Check for buffer sizes mismatch
    
    if (bufferSize != argSourceBuffer.bufferSize)
    {
        std::cout << "Buffer size mismatch. Copy() call ignored.\n";
        return;
    }
    
    for(int i=0; i<bufferSize; i++)
    {
        this->Set(argSourceBuffer.Get(i),i);
    }
}

void Buffer::Copy(Buffer& argSourceBuffer, int argSourceIndex) // Function to copy contents of sourceBuffer from index
{                                                              // argSourceIndex to buffer
    int maxIndex;
    bufferSize < argSourceBuffer.bufferSize - argSourceIndex ? maxIndex = bufferSize : maxIndex = argSourceBuffer.bufferSize - argSourceIndex;
    
    for(int i=0; i<maxIndex; i++)
        bufferContents[i] = argSourceBuffer.bufferContents[i+argSourceIndex];
}

void Buffer::Add(Buffer& argBuffer)   // Function to add contents of argBuffer to buffer
{
    // Check for buffer sizes mismatch
    
    
    // TAKE THIS OUT LATER****
    //std::cout << bufferSize << "\t" << argBuffer.bufferSize << "\n";
    if (bufferSize != argBuffer.bufferSize)
    {
        std::cout << "Buffer size mismatch. Add() call ignored.\n";
        return;
    }
    
    for(int i=0; i<bufferSize; i++)
        bufferContents[i] += argBuffer.bufferContents[i];
}

void Buffer::Add(Buffer& argBuffer, int argIndex)
{
    int maxIndex;
    bufferSize < argBuffer.bufferSize + argIndex? maxIndex = bufferSize : maxIndex = argIndex + argBuffer.bufferSize;
    
    for(int i=argIndex; i<maxIndex; i++)
        bufferContents[i] += argBuffer.bufferContents[i-argIndex];
}

void Buffer::Add(Buffer& argBuffer, float argMultFactor, int argIndex)
{
    int maxIndex;
    bufferSize < argBuffer.bufferSize + argIndex? maxIndex = bufferSize : maxIndex = argIndex + argBuffer.bufferSize;
    
    for(int i=argIndex; i<maxIndex; i++)
        bufferContents[i] += argMultFactor * argBuffer.bufferContents[i-argIndex];
}


void Buffer::Subtract(Buffer& argBuffer)
{
    // Check for buffer sizes mismatch
    
    if (bufferSize != argBuffer.bufferSize)
    {
        std::cout << "Buffer size mismatch. Subtract() call ignored.\n";
        return;
    }
    
    for(int i=0; i<bufferSize; i++)
        bufferContents[i] -= argBuffer.bufferContents[i];
}


void Buffer::Multiply(Buffer& argBuffer)
{
    // Check for buffer sizes mismatch
    
    if (bufferSize != argBuffer.bufferSize)
    {
        std::cout << "Buffer size mismatch. Multiply() call ignored.\n";
        return;
    }
    
    for(int i=0; i<bufferSize; i++)
        bufferContents[i] *= argBuffer.bufferContents[i];
}


void Buffer::Multiply(float argFactor)
{
    for (int i=0; i<bufferSize; i++)
        bufferContents[i] *= argFactor;
}

void Buffer::Reverse()
{
    sample* tempBufferContents;
    tempBufferContents = new sample[bufferSize];    // Create a temporary array to store bufferContents
    int i = 0;
    
    for(i=0; i<bufferSize; i++)                     // Copy bufferContents to tempBufferContents
        tempBufferContents[i] = bufferContents[i];
    
    for(i=0; i<bufferSize; i++)                     // Copy tempBufferContents in reverse back to bufferContents
        bufferContents[i] = tempBufferContents[bufferSize-i];
    
    delete[] tempBufferContents;                      // Get rid of temp array before exiting
}

void Buffer::Invert()
{
    for(int i=0; i<bufferSize; i++)
        bufferContents[i] = (-1) * bufferContents[i];
}


// Constructors and Destructors

Buffer::Buffer()
{
    bufferSize = BUFFER_SIZE;
    bufferContents = new sample [bufferSize];
    this->Clear();
}

Buffer::Buffer(int argBufferSize)
{
    bufferSize = argBufferSize;
    bufferContents = new sample [bufferSize];
    this->Clear();
}

Buffer::Buffer(const Buffer& other)
{
    bufferSize = other.bufferSize;
    bufferContents = new sample [bufferSize];
    this->Clear();
}

Buffer& Buffer::operator=(Buffer rhs)
{
    // Check sizes
    
    if(bufferSize != rhs.bufferSize)
    {
        std::cout << "Buffer size mismatch.\n";
    }else{
        for(int i=0; i<bufferSize; i++)
            this->Set(rhs.Get(i),i);
    }
    
    return *this;
}

Buffer::~Buffer()
{
    delete[] bufferContents;
}