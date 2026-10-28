#include "StockTransactionManager.h"
#include <fstream>

//tao danh sach rong voi dung luong ban dau (it nhat 1)
StockTransactionManager::StockTransactionManager(const int& capacity){
    this->Capacity=capacity>0 ? capacity : 1;
    this->Size=0;
    this->List=new StockTransaction[this->Capacity];
}

//giai phong mang
StockTransactionManager::~StockTransactionManager(){
    delete[] this->List;
}

//het cho thi nhan doi mang
void StockTransactionManager::Grow(){
    int newCapacity=this->Capacity*2;
    StockTransaction* newList=new StockTransaction[newCapacity];
    for(int i=0;i<this->Size;i++)
        newList[i]=this->List[i];
    delete[] this->List;
    this->List=newList;
    this->Capacity=newCapacity;
}

//them giao dich vao cuoi danh sach (tu dong tang dung luong khi day)
//tra ve FALSE neu ID rong/da ton tai, loai khong phai Import/Export, hoac so luong <= 0
bool StockTransactionManager::Add(const StockTransaction& t){
    if(t.GetTransactionId()=="" || this->Search(t.GetTransactionId())!=NULL)
        return false;
    if(t.GetType()!="Import" && t.GetType()!="Export")
        return false;
    if(t.GetQuantity()<=0)
        return false;
    if(this->Size==this->Capacity)
        this->Grow();
    this->List[this->Size]=t;
    this->Size++;
    return true;
}

//lay so luong giao dich
int StockTransactionManager::GetCount() const{
    return this->Size;
}

//in tat ca giao dich theo thu tu them
void StockTransactionManager::Show() const{
    if(this->Size==0){
        cout<<"Chua co giao dich kho nao."<<endl;
        return;
    }
    for(int i=0;i<this->Size;i++)
        this->List[i].Output();
}

//tim giao dich theo Transaction ID, tra ve NULL neu khong thay
StockTransaction* StockTransactionManager::Search(const string& transactionId){
    for(int i=0;i<this->Size;i++){
        if(this->List[i].GetTransactionId()==transactionId)
            return &this->List[i];
    }
    return NULL;
}

//in cac giao dich co loai cho truoc (Import/Export), tra ve so giao dich tim duoc
int StockTransactionManager::ShowByType(const string& type) const{
    int count=0;
    for(int i=0;i<this->Size;i++){
        if(this->List[i].GetType()==type){
            this->List[i].Output();
            count++;
        }
    }
    return count;
}

//in cac giao dich cua 1 doi giay, tra ve so giao dich tim duoc
int StockTransactionManager::ShowByShoe(const string& shoeId) const{
    int count=0;
    for(int i=0;i<this->Size;i++){
        if(this->List[i].GetShoeId()==shoeId){
            this->List[i].Output();
            count++;
        }
    }
    return count;
}

//in cac giao dich co ngay bat dau bang chuoi date (vd 2026-10-23), tra ve so giao dich tim duoc
int StockTransactionManager::ShowByDate(const string& date) const{
    int count=0;
    for(int i=0;i<this->Size;i++){
        if(this->List[i].GetTransactionDate().find(date)==0){
            this->List[i].Output();
            count++;
        }
    }
    return count;
}

//in giao dich theo gia tri giam dan (sap xep tren ban sao, danh sach goc khong doi)
void StockTransactionManager::ShowMaxToMin() const{
    if(this->Size==0){
        cout<<"Chua co giao dich kho nao."<<endl;
        return;
    }
    StockTransaction* tmp=new StockTransaction[this->Size];
    for(int i=0;i<this->Size;i++)
        tmp[i]=this->List[i];
    for(int i=0;i<this->Size-1;i++){
        int max=i;
        for(int j=i+1;j<this->Size;j++){
            if(tmp[j].GetTotalValue()>tmp[max].GetTotalValue())
                max=j;
        }
        StockTransaction t=tmp[i];
        tmp[i]=tmp[max];
        tmp[max]=t;
    }
    for(int i=0;i<this->Size;i++)
        tmp[i].Output();
    delete[] tmp;
}

//dem so giao dich co loai cho truoc
int StockTransactionManager::CountByType(const string& type) const{
    int count=0;
    for(int i=0;i<this->Size;i++){
        if(this->List[i].GetType()==type)
            count++;
    }
    return count;
}

//tong so luong giay theo loai giao dich (Import/Export)
int StockTransactionManager::TotalQuantityByType(const string& type) const{
    int sum=0;
    for(int i=0;i<this->Size;i++){
        if(this->List[i].GetType()==type)
            sum+=this->List[i].GetQuantity();
    }
    return sum;
}

//ton kho rong cua 1 doi giay = tong nhap - tong xuat
int StockTransactionManager::NetQuantityByShoe(const string& shoeId) const{
    int sum=0;
    for(int i=0;i<this->Size;i++){
        if(this->List[i].GetShoeId()==shoeId){
            if(this->List[i].GetType()=="Import")
                sum+=this->List[i].GetQuantity();
            else
                sum-=this->List[i].GetQuantity();
        }
    }
    return sum;
}

//tong gia tri giao dich theo loai (Import = tien nhap hang, Export = tien xuat hang)
long long StockTransactionManager::TotalValueByType(const string& type) const{
    long long sum=0;
    for(int i=0;i<this->Size;i++){
        if(this->List[i].GetType()==type)
            sum+=this->List[i].GetTotalValue();
    }
    return sum;
}

//luu moi giao dich thanh 1 dong, tra ve FALSE neu khong ghi duoc file
bool StockTransactionManager::SaveToFile(const string& path) const{
    ofstream f(path.c_str());
    if(!f)
        return false;
    for(int i=0;i<this->Size;i++)
        f<<this->List[i].ToLine()<<'\n';
    return true;
}

//doc giao dich tu file, dong sai dinh dang hoac trung ID thi bo qua
//tra ve -1 neu khong mo duoc file, nguoc lai tra ve so giao dich doc duoc
int StockTransactionManager::LoadFromFile(const string& path){
    ifstream f(path.c_str());
    if(!f)
        return -1;
    int count=0;
    string line;
    while(getline(f,line)){
        StockTransaction t;
        if(StockTransaction::FromLine(line,t) && this->Add(t))
            count++;
    }
    return count;
}