// Zoe Dauphinee, hw07, Nobles and Protectors - inheritance

#include <string>
#include <vector>
#include <iostream>
#include <cassert>
using namespace std;


class Noble;
class Lord;

//
// Protectors
//

// base class
class Protector {
    private:
        string name;
        double strength;
        Lord* employer;

        friend ostream& operator<<(ostream& os, const Protector& protector);

    public:
        Protector(const string& name, double strength);
        const string& get_name() const;
        const double get_strength() const;
        const Lord* get_employer() const;
        void change_strength(double new_strength);
        const bool isHired() const;
        void change_employer(Lord* new_boss);
        void remove_employer();
        void runaway();
        virtual void fight() = 0;
};

// Wizard - fight with magic - derived from Protector
class Wizard : public Protector {
    public:
        Wizard(const string& name, double strength);
        void fight();
};

// Warrior - fight without magic - derived from Protector
class Warrior : public Protector {
    public:
        Warrior(const string& name, double strength);
        void fight();
};

// Archer - derived from Warrior
class Archer : public Warrior {
    public:
        Archer(const string& name, double strength);
        void fight();
};

// Swordsman - derived from Warrior
class Swordsman : public Warrior {
    public:
        Swordsman(const string& name, double strength);
        void fight();
};


//
// Nobles
//

// base class
class Noble {
    private:
        string name;
        bool dead;

        friend ostream& operator<<(ostream& os, const Noble& Noble);

    public:
        Noble(const string& name);
        const string& get_name() const;
        const bool get_life_status() const;
        void change_life_status(bool status);
        virtual const double get_strength() const = 0;
        void battle(Noble& opponent);
        virtual void battle_cry() = 0;
        virtual void win(double reduce_by) = 0;
        virtual void lose() = 0;
        virtual void display(ostream& os) const = 0;
};

// Lord of the Land - derived from Noble
// fight with armies
class Lord : public Noble {
    private:
        vector<Protector*> army;

    public:
        Lord(const string& name);
        const double get_strength() const;
        bool hires(Protector& protector);
        bool fires(Protector& protector);
        void loses_protector(Protector& runaway);
        const double army_strength();
        void battle_cry();
        void win(double reduce_by);
        void lose();
        void display(ostream& os) const;
};

// Lord With Strength to Fight - derived from Noble
// fight on their own
class PersonWithStrengthToFight : public Noble {
    private:
        double strength;

    public:
        PersonWithStrengthToFight(const string& name, double strength);
        const double get_strength() const;
        void battle_cry();
        void win(double reduce_by);
        void lose();
        void display(ostream& os) const;
};



//
// main - test code
//

int main() {
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250); 	
    Lord janet("Janet");	
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);	
    janet.hires(stout);	
    janet.hires(samantha);     // fails because samantha works for sam.
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);	
    cout << "\n==========\nNobles: \n"
	 << sam << endl
	 << randy << endl
	 << janet << endl
	 << barclay << endl
	 << joe << endl
	 << "\n==========\n";
    joe.battle(randy);	            // joe has no army and dies.
    joe.battle(sam);	            // joe is dead
    janet.battle(barclay);          // barclay wins
    Archer pethora("Pethora", 50);	
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);          // janet is dead, so can't hire
    sam.hires(thora);              // sam brings in reinforcements
    sam.hires(pethora);
    sam.hires(merlin);
    janet.battle(barclay);	   // Silly janet
    sam.battle(barclay);           // Go Sam!
    samantha.runaway();            // Samantha has had enough
    sam.fires(thora);              // These layoffs! Sam fires thora.
    joe.battle(barclay);           // They're both dead already

    cout << "\n==========\nNobles: \n"
	 << sam << endl
	 << randy << endl
	 << janet << endl
	 << barclay << endl
	 << joe << endl
	 << "==========\n";
} // main



/*
methods for Protector
*/

// constructor
Protector::Protector(const string& name, double strength) 
    : name(name), strength(strength), employer(nullptr) {}

// getter for name
const string& Protector::get_name() const {
    return name;
}

// getter for strength
const double Protector::get_strength() const {
    return strength;
}

// getter for employer
const Lord* Protector::get_employer() const {
    return employer;
}

// change strength to new value
void Protector::change_strength(double new_strength) {
    strength = new_strength;
}

// false if employer = nullptr, true otherwise
const bool Protector::isHired() const {
    if (employer) {
        return true;
    }
    return false;
}

// assigns employer to new Noble address
void Protector::change_employer(Lord* new_boss) {
    employer = new_boss;
}

// removes employer (sets to nullptr)
void Protector::remove_employer() {
    employer = nullptr;
}

// Protector runs away (no longer employed), tells Noble
void Protector::runaway() {
    employer->loses_protector(*this);
    cout << name << " flees in terror, abandoning his lord, " << 
    employer->get_name() << endl;
    remove_employer();
}

// output operator for Protector
ostream& operator<<(ostream& os, const Protector& protector) {
    os << protector.name << " has strength: " << protector.strength << endl;
    return os;
}

/*
methods for Wizard
*/

// constructor
Wizard::Wizard(const string& name, double strength) 
    : Protector(name, strength) {}

// fight statement
void Wizard::fight() {
    cout << "POOF!\n";
}

/*
methods for Warrior
*/

// constructor
Warrior::Warrior(const string& name, double strength) 
    : Protector(name, strength) {}

// fight statement
void Warrior::fight() {
    cout << " says: Take that in the name of my lord, ";
}

/*
methods for Archer
*/

// constructor
Archer::Archer(const string& name, double strength) 
    : Warrior(name, strength) {}

// fight statement
void Archer::fight() {
    cout << "TWANG!    " << get_name();
    Warrior::fight();
    cout << get_employer()->get_name() << endl;
}

/*
methods for Swordsman
*/

// constructor
Swordsman::Swordsman(const string& name, double strength) 
    : Warrior(name, strength) {}

// fight statement
void Swordsman::fight() {
    cout << "CLANG!    " << get_name();
    Warrior::fight();
    cout << get_employer()->get_name() << endl;
}



/*
methods for Noble
*/

// constructor
Noble::Noble(const string& name) 
    : name(name), dead(false) {}

// getter for name
const string& Noble::get_name() const {
    return name;
}

// getter for dead/alive
const bool Noble::get_life_status() const {
    return dead;
}

// changes life status
void Noble::change_life_status(bool status) {
    dead = status;
}

// two nobles battle, outcome based on army/individual strengths
void Noble::battle(Noble& opponent) {
    cout << endl << name << " battles " << opponent.name << endl;
    battle_cry();
    opponent.battle_cry();
    double my_strength = get_strength();
    double opp_strength = opponent.get_strength();

    // both dead
    if (dead && opponent.dead) {
        cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
        return;
    }
    // i'm dead
    else if (dead) {
        cout << "He's dead, " << opponent.name << endl;
        return;
    }
    // opponent is dead
    else if (opponent.dead) {
        cout << "He's dead, " << name << endl;
        return;
    }
    // i'm stronger than opponent
    if (my_strength > opp_strength) {
        double reduce_by = (opp_strength/my_strength);
        this->win(reduce_by);
        opponent.lose();
        cout << name << " defeats " << opponent.name << endl;
    }
    // opponent is stronger than me
    else if (opp_strength > my_strength) {
        double reduce_by = (my_strength/opp_strength);
        opponent.win(reduce_by);
        this->lose();
        cout << opponent.name << " defeats " << name << endl;
    }
    // equal strength
    else if (my_strength == opp_strength) {
        this->lose();
        opponent.lose();
        cout << "Mutual Annihilation: ";
        cout << name << " and " << opponent.name << " die at each other's hands\n";
    }
}

// display for Noble
void Noble::display(ostream& os) const {
    os << name << " has ";
}

// output operator for Noble
ostream& operator<<(ostream& os, const Noble& noble) {
    noble.display(os);
    return os;
}


/*
methods for Lord
*/

// constructor
Lord::Lord(const string& name) 
    : Noble(name), army(0) {}

// getter for strength (calculates army strength)
const double Lord::get_strength() const {
    double strength = 0;
    for (size_t index = 0; index < army.size(); ++index) {
        strength += army[index]->get_strength();
    }
    return strength;
}

// hire a Protector (returns false if fails)        
bool Lord::hires(Protector& protector) {
    if (!get_life_status()) {
        // if Lord is not dead, check to see if Protector is already employed
        // Protector is employed (fail)
        if (protector.isHired()) {
            return false;
        }
        // Protector is unemployed (succeed)
        else {
            army.push_back(&protector);
            protector.change_employer(this);
            return true;
        }
    }
    // Protector is dead (fail)
    return false;
}

// fire a Protector (returns false if fails)        
bool Lord::fires(Protector& protector) {
    if (!get_life_status()) {
        // if Lord is not dead, check to see if Protector is in Lord's army
        for (size_t index = 0; index < army.size(); ++index) {
            // Protector found, go through with termination
            if (army[index] == &protector) {
                protector.remove_employer();
                cout << protector.get_name() << ", you don't work for me any more! -- ";
                cout << get_name() << "." << endl;
                for (size_t index2 = index; index2 < army.size() - 1; ++index2) {
                    army[index2] = army[index2 + 1];
                }
                army.pop_back();
                return true;
            }
        }
        // Protector isn't in Lord's army
        return false;
    }
    // Lord doesn't exist
    return false;
}

// Protector ran away
void Lord::loses_protector(Protector& runaway) {
    for (size_t index = 0; index < army.size(); ++index) {
        if (army[index] == &runaway) {
            for (size_t index2 = index; index2 < army.size() - 1; ++index2) {
                    army[index2] = army[index2 + 1];
                }
                army.pop_back();
        }
    }
}

// battle cry
void Lord::battle_cry() {
    if (!get_life_status()) {
        for (size_t index = 0; index < army.size(); ++index) {
            if (army[index]) {
                army[index]->fight();
            }
        }
    }
}

// army strength gets reduced
void Lord::win(double reduce_by) {
    for (size_t index = 0; index < army.size(); ++index) {
        double new_strength = army[index]->get_strength() * (1-reduce_by);
        army[index]->change_strength(new_strength);
    }
}

// Lord and army die (also called when strengths are =)
void Lord::lose() {
    // army strength gets set to 0
    for (size_t index = 0; index < army.size(); ++index) {
        army[index]->change_strength(0);
    }
    // Lord dies
    change_life_status(true);
}

// display for Lord
void Lord::display(ostream& os) const {
    Noble::display(os);
    os << "army of size: " << army.size() << endl;
    for (size_t index = 0; index < army.size(); ++index) {
        os << "    " << *army[index];
    }
}


/*
methods for PersonWithStrengthToFight
*/

// constructor
PersonWithStrengthToFight::PersonWithStrengthToFight(const string& name, double strength) 
    : Noble(name), strength(strength) {}

// getter for strength
const double PersonWithStrengthToFight::get_strength() const {
    return strength;
}

// battle cry
void PersonWithStrengthToFight::battle_cry() {
    cout << "Ugh!\n";
}

// PersonWithStrengthToFight strength gets reduced
void PersonWithStrengthToFight::win(double reduce_by) {
    strength = strength * (1-reduce_by);
}

// PersonWithStrengthToFight dies (also called when strengths are =)
void PersonWithStrengthToFight::lose() {
    strength = 0;
    change_life_status(true);
}

// display for PersonWithStrengthToFight
void PersonWithStrengthToFight::display(ostream& os) const {
    Noble::display(os);
    os << "strength: " << strength;
}