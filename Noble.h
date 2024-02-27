// Zoe Dauphinee, hw07, header file for Noble types

#ifndef NOBLE_H
#define NOBLE_H

#include <string>
#include <vector>
#include <iostream>
#include <cassert>

namespace WarriorCraft {
    class Protector;

    // base class
    class Noble {
        private:
            std::string name;
            bool dead;

            friend std::ostream& operator<<(std::ostream& os, const Noble& Noble);

        public:
            Noble(const std::string& name);
            const std::string& get_name() const;
            const bool get_life_status() const;
            void change_life_status(bool status);
            virtual const double get_strength() const = 0;
            void battle(Noble& opponent);
            virtual void battle_cry() = 0;
            virtual void win(double reduce_by) = 0;
            virtual void lose() = 0;
            virtual void display(std::ostream& os) const = 0;
    };

    // Lord of the Land - derived from Noble
    // fight with armies
    class Lord : public Noble {
        private:
            std::vector<Protector*> army;

        public:
            Lord(const std::string& name);
            const double get_strength() const;
            bool hires(Protector& protector);
            bool fires(Protector& protector);
            void loses_protector(Protector& runaway);
            const double army_strength();
            void battle_cry();
            void win(double reduce_by);
            void lose();
            void display(std::ostream& os) const;
    };

    // Lord With Strength to Fight - derived from Noble
    // fight on their own
    class PersonWithStrengthToFight : public Noble {
        private:
            double strength;

        public:
            PersonWithStrengthToFight(const std::string& name, double strength);
            const double get_strength() const;
            void battle_cry();
            void win(double reduce_by);
            void lose();
            void display(std::ostream& os) const;
    };
}

#endif