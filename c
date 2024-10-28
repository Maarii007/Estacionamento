#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#define NUM_VAGAS 10

typedef struct{
	char placa[8];
	char modelo[15];
	char marca[15];
	char cor[15];
}informacaoVeiculo;

informacaoVeiculo  carro;

typedef struct{
	char data[9];
	char hora[6];
	char numero[NUM_VAGAS];
}informacaoVaga;

informacaoVaga vaga[NUM_VAGAS];

int converterMin(int horas, int minutos){
    return horas * 60 + minutos;
}

int horarioValido(int horas){
    return horas >= 8 && horas <= 17;
}
float custoEstacionamento(int minutosChegada, int minutosSaida, int horaAbertura, int horaFechamento, float taxaHora){
    if(!horarioValido(horaAbertura) || !horarioValido(horaFechamento)){
        printf("Horários de abertura ou fechamento inválidos. Redigite.\n");
        return 0;
    }

    if (minutosChegada < horaAbertura * 60) {
        minutosChegada = horaAbertura * 60;
    }

    if (minutosSaida > horaFechamento * 60) {
        minutosSaida = horaFechamento * 60;
    }

    int minutosEstacionado = minutosSaida - minutosChegada;

    float custoTotal = minutosEstacionado / 60.0 * taxaHora;

    return custoTotal;
}
void pagamento(){
	fflush(stdin);
     int horaAbertura = 8; 
     
     int horaFechamento = 17; 
    
     float taxaHora = 5;
     
     char entrada[5];
     
     int horaChegada, minutoChegada;
     
     
     do{
        printf("Digite a hora de chegada: ");
        scanf("%d:%d", &horaChegada, &minutoChegada);

        if(!horarioValido(horaChegada)){
            printf("Hora de chegada inválida. Redigite.\n");
            
        }
     }while(!horarioValido(horaChegada));
     	int horaSaida, minutoSaida;

     do{
        printf("Digite a hora de saída: ");
        scanf("%d:%d", &horaSaida, &minutoSaida);
        
        if(!horarioValido(horaSaida)){
            printf("Hora de saída inválida. Redigite. \n");
        }
     } while (!horarioValido(horaSaida));
     	 int minutosChegada = converterMin(horaChegada, minutoChegada);
		 int minutosSaida = converterMin(horaSaida, minutoSaida);
		 float custo = custoEstacionamento(minutosChegada, minutosSaida, horaAbertura, horaFechamento, taxaHora);
		 
	 if(custo != 0){
	  printf("O custo do estacionamento é: R$ %.2f\n", custo);
	  
      return 0;
	 }
}

void inicializarVagas() {
	int i;
    for (i = 0; i < NUM_VAGAS; i++) {
        vaga[i].numero[0] = '\0';
    }
}

int cadastroVeiculo(){
	fflush(stdin);
	FILE *fp;
	fp = fopen("cadastroVeiculo.txt","a");
	fflush(stdin);
	int i,j;
	if (fp== NULL) {
		printf("Erro ao abrir o arquivo");
	}
	else{
	printf("\nPlaca:");
	fscanf(stdin,"%s",carro.placa);
	fprintf(fp,"%s\n",carro.placa);
	
	printf("\nModelo:");
	fscanf(stdin,"%s",carro.modelo);
	fprintf(fp,"%s\n",carro.modelo);
	
	printf("\nMarca:");
	fscanf(stdin,"%s",carro.marca);
	fprintf(fp,"%s\n",carro.marca);
	
	printf("\nCor:");
	fscanf(stdin,"%s",carro.cor);
	fprintf(fp,"%s\n",carro.cor);
	i++;
}
	fclose(fp);
    return 0;
}

 int ocuparVaga(){
 	fflush(stdin);
 	FILE *leitura;
 	FILE *escrita;
 	leitura = fopen("cadastroVeiculo.txt","r");
 	char linha[50],busca[8];
 	int i,compara;

 	
 	if(leitura == NULL){
 		printf("Erro ao abrir o arquivo");
	 }else{
	 printf("Insira a placa do veiculo: ");
	 fscanf(stdin,"%s",busca);
	 
 	i=0;
 	        for (i = 0; i < NUM_VAGAS; i++) {
            if (vaga[i].numero[0] == '\0') {
                strcpy(vaga[i].numero, busca);

                printf("Insira a data de chegada:");
                scanf("%s", vaga[i].data);

                printf("Insira a hora da chegada:");
                scanf("%s", vaga[i].hora);

                printf("\nVaga %d ocupada\n", i + 1);

                escrita = fopen("estacionamento.txt", "a");
                if (escrita != NULL) {
                    fprintf(escrita, "%s\n", busca);
                    fprintf(escrita, "%s\n", vaga[i].data);
                    fprintf(escrita, "%s\n", vaga[i].hora);
                    fclose(escrita);
                } else {
                    printf("Erro ao abrir o arquivo de estacionamento\n");
                }

                fclose(leitura);
                return 0;
            }
        }
        printf("\nTodas as vagas estão ocupadas\n");
        fclose(leitura);
    }
    return 1;
}


void listarVagasOcupadas() {
	fflush(stdin);
    printf("Vagas ocupadas: ");
    int i;
    for (i = 0; i < NUM_VAGAS; i++) {
        if (vaga[i].numero[0] != '\0') {
            printf("%d ", i + 1);
        }
    }
    printf("\n");
}

void listarVagasLivres() {
    printf("Vagas livres: ");
    int i;
    for (i = 0; i < NUM_VAGAS; i++) {
        if (vaga[i].numero[0] == '\0') {
            printf("%d ", i + 1);
        }
    }
    printf("\n");
}

void liberarVaga() {
	char busca[8];
	int i;
	int compara;
	
	printf("Insira a placa do veículo: ");
	scanf("%s",&busca);
	
	for (i = 0; i < NUM_VAGAS; i++) {
        compara = strcmp(busca, vaga[i].numero);

          if (compara == 0) {
            printf("Vaga %d liberada\n", i + 1);
            break;
        }
    }

    if (i < NUM_VAGAS) {
        pagamento();
        vaga[i].numero[0] = '\0';
    } else {
        printf("\n Placa não encontrada entre os veículos\n");
    }
}

int menu(){
    int opcao;

    do {
        printf("======= Menu Principal =======\n");
        printf("1. Cadastro do veículo\n");
        printf("2. Ocupar uma vaga\n");
        printf("3. Listar vagas livres\n");
        printf("4. Listar vagas ocupadas\n");
        printf("5. Liberar vaga\n");
        printf("6. Sair\n");
        printf("==============================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        fflush(stdin);

        switch (opcao) {
            case 1:
            	fflush(stdin);
                cadastroVeiculo();
                break;
            case 2:
            	fflush(stdin);
                ocuparVaga();
                break;
            case 3:
            	fflush(stdin);
                listarVagasLivres();
                break;
            case 4:
            	fflush(stdin);
                listarVagasOcupadas();
                break;
            case 5:
            	fflush(stdin);
            	liberarVaga();
            	break;
            case 6:
                printf("Saindo do programa. Por favor aguarde. \n");
                break;
            default:
                printf("A opção que digitou é inválida. Caso ocorreu um erro, por favor, tente novamente.\n");
                break;
        }
        fflush(stdin);
    } while (opcao != 6);
}


int main(){
	setlocale(LC_ALL,"Portuguese");
	inicializarVagas();
	menu();
}
