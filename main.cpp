#include <string>
#include <iostream>
#include <vector>
#include <functional>

class masina {
    static const std::string desc;
    static const std::string model;
protected:
    std::string marca;

    virtual void citire( std::istream& );

    virtual void afisare( std::ostream& ) const;

public:
    virtual ~masina();

    explicit masina( const std::string& marcaData = "" );

    masina( const masina& );

    masina& operator=( const masina& marcaData );

    const std::string getMarca() const;

    static const std::string getDesc();

    static const std::string getModel();

    friend std::istream& operator>>( std::istream&, masina& );

    friend std::ostream& operator<<( std::ostream&, const masina& );
};

class cabrio : public masina {
    static const std::string desc;
    static const std::string model;

    void citire( std::istream& ) override;

    void afisare( std::ostream& ) const override;

public:
    cabrio();

    cabrio( const cabrio& );

    ~cabrio() override;

    cabrio& operator=( const cabrio& );

    friend std::istream& operator>>( std::istream&, masina& );

    friend std::ostream& operator<<( std::ostream&, const masina& );
};

class coupe : public masina {
    static const std::string desc;
    static const std::string model;

    void citire( std::istream& ) override;

    void afisare( std::ostream& ) const override;

public:
    coupe();

    coupe( const coupe& );

    ~coupe() override;

    coupe& operator=( const coupe& );

    friend std::istream& operator>>( std::istream&, masina& );

    friend std::ostream& operator<<( std::ostream&, const masina& );
};

class hotHatch : public masina {
    static const std::string desc;
    static const std::string model;

    void citire( std::istream& ) override;

    void afisare( std::ostream& ) const override;

public:
    hotHatch();

    hotHatch( const hotHatch& );

    ~hotHatch() override;

    hotHatch& operator=( const hotHatch& );

    friend std::istream& operator>>( std::istream&, masina& );

    friend std::ostream& operator<<( std::ostream&, const masina& );
};

class supersport : public masina {
    static const std::string desc;
    static const std::string model;

    void citire( std::istream& ) override;

    void afisare( std::ostream& ) const override;

public:
    supersport();

    supersport( const supersport& );

    ~supersport() override;

    supersport& operator=( const supersport& );

    friend std::istream& operator>>( std::istream&, masina& );

    friend std::ostream& operator<<( std::ostream&, const masina& );
};

template < class tipMasina >
class expozitie {
    int nrObiecteExpuse;
    std::vector< std::pair< masina*, const std::string >> v;

    void push( tipMasina* masina ) {
        v.emplace_back( masina, typeid( tipMasina ).name() );
        nrObiecteExpuse++;
    }

public:
    int getNrObiecte() const {
        return nrObiecteExpuse;
    }

    expozitie< tipMasina >() {
        nrObiecteExpuse = 0;
    }

    expozitie< tipMasina >( const expozitie< tipMasina >& ) = delete;

    const expozitie< tipMasina >& operator=( const expozitie< tipMasina >& ) = delete;

    ~expozitie< tipMasina >() {
        for ( auto& i:v ) {
            delete i.first;
        }
        v.clear();
        nrObiecteExpuse = 0;
    }

    friend std::istream& operator>>( std::istream&, expozitie< masina >& );

    friend std::ostream& operator<<( std::ostream&, const expozitie< masina >& );
};


template <>
class expozitie< supersport > {
    int nrObiecteExpuse;
    int nrObiecteVandute;
    std::vector< std::pair< supersport*, int>> v;
    std::vector< std::pair< supersport*, int>> vandute;

    void push( supersport* car ) {
        v.emplace_back( car, -1 );
        nrObiecteExpuse++;
    }

public:
    expozitie< supersport >() {
        nrObiecteExpuse = 0;
        nrObiecteVandute = 0;
    }

    expozitie< supersport >( const expozitie< supersport >& ) = delete;

    const expozitie< supersport >& operator=( const expozitie< supersport >& ) = delete;

    void sale( const int& poz, const int& price ) {
        if ( poz < nrObiecteExpuse ) {
            vandute.emplace_back( v[ poz ].first, price );
            v[ poz ] = v.back();
            v.pop_back();
            nrObiecteVandute++;
            nrObiecteExpuse--;
        }
        else
            throw std::bad_function_call();
    }

    ~expozitie< supersport >() {
        for ( auto& i:v ) {
            delete i.first;
        }
        v.clear();
        for ( auto& i:vandute ) {
            delete i.first;
        }
        vandute.clear();
        nrObiecteExpuse = 0;
        nrObiecteVandute = 0;
    }

    friend std::istream& operator>>( std::istream&, expozitie< supersport >& );

    friend std::ostream& operator<<( std::ostream&, const expozitie< supersport >& );

    expozitie< supersport >& operator-=( std::pair< const int&, const int& > myPair ) {
        sale( myPair.first, myPair.second );
        return *this;
    }
};

const std::string masina::desc = "";
const std::string masina::model = "";

const std::string masina::getMarca() const {
    return marca;
}

const std::string masina::getDesc() {
    return desc;
}

const std::string masina::getModel() {
    return model;
}

masina::~masina() {
    marca = "";
}

masina::masina( const std::string& marcaData ) : marca( marcaData ) {}

masina& masina::operator=( const masina& masinaData ) {
    marca = masinaData.marca;
    return *this;
}

std::istream& operator>>( std::istream& in, masina& car ) {
    car.citire( in );
    return in;
}

std::ostream& operator<<( std::ostream& out, const masina& car ) {
    car.afisare( out );
    return out;
}

void masina::citire( std::istream& in ) {
    in >> marca;
}

void masina::afisare( std::ostream& out ) const {
    out << "marca: " << marca;
}

masina::masina( const masina& car ) : marca( car.marca ) {}


const std::string cabrio::desc = "modele decapotabile cu acoperiș metalic sau din material textil";
const std::string cabrio::model = typeid( cabrio ).name();

cabrio::cabrio() : masina() {}

cabrio::cabrio( const cabrio& car ) : masina( car ) {}

cabrio::~cabrio() {}

cabrio& cabrio::operator=( const cabrio& car ) {
    marca = car.marca;
    return *this;
}

void cabrio::citire( std::istream& in ) {
    masina::citire( in );
}

void cabrio::afisare( std::ostream& out ) const {
    masina::afisare( out );
    out << ";\n model: " << model << ";\n descriere: " << desc;
}

const std::string coupe::desc = "";
const std::string coupe::model = typeid( coupe ).name();

coupe::coupe() : masina() {}

coupe::coupe( const coupe& car ) : masina( car ) {}

coupe::~coupe() {}

coupe& coupe::operator=( const coupe& car ) {
    marca = car.marca;
    return *this;
}

void coupe::citire( std::istream& in ) {
    masina::citire( in );
}

void coupe::afisare( std::ostream& out ) const {
    masina::afisare( out );
    out << ";\n model: " << model << ";\n descriere: " << desc;
}

const std::string hotHatch::desc = "modele hatckback de clasa mica și compacta cu motoare performante ce au la bază modele obișnuite";
const std::string hotHatch::model = typeid( hotHatch ).name();

hotHatch::hotHatch() : masina() {}

hotHatch::hotHatch( const hotHatch& car ) : masina( car ) {}

hotHatch::~hotHatch() {}

hotHatch& hotHatch::operator=( const hotHatch& car ) {
    marca = car.marca;
    return *this;
}

void hotHatch::citire( std::istream& in ) {
    masina::citire( in );
}

void hotHatch::afisare( std::ostream& out ) const {
    masina::afisare( out );
    out << ";\n model: " << model << ";\n descriere: " << desc;
}

const std::string supersport::desc = "masini de viteza";
const std::string supersport::model = typeid( supersport ).name();

supersport::supersport() : masina() {}

supersport::supersport( const supersport& car ) : masina( car ) {}

supersport::~supersport() {}

supersport& supersport::operator=( const supersport& car ) {
    marca = car.marca;
    return *this;
}

void supersport::citire( std::istream& in ) {
    masina::citire( in );
}

void supersport::afisare( std::ostream& out ) const {
    masina::afisare( out );
    out << ";\n model: " << model << ";\n descriere: " << desc;
}

std::istream& operator>>( std::istream& in, expozitie< masina >& expo ) {
    int opt( -1 );
    in >> opt;
    masina* car;
    if ( opt == 1 ) {
        car = new cabrio;
        in >> *dynamic_cast<cabrio*>(car);
    }
    else if ( opt == 2 ) {
        car = new coupe;
        in >> *dynamic_cast<coupe*>(car);
    }
    else if ( opt == 3 ) {
        car = new hotHatch;
        in >> *dynamic_cast<hotHatch*>(car);
    }
    else if ( opt == 4 ) {
        car = new supersport;
        in >> *dynamic_cast<supersport*>(car);
    }
    else
        throw std::bad_function_call();
    expo.push( car );
    return in;
}

std::ostream& operator<<( std::ostream& out, const expozitie< masina >& expo ) {
    for ( auto& i:expo.v ) {
        std::cout << *i.first << "\n\n";
    }
    return out;
}

std::istream& operator>>( std::istream& in, expozitie< supersport >& expo ) {
    supersport* car;
    car = new supersport;
    in >> *dynamic_cast<supersport*>(car);
    expo.push( car );
    return in;
}

std::ostream& operator<<( std::ostream& out, const expozitie< supersport >& expo ) {
    std::cout << "Masini expuse:\n";
    for ( auto& i:expo.v ) {
        std::cout << *i.first << "\n\n";
    }
    std::cout << "Masini vandute\n";
    for ( auto& i:expo.vandute ) {
        std::cout << *i.first << "\npret vanzare: " << i.second << "\n\n";
    }
    return out;
}

int main() {
    expozitie< masina > expo;
    expozitie< supersport > expoSport;
    masina car;
    int optiuneMeniu;
    std::cout << "opt1: citeste o masina in expozitia generala\n";
    std::cout << "opt2: afisare toate masinile\n";
    std::cout << "opt3: citeste o masina in expozitia sport\n";
    std::cout << "opt4: afisare toate masinile sport expuse & vandute\n";
    std::cout << "opt5: vinde o masina\n";
    std::cout << "opt(-1): exit\n\n";
    std::cout << "Introduceti optiune: ";
    while ( std::cin >> optiuneMeniu ) {
        try {
            if ( optiuneMeniu == 1 ) {
                std::cout << "1 cabrio, 2 coupe, 3 hotHatch, 4 supersport\n";
                std::cout << "format: tip numeProducator\n";
                std::cin >> expo;
            }
            else if ( optiuneMeniu == 2 ) {
                std::cout << expo;
            }
            else if ( optiuneMeniu == 3 ) {
                std::cout << "format: numeProducator\n";
                std::cin >> expoSport;
            }
            else if ( optiuneMeniu == 4 ) {
                std::cout << expoSport;
            }
            else if ( optiuneMeniu == 5 ) {
                int price;
                std::cout << "indice masina de vandut: ";
                std::cin >> optiuneMeniu;
                std::cout << "pret vanzare: ";
                std::cin >> price;
                expoSport -= std::make_pair( optiuneMeniu, price );
            }
            else if ( optiuneMeniu < 0 )
                break;
            else
                std::cout << "Optiune invalida\n";
        }
        catch ( std::exception& e ) {
            std::cout << "Exceptie aruncata: " << e.what() << '\n';
        }
        std::cout << "Introduceti optiune: ";
    }
    return 0;
}
