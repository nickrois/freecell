/*
Creator: Nicolas Brambilla Rodrigues
Instagram: @nickrois_
Github: github.com/nickrois
Description: Development for data structure subject at Itajuba's
             Federal University, taught by Dr. Enzo Seraphim
             and Dr. Thatyana Seraphim.
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include<windows.h>

typedef struct no{
  int num;
  char naipe;
  struct no *prox;
} tCarta;

tCarta *primMesa[8];
tCarta *primNaipe[4];
tCarta *temp[4];
tCarta *primMonte;

int total=0;
int numNaipe[4];
int totalMesa[8];

void inicializaVar(){ // inicializa variaveis
  primMonte = NULL;

  for(int i=0;i<8;i++){
    primMesa[i] = NULL;
    totalMesa[i] = 0;
    if(i<4){
      primNaipe[i] = NULL;
      temp[i] = NULL;
      numNaipe[i] = 0;
    }
  }
}

void carta(int pos, int num, char naipe){ // cria carta na lista dinamica primMonte
  tCarta *aux = primMonte;
  tCarta *novo = (tCarta*)malloc(sizeof(tCarta));
  novo->num = num;
  novo->naipe = naipe;
  if(pos==0){
    novo->prox = primMonte;
    primMonte = novo;
  }else{
    for(int i=0;i<pos-1;i++){
      aux = aux->prox;
    }
    novo->prox = aux->prox;
    aux->prox = novo;
  }
}

void gerarBaralho(){ // gera baralho ja embaralhado
  int pos;
  for(int i=3;i<=6;i++){
    for(int j=1;j<=13;j++){
      pos = rand()%(total+1);    // pos em rand ja embaralha ao criar baralho
      carta(pos,j,i);
      total++;
    }
  }
}//end gerarBaralho

void distribuirMesa(){
  tCarta *aux,*pen,*auxMesa;

  for(int base=0;base<7;base++){ // distribui 6 cartas em cada pilha da mesa
    for(int i=0;i<8;i++){ // distribui 4 ultimas cartas nas pilhas da mesa
      if(base==6 && i>3)//verifica onde vai colocar as 4 ultimas cartas
        break;
      aux = primMonte;
      pen = primMonte;
      auxMesa = primMesa[i];
      while(aux->prox!=NULL){ //acha ultimo elemento
        aux = aux->prox;
      }
      if(pen->prox!=NULL){ // nao perde ultimo elemento
        while(pen->prox!=aux){ // acha penultimo elemento, caso tenha
          pen = pen->prox;
        }
      }
      pen->prox = NULL;
      if(primMesa[i]==NULL){ // insere no caso 1: primeira posicao da pilha
        primMesa[i] = aux;
        aux->prox = NULL;
      }else{ // insere no caso 2: demais posicoes da pilha
        while(auxMesa->prox!=NULL){
          auxMesa = auxMesa->prox;
        }
        auxMesa->prox = aux; // atualiza ponteiros base
        aux->prox = NULL;
      }
      totalMesa[i]++;
    }
  }

}//end distribuirMesa

void imprime(){
  char letra = 'a';

  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // comandos do cmd para definir hConsole
  CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

  WORD saved_attributes;
  /* Salvar estado atual */
  GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
  saved_attributes = consoleInfo.wAttributes; // salva config base do cmd ("color 20")

  system("cls");
  for(int i=0;i<4;i++){ // imprime temp
    printf("Temp %d: ",i+1);
    if(temp[i]==NULL){
      printf("[    ] ",i+1);
    }else{
      if(temp[i]->naipe==3||temp[i]->naipe==4)
        SetConsoleTextAttribute(hConsole, 0x74); // carta vermelha
      else
        SetConsoleTextAttribute(hConsole, 0x70); // carta preta

        if(temp[i]->num==1) // letras no lugar dos numero em algumas cartas
          letra = 'A';
        if(temp[i]->num==11)
          letra = 'J';
        if(temp[i]->num==12)
          letra = 'Q';
        if(temp[i]->num==13)
          letra = 'K';

        if(letra=='a')
          printf("[%02d/%c]", temp[i]->num, temp[i]->naipe); // imprime cartas
        else
          printf("[%c /%c]", letra, temp[i]->naipe);

        letra = 'a';

      SetConsoleTextAttribute(hConsole, saved_attributes); // volta para config base ("color 20")
      printf(" ");
    }
  }
  printf("\n\n");

  tCarta *naipeAux;
  for(int i=0;i<4;i++){ // imprime pilhas de naipes, repetindo configs da impressao do temp
    naipeAux = primNaipe[i];
    if(naipeAux==NULL){
      printf("Naipe %d-%c: [    ]", i+1, i+3);
    }else{
      printf("Naipe %d-%c: ", i+1, i+3);
      while(naipeAux!=NULL){
        if(naipeAux->naipe==3||naipeAux->naipe==4)
          SetConsoleTextAttribute(hConsole, 0x74);
        else
          SetConsoleTextAttribute(hConsole, 0x70);

          if(naipeAux->num==1)
            letra = 'A';
          if(naipeAux->num==11)
            letra = 'J';
          if(naipeAux->num==12)
            letra = 'Q';
          if(naipeAux->num==13)
            letra = 'K';

          if(letra=='a')
            printf("[%02d/%c]", naipeAux->num, naipeAux->naipe);
          else
            printf("[%c /%c]", letra, naipeAux->naipe);

          letra = 'a';

        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(" ");
        naipeAux = naipeAux->prox;
      }
    }
    printf("\n");
  }
  printf("\n");

  tCarta *mesaAux;
  for(int i=0;i<8;i++){ // imprime mesa, repetindo configs da impressao do temp
    mesaAux = primMesa[i];
    if(mesaAux==NULL){
      printf("Mesa %d: [    ]", i+1);
    }else{
      printf("Mesa %d: ", i+1);
      while(mesaAux!=NULL){

        if(mesaAux->naipe==3||mesaAux->naipe==4)
          SetConsoleTextAttribute(hConsole, 0x74);
        else
          SetConsoleTextAttribute(hConsole, 0x70);

        if(mesaAux->num==1)
          letra = 'A';
        if(mesaAux->num==11)
          letra = 'J';
        if(mesaAux->num==12)
          letra = 'Q';
        if(mesaAux->num==13)
          letra = 'K';

        if(letra=='a')
          printf("[%02d/%c]", mesaAux->num, mesaAux->naipe);
        else
          printf("[%c /%c]", letra, mesaAux->naipe);
        letra = 'a';
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(" ");
        mesaAux = mesaAux->prox;
      }
    }
    printf("\n");
  }
  printf("\n");
}//end imprime


void moveMesaNaipe(){ // move carta da mesa para pilhas de naipe

  int posMesa, posNaipe;
  printf("\nDigite posicao da mesa e do naipe\nExemplo: 1 1\n-> ");
  scanf("%d %d", &posMesa, &posNaipe);
  tCarta *auxMesa = primMesa[posMesa-1];
  tCarta *penMesa = NULL;
  tCarta *auxNaipe = primNaipe[posNaipe-1];

  if(auxNaipe!=NULL){
    while(auxNaipe->prox!=NULL){ // ultimo naipe
      auxNaipe = auxNaipe->prox;
    }
  }

  while(auxMesa->prox!=NULL){ // penultimo e ultima posicao da linha da mesa
    penMesa = auxMesa;
    auxMesa = auxMesa->prox;
  }

  if((auxMesa->num)==(numNaipe[posNaipe-1]+1)){ // define ifs num e naipe
    if(auxMesa->naipe==posNaipe+2){
      if(primNaipe[posNaipe-1]==NULL){
        primNaipe[posNaipe-1] = auxMesa; // primeira insercao
      }else{
        auxNaipe->prox = auxMesa; // qualquer insercao
      }

      if(penMesa==NULL){ // if deixa mesa vazia ou nao
        auxNaipe = primMesa[posMesa-1];
        primMesa[posMesa-1] = NULL;
      }else{
        auxNaipe = auxMesa;
        penMesa->prox = NULL;
      }
      numNaipe[posNaipe-1] += 1;


    }//end if naipe mesa igual a pilha de naipe
    else{
      printf("\nNaipe da carta deve ser o mesmo da pilha de naipes!\nENTER PARA CONTINUAR.");
      getchar();
      getchar();
    }//end else naipe diferente
  }//end if numero em ordem
  else{
    printf("\nNumero da carta da mesa deve ser um a mais da ultima carta da pilha de naipes, com inicio em 1!\nENTER PARA CONTINUAR.");
    getchar();
    getchar();
  }


}//end moveMesaNaipe

void moveMesaTemp(){ // move carta da mesa para um dos temps
  int posMesa, posTemp;
  printf("\nDigite posicao da mesa e do temp\nExemplo: 1 1\n-> ");
  scanf("%d %d", &posMesa, &posTemp);
  if(temp[posTemp-1]==NULL){ // condicao para temp estar vazio
    if(primMesa[posMesa-1]!=NULL){ // condicao para mesa ter elemento
      tCarta *auxMesa = primMesa[posMesa-1];
      tCarta *penMesa = NULL;

      while(auxMesa->prox!=NULL){ // percorre posicao da mesa
        penMesa = auxMesa;
        auxMesa = auxMesa->prox;
      }

      if(penMesa==NULL){ // verifica se mesa vai ficar vazia
        temp[posTemp-1] = primMesa[posMesa-1];
        primMesa[posMesa-1] = NULL;
      }else{
        temp[posTemp-1] = auxMesa;
        penMesa->prox = NULL;
      }
    }else{
      printf("\nMesa %d vazia. ENTER PARA CONTINUAR.",posMesa);
      getchar();
      getchar();
    }
  }else{
    printf("\nTemp %d ja cheio. ENTER PARA CONTINUAR.",posTemp);
    getchar();
    getchar();

  }
}//end moveMesaTemp

void moveTempMesa(){
  int posMesa, posTemp;
  bool corTemp,corMesa; //1=vermelho, 0=preto
  printf("\nDigite posicao do temp e da mesa\nExemplo: 1 1\n-> ");
  scanf("%d %d", &posTemp, &posMesa);
  tCarta *mesaAux = primMesa[posMesa-1];

  if(temp[posTemp-1]!=NULL){ // if garante temp cheio
      if(primMesa[posMesa-1]==NULL){ // if mesa vazia
        primMesa[posMesa-1] = temp[posTemp-1];
        temp[posTemp-1] = NULL;
      }else{
      while(mesaAux->prox!=NULL){ // percore mesa
        mesaAux = mesaAux->prox;
      }
      if(mesaAux==NULL){ // if mesa vazia
        mesaAux = temp[posTemp-1];
        temp[posTemp-1] = NULL;
      }else{
        if((mesaAux->naipe==3)||(mesaAux->naipe)==4) // if verifica cor
          corMesa = true;
        else
          corMesa = false;

        if((temp[posTemp-1]->naipe==3)||(temp[posTemp-1]->naipe)==4)
          corTemp = true;
        else
          corTemp = false;

        if((corTemp!=corMesa)){
          if((temp[posTemp-1]->num == (mesaAux->num)-1)){ // atualiza ponteiros de requisito de cor e numero foram aceitos
            mesaAux->prox = temp[posTemp-1];
            temp[posTemp-1] = NULL;
          }//end if numero
          else{
            printf("\nNumero do temp deve ser exatamente um a menos da mesa!\nENTER PARA CONTINUAR.");
            getchar();
            getchar();
          }//end else numero
        }//end if cor
        else{
          printf("\nCor do temp dever ser diferente da cor da mesa!\nENTER PARA CONTINUAR.",posTemp);
          getchar();
          getchar();
        }//end else cor
      }//end else mesa cheia
    }
  }//end if temp null
  else{
    printf("\nTemp vazio! ENTER PARA CONTINUAR.",posTemp);
    getchar();
    getchar();
  }//end else temp null

}//end moveTempMesa

void destroiJogo(){ // percore todos os vetores e matrizes e da free em tudo
  tCarta *aux;

  for(int i=0;i<4;i++){ // free nos temps
    free(temp[i]);
  }

  for(int i=0;i<4;i++){ // free nos naipes
    aux = primNaipe[i];
    while(aux->prox!=NULL){
      aux = primNaipe[i];
      primNaipe[i] = primNaipe[i]->prox;
      free(aux);
    }
    free(primNaipe[i]);
  }

  for(int i=0;i<8;i++){ //free na mesa
    aux = primMesa[i];
    while(aux->prox!=NULL){
      aux = primMesa[i];
      primMesa[i] = primMesa[i]->prox;
      free(aux);
    }
    free(primMesa[i]);
  }

}//end destroiJogo

void moveNaipeTemp(){
  int posNaipe, posTemp;

  printf("\nDigite posicao do naipe e do temp\nExemplo: 1 1\n-> ");
  scanf("%d %d", &posNaipe, &posTemp);

  if(temp[posTemp-1]==NULL){ // condicao para temp estar vazio
    if(primNaipe[posNaipe-1]!=NULL){ // condicao para naipe ter elemento
      tCarta *auxNaipe = primNaipe[posNaipe-1];
      tCarta *penNaipe = NULL;

      while(auxNaipe->prox!=NULL){ // percorre posicao do naipe
        penNaipe = auxNaipe;
        auxNaipe = auxNaipe->prox;
      }

      if(penNaipe==NULL){ // verifica se naipe vai ficar vazio
        temp[posTemp-1] = primNaipe[posNaipe-1];
        primNaipe[posNaipe-1] = NULL;
      }else{
        temp[posTemp-1] = auxNaipe;
        penNaipe->prox = NULL;
      }
      numNaipe[posNaipe-1] -= 1;
    }else{
      printf("\nNaipe %d vazio. ENTER PARA CONTINUAR.",posNaipe);
      getchar();
      getchar();
    }
  }else{
    printf("\nTemp %d ja cheio. ENTER PARA CONTINUAR.",posTemp);
    getchar();
    getchar();
  }

}//end moveNaipetemp

void moveTempNaipe(){

  int posTemp, posNaipe;
  printf("\nDigite posicao do temp e do naipe\nExemplo: 1 1\n-> ");
  scanf("%d %d", &posTemp, &posNaipe);
  if(temp[posTemp-1]!=NULL){
    tCarta *auxTemp = temp[posTemp-1];
    tCarta *auxNaipe = primNaipe[posNaipe-1];

    if(auxNaipe!=NULL){
      while(auxNaipe->prox!=NULL){ // ultimo naipe
        auxNaipe = auxNaipe->prox;
      }
    }


    if((auxTemp->num)==(numNaipe[posNaipe-1]+1)){ // define ifs num e naipe
      if(auxTemp->naipe==posNaipe+2){

        if(primNaipe[posNaipe-1]==NULL){
          primNaipe[posNaipe-1] = auxTemp; // primeira insercao
        }else{
          auxNaipe->prox = auxTemp; // qualquer insercao
          auxTemp->prox = NULL;
        }

        temp[posTemp-1] = NULL;
        numNaipe[posNaipe-1] += 1;


      }//end if naipe temp igual a pilha de naipe
      else{
        printf("\nNaipe da carta deve ser o mesmo da pilha de naipes!\nENTER PARA CONTINUAR.");
        getchar();
        getchar();
      }//end else naipe diferente
    }//end if numero em ordem
    else{
      printf("\nNumero da carta do temp deve ser um a mais da ultima carta da pilha de naipes, com inicio em 1!\nENTER PARA CONTINUAR.");
      getchar();
      getchar();
    }
  }else{
    printf("\nTemporario deve estar cheio!\nENTER PARA CONTINUAR.");
    getchar();
    getchar();
  }//end else temp vazio


}//end moveTempNaipe

void moveNaipeMesa(){

  int posNaipe, posMesa;
  bool mesaCor;
  bool naipeCor;

  printf("\nDigite posicao do naipe e da mesa\nExemplo: 1 1\n-> ");
  scanf("%d %d", &posNaipe, &posMesa);

  if(primNaipe[posNaipe-1]!=NULL){ // condicao para naipe nao estar vazio
      tCarta *auxNaipe = primNaipe[posNaipe-1];
      tCarta *penNaipe = NULL;
      tCarta *auxMesa = primMesa[posMesa-1];
      tCarta *penMesa = NULL;

      while(auxNaipe->prox!=NULL){ // percorre posicao do naipe
        penNaipe = auxNaipe;
        auxNaipe = auxNaipe->prox;
      }

      while(auxMesa->prox!=NULL){ // percorre posicao da mesa
        penMesa = auxMesa;
        auxMesa = auxMesa->prox;
      }

      if(auxMesa==NULL){//if mesa vazia
        primMesa[posMesa-1] = auxNaipe;
        if(penNaipe==NULL){//se ultimo no naipe
          primNaipe[posNaipe-1] = NULL;
        }else{
          penNaipe->prox = NULL;
        }//end se ultimo no naipe
        numNaipe[posNaipe-1] -= 1;
      }else{

        if((auxMesa->naipe==3)||(auxMesa->naipe==4)) // ifs verifica cor
          mesaCor = true;
        else
          mesaCor = false;

        if((auxNaipe->naipe==3)||(auxNaipe->naipe==4))
          naipeCor = true;
        else
          naipeCor = false;

        if(naipeCor!=mesaCor){
          if((auxNaipe->num == (auxMesa->num)-1)){
            auxMesa->prox = auxNaipe;

            if(penNaipe==NULL){//se ultimo no naipe
              primNaipe[posNaipe-1] = NULL;
            }else{
              penNaipe->prox = NULL;
            }//end se ultimo no naipe

            numNaipe[posNaipe-1] -= 1;

          }else{
              printf("\nNumero do naipe deve ser exatamente um a menos da mesa!\nENTER PARA CONTINUAR.");
              getchar();
              getchar();
            }//end else numero
        }//end if cor
        else{
          printf("\nCor do naipe dever ser diferente da cor do ultimo da mesa!\nENTER PARA CONTINUAR.");
          getchar();
          getchar();
        }//end else cor
      }//end else mesa cheia
  }else{
    printf("\nNaipe %d vazio! ENTER PARA CONTINUAR.",posNaipe);
    getchar();
    getchar();
  }

}//end moveNaipeMesa

void deletacartaMesa(){ //deleta uma carta de uma mesa (DEV)
  int mesaO;
  printf("\nDigite posicao da mesa\nExemplo: 1\n-> ");
  scanf("%d", &mesaO);
  if(primMesa[mesaO-1]!=NULL){
    tCarta *auxMesaO = primMesa[mesaO-1];
    tCarta *penMesaO = NULL;
    while(auxMesaO->prox!=NULL){ // percorre posicoes da mesaO
      penMesaO = auxMesaO;
      auxMesaO = auxMesaO->prox;
    }//end while
    if(penMesaO==NULL)
      primMesa[mesaO-1]=NULL;
    else
      penMesaO->prox = NULL;
  }
}//end deletacartaMesa

void deletaTodasCartasMesa(){ //deleta todas as cartas da mesa (DEV)
  for(int i=0;i<8;i++){
    primMesa[i] = NULL;
  }
}

void moveMesaMesa(){
  int mesaO, mesaD, qMove, holder;
  int totalO=1;
  bool origem=true,mesaCorO,mesaCorD;
  printf("\nDigite posicao de origem e destino da mesa e a quantidade de cartas\nExemplo: 1 1 1\n-> ");
  scanf("%d %d %d", &mesaO, &mesaD, &qMove);
  if(primMesa[mesaO-1]!=NULL){
    tCarta *auxMesaO = primMesa[mesaO-1];
    tCarta *penMesaO = NULL;
    tCarta *auxMesa;
    tCarta *auxMesaD = primMesa[mesaD-1];
    tCarta *penMesaD = NULL;

    while(auxMesaO->prox!=NULL){ // percorre posicoes da mesaO
      penMesaO = auxMesaO;
      auxMesaO = auxMesaO->prox;
      totalO+=1;
    }//end while

    if(primMesa[mesaD-1]!=NULL){//acessa posicoes apenas se existirem
      while(auxMesaD->prox!=NULL){ // percorre posicoes da mesaD
        penMesaD = auxMesaD;
        auxMesaD = auxMesaD->prox;
      }//end while
    }

    totalO -= qMove;
    holder = totalO;

    if(totalO>=0){ //verifica ate onde deve percorrer
      auxMesaO = primMesa[mesaO-1];
      penMesaO = NULL;
      while((auxMesaO->prox!=NULL)&&(totalO)){ // percorre posicoes da mesaO
        penMesaO = auxMesaO;
        auxMesaO = auxMesaO->prox;
        totalO--;
      }//chega no inicio das cartas a serem movidas
      auxMesa = auxMesaO;
      if(qMove>1){
        while(auxMesaO->prox!=NULL){ //verifica as cartas seguintes da origem
          if(((auxMesaO->naipe==3)&&(auxMesaO->prox->naipe==3))||
             ((auxMesaO->naipe==4)&&(auxMesaO->prox->naipe==4))||
             ((auxMesaO->naipe==3)&&(auxMesaO->prox->naipe==4))||
             ((auxMesaO->naipe==4)&&(auxMesaO->prox->naipe==3))||
             (auxMesaO->num != (auxMesaO->prox->num)+1)){
               origem=false;
               break;
          }
          penMesaO = auxMesaO;
          auxMesaO = auxMesaO->prox;
        }//end verifica origem
      }

      if((auxMesa->naipe==3)||(auxMesa->naipe==4)) // ifs verifica cor mesaO e mesaD
        mesaCorO = true;
      else
        mesaCorO = false;

      if(primMesa[mesaD-1]!=NULL){//acessa posicoes apenas se existirem
        if((auxMesaD->naipe==3)||(auxMesaD->naipe==4))
          mesaCorD = true;
        else
          mesaCorD = false;
      }else{
        mesaCorD = !mesaCorO; //forca cores a serem diferentes para os proximos ifs de verificacao
      }

      if(origem){ //verifica se requisito base é cumprido(cartas em ordem e cor alternada)
        if(mesaCorO!=mesaCorD){ //verifica se cores diferentes
          if(primMesa[mesaD-1]!=NULL){
          if((auxMesa->num == (auxMesaD->num)-1)){

            if(primMesa[mesaD-1]==NULL){//se primeiro na mesa destino
              primMesa[mesaD-1] = auxMesa;
            }else{
              auxMesaD->prox = auxMesa;
            }//end se primeiro na mesa destino

            auxMesaO = primMesa[mesaO-1];
            penMesaO = NULL;
            while((auxMesaO->prox!=NULL)&&(holder)){ // percorre posicoes da mesaO
              penMesaO = auxMesaO;
              auxMesaO = auxMesaO->prox;
              holder--;
            }

            if(penMesaO==NULL){//se ultimo na mesa origem
              primMesa[mesaO-1] = NULL;
            }else{
              penMesaO->prox = NULL;
            }//end se ultimo na mesa origem

          }else{
              printf("\nNumero da mesa origem deve ser exatamente um a menos da mesa destino!\nENTER PARA CONTINUAR.");
              getchar();
              getchar();
            }//end else numero
          }else{//else para se a mesa destino estiver vazia nao acessar posicoes invalidas (ex.:mesadestino->num)

            primMesa[mesaD-1] = auxMesa;

            auxMesaO = primMesa[mesaO-1];
            penMesaO = NULL;
            while((auxMesaO->prox!=NULL)&&(holder)){ // percorre posicoes da mesaO
              penMesaO = auxMesaO;
              auxMesaO = auxMesaO->prox;
              holder--;
            }

            if(penMesaO==NULL){//se ultimo na mesa origem
              primMesa[mesaO-1] = NULL;
            }else{
              penMesaO->prox = NULL;
            }//end se ultimo na mesa origem

          }//else mesa destino vazia
        }else{
          printf("\nCor da mesa origem dever ser diferente da cor da mesa destino!\nENTER PARA CONTINUAR.");
          getchar();
          getchar();
        }//end else cor
     }else{//cartas da origem movimento invalido
       printf("\nCartas da origem nao sao alternadas em cor e um numero a menos (gradativo)!\nENTER PARA CONTINUAR.");
       getchar();
       getchar();
     }
    }else{//cartas insuficientes na mesa origem
      printf("\nCartas insuficientes na mesa origem!\nENTER PARA CONTINUAR.");
      getchar();
      getchar();
    }

  }else{//mesa origem vazia
    printf("\nMesa de origem vazia!\nENTER PARA CONTINUAR.");
    getchar();
    getchar();
  }

}//end moveMesaMesa

bool verificaVitoria(){
  bool verifica = true;
  tCarta *naipe;

  for(int i=0;i<4;i++){ //verifica naipes
    naipe = primNaipe[i];
    if(naipe!=NULL){
      while(naipe->prox !=NULL){
        naipe = naipe->prox;
      }
      if(naipe->num!=13){ //verifica se naipes estao completos
        verifica = false;
      }
    }else{
      verifica = false; //verifica se tem pelo menos um elemento nos naipes
    }
  }

  if(verifica){ //tela de vitoria se naipes completos
    system("cls");
    printf("\n                       -============================================-\n");
    printf("                      :==-.    :============================:.   .-==:\n");
    printf("                      :==-      :==========================-      -==:\n");
    printf("                       -==:      -========================-      :==-\n");
    printf("                        .-=-:    .========================:    :-=-.\n");
    printf("                          .:-=-.  -=======================  .-==:.\n");
    printf("                             .:=-::======================-:-=:.\n");
    printf("                                :-========================-:\n");
    printf("                                  .=====================-.\n");
    printf("                                    -==================-\n");
    printf("                                     -================-\n");
    printf("                                      :==============:\n");
    printf("                                        .-========-:\n");
    printf("                                            -==-\n");
    printf("                                            -==-\n");
    printf("                                            -==-\n");
    printf("                                            ====\n");
    printf("                                           .====.\n");
    printf("                                          .======.\n");
    printf("                                       ..:========:..\n");
    printf("                                    .::==============::\n");
    printf("                              :-----+******************------:\n");
    printf("                              +*-----------VITORIA-----------*\n");
    printf("                              ++-----------FREECELL---------=*\n");
    printf("                              +-------------UNIFEI----------=*\n");
    printf("                              +*=============================*\n");
    printf("\n\n                                     OBRIGADO POR JOGAR\n");
    destroiJogo();
    return true;
  }else{
    return false;
  }

}//end verificaVitoria


int main(int argc, char **argv){
    system("color 20");
    int op=0;
    srand(time(NULL));
    gerarBaralho();
    distribuirMesa();
    while(op!=8){
        if(verificaVitoria()){
          destroiJogo();
          return 0;
        }
        imprime();
        printf("Table->Mesa; Naipe->Suit; Temp->Temporary\n");
        printf("1- Mesa para naipe\n");
        printf("2- Mesa para temp\n");
        printf("3- Temp para mesa\n");
        printf("4- Naipe para temp\n");
        printf("5- Temp para naipe\n");
        printf("6- Naipe para mesa\n");
        printf("7- Mesa para mesa\n");
        printf("8- Sair\n\n");
        /*printf("9- Deleta uma carta(DEV)\n");
        printf("10- Deleta todas as mesas(DEV)\n");*/
        printf("Escolha: ");
        scanf("%d", &op);
        getchar();
        switch(op){
            case 1:
              moveMesaNaipe();
              break;
            case 2:
              moveMesaTemp();
              break;
            case 3:
              moveTempMesa();
              break;
            case 4:
              moveNaipeTemp();
              break;
            case 5:
              moveTempNaipe();
              break;
            case 6:
              moveNaipeMesa();
              break;
            case 7:
              moveMesaMesa();
              break;
            case 8:
              system("cls");
              destroiJogo();
              return 0;
              break;
            /*case 9:
              deletacartaMesa();
              break;
            case 10:
              deletaTodasCartasMesa();
              break;*/
            default:
              printf("\nOpcao invalida (enter)\n");
              getchar();
              break;
        }
    }
    return 0;
}//end main
