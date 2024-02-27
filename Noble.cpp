// Zoe Dauphinee, hw07, implementation file for Noble types

#include "Noble.h"
#include "Protector.h"

namespace WarriorCraft {
    /*
    methods for Noble
    */

    // constructor
    Noble::Noble(const std::string& name) 
        : name(name), dead(false) {}

    // getter for name
    const std::string& Noble::get_name() const {
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
        std::cout << std::endl << name << " battles " << opponent.name << std::endl;
        battle_cry();
        opponent.battle_cry();
        double my_strength = get_strength();
        double opp_strength = opponent.get_strength();

        // both dead
        if (dead && opponent.dead) {
            std::cout << "Oh, NO!  They're both dead!  Yuck!" << std::endl;
            return;
        }
        // i'm dead
        else if (dead) {
            std::cout << "He's dead, " << opponent.name << std::endl;
            return;
        }
        // opponent is dead
        else if (opponent.dead) {
            std::cout << "He's dead, " << name << std::endl;
            return;
        }
        // i'm stronger than opponent
        if (my_strength > opp_strength) {
            double reduce_by = (opp_strength/my_strength);
            this->win(reduce_by);
            opponent.lose();
            std::cout << name << " defeats " << opponent.name << std::endl;
        }
        // opponent is stronger than me
        else if (opp_strength > my_strength) {
            double reduce_by = (my_strength/opp_strength);
            opponent.win(reduce_by);
            this->lose();
            std::cout << opponent.name << " defeats " << name << std::endl;
        }
        // equal strength
        else if (my_strength == opp_strength) {
            this->lose();
            opponent.lose();
            std::cout << "Mutual Annihilation: ";
            std::cout << name << " and " << opponent.name << " die at each other's hands\n";
        }
    }

    // display for Noble
    void Noble::display(std::ostream& os) const {
        os << name << " has ";
    }

    // output operator for Noble
    std::ostream& operator<<(std::ostream& os, const Noble& noble) {
        noble.display(os);
        return os;
    }


    /*
    methods for Lord
    */

    // constructor
    Lord::Lord(const std::string& name) 
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
                    std::cout << protector.get_name() << ", you don't work for me any more! -- ";
                    std::cout << get_name() << "." << std::endl;
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
    void Lord::display(std::ostream& os) const {
        Noble::display(os);
        os << "army of size: " << army.size() << std::endl;
        for (size_t index = 0; index < army.size(); ++index) {
            os << "    " << *army[index];
        }
    }


    /*
    methods for PersonWithStrengthToFight
    */

    // constructor
    PersonWithStrengthToFight::PersonWithStrengthToFight(const std::string& name, double strength) 
        : Noble(name), strength(strength) {}

    // getter for strength
    const double PersonWithStrengthToFight::get_strength() const {
        return strength;
    }

    // battle cry
    void PersonWithStrengthToFight::battle_cry() {
        std::cout << "Ugh!\n";
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
    void PersonWithStrengthToFight::display(std::ostream& os) const {
        Noble::display(os);
        os << "strength: " << strength;
    }
}