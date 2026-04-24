#include "prompt_parser.hpp"

#include "avaliacao.hpp"

#include <cctype>
#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <utility>

using namespace std;

namespace {

bool eh_inteiro(const string& texto) {
    if (texto.empty()) {
        return false;
    }

    size_t indice = 0;
    if (texto[0] == '-') {
        if (texto.size() == 1) {
            return false;
        }
        indice = 1;
    }

    for (; indice < texto.size(); ++indice) {
        if (!isdigit(static_cast<unsigned char>(texto[indice]))) {
            return false;
        }
    }

    return true;
}

bool eh_nome_variavel(const string& texto) {
    if (texto.empty()) {
        return false;
    }

    const unsigned char primeiro = static_cast<unsigned char>(texto[0]);
    if (!isalpha(primeiro)) {
        return false;
    }

    for (char caractere : texto) {
        const unsigned char atual = static_cast<unsigned char>(caractere);
        if (!isalnum(atual) && caractere != '_') {
            return false;
        }
    }

    return true;
}

optional<Operando> analisar_operando(const string& texto) {
    if (eh_inteiro(texto)) {
        return Operando {Numero(stoi(texto))};
    }

    if (eh_nome_variavel(texto)) {
        return Operando {Variavel(texto)};
    }

    return nullopt;
}

optional<int> ler_valor_variavel(
    const string& nome,
    istream& entrada,
    ostream& saida,
    ostream& erro) {
    saida << "Informe o valor de " << nome << "> ";

    string linha;
    if (!getline(entrada, linha)) {
        erro << "Erro: entrada encerrada ao ler a variavel.\n";
        return nullopt;
    }

    if (!eh_inteiro(linha)) {
        erro << "Erro: valor invalido para a variavel.\n";
        return nullopt;
    }

    return stoi(linha);
}

optional<Operacao> analisar_operacao(const string& expressao, string& mensagem_erro) {
    istringstream fluxo(expressao);
    string esquerdo_texto;
    string operador_texto;
    string direito_texto;
    string sobra;

    if (!(fluxo >> esquerdo_texto >> operador_texto >> direito_texto) || (fluxo >> sobra)) {
        mensagem_erro = "expressao invalida; use o formato operando operador operando";
        return nullopt;
    }

    auto esquerdo = analisar_operando(esquerdo_texto);
    auto direito = analisar_operando(direito_texto);
    if (!esquerdo.has_value() || !direito.has_value()) {
        mensagem_erro = "operando invalido";
        return nullopt;
    }

    TipoOperacao tipo;
    if (operador_texto == "+") {
        tipo = TipoOperacao::soma;
    } else if (operador_texto == "-") {
        tipo = TipoOperacao::subtracao;
    } else if (operador_texto == "*") {
        tipo = TipoOperacao::multiplicacao;
    } else {
        mensagem_erro = "operador invalido";
        return nullopt;
    }

    return Operacao(move(*esquerdo), tipo, move(*direito));
}

int avaliar_operacao_interativamente(
    const Operacao& operacao,
    istream& entrada,
    ostream& saida,
    ostream& erro) {
    map<string, int> valores_variaveis;
    for (const string& nome : operacao.nomes_variaveis()) {
        const auto valor = ler_valor_variavel(nome, entrada, saida, erro);
        if (!valor.has_value()) {
            erro.setstate(ios::failbit);
            return 0;
        }
        valores_variaveis.emplace(nome, *valor);
    }

    return operacao.avaliar(valores_variaveis);
}

}  // namespace

bool executar_prompt(istream& entrada, ostream& saida, ostream& erro) {
    saida << "Informe a operacao> ";

    string expressao;
    if (!getline(entrada, expressao)) {
        erro << "Erro: nao foi possivel ler a operacao.\n";
        return false;
    }

    string mensagem_erro;
    auto operacao = analisar_operacao(expressao, mensagem_erro);
    if (!operacao.has_value()) {
        erro << "Erro: " << mensagem_erro << '\n';
        return false;
    }

    const int resultado = avaliar_operacao_interativamente(*operacao, entrada, saida, erro);
    if (erro.fail()) {
        return false;
    }

    saida << "Resultado: " << resultado << '\n';
    return true;
}
