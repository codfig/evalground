#ifndef AVALIACAO_HPP
#define AVALIACAO_HPP

#include <map>
#include <string>
#include <variant>
#include <vector>

using namespace std;

class Numero {
public:
    Numero(int valor);

    int valor() const;

private:
    int valor_;
};

class Variavel {
public:
    Variavel(std::string nome);

    const string& nome() const;

private:
    string nome_;
};

using Operando = variant<Numero, Variavel>;

enum class TipoOperacao {
    soma,
    subtracao,
    multiplicacao
};

class Operacao {
public:
    Operacao(Operando esquerdo, TipoOperacao tipo, Operando direito);

    int avaliar(const map<string, int>& valores) const;
    vector<string> nomes_variaveis() const;

private:
    int resolver_operando(const Operando& operando, const map<string, int>& valores) const;

    Operando esquerdo_;
    TipoOperacao tipo_;
    Operando direito_;
};

#endif
