int ledPin = 2;
int data = 0;
boolean state = false;

void setup() {

  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
}


void loop() {
  data=Serial.parseInt();
  if(data==2){
    state=true;
    Serial.println("ON");
  }else if(data==1){
    state=false;
    Serial.println("OFF");
  }
  if(state){
    digitalWrite(ledPin,LOW);
  }else{
     digitalWrite(ledPin,HIGH);
  }

  //Serial.println(data);
  delay(10);
}



