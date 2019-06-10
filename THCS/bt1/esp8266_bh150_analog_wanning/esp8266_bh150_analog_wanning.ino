int cambien = A0;// khai báo chân digital 4 cho cảm biến
#define MUC0 100
#define MUC1 400
#define MUC2 650
#define MUC3 850
#define MUC4 1024
int LedPin[] = {D3, D4, D5, D6};
void setup (){
  pinMode(cambien,INPUT);//pinMode nhận tín hiệu đầu vào cho cảm biến
  Serial.begin(115200);
  Serial.println(F("BH1750 Test begin"));

  for (int i = 0; i < 4; i++) {
    pinMode(LedPin[i], OUTPUT);
    digitalWrite(LedPin[i], LOW);
  }
}

void loop (){
   int value = analogRead(cambien); 
   Serial.print("Light: ");
   Serial.println(value);//xuất giá trị 
   delay(1000);

   if (MUC0 >= value){ // value <= 100
      for (int i = 0; i < 4; i++)
         digitalWrite(LedPin[i], LOW);
      delay(1000);
   }
   if (MUC0 < value && value < MUC1) 
     digitalWrite(D3, HIGH);
   if (MUC1 < value && value < MUC2) 
     digitalWrite(D4, HIGH);
   if (MUC2 < value && value < MUC3)
     digitalWrite(D5, HIGH);
   if (MUC3 < value && value < MUC4) 
     digitalWrite(D6, HIGH); 
   if (value >= MUC4) {
      for (int i = 0; i < 5; i++)
         digitalWrite(LedPin[i], HIGH);
      delay(1000);
      for (int i = 0; i < 5; i++)
         digitalWrite(LedPin[i], LOW);
      delay(1000);
   }
}
