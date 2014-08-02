//
//  ListMiner.cpp
//  ListMiner
//
//  Created by Chenhao Liu on 11/29/12.
//  Copyright (c) 2012 Chenhao Liu. All rights reserved.
//

#include "ListMiner.h"
#include <fstream>
#include <sstream>
#include <ext/hash_map>
#include "GraphParser.h"
void ListMiner::miner(const char* infile,const int sigma,const int Pmax, const int start){
    ifstream myfile(infile);
    if(!myfile.is_open()){
        cout<<"Unable to open file: "<<infile<<", please double check!\n"<<endl;
        return;
    }
    int tracker=1;
    while (myfile.good()&&tracker<start) {
        string buffer;
        getline(myfile,buffer);
        ++tracker;
    }
    //1: A<- NEW MATRIX
    vector<vector<list<ListNode*>*>*>* A= new vector<vector<list<ListNode*>*>*>();
    for(int i=0;i<=Pmax;++i){
        A->push_back(new vector<list<ListNode*>*>());
        for(int j=0;j<i;++j)
            (*A)[i]->push_back(new list<ListNode*>());
    }
    vector<ListNode*>* B = new vector<ListNode*>();
    //2: H<- NEW SUBGRAPH HASHMAP
    __gnu_cxx::hash_map<ListNode,list<ListNode*>,my_compare>* H = new __gnu_cxx::hash_map<ListNode,list<ListNode*>,my_compare>();
    //3: for(t←0 to T-1) do
    string line;
    int t=0,phase;
    GraphParser* gp= new GraphParser();
    while(myfile.good()){
        getline(myfile,line);
    //4: Gt <- input[t]
        Graph* Gt=gp->parseGraph(line);
        B->push_back(new ListNode(t,t,1,Gt));
        /*
        if(t==0){
            list<ListNode*>* L=new list<ListNode*>();
            L->push_front(new ListNode(t,t,1,Gt));
            //update(L,)
            A->at(0)->at(0)=L;
            ++t;
            continue;
        }
         */
    //5: for (p←1 to min (t, Pmax)) do
        for(int p=1;p<=min(t,Pmax);++p){
    //6: phase ← t mod p
            phase=t%p;
    //7: L←A[p][phase]
            list<ListNode*>* L=A->at(p)->at(phase);
    //8: N= new ListNode(Gt,t,t, 1)
            ListNode* N=new ListNode(t,t,1,Gt);
    //9: L.push_head(N)
            L->push_front(N);
    //10: update(L)
            update(L,t,p,sigma,H);
    //11: end for
        }
    //12: end while
        ++t;        
    }
    myfile.close();
    //13: for (i←0 to Pmax )do
    for(int i=0;i<=Pmax;++i)
    //14: for(j←0 to i) do
        for(int j=0;j<i;++j){
    //15: L←A[i][j];
            list<ListNode*>* L=A->at(i)->at(j);
    //16: iterator ← L.begin()
            list<ListNode*>::iterator it=L->begin();
    //17: for iterator to L.end() do
            while(it!=L->end()){
    //18: Gx ← L.iterator()
                ListNode* ndp=*it;
    //19: if(!Subsumed (Gx,i)and Gx.support() ≥ σ) then
                if ((!subsumed(ndp,i,sigma,H))&&(ndp->getSupport()>=sigma)) {
    //20: print Gx
                    print(ndp);
    //21: endif
                }
    //22: end for
                ++it;
            }
    //23: end for
        }
    //24: end for
    delete A;
    delete B;
    delete gp;
}

unsigned long myhash(const ListNode& node){
    unsigned long hash=5381;
    vector<int>* v=node.getGraph()->getter();
    for(int i=0;i<v->size();++i)
        hash=((hash<<5)+hash)+v->at(i);
    return hash;
}

void ListMiner::update(list<ListNode*>* L,const int t,const int p,const int sigma,__gnu_cxx::hash_map<ListNode,list<ListNode*>,my_compare>* H){
    //1. Gt ← L.begin()
    Graph* Gt=L->front()->getGraph();
    //2. iterator ← L.begin()
    list<ListNode*>::iterator it=L->begin();
    //3. iterator.next()
    ++it;
    //4. while iterator ≤ L.end() do
    while (it!=L->end()) {
    //5. N ← L.iterator()
        ListNode* N=*it;
    //6. F ← L.iterator().graph()
        Graph* F=N->getGraph();
    //7. C ← Gt ∩ F
        Graph* C=MCS(Gt,F);
    //8. if (F ⊂ Gt) then
        if(F->isPartOf(*Gt)){
    //9. while iterator ≤ L.end() do
            while(it!=L->end()){
    //10. N ← L.iterator()
                N=*it;
    //11. N.update_end_index(t)
                N->setEnd(t);
    //12. N.update_support(support(F)+1)
                N->incrementSupport();
                
                bool flag=true;
                if ((*N->getGraph())==*((*(--it))->getGraph())) {
                    flag=false;
                    it=L->erase(it);
                }
                ++it;
                if (flag) {
                    ++it;
                }
                //++it;
    //13. end while
            }
    //14. else if C = ∅ then
        } else if (C->getter()->size()==0){
    //15. while iterator ≤ L.end() do
            while (it!=L->end()) {
    //16. N ← L.iterator()
                N=*it;
    //17. if (!Subsumed (N.graph(),p) and N.support() ≥ σ ) then
                if(!subsumed(N, p,sigma,H) && N->getSupport()>=sigma)
    //18. print N
                    print(N);
    //19. endif
    //20. delete N
                it=L->erase(it);
    //21. end while
            }
    //22. else // case C != ∅ and C!= F
        } else {
    //23. if (!Subsumed (N.graph(),p) and N.support() ≥ σ ) then
            if(!subsumed(N, p,sigma,H) && N->getSupport()>=sigma)
    //24. print N
                print(N);
    //25. endif
    //26: N.update_graph(C) //the graph of N is set to C
            N->setGraph(*C);
    //27: N.update_end_index(t) // the end index of N is set equal to t
            N->setEnd(t);
    //28: N.update_support(support(N)+1) //the support of N is incremented by one
            N->incrementSupport();
    //29: if (N.graph() is equal to the graph of the previous node) then
            bool flag=true;
            if ((*C)==*((*(--it))->getGraph())) {
    //30: delete the previous node
                flag=false;
                it=L->erase(it);
    //31. endif
            }
    //32: iterator.next()
            ++it;
            if (flag) {
                ++it;
            }            
    //33: endif
        }
    //34: endif
    //35: endfor
    }    
}

Graph* ListMiner::MCS(const Graph* g1,const Graph* g2){
    int l1=(int)g1->getter()->size();
    int l2=(int)g2->getter()->size();
    if(l1==0||l2==0)
        return (new Graph());
    int i=0,j=0;
    vector<int>* v=new vector<int>();
    while (i<l1&&j<l2) {
        if (g1->getter()->at(i)==g2->getter()->at(j)) {
            v->push_back(g1->getter()->at(i));
            ++i,++j;
        } else if (g1->getter()->at(i)>g2->getter()->at(j))
            ++j;
        else ++i;
    }
    return (new Graph(v));
}

bool ListMiner::subsumed(ListNode* G,const int p, const int sigma,__gnu_cxx::hash_map<ListNode,list<ListNode*>,my_compare>* H){
//1: subsumed=false;
    bool subsumed=false;
//2: if (H.search(G.graph())=false) then
    __gnu_cxx::hash_map<ListNode,list<ListNode*>,my_compare>::iterator it=H->find(*G);
    if (it==H->end()) {
//3: if (G.support() ≥ σ) then
        if (G->getSupport()>=sigma) {
//4: H.insert(G.graph, G.start(),G.end(),p)
            list<ListNode*>* L=new list<ListNode*>();
            L->push_back(G);
            H->insert(pair<ListNode, list<ListNode*>>(*G,*L));
//5: endif
        }
//6: else
    } else{
//7: for each descriptor D ∈ H.search(G.graph())
        list<ListNode*> L=it->second;
        for (list<ListNode*>::iterator it=L.begin(); it!=L.end();++it) {
//8: if (p mod D.period()=0 and G.start() ≥ D.start() and G.end() ≤ D.end()) then
            int period=((*it)->getEnd()-(*it)->getStart())/((*it)->getSupport()-1);
            if ((p%period==0)&&(G->getStart()>=(*it)->getStart())&&(G->getEnd()<=(*it)->getEnd())) {
//9: subsumed=true                
                subsumed=true;
//10: break
                break;
//11: end if
            }
//12: end for each
        }
//13: if (subsumed=false and G.support() ≥ σ) then
        if(subsumed==false&&G->getSupport()>=sigma){
//14: H.insert(G.graph, G.start(),G.end(),p)
            list<ListNode*>* L=new list<ListNode*>();
            L->push_back(G);
            H->insert(pair<ListNode, list<ListNode*>>(*G,*L));
//15: endif
        }
//16: endif
    }
    return subsumed;
}

void ListMiner::print(const ListNode* g){
    int period=(g->getEnd()-g->getStart())/(g->getSupport()-1);
    cout<<"Start: "<<g->getStart()<<" Support: "<<g->getSupport()<<" Period:"<<period<<" [";
    vector<int>::iterator it=g->getGraph()->getter()->begin();
    for (; it!=g->getGraph()->getter()->end(); ++it){
        cout<<*it<<" ";
    }
    cout<<"]"<<endl;
}






