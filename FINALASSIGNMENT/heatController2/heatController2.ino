const byte RED_1 = 3;
const byte RED_2 = 4;
const byte RED_3 = 5;
const byte BLACK_STRAIGHT = 6;
const byte BLACK_DIAGONAL = 7;

#define BLACK_STRAIGHT_OFF 0
#define BLACK_DIAGONAL_OFF 1
#define RED_1_OFF 2
#define RED_2_OFF 3
#define RED_3_OFF 4
#define BLACK_STRAIGHT_ON 5
#define BLACK_DIAGONAL_ON 6
#define RED_1_ON 7
#define RED_2_ON 8
#define RED_3_ON 9

int R1_pulseWidth = 5;
int R2_pulseWidth = 5;
int R3_pulseWidth = 5;
int BS_pulseWidth = 1;
int BD_pulseWidth = 1;

int timeAtStart;
int timeSinceStart = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(RED_1, OUTPUT);
  pinMode(RED_2, OUTPUT);
  pinMode(RED_3, OUTPUT);
  pinMode(BLACK_STRAIGHT, OUTPUT);
  pinMode(BLACK_DIAGONAL, OUTPUT);

  timeAtStart = millis();

  Serial.begin(9600);
}

void loop() {
  timeSinceStart = millis() - timeAtStart;

  //RED1_control(true);
  //Serial.println(millis() % R1_pulseWidth);

  bs();
  Serial.print(millis() - timeAtStart);

}

void bs(){
Serial.print(" ");
if(millis() - timeAtStart < 10000){
  RED1_control(true);
  //RED2_control(true);
  Serial.println("1");
}
if(millis() - timeAtStart > 10000 && millis() - timeAtStart < 20000){
  RED1_control(true);
  //RED2_control(true);
  BS_control(true);
  Serial.println("2");
}
if(millis() - timeAtStart > 20000 && millis() - timeAtStart < 30000){
  RED1_control(true);
  RED2_control(true);
  BD_control(true);
  Serial.println("3");
}
 if(millis() - timeAtStart > 30000 && millis() - timeAtStart < 40000){
  BS_control(true);
  BD_control(true);
  RED1_control(true);
  RED2_control(true);
  Serial.println("4");
 }
 if(millis() - timeAtStart > 40000 && millis() - timeAtStart < 50000){
  BS_control(true);
  BD_control(true);
  RED1_control(false);
  RED2_control(true);
  Serial.println("5");
 }
 if(millis() - timeAtStart > 50000 && millis() - timeAtStart < 60000){
  BS_control(true);
  BD_control(false);
  RED1_control(false);
  RED2_control(true);
  Serial.println("6");
 }
 if(millis() - timeAtStart > 60000 && millis() - timeAtStart < 70000){
  BS_control(false);
  BD_control(false);
  RED1_control(false);
  RED2_control(true);
  RED3_control(true);
  Serial.println("7");
 }
 if(millis() - timeAtStart > 70000 && millis() - timeAtStart < 80000){
  BS_control(false);
  BD_control(true);
  RED1_control(false);
  RED2_control(false);
  RED3_control(true);
  Serial.println("8");
 }
 if(millis() - timeAtStart > 80000){
  timeAtStart = millis();
  Serial.println("9");
 }
}

void notBS(){
    if(Serial.read() == RED_1_ON){
    RED1_control(true);
  }else if(Serial.read() == RED_1_OFF){
    RED1_control(false);
  }

  if(Serial.read() == RED_2_ON){
    RED2_control(true);
  }else{
    RED2_control(false);
  }

  if(Serial.read() == RED_3_ON){
    RED3_control(true);
  }else{
    RED3_control(false);
  }

  if(Serial.read() == BLACK_STRAIGHT_ON){
    BS_control(true);
  }else if(Serial.read() == BLACK_STRAIGHT_OFF){
    BS_control(false);
  }
  
  if(Serial.read() == BLACK_DIAGONAL_ON){
    BD_control(true);
  }else{
    BD_control(false);
  }
}

void BS_control(boolean on){
  if(on){
    if(millis() % BS_pulseWidth == 0){
      digitalWrite(BLACK_STRAIGHT, HIGH);
    }else{
      digitalWrite(BLACK_STRAIGHT, LOW);
    }
  }
  else{
    digitalWrite(BLACK_STRAIGHT, LOW);
  }
  
}

void BD_control(boolean on){
  if(on){
    if(millis() % BD_pulseWidth == 0){
      digitalWrite(BLACK_DIAGONAL, HIGH);
    }else{
      digitalWrite(BLACK_DIAGONAL, LOW);
    }
  }
  else{
    digitalWrite(BLACK_DIAGONAL, LOW);
  }
}

void RED1_control(boolean on){
  if(on){
    if(millis() % R1_pulseWidth == 0){
      digitalWrite(RED_1, HIGH);
    }else{
      digitalWrite(RED_1, LOW);
    }
  }
  
  if(!on){
    digitalWrite(RED_1, LOW);
  }
}

void RED2_control(boolean on){
  if(on){
    if(millis() % R2_pulseWidth == 0){
      digitalWrite(RED_2, HIGH);
    }else{
      digitalWrite(RED_2, LOW);
    }
  }
  else{
    digitalWrite(RED_2, LOW);
  }
}

void RED3_control(boolean on){
  if(on){
    if(millis() % R3_pulseWidth == 0){
      digitalWrite(RED_3, HIGH);
    }else{
      digitalWrite(RED_3, LOW);
    }
  }
  else{
    digitalWrite(RED_3, LOW);
  }
}

void black(boolean on){
  if(on){
    digitalWrite(BLACK_STRAIGHT, HIGH);
    digitalWrite(BLACK_DIAGONAL, HIGH);
  }else{
    digitalWrite(BLACK_STRAIGHT, LOW);
    digitalWrite(BLACK_DIAGONAL, LOW);
  }
}

void red(boolean on){
  if(on){
    //digitalWrite(RED_1, HIGH);
    digitalWrite(RED_2, HIGH);
    //digitalWrite(RED_3, HIGH);
  }else{
    digitalWrite(RED_1, LOW);
    digitalWrite(RED_2, LOW);
    digitalWrite(RED_3, LOW);
  }
}
void all_control(boolean on){
  if(on){
    digitalWrite(RED_1, HIGH);
    digitalWrite(RED_2, HIGH);
    digitalWrite(RED_3, HIGH);
    digitalWrite(BLACK_STRAIGHT, HIGH);
    digitalWrite(BLACK_DIAGONAL, HIGH);
  }else{
    digitalWrite(RED_1, LOW);
    digitalWrite(RED_2, LOW);
    digitalWrite(RED_3, LOW);
    digitalWrite(BLACK_STRAIGHT, LOW);
    digitalWrite(BLACK_DIAGONAL, LOW);
  }
}
