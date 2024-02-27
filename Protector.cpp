// Zoe Dauphinee, hw07, implementation file for Protector types

#include "Noble.h"
#include "Protector.h"

namespace WarriorCraft {
    /*
    methods for Protector
    */

    // constructor
    Protector::Protector(const std::string& name, double strength) 
        : name(name), strength(strength), employer(nullptr) {}

    // getter for name
    const std::string& Protector::get_name() const {
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
        std::cout << name << " flees in terror, abandoning his lord, " << 
        employer->get_name() << std::endl;
        remove_employer();
    }

    // output operator for Protector
    std::ostream& operator<<(std::ostream& os, const Protector& protector) {
        os << protector.name << " has strength: " << protector.strength << std::endl;
        return os;
    }

    /*
    methods for Wizard
    */

    // constructor
    Wizard::Wizard(const std::string& name, double strength) 
        : Protector(name, strength) {}

    // fight statement
    void Wizard::fight() {
        std::cout << "POOF!\n";
    }

    /*
    methods for Warrior
    */

    // constructor
    Warrior::Warrior(const std::string& name, double strength) 
        : Protector(name, strength) {}

    // fight statement
    void Warrior::fight() {
        std::cout << " says: Take that in the name of my lord, ";
    }

    /*
    methods for Archer
    */

    // constructor
    Archer::Archer(const std::string& name, double strength) 
        : Warrior(name, strength) {}

    // fight statement
    void Archer::fight() {
        std::cout << "TWANG!    " << get_name();
        Warrior::fight();
        std::cout << get_employer()->get_name() << std::endl;
    }

    /*
    methods for Swordsman
    */

    // constructor
    Swordsman::Swordsman(const std::string& name, double strength) 
        : Warrior(name, strength) {}

    // fight statement
    void Swordsman::fight() {
        std::cout << "CLANG!    " << get_name();
        Warrior::fight();
        std::cout << get_employer()->get_name() << std::endl;
    }
}