#include <iostream>
#include <locale>
#include <fstream>

using namespace std;

struct Socio {
    int numtitulo;
    string nometitular;
    string nomedependente[2];
    bool pagtoemdia;
    Socio* next;
};

struct entradasaida {
    int numtitulo;
    string nomesocio;
    int ocorrencias;
    entradasaida* next;
};

void inserirsocio(Socio*& lista);
void listarsocio(Socio* lista);
void removersocio(Socio*& lista);
void registrarvisita(entradasaida*& registroportaria, Socio*& lista);
void relatoriovisitas(entradasaida*& registroportaria);
void salvarrelatorio(entradasaida* registroportaria);
void carregarsocios(Socio* lista);
void liberarmemoria(Socio* lista, entradasaida* registroportaria);

int main() {
    setlocale(LC_ALL, "Portuguese");
    Socio* listasocios = NULL;
    entradasaida* registrosportaria = NULL;
    int menu;

    do {
        cout << "MENU: \n";
        cout << "1 - Inserir sócio \n";
        cout << "2 - Listar sócios e dependentes \n";
        cout << "3 - Remover sócio \n";
        cout << "4 - Registrar entrada ou saída de sócio \n";
        cout << "5 - Gerar relatório de visitas \n";
        cout << "6 - Carregar sócios \n";
        cout << "0 - Sair \n Escolha a opção: ";
        cin >> menu;

        switch (menu) {
            case 1:
                inserirsocio(listasocios);
                break;
            case 2:
                listarsocio(listasocios);
                break;
            case 3:
                removersocio(listasocios);
                break;
            case 4:
                registrarvisita(registrosportaria, listasocios);
                break;
            case 5:
                relatoriovisitas(registrosportaria);
                break;
            case 6:
                carregarsocios(listasocios);
                break;
            case 0:
                cout << "Saindo...";
                break;
            default:
                cout << "Opção inválida. Tente novamente.\n";
        }
    } while (menu != 0);

    liberarmemoria(listasocios, registrosportaria);

    return 0;
}

void inserirsocio(Socio *&lista){
	Socio* novoSocio = new Socio;
    cout << "Número do título: ";
    cin >> novoSocio->numtitulo;
    cin.ignore();
    cout << "Nome do titular: ";
    getline(cin, novoSocio->nometitular);
    cout << "Nome do dependente 1: ";
    getline(cin, novoSocio->nomedependente[0]);
    cout << "Nome do dependente 2: ";
    getline(cin, novoSocio->nomedependente[1]);
    cout << "Pagamento em dia (1 para Sim, 0 para Não): ";
    int pagamento;
    cin >> pagamento;

    if (pagamento == 1) {
        novoSocio->pagtoemdia = true;
    } else if (pagamento == 0){
        novoSocio->pagtoemdia = false;
	}

    novoSocio->next = lista;
    lista = novoSocio;
    cout << "Sócio cadastrado com sucesso!\n";
}

void listarsocio(Socio *lista){
	cout << "Lista de sócios:\n";
    Socio* atual = lista;
    while (atual != NULL) {
        cout << "Número do título: " << atual->numtitulo << "\n";
        cout << "Nome do titular: " << atual->nometitular << "\n";
        cout << "Nome do dependente 1: " << atual->nomedependente[0] << "\n";
        cout << "Nome do dependente 2: " << atual->nomedependente[1] << "\n";
        cout << "Pagamento em dia: " << (atual->pagtoemdia ? "Sim" : "Não") << "\n";
        cout << "------------------------\n";
        atual = atual->next;
    }
}

void removersocio(Socio *&listasocios){
	int numtitulo;
    cout << "Digite o número do título do sócio a ser removido: ";
    cin >> numtitulo;

    Socio* atual = listasocios;
    Socio* anterior = NULL;

    while (atual != NULL && atual->numtitulo != numtitulo) {
        anterior = atual;
        atual = atual->next;
    }

    if (atual != NULL) {
        if (anterior != NULL) {
            anterior->next = atual->next;
        } else {
            listasocios = atual->next;
        }
        
        delete atual;
        cout << "Sócio removido com sucesso!\n";
    } else {
        cout << "Sócio não encontrado.\n";
    }
}

void registrarvisita(entradasaida *&registroportaria, Socio *&listasocios){
    int numtitulo, socio;
    bool encontrado = false;
    cout << "Número da carteirinha: ";
    cin >> numtitulo;
    cout << "\nQuem está entrando? \n	1 - Sócio \n	2 - Dependente 1 \n	3 - Dependente 2\n";
    cin >> socio;

    Socio* atual = listasocios;

    while(atual != NULL){
        if (atual->numtitulo == numtitulo && atual->pagtoemdia) {
        	encontrado = true;
            entradasaida* entrada = new entradasaida;
            entrada->numtitulo = atual->numtitulo;

            if(socio==1){// Registra entrada do titular
                entrada->nomesocio = atual->nometitular;
            }else if(socio==2){// Registra entrada do dependente 1
                entrada->nomesocio = atual->nomedependente[0];
            }else if(socio==3){// Registra entrada do dependente 2
                entrada->nomesocio = atual->nomedependente[1];
            }

            entrada->ocorrencias = 1;  // Inicia o contador de ocorrências

            // Verifica se já existe uma entrada para o mesmo sócio
            entradasaida* existente = registroportaria;
            while (existente != NULL) {
                if (existente->numtitulo == entrada->numtitulo && existente->nomesocio == entrada->nomesocio) {
                    existente->ocorrencias++;  // Incrementa o contador de ocorrências
                    delete entrada;  // Descarta a nova entrada
                    cout << "Nova ocorrência registrada para " << existente->nomesocio << ". Total de ocorrências: " << existente->ocorrencias << "\n";
                    return;
                }
                existente = existente->next;
            }

            // Registra a nova entrada
            entrada->next = registroportaria;
            registroportaria = entrada;

            cout << "Entrada registrada com sucesso.\n";
            return;
        }
        atual = atual->next;
    }
	if(encontrado==false){
		cout << "Sócio não encontrado ou inadimplente.\n";
	}else{
		cout << "Registro feito com sucesso. \n";
	}
    
}


void relatoriovisitas(entradasaida *&registroportaria){
	cout << "Relatório de visitas no dia:\n";
    entradasaida* atual = registroportaria;
    while (atual != NULL) {
        cout << "Número do título: " << atual->numtitulo << "\n";
        cout << "Nome do sócio ou dependente: " << atual->nomesocio << "\n";
        cout << "Entradas e saídas: " << atual->ocorrencias << "\n";
        cout << "------------------------\n";
        atual = atual->next;
    }
    
    salvarrelatorio(registroportaria); // Chama a função para salvar o relatório em um arquivo
}

void salvarrelatorio(entradasaida* registroportaria) {
    string nomeArquivo;
    cout << "Digite o nome do arquivo para salvar o relatório (ex: relatorio_visitas.txt): ";
    cin >> nomeArquivo;

    ofstream arquivo(nomeArquivo.c_str());

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo para salvar o relatório.\n";
        return;
    }

    entradasaida* atual = registroportaria;
    while (atual != NULL) {
        arquivo << "Número do título: " << atual->numtitulo << "\n";
        arquivo << "Nome do sócio ou dependente: " << atual->nomesocio << "\n";
        arquivo << "Entradas e saídas: " << atual->ocorrencias << "\n";
        arquivo << "------------------------\n";
        atual = atual->next;
    }

    cout << "Relatório de visitas salvo com sucesso.\n";
    arquivo.close();
}


void carregarsocios(Socio* listasocios) {
    string nomeArquivo;
    cout << "Digite o nome do arquivo (ex: dados_socios.txt): ";
    cin >> nomeArquivo;

    ifstream arquivo(nomeArquivo.c_str());

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo.\n";
        return;
    }

    Socio* socio = NULL; // Inicializa com nullptr

    while (arquivo >> socio->numtitulo >> socio->nometitular >> socio->nomedependente[0] >> socio->nomedependente[1] >> socio->pagtoemdia) {
        Socio* novoSocio = new Socio; // Aloca novo espaço de memória para cada sócio
        novoSocio->numtitulo = socio->numtitulo;
        novoSocio->nometitular = socio->nometitular;
        novoSocio->nomedependente[0] = socio->nomedependente[0];
        novoSocio->nomedependente[1] = socio->nomedependente[1];
        novoSocio->pagtoemdia = socio->pagtoemdia;

        novoSocio->next = listasocios;
        listasocios = novoSocio;
    }

    cout << "Dados carregados com sucesso.\n";
    arquivo.close();
}


void liberarmemoria(Socio* listasocios, entradasaida* registroportaria) {
    Socio* atualSocios = listasocios;
    while (atualSocios != NULL) {
        Socio* next = atualSocios->next;
        delete atualSocios;
        atualSocios = next;
    }

    entradasaida* atualEntradas = registroportaria;
    while (atualEntradas != NULL) {
        entradasaida* next = atualEntradas->next;
        delete atualEntradas;
        atualEntradas = next;
    }
}
