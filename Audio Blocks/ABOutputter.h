//
//  Outputter.h
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 12/10/12.
//  Copyright (c) 2012 Hariharan Mohanraj. All rights reserved.
//

// NOT REQUIRED FOR NOW!!!

#ifndef __SoniScan_2_0__ABOutputter__
#define __SoniScan_2_0__ABOutputter__

#include <iostream>
#include "AudioBlockBase.h"

class ABOutputter : public AudioBlockBase
{
    Buffer* destinationBuffer;
    sample* writePtr;
    
public:
    void SetDestBuffer(Buffer*);
    Buffer* GetDestBuffer();
    void Process(std::vector<Buffer>&);
    
    ABOutputter();
    ABOutputter(int);
    ABOutputter(int,int);
};


#endif /* defined(__SoniScan_2_0__Outputter__) */
