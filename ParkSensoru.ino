const int trigPin = 9;
const int echoPin = 10;

const int buzzerPin = 7;
bool buzzerAktif = false;

const int buton = 6;
int prev_state = HIGH;

const int startButon = 5;
int prev_start = HIGH;
bool start = false;

const int LED = 4;

// int notalar[] = {261, 293, 329, 349, 392, 440, 493, 523};
//               $   do  re   mi   fa   sol  la   si   do
long duration;
int distance;

const int numReadings = 10;
int readings[numReadings];      
int index = 0;                  
int total = 0;                  
int averageDistance = 0;        

void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(LED, OUTPUT);
    pinMode(buzzerPin, OUTPUT);
    pinMode(buton, INPUT_PULLUP);
    pinMode(startButon, INPUT_PULLUP);
    Serial.begin(9600);
}

void loop() {
    int startState = digitalRead(startButon);

    if(startState != prev_start){
        prev_start = startState;
        if (startState == LOW)
        {
          start = !start;
        }
        Serial.println("Butona basıldı.");
      }

    if(start){

    int state = digitalRead(buton);
    distance = getDistance();

    if(state != prev_state){
        prev_state = state;
        if (state == LOW)
        {
          buzzerAktif = !buzzerAktif;
        }
        Serial.println("Butona basıldı.");
      }

    if (distance >= 400 || distance <= 1) 
    {
      Serial.println("Menzil dışı!");
    }
    else 
    {
      total = total - readings[index];        
      readings[index] = distance;             
      total = total + readings[index];        
      index = (index + 1) % numReadings;      
      averageDistance = total / numReadings;  
      
      Serial.print("Uzaklık: ");
      Serial.println(averageDistance);
      
      if(averageDistance > 300 && averageDistance < 400){
        if (buzzerAktif)
        {
          tone(buzzerPin, 261);
          digitalWrite(LED, LOW);
          delay(200);
          digitalWrite(LED, HIGH);
          noTone(buzzerPin);
          delay(20);
        }
      }
      else if (averageDistance > 250 && averageDistance < 300)
      {
        if (buzzerAktif)
        {
          tone(buzzerPin, 293);
          digitalWrite(LED, LOW);
          delay(175);
          digitalWrite(LED, HIGH);
          noTone(buzzerPin);
          delay(20);
        }
      }
      else if (averageDistance > 200 && averageDistance < 250)
      {
        if (buzzerAktif)
        {
          tone(buzzerPin, 329);
          digitalWrite(LED, LOW);
          delay(150);
          digitalWrite(LED, HIGH);
          noTone(buzzerPin);
          delay(20);
        }
      }
      else if (averageDistance > 150 && averageDistance < 200)
      {
        if (buzzerAktif)
        {
          tone(buzzerPin, 349);
          digitalWrite(LED, LOW);
          delay(125);
          digitalWrite(LED, HIGH);
          noTone(buzzerPin);
          delay(20);
        }
      }
      else if (averageDistance > 100 && averageDistance < 150)
      {
        if (buzzerAktif)
        {
          tone(buzzerPin, 392);
          digitalWrite(LED, LOW);
          delay(100);
          digitalWrite(LED, HIGH);
          noTone(buzzerPin);
          delay(20);
        }
      }
      else if (averageDistance > 50 && averageDistance < 100)
      {
        if (buzzerAktif)
        {
          tone(buzzerPin, 440);
          digitalWrite(LED, LOW);
          delay(75);
          digitalWrite(LED, HIGH);
          noTone(buzzerPin);
          delay(20);
        }
      }
      else if (averageDistance > 25 && averageDistance < 50)
      {
        if (buzzerAktif)
        {
          tone(buzzerPin, 493);
          digitalWrite(LED, LOW);
          delay(50);
          digitalWrite(LED, HIGH);
          noTone(buzzerPin);
          delay(20);
        }
      }
      else if(averageDistance < 25)
      {
        if (buzzerAktif)
        {
          tone(buzzerPin, 523);
          digitalWrite(LED, LOW);
          delay(25);
          digitalWrite(LED, HIGH);
          noTone(buzzerPin);
          delay(20);
        }
      }
      else
      {
        Serial.println("Buzzer aktif değil!");
        noTone(buzzerPin); 
      }
    }
    }
    else{
      Serial.println("Start butonuna basınız.");
      delay(2000);
    }

    digitalWrite(LED, LOW);
    delay(50);
}

int getDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.0343 / 2;
  return distance;
}