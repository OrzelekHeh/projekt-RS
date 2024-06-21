#include <iostream>

#include "Polynomial.h"

int main() {
    try {
        //===================wielomian generujący dla t=3=========================
        Polynomial pierwszy{0, 1};
        pierwszy.Add_Element(1, 0);
        Polynomial drugi{0, 1};
        for (int As = 2; As <= 6; As++) {
            drugi.Add_Element(As, 0);
            pierwszy = pierwszy * drugi;
            drugi.Pop_Element();
        }
        pierwszy.TidyUp_Same_Elements();
        //========================================================================


        Polynomial zakodowana{};
        zakodowana.Encoder_s("testowa wiadomosc moze miec do 121 znakow",pierwszy);//w cudzysłowie jest wiadomość którą chcemy zakodować
        Polynomial fajna{32,110}; //Power_a to jest wartość błędu który wprowadzamy, Power_x to pozycja błędu który wprowadzamy
        fajna.Add_Element(95,40);
        fajna.Add_Element(110,56);


        zakodowana.Word_Show(); //wyświetlenie wiadomości zakodowanej
        zakodowana=zakodowana+fajna; //zepsucie wiadomości
        zakodowana.Word_Show(); //wyświetlenie wiadomości zakodowanej z błędami
        zakodowana.Decoder(pierwszy); //zdekodowanie wiadomości za pomocą dekodera dedykowanego
        //zakodowana.Simple_Decoder(pierwszy); //zdekodowanie wiadomości za pomocą uproszczonego dekodera
        zakodowana.Word_Show(); //wyświetlenie wiadomości po zdekodowaniu
        //zakodowana.Show(); //wyświetlenie wiadomości jako wielomian
        //zakodowana.Special_Show(); //wyświetlenie wiadomości jako wielomian z podstawionymi wartościami dziesiętnymi pod alfy

    } catch (std::logic_error &e) {
        std::cout << e.what() << std::endl;
    }
}
