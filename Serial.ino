String caractere;
int valor = 0;
int passo[6];
int interruptPin = 2;
int buttonLast = 0;
int buttonNow = 1;

void setup(){
  Serial.begin(9600);
  delay(1000);
  attachInterrupt(0, captura, CHANGE);
   
  pinMode(2, INPUT);
  pinMode(9, OUTPUT);
  
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);  
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
   
}

void loop(){
  Serial.println("Nop! ");
  buttonNow = 1;
  buttonLast = 0;
  delay(1000);
}

void captura(){
  
  if(buttonNow != buttonLast){
    
    passo[0] = traduzir(A0);
    passo[1] = traduzir(A1);
    passo[2] = traduzir(A2);
    passo[3] = traduzir(A3);
    passo[4] = traduzir(A4);
    passo[5] = traduzir(A5);
    
    imprimi(passo);
    tone(9, 100, 500);
    delay(2);
    
    buttonLast = buttonNow;  
  }

}

/* Os case sao os valores das resistencias */
int traduzir(int pin){
   int resistencia = analogRead(pin);
   Serial.println("VALOR RESISTENCIA: ");
   Serial.println(resistencia);
   delay(1000);
   if (resistencia > 1009 && resistencia < 1030){
     return 0;
   }else if(resistencia > 960 && resistencia < 999){
     return 1;
   }else if(resistencia > 600 && resistencia < 620){
     return 2;
   }else if(resistencia > 220 && resistencia < 235){
     return 5;
   }else if(resistencia > 130 && resistencia < 155){
     return 3;
   }else if(resistencia > 15 && resistencia < 50){
     return 4;
   }else{
       return -1;
    }
}

/* Imprimi oque tem dentro da Array */
void imprimi(int* p){
  Serial.println("Valores: ");
   int i = 0;
  for(i = 0; i < 6;i++){
                Serial.print("Vetor[");
                Serial.print(i);
                Serial.print("] = ");
		Serial.print(p[i]);
                Serial.println(" ");
	 }
}
