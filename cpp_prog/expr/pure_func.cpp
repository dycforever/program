
class Parent  
{  
public: 
    Parent() { }   
    ~Parent() {    
        ClearALL();    
    }    

    void ClearALL()   {    
        ThePure();
    }   

    virtual bool ThePure() = 0 ;  
};   

class Child : public Parent  
{  
public: 
    Child() { }    
    ~Child() { }
    bool ThePure() {
        return true;
    }  
};


int main()  
{  
    Child c;  
}  
