#include "salarios.h"
/* Classe Base */
Salario::Salario(){ }
Salario::~Salario() { }
/* Classes Derivadas */
// Fixo
Fixo::Fixo(double fixo){ _fixo = fixo; }
double Fixo::value() { return _fixo; }
// Comissao
Comissao::Comissao(double base, double percentage) {_base = base; _percentage = percentage;}
Comissao::Comissao(double base) {_base = base; _percentage = 0.1;}
double Comissao::value() {return _base * _percentage;}
// Agregado
void SalarioComposto::agrega(Salario *f){ _sal.push_back(f); }
double SalarioComposto::value(){
	double sal = 0;
    for(vector<Salario*>::iterator it = _sal.begin(); it!=_sal.end(); ++it){
        sal += (**it).value();
    }
    return sal;
}
