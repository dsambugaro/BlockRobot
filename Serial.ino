#define Brick0_HIGH 1030
#define Brick0_LOW 1009

#define Brick1_HIGH 999
#define Brick1_LOW	960

#define Brick2_HIGH 450
#define Brick2_LOW 400

#define Brick3_HIGH 300
#define Brick3_LOW 220

#define Brick4_HIGH 155
#define Brick4_LOW 130

#define Brick5_HIGH 50
#define Brick5_LOW 15

byte passo[12];
byte modulos = 12;

int buttonLast = 0;
int buttonNow = 1;

int lin1 = 8;
int lin2 = 9;

void setup(){
  Serial.begin(9600);
  attachInterrupt(0, captura, CHANGE);

  pinMode(lin1, OUTPUT);
  pinMode(lin2, OUTPUT);
  digitalWrite(lin1, LOW);
  digitalWrite(lin2, LOW);
  
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);  
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
   
}

void loop(){
  
  buttonNow = 1;
  buttonLast = 0;
  delay(100);
}

/* Aonde insere no vetor */
void captura(){
  
  if(buttonNow != buttonLast){ 

    /*Muda a Linha*/
    digitalWrite(lin1, HIGH);
    digitalWrite(lin2, LOW);
    
    passo[0] = traduzir(A0);
    passo[1] = traduzir(A1);
    passo[2] = traduzir(A2);
    passo[3] = traduzir(A3);
    passo[4] = traduzir(A4);
    passo[5] = traduzir(A5);
    
    /*Muda A Linha */
    digitalWrite(lin1, LOW);
    digitalWrite(lin2, HIGH);
    
    passo[6] = traduzir(A0);
    passo[7] = traduzir(A1);
    passo[8] = traduzir(A2);
    passo[9] = traduzir(A3);
    passo[10] = traduzir(A4);
    passo[11] = traduzir(A5);
    
    
    imprimi(passo);
    delay(5000);
    
    buttonLast = buttonNow;  
    
    /*Seta para Zero as Linhas*/
    digitalWrite(lin1, LOW);
  	digitalWrite(lin2, LOW);
  }

}

/* Os case sao os valores das resistencias */
int traduzir(int pin){
   int resistencia = analogRead(pin);
  
   Serial.println("VALOR RESISTENCIA: ");
   Serial.println(resistencia);
   delay(100);
  
   if (resistencia > Brick0_LOW && resistencia < Brick0_HIGH){
     return 0;
   }else if(resistencia > Brick1_LOW && resistencia < Brick1_HIGH){
     return 1;
   }else if(resistencia > Brick2_LOW && resistencia < Brick2_HIGH){
     return 2;
   }else if(resistencia > Brick3_LOW && resistencia < Brick3_HIGH){
     return 5;
   }else if(resistencia > Brick4_LOW && resistencia < Brick4_HIGH){
     return 3;
   }else if(resistencia > Brick5_LOW && resistencia < Brick5_HIGH){
     return 4;
   }else{
   		return -1;
   }
}

/* Imprimi o que tem dentro da Array */
void imprimi(byte* p){
  int i = 0;
  for(i = 0; i < modulos;i++){
		Serial.print(p[i]);
        	if( i != (modulos-1))
            	Serial.print(",");
	 }
	Serial.println(" ");
}
