#ifndef SLOT_MACHINE_H
#define SLOT_MACHINE_H
#include "Reel.hpp"
#include <random>

template <typename SlotMachineTemplate>
class SlotMachine {
    private:
           int slots;
           vector<SlotMachineTemplate> reels;
           vector<typename SlotMachineTemplate::iterator> current;
    
           int rand() { // generate a random number between 1 and 100
               random_device rd;
               mt19937 gen(rd());
               uniform_int_distribution<int> dis(1,100);
               return dis(gen);
           }
    
    public:
        SlotMachine(int size = 0) : slots(size){
            for (int i = 0; i < slots; i++)
                reels.push_back(SlotMachineTemplate());
                
            for (int i = 0; i < slots; i++)
                current.push_back(reels[i].begin());
        }
        
        SlotMachine(int size, const SlotMachineTemplate & reel) : slots(size){
            for (int i = 0; i < slots; i++)
                reels.push_back(SlotMachineTemplate(reel));
                
            for (int i = 0; i < 3; i++)
                current.push_back(reels[i].begin());
        }
        
        ~SlotMachine() {}
        SlotMachine(const SlotMachine & slotMachi) : reels(slotMachi.reels), current(slotMachi.current) {}
        SlotMachine(SlotMachine && slotMachi) : reels(move(slotMachi.reels)), current(move(slotMachi.current)) {}
        
        SlotMachine & operator= (const SlotMachine & slotMachi){
            if (&slotMachi == this)
                    return *this;
            reels = slotMachi.reels;
            current = slotMachi.current;
            return *this;
        }
    
        SlotMachine & operator= (SlotMachine && slotMachi){
            swap(reels, slotMachi.reels);
            swap(current, slotMachi.current);
            return *this;
        }
        
        void spin()
        {
            for (int i = 0; i < slots; i++) {
                int n = rand();
                reels[i].advance(current[i], n);
            }
        }
        
        auto get(int i) const { // return the element pointed by the i current pointer
            if (i < 1 or i > 3)
                return '\0';
                
            return *current[i-1];
        }
        
   
};

#endif
