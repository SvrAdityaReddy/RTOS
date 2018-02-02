void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT); // to act as interrupt for rpi 2b
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(2, HIGH);                       
  digitalWrite(3, HIGH);        
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  delay(2000);
  digitalWrite(6, LOW); 
  delay(2000);     
}
