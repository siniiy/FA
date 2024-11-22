#include <iostream>
#include <cmath>

class complex final { 
    public:
        complex(double r=0.0, double i=0.0  ) {
            real = r;
            img = i;
        }

        void info() const {
            std::cout << real << " " << img << "i" << std::endl;
        }
        void add(const complex obj) {
            real += obj.real;
            img += obj.img;
        }
        void substract(const complex obj) {
            real -= obj.real;
            img -= obj.img;
        }
        void multiply (complex obj) {
            double temp = real; // (a + ib) * (c + id) = ac + adi + bci - bd
            real = real * obj.real - img * obj.img;
            img = temp * obj.img + img * obj.real; 
        }
        void divide (const complex &obj) {
            double divider = obj.real * obj.real + obj.img * obj.img;
            double old_real = real;


            if(divider < __DBL_EPSILON__) {
                throw std::overflow_error("Division by zero");
            }

            real = (real * obj.real + img * obj.img) / divider;
            
            img = (img * obj.real - old_real * obj.img);
        }
        double module() const {
            return std::sqrt(real * real + img * img);
        }
        double argument() const {
            return std::atan(img / real) * 180 / M_PI;
        }
    virtual ~complex() = default;
    private:
        double img, real;
};

int main() {
    complex goal = complex(-4, 2);

    complex goal2 = complex(1, -3);

    complex goal3(27.4, 72.8991);

    goal3.add(goal);

    goal3.info();


    try { 
        goal.divide(goal2); 
        goal.info(); 
    } 
    catch (std::overflow_error const &e) { 
        std::cout << e.what() << std::endl; 
    }
    
    goal.divide(goal2);

    goal.info();

    goal2.info();

    return 0;
}