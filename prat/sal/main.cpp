#include <iostream>

#include "salarios.h"

int main(){
    cout << "polimorfismo" << endl;

    SalarioComposto salario;

    salario.agrega(new Fixo(900.00));
    salario.agrega(new Comissao(500.0));
    salario.agrega(new Comissao(600.0, 0.2));
    salario.agrega(new Comissao(10000.0, 0.05));

    cout << "O valor total do salario: " << salario.value() << endl;
}
