#ifndef REEL_H
#define REEL_H
#include "List.hpp"
#include <vector>

using namespace std;
template <typename ReelTemplate>// template called RealTemplateName

class Reel : public CircularLinkedist<ReelTemplate> { // reel class can accres publicmembers of circular Linked-List
    public:
        Reel(const vector<ReelTemplate> & r) {
            for (auto & x : r)
                this->push_back(x);
        }
        Reel(vector<ReelTemplate> && r) {
            for (auto & x : r)
                this->push_back(move(x));
        }
        ~Reel(){}
        
        // advance an iterator n positions cyclically
        void advance(typename CircularLinkedist<ReelTemplate>::iterator & itr, int n) {
            this->check_iterator(itr);
            
            if (itr == this->end())
                itr = this->begin();
                
            for (int i = 0; i < n; i++) {
                ++itr;
                if (itr == this->end())
                    itr = this->begin();
            }
        }
        
        // move back an iterator n positions cyclically
        void backward(typename CircularLinkedist<ReelTemplate>::iterator & itr, int n) {
            this->check_iterator(itr);
            
            if (itr == this->begin())
                itr = this->end();
                
            for (int i = 0; i < n; i++) {
                --itr;
                if (itr == this->begin())
                    itr = --(this->end());
            }
        }
};

#endif
