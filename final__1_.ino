#define ADC 0
#define Echo 3
#define Trig 4
#define PWMLED 5
#define water1 6
#define water2 7
#define Button_Pin 8
unsigned long distance;
int adc = 0;
int pwm = 0;
int button_state = 0;
bool water1_status = false, water2_status = false;

unsigned long measure(int echoPin, int trigPin) {
  unsigned long duration, mm;
  digitalWrite(Trig, LOW);
  delayMicroseconds(5);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  pinMode(Echo, INPUT);
  duration = pulseIn(Echo, HIGH);
  mm = duration / 2 / 2.88;
  return mm;
}

void setup() {
  Serial.begin(9600);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(PWMLED, OUTPUT);
  pinMode(water1, OUTPUT);
  pinMode(water2, OUTPUT);
  pinMode(Button_Pin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); 
}

void loop() {

  if (Serial.available()) { 
    digitalWrite(LED_BUILTIN, HIGH);
    String input = Serial.readStringUntil("\n");
    pwm = input.substring(0, input.indexOf(',')).toInt();
    water1_status = input.substring(input.indexOf(',') + 1, input.lastIndexOf(';')).toInt();
    water2_status = input.substring(input.lastIndexOf(',') + 1).toInt();
  } else {  
    digitalWrite(LED_BUILTIN, LOW); 
  }
  analogWrite(PWMLED, pwm);
  digitalWrite(water1, water1_status);
  digitalWrite(water2, water2_status);

  adc = analogRead(ADC);
  adc = map(adc, 0, 1023, 0, 250);
  button_state = digitalRead(Button_Pin);
  distance = measure(Echo, Trig);
  String output = String(adc) + ";" + String(distance) + ";" + String(button_state);
  Serial.println(output);
  delay(500);
}
