void setup() {
  // put your setup code here, to run once:
  pinMode(2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
  digitalWrite(2,1);
  delay(100);
  digitalWrite(2,0);
}
