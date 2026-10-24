#include "NodeC.h"

class HashTableC{
    private:
        NodeC** Table;
        int M;

        int HashFunction(const string&) const;

    public:
        HashTableC(const int& = 101);
        ~HashTableC();

        bool Insert(NodeC*);
        bool Delete(NodeC*);
        NodeC* Search(const string&);

        friend class CustomerManager;
};
