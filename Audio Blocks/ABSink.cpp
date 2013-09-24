//
//  ABSink.cpp
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 2/20/13.
//  Copyright (c) 2013 Hariharan Mohanraj. All rights reserved.
//

#include "ABSink.h"

void ABSink::Process(std::vector<Buffer>&)
{
    localBuffer->Copy(inputBuffers[0]);
    outputBuffers[0].Copy(inputBuffers[0]);
}

Buffer ABSink::ReturnOutputBuffer()
{
    return outputBuffers[0];
}


ABSink::ABSink()
: AudioBlockBase(1,1)
{
    localBuffer = new Buffer();
}

ABSink::ABSink(int argBufferSize)
: AudioBlockBase(argBufferSize, 1, 1)
{
    localBuffer = new Buffer(argBufferSize);
}

ABSink::~ABSink()
{
    delete localBuffer;
}