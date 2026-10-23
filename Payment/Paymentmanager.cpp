#include "PaymentManager.h"
#include <fstream>
const int TRUE=1;
const int FALSE=0;

//tao danh sach rong voi dung luong ban dau (it nhat 1)
PaymentManager::PaymentManager(const int& capacity){
    this->Capacity=capacity>0 ? capacity : 1;
    this->Size=0;
    this->List=new Payment[this->Capacity];
}

//giai phong mang
PaymentManager::~PaymentManager(){
    delete[] this->List;
}

//het cho thi nhan doi mang
void PaymentManager::Grow(){
    int newCapacity=this->Capacity*2;
    Payment* newList=new Payment[newCapacity];
    for(int i=0;i<this->Size;i++)
        newList[i]=this->List[i];
    delete[] this->List;
    this->List=newList;
    this->Capacity=newCapacity;
}

//them giao dich vao cuoi danh sach (tu dong tang dung luong khi day)
//tra ve FALSE neu Payment ID rong hoac da ton tai
int PaymentManager::Add(const Payment& p){
    if(p.getPaymentId()=="" || this->Search(p.getPaymentId())!=NULL)
        return FALSE;
    if(this->Size==this->Capacity)
        this->Grow();
    this->List[this->Size]=p;
    this->Size++;
    return TRUE;
}

//lay so luong giao dich
int PaymentManager::GetCount(){
    return this->Size;
}

//in tat ca giao dich theo thu tu them
void PaymentManager::Show(){
    if(this->Size==0){
        cout<<"Chua co giao dich nao."<<endl;
        return;
    }
    for(int i=0;i<this->Size;i++)
        this->List[i].Output();
}

//tim giao dich theo Payment ID, tra ve NULL neu khong thay
Payment* PaymentManager::Search(const string& paymentId){
    for(int i=0;i<this->Size;i++){
        if(this->List[i].getPaymentId()==paymentId)
            return &this->List[i];
    }
    return NULL;
}

//in cac giao dich co trang thai cho truoc, tra ve so giao dich tim duoc
int PaymentManager::ShowByStatus(const string& status){
    int count=0;
    for(int i=0;i<this->Size;i++){
        if(this->List[i].getStatus()==status){
            this->List[i].Output();
            count++;
        }
    }
    return count;
}

//in cac giao dich co ngay bat dau bang chuoi date (vd 2026-10-23), tra ve so giao dich tim duoc
int PaymentManager::ShowByDate(const string& date){
    int count=0;
    for(int i=0;i<this->Size;i++){
        if(this->List[i].getPaymentDate().find(date)==0){
            this->List[i].Output();
            count++;
        }
    }
    return count;
}

//in giao dich theo so tien giam dan (sap xep tren ban sao, danh sach goc khong doi)
void PaymentManager::ShowMaxToMin(){
    if(this->Size==0){
        cout<<"Chua co giao dich nao."<<endl;
        return;
    }
    Payment* tmp=new Payment[this->Size];
    for(int i=0;i<this->Size;i++)
        tmp[i]=this->List[i];
    for(int i=0;i<this->Size-1;i++){
        int max=i;
        for(int j=i+1;j<this->Size;j++){
            if(tmp[j].getAmount()>tmp[max].getAmount())
                max=j;
        }
        Payment t=tmp[i];
        tmp[i]=tmp[max];
        tmp[max]=t;
    }
    for(int i=0;i<this->Size;i++)
        tmp[i].Output();
    delete[] tmp;
}

//dem so giao dich co trang thai cho truoc
int PaymentManager::CountByStatus(const string& status){
    int count=0;
    for(int i=0;i<this->Size;i++){
        if(this->List[i].getStatus()==status)
            count++;
    }
    return count;
}

//tong doanh thu (chi tinh giao dich Success)
long long PaymentManager::TotalRevenue(){
    long long sum=0;
    for(int i=0;i<this->Size;i++){
        if(this->List[i].getStatus()=="Success")
            sum+=this->List[i].getAmount();
    }
    return sum;
}

//doanh thu theo phuong thuc thanh toan (chi tinh Success)
long long PaymentManager::RevenueByMethod(const string& method){
    long long sum=0;
    for(int i=0;i<this->Size;i++){
        if(this->List[i].getStatus()=="Success" && this->List[i].getPaymentMethod()==method)
            sum+=this->List[i].getAmount();
    }
    return sum;
}

//doanh thu theo ngay, date la tien to cua ngay gio (vd 2026-10-23) (chi tinh Success)
long long PaymentManager::RevenueByDate(const string& date){
    long long sum=0;
    for(int i=0;i<this->Size;i++){
        if(this->List[i].getStatus()=="Success" && this->List[i].getPaymentDate().find(date)==0)
            sum+=this->List[i].getAmount();
    }
    return sum;
}

//luu moi giao dich thanh 1 dong, tra ve FALSE neu khong ghi duoc file
int PaymentManager::SaveToFile(const string& path){
    ofstream f(path.c_str());
    if(!f)
        return FALSE;
    for(int i=0;i<this->Size;i++)
        f<<this->List[i].ToLine()<<'\n';
    return TRUE;
}

//doc giao dich tu file, dong sai dinh dang hoac trung ID thi bo qua
//tra ve -1 neu khong mo duoc file, nguoc lai tra ve so giao dich doc duoc
int PaymentManager::LoadFromFile(const string& path){
    ifstream f(path.c_str());
    if(!f)
        return -1;
    int count=0;
    string line;
    while(getline(f,line)){
        Payment p;
        if(Payment::FromLine(line,p) && this->Add(p)==TRUE)
            count++;
    }
    return count;
}