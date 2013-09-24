//
//  ABConvolver.h
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 12/19/12.
//  Copyright (c) 2012 Hariharan Mohanraj. All rights reserved.
//

#ifndef __SoniScan_2_0__ABConvolver__
#define __SoniScan_2_0__ABConvolver__

#include <iostream>
#include "AudioBlockBase.h"

// This class acts as a basic convolution engine

class ABConvolver : public AudioBlockBase
{
    std::vector<Buffer> impulseResponses;
    std::vector<Buffer> memoryBuffers;
    
    int impulseResponseLength;
    int memoryBufferLength;
    
public:
    
    void Process(std::vector<Buffer>&);
    
    int GetImpulseResponseLength();
    void SetImpulseResponseLength(int);
    
    void SetImpulseResponse(Buffer,int);
    std::vector<Buffer> GetImpulseResponses();
    
    void AddOutputBuffer();
    void RemoveOutputBuffer();
    
    ABConvolver();
    ABConvolver(int);
    ABConvolver(int,int);
    ABConvolver(int,int,int);
};



#endif /* defined(__SoniScan_2_0__ABConvolver__) */
