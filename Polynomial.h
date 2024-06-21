
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <vector>
#include <iostream>
#include <array>
#include <algorithm>
#include <cstdlib>

class Polynomial {
private:
    class element {
    private:
        int Pa,Px;
    public:
        element(){Pa=1,Px=1;}
        element(int const Power_a, int const Power_x){Pa=Power_a, Px=Power_x;}
        void Set_Power_a(int const Power_a){Pa=Power_a;}
        void Set_Power_x(int const Power_x){Px=Power_x;}
        [[nodiscard]] int Get_Power_a() const{return Pa;}
        [[nodiscard]] int Get_Power_x() const{return Px;}
        bool operator<(element &addon) const {if(this->Get_Power_x()>addon.Get_Power_x()) {return true;}{return false;}};
        bool operator==(element const &eq) const {if(this->Get_Power_a()==eq.Get_Power_a()&&this->Get_Power_x()==eq.Get_Power_x()) {return true;}{return false;}}
    };
    std::vector<element> Pol;
    std::vector<int> Galois;
public:
    Polynomial();
    Polynomial(int Power_a, int Power_x);
    ~Polynomial() {
        Pol.erase(Pol.cbegin(), Pol.cend());
        Pol.clear();
    }
    Polynomial operator*(Polynomial &first);
    Polynomial operator%(Polynomial &second);
    Polynomial operator+(Polynomial &add);
    bool inline Checker();//returns true if Polynomial is empty
    void TidyUp_Same_Elements();
    void Add_Element(int Power_a, int Power_x);
    void Add_Element(element addon);
    void Pop_Element();
    void Simple_Decoder(Polynomial Gx);
    Polynomial error_locator(Polynomial Gx);
    [[nodiscard]] std::vector<int> Root_of_EL() const;
    void Decoder(Polynomial Gx);
    void Sort();
    void Delete_Null();
    void Move_To_right();
    void Move_To_left();
    std::vector<element> Get_Polynomial();
    void Show()const;
    void Special_Show();//displays Gx with number values instead of alphas
    void Word_Show();//displays values in string format
    void Encoder(int Number_To_Code, Polynomial Gx);
    void Encoder(const std::vector<int>& Values,Polynomial Gx);
    void Encoder_s(std::string word, Polynomial Gx);
    void Fill_Null();
};



#endif //POLYNOMIAL_H
