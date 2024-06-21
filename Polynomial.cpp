#include "Polynomial.h"

Polynomial::Polynomial() {
    int a = 131, i = 0, x; //a=Primal polynomial
    Galois.push_back(1);
    while (i != 127) {
        x = Galois[i] << 1;
        if (x <= 127) {
            Galois.push_back(x);
            i++;
        } else {
            x ^= a;
            Galois.push_back(x);
            i++;
        }
    }
    element heh{};
    Pol.push_back(heh);
}

Polynomial::Polynomial(int const Power_a, int const Power_x) {
    int a = 131, i = 0, x; //a=Primal polynomial
    if (Power_a >= 127) throw std::logic_error("Power of alfa given is too big");
    if (Power_x >= 127) throw std::logic_error("Power of x given is too big");
    Galois.push_back(1);
    while (i != 127) {
        x = Galois[i] << 1;
        if (x <= 127) {
            Galois.push_back(x);
            i++;
        } else {
            x ^= a;
            Galois.push_back(x);
            i++;
        }
    }
    element heh{Power_a, Power_x};
    Pol.push_back(heh);
}

void Polynomial::TidyUp_Same_Elements() {
    //sort not needed
    Sort();
    element null{-111, -999};
    int help = 0, secondhelp = 0, w = 1, again = 0;
    Pol.push_back(null);
    while (w < Pol.size()) {
        int i = 0;
        while (i < Pol.size()) {
            if (Pol[i].Get_Power_x() == Pol[w].Get_Power_x() && Pol[i].Get_Power_a() != -111 && Pol[w].Get_Power_a() != -1 && Pol[i].Get_Power_a() != -1 && w != i && Pol[w].Get_Power_a() != -111) {
                again = 1;
                help = Pol[i].Get_Power_a();
                secondhelp = Pol[w].Get_Power_a();
                help = Galois[help];
                secondhelp = Galois[secondhelp];
                help = help ^ secondhelp;
                if (help == 0) {
                    element special{-1, Pol[i].Get_Power_x()};
                    if (std::find(Pol.begin(), Pol.end(), special) == Pol.end()) {
                        Pol.push_back({-1, Pol[i].Get_Power_x()});
                    }
                    if(i<w) {
                        Pol.erase(std::next(Pol.begin(), w));
                        Pol.erase(std::next(Pol.begin(), i));
                    }else {
                        Pol.erase(std::next(Pol.begin(), w));
                        Pol.erase(std::next(Pol.begin(), i - 1));
                    }
                } else {
                    for (int o = 0; o < Galois.size(); o++) {
                        if (help == Galois[o]) {
                            help = o;
                            break;
                        }
                    }
                    Pol[w].Set_Power_a(help);
                    Pol.erase(std::next(Pol.begin(), i));
                }
            }

            i++;
        }
        if (again == 1 && w == Pol.size() - 1) {
            again = 0;
            w = 1;
        } else {
            w++;
        }
    }
    for (int b = 0; b < Pol.size(); b++) {
        if (Pol[b].Get_Power_a() == -111) {
            Pol.erase(std::next(Pol.begin(), b));
            break;
        }
    }
}

void Polynomial::Add_Element(element addon) {
    if (addon.Get_Power_a() >= 127) throw std::logic_error("Power of alfa given is too big");
    if (addon.Get_Power_x() >= 127) throw std::logic_error("Power of x given is too big");
    Pol.push_back(addon);
}

void Polynomial::Add_Element(int const Power_a, int const Power_x) {
    if (Power_a >= 127) throw std::logic_error("Power of alfa given is too big");
    if (Power_x >= 127) throw std::logic_error("Power of x given is too big");
    element heh{Power_a, Power_x};
    Pol.push_back(heh);
}

void Polynomial::Sort() {
    std::sort(Pol.begin(), Pol.end());
}

void Polynomial::Delete_Null() {
    int g = 0;
    while (g < Pol.size()) {
        if (Pol[g].Get_Power_a() == -1) {
            Pol.erase(std::next(this->Pol.begin(), g));
        } else {
            g++;
        }
    }
}

Polynomial Polynomial::operator+(Polynomial &add) {
    element null{-999, -999};
    int help, i = 0, again = 0;
    Polynomial addon{};
    addon.Pol=add.Pol;
    addon.TidyUp_Same_Elements();
    Polynomial ToAdd{};
    ToAdd.Pol = this->Pol;
    ToAdd.TidyUp_Same_Elements();
    while (ToAdd.Pol.size() < addon.Pol.size()) {
        ToAdd.Pol.push_back(null);
    }
    while (ToAdd.Pol.size() > addon.Pol.size()) {
        addon.Pol.push_back(null);
    }
    while (i < ToAdd.Pol.size()) {
        int c = 0;
        while (c < addon.Pol.size()) {
            if (addon.Pol[c].Get_Power_x() == ToAdd.Pol[i].Get_Power_x() && addon.Pol[c].Get_Power_a() != -999 && ToAdd.Pol[i].Get_Power_a() != -999 && addon.Pol[c].Get_Power_a() != -1 && ToAdd.Pol[i].Get_Power_a() != -1) {
                again = 1;
                help = Galois[addon.Pol[c].Get_Power_a()] ^ Galois[ToAdd.Pol[i].Get_Power_a()];
                if (help == 0) {
                    element special{-1, addon.Pol[c].Get_Power_x()};
                    if (std::find(addon.Pol.begin(), addon.Pol.end(), special) == addon.Pol.end()) {
                        addon.Pol.push_back(special);
                        ToAdd.Pol.push_back(null);
                    }
                    addon.Pol.erase(std::next(addon.Pol.begin(), c));
                    ToAdd.Pol.erase(std::next(ToAdd.Pol.begin(), i));
                } else {
                    for (int w = 0; w < Galois.size(); w++) {
                        if (help == Galois[w]) {
                            help = w;
                            break;
                        }
                    }
                    addon.Pol[c].Set_Power_a(help);
                    ToAdd.Pol.erase(std::next(ToAdd.Pol.begin(), i));
                    ToAdd.Pol.push_back(null);
                }
            }
            c++;
        }
        if (again == 1 && i == ToAdd.Pol.size() - 1) {
            again = 0;
            i = 0;
        } else {
            i++;
        }
    }

    again = 0;
    for (int k = 0; k < ToAdd.Pol.size(); k++) {
        if (ToAdd.Pol[k].Get_Power_a() != -1) {
            for (int nk = 0; nk < addon.Pol.size(); nk++) {
                if (addon.Pol[nk].Get_Power_a() == -1 && ToAdd.Pol[k].Get_Power_x() == addon.Pol[nk].Get_Power_x()) {
                    addon.Pol[nk] = ToAdd.Pol[k];
                    again = 1;
                    ToAdd.Pol.erase(std::next(ToAdd.Pol.begin(), k));
                }
            }
            if (again == 1) {
                k = 0;
                again = 0;
            }
        }
    }

    for (int k = 0; k < ToAdd.Pol.size(); k++) {
        if (ToAdd.Pol[k].Get_Power_a() != -1) {
            addon.Add_Element(ToAdd.Pol[k]);
        } else {
            int nk = 0;
            int check = 1;
            while (nk < addon.Pol.size()) {
                if (addon.Pol[nk].Get_Power_x() == ToAdd.Pol[k].Get_Power_x()) check = 0;
                nk++;
            }
            if (check == 1) addon.Add_Element(ToAdd.Pol[k]);
        }
    }

    int k = 0;
    while (k < addon.Pol.size()) {
        if (addon.Pol[k].Get_Power_a() == -999) {
            addon.Pol.erase(std::next(addon.Pol.begin(), k));
            k = 0;
        } else {
            k++;
        }
    }
    return addon;
}

Polynomial Polynomial::operator*(Polynomial &first) {
    Polynomial result{};
    element help{};
    result.Pop_Element();
    for (int i = 0; i < first.Pol.size(); i++) {
        for (int c = 0; c < this->Pol.size(); c++) {
            if (first.Pol[i].Get_Power_a() != -1 && this->Pol[c].Get_Power_a() != -1) {
                if ((first.Pol[i].Get_Power_a() + this->Pol[c].Get_Power_a()) % 127 < 0) {
                    help.Set_Power_a((127 + first.Pol[i].Get_Power_a() + this->Pol[c].Get_Power_a()) % 127);
                } else {
                    help.Set_Power_a((first.Pol[i].Get_Power_a() + this->Pol[c].Get_Power_a()) % 127); //chyba 127 nie?
                }
                help.Set_Power_x((first.Pol[i].Get_Power_x() + this->Pol[c].Get_Power_x()) % 127);
                result.Pol.push_back(help);
            }
        }
    }
    return result;
}

void Polynomial::Encoder(int Number_To_Code, Polynomial Gx) {
    Polynomial coded{};
    Polynomial remainder{};
    int digit, i = 0;
    coded.Pol.clear();
    if(Number_To_Code==0) throw std::logic_error("0 can't be coded");
    while (Number_To_Code != 0) {
        digit = Number_To_Code % 10;
        Number_To_Code = Number_To_Code / 10;
        if (digit == 0) {
            digit = -1;
        } else {
            for (int w = 0; w < Galois.size(); w++) {
                if (digit == Galois[w]) {
                    digit = w;
                    break;
                }
            }
        }
        coded.Add_Element(digit, 6 + i);
        i++;
    }
    remainder = coded % Gx;
    remainder.Delete_Null();
    coded = coded + remainder;
    coded.TidyUp_Same_Elements();
    Pol = coded.Pol;
}

void Polynomial::Encoder(const std::vector<int> &Values, Polynomial Gx) {
    Polynomial coded{};
    Polynomial remainder{};
    int Value = 0, i = 0;
    coded.Pol.clear();
    for (int z = Values.size() - 1; z >= 0; z--) {
        if (Values[z] > 127 || Values[z] < 0) throw std::logic_error("This Value can't be coded, it's too big or too small");
        if (Values[z] == 0) {
            Value = -1;
        } else {
            for (int w = 0; w < Galois.size(); w++) {
                if (Values[z] == Galois[w]) {
                    Value = w;
                    break;
                }
            }
        }
        coded.Add_Element(Value, 6 + i);
        i++;
    }
    remainder = coded % Gx;
    remainder.Delete_Null();
    coded = coded + remainder;
    coded.TidyUp_Same_Elements();
    Pol = coded.Pol;
}

void Polynomial::Encoder_s(std::string word, Polynomial Gx) {
    std::vector<int> Vword;
    Vword.reserve(word.size());
    for (int i = 0; i < word.size(); i++) {
        if (word[i] >= 127 || word[i] < -1) throw std::logic_error("This word can't be coded");
        Vword.push_back(word[i]);
    }
    Encoder(Vword, Gx);
}

bool Polynomial::Checker() {
    if (Pol.empty()) return true;
    for (auto i: Pol) {
        if (i.Get_Power_a() != -1) return false;
    }
    return true;
}

void Polynomial::Simple_Decoder(Polynomial Gx) {
    int t = 3, i = 0, k = 127;
    Polynomial CodeWord{};
    CodeWord.Pol = this->Pol;
    Polynomial s{};
    while (true) {
        s = CodeWord % Gx;
        s.Sort();
        int x = 0, w = 0;
        for (auto j: s.Pol) {
            if (j.Get_Power_a() != -1) {
                x = j.Get_Power_x();
                break;
            }
        }
        for (int j = 0; j < s.Pol.size(); j++) {
            if (s.Pol[j].Get_Power_x() <= x && s.Pol[j].Get_Power_a() != -1) {
                w++;
            }
        }
        if (w <= t) {
            CodeWord = CodeWord + s;
            while (i > 0) {
                CodeWord.Move_To_left();
                i--;
            }
            this->Pol = CodeWord.Pol;
            return;
        }
        if (i == k) {
            std::cout << std::endl << "Coded message couldn't be corrected by simple decoder" << std::endl;
            return;
        }
        Polynomial Just{0, 1};
        CodeWord.Move_To_right();
        i++;
    }
}

Polynomial Polynomial::error_locator(Polynomial Gx) {
    //Berlekamp-Massey algorithm
    std::array<int, 6> syndrome{}; //have a power of alphas stored
    Polynomial CodeWord{};
    Polynomial El{};
    CodeWord.Pol = this->Pol;
    El = CodeWord;
    El = El % Gx;
    if (El.Checker()) throw std::logic_error("This is already correct codeword");
    for (int iter = 1; iter < 7; iter++) {
        auto eval = 0;
        for (const auto &word: CodeWord.Pol) {
            if(word.Get_Power_a()!=-1) {
                auto alpha = word.Get_Power_a();
                auto xElem = word.Get_Power_x() * iter % 127;

                auto pow = (alpha + xElem) % 127;
                eval ^= Galois[pow];
            }
        }
        if(eval==0) {
            syndrome[iter-1]=-1;
        }
        else {
            for (int i = 0; i < Galois.size(); i++) {
                if (eval == Galois[i]) {
                    syndrome[iter - 1] = i;
                    break;
                }
            }
        }
    }
    int r = 0; //K
    int length = 0;
    int e ; //have powers of alphas stored
    Polynomial lambda{0, 0};
    Polynomial lambda_star{0, 0};
    Polynomial C{0, 1};
    while (r < 6) {
        r++;
        e = syndrome[r - 1];
        int correction=0;
        for (int j = 1; j <= length; j++) {
            if(lambda.Pol[lambda.Pol.size() - j - 1+correction].Get_Power_x()==j){
            if (e != -1) {
                if(lambda.Pol[lambda.Pol.size() - j - 1+correction].Get_Power_a()!=-1&&syndrome[r - j - 1]!=-1){
                    int res = (lambda.Pol[lambda.Pol.size() - j - 1+correction].Get_Power_a() + syndrome[r - j - 1]) % 127;
                res = Galois[e]^Galois[res];
                if (res == 0) {
                    e = -1;
                } else {
                    for (int q = 0; q < Galois.size(); q++) {
                        if (Galois[q] == res) {
                            e = q;
                            break;
                        }
                    }
                }
            }
            }else{
                if(lambda.Pol[lambda.Pol.size() - j - 1+correction].Get_Power_a()!=-1&&syndrome[r - j - 1]!=-1) {
                    e=(lambda.Pol[lambda.Pol.size() - j - 1+correction].Get_Power_a()+syndrome[r - j - 1]) % 127;
                }
            }
        }else {
            correction++;
        }
        }
        if (e != -1) {
            Polynomial tmp{e, 0};
            tmp = C * tmp;
            lambda_star = lambda + tmp;
            lambda_star.Delete_Null();
            if (2 * length < r) {
                length = r - length;
                tmp = lambda;
                for (int t = 0; t < lambda.Pol.size(); t++) {
                    if ((tmp.Pol[t].Get_Power_a() - e) % 127 < 0) {
                        tmp.Pol[t].Set_Power_a((127 + tmp.Pol[t].Get_Power_a() - e) % 127);
                    } else {
                        tmp.Pol[t].Set_Power_a((tmp.Pol[t].Get_Power_a() - e) % 127);
                    }
                }
                C = tmp;
            }
            lambda = lambda_star;
            lambda.Sort();
        }
        Polynomial X{0, 1};
        C = C * X;
    }
    return lambda;
}

std::vector<int> Polynomial::Root_of_EL() const {
    //chien search
    auto zeros = std::vector<int>();
    auto eval = 0;
    for (auto iter = 0; iter < 127; iter++) {
        for (const auto &word: Pol) {
            auto alpha = word.Get_Power_a();
            auto xElem = word.Get_Power_x() * iter % 127;

            auto pow = (alpha + xElem) % 127;
            eval ^= Galois[pow];
        }

        if (eval == 0) {
            zeros.push_back((127-iter)%127);
        }

        eval = 0;
    }
    if(zeros.size()!=this->Pol[0].Get_Power_x()) throw std::logic_error("This codeword can't be repaired");
    return zeros;
}

void Polynomial::Decoder(Polynomial Gx) {
    //Forney's algorithm
    Polynomial syndrome{};
    Polynomial CodeWord{};
    Polynomial error_l{};
    Polynomial omega{};
    Polynomial final_pol{};
    final_pol.Pol.clear();
    error_l = error_locator(Gx);
    std::vector<int> roots{};
    roots = error_l.Root_of_EL();
    CodeWord.Pol = this->Pol;
    syndrome.Pol.clear();
    for (int iter = 1; iter < 7; iter++) {
        auto eval = 0;
        for (const auto &word: CodeWord.Pol) {
            if(word.Get_Power_a()!=-1) {
                auto alpha = word.Get_Power_a();
                auto xElem = word.Get_Power_x() * iter % 127;

                auto pow = (alpha + xElem) % 127;
                eval ^= Galois[pow];
            }
        }
        if(eval==0) {
            syndrome.Add_Element(-1,iter-1);
        }
        else {
            for (int i = 0; i < Galois.size(); i++) {
                if (eval == Galois[i]) {
                    syndrome.Add_Element(i,iter-1);
                    break;
                }
            }
        }
    }
    syndrome.Sort();
    omega = error_l * syndrome;
    omega.TidyUp_Same_Elements();
    omega.Delete_Null();
    if (omega.Pol[0].Get_Power_x() > 5) {
        Polynomial tmp{0, 6};
        omega = omega % tmp;
    }
    omega.Delete_Null();
    error_l.Sort();
    int e = roots.size();
    Polynomial cp{};
    cp.Pol.clear();
    for (int j = 1; j < error_l.Pol.size(); j++) {
        if(error_l.Pol[error_l.Pol.size() - 1 - j].Get_Power_x()%2!=0) {
            cp.Add_Element(error_l.Pol[error_l.Pol.size() - 1 - j].Get_Power_a(),error_l.Pol[error_l.Pol.size() - 1 - j].Get_Power_x()-1);//derivative of error locator
        }
    }
    error_l.Pol = cp.Pol;
    error_l.Sort();
    std::vector<int> errors{}; //stores powers of alphas of errors
    for (int i = 0; i < e; i++) {
        int rev = 127 - roots[i];
        int Sp_omega = 0;
        if(omega.Pol.size()==1) {
            Sp_omega=omega.Pol[0].Get_Power_x()*rev%127;
            Sp_omega=Sp_omega+omega.Pol[0].Get_Power_a()%127;
        }else {
            for (const auto &word: omega.Pol) {
                auto alpha = word.Get_Power_a();
                auto xElem = word.Get_Power_x() * rev % 127;

                auto pow = (alpha + xElem) % 127;
                Sp_omega ^= Galois[pow];
            }
            if (Sp_omega == 0) throw std::logic_error("check this decoder");
            for (int ia = 0; ia < Galois.size(); ia++) {
                if (Sp_omega == Galois[ia]) {
                    Sp_omega = ia;
                    break;
                }
            }
        }
        int Sp_lambda = 0;
        if(error_l.Pol.size()==1) {
            Sp_lambda=error_l.Pol[0].Get_Power_x()*rev%127;
            Sp_lambda=Sp_lambda+error_l.Pol[0].Get_Power_a()%127;
        }else {
            for (const auto &words: error_l.Pol) {
                auto alphas = words.Get_Power_a();
                auto xElems = words.Get_Power_x() * rev % 127;

                auto pow = (alphas + xElems) % 127;
                Sp_lambda ^= Galois[pow];
            }
            if (Sp_lambda == 0) throw std::logic_error("check this decoder");
            for (int is = 0; is < Galois.size(); is++) {
                if (Sp_lambda == Galois[is]) {
                    Sp_lambda = is;
                    break;
                }
            }
        }
        int res;
        if (Sp_omega - Sp_lambda < 0) {
            res = 127 + (Sp_omega - Sp_lambda);
        } else {
            res = Sp_omega - Sp_lambda;
        }
        res = (res + roots[i]) % 127;
        int nice=127-roots[i];
        res=(res+nice)%127;//true result
        errors.push_back(res);
    }
    for (int z = 0; z < e; z++) {
        final_pol.Add_Element(errors[z], roots[z]);
    }
    CodeWord = CodeWord + final_pol;
    this->Pol = CodeWord.Pol;
}

void Polynomial::Move_To_right() {
    for (int i = 0; i < Pol.size(); i++) {
        if (Pol[i].Get_Power_x() - 1 >= 0) {
            Pol[i].Set_Power_x(Pol[i].Get_Power_x() - 1);
        } else {
            Pol[i].Set_Power_x(126);
        }
    }
}

void Polynomial::Move_To_left() {
    for (int i = 0; i < Pol.size(); i++) {
        if (Pol[i].Get_Power_x() + 1 <= 126) {
            Pol[i].Set_Power_x(Pol[i].Get_Power_x() + 1);
        } else {
            Pol[i].Set_Power_x(0);
        }
    }
}

void Polynomial::Fill_Null() {
    Polynomial Full_Of_Null{};
    Polynomial P{};
    P.Pol = Pol;
    Full_Of_Null.Pop_Element();
    for (int i = 0; i < 127; i++) {
        Full_Of_Null.Add_Element({-1, i});
    }
    P = P + Full_Of_Null;
    Pol = P.Pol;
}

Polynomial Polynomial::operator%(Polynomial &second) {
    second.Sort();
    Polynomial first{};
    first.Pol = this->Pol;
    first.Sort();
    Polynomial Normal_result{};
    Polynomial Only_for_Mul{};
    Polynomial Only_for_dividing{};
    Only_for_dividing.Pop_Element();
    Normal_result.Pop_Element();
    int fir = 0, sec = 0;
    for (int j = 0; j < first.Pol.size(); j++) {
        if (first.Pol[j].Get_Power_a() != -1) {
            fir = j;
            break;
        }
    }
    for (int j = 0; j < second.Pol.size(); j++) {
        if (second.Pol[j].Get_Power_a() != -1) {
            sec = j;
            break;
        }
    }
    if (first.Pol[fir].Get_Power_x() < second.Pol[sec].Get_Power_x()) throw std::logic_error("These Polynomials can't be divided at least in this configuration (rest)");
    int i = 0;
    while (first.Pol[fir].Get_Power_x() >= second.Pol[sec].Get_Power_x() && first.Pol[fir].Get_Power_a() != -1 && second.Pol[0].Get_Power_a() != -1) {
        if ((first.Pol[fir].Get_Power_a() - second.Pol[sec].Get_Power_a()) % 127 < 0) {
            Normal_result.Add_Element((127 + first.Pol[fir].Get_Power_a() - second.Pol[sec].Get_Power_a()) % 127, first.Pol[fir].Get_Power_x() - second.Pol[sec].Get_Power_x());
        } else {
            Normal_result.Add_Element((first.Pol[fir].Get_Power_a() - second.Pol[sec].Get_Power_a()) % 127, first.Pol[fir].Get_Power_x() - second.Pol[sec].Get_Power_x()); //chyba 127 nie?
        }
        Only_for_Mul.Pol[0] = Normal_result.Pol[i];
        Only_for_dividing = Only_for_Mul * second;
        first = first + Only_for_dividing;
        for (int j = 0; j < first.Pol.size(); j++) {
            if (first.Pol[j].Get_Power_a() != -1) {
                fir = j;
                break;
            }
        }
        for (int j = 0; j < second.Pol.size(); j++) {
            if (second.Pol[j].Get_Power_a() != -1) {
                sec = j;
                break;
            }
        }
        i++;
    }
    first.Sort();
    return first;
}

void Polynomial::Show() const {
    std::cout << std::endl;
    std::cout << "=====Normal display=====";
    std::cout << std::endl;
    int check = 0;
    for (auto d: Pol) {
        if (d.Get_Power_a() == -1) check++;
    }
    if (check == Pol.size()) {
        std::cout << "0" << std::endl;
        return;
    }
    int x = 0, g = 0;
    for (auto j: Pol) {
        if (j.Get_Power_a() != -1) {
            x = j.Get_Power_x();
            break;
        }
    }
    int br = 0;
    for (auto j: Pol) {
        if (j.Get_Power_a() == -1 && j.Get_Power_x() < x) {
            br++;
        }
    }
    for (auto &i: Pol) {
        if (i.Get_Power_a() != 0 && i.Get_Power_a() != 1 && i.Get_Power_a() != -1) std::cout << "a^" << i.Get_Power_a();
        if (i.Get_Power_a() == 1) std::cout << "a";
        if (i.Get_Power_x() != 0 && i.Get_Power_x() != 1 && i.Get_Power_a() != -1) std::cout << "x^" << i.Get_Power_x();
        if (i.Get_Power_x() == 1 && i.Get_Power_a() != -1) std::cout << "x";
        if (i.Get_Power_a() == -1 && i.Get_Power_x() < x) std::cout << 0;
        if (i.Get_Power_a() == 0 && i.Get_Power_x() == 0) std::cout << 1;
        if (g < Pol.size() - check - 1 + br && i.Get_Power_x() <= x) std::cout << " + ";
        if (i.Get_Power_x() <= x) g++;
    }
    std::cout << std::endl;
}

void Polynomial::Special_Show() {
    std::cout << std::endl;
    std::cout << "=====Special display=====";
    std::cout << std::endl;
    int check = 0;
    for (auto d: Pol) {
        if (d.Get_Power_a() == -1) check++;
    }
    if (check == Pol.size()) {
        std::cout << "0" << std::endl;
        return;
    }
    int g = 0, x = 0;
    for (auto j: Pol) {
        if (j.Get_Power_a() != -1) {
            x = j.Get_Power_x();
            break;
        }
    }
    int br = 0;
    for (auto j: Pol) {
        if (j.Get_Power_a() == -1 && j.Get_Power_x() < x) {
            br++;
        }
    }
    for (auto &i: Pol) {
        if (i.Get_Power_a() > 0) {
            int alpha = 0, value = -999;
            while (alpha < Galois.size()) {
                if (Galois[i.Get_Power_a()] == Galois[alpha] && i.Get_Power_a() != -1) {
                    value = Galois[alpha];
                    alpha = Galois.size() + 1;
                }
                alpha++;
            }
            if (value == -999) throw std::logic_error("Something went wrong in Special show");
            std::cout << value;
        }
        if (i.Get_Power_x() != 0 && i.Get_Power_x() != 1 && i.Get_Power_a() != -1) std::cout << "x^" << i.Get_Power_x();
        if (i.Get_Power_x() == 1 && i.Get_Power_a() != -1) std::cout << "x";
        if (i.Get_Power_a() == -1 && i.Get_Power_x() < x) std::cout << 0;
        if (g < Pol.size() - check - 1 + br && i.Get_Power_x() <= x) std::cout << " + ";
        if (i.Get_Power_x() <= x) g++;
    }
    std::cout << std::endl;
}

void Polynomial::Word_Show() {
    //words are from 6 to 126 but from backward it means that for example if you have word "hair" r is on 6 posistion and h is on 9 position
    std::cout << std::endl;
    std::cout << "=====Word display=====";
    std::cout << std::endl;
    std::string word;
    Sort();
    if (Pol.size() < 6) throw std::logic_error("propably no word is coded");
    for (int i = 0; i < Pol.size() - 6; i++) {
        if (Pol[i].Get_Power_a() != -1) word.push_back(Galois[Pol[i].Get_Power_a()]);
    }
    std::cout << word;
    std::cout << std::endl;
}

std::vector<Polynomial::element> Polynomial::Get_Polynomial() {
    return Pol;
}

void Polynomial::Pop_Element() {
    Pol.pop_back();
}
