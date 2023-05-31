#include<iostream>
#include<cstring>
#include<vector>
#include<set>
#include<list>
#include<sstream>
#include<unordered_map>
#include<fstream>

using namespace std;


class Campaign;
class Post;
class Invoice;

// Clasa abstracta 
class IOinterface {  
    public:
    // Functii virtuale pure
        virtual istream& input(istream& in) = 0;
        virtual ostream& output(ostream& out) const = 0;
        virtual float calculateTotalCost() const = 0;
};

// Clasa template
template <class T>
class Container {
private:
    std::vector<T> items;

public:
    // Adaugarea elementelor in container
    void addItem(const T& item) {
        items.push_back(item);
    }

    // Afisarea tuturor elementelor
    void printContainer(const Container<T>& container) {
        for (const auto& item : container.items) {
            cout << item << endl;
        }
    }
};



class Client : public IOinterface {
    protected:
        std::string client_name;              // Numele clientului
        const int clientID;                   // ID-ul clientului(unic)
        static int numberOfClients;           // Numarul total clientilor 
        std::string company;                  // Numele comapniei
        long marketing_budget;                // Bugetul de marketing
        bool contract;                        // Contract semnat 
        vector<Campaign> campaigns;           // Campaniile clientului
        vector<Invoice> invoices;             // Facturile clientului
    public:

    // client_name
        void setClientName(const std::string newClientName) {this->client_name = newClientName;}
        const std::string getClientName() const {return this-> client_name;}
    
    // ID
        const int getID() const {return this->clientID;}

    // company
        void setCompany(std::string newCompany) {this->company = newCompany;}
        std::string getCompany() {return this->company;}

    // marketing_budget
        void setMarketingBudget(long newMarketingBudget) {this->marketing_budget = newMarketingBudget;}
        long getMarketingBudget() {return this->marketing_budget;}
    
    // contract
        void setContract(bool newContract) {this->contract = newContract;}
        bool getContract() {return this->contract;}

    // Constructori
        Client();
        Client(const std::string client_name, const std::string company, const long marketing_budget, const bool contract);
        Client(const Client& obj);

    // Operatorul "="
        Client& operator=(const Client& obj);

    // Destructor
        ~Client(){};

    // Functiile virtuale implementate
    istream& input(istream& in) {
        cout << "Client name: ";
        getline(in, this->client_name);
        cout << "Company: ";
        getline(in, this->company);
        cout << "Marketing budget: ";
        in >> this->marketing_budget;
        cout << "Contract: ";
        in >> this->contract;

        return in;
    }

    ostream& output(ostream& out) const {
        out << "---------------------------------------------------" << endl;
        out << "ClientID: " << this->clientID / 2 << "\n";
        out << "Client name: "<< this->client_name << "\n";
        out << "Number of clients: " << this->numberOfClients / 2 << "\n";
        out << "Company: " << this->company << "\n";
        out << "Marketing budget: " << this->marketing_budget << "\n";
        out << "Contract: " << this->contract << "\n";
        out << "---------------------------------------------------" << endl;

        return out;
    };

    // Operatori de citire si afisare
        friend istream& operator>>(istream& in, Client& obj){return obj.input(in);}
        friend ostream& operator<<(ostream& out, const Client& obj){return obj.output(out);}

    // Metoda virtuala implementata
        float calculateTotalCost() const override {return 0.0;}

    // Metodele pentru citire si scriere in fisier
    void writeClientToFile(const Client& client, const std::string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            file << client;  // Folosim operatorul de afișare pentru a scrie obiectul în fișier
            file.close();
            cout << "Datele au fost scrise in fisier.\n";
        } else {
            cout << "Eroare la deschiderea fisierului.\n";
        }
    }

    void readClientFromFile(Client& client, const std::string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            file >> client;  // Folosim operatorul de citire pentru a citi obiectul din fișier
            file.close();
            cout << "Datele au fost citite din fisier.\n";
        } else {
            cout << "Eroare la deschiderea fisierului.\n";
        }
    }

    void addCampaign(const Campaign& campaign) {
        campaigns.push_back(campaign);
    }

    const std::vector<Campaign>& getCampaigns() const {
        return campaigns;
    }
};

int Client::numberOfClients = 0;

// Constructorii
Client::Client():clientID(++numberOfClients){
    this->client_name = "NULL";
    this->company = "NULL";
    this->marketing_budget = 0;
    this->contract = 0;
}

Client::Client(const std::string client_name, const std::string company, const long marketing_budget, const bool contract):clientID(++numberOfClients) {
    this->client_name = client_name;
    this->company = company;
    this->marketing_budget = marketing_budget;
    this->contract = contract;
}

Client::Client(const Client& obj):clientID(++numberOfClients) {
    this->client_name = obj.client_name;
    this->company = obj.company;
    this->marketing_budget = obj.marketing_budget;
    this->contract = obj.contract;
}

// Operatorul "="
Client& Client::operator=(const Client& obj) {
    if(this != &obj) {
        this->client_name = obj.client_name;
        this->company = obj.company;
        this->marketing_budget = obj.marketing_budget;
        this->contract = obj.contract;
    }
    return *this;
}

class Campaign : virtual public Client {
    protected:
        std::string campaign_name;           // Numele campaniei
        set<std::string> objectives;         // Obiectivele campaniei
        std::string socialMediaPlatform;     // Platforma
        list<Post> posts;               // Postarile campaniei
    public:
    // campaign_name
        void setCampaignName(const std::string newCampaignName){this->campaign_name = newCampaignName;}
        const std::string getCampaignName() const {return this->campaign_name;}

    // objectives
        void setObjectives(const set<std::string>& newObjectives) {this->objectives = newObjectives;}
        const set<std::string>& getObjectives() {return this-> objectives;}

    // socialMediaPlatform
        void setSocialMediaPlatform(std::string newSocialMediaPlatform) {this->socialMediaPlatform = newSocialMediaPlatform;}
        std::string getSocialMediaPlatform() {return this->socialMediaPlatform;}

    // Constructorii
        Campaign();
        Campaign(const std::string campaign_name, const set<std::string> objectives, const std::string socialMediaPlatform);
        Campaign(const Campaign& obj);

    // Operatorul "="
        Campaign& operator=(const Campaign& obj);

    // Destructor
        virtual ~Campaign(){};

    // Functiile virtuale implementate
        istream& input(istream& in) {
            cout << "Campaign name: ";
            getline(in, this->campaign_name);
            cout << "Objectives: ";
            std::string temp;
            while(getline(in, temp)) {
                if (temp.empty()) { 
                    break;
                }
                this->objectives.insert(temp);
                cout << "Enter another objective (or press Enter to finish): ";
            }
            cout << "Social media platform: ";
            in >> this->socialMediaPlatform;
            in.ignore();

            return in;
        }

        ostream& output(ostream& out) const {
            out << "---------------------------------------------------" << endl;
            out << "Campaign name: " << this->campaign_name << "\n";
            out << "Objectives: ";
            int index = 0;
            for (const auto& objective : objectives) {
                if (index == 0) {
                    out << "-" << objective << endl;
                } else {
                    out << "            -" << objective << endl;
                }
                index++;
            }
            out << "Social media platform: " << this->socialMediaPlatform << "\n";
            out << "---------------------------------------------------" << endl;

            return out;
        }

    // Operatorii de citire si afisare
        friend istream& operator>>(istream& in, Campaign& obj) {return obj.input(in);};
        friend ostream& operator<<(ostream& out, const Campaign& obj) {return obj.output(out);}

    // Returneaza toate postarile campaniei
        const list<Post>& getPosts() const {
            return posts;
        }

    // Adauga un obiectiv campaniei
        void addObjective (const std::string& objective) {
            objectives.insert(objective);
        }

    // Functia virtuala implementata
        float calculateTotalCost() const override {return 0.0;}

    // Adauga o postare campaniei
        void addPost(const Post& post) {posts.push_back(post);}

    // Functia template care adauga un obiectiv campaniei
    template <typename T>
    void addCustomObjective(const T& objective) {
        stringstream ss;
        ss << objective;
        objectives.insert(ss.str());
    }

    // Metodele de citire si scriere in fisier
    void writeCampaignToFile(const Campaign& campaign, const std::string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            file << campaign;
            file.close();
            std::cout << "Datele au fost scrise in fisier.\n";
        } else {
            std::cout << "Eroare la deschiderea fisierului.\n";
        }
    }

    void readCampaignFromFile(Campaign& campaign, const std::string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        getline(file, campaign.campaign_name);
        std::string line;
        getline(file, line);
        int numObjectives = stoi(line); // Citirea numărului de obiective din fișier
        for (int i = 0; i < numObjectives; i++) {
            std::getline(file, line);
            campaign.objectives.insert(line);
        }
        getline(file, campaign.socialMediaPlatform);
        file.close();
        cout << "Datele au fost citite din fisier.\n";
    } else {
        cout << "Eroare la deschiderea fisierului.\n";
    }

}
};

// Constructorii
Campaign::Campaign():Client() {
    this->campaign_name = "NULL";
    this->objectives = {};
    this->socialMediaPlatform = "NULL";
};

Campaign::Campaign(const std::string campaign_name,const set<std::string> objectives, const std::string socialMediaPlatform):Client(client_name, company, marketing_budget, contract){
    this->campaign_name = campaign_name;
    this->objectives = objectives;
    this->socialMediaPlatform = socialMediaPlatform;
}

Campaign::Campaign(const Campaign& obj):Client(obj) {
    this->campaign_name = obj.campaign_name;
    this->objectives = obj.objectives;
    this->socialMediaPlatform = obj.socialMediaPlatform;
}

// Operatorul "="
Campaign& Campaign::operator=(const Campaign& obj) {
    if (this != &obj) {
        this->campaign_name = obj.campaign_name;
        this->objectives = obj.objectives;
        this->socialMediaPlatform = obj.socialMediaPlatform;
    }
    return *this;
}

class Invoice : virtual public Client {
    protected:
        std::string address;     // Adresa clientului
        double commission;       // Comisionul agentiei
        int payment_time;        // Data scadenta
        float tax_rates;         // Taxe
        float total_amount;      // Totalul de plata
    public:
    // address
        void setAddress(const std::string newAddress) {this->address = newAddress;}
        std::string getAddress() {return this->address;}

    // commission
        void setCommission(const double newCommission) {this->commission = newCommission;}
        double getCommission() {return this->commission;}

    // payment_time
        void setPaymentTime(const int newPaymentTime) {this->payment_time = newPaymentTime;}
        int getPaymentTime() {return this->payment_time;}

    // tax_rates
        void setTaxRates(const float newTaxRates) {this->tax_rates = newTaxRates;}
        float getTaxRates() {return this->tax_rates;}

    // total_amount
        void setTotalAmount(const float newTotalAmount) {this->total_amount = newTotalAmount;}
        int getTotalAmount() {return this->total_amount;}

    // Constructori
        Invoice();
        Invoice(const std::string address, const double commission, const int payment_time, const float tax_rates, const float total_amount);
        Invoice(const Invoice& obj);

    // Operatorul "="
        Invoice& operator=(const Invoice& obj);

    // Destructor
        virtual ~Invoice(){};

    // Implementarea functiilor virtuale
        istream& input(istream& in) {
            cout << "Address: ";
            getline(in, this->address);
            cout << "Commission(%): ";
            in >> this->commission;
            cout << "Tax rates(%): ";
            in >> this->tax_rates;
            cout << "Payment time(days): ";
            in >> this->payment_time;
            cout << "Total amount($): ";
            in >> total_amount;

            return in;
        }

        ostream& output(ostream& out) const {
            out << "---------------------------------------------------" << endl;
            out << "Client name: " << this->client_name << "\n";
            out << "Address: " << this->address << "\n";
            out << "Commission: " << this->commission << "%" << "\n";
            out << "Payment time: " << this->payment_time << " DAYS" <<"\n";
            out << "Tax rates: " << this->tax_rates << "%" << "\n";
            out << "Total amount: " << this->total_amount << "$" << "\n";
            out << "---------------------------------------------------" << endl;

            return out;
        }

    // Operatorii de citire si afisare
        friend istream& operator>>(istream& in, Invoice& obj){return obj.input(in);};
        friend ostream& operator<<(ostream& out, const Invoice& obj){return obj.output(out);};

    // Calcularea taxelor si a comisionului
        float calculateTotalCost() const override {
            float total_cost;
            total_cost = (this->tax_rates / 100) * this->total_amount + (this->commission / 100) * this->total_amount;
            return total_cost;
        }

        void generateInvoice() {
            cout << "-------- Invoice --------" << endl;
            cout << "Client name: " << client_name << endl;
            cout << "Address: " << address << endl;
            cout << "Commission: " << commission << "%" << endl;
            cout << "Payment time: " << payment_time << " days" << endl;
            cout << "Tax rates: " << tax_rates << "%" << endl;
            cout << "Total taxes: " << calculateTotalCost() << endl;
            cout << "-------------------------" << endl;
        }

    // Clasa template pentru calcularea sumei dupa aplicarea unui discount
        template <typename T>
        T calculateTotalAfterDiscount(const T& discountRate) {
            T discountedAmount = this->total_amount - (this->total_amount * discountRate / 100);
            return discountedAmount;
        }

    // Metodele de citire si scriere in fisier
        void writeInvoiceToFile(const Invoice& invoice, const std::string& filename) {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << invoice;
            file.close();
            cout << "Datele au fost scrise in fisier.\n";
        } else {
            cout << "Eroare la deschiderea fisierului.\n";
        }
    }

    // Implementare pentru metoda virtuală readFromFile
    void readInvoiceFromFile(Invoice& invoice, const std::string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            getline(file, address);
            file >> commission;
            file >> payment_time;
            file >> tax_rates;
            file >> total_amount;
            file.close();
            cout << "Datele au fost citite din fisier.\n";
        } else {
            cout << "Eroare la deschiderea fisierului.\n";
        }
    }

};

// Constructori
Invoice::Invoice():Client() {
    this->address = "NULL";
    this->commission = 0.0;
    this->payment_time = 0;
    this->commission = 0.0;
    this->total_amount = 0.0;
}

Invoice::Invoice(const std::string address, const double commission, const int payment_time, const float tax_rates, const float total_amount):Client(client_name, company, marketing_budget, contract) {
    this->address = address;
    this->commission = commission;
    this->tax_rates = tax_rates;
    this->payment_time = payment_time;
    this->total_amount = total_amount;
}

Invoice::Invoice(const Invoice& obj):Client(obj) {
    this->address = obj.address;
    this->commission = obj.commission;
    this->tax_rates = obj.tax_rates;
    this->payment_time = obj.payment_time;
    this->total_amount = obj.total_amount;
}

//Operatorul "="
Invoice& Invoice::operator=(const Invoice& obj) {
    if(this != &obj) {
        this->address = obj.address;
        this->commission = obj.commission;
        this->tax_rates = obj.tax_rates;
        this->payment_time = obj.payment_time;
        this->total_amount = obj.total_amount;
    }
    return *this;
}

class Post : public Campaign, public Invoice {
    private:
        int likes_count;        // Numarul de likeuri
        int shares_count;       // Numarul de shareuri
        int views_count;        // Numarul de vizualizari
        int post_duration;      // Durata postarii

    public:
    // likes_count
        void setLikesCount(const int newLikesCount) {this->likes_count = newLikesCount;}
        int getLikesCount() {return this->likes_count;}

    // shares_count
        void setSharesCount(const int newSharesCount) {this->shares_count = newSharesCount;}
        int getSharesCount() {return this->shares_count;}

    // views_count
        void setViewsCount(const int newViewsCount) {this->views_count = newViewsCount;}
        int getViewsCount() {return this->views_count;}

    // post_date
        void setPostDate(const int newPostDate) {this->post_duration = newPostDate;}
        int getPostDate() {return this->post_duration;}

    // Constructori
        Post();
        Post(const int likes_count, const int shares_count, const int views_count, const int post_duration);
        Post(const Post& obj);

    // Operatorul "="
        Post& operator=(const Post& obj);

    // Destructor 
        ~Post(){};

    // Functiile virtuale implementate
        istream& input(istream& in) {
            cout << "Likes: ";
            in >> this->likes_count;
            cout << "Shares: ";
            in >> this->shares_count;
            cout << "Views: ";
            in >> this->views_count;
            cout << "Post duration: ";
            in >> this->post_duration;

            return in;
        }

        ostream& output(ostream& out) const {
            out << "---------------------------------------------------" << endl;
            out << "Client name: " << client_name << "\n";
            out << "Campaign name: " <<campaign_name << "\n";
            out << "Likes: " << this->likes_count << "\n";
            out << "Shares: " << this->shares_count << "\n";
            out << "Views: " << this->views_count << "\n";
            out << "Post duration: " << this->post_duration << " DAYS" <<"\n";
            out << "Social media platform: " << socialMediaPlatform << "\n";
            out << "---------------------------------------------------" << endl;

            return out;    
        }

    // Operatorii de citire si afisare
        friend istream& operator>>(istream& in, Post& obj){return obj.input(in);};
        friend ostream& operator<<(ostream& out, const Post& obj){return obj.output(out);};

    // Functia pentru calcularea pretului unei postari in functie de numarul de zile 
        float calculateTotalCost() const override {
            cout << "Price to pay for " << this->post_duration << " DAYS " << "is: ";
            return this->post_duration * 10;
        }

    // Merodele de citire si scriere in fisier 
    void writePostToFile(const Post& post, const std::string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            file << post;
            file.close();
            cout << "Datele au fost scrise in fisier.\n";
        } else {
            cout << "Eroare la deschiderea fisierului.\n";
        }
    }

    void readPostFromFile(Post& post, const std::string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            // Citește datele specifice obiectului Post din fișier
            file >> likes_count >> shares_count >> views_count >> post_duration;
            file.close();
            cout << "Datele au fost citite din fisier.\n";
        } else {
            cout << "Eroare la deschiderea fisierului.\n";
        }
    }

};

Post::Post():Invoice(), Campaign() {
    this->likes_count = 0;
    this->shares_count = 0;
    this->views_count = 0;
    this->post_duration = 0;
}

Post::Post(const int likes_count, const int shares_count, const int views_count, const int post_duration):Invoice(address,commission, payment_time, tax_rates, total_amount), Campaign(campaign_name, objectives,socialMediaPlatform) {
    this->likes_count = likes_count;
    this->shares_count = shares_count;
    this->views_count = views_count;
    this->post_duration = post_duration;
}

Post::Post(const Post& obj):Campaign(obj), Invoice(obj) {
    this->likes_count = obj.likes_count;
    this->shares_count = obj.shares_count;
    this->views_count = obj.views_count;
    this->post_duration = obj.post_duration;
}

Post& Post::operator=(const Post& obj) {
    if(this != &obj) {
        this->likes_count = obj.likes_count;
        this->shares_count = obj.shares_count;
        this->views_count = obj.views_count;
        this->post_duration = obj.post_duration;
    }
    return *this;
}

class SingletonMenu {
private:
    static SingletonMenu* instance;
    list<Client> clients;
    SingletonMenu() {}  // Constructorul este privat pentru a preveni crearea de instante

public:
    static SingletonMenu* getInstance() {
        if (instance == nullptr) {
            instance = new SingletonMenu();
        }
        return instance;
    }

    Client* findClientById(int clientId) {
        for (auto& client : clients) {
            if (client.getID() == clientId) {
                return &client;
            }
        }
        return nullptr;  // Clientul nu a fost găsit
    }

    void showMenu() {
        int choice;
        bool exitMenu = false;

            while (!exitMenu) {
            cout << "===== Meniu Principal =====" << endl;
            cout << "1. Creare client nou" << endl;
            cout << "2. Afisare lista de clienti" << endl;
            cout << "3. Selectare client (dupa ID)" << endl;
            cout << "4. Generare factura pentru client" << endl;
            cout << "5. Citire din fisier" << endl;
            cout << "6. Scriere in fisier" << endl;
            cout << "0. Iesire" << endl;
            cout << "Alegeti o optiune: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    createNewClient();
                    break;
                case 2:
                    displayClientList();
                    break;
                case 3:
                    selectClient();
                    break;
                case 4:
                    generateInvoiceForClient();
                    break;
                case 5:
                    readFromFile();
                    break;
                case 6:
                    writeToFile();
                    break;
                case 0:
                    exitMenu = true;
                    break;
                default:
                    cout << "Optiune invalida. Reincercati!" << endl;
                    break;
            }

            cout << endl;
        }
    }

    void createNewClient() {
        Client client;
        cin.ignore();
        cin >> client;
        clients.push_back(client);
        cout << "Client nou creat!" << endl;
    }

    void displayClientList() {
        cout << "Lista de clienti:" << endl;
        for (const auto& client : clients) {
           cout << client;
        }
    }

    void selectClient() {
        int id;
        cout << "Introduceti ID-ul clientului: ";
        cin >> id;

        // Cautam clientul după ID in lista de clienți
        for (const auto& client : clients) {
            if (client.getID() == id / 2) {
                cout << "Client selectat: ID: " << client.getID() / 2 << ", \nNume: " << client.getClientName() << endl;
                return;
            }
        }
        cout << "Client selectat!" << endl;

        int choice;
        bool exitSubMenu = false;

        while (!exitSubMenu) {
            cout << "===== Meniu Client =====" << endl;
            cout << "1. Afisare campanii pentru client" << endl;
            cout << "2. Adaugare campanie pentru client" << endl;
            cout << "3. Selectare campanie pentru client" << endl;
            cout << "0. inapoi" << endl;
            cout << "Alegeti o optiune: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    displayCampaignsForClient(id);
                    break;
                case 2:
                    enterCampaignForClient(id);
                    break;
                case 3:
                    selectCampaignForClient(id);
                    break;
                case 0:
                    exitSubMenu = true;
                    break;
                default:
                    cout << "Optiune invalida. Reincercati!" << endl;
                    break;
            }

            cout << endl;
        }
    }

    void displayCampaignsForClient(int id) {

    // Cautam clientul dupa ID în lista de clienti
    for (const auto& client : clients) {
        cout << client;
        if (client.getID() == id * 2) {
            cout << "Campanii pentru clientul cu ID-ul " << client.getID() / 2<< ":" << endl;
            client.getCampaigns();
        }
    }

    cout << "Nu s-a gasit niciun client cu ID-ul specificat." << endl;
    }

    void enterCampaignForClient(int id) {
        Campaign campaign;
        cin.ignore();
        cin >> campaign;
        for (auto& client : clients) {
            if(client.getID() == id * 2) {
                client.addCampaign(campaign);
            }
        }
        cout << "Campanie adaugata pentru client!" << endl;
    }

    void selectCampaignForClient(int id) {

        cout << "Campanie selectată pentru client!" << endl;

        int choice;
        bool exitSubMenu = false;

        while (!exitSubMenu) {
           cout << "===== Meniu Campanie =====" <<endl;
           cout << "1. Afisare postari pentru campanie" <<endl;
           cout << "2. Adaugare postare pentru campanie" <<endl;
           cout << "0. Inapoi" <<endl;
           cout << "Alegeti o optiune: ";
           cin >> choice;

            switch (choice) {
                case 1:
                    displayPostsForCampaign();
                    break;
                case 2:
                    enterPostForCampaign();
                    break;
                case 0:
                    exitSubMenu = true;
                    break;
                default:
                    cout << "Opțiune invalidă. Reîncercați!" << endl;
                    break;
            }

            cout << endl;
        }
    }

    void displayPostsForCampaign() {
        cout << "Postari pentru campanie:" << endl;
    }

    void enterPostForCampaign() {
        cout << "Postare adaugata pentru campanie!" << endl;
    }

    void generateInvoiceForClient() {
        cout << "Factura generata pentru client!" << endl;
    }

    void readFromFile() {
        cout << "Citire din fisier realizata!" << endl;
    }

    void writeToFile() {
        cout << "Scriere în fisier realizata!" << endl;
    }
};

SingletonMenu* SingletonMenu::instance = nullptr;

int main() {
    // vector<Client> clients;
    // vector<Campaign> campaigns;
    // vector<Post> posts;
    // vector<Invoice> invoices;

    // Client  a("Andrei", "Amazon", 30000, 1),
    //         b("Mihnea", "Meta", 50200, 1),
    //         c("Ioana", "Huawei", 12800, 0);
    // clients.push_back(a);
    // clients.push_back(b);
    // clients.push_back(c);

    //Campaign d("Mindful",{"Increase brand awareness and visibility", "Drive website traffic and generate leads"},"Instagram");
    //Campaign e("Digital Boost",{"Increase sales and revenue"},"Instagram");
    //Campaign f("Creative Connections",{"Boost social media engagement and follower growth", "Support a cause or charity partnership"}, "Faceook");
    
    
    //clients[0].addCampaign(d);
    //clients[1].addCampaign(e);
    //clients[2].addCampaign(f);

    // Campaign a;
    // Post b;
    // a.addPost(b);
    // const std::list<Post>& campaignPosts = a.getPosts();

    // // Output each post
    // for (const Post& post : campaignPosts) {
    //     std::cout << post << std::endl;
    // }

// Campaign campaign;
// campaign.addCustomObjective(50);  // Adăugare obiectiv personalizat de tip const char*
// campaign.addCustomObjective(std::string("Drive website traffic")); // Adăugare obiectiv personalizat de tip std::string
// campaign.addCustomObjective("Increase brand awareness");  // Eliminare obiectiv personalizat
// cout << campaign;




    // Invoice invoice;
    // invoice.setTotalAmount(150.2);
    // double discountRateDouble = 0.2;
    // float discountRateFloat = 0.15;

    // double discountedAmountDouble = invoice.calculateTotalAfterDiscount(discountRateDouble);
    // float discountedAmountFloat = invoice.calculateTotalAfterDiscount(discountRateFloat);

    // std::cout << "Discounted amount (double): " << discountedAmountDouble << std::endl;
    // std::cout << "Discounted amount (float): " << discountedAmountFloat << std::endl;


// -----------Clasa template

    // Container<Campaign> campaignContainer;
    // Campaign campaign1;
    // Campaign campaign2;
    // cin >> campaign1 >> campaign2;

    // campaignContainer.addItem(campaign1);
    // campaignContainer.addItem(campaign2);
    // campaignContainer.printContainer(campaignContainer);

// ----------Invoice
    // Invoice a;
    // a.setCommission(10);
    // a.setTaxRates(20);
    // a.setTotalAmount(20000);
    // Invoice b(a);
    // Client h;
    // cout << h;
    
    SingletonMenu* menu = SingletonMenu::getInstance();
    menu->showMenu();

    return 0;
}