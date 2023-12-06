#include <iostream>
#include <locale>
#include <fstream>

using namespace std;

struct associados{
	int numtitulo; 
	string nometitular;
	string nomedependente[2];
	bool pagtoemdia;
};
	
struct node{
	
};

struct lista{ 
	
};

struct entradas{
	
};

void verificarinadimplencia();
void inserirsocio();
void inserirdependente();
void listarsocio();
void removersocio();
void registrarvisita();
void relatoriovisitas();
void carregarsocios(); //DICA: Utilize a biblioteca fstream do C++ | Definir a estrutura do arquivo .txt


int main(int argc, char** argv) {
	setlocale(LC_ALL, "Portuguese");
	int menu;
	
	cout << "MENU: \n";
	cout << "1 - Checar situação do título\n";
	cout << "2 - Inserir sócio \n";
	cout << "3 - Inserir dependente \n";
	cout << "4 - Listar sócios e dependentes \n";
	cout << "5 - Remover sócio \n";
	cout << "6 - Registrar entrada ou saída de sócio \n";
	cout << "7 - Gerar relatório de visitas \n";
	cout << "8 - Carregar sócios \n";
	cout << "9 - Sair \n Escolha a opção: ";
    cin >> menu;
    
	do{
		switch(menu){
        	case 1:
        		verificarinadimplencia();
            	break;
        	case 2:
        		inserirsocio();
            	break;
        	case 3:
        		inserirdependente();
            	break;
        	case 4 :
        		listarsocio();
            	break;
        	case 5 :
        		removersocio();
        		break;
        	case 6 :
        		registrarvisita();
        		break;
        	case 7 :
        		relatoriovisitas();
        		break;
        	case 8 :
        		carregarsocios();
        		break;
        	case 9 :
            	cout << "Saindo...";
        	    break;
    	}
    }while(menu != 9);
	
	return 0;
}

void inserirsocio(){
	
}

void listarsocio(){
	
}

void removersocio(){
	
}

void inserirdependente(){
	
}

void verificarinadimplencia(){
	
}
