#include <iostream>
#include "ShoesManager.h"

int main(){
    Shoes s1("NK001", "AirForce1", "Nike", 40, 2000000, 10);
    Shoes s2("AD001", "Samba", "Adidas", 41, 1800000, 7);
    Shoes s3("NB001", "NB530", "NewBalance", 42, 2500000, 5);
    ShoesManager List;
    List.Insert(s3,NULL);
    List.Insert(s2,NULL);
    List.Insert(s1,NULL);
    Node *tmp=List.Search("AD001");
    List.Delete(tmp);
    List.Show();
    return 0;
}