#define Brick0_HIGH 1030
#define Brick0_LOW 1009

#define Brick1_HIGH 999
#define Brick1_LOW 960

#define Brick2_HIGH 450
#define Brick2_LOW 400

#define Brick3_HIGH 300
#define Brick3_LOW 220

#define Brick4_HIGH 155
#define Brick4_LOW 130

#define Brick5_HIGH 50
#define Brick5_LOW 15

char* passo[25];
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
    
    String word = "";
    
    word += "[";
    for(int i = 14; i <= 19;i++){
        word += traduzir(i);
   		word += ",";
    }
    
    /*Muda A Linha */
    digitalWrite(lin1, LOW);
    digitalWrite(lin2, HIGH);
    
    for(int i = 14; i <= 18;i++){
        word += traduzir(i);
   		word += ",";
    }
    
    word += traduzir(A5);
    word += "]";

    /* Imprimi o que tem dentro da Array */
    Serial.println(word);
    

    delay(100);
    
    buttonLast = buttonNow;  
    
    /*Seta para Zero as Linhas*/
    digitalWrite(lin1, LOW);
  	digitalWrite(lin2, LOW);
  }

}

/* Os case sao os valores das resistencias */
char* traduzir(int pin){
   int resistencia = analogRead(pin);
  
   //Serial.println("RES: ");
   //Serial.println(resistencia);
   delay(100);
  
   if (resistencia > Brick0_LOW && resistencia < Brick0_HIGH){
     return "0";
   }else if(resistencia > Brick1_LOW && resistencia < Brick1_HIGH){
     return "1";
   }else if(resistencia > Brick2_LOW && resistencia < Brick2_HIGH){
     return "2";
   }else if(resistencia > Brick3_LOW && resistencia < Brick3_HIGH){
     return "5";
   }else if(resistencia > Brick4_LOW && resistencia < Brick4_HIGH){
     return "3";
   }else if(resistencia > Brick5_LOW && resistencia < Brick5_HIGH){
     return "4";
   }else{
   		return "-1";
   }
}
