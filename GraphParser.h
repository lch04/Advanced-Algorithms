//
//  GraphParser.h
//  ListMiner
//
//  Created by Chenhao Liu on 11/29/12.
//  Copyright (c) 2012 Chenhao Liu. All rights reserved.
//

#ifndef __ListMiner__GraphParser__
#define __ListMiner__GraphParser__

#include <iostream>
#include <string>
#include "Graph.h"
#include "memory"
using namespace std;
#endif /* defined(__ListMiner__GraphParser__) */
class GraphParser{
public:
    //GraphParser();
    Graph* parseGraph(const string line);
    static int mark;
};