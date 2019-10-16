#ifndef LIST_H
#define LIST_H
#include <stdexcept>
#include <utility>

template <typename CircularTemplate>// template declare and template name

class CircularLinkedist {
    private:
        struct Node {
            CircularTemplate data;
            Node *previousData;
            Node *nextData;
            
            Node(const CircularTemplate & Data = CircularTemplate(), Node *p = nullptr, Node *n = nullptr) : data(Data), previousData(p), nextData(n) {}
            Node(CircularTemplate && Data, Node *previousPtr = nullptr, Node *nextPtr = nullptr) : data(std::move(Data)), previousData(previousPtr), nextData(nextPtr) {}
        };
    
    public:
    class const_iterator {
            protected:
                const CircularLinkedist<CircularTemplate> *list;
                Node *currentPosition;
                       
                const_iterator(const CircularLinkedist<CircularTemplate> & l, Node * p) : list(&l), currentPosition(p) {}
                       
                const CircularTemplate & retrieve() const {
                        return currentPosition->data;
                }
                       
                void check() const {
                    if (list == nullptr or currentPosition == nullptr or currentPosition == list->head)
                               throw std::out_of_range("Iterator out of range");
                }
        
            public:
                const CircularTemplate & operator* () const {
                    return retrieve();
                }
                
                const_iterator & operator++ () {
                    currentPosition = currentPosition -> nextData;
                    return *this;
                }
            
                const_iterator operator++ (int) {
                    const_iterator old = *this;
                    currentPosition = currentPosition->nextData;
                    return old;
                }
                
                const_iterator & operator-- () {
                    currentPosition = currentPosition -> previousData;
                    return *this;
                }
                const_iterator operator-- (int) {
                    const_iterator old = *this;
                    currentPosition = currentPosition -> previousData;
                    return old;
                }
                
                bool operator== (const const_iterator & itr) const {
                    return currentPosition == itr.currentPosition;
                }
                
                bool operator!= (const const_iterator & itr) const {
                    return !(*this == itr);
                }
        
                friend class CircularLinkedist<CircularTemplate>;// to grants the CircularLinkedist class access to constant nonpublic members.
        };
        
    class iterator : public const_iterator {
        
            protected:
                iterator(const CircularLinkedist<CircularTemplate> & l, Node * previous) : const_iterator(l, previous) {}
                friend class CircularLinkedist<CircularTemplate>;
            
            public:
                CircularTemplate & operator* () {
                    return this->currentPosition->data;
                }
                
                const CircularTemplate & operator* () const {
                    return const_iterator::operator*();
                }
                
                iterator & operator++ () {
                    this->currentPosition = this->currentPosition->nextData;
                    return *this;
                }
                
                iterator operator++ (int) {
                    iterator old = *this;
                    this->currentPosition = this->currentPosition -> nextData;
                    return old;
                }
                
                iterator & operator-- () {
                    this->currentPosition = this->currentPosition->previousData;
                    return *this;
                }
                
                iterator operator-- (int) {
                    iterator old = *this;
                    this->currentPosition = this->currentPosition -> previousData;
                    return old;
                }
                
                bool operator==(const iterator & itr) const {
                    return const_iterator::operator==(itr);
                }
                
                bool operator!=(const iterator & itr) const {
                    return const_iterator::operator!=(itr);
                }
            
        };
        
        
        private:
            int length;
            Node *head;
            Node * tail;
                  
            void initialization() {// initialization
                length = 0;
                head = new Node;
                tail = new Node;
                head->nextData = tail;
                tail->previousData = head;
            }
                  
        protected:
            void check_iterator(const_iterator itr) {// check for the  interator belongs to the current CircularLinkedist
              itr.check();
              if (itr.list != this)
                  throw std::out_of_range("Iterator doesn't belong to current list");
            }
                  
    
        public:
            CircularLinkedist() {
                initialization();
            }
            
            CircularLinkedist(const CircularLinkedist & l) {
                initialization();
                for (auto & x : l)
                    push_back(x);
            }
            
            CircularLinkedist(CircularLinkedist && l) : length(l.length), head(l.head), tail(l.tail) {
                l.length = 0;
                l.head = nullptr;
                l.tail = nullptr;
            }
             
            ~CircularLinkedist() {
                clear();
                delete head;
                delete tail;
            }
            
            CircularLinkedist & operator= (const CircularLinkedist & l ){
                CircularLinkedist copy(l);
                std::swap(*this, copy);
                return *this;
            }
            
            CircularLinkedist & operator= (CircularLinkedist && l) {
                std::swap(length, l.length);
                std::swap(head, l.head);
                std::swap(tail, l.tail);
                
                return *this;
            }
            
            iterator begin() {
                return iterator(*this, head -> nextData);
            }
            const_iterator begin() const {
                return const_iterator(*this, head -> nextData);
            }
            
            iterator end() {
                return iterator(*this, tail);
            }
    
            const_iterator end() const {
                return const_iterator(*this, tail);
            }
            
            int size() const {
                return length;
            }
            
            bool empty() const {
                return length == 0;
            }
            
            void clear() {
                while(!empty())
                    pop_front();
            }
            
            CircularTemplate & front(){
                return *begin();
            }
            const CircularTemplate & front() const {
                return *begin();
            }
            
            CircularTemplate & back(){
                return *(--end());
            }
            const CircularTemplate & back() const{
                return *(--end());
            }
            
            void push_front(const CircularTemplate & x){
                insert(begin(), x);
            }
            void push_front(CircularTemplate && x){
                insert(begin(), x);
            }
            
            void push_back(const CircularTemplate & x){
                insert(end(), x);
            }
            void push_back(CircularTemplate && x){
                insert(end(), x);
            }
            
            void pop_front(){
                erase(begin());
            }
            
            void pop_back(){
                erase(--end());
            }
            
            iterator insert(iterator itr, const CircularTemplate & x){ // insert be4 itrator
                check_iterator(itr);
                Node *p = itr.currentPosition;
                Node *n = new Node(x, p -> previousData, p);
                p->previousData->nextData = n;
                p->previousData = n;
                length++;
                
                return iterator(*this, n);
            }
            iterator insert(iterator itr, CircularTemplate && x){
                check_iterator(itr);
                Node *p = itr.currentPosition;
                Node *n = new Node(x, p -> previousData, p);
                p->previousData->nextData = n;
                p->previousData = n;
                length++;
                
                return iterator(*this, n);
            }
            
            iterator erase(iterator itr){
                check_iterator(itr);
                Node *p = itr.currentPosition;
                iterator ret(*this, p->nextData);
                p->previousData->nextData = p->nextData;
                p->nextData->previousData = p->previousData;
                delete p;
                --length;
                
                return ret;
            }
            
            iterator erase(iterator to, iterator from){
                check_iterator(to);
                check_iterator(from);
                for (iterator itr = from; itr != to;){
                    itr = erase(itr);
                }
                return to;
            }
      
};

#endif 
