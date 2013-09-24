//
//  Summer.h
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 12/17/12.
//  Copyright (c) 2012 Hariharan Mohanraj. All rights reserved.
//

// NOT REQUIRED FOR NOW!!!

#ifndef __SoniScan_2_0__ABSummer__
#define __SoniScan_2_0__ABSummer__

#include <iostream>
#include "AudioBlockBase.h"

// Class to take in N input channels, and sum them into one output channel

class ABSummer : public AudioBlockBase
{
    
public:
    
    void Process(std::vector<Buffer>&);
    
    ABSummer();
    ABSummer(int);
    ABSummer(int,int);
};



#endif /* defined(__SoniScan_2_0__Summer__) */
