//
//  Outputter.cpp
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 12/10/12.
//  Copyright (c) 2012 Hariharan Mohanraj. All rights reserved.
//

#include "ABOutputter.h"

void ABOutputter::SetDestBuffer(Buffer* argDestBuffer)
{
    destinationBuffer = argDestBuffer;
}

Buffer* ABOutputter::GetDestBuffer()
{
    return destinationBuffer;
}


void ABOutputter::Process(std::vector<Buffer>& targetOutputBuffer)
{
    
    if (noInputBuffers != 0)
        std::cout << "OUTPUTTER OUTPUT:\n";
        for (int i=0; i<bufferSize; i++)
        {
            writePtr = (float *)destinationBuffer;
            
            for (int j=0; j<noInputBuffers; j++)
            {
                //std::cout << inputBuffers[j].Get(i) << "\t";
                destinationBuffer->Copy(inputBuffers[j]);
                
            }
            //std::cout << std::endl;
        }
}

ABOutputter::ABOutputter()
: AudioBlockBase(128,1,0)
{
    bValidInput = 1;
    bValidOutput = 0;
    bMultipleInput = 0;
    
    destinationBuffer = 0;
    writePtr = 0;
}

ABOutputter::ABOutputter(int noChannels)
: AudioBlockBase(128,noChannels,0)
{
    bValidInput = 1;
    bValidOutput = 0;
    bMultipleInput = 0;
    
    destinationBuffer = 0;
    writePtr = 0;
}

ABOutputter::ABOutputter(int noChannels, int bufferSize)
: AudioBlockBase(bufferSize, noChannels, 0)
{
    bValidInput = 1;
    bValidOutput = 0;
    bMultipleInput = 0;
    
    destinationBuffer = 0;
    writePtr = 0;
}