//
//  ABBlockSummer.h
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 12/31/12.
//  Copyright (c) 2012 Hariharan Mohanraj. All rights reserved.
//

#ifndef __SoniScan_2_0__ABBlockSummer__
#define __SoniScan_2_0__ABBlockSummer__

#include <iostream>
#include "AudioBlockBase.h"

class ABBlockSummer : public AudioBlockBase
{
    std::vector<Buffer> summedBuffers;
    std::vector<int> inputFlags;
    
public:
    
    void Process(std::vector<Buffer>&);
    void FlowSignal(std::vector<Buffer>&,AudioBlockBase*);
    
    void AddInputBuffer();
    void RemoveInputBuffer();
    
    void AddOutputBuffer();
    void RemoveOutputBuffer();
    
    ABBlockSummer();
    ABBlockSummer(int);
    ABBlockSummer(int,int);
    
};

#endif /* defined(__SoniScan_2_0__ABBlockSummer__) */
