#include "avaliacao.hpp"

#include <set>
#include <utility>

using namespace std;

Numero::Numero(int valor) : valor_(valor) {}

int Numero::valor() const {
    return valor_;
}

Variavel::Variavel(string nome) : nome_(move(nome)) {}

const string& Variavel::nome() const {
    return nome_;
}

Operacao::Operacao(Operando esquerdo, TipoOperacao tipo, Operando direito)
    : esquerdo_(move(esquerdo)), tipo_(tipo), direito_(move(direito)) {}

int Operacao::avaliar(const map<string, int>& valores) const {
    const int valor_esquerdo = resolver_operando(esquerdo_, valores);
    const int valor_direito = resolver_operando(direito_, valores);

    switch (tipo_) {
        case TipoOperacao::soma:
            return valor_esquerdo + valor_direito;
        case TipoOperacao::subtracao:
            return valor_esquerdo - valor_direito;
        case TipoOperacao::multiplicacao:
            return valor_esquerdo * valor_direito;
    }

    return 0;
}

vector<string> Operacao::nomes_variaveis() const {
    vector<string> nomes;
    set<string> nomes_vistos;

    auto registrar = [&](const Operando& operando) {
        if (const auto* variavel = get_if<Variavel>(&operando)) {
            if (nomes_vistos.insert(variavel->nome()).second) {
                nomes.push_back(variavel->nome());
            }
        }
    };

    registrar(esquerdo_);
    registrar(direito_);

    return nomes;
}

int Operacao::resolver_operando(const Operando& operando, const map<string, int>& valores) const {
    if (const auto* numero = get_if<Numero>(&operando)) {
        return numero->valor();
    }

    const auto& variavel = get<Variavel>(operando);
    return valores.at(variavel.nome());
}
