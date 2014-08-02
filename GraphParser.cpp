//
//  GraphParser.cpp
//  ListMiner
//
//  Created by Chenhao Liu on 11/29/12.
//  Copyright (c) 2012 Chenhao Liu. All rights reserved.
//

#include "GraphParser.h"
#include <fstream>
#include <sstream>

int GraphParser::mark=0;

Graph* GraphParser::parseGraph(const string line){
    if (line[0]!='*') {
        vector<int>* g=new vector<int>();
        g->clear();
        g->push_back(--mark);
        return (new Graph(g));
        //return NULL;
    } else {
        istringstream iss(line);
        string buffer;
        iss>>buffer;
        int n;
        vector<int>* v=new vector<int>();
        v->clear();
        while (iss>>n) {
            v->push_back(n);
        }
        return (new Graph(v));
    }
}
