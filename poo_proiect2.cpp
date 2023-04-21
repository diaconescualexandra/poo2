#include <iostream>
#include <vector>
#include <string>
#include <sstream>
class Persoana {

    private:
        //var statica
        static int numar_persoane;
        int id;
        std::string nume;

    public:

        //fct virtual pt downcasting
        virtual void printInfo() const
        {
            std::cout << "ID: " << id << " Nume: " << nume << std::endl;
        }

        //CONSTR FARA PARAM
        Persoana() : id(0), nume(" ") {}

        //constr cu param
        Persoana(int id, std::string nume) : id(id), nume(nume) {}

        //destructor
        ~Persoana() {}

        //constructor de copiere
        Persoana(const Persoana &persoana) : id(persoana.id), nume(persoana.nume) {}

        std::string get_nume() const
        {
            return nume;
        }

        int get_id() const{
            return id;
        }

        //functie statica
        static int getNumarPersoane()
        {
            return numar_persoane;
        }

     Persoana& operator=(const Persoana& obiect)
     {
        if ( this != &obiect) 
        {
            id=obiect.id;
            nume = obiect.nume;
        }
        return *this;
     }

     friend std::istream& operator>>(std::istream& is, Persoana& p)
     {
        is >> p.id >> p.nume;
        return is;
     }

     friend std::ostream& operator<<(std::ostream& os, const Persoana& p)
     {
        os << p.id << " "<< p.nume;
        return os;
     }
};

//memorarea a n obiecte din clasa persoana

std::vector<Persoana> memorarepersoane(int n)
{
    std::vector<Persoana> objects;

    for (int i = 0; i <= n; i++)
    {
        Persoana obj = Persoana ();
        objects.push_back(obj);
        
    }
    return objects;
}


// citirea a n obiecte din clasa persoana

void citirenobiecte( std::vector<Persoana> &objects)
{
    for (int i = 0; i <= objects.size(); i++)
    {
        std::cin>>objects[i];

    }
}

// afisarea a n obiecte din clasa persoana

void afisarenobiecte( const std::vector<Persoana> &objects)
{
    for (int i = 0; i <= objects.size(); i++)
    {
        std::cout << objects[i]<<std::endl;
    }
}

//initializare var statica
int Persoana::numar_persoane = 8;

class Abonat : public Persoana{
    private:
        std::string nr_telefon;

    public:
    //constructor param
        Abonat(int id = 0, const std::string& nr = "", const std::string& nume = "") : Persoana(id, nume), nr_telefon(nr) {}

        // constr fara param + encapsulare
        Abonat() : Persoana(0, ""), nr_telefon("") {}

        // copy constr
        Abonat(const Abonat &other): Persoana(other), nr_telefon(other.nr_telefon) {}

        ~Abonat() {}

    
    //overload =
        Abonat operator=(const Abonat& obiect)
        {
            if(this!= &obiect)
            { 
                this-> Persoana::operator=(obiect); 
            }
            return *this;
        }
};

class Abonat_Skype : public Abonat{
    private:
        std::string id_skype;
    public:
        Abonat_Skype(int id = 0, const std::string& nr = "", const std::string& nume = "", const std::string& Id_skype = "") : Abonat(id, nr, nume), id_skype(Id_skype) {}

        //constr fara param + encapsulare
        Abonat_Skype() : Abonat(0, "", ""), id_skype("") {}

        // copy constr
        Abonat_Skype(const Abonat_Skype& other) : Abonat( other) ,id_skype(other.id_skype) {}

        ~Abonat_Skype() {}

        //overload = 

        Abonat_Skype& operator=(Abonat_Skype& obiect)
        {
            if(this!= &obiect)
            {
                this->Abonat::operator=(obiect);
            }
            return *this;
        }

        
};

class Abonat_Skype_Romania : virtual public Abonat_Skype
{
    private:
       std::string adresa_email;

    public:
        Abonat_Skype_Romania(int id = 0, const std::string& nr = "", const std::string& nume = "", const std::string& Id_skype = 0, const std::string &Adresa_email = 0) : Abonat_Skype(id, nr, nume, Id_skype), adresa_email(Adresa_email) {}

        // constr fara param + encapsulare
        Abonat_Skype_Romania() : Abonat_Skype(0,"","", ""), adresa_email("") {}

        //copy constr
        Abonat_Skype_Romania(const Abonat_Skype_Romania& other): Abonat_Skype(other), adresa_email(other.adresa_email) {}

        ~Abonat_Skype_Romania() {}

        //overload =
        Abonat_Skype_Romania& operator=(Abonat_Skype_Romania& obiect)
        {
            if (this != &obiect)
            {
                this->Abonat_Skype::operator=(obiect);
            }
            return *this;
        }
};


class Abonat_Skype_Extern : virtual public Abonat_Skype{
    std::string tara;

    public:
        Abonat_Skype_Extern(int id = 0, const std::string& nr = "", const std::string& nume = "", const std::string& Id_skype = 0, const std::string& Adresa_email = 0, const std::string& Tara = 0) : Abonat_Skype(id, nr, nume, Id_skype), tara(Tara) {}

        // constr fara param + encapsulare
        Abonat_Skype_Extern() : Abonat_Skype(0,"","",""), tara("") {}

        //copy constr
        Abonat_Skype_Extern(const Abonat_Skype_Extern& other): Abonat_Skype(other), tara(other.tara) {}

        //overload=
        Abonat_Skype_Extern& operator=(Abonat_Skype_Extern& obiect)
        {
            if ( this != &obiect)
            {
                this->Abonat_Skype::operator=(obiect);
            }
            return *this;
        }
};

class Agenda {
    private:
    std::vector<Abonat_Skype_Extern*> subscribers;

    public:
    //constr neparam
    Agenda () {}
    //constr param
    Agenda(const Abonat_Skype_Extern &subscriber)
    {
            subscribers.push_back(new Abonat_Skype_Extern(subscriber));
    }

    //copy constr
    Agenda(const Agenda& agenda): subscribers(agenda.subscribers) {}

    ~Agenda() {
        for (int i = 0; i < subscribers.size(); i++)
        {
            Abonat_Skype_Extern *sub = subscribers[i];
            delete sub;
        }
    }

    std::vector<Abonat_Skype_Extern *> get_subscribers() const
    {
            return subscribers;
    }

    Agenda operator=(const Agenda& ob)
    {
            if (this != &ob)
            {
                subscribers = ob.subscribers;
            }
            return *this;
    }

    friend std::istream& operator>>(std::istream &is, Agenda &a)
    {
            for (int i = 0; i < a.subscribers.size(); i++)
            {
                Abonat_Skype_Extern *&subscriber = a.subscribers[i];
                is >> *subscriber;
            }
            return is;
    }

    friend std::ostream &operator<<(std::ostream &os, const Agenda &a)
    {
            for (int i = 0; i < a.subscribers.size(); i++)
            {
                const Abonat_Skype_Extern *subscriber = a.subscribers[i];
                os << *subscriber << std::endl;
            }
            return os;
    }

    std::string get_id(const std::string &nume) const
    {
            for (int i = 0; i < subscribers.size(); i++)
            {
                const Abonat_Skype_Extern *sub = subscribers[i];
                if (sub->get_nume() == nume)
                {
                    std::ostringstream out;
                    out << sub->get_id();
                    return out.str();
                }
            }

            throw std::runtime_error("Subscriber not found");
    }

    //overload []

    int operator[](const std::string &name) const
    {
        for (int i = 0; i < subscribers.size(); i++)
        {
            if (subscribers[i]->get_nume() == name)
            {
                return subscribers[i]->get_id();
            }
        }

            throw std::runtime_error("Subscriber not found!");
    }
};

int main()
{ 
    Abonat a(9, "0771234567", "will smith");

    // upcasting
    Persoana *p = &a;
    std::cout << *p << std::endl;

    //downcast
    Abonat b(1, "1234567890", "John Doe");
    Persoana *j = &b;

    // downcast to Abonat and call printInfo() function
    if (Abonat *ab = dynamic_cast<Abonat *>(j))
    {
        ab->printInfo();
    }
    else
    {
        std::cout << "failed";
    }

    Abonat_Skype_Extern subscriber1(1, "09877", "John", "123", "bhwkb", "bbk");
    Agenda agenda(subscriber1);

    std::cout << agenda["John"] << std::endl;

    std::cout<< Persoana::getNumarPersoane();



    return 0;
}
