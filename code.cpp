#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;
class item{
    public : 
        virtual string getName() = 0;
        virtual int getQuantity() = 0;
        virtual double getPrice() = 0;
        virtual void updateQuantity(int &val) = 0;
        virtual void updatePrice(double &val) = 0;
};
class product : public item{
    private : 
        string name;
        int quantity;
        double price;
    public : 
        product() : name(""), quantity(0), price(0) {}
        product(string name1, int quantity1, double price1) : name(name1), quantity(quantity1), price(price1) {}
        string getName() override{
            return name;
        }
        int getQuantity() override{
            return quantity;
        }
        double getPrice() override{
            return price;
        }
        void updateQuantity(int &val) override{
            quantity = val;
        }
        void updatePrice(double &val) override{
            price = val;
        }
        bool operator==(product &other){
            return other.getName() == name;
        }
};
class inventory{
    private : 
        vector<product> products;
    public : 
        void addProduct(){
            cout<<"details of the product you want to add : "<<endl;
            string name;
            int quantity;
            double price;
            cout<<"Name : ";
            cin>>name;
            cout<<"Quantity : ";
            cin>>quantity;
            cout<<"Price : ";
            cin>>price;
            product temp(name, quantity, price);
            products.push_back(temp);
            cout<<"Item is successfully added!"<<endl;
        }
        void updateProduct(){
            string name;
            cout<<"Name of the product you want to update : ";
            cin>>name;
            for(product &it : products){
                if(it == products[products.size() - 1] and it.getName() != name){
                    cout<<"product not found!"<<endl;
                    return;
                }
                if(it.getName() != name) continue;
                int choice;
                cout<<"Choices : "<<endl<<"1) price"<<endl<<"2) quantity"<<endl<<"Enter your choice : ";
                cin>>choice;
                switch(choice){
                    case 1 : 
                        double updatedPrice;
                        cout<<"updated price : ";
                        cin>>updatedPrice;
                        it.updatePrice(updatedPrice);
                        cout<<"price is successfully updated!"<<endl;
                        break;
                    case 2 : 
                        int updatedQuantity;
                        cout<<"updated quantity : ";
                        cin>>updatedQuantity;
                        it.updateQuantity(updatedQuantity);
                        cout<<"quantity is successfully updated!"<<endl;
                        break;
                    default : 
                        cout<<"Invalid choice!"<<endl;
                }
                return;
            }
        }
        void displayInventory(){
            if(!products.size()){
                cout<<"Inventory is empty!"<<endl;
                return;
            }
            cout<<left<<setw(20)<<"Name"<<setw(10)<<"Quantity"<<setw(10)<<"Price"<<endl;
            cout<<"--------------------------------------------"<<endl;
            for(product it : products){
                cout<<left<<setw(20)<<it.getName()<<setw(10)<<it.getQuantity()<<setw(10)<<fixed<<setprecision(2)<<it.getPrice()<<endl;
            }
        }
        void loadFromFile(){
            ifstream file;
            file.open("inv.txt");
            if(!file.is_open()){
                cout<<"error opening the file!"<<endl;
                exit(1);
            }
            if(file.is_open() and file.peek() == ifstream::traits_type::eof()){
                cout<<"file is empty!"<<endl;
                file.close();
                return;
            }
            string line;
            while(getline(file, line)){
                int pos1 = line.find(',');
                int pos2 = line.find(',', pos1 + 1);
                string name = line.substr(0, pos1);
                int quantity = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
                double price = stod(line.substr(pos2 + 1));
                product temp(name, quantity, price);
                products.push_back(temp);
            }
            cout<<"Inventory is loaded successfully!"<<endl;
            file.close();
        }
        void loadToFile(){
            ofstream file;
            file.open("inv.txt");
            if(!file.is_open()){
                cout<<"error opening the file!"<<endl;
                exit(1);
            }
            if(!products.size()){
                file<<"";
                return;
            }
            for(product it : products){
                file<<it.getName()<<","<<it.getQuantity()<<","<<it.getPrice()<<endl;
            }
            file.close();
        }
        void searchProduct(){
            string name;
            cout<<"Name of the product you want to search : ";
            cin>>name;
            for(product it : products){
                if(it.getName() == name){
                    cout<<"Item is found!"<<endl;
                    cout<<"name\t\t\tquantity\t\tprice"<<endl;
                    cout<<it.getName()<<"\t\t\t"<<it.getQuantity()<<"\t\t\t"<<it.getPrice()<<endl;
                    return;
                }
            }
            cout<<"Item is not found!"<<endl;
        }
        void deleteProduct(){
            string name;
            cout<<"Name of the product you want to delete : ";
            cin>>name;
            for(auto it = products.begin(); it != products.end(); it++){
                if(it -> getName() == name){
                    it = products.erase(it);
                    cout<<"Product is deleted successfully!"<<endl;
                    return;
                }
            }
            cout<<"Item is not found!"<<endl;
        }
        product *findProduct(string name){
            for(auto &it : products){
                if(it.getName() == name){
                    return &it;
                }
            }
            return nullptr;
        }
        void maintain() {
            auto it = products.begin();
            while(it != products.end()){
                if(it->getQuantity() == 0){
                    it = products.erase(it);
                }
                else{
                    ++it;
                }
            }
        }
};
class cart{
    private : 
        vector<product> items;
        inventory &inv;
    public : 
        cart(inventory &inventoryRef) : inv(inventoryRef) {}
        void addToCart(){
            string name;
            cout<<"Name of the product : ";
            cin>>name;
            product *prod = inv.findProduct(name);
            if(prod == nullptr){
                cout<<"Product not found in inventory!"<<endl;
                return;
            }
            int quantity;
            cout<<"Quantity : ";
            cin>>quantity;
            if(quantity > prod -> getQuantity()){
                cout<<"Not enough stock!"<<endl;
                cout<<"want to add the available quantity?"<<endl;
                int choice;
                cout<<endl<<endl;
                cout<<"-----------------------"<<endl;
                cout<<"1) yes"<<endl;
                cout<<"2) no"<<endl;
                cout<<"Enter your choice : ";
                cin>>choice;
                cout<<"-----------------------"<<endl;
                if(choice == 2) return;
                else{
                    product temp(name, prod -> getQuantity(), prod -> getPrice());
                    int newQuantity = 0;
                    prod -> updateQuantity(newQuantity);
                    items.push_back(temp);
                    cout<<"Product added!"<<endl;
                }
            }
            else{
                product temp(name, quantity, prod -> getPrice());
                items.push_back(temp);
                int newQuantity = prod -> getQuantity() - quantity;
                prod -> updateQuantity(newQuantity);
                cout<<"Product added!"<<endl;
            }
            inv.maintain();
        }
        void printBill(){
            if(items.empty()){
                cout<<"Cart is empty!"<<endl;
                return;
            }
            double total = 0;
            cout<<left<<setw(20)<<"Name"<<setw(10)<<"Quantity"<<setw(10)<<"Price"<<setw(10)<<"Total"<<endl;
            cout<<"----------------------------------------------------------"<<endl;
            for(product it : items){
                double itemTotal = it.getQuantity() * it.getPrice();
                cout<<left<<setw(20)<<it.getName()<<setw(10)<<it.getQuantity()<<setw(10)<<fixed<<setprecision(2)<<it.getPrice()<<setw(10)<<fixed<<setprecision(2)<<itemTotal<<endl;
                total += itemTotal;
            }
            cout<<"----------------------------------------------------------"<<endl;
            cout<<left<<setw(40)<<"Total Bill : "<<fixed<<setprecision(2)<<total<<endl;
        }
};
void manageInventory(){
    inventory inv;
    inv.loadFromFile();
    int choice;
    do{
        cout<<"----------------------------"<<endl;
        cout<<"1) Add a product"<<endl;
        cout<<"2) Update a product"<<endl;
        cout<<"3) Display the inventory"<<endl;
        cout<<"4) Search for a product"<<endl;
        cout<<"5) Delete a product"<<endl;
        cout<<"6) Save and exit"<<endl;
        cout<<"Enter your choice : ";
        cin>>choice;
        cout<<"----------------------------"<<endl;
        cout<<endl<<endl;
        switch(choice){
            case 1 : 
                inv.addProduct();
                break;
            case 2 : 
                inv.updateProduct();
                break;
            case 3 : 
                inv.displayInventory();
                break;
            case 4 : 
                inv.searchProduct();
                break;
            case 5 : 
                inv.deleteProduct();
                break;
            case 6 : 
                inv.loadToFile();
                cout<<"Inventory is saved successfully!"<<endl;
                break;
            default : 
                cout<<"Invalid input!"<<endl;
        }
    }while(choice != 6);
    return;
}
void billing(){
    inventory inv;
    inv.loadFromFile();
    cart c(inv);
    int choice;
    do{
        cout<<"-------------------------"<<endl;
        cout<<"1) Add items to cart"<<endl;
        cout<<"2) Print bill"<<endl;
        cout<<"3) Exit"<<endl;
        cout<<"Enter your choice : ";
        cin>>choice;
        cout<<"-------------------------"<<endl;
        cout<<endl<<endl;
        switch(choice){
            case 1 : 
                c.addToCart();
                break;
            case 2 : 
                c.printBill();
                break;
            case 3 : 
                break;
            default : 
                cout<<"Invalid input!"<<endl;
        }
    }while(choice != 3);
    inv.loadToFile();
}
int main(){
    int choice;
    do{
        cout<<"----------------------"<<endl;
        cout<<"1) Manage inventory"<<endl;
        cout<<"2) Billing"<<endl;
        cout<<"3) Exit"<<endl;
        cout<<"Enter your choice : ";
        cin>>choice;
        cout<<"----------------------"<<endl;
        cout<<endl<<endl;
        switch(choice){
            case 1 : 
                manageInventory();
                break;
            case 2 : 
                billing();
                break;
            case 3 : 
                cout<<"!Exiting the program!"<<endl;
                break;
            default : 
                cout<<"Invalid input!"<<endl;
        }
    }while(choice != 3);
    return 0;   
}