
#include <iostream>
#include "ShoesManager.h"

using namespace std;

int main() {
    ShoesManager manager;

    // 1. Them du lieu mau
    cout << "=== THEM DU LIEU MAU ===\n";

    Shoes a("NK001", "AirForce1", "Nike", 40, 2000000, 10);
    Shoes b("KN001", "Samba", "Adidas", 41, 1800000, 7);
    Shoes c("NB001", "NB530", "NewBalance", 42, 2500000, 5);
    Shoes d("AD001", "Ultraboost", "Adidas", 42, 3000000, 4);
    Shoes e("AS001", "GelKayano", "Asics", 39, 1200000, 8);

    if (manager.Insert(a, NULL))
        cout << "Da them NK001\n";

    if (manager.Insert(b, NULL))
        cout << "Da them KN001\n";

    if (manager.Insert(c, NULL))
        cout << "Da them NB001\n";

    if (manager.Insert(d, NULL))
        cout << "Da them AD001\n";

    if (manager.Insert(e, NULL))
        cout << "Da them AS001\n";


    // 2. Hien thi danh sach giay
    cout << "\n=== DANH SACH GIAY ===\n";
    manager.Show();


    // 3. Tim kiem giay theo ma
    cout << "\n=== TIM KIEM ===\n";

    if (manager.Search("KN001") != NULL)
        cout << "Tim thay KN001\n";
    else
        cout << "Khong tim thay KN001\n";

    if (manager.Search("XX999") == NULL)
        cout << "Khong tim thay XX999\n";


    // 4. Sap xep va loc theo gia
    cout << "\n=== GIA TU THAP DEN CAO ===\n";
    manager.ShowPriceLowToHigh();

    cout << "\n=== GIA TU CAO DEN THAP ===\n";
    manager.ShowPriceHighToLow();

    cout << "\n=== GIAY CO GIA TU 1500000 DEN 2500000 ===\n";
    manager.ShowPriceRange(1500000, 2500000);


    // 5. Ban giay
    cout << "\n=== BAN HANG ===\n";
    manager.SellShoe("NK001", 3); 
    manager.SellShoe("KN001", 5); 
    manager.SellShoe("NB001", 99);
    manager.SellShoe("XX999", 1);


    // 6. Hien thi top giay ban chay
    cout << "\n=== TOP 3 GIAY BAN CHAY ===\n";
    manager.ShowTopSellers(3);


    // 7. Xoa giay
    cout << "\n=== XOA GIAY NK001 ===\n";

    Node* p = manager.Search("NK001");

    if (p != NULL && manager.Delete(p))
        cout << "Da xoa NK001\n";
    else
        cout << "Xoa NK001 that bai\n";


    // 8. Kiem tra sau khi xoa
    cout << "\n=== KIEM TRA SAU KHI XOA ===\n";

    if (manager.Search("NK001") == NULL)
        cout << "NK001 khong con ton tai\n";
    else
        cout << "NK001 van con ton tai\n";

    if (manager.Search("KN001") != NULL)
        cout << "KN001 van tim thay binh thuong\n";
    else
        cout << "Khong tim thay KN001\n";


    // 9. Hien thi danh sach cuoi cung
    cout << "\n=== DANH SACH SAU KHI XOA ===\n";
    manager.Show();

    return 0;
}
