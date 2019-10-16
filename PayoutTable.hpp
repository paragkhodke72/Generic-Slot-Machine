#ifndef PAYOUT_TABLE_H
#define PAYOUT_TABLE_H
#include <utility>
#include <set>

using namespace std;
template <typename object, typename data>

class PayOut {
    using item = pair<object, data>;
    
    private:
        set<item> table;
    
    public:
        PayOut() {}// Constructor with args
        ~PayOut() {} // De-Constructore
        PayOut(const PayOut & payTable): table(payTable.table) {}
        PayOut(PayOut && payTable): table(move(payTable.table)) {};
        
        PayOut & operator= (const PayOut & payTable) {
            if (&payTable == this)
                return *this;
            
            table = payTable.table;
            return *this;
        }
        
        PayOut & operator= (PayOut && payTable) {
            swap(table, payTable.table);
            return *this;
        }
        
        item find(const object & combination){
            for (auto x : table) {
                if (x.first == combination)
                    return x;
            }
            return item();
        }
    
        void insert(const item & x)
        {
            table.insert(x);
        }
        
        void erase(const item & x) {
            table.erase(x);
        }
};

#endif
