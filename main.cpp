//
//  main.cpp
//  ListMiner
//
//  Created by Chenhao Liu on 11/1/12.
//  Copyright (c) 2012 Chenhao Liu. All rights reserved.
//

//#include <iostream>
//#include <boost/numeric/ublas/matrix.hpp>
//#include <boost/numeric/ublas/io.hpp>
//#include <sparsehash/sparse_hash_map>
//#include <google/dense_hash_map>

#include "ListMiner.h"
/*
#include "Graph.h"
#include "ListNode.h"
#include "GraphParser.h"
#include "Header.h"
*/
int main(int argc, const char * argv[])
{

    // insert code here...
    
    //cout<<"Please specify data file:\n"<<endl;
    
    ListMiner* lm=new ListMiner();
    bool run=true;
    if (run==true) {
        lm->miner("/Users/Bruce/Desktop/input.txt", 3, 10, 600);
    } else {
        lm->miner("/Users/Bruce/Desktop/test.txt", 4, 100, 0);
    }
    
    getchar();
    return 0;
}

