#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <TimerOne.h>
 
//
//variavais de controle
//
int ditTime = 100;              //tempo do ponto
int dashTime = ditTime * 3;     //tempo do traco (ponto * 3) 
int spaceLetter = dashTime;     //espaco entre letras
int space = ditTime;            //espaco entre pontos e tracos qeu compoem mesma letra
int spaceWord = ditTime * 7;    //espaco entre palavras
//
int intervaloBeacon = 2000; //tempo default de espera de interacao do beacon
//
boolean isAutomatico = false;
boolean interacoes = false;
// portas e configuracoes de hardware
//
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //pinos do display LCD
//
int teclaTraco = 8;
int teclaPonto = 9; 
//
int chave1 = A1;
int chave2 = A2;
//
//
int saida = 13; //saida para circuito Rele
int saida2 = 7;
//
//variaveis de controle EEPROM
int tamanhoMemoria = 512;
char t;
int address = 0;
byte value;
//
//variaveis de tela do editor
//
//
int i = 0; //cariavel do cursor do seletor de texto de memoria
int c = 0;  //varicavel cursor de LCD para display texto
//
char v;     //char para conversao do inteiro em char e exibicao no LCD
String out = String(""); //saida de texto para gravaçao na memoria
//
//vetor de inteiros representando letras e caracteres, 
//para exibicao na tela LCD no modo de edicao
int vetorCaracteres[] = {  
  65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90,48, 49, 50, 51, 52, 53, 54, 55, 56,57,32};
//
//
//variaveis de tela de boas vindas
//
String splash1 = String("Chave Automatica");
String splash2 = String("Bem Vindo! v:1.0");
//
int tempoSplashScreen = 3000;
//
//
//Variaveis de comparacao e controle de dados
//String que sera concatenada
String str = String("");
boolean done = false;
int index = 0; 
boolean isMenuAtivo = false;
//
//
String txt = String(""); 
String morse = String(""); 
//
const String A = String(".-"); 
const String B = String("-..."); 
const String C = String("-.-."); 
const String D = String("-.."); 
const String E = String("."); 
const String F = String("..-."); 
const String G = String("--."); 
const String H = String("...."); 
const String I = String(".."); 
const String J = String(".---"); 
const String K = String("-.-"); 
const String L = String(".-.."); 
const String M = String("--"); 
const String N = String("-."); 
const String O = String("---"); 
const String P = String(".--."); 
const String Q = String("--.-"); 
const String R = String(".-."); 
const String S = String("..."); 
const String T = String("-"); 
const String U = String("..-"); 
const String V = String("...-"); 
const String W = String(".--"); 
const String X = String("-..-"); 
const String Y = String("-.--"); 
const String Z = String("--.."); 
//
const String zero = String("-----"); 
const String um = String(".----"); 
const String dois = String("..---"); 
const String tres = String("...--"); 
const String quatro = String("....-"); 
const String cinco = String("....."); 
const String seis = String("-...."); 
const String sete = String("--..."); 
const String oito = String("---.."); 
const String nove = String("----."); 
//
//
//
const String _A = String("A"); 
const String _B = String("B"); 
const String _C = String("C"); 
const String _D = String("D"); 
const String _E = String("E"); 
const String _F = String("F"); 
const String _G = String("G"); 
const String _H = String("H"); 
const String _I = String("I"); 
const String _J = String("J"); 
const String _K = String("K"); 
const String _L = String("L"); 
const String _M = String("M"); 
const String _N = String("N"); 
const String _O = String("O"); 
const String _P = String("P"); 
const String _Q = String("Q"); 
const String _R = String("R"); 
const String _S = String("S"); 
const String _T = String("T"); 
const String _U = String("U"); 
const String _V = String("V"); 
const String _W = String("W"); 
const String _X = String("X"); 
const String _Y = String("Y"); 
const String _Z = String("Z"); 
//
const String _0 = String("0"); 
const String _1 = String("1"); 
const String _2 = String("2"); 
const String _3 = String("3"); 
const String _4 = String("4"); 
const String _5 = String("5"); 
const String _6 = String("6"); 
const String _7 = String("7"); 
const String _8 = String("8"); 
const String _9 = String("9"); 
//
 
 
 
//metodo executado pela interrupcao, busca leitura do potenciometro com o objetivo de ajustar a velocidade
void potenciometro(){
 
  int sensorValue = analogRead(0);        
 
  ditTime = sensorValue *0.2; 
  dashTime = ditTime * 3;
  dashTime = ditTime * 3;     //tempo do traco (ponto * 3) 
  spaceLetter = dashTime;     //espaco entre letras
  space = ditTime;            //espaco entre pontos e tracos qeu compoem mesma letra
  spaceWord = ditTime * 7;    //espaco entre palavras
  //
 
  //caso qualquer paddle seja pressionado, retorna ao modo manual e limpa a tela
  if((isAutomatico && (digitalRead(teclaTraco) == HIGH)) || (isAutomatico && (digitalRead(teclaPonto) == HIGH))){
    isAutomatico = false; 
    lcd.clear();
  }
 
  if((digitalRead(chave2)==HIGH)&&(digitalRead(chave1)==HIGH)){
 
    delay(1000);
    if((digitalRead(chave2)==HIGH)&&(digitalRead(chave1)==HIGH)){  
      isAutomatico = false;
      loop();
 
    }
  }
 
 
}
 
void setup(){
 
  Timer1.initialize(1600000);
  Timer1.attachInterrupt(potenciometro); 
  //
  lcd.begin(16, 2);
  mostraSplashScreen(); 
  //
  //Serial.begin(9600);
  //
  pinMode(chave1, INPUT); 
  pinMode(chave2, INPUT); 
  //
  pinMode(teclaTraco, INPUT); 
  pinMode(teclaPonto, INPUT); 
  //
  pinMode(saida, OUTPUT);
  //
  ///leitura();
 
}
 
void loop(){
 
  //leitura();
 
  //
  //
  if(digitalRead(chave1)==HIGH){
    delay(300);
    exibeMenu();
 
  }
  else
    //ROTINA AUTO/MANUAL
    if(isAutomatico){
      beacon();
    }
  else{   
 
 
    checa();
 
  }
 
 
}
 
void ajustaTempoBeacon(){
  lcd.clear();
 
  lcd.setCursor(0,1);
  lcd.print("Tmp.Esper.Beac.");  
  while(true){
 
    lcd.setCursor(0,0);
    lcd.print(intervaloBeacon/1000);
    lcd.print(" Segundos."); 
 
    if(digitalRead(teclaTraco)==HIGH){
 
      delay(100);
      lcd.setCursor(0,0);
      lcd.print(intervaloBeacon/1000);
      lcd.print(" Segundos."); 
 
      delay(500);
      if(intervaloBeacon==10000){
        intervaloBeacon = intervaloBeacon;
 
      }
      else { 
        intervaloBeacon = intervaloBeacon + 1000;
 
      }
    }
    else if(digitalRead(teclaPonto)==HIGH){
      delay(100);
 
      lcd.setCursor(0,0);
      lcd.print(intervaloBeacon/1000);
      lcd.print(" Segundos."); 
 
      delay(500);
      if(intervaloBeacon==1000){
        intervaloBeacon = intervaloBeacon;
      }
      else{
        intervaloBeacon = intervaloBeacon - 1000;
      }
    }
 
 
 
 
 
    if(digitalRead(chave1)==HIGH){
      delay(100);
      if(digitalRead(chave1)==LOW){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Beacon = " + (intervaloBeacon/1000));
        delay(1000); 
        isAutomatico=false; 
        loop();
        break; //sai do metodo
      }
    }
  }
}
 
 
void exibeMenu(){
 
  int indiceMenu = 0; 
  int totalMenu = 4; 
  isMenuAtivo= true;
  lcd.clear();
 
  menu(indiceMenu);
 
  while(isMenuAtivo){
    if(digitalRead(teclaTraco)==HIGH){
      delay(700);
      indiceMenu++;
      if(indiceMenu>totalMenu){
        indiceMenu = totalMenu;
      }
      menu(indiceMenu);
    }
    else if(digitalRead(teclaPonto)==HIGH){
      delay(700);
      indiceMenu--; 
      if(indiceMenu<0){
        indiceMenu = 0;
      }
      menu(indiceMenu);
    }    
    else if(digitalRead(chave2)==HIGH){
      delay(10);
      if(digitalRead(chave2)==LOW){ 
        break; //sai do menu
      }
    }
    else if(digitalRead(chave1)==HIGH){
      delay(100);
      switch(indiceMenu){
 
      case 1:
        if(isMenuAtivo){
          isAutomatico = true;
          beacon();
          isMenuAtivo= false; 
        }
        break; 
      case 2:
        if(isMenuAtivo){
          ajustaTempoBeacon();
          isMenuAtivo= true; 
        }
        break;
      case 3:
        if(isMenuAtivo){
          isMenuAtivo= false;
          //MENU ESCREVE TEXTO MEMORIA
          textoMemorizar();
          isMenuAtivo= true; 
        }
        break;
 
      case 4:
        if(isMenuAtivo){
          isMenuAtivo= false; 
        }
        break;
      default:
        isMenuAtivo = true;
        break;
 
      }
 
    }
    //lcd.setCursor(0,0); 
    //lcd.print(indiceMenu);
  }
 
  lcd.clear(); 
 
  return; 
}
 
void menu(int m){
 
 
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("  *** MENU ***  ");
 
  switch(m){
 
  case 0:
 
    lcd.setCursor(0,1); 
    lcd.print("");
    break;
 
  case 1:
 
    lcd.setCursor(0,1); 
    lcd.print("-Iniciar Beacon");
    break;
  case 2:
 
    lcd.setCursor(0,1); 
    lcd.print("-Tempo Beacon");
    break;
  case 3:
 
    lcd.setCursor(0,1); 
    lcd.print("-Gravar Memoria");
    break;
    //case 3:
 
    //    lcd.setCursor(0,1); 
    //    lcd.print("-Apagar Memoria");
    //    break;
  case 4:
 
    lcd.setCursor(0,1); 
    lcd.print("-Voltar");
    break;
 
  }
 
 
 
 
}
 
 
void beacon(){
 
  leitura();
  lcd.clear();
  lcd.setCursor(3,1); 
  lcd.print("... TX ..."); 
  lcd.setCursor(0,0); 
  comparaTexto();
  delay(10);
  espaco();
  delay(10);
 
  //
  index = 0;
  //
  delay(10);
  //
 
 
  lcd.clear();
  lcd.setCursor(1,1); 
  lcd.print("Aguardando...");  //
 
 
 
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0); 
 
}
 
void emiteMorse(String m){
 
  if(isAutomatico){
    for(int j=0;j<m.length();j++){
      if(m.charAt(j)=='.'){
        ponto();
      }
      else if (m.charAt(j)=='-'){
        traco();
      }
      else{
        espaco();
      }
 
    }
  }
  else{
    return;
  }
}
 
void comparaTexto(){
  //lcd.print(txt);
 
  if(isAutomatico){
    for(int i =0; i<txt.length(); i++){
 
      limpaLcd();
 
      index++; 
 
      if(txt.charAt(i)==_A.charAt(0)){
        lcd.print(_A);
        emiteMorse(A); 
      }
      else     if(txt.charAt(i)==_B.charAt(0)){
        lcd.print(_B);
        emiteMorse(B); 
      }
      else     if(txt.charAt(i)==_C.charAt(0)){
        lcd.print(_C);
        emiteMorse(C); 
      }
      else     if(txt.charAt(i)==_D.charAt(0)){
        lcd.print(_D);
        emiteMorse(D); 
      }
      else     if(txt.charAt(i)==_E.charAt(0)){
        lcd.print(_E);
        emiteMorse(E); 
      }
      else     if(txt.charAt(i)==_F.charAt(0)){
        lcd.print(_F);
        emiteMorse(F); 
      }
      else     if(txt.charAt(i)==_G.charAt(0)){
        lcd.print(_G);
        emiteMorse(G); 
      }
      else     if(txt.charAt(i)==_H.charAt(0)){
        lcd.print(_H);
        emiteMorse(H); 
      }
      else     if(txt.charAt(i)==_I.charAt(0)){
        lcd.print(_I);
        emiteMorse(I); 
      }    
      else     if(txt.charAt(i)==_J.charAt(0)){
        lcd.print(_J);
        emiteMorse(J); 
      }
      else     if(txt.charAt(i)==_K.charAt(0)){
        lcd.print(_K);
        emiteMorse(K); 
      }
      else     if(txt.charAt(i)==_L.charAt(0)){
        lcd.print(_L);
        emiteMorse(L); 
      }
      else     if(txt.charAt(i)==_M.charAt(0)){
        lcd.print(_M);
        emiteMorse(M); 
      }
      else     if(txt.charAt(i)==_N.charAt(0)){
        lcd.print(_N);
        emiteMorse(N); 
      }
      else     if(txt.charAt(i)==_O.charAt(0)){
        lcd.print(_O);
        emiteMorse(O); 
      }
      else     if(txt.charAt(i)==_P.charAt(0)){
        lcd.print(_P);
        emiteMorse(P); 
      }
      else     if(txt.charAt(i)==_Q.charAt(0)){
        lcd.print(_Q);
        emiteMorse(Q); 
      }
      else     if(txt.charAt(i)==_R.charAt(0)){
        lcd.print(_R);
        emiteMorse(R); 
      }
      else     if(txt.charAt(i)==_S.charAt(0)){      
        lcd.print(_S);
        emiteMorse(S); 
      }
      else     if(txt.charAt(i)==_T.charAt(0)){
        lcd.print(_T);
        emiteMorse(T); 
      }
      else     if(txt.charAt(i)==_U.charAt(0)){
        lcd.print(_U);
        emiteMorse(U); 
      }
      else     if(txt.charAt(i)==_V.charAt(0)){
        lcd.print(_V);
        emiteMorse(V); 
      }
      else     if(txt.charAt(i)==_W.charAt(0)){
        lcd.print(_W);
        emiteMorse(W); 
      }
      else     if(txt.charAt(i)==_X.charAt(0)){
        lcd.print(_X);
        emiteMorse(X); 
      }
      else     if(txt.charAt(i)==_Y.charAt(0)){
        lcd.print(_Y);
        emiteMorse(Y); 
      }
      else     if(txt.charAt(i)==_Z.charAt(0)){
        lcd.print(_Z);
        emiteMorse(X); 
      }
      //
      //
      else     if(txt.charAt(i)==_0.charAt(0)){
        lcd.print(zero);
        emiteMorse(zero);
      }
      else     if(txt.charAt(i)==_1.charAt(0)){
        lcd.print(_1);
        emiteMorse(um);
      }
      else     if(txt.charAt(i)==_2.charAt(0)){
        lcd.print(_2);
        emiteMorse(dois);
      }
      else     if(txt.charAt(i)==_3.charAt(0)){
        lcd.print(_3);
        emiteMorse(tres);
      }
      else     if(txt.charAt(i)==_4.charAt(0)){
        lcd.print(_4);
        emiteMorse(quatro); 
      }
      else     if(txt.charAt(i)==_5.charAt(0)){
        lcd.print(_5);
        emiteMorse(cinco); 
      }
      else     if(txt.charAt(i)==_6.charAt(0)){
        lcd.print(_6);
        emiteMorse(seis); 
      }
      else     if(txt.charAt(i)==_7.charAt(0)){
        lcd.print(_7);
        emiteMorse(sete); 
      }
      else     if(txt.charAt(i)==_8.charAt(0)){
        lcd.print(_8);
        emiteMorse(oito); 
      }
      else     if(txt.charAt(i)==_9.charAt(0)){
        lcd.print(_9);
        emiteMorse(nove); 
      }
      else{
        lcd.print(" ");
        //      emiteMorse(String(" "));
        // delay(spaceWord);
        espaco();
      }
 
      // emiteMorse(String(" ")); delay(250); 
      delay(spaceLetter);
 
    }
  }
  else{
    return;
  }
 
}
 
void checa(){
 
  if(isAutomatico){
    return; 
  }
 
  if((digitalRead(teclaTraco)== HIGH)&&(digitalRead(teclaPonto)== LOW)){  
 
    traco(); 
 
  }
  else if((digitalRead(teclaPonto)== HIGH)&&(digitalRead(teclaTraco)== LOW)){  
 
    ponto();   
 
  }
  else  if((digitalRead(teclaTraco)== HIGH)&&(digitalRead(teclaPonto)== HIGH)){
 
    //    do{
    //      traco(); 
    //      delay(ditTime); 
    //      ponto();
    //      delay(ditTime); 
    //    }
    //    while((digitalRead(teclaTraco)== HIGH)&&(digitalRead(teclaPonto)== HIGH));
 
  }
 
 
  if((digitalRead(teclaTraco)== LOW)&&(digitalRead(teclaPonto)== LOW) && !isAutomatico){
 
    if(!done){
      //  //Serial.print(str);
      compara();
      //Serial.print(" ");
      str = String("");
      done = true; 
 
    }   
  }
 
 
}
 
void espaco(){
 
  digitalWrite(saida, LOW);
  delay(spaceLetter);
  str.concat(" "); 
  done = false;
  if(!isAutomatico)
    checa();    
 
}
 
void traco(){
 
 
 
  digitalWrite(saida, HIGH);
  delay(dashTime);
  digitalWrite(saida, LOW);
  delay(ditTime);
  str.concat("-"); 
  done = false;
  checa();
  if((digitalRead(teclaTraco)== HIGH)&&(digitalRead(teclaPonto)== HIGH) && !isAutomatico){
    ponto();
  }
 
 
}
 
void ponto(){
 
  digitalWrite(saida, HIGH); 
  delay(ditTime);
 
  digitalWrite(saida, LOW);
  delay(ditTime);
  str.concat("."); 
  done = false;
  checa();    
  if((digitalRead(teclaTraco)== HIGH)&&(digitalRead(teclaPonto)== HIGH)&& !isAutomatico){
    traco();
  }
 
 
}
 
void limpaLcd(){
  if(index ==15){
    index = 0; 
    lcd.clear();
    lcd.setCursor(0,0);
  }  
 
}
 
void limpaLcdTotal(){
  delay(500);
  if((digitalRead(teclaTraco)== HIGH)&&(digitalRead(teclaPonto)== HIGH)){
    lcd.clear();
    lcd.setCursor(0,0);
  }
}
////////////////
 
void compara(){
 
 
  limpaLcd();
 
  index++; 
 
 
  if(str.equals(String(""))){
    //Serial.println("");
  }
  else  
    if(str.equals(A)){
    //Serial.print(_A); 
    lcd.print(_A);
  }
  else  
    if(str.equals(B)){
    //Serial.print(_B); 
    lcd.print(_B);
  }
  else  
    if(str.equals(C)){
    //Serial.print(_C); 
    lcd.print(_C);
  }
  else  
    if(str.equals(D)){
    //Serial.print(_D); 
    lcd.print(_D);
  }
  else  
    if(str.equals(E)){
    //Serial.print(_E); 
    lcd.print(_E);
  }
  else  
    if(str.equals(F)){
    //Serial.print(_F); 
    lcd.print(_F);
  }
  else  
    if(str.equals(G)){
    //Serial.print(_G); 
    lcd.print(_G);
  }
  else  
    if(str.equals(H)){
    //Serial.print(_H); 
    lcd.print(_H);
  }
  else  
    if(str.equals(I)){
    //Serial.print(_I); 
    lcd.print(_I);
  }
  else  
    if(str.equals(J)){
    //Serial.print(_J); 
    lcd.print(_J);
  }
  else  
    if(str.equals(K)){
    //Serial.print(_K); 
    lcd.print(_K);
  }
  else  
    if(str.equals(L)){
    //Serial.print(_L); 
    lcd.print(_L);
  }
  else  
    if(str.equals(M)){
    //Serial.print(_M); 
    lcd.print(_M);
  }
  else  
    if(str.equals(N)){
    //Serial.print(_N); 
    lcd.print(_N);
  }
  else  
    if(str.equals(O)){
    //Serial.print(_O); 
    lcd.print(_O);
  }
  else  
    if(str.equals(P)){
    //Serial.print(_P); 
    lcd.print(_P);
  }
  else  
    if(str.equals(Q)){
    //Serial.print(_Q); 
    lcd.print(_Q);
  }
  else  
    if(str.equals(R)){
    //Serial.print(_R); 
    lcd.print(_R);
  }
  else  
    if(str.equals(S)){
    //Serial.print(_S); 
    lcd.print(_S);
  }
  else  
    if(str.equals(T)){
    //Serial.print(_T); 
    lcd.print(_T);
  }
  else  
    if(str.equals(U)){
    //Serial.print(_U); 
    lcd.print(_U);
  }
  else  
    if(str.equals(V)){
    //Serial.print(_V); 
    lcd.print(_V);
  }
  else  
    if(str.equals(W)){
    //Serial.print(_W); 
    lcd.print(_W);
  }
  else  
    if(str.equals(X)){
    //Serial.print(_X); 
    lcd.print(_X);
  }
  else  
    if(str.equals(Y)){
    //Serial.print(_Y); 
    lcd.print(_Y);
  }
  else  
    if(str.equals(Z)){
    //Serial.print(_Z); 
    lcd.print(_Z);
  } 
  else  
    if(str.equals(zero)){
    //Serial.print(_0); 
    lcd.print(_0);
  }
  else  
    if(str.equals(um)){
    //Serial.print(_1); 
    lcd.print(_1);
  }
  else  
    if(str.equals(dois)){
    //Serial.print(_2); 
    lcd.print(_2);
  }
  else  
    if(str.equals(tres)){
    //Serial.print(_3); 
    lcd.print(_3);
  }
  else  
    if(str.equals(quatro)){
    //Serial.print(_4); 
    lcd.print(_4);
  }
  else  
    if(str.equals(cinco)){
    //Serial.print(_5); 
    lcd.print(_5);
  }
  else  
    if(str.equals(seis)){
    //Serial.print(_6); 
    lcd.print(_6);
  }
  else  
    if(str.equals(sete)){
    //Serial.print(_7); 
    lcd.print(_7);
  }
  else  
    if(str.equals(oito)){
    //Serial.print(_8); 
    lcd.print(_8);
  }
  else  
    if(str.equals(nove)){
    //Serial.print(_9); 
    lcd.print(_9);
  }
 
  else{    
    //Serial.print(str); 
    lcd.print(str);
    index += str.length();
 
  }
  limpaLcd();
 
}
 
 
 
 
void leitura()
{
  while(true){
    // read a byte from the current address of the EEPROM
    value = EEPROM.read(address);
 
    if(value==35) return;  //'#' sai do metodo
 
    t = value; 
 
    //Serial.print(address);
    //Serial.print("\t");
    //Serial.print(t);
    //Serial.print("\t");
    //Serial.print(value);
    //Serial.println();
    txt.concat(t);
    //Serial.println(txt);
 
 
 
    // advance to the next address of the EEPROM
    address = address + 1;
 
    // there are only 512 bytes of EEPROM, from 0 to 511, so if we're
    // on address 512, wrap around to address 0
    if (address == tamanhoMemoria){
      address = 0;
      return;
    }
    //  delay(500);
  }
}
 
 
void mostraSplashScreen(){
 
  //
  lcd.setCursor(0,0);
  lcd.print(splash1);
  lcd.setCursor(0,1);
  lcd.print(splash2); 
  delay(tempoSplashScreen);
  lcd.clear();
  //
 
}
 
void textoMemorizar(){
  lcd.clear();
  lcd.setCursor(c,0);
  lcd.cursor();
  //  boolean isStay = true;
  // while(!isMenuAtivo){  
 
  while(true){
 
 
    if((digitalRead(chave2)==HIGH)&&(digitalRead(chave1)==HIGH)){
 
      delay(1000);
      if((digitalRead(chave2)==HIGH)&&(digitalRead(chave1)==HIGH)){  
 
        loop();
 
      }
 
 
    }
 
    if((digitalRead(chave1)==HIGH) && (out.length()>0)){
      delay(10);
      //if((digitalRead(chave1)==LOW) && (out.length()>0)){        
      delay(250); 
      gravaMemoria(); 
      //TESTE
      //   isAutomatico = true;
      isMenuAtivo = true;
      // isStay = false;
      //return;
      //
      //}
    }
 
    if(digitalRead(chave2)==HIGH){
      //      delay(10);
      //        if(digitalRead(chave2)==LOW){
      delay(250); 
      c--;
      lcd.setCursor(c,0); 
      out = out.substring(0,c); 
      //    }
    }
 
    if((digitalRead(teclaTraco)== HIGH)&&(digitalRead(teclaPonto)== LOW)){  
      do{
        lcd.noCursor();
        lcd.setCursor(c,0); 
        i++;
 
        if(i>37)
        {
          i = 0;
          v = 32;
        }
 
        v = vetorCaracteres[i];
        lcd.print(v);
        delay(400);
      }
      while ((digitalRead(teclaTraco)== HIGH)&&(digitalRead(teclaPonto)== LOW));
    }
    else if((digitalRead(teclaPonto)== HIGH)&&(digitalRead(teclaTraco)== LOW)){  
 
      do{
        lcd.noCursor();
        lcd.setCursor(c,0); 
        i--;
        if(i<0)
        {
          i =37;
          v = 32; 
        }
        v = vetorCaracteres[i];
        lcd.print(v);
        delay(400);
      }
      while ((digitalRead(teclaPonto)== HIGH)&&(digitalRead(teclaTraco)== LOW));
    }
    if((digitalRead(teclaTraco)== HIGH)&&(digitalRead(teclaPonto)== HIGH)){
      delay(10);
      // if((digitalRead(teclaTraco)== LOW)&&(digitalRead(teclaPonto)== LOW)){
      c++;
      lcd.clear();
      out.concat(v);
 
      i = 64;
      lcd.setCursor(c,0);
      lcd.cursor();  
      delay(100);
     // isMenuAtivo = false;
      // isStay = true;
      //break;
 
    lcd.clear(); 
    lcd.print(out);
    delay(1000);
 
       //}
    }
 
  }
  //  isMenuAtivo = true;
  //  }
}
 
 
void gravaMemoria(){
 
  lcd.setCursor(0,1);
  lcd.print("Gravando Mem....");
  limpaMemoria(); 
 
  int addr = 0;
 
  for(; addr<=out.length(); addr++){
    EEPROM.write(addr, out.charAt(addr));
    if (addr == tamanhoMemoria){
 
      break;
    }
 
 
  }
  EEPROM.write(addr, 35);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("    Gravado!    ");
  beep();
 
 
}
 
 
void limpaMemoria(){
 
  for (int i = 0; i < tamanhoMemoria; i++)
    EEPROM.write(i, 0);
}
 
void beep(){
 
  digitalWrite(saida2, HIGH);
  delay(100);
  digitalWrite(saida2, LOW);
  delay(100);
  digitalWrite(saida2, HIGH);
  delay(100);
  digitalWrite(saida2, LOW);
  delay(100);
  digitalWrite(saida2, HIGH);
  delay(300);
  digitalWrite(saida2, LOW);
  delay(100);
 
  lcd.clear();
  loop();
 
}
 
////////////////////////////////////////////
//void S(){
//
//  ponto();
//  delay(ditTime); 
//  ponto();
//  delay(ditTime); 
//  ponto();
//  delay(ditTime); 
//
//}
//
//
//void O(){
//
//  traco();
//  delay(ditTime); 
//  traco();
//  delay(ditTime); 
//  traco();
//  delay(ditTime); 
//
