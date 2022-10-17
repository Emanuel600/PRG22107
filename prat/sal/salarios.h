#ifndef SALARIO_H
#define SALARIO_H

#include <vector>

using namespace std;

// Classe base
class Salario{
public:
    Salario();

    virtual ~Salario()=0;

    virtual double value()=0;
};
/* Classes Derivadas */
// Fixo
class Fixo: public Salario{
private:
    double _fixo;
public:
    Fixo(double fixo);

    double value();
};
// Comissao
class Comissao: public Salario{
private:
    double _base;
    double _percentage;
public:
    Comissao(double base, double percentage);
    Comissao(double base);

    double value();
};

// Composto
class SalarioComposto : public Salario{
private:
    std::vector<Salario*> _sal;
public:
    SalarioComposto() { }

    void agrega(Salario* f);
    double value();
};

#endif // SALARIO_H
