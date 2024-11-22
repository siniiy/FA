#include <iostream>


class log final { 
    public: 
        log(unsigned int a = 0) {
            value = a;
        }

        void info() {
            std::cout << value << std::endl;
        }

        unsigned int accessor() {
            return value;
        }

        log inversion() {
            return log(~value);
        }

        int get_bit(const int a) {
            if (a >= (sizeof(value) << 3)) {
                throw std::length_error("Incorrect position");
            }
            if (value & (1 << a)) {
                return 1;
            }
            return 0;
        }
        log conjunction(const unsigned int a) {
            return log(value & a);
        }

        log disjunction(const unsigned int a) {
            log temp = log(a).inversion();
            return this->inversion().conjunction(log(a).inversion().accessor()).inversion();
        }

        log implication(const unsigned int a) {
            log first = this->inversion();
            return first.disjunction(a);
        }

        log coimplication(const unsigned int a) {
            log first = this->inversion();
            return first.conjunction(a);
        }

        log equivalence(const unsigned int a) {
            return this->add_mod_2(a).inversion();
        }

        log add_mod_2(const unsigned int a) {
            return log(value ^ a);
        }

        log Pirs(const unsigned int a) {
            return this->disjunction(a).inversion();
        }

        log Sheffer(const unsigned int a) {
            return this->conjunction(a).inversion();
        }

        void res_print() {
            for (int i = 0; i < sizeof(value) << 3; i++) {
                std::cout<< this->get_bit(i);
            }
            
            std::cout << std::endl;
        }

    virtual ~log() = default;
    private:
        unsigned int value;
};

int main() {
    log goal = log(1230);

    log goal2 = log(1234);

    std::cout << "goal: ";
    goal.res_print();
    std::cout << "goal 2: ";
    goal2.res_print();


    std::cout << "Conjunction: ";
    goal.conjunction(goal2.accessor()).res_print();

    std::cout << "Disjunction: ";
    goal.disjunction(goal2.accessor()).res_print();

    std::cout << "Implication: ";
    goal.implication(goal2.accessor()).res_print();

    std::cout << "Coimplication: ";
    goal.coimplication(goal2.accessor()).res_print();

    std::cout << "Xor: ";
    goal.add_mod_2(goal2.accessor()).res_print();

    std::cout << "Equivalence: ";
    goal.equivalence(goal2.accessor()).res_print();

    std::cout << "Pirs: ";
    goal.Pirs(goal2.accessor()).res_print();

    std::cout << "Sheffer: ";
    goal.Sheffer(goal2.accessor()).res_print();

    std::cout << "Inversed goal: ";
    goal.inversion().res_print();

    std::cout << "Inversed goal 2: ";
    goal2.inversion().res_print();

    return 0;

}