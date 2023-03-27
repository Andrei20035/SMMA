#include<iostream>
#include<string.h>
#include<vector>
#include <limits>
using namespace std;
// const char*, pointerul poate fi mutat, specifica faptul ca variabila este constanta si nu poate fi modificata prin intermediul pointerului
// const char* const, atat pointerul cat si continutul sunt imutabile
// char* const, adresa pointerului este imutabila, dar continutul poate fi modificat


//company, address, likes


class Client {
    private:
        char* client_name;                  // numele clientului
        const int clientID;                 // ID-ul clientului
        static int numberOfClients;         // numarul de obiecte Client create 
        string Company;                     // numele companiei 
        long Marketing_budget;              // bugetul alocat pentru campania de marketing
        bool Contract;                      // clientul are contract semnat sau nu
        int array[10];
    public:
    // operatorul de indexare
        int& operator[](int index) {
            return this->array[index];
        }

    // operatorul ++
        // prefix
        Client& operator++() {
            this->Marketing_budget++;
            return *this;
        }

        // postfix 
        Client operator++(int) {
            Client temp(*this);
            this->Marketing_budget++;
            return temp;
        }
    // operatorul +
        Client& operator+(const Client& obj) {
            this->Marketing_budget += obj.Marketing_budget;
            return *this;
        }

    // Operatorul -
        Client& operator-(const Client& obj) {
            this->Marketing_budget -= obj.Marketing_budget;
            return *this;
        }

    // operatorul cast explicit
        explicit operator long() const {
            return this->Marketing_budget;
        }

    // operatorul conditional <
        bool operator<(const Client& obj) const {
            return this->Marketing_budget < obj.Marketing_budget;
        }

    //operatorul de egalitate
        bool operator==(const Client& obj) const {
            if (strcmp(this->client_name, obj.client_name) != 0)
                return false;
            if (this->clientID != obj.clientID)
                return false;
            if (this->Company != obj.Company)
                return false;
            if (this->Marketing_budget != obj.Marketing_budget)
                return false;
            if (this->Contract != obj.Contract)
                return false;
            if (memcmp(this->array, obj.array, sizeof(array)) != 0)
                return false;
            return true;
        }

    // client_name
        void setClientName(const char* newClientName) {
            char* newString = new char[strlen(newClientName) + 1];
            strcpy(newString, newClientName);
            if (this->client_name != nullptr) {
                delete[] this->client_name;
            }
            this->client_name = new char[strlen(newClientName) + 1];
            strcpy(this->client_name, newString);
        }

        const char* getClientName() {return this->client_name;}

    // clientID
        const int getClientID(){return this->clientID;}

    // clients
        static int getClients(){return numberOfClients;} 

    // company
        void setCompany(string newCompany) {this->Company = newCompany;}
        string getCompany() {return this->Company;}

    // Marketing_budget
        void setMarketingBudget(long newMarketingBudget) {this->Marketing_budget = newMarketingBudget;}
        long getMarketingBudget() {return this->Marketing_budget;}
    
    // contract
        void setContract(bool newContract) {this->Contract = newContract;}
        bool getContract() {return this->Contract;}

    // array
    void setArray(int index, int value) {
        if (index >= 0 && index < 20) {
            this->array[index] = value;
        }
    }

    int getArray(int index) {
        if (index >= 0 && index < 20) {
            return this->array[index];
        }
    }

    // constructori
        Client();
        Client(const char* const client_name, const int clientID, const string Company, const long Marketing_budget, bool Contract);
        Client(const char* const client_name, const string company);
        Client(const long budget, const bool contract);
        Client(const Client &obj);
    
    // destructor
        ~Client();
    
    // supraincarcarea operatorului "="
        Client &operator =(const Client &obj);

    // functii friend
        friend ostream& operator<<(ostream& out, const Client& obj);
        friend istream& operator>>(istream& in, Client& obj);  


};

int Client::numberOfClients = 0;

// constructor fara parametrii
Client::Client():clientID(++numberOfClients) {
    this->client_name = new char[strlen("NULL") + 1];
    strcpy(this->client_name, "NULL");
    this->Company = "NULL";
    this->Marketing_budget = 0;
    this->Contract = false;
}

// constructori cu parametrii
Client::Client(const char* const client_name, const string company):clientID(++numberOfClients) {
    this->client_name = new char[strlen(client_name) + 1];
    strcpy(this-> client_name, client_name);
    this->Company = company;
    this->Marketing_budget = 0;
    this->Contract = 0;
};

Client::Client(const long budget, const bool contract):clientID(++numberOfClients) {
    this->client_name = new char[1];
    this->client_name[0] = '\0';
    this->Company = "";
    this->Marketing_budget = budget;
    this->Contract = contract;
}

// constructor cu toti parametrii
Client::Client(const char* client_name, const int clientID, string Company, long Marketing_budget, bool Contract):clientID(++numberOfClients) {
    this->client_name = new char[strlen(client_name) + 1];
    strcpy(this->client_name, client_name);
    this->Company = Company;
    this->Marketing_budget = Marketing_budget;
    this->Contract = Contract;
}

// constructor de copiere
Client::Client(const Client &obj):clientID(++numberOfClients) {
    this->client_name = new char[strlen(obj.client_name) + 1];
    strcpy(this->client_name, obj.client_name);
    this->Company = obj.Company;
    this->Marketing_budget = obj.Marketing_budget;
    this->Contract = obj.Contract;
}

// destructor
Client::~Client() {
    if (this->client_name != nullptr)
        delete[] this->client_name;
        this->client_name = nullptr;
}

//supraincarcarea operatorului "="
Client& Client::operator =(const Client &obj) {
    if (this != &obj) {
        if(this-> client_name != nullptr) {
            delete[] this->client_name;
            this->client_name = nullptr;
        }
        this->client_name = new char[strlen(obj.client_name) + 1];
        strcpy(this->client_name, obj.client_name);
        this->Company = obj.Company;
        this->Marketing_budget = obj.Marketing_budget;
        this->Contract = obj.Contract;
    }
    return *this;
}

//supraincarcarea operatorului "<<"
ostream& operator<<(ostream& out, const Client& obj) {
    out << "---------------------------------------------------" << endl;
    out << "ClientID: " << obj.clientID << "\n\n";
    out << "Client name: "<< obj.client_name << "\n\n";
    out << "Number of clients: " << obj.numberOfClients - 100 << "\n\n";
    out << "Company: " << obj.Company << "\n\n";
    out << "Marketing budget: " << obj.Marketing_budget << "\n\n";
    out << "Contract: " << obj.Contract << "\n";
    out << "---------------------------------------------------" << endl;

    return out;
};

//supraincarcarea operatorului ">>"
istream& operator>>(istream& in, Client& obj) {
    cout << "Client name: ";
    char aux[100];
    in.ignore();
    in.getline(aux, 100);
    if (obj.client_name != nullptr)
        delete[] obj.client_name;
    obj.client_name = new char[strlen(aux) + 1];
    strcpy(obj.client_name, aux);
    cout << "Company: ";
    getline(in, obj.Company);
    cout << "Marketing budget: ";
    in >> obj.Marketing_budget;
    cout << "Contract: ";
    in >> obj.Contract; 
    
    return in;
} 




class Campaign {
    private:
        char* client_name;                    
        char* campaign_name;
        std::vector<std::string> objectives;
        long marketing_budget;
        string socialMediaPlatform;
        int array[20];

    public:
    // operatorul de indexare
        int& operator[](int index) {
            return this->array[index];
        }

    // operatorul ++
        // prefix
        Campaign& operator++() {
            this->marketing_budget++;
            return *this;
        }

        // postfix 
        Campaign operator++(int) {
            Campaign temp(*this);
            this->marketing_budget++;
            return temp;
        }
    // operatorul +
        Campaign& operator+(const Campaign& obj) {
            this->marketing_budget += obj.marketing_budget;
            return *this;
        }

    // Operatorul -
        Campaign& operator-(const Campaign& obj) {
            this->marketing_budget -= obj.marketing_budget;
            return *this;
        }

    // operatorul cast explicit
        explicit operator long() const {
            return this->marketing_budget;
        }

    // operatorul conditional <
        bool operator<(const Campaign& obj) const {
            return this->marketing_budget < obj.marketing_budget;
        }

    //operatorul de egalitate
        bool operator==(const Campaign& obj) const {
            if (strcmp(this->client_name, obj.client_name) != 0)
                return false;
            if (strcmp(this->campaign_name, obj.campaign_name) != 0)
                return false;
           // vector
            if (this->socialMediaPlatform != obj.socialMediaPlatform)
                return false;
            if (this->marketing_budget != obj.marketing_budget)
                return false;
            if (memcmp(this->array, obj.array, sizeof(array)) != 0)
                return false;
            return true;
        }


    // client_name
        void setClientName(const char* newClientName) {
            char* newString = new char[strlen(newClientName) + 1];
            strcpy(newString, newClientName);
            if (this->client_name != nullptr) {
                delete[] this->client_name;
            };
            this->client_name = newString;
        };

        const char* getClientName() {return this->client_name;}
    
    // campaign_name
        void setCampaignName(const char* newCampaignName) {
            char* newString = new char[strlen(newCampaignName) + 1];
            strcpy(newString, newCampaignName);
            if (this->campaign_name != nullptr) {
                delete[] this->campaign_name;
            };
            this->campaign_name = newString;
        };

        const char* getCampaignName() {return this->campaign_name;}
    
    // objectives
        void setObjectives(const std::vector<std::string>& newObjectives) {this->objectives = newObjectives;}
        const std::vector<std::string>& getObjectives() const {return this-> objectives;}

    // marketing_budget
        void setMarketingBudget(const long& newMarketingBudget) {this->marketing_budget = newMarketingBudget;}
        long getMarketingBudget() {return this->marketing_budget;}
    
    // Social media platform
        void setSocialMediaPlatform(const string& platform) {this->socialMediaPlatform = platform;}
        const string& getSocialMediaPlatform() const {return this->socialMediaPlatform;}

    // array
    void setArray(int index, int value) {
        if (index >= 0 && index < 20) {
            this->array[index] = value;
        }
    }

    int getArray(int index) {
        if (index >= 0 && index < 20) {
            return this->array[index];
        }
    }
    
    // constructori
        Campaign();
        Campaign(const char* const campaign_name, const long marketing_budget);
        Campaign(const char* const client_name, const string platform);
        Campaign(const char* client_name, const char* campaign_name, const std::vector<std::string>& objectives, long marketing_budget, string socialMediaPlatform);
        Campaign(const Campaign &obj);
    
    // destructor
        ~Campaign();
    
    // supraincarcarea operatorului "="
        Campaign &operator =(const Campaign &obj);

    // functii friend
        friend ostream& operator<<(ostream& out, const Campaign& obj);
        friend istream& operator>>(istream& in, Campaign& obj);  
        
};

// constructor fara parametrii
Campaign::Campaign() {
    this->client_name = new char[strlen("NULL") + 1];
    strcpy(this->client_name, "NULL");
    this->campaign_name = new char[strlen("NULL") + 1];
    strcpy(this->campaign_name, "NULL");
    this->objectives = {};
    this->marketing_budget = 0;
    this->socialMediaPlatform = "NULL";
}

//constructori cu parametrii
    Campaign::Campaign(const char* const campaign_name, const long marketing_budget) {
        this->client_name = new char[1];
        this->client_name[0] = '\0';
        this->campaign_name = new char[strlen(campaign_name) + 1];
        strcpy(this->campaign_name, campaign_name);
        this->objectives = {};
        this->marketing_budget = marketing_budget;
        this->socialMediaPlatform = "";
    };

    Campaign::Campaign(const char* const client_name, const string platform) {
        this->client_name = new char[strlen(client_name) + 1];
        strcpy(this->client_name, client_name);
        this->campaign_name = new char[1];
        this->campaign_name[0] = '\0';
        this->objectives = {};
        this->marketing_budget = 0;
        this->socialMediaPlatform = platform;
    };

// constructor cu toti parametrii
Campaign::Campaign(const char* client_name, const char* campaign_name, const std::vector<std::string>& objectives, long marketing_budget, string socialMediaPlatform){
    this->client_name = new char[strlen(client_name) + 1];
    strcpy(this->client_name, client_name);
    this->campaign_name = new char[strlen(campaign_name) + 1];
    strcpy(this->campaign_name, campaign_name);
    this->objectives = objectives;
    this->marketing_budget = marketing_budget;
    this->socialMediaPlatform = socialMediaPlatform;
}

// constructor de copiere
Campaign::Campaign(const Campaign &obj) {
    this-> client_name = new char[strlen(obj.client_name) + 1];
    strcpy(this->client_name, obj.client_name);
    this-> campaign_name = new char[strlen(obj.campaign_name) + 1];
    strcpy(this->campaign_name, obj.campaign_name);
    this-> objectives = obj.objectives;
    this-> marketing_budget = obj.marketing_budget;
    this-> socialMediaPlatform = obj.socialMediaPlatform;   
}

// destructor
Campaign::~Campaign() {
    if (this->client_name != nullptr) {
        delete[] this->client_name;
        this->client_name = nullptr;
    }
    if (this->campaign_name != nullptr) {
        delete[] this->campaign_name;
        this->campaign_name = nullptr;
    }
}

// supraincarcarea operatorului "="
Campaign& Campaign::operator =(const Campaign &obj) {
    if(this != &obj) {
        if(this->client_name != nullptr)
            delete[] this-> client_name;
            this->client_name = nullptr;
        if(this->campaign_name != nullptr)
            delete[] this-> campaign_name;
            this->campaign_name = nullptr;
        this-> client_name = new char[strlen(obj.client_name) + 1];
        strcpy(this-> client_name, obj.client_name);
        this-> campaign_name = new char[strlen(obj.campaign_name) + 1];
        strcpy(this-> campaign_name, obj.campaign_name);
        this->objectives = obj.objectives;
        this->marketing_budget = obj.marketing_budget;
        this->socialMediaPlatform = obj.socialMediaPlatform;
    };
    return* this;
};

// supraincarcarea operatorului "<<"
ostream& operator<<(ostream& out, const Campaign& obj) {
    out << "---------------------------------------------------" << endl;
    out << "Client name: " << obj.client_name << "\n\n";
    out << "Campaign name: " << obj.campaign_name << "\n\n";
    out << "Objectives: ";
    for (int i = 0; i < obj.objectives.size(); i++)
        if (i == 0) {
            out << "-" << obj.objectives[i] << endl;
        } else {
            out << "            -" << obj.objectives[i] << endl;
        }
        
    out << "\n" << "Marketing budget: " << obj.marketing_budget << "\n\n";
    out << "Social media platform: " << obj.socialMediaPlatform << "\n";
    out << "---------------------------------------------------" << endl;

    return out;
};

// supraincarcarea operatorului ">>"
istream& operator>>(istream& in, Campaign& obj) {
    cout << "Client name: ";                        
    char aux1[100];     
    in.ignore();                              
    in.getline(aux1, 100);                                        
    if (obj.client_name != nullptr) {
        delete[] obj.client_name;
    }
    obj.client_name = new char[strlen(aux1) + 1];
    strcpy(obj.client_name, aux1);
    
    cout << "Campaign name: ";
    char aux2[100];
    in.getline(aux2, 100);
    if (obj.campaign_name != nullptr) {
        delete[] obj.campaign_name;
    }
    obj.campaign_name = new char[strlen(aux2) + 1];
    strcpy(obj.campaign_name, aux2);

    cout << "Objectives: ";
    string temp;
    while(getline(in, temp)) {
        if (temp.empty()) { 
            break;
        }
        obj.objectives.push_back(temp);
        cout << "Enter another objective (or press Enter to finish): ";
    }
    cout << "Marketing budget: ";
    in >> obj.marketing_budget;
    cout << "Social media platform: ";
    in >> obj.socialMediaPlatform;
    
    return in;
};

class Invoice {
    private:
        char* client_name;
        char* address;
        double commission;
        int payment_time;
        float total_amount;
        float* tax_rates;
        int array[20];
    public:
        static int numberOfInvoices;
    // operatorul de indexare
        int& operator[](int index) {
            return this->array[index];
        }

    // operatorul ++
        // prefix
        Invoice& operator++() {
            this->payment_time++;
            return *this;
        }

        // postfix 
        Invoice operator++(int) {
            Invoice temp(*this);
            this->payment_time++;
            return temp;
        }
    // operatorul +
        Invoice& operator+(const Invoice& obj) {
            this->payment_time += obj.payment_time;
            return *this;
        }

    // Operatorul -
        Invoice& operator-(const Invoice& obj) {
            this->payment_time -= obj.payment_time;
            return *this;
        }

    // operatorul cast explicit
        explicit operator long() const {
            return this->payment_time;
        }

    // operatorul conditional <
        bool operator<(const Invoice& obj) const {
            return this->payment_time < obj.payment_time;
        }

    //operatorul de egalitate
        bool operator==(const Invoice& obj) const {
            if (strcmp(this->client_name, obj.client_name) != 0)
                return false;
            if (strcmp(this->address, obj.address) != 0)
                return false;
            if (this->commission != obj.commission)
                return false;
            if (this->payment_time != obj.payment_time)
                return false;
            if (this->total_amount != obj.total_amount)
                return false;
            if (memcmp(this->tax_rates, obj.tax_rates, sizeof(tax_rates)) != 0)
                return false;
            return true;
        }

    // client_name
        void setClientName(const char* newClientName) {
            char* newString = new char[strlen(newClientName) + 1];
            strcpy(newString, newClientName);
            if(this->client_name != nullptr) {
                delete[] this-> client_name;
            };
            this-> client_name = newString;
        }
        
        const char* getClientName() {return this-> client_name;}

    // address
        void setAddress(const char* newAddress) {
            char* newString = new char[strlen(newAddress) + 1];
            strcpy(newString, newAddress);
            if(this->address != nullptr) {
                delete[] this-> address;
            };
            this-> address = newString;
        }
        
        const char* getAddress() {return this-> address;}

    // commission
        void setCommission(const double newCommission) {this->commission = newCommission;}
        double getCommission() {return this->commission;}

    // payment_time
        void setPaymentTime(const int newPaymentTime) {this->payment_time = newPaymentTime;}
        int getPaymentTime () {return this->payment_time;}

    // total_amount
        void setTotalAmount(const float total_amount) {this->total_amount = total_amount;}
        float getTotalAmount() {return this->total_amount;}

    // numberOfInvoices
        static int getNumberOfInvoices() {return numberOfInvoices;}

    // tax_rates
        void setTaxRates(const float& tax_rates) {*(this->tax_rates) = tax_rates;}
        const float* getTaxRates() {return this->tax_rates;}
    
    // array
    void setArray(int index, int value) {
        if (index >= 0 && index < 20) {
            this->array[index] = value;
        }
    }

    int getArray(int index) {
        if (index >= 0 && index < 20) {
            return this->array[index];
        }
    }

    // constructori
         Invoice();
         Invoice(const char* client_name, const char* address, const double commission, const int payment_time,
                 const float total_amount, const float* tax_rates);
         Invoice(const int payment_time, const float* tax_rates);
         Invoice(const char* client_name, const double commission, const float* tax_rates);
         Invoice(const Invoice &obj);

    // destructor
        ~Invoice();

    // supraincarcarea operatorului "="
        Invoice &operator =(const Invoice &obj);

    // functii friend
        friend ostream& operator<<(ostream& out, const Invoice& obj);
        friend istream& operator>>(istream& in, Invoice& obj);  
    
};

//constructor fara parametrii
    Invoice::Invoice() {
        numberOfInvoices++;
        this->client_name = new char[strlen("NULL") + 1];
        strcpy(this->client_name, "NULL");
        this->address = new char[strlen("NULL") + 1];
        strcpy(this->address, "NULL");        
        this->commission = 0;
        this->payment_time = 0;
        this->total_amount = 0;
        this->tax_rates = nullptr;
    }

// constructori cu parametrii
    Invoice::Invoice(const int payment_time, const float* tax_rates) {
        this->client_name = new char[strlen("NULL") + 1];
        strcpy(this->client_name, "NULL");
        this->address = new char[strlen("NULL") + 1];
        strcpy(this->address, "NULL");     
        this->commission = 0;
        this->payment_time = payment_time;
        this->total_amount = 0;
        numberOfInvoices++;
        this->tax_rates = new float[1];
        this->tax_rates[0] = tax_rates[0];
    }

    Invoice::Invoice(const char* client_name, const double commission, const float* tax_rates) {
        this->client_name = new char[strlen(client_name) + 1];
        strcpy(this->client_name, client_name);
        this->address = new char[strlen("NULL") + 1];
        strcpy(this->address, "NULL");
        this->commission = commission;
        this->payment_time = 0;
        this->total_amount = 0;
        numberOfInvoices++;
        this->tax_rates = new float[1];
        this->tax_rates[0] = tax_rates[0];
    }

// constructor cu toti parametrii
    Invoice:: Invoice(const char* client_name, const char* address, const double commission, const int payment_time, const float total_amount, const float* tax_rates) {
                    this->client_name = new char[strlen(client_name) + 1];
                    strcpy(this->client_name, client_name);
                    this->address = new char[strlen(address) + 1];
                    strcpy(this->address, address);
                    this->commission = commission;
                    this->payment_time = payment_time;
                    this->total_amount = total_amount;
                    this->tax_rates = new float[1];
                    this->tax_rates[0] = tax_rates[0];             
                    numberOfInvoices++;       
                 }

// constructor de copiere
    Invoice::Invoice(const Invoice &obj) {
            this-> client_name = new char[strlen(obj.client_name) + 1];
            strcpy(this->client_name, obj.client_name);
            this-> address = new char[strlen(obj.address) + 1];
            strcpy(this->address, obj.address);
            this-> commission = obj.commission;
            this-> payment_time = obj.payment_time;
            this->total_amount = obj.total_amount;
            int tax_rates_length = sizeof(float) * (strlen((const char*)obj.tax_rates) + 1);
            this->tax_rates = new float[sizeof(obj.tax_rates) / sizeof(float)];
            memcpy(this->tax_rates, obj.tax_rates, tax_rates_length);
            numberOfInvoices++;
    }

// destructor
    Invoice::~Invoice() {
        numberOfInvoices--;
        if (this->client_name != nullptr) {
            delete[] this-> client_name;
            this->client_name = nullptr;
        }
        if (this->address != nullptr) {
            delete[] this-> address;
            this->address = nullptr;
        }
        if (this->tax_rates != nullptr) {
            delete[] this-> tax_rates;
            this->tax_rates = nullptr;
        }
    }

// supraincarcarea operatorului "="
    Invoice& Invoice::operator=(const Invoice &obj) {
        if(this != &obj) {
            if(this->client_name != nullptr) {
                delete[] this-> client_name;
                this->client_name = nullptr;
            }
            if(this->address != nullptr) {
                delete[] this-> address;
                this->address = nullptr;
            }
            this-> client_name = new char[strlen(obj.client_name) + 1];
            strcpy(this-> client_name, obj.client_name);
            this-> address = new char[strlen(obj.address) + 1];
            strcpy(this-> address, obj.address);
            this->commission = obj.commission;
            this->payment_time = obj.payment_time;
            this->total_amount = obj.total_amount;
            int tax_rates_length = sizeof(float) * (strlen((const char*)obj.tax_rates) + 1);
            this->tax_rates = new float[sizeof(obj.tax_rates) / sizeof(float)];
            memcpy(this->tax_rates, obj.tax_rates, tax_rates_length);
        };
        return* this;
    }

// supraincarcarea operatorului "<<"    
    ostream& operator<<(ostream& out, const Invoice& obj) {
    out << "---------------------------------------------------" << endl;
    out << "Client name: " << obj.client_name << "\n";
    out << "Address: " << obj.address << "\n";
    out << "Commission: " << obj.commission << "%" << "\n";
    out << "Payment time: " << obj.payment_time << " DAYS" <<"\n";
    out << "Total amount: " << obj.total_amount << "$" << "\n";
    out << "Number of invoices: " << obj.numberOfInvoices-100 << "\n";
    out << "Tax rates: " << obj.tax_rates[0] << "%" << "\n";
    out << "---------------------------------------------------" << endl;

    return out;
};

//supraincarcarea operatorului ">>"
    istream& operator>>(istream& in, Invoice& obj){
        cout << "Client name: ";                        
        char aux1[100]; 
        in.ignore();                                  
        in.getline(aux1, 100);                                        
        if (obj.client_name != nullptr) {
            delete[] obj.client_name;
            obj.client_name = nullptr;
        }
        obj.client_name = new char[strlen(aux1) + 1];
        strcpy(obj.client_name, aux1);

        cout << "Adress: ";                        
        char aux2[200];                                   
        in.getline(aux2, 200);                                        
        if (obj.address != nullptr) {
            delete[] obj.address;
            obj.address = nullptr;
        }
        obj.address = new char[strlen(aux2) + 1];
        strcpy(obj.address, aux2);

        cout << "Commission: ";
        in >> obj.commission;
        cout << "Payment time: ";
        in >> obj.payment_time;
        cout << "Total amount: ";
        in >> obj.total_amount;
        if (obj.tax_rates != nullptr) {
            delete[] obj.tax_rates;
            obj.tax_rates = nullptr;
        }
        cout << "Tax rates: ";
        obj.tax_rates = new float[1];
        in >> obj.tax_rates[0];

        return in;
    }

int Invoice::numberOfInvoices = 0;



class Analytics {
    private:
        int likes;
        int shares;
        int views;
        float view_time;
        int array[20];
    public:
    // operatorul de indexare
        int& operator[](int index) {
            return this->array[index];
        }
    // operatorul ++
        // prefix
        Analytics& operator++() {
            this->likes++;
            return *this;
        }

        // postfix 
        Analytics operator++(int) {
            Analytics temp(*this);
            this->likes++;
            return temp;
        }
    // operatorul +
        Analytics& operator+(const Analytics& obj) {
            this->likes += obj.likes;
            return *this;
        }

    // Operatorul -
        Analytics& operator-(const Analytics& obj) {
            this->likes -= obj.likes;
            return *this;
        }

    // operatorul cast explicit
        explicit operator long() const {
            return this->likes;
        }

    // operatorul conditional <
        bool operator<(const Analytics& obj) const {
            return this->likes < obj.likes;
        }

    //operatorul de egalitate
        bool operator==(const Analytics& obj) const {
            if (this->likes != obj.likes)
                return false;
            if (this->shares != obj.shares)
                return false;
            if (this->views != obj.views)
                return false;
            if (this->view_time != obj.view_time)
                return false;
            return true;
        }

        // likes
            void setLikes (const int newLikes) {this->likes = newLikes;}
            int getLikes () {return this->likes;}

        // shares
            void setShares (const int newShares) {this->shares = newShares;}
            int getShares () {return this->shares;}
        
        // views
            void setViews (const int newViews) {this->views = newViews;}
            int getViews () {return this->views;}
        
        // view time
            void setViewTime (const int newViewTime) {this->view_time = newViewTime;}
            float getViewTime () {return this->view_time;}

        // array
            void setArray(int index, int value) {
                if (index >= 0 && index < 20) {
                    this->array[index] = value;
                }
            }

            int getArray(int index) {
                if (index >= 0 && index < 20) {
                    return this->array[index];
                }
            }
        
        // constructori
            Analytics();
            Analytics(const int likes, const int views);
            Analytics(const int likes, const int shares, const float view_time);
            Analytics(const int likes, const int shares, const int views, const float view_time);
            Analytics(const Analytics& obj);

        // destructor 
            ~Analytics(){};   
        
        // supraincarcarea operatorului "="
            Analytics &operator=(const Analytics &obj);

        // functii friend
            friend ostream& operator<<(ostream& out, const Analytics &obj);
            friend istream& operator>>(istream& in, Analytics& obj);
};

// constructor fara parametrii
    Analytics::Analytics() {
        this->likes = 0;
        this->shares = 0;
        this->views = 0;
        this->view_time = 0.0;
    }

// constructori cu parametrii
    Analytics::Analytics(const int likes, const int views) {
        this->likes= likes;
        this->shares = 0;
        this->views = views;
        this->view_time = 0;
    }

    Analytics::Analytics(const int likes, const int shares, const float view_time) {
        this->likes= likes;
        this->shares = shares;
        this->views = 0;
        this->view_time = view_time;        
    }

// constructor cu toti parametrii
    Analytics::Analytics(const int likes, const int shares, const int views, const float view_time) {
        this->likes= likes;
        this->shares = shares;
        this->views = views;
        this->view_time = view_time;         
    }

// constructor de copiere
    Analytics::Analytics(const Analytics& obj) {
        this->likes= obj.likes;
        this->shares = obj.shares;
        this->views = obj.views;
        this->view_time = obj.view_time;
    }

// supraincarcarea operatorului "="
    Analytics& Analytics::operator=(const Analytics &obj) {
        if(this != &obj) {
            this->likes= obj.likes;
            this->shares = obj.shares;
            this->views = obj.views;
            this->view_time = obj.view_time;
        };
        return* this;
    }

// supraincarcarea operatorului ">>"
    istream& operator>>(istream& in, Analytics& obj) {
        cout << "Likes: ";
        in >> obj.likes;
        cout << "Shares: ";
        in >> obj.shares;
        cout << "Views: ";
        in >> obj.views;
        cout << "View time: ";
        in >> obj.view_time;

        return in;
    }

// supraincarcarea operatorului "<<"
    ostream& operator<<(ostream& out, const Analytics& obj) {
        out << "---------------------------------------------------" << endl;
        out << "Likes: " << obj.likes << "\n";
        out << "Shares: " << obj.shares << "\n";
        out << "Views: " << obj.views << "\n";
        out << "View time: " << obj.view_time << "sec" <<"\n";
        out << "---------------------------------------------------" << endl;

        return out;
    }



int main() {
// Client C1("Mihai", 2, "Meta", 15000000, false),
// C2("andrei rusu", "polaris");
// cout << C2;

    // cout <<"ClientID: " << C1.getClientID() << endl;
    // cout << "Client name: " << C1.getClientName() << endl;
    // cout << "Number of clients: " << C1.getClients() << endl;
    // cout << "Company: " << C1.getCompany() << endl;
    // cout << "Contract: " << C1.getContract() << endl;
    // cout << "Marketing budget: " << C1.getMarketingBudget() << "\n\n\n";

    // cout<<C1<<"\n\n\n"; 

//Campaign Campaign1("pix", 50000), Campaign2("Andrei Rusu", "Instagram");

    // Campaign Campaign1("Andrei Rusu", "pix", {"bani", "followers"}, 25000, "Instagram");
    // // cout << "\n\n\n" << Campaign1;
    // Campaign1.setCampaignName("pizza");

    // cout << "Client name: " << Campaign1.getClientName() << endl;
    // cout << "Campaign name: " << Campaign1.getCampaignName() << endl;
    // cout << "Objectives: " << endl;
    // for(const auto& objective : Campaign1.getObjectives()) {
    //     cout << "           -" << objective << endl;
    // }
    // cout << "Marketing budget: " << Campaign1.getMarketingBudget() << endl;
    // cout << "Social media platform: " << Campaign1.getSocialMediaPlatform() << endl;
    
    //cout << Campaign1 << Campaign2;

//float tax_rates[] = {20};
//Invoice I1, I2(35, tax_rates), I3("Andrei Rusu", 10, tax_rates), I5("Alexia", "Nicolae G. Caramfil", 8, 30, 20000, tax_rates), I4(I5);

    // cout << "Client name: " << I4.getClientName() << endl;
    // cout << "Address: " << I4.getAddress() << endl;
    // cout << "Commission: " << I4.getCommission() << "%" << endl;
    // cout << "Payment time: " << I4.getPaymentTime() << " DAYS" << endl;
    // cout << "Total amount: " << I4.getTotalAmount()<< "$" << endl;
    // cout << "Number of invoices: " << I4.getNumberOfInvoices() << endl;
    // cout << "Tax rates: " << I4.getTaxRates()[0] << "%" << endl;

    // cin >> I5;
    // cout << I5;


// Analytics A1, A2(20, 15), A3(15, 20, 3.2), A4(20, 25, 35, 4.28), A5(A4);

//     A1 = A5;
//     cout << A1;
            
// Client C1, C2, C3;

//  cin>>C1>>C2>>C3;
//  cout << C1+C2+C3;




Client ClientList[100];
Campaign CampaignList[100];
Invoice InvoiceList[100];
Analytics AnalyticsList[100];
int contorClients = 0, contorCampaigns = 0, contorInvoices = 0, contorAnalytics = 0;
int k = 1;
while (k != 0) {
    int command;
    cout << "\n1-Add Client";
    cout << "\n2-Add Campaign";
    cout << "\n3-Add Invoice";
    cout << "\n4-Add Analytics";
    cout << "\n5-Display List of Clients";
    cout << "\n6-Display List of Campaigns";
    cout << "\n7-Display List of Invoices";
    cout << "\n8-Display List of Analytics";
    cout << "\n9-Stop";
    cin >> command;
    switch (command) {
        case 1: {
            Client c;
            cin >> c;
            ClientList[contorClients] = c;
            contorClients++;
            break;
        }
        case 2: {
            Campaign c;
            cin >> c;
            CampaignList[contorCampaigns] = c;
            contorCampaigns++;
            break;
        }
        case 3: {
            Invoice i;
            cin >> i;
            InvoiceList[contorInvoices] = i;
            contorInvoices++;
            break;
        }
        case 4: {
            Analytics a;
            cin >> a;
            AnalyticsList[contorAnalytics] = a;
            contorAnalytics++;
            break;
        }
        case 5: {
            for (int i = 0; i < contorClients; i++)
                cout << ClientList[i] << endl;
            break;
        }
        case 6: {
            for (int i = 0; i < contorCampaigns; i++)
                cout << CampaignList[i] << endl;
            break;
        }
        case 7: {
            for (int i = 0; i < contorInvoices; i++)
                cout << InvoiceList[i] << endl;
            break;
        }
        case 8: {
            for (int i = 0; i < contorAnalytics; i++)
                cout << AnalyticsList[i] << endl;
            break;
        }
        case 9: {
            k = 0;
            break;
        }
        default: {
            cout << "\n\tInvalid command";
            break;
        }
    }
}


return 0;

}



