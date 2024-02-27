// Zoe Dauphinee, hw07, header file for Protector types

#ifndef PROTECTOR_H
#define PROTECTOR_H

#include <string>
#include <vector>
#include <iostream>
#include <cassert>

namespace WarriorCraft {
    class Noble;
    class Lord;

    // base class
    class Protector {
        private:
            std::string name;
            double strength;
            Lord* employer;

            friend std::ostream& operator<<(std::ostream& os, const Protector& protector);

        public:
            Protector(const std::string& name, double strength);
            const std::string& get_name() const;
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
            Wizard(const std::string& name, double strength);
            void fight();
    };

    // Warrior - fight without magic - derived from Protector
    class Warrior : public Protector {
        public:
            Warrior(const std::string& name, double strength);
            void fight();
    };

    // Archer - derived from Warrior
    class Archer : public Warrior {
        public:
            Archer(const std::string& name, double strength);
            void fight();
    };

    // Swordsman - derived from Warrior
    class Swordsman : public Warrior {
        public:
            Swordsman(const std::string& name, double strength);
            void fight();
    };
}

#endif