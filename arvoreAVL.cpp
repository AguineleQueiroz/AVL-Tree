
#include <iostream>
#include <iomanip> 
#include <stdlib.h>
#include <fstream>
#include <time.h>


struct No_Registro
{
    int chave;
    int altura; 
    No_Registro *_esquerda;
    No_Registro *_direita;
};

struct Arv_Arquivo
{
    std::string nome_Arquivo;
    int chave_Arquivo;
    int dados_Arquivo;
};

No_Registro *no_RegistroAVL( int valor )
{
    No_Registro *No_Registro_ = new No_Registro(); 
    No_Registro_->chave = valor;
    No_Registro_->_esquerda = NULL;
    No_Registro_->_direita = NULL;
    No_Registro_->altura = 1;

    return ( No_Registro_);
}

int altura_No_Registro( No_Registro *no_Reg )
{
    if( no_Reg == NULL )
    {
        return -1;
    }else{
        return no_Reg->altura;
    }
}

int maior_( int a, int b )
{
    if (  a > b )
    {
        return a;
    }else{
        return b;
    }
}

int balanceamento_No_Registro( No_Registro *no_Reg )
{
    if(no_Reg == NULL)
    {
        return -1;
    }
    return (altura_No_Registro( no_Reg->_esquerda ) - altura_No_Registro( no_Reg->_direita ));
} 
//Rotacao simples esquerda
No_Registro *rotacao_EE( No_Registro *raiz )
{
    No_Registro *aux;
    aux = raiz->_esquerda;
    raiz->_esquerda = aux->_direita; // trocando as chaves dos No_Registros antes de rotacionar
    aux->_direita = raiz;
    raiz->altura = maior_( altura_No_Registro( raiz->_esquerda ), altura_No_Registro(raiz->_direita ) ) + 1;
    aux->altura = maior_( altura_No_Registro( aux->_esquerda ), raiz->altura) + 1;
    raiz = aux;
    return raiz; 
} 
//Rotacao simples direita
No_Registro *rotacao_DD( No_Registro *raiz )
{
    No_Registro *aux;
    aux = raiz->_direita;
    raiz->_direita = aux->_esquerda; 
    aux->_esquerda = raiz; // a chave que estava na raiz é o filho da esquerda de aux
    raiz->altura = maior_( altura_No_Registro( raiz->_esquerda ), altura_No_Registro( raiz->_direita ) ) + 1;
    aux->altura = maior_( altura_No_Registro ( aux->_direita ), raiz->altura ) + 1;
    raiz = aux;
    return raiz;
}
//Rotacao dupla
No_Registro *rotacao_ED( No_Registro * raiz )
{
    rotacao_DD( &*raiz->_esquerda ); 
    rotacao_EE( raiz );
    return raiz;
}
// Rotação dupla
No_Registro *rotacao_DE( No_Registro * raiz )
{
    rotacao_EE( &*raiz->_direita ); 
    rotacao_DD( raiz );
    return raiz;
}

No_Registro *InserirAVL( No_Registro *raiz,  int valor )
{
    if( raiz == NULL )
    {
        return (no_RegistroAVL( valor )); 
    }
    if(valor < raiz->chave )
    {
        raiz->_esquerda = InserirAVL( raiz->_esquerda, valor );
    }else if( valor > raiz->chave) 
    {        
        raiz->_direita = InserirAVL( raiz->_direita, valor );
    }else{
        return raiz; // Chaves iguais nao sao permitidas
    }
    //atualizando a altura do No_Registro anterior
    raiz->altura = 1 + maior_( altura_No_Registro(raiz->_esquerda), altura_No_Registro(raiz->_direita) );

    int balanco_altura = balanceamento_No_Registro( raiz );
    //casos de desbalanceamentos e correcoes
    if( balanco_altura > 1)
    {
        if( valor < raiz->_esquerda->chave )
        {
            return rotacao_EE( raiz );
        }else if( valor > raiz->_esquerda->chave )
        {
            // Rotação dupla ( uma simples para direita e outra para a esquerda)
            raiz->_esquerda = rotacao_DD( raiz->_esquerda );
            return rotacao_EE( raiz );
        }
    }
    if( balanco_altura < -1)
    {
        if( valor > raiz->_direita->chave )
        {
            return rotacao_DD( raiz );

        }else if( valor < raiz->_direita->chave )
        {
            // Rotação dupla ( uma simples para esquerda e outra para a direita)
            raiz->_direita = rotacao_EE( raiz->_direita ); 
            return rotacao_DD( raiz ); 
        }
    }
    return raiz;
}
// Variavel global para acumular o numero de comparacoes
float comparacoes = 0;

No_Registro *Consulta(No_Registro *aponta, int valor_Busca)
{
    int quantidade_Consultas = 0;
    if ( aponta == NULL )
    {
        quantidade_Consultas++;
        std::cout << "\nArvore Vazia!" << std::endl;
        return 0;
    }
    No_Registro *noAtual = aponta;
    bool registro_Encontrado = false;
    while ( noAtual != NULL )
    {
        
        if ( valor_Busca == noAtual->chave )
        {
            quantidade_Consultas++;
            std::cout << "\nChave de Registro numero " << valor_Busca << " Encontrada!" << std::endl;
            std::cout << "Comparacoes executadas: " << quantidade_Consultas  << std::endl;

            registro_Encontrado = true;
            break;
        }else if (valor_Busca < noAtual->chave )
        {
            quantidade_Consultas++;
            noAtual = noAtual->_esquerda;
        }
        else if (valor_Busca > noAtual->chave )
        {
            quantidade_Consultas++;
            noAtual = noAtual->_direita;
        }       
    }
    if ( registro_Encontrado == false)
    {
        std::cout << "\nChave de Registro numero " << valor_Busca << " nao encontrada!" << std::endl;
        std::cout << " Comparacoes executadas: "<< quantidade_Consultas  << std::endl;
    }
    comparacoes +=quantidade_Consultas;
    return 0; 
}

int main( )
{
    int tamanho_arq = 1000, chave, dados, chave_busca, buscas = 2;
    float tempo_Medio = 0.0;
    std::string nome;
    // obtem o tempo antes e após finalizar uma busca
    clock_t tempo_Inicial, tempo_Final;

    Arv_Arquivo Arvore_Arquivo[tamanho_arq];
    Arv_Arquivo registro_Arv;

    No_Registro *raiz = NULL;
        
    std::ifstream leitura_Arq;
    leitura_Arq.open("numeros_Desordenados_1000.txt");

    for (int i = 0; i < tamanho_arq; i++)
    {
        leitura_Arq >> chave >> dados >> nome;
        registro_Arv.chave_Arquivo = chave;
        registro_Arv.dados_Arquivo = dados;
        registro_Arv.nome_Arquivo = nome;
        Arvore_Arquivo[i] = registro_Arv;

    }
    // Rotina de Insercao dos registros lidos na arvore
    for (int i = 0; i < tamanho_arq; i++)
    {
       raiz = InserirAVL( raiz, Arvore_Arquivo[i].chave_Arquivo );
    }
    leitura_Arq.close();
    

    // Rotina de obtencao do tempo médio das buscas por arquivo de entrada
    for (int i = 0; i < buscas; i++)
    {
        std::cout << "\nConsultar chave de numero: ";
        std::cin >> chave_busca;

        tempo_Inicial= clock();
        Consulta( raiz, chave_busca );
        tempo_Final = clock();

        tempo_Medio += tempo_Final - tempo_Inicial;
    }

    std::cout << std::fixed << std::setprecision(10);
    std::cout << "\nTempo Médio de Processamento de Buscas: " 
         << tempo_Medio/ (CLOCKS_PER_SEC * 1000)  << " milissegundos!" << std::endl;
         
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "Media de Comparacoes: " << comparacoes/ buscas << std::endl;
    return 0;
}
