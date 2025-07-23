#include <iostream>   // Para entrada e saída padrão
#include <fstream>    // Para ler e escrever em arquivos
#include <string>     // Para trabalhar com strings

#define MAX_TAREFAS 100  // Número máximo de tarefas que podem ser armazenadas

using namespace std;

// Estrutura que representa uma tarefa
struct Tarefa {
    string descricao;
    bool concluida;
};

// Função para adicionar uma nova tarefa
void adicionarTarefa(Tarefa tarefas[], int& total) {
    if (total >= MAX_TAREFAS) {
        cout << "Limite de tarefas atingido.\n";
        return;
    }

    cout << "Digite a descrição da tarefa: ";
    getline(cin, tarefas[total].descricao);  // Lê a descrição com espaços
    tarefas[total].concluida = false;        // Tarefa começa como "pendente"
    total++;

    cout << "Tarefa adicionada!\n";
}

// Função para listar todas as tarefas
void listarTarefas(Tarefa tarefas[], int total) {
    cout << "\n=== Lista de Tarefas ===\n";
    if (total == 0) {
        cout << "Nenhuma tarefa cadastrada.\n";
        return;
    }

    for (int i = 0; i < total; i++) {
        cout << (i + 1) << ". " << tarefas[i].descricao;
        cout << (tarefas[i].concluida ? " [Concluída]" : " [Pendente]") << "\n";
    }
}

// Função para marcar uma tarefa como concluída
void concluirTarefa(Tarefa tarefas[], int total) {
    listarTarefas(tarefas, total);  // Mostra as tarefas para o usuário escolher
    int index;
    cout << "Digite o número da tarefa a concluir: ";
    cin >> index;
    cin.ignore(); // Limpa o buffer após o uso de cin

    if (index < 1 || index > total) {
        cout << "Número inválido.\n";
        return;
    }

    tarefas[index - 1].concluida = true; // Marca como concluída
    cout << "Tarefa marcada como concluída!\n";
}

// Função para remover todas as tarefas concluídas
void removerConcluidas(Tarefa tarefas[], int& total) {
    int novaQtd = 0;

    // Copia apenas as tarefas pendentes para o início do array
    for (int i = 0; i < total; i++) {
        if (!tarefas[i].concluida) {
            tarefas[novaQtd++] = tarefas[i];
        }
    }

    int removidas = total - novaQtd;
    total = novaQtd;  // Atualiza o total
    cout << removidas << " tarefa(s) concluída(s) removida(s).\n";
}

// Função para salvar as tarefas em um arquivo
void salvarTarefas(Tarefa tarefas[], int total) {
    ofstream arquivo("tarefas.txt");  // Abre o arquivo para escrita

    for (int i = 0; i < total; i++) {
        arquivo << tarefas[i].descricao << "\n";               // Linha 1: descrição
        arquivo << (tarefas[i].concluida ? "1" : "0") << "\n"; // Linha 2: status
    }

    arquivo.close();  // Fecha o arquivo
    cout << "Tarefas salvas no arquivo!\n";
}

// Função para carregar as tarefas do arquivo
void carregarTarefas(Tarefa tarefas[], int& total) {
    ifstream arquivo("tarefas.txt");  // Abre o arquivo para leitura
    if (!arquivo) return;             // Se o arquivo não existe, sai da função

    string linha;
    total = 0;

    // Lê duas linhas por tarefa (descrição e status)
    while (getline(arquivo, linha) && total < MAX_TAREFAS) {
        tarefas[total].descricao = linha;
        getline(arquivo, linha);
        tarefas[total].concluida = (linha == "1");
        total++;
    }

    arquivo.close();
}

// Função principal com o menu
int main() {
    Tarefa tarefas[MAX_TAREFAS];  // Array fixo de tarefas
    int totalTarefas = 0;         // Quantidade atual de tarefas
    int opcao;                    // Opção do menu

    carregarTarefas(tarefas, totalTarefas);  // Carrega as tarefas salvas

    do {
        // Exibe o menu principal
        cout << "\n=== MENU ===\n";
        cout << "1. Adicionar tarefa\n";
        cout << "2. Listar tarefas\n";
        cout << "3. Marcar como concluída\n";
        cout << "4. Remover tarefas concluídas\n";
        cout << "5. Salvar e sair\n";
        cout << "Escolha: ";
        cin >> opcao;
        cin.ignore();  // Limpa o buffer após ler número

        // Executa a opção escolhida
        switch (opcao) {
            case 1:
                adicionarTarefa(tarefas, totalTarefas);
                break;
            case 2:
                listarTarefas(tarefas, totalTarefas);
                break;
            case 3:
                concluirTarefa(tarefas, totalTarefas);
                break;
            case 4:
                removerConcluidas(tarefas, totalTarefas);
                break;
            case 5:
                salvarTarefas(tarefas, totalTarefas);
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opção inválida!\n";
        }

    } while (opcao != 5);  // Sai quando o usuário escolhe 5 (salvar e sair)

    return 0;
}

