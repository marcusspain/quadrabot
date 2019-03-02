#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define MIN_PULSE_WIDTH 650
#define MAX_PULSE_WIDTH 2350
#define DEFAULT_PULSE_WIDTH 1500
#define FREQUENCY 50

const int ARMS = 4;
const int JOINTS = 3;
const int REZ = 30;

const int armPorts[ARMS][JOINTS] = {
  { 0, 1, 2 },
  { 3, 4, 5 },
  { 6, 7, 8 },
  { 9, 10, 11 }
};

const int liftFrontRight[ARMS][JOINTS] = {
  { 60, 0, 150 },
  { 125, 40, 30 },
  { 125, 40, 60 },
  { 35, 60, 140 }
};

const int liftFrontLeft[ARMS][JOINTS] = {
  { 55, 140, 150 },
  { 120, 180, 30 },
  { 125, 120, 40 },
  { 55, 140, 120 }
};

const int liftBackRight[ARMS][JOINTS] = {
  { 55, 140, 120 },
  { 125, 120, 40 },
  { 120, 180, 30 },
  { 55, 140, 150 }
};

const int liftBackLeft[ARMS][JOINTS] = {
  { 35, 60, 140 },
  { 125, 40, 60 },
  { 125, 40, 30 },
  { 60, 0, 150 }
};

const int liftBody[ARMS][JOINTS] = {
  { 60, 120, 120 },
  { 120, 60, 60 },
  { 120, 60, 60 },
  { 60, 120, 120 }
};

const int stand[ARMS][JOINTS] = {
  { 15, 60, 120 },
  { 165, 110, 60 },
  { 165, 110, 60 },
  { 15, 60, 120 }
};

void setup()
{
  Serial.begin(57600);

  // Serial.println("awake");
  // Serial.println(convertPointOnRange( 0, stand[0][0], liftFrontLeft[0][0], 0, REZ));
  // Serial.println(convertPointOnRange( 25, stand[0][0], liftFrontLeft[0][0], 0, REZ));
  // Serial.println(convertPointOnRange( 50, stand[0][0], liftFrontLeft[0][0], 0, REZ));
  // Serial.println(convertPointOnRange( 75, stand[0][0], liftFrontLeft[0][0], 0, REZ));
  // Serial.println(convertPointOnRange( 100, stand[0][0], liftFrontLeft[0][0], 0, REZ));


  Serial.println("Quandrabot is Alive!");
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);

  actionAttention();
  delay(2000);
  moveToTargets(liftFrontRight, 20);
  delay(1000);
  moveToTargets(liftFrontLeft, 20);
  delay(1000);
  moveToTargets(liftBackLeft, 20);
  delay(1000);
  moveToTargets(liftBackRight, 20);
  delay(1000);
  moveToTargets(liftBody, 20);
  delay(2000);
  moveToTargets(stand);


//   Serial.println("do the thing");
//
//
//   int splines = new int[ARMS][JOINTS][2];
//   // Serial.println((unsigned int)&splines);
//
//   int testE[2][5] = {
//     { 1000, 1001, 1002, 1003, 1004 },
//     { 2000, 2001, 2002, 2003, 2004 }
//   };
//
//   int *ptr = (unsigned int)&testE;
//
//   Serial.println((unsigned int)&ptr);
//   Serial.println((unsigned int)ptr);
//   Serial.println((unsigned int)&testE);
//   Serial.println((unsigned int)&testE[0][0]);
//   Serial.println(testE[0][0]);
//   Serial.println("-------");
//   for (int a=0; a<2; a++) {
//     for (int i=0; i<5; i++) {
//       Serial.print((unsigned int)&testE[a][i]);
//       Serial.print(":  ");
//       Serial.print(testE[a][i]);
//       Serial.print("\n");
//     }
//     Serial.print("\n");
//   }
//
//   tfunc(testE);
//   // testE[1][2] = 2222;
//
//   Serial.println("-------");
//   for (int a=0; a<2; a++) {
//     for (int i=0; i<5; i++) {
//       Serial.print((unsigned int)&testE[a][i]);
//       Serial.print(":  ");
//       Serial.print(testE[a][i]);
//       Serial.print("\n");
//     }
//     Serial.print("\n");
//   }
//
//   Serial.println("--------------");
//
//   // int **p = new int*[2*5];
//
//   int testF[2][5];
//   Serial.println((unsigned int)&testF);
//   Serial.println((unsigned int)&testF[0]);
//   Serial.println((unsigned int)&testF[0][0]);
//   Serial.println((unsigned int)&testF[0][1]);
//
//   testF[0][0] = new int(3000);
//
//   tfunc(testF);
//
// }
//
// void tfunc( int n[2][5] ) {
//   Serial.println("tfunc");
//   Serial.println((unsigned int)&n);
//   Serial.println(n[0][0]);
//
//   n[1][2] = 2222;
//
//   Serial.println("-------");
//   for (int a=0; a<2; a++) {
//     for (int i=0; i<5; i++) {
//       Serial.print((unsigned int)&n[a][i]);
//       Serial.print(":  ");
//       Serial.print(n[a][i]);
//       Serial.print("\n");
//     }
//     Serial.print("\n");
//   }

  // int frames[ARMS][JOINTS][REZ];
  // Serial.println();
  // Serial.println(sizeof(frames));
  // Serial.println((unsigned int)&frames[0][0][0], HEX);
  //
  // for ( int a=0; a<ARMS; a++ ) {
  //   for ( int j=0; j<JOINTS; j++ ) {
  //     for ( int f=0; f<10; f++ ) {
  //         frames[a][j][f] = 0;
  //     }
  //     Serial.print("\n");
  //   }
  //   Serial.print("\n");
  // }
  // Serial.print("\n");
  //
  // for ( int a=0; a<ARMS; a++ ) {
  //   for ( int j=0; j<JOINTS; j++ ) {
  //     for ( int f=0; f<10; f++ ) {
  //         Serial.print((unsigned int)&frames[a][j][f], HEX);
  //         Serial.print("=");
  //         Serial.print(frames[a][j][f]);
  //         Serial.print(", ");
  //     }
  //     Serial.print("\n");
  //   }
  //   Serial.print("\n");
  // }
  // Serial.print("\n");
  //
  // transformToPosition(frames, stand, liftFrontRight);
  //
  // Serial.println();
  //
  // for ( int a=0; a<ARMS; a++ ) {
  //   for ( int j=0; j<JOINTS; j++ ) {
  //     for ( int f=0; f<10; f++ ) {
  //         Serial.print((unsigned int)&frames[a][j][f], HEX);
  //         Serial.print("=");
  //         Serial.print(frames[a][j][f]);
  //         Serial.print(", ");
  //     }
  //     Serial.print("\n");
  //   }
  //   Serial.print("\n");
  // }
  // Serial.print("\n");

  // Serial.println();
  //
  // int *frames = (int *)malloc(ARMS * JOINTS * REZ * sizeof(int));
  //
  // Serial.print("Size   : ");
  // Serial.println(sizeof(frames));
  // Serial.print("Address: ");
  // Serial.println((unsigned int)&frames, HEX);
  //
  // trans2P(frames,stand,liftFrontLeft);
  //
  // for (int a=0; a<ARMS; a++) {
  //   for (int j=0; j<JOINTS; j++) {
  //     for (int f=0; f<REZ; f++) {
  //       Serial.print((unsigned int)&frames + (a*JOINTS*REZ) + (j*REZ) + f, HEX);
  //       Serial.print("=");
  //       Serial.print(*(frames + (a*JOINTS*REZ) + (j*REZ) + f));
  //       Serial.print(", ");
  //     }
  //     Serial.print("\n");
  //   }
  //   Serial.print("\n");
  // }
  // Serial.print("\n");

}

void trans2P( int s[ARMS*JOINTS*REZ], int startPosition[ARMS][JOINTS], int endPosition[ARMS][JOINTS] ) {
  Serial.println("trans2P!");
  Serial.println((unsigned int)&s, HEX);

  for ( int a=0; a<ARMS; a++ ) {
    for ( int j=0; j<JOINTS; j++ ) {
      for ( int f=0; f<REZ; f++ ) {
          *(s + (a*JOINTS*REZ) + (j*REZ) + f + sizeof(int)) = convertPointOnRange( f, startPosition[a][j], endPosition[a][j], 0, REZ );
          Serial.print((unsigned int)&s + (a*JOINTS*REZ) + (j*REZ) + f + sizeof(int), HEX);
          Serial.print("=");
          Serial.print(*(s + (a*JOINTS*REZ) + (j*REZ) + f + sizeof(int)));
          Serial.print(", ");
      }
      Serial.print("\n");
    }
    Serial.print("\n");
  }
  Serial.print("\n");
  Serial.println("/trans2P");
  Serial.print("\n");
  return;
}

void transformToPosition( int s[ARMS][JOINTS][REZ], int startPosition[ARMS][JOINTS], int endPosition[ARMS][JOINTS] ) {
  Serial.println("transformToPosition!");
  Serial.println((unsigned int)&s, HEX);

  for ( int a=0; a<ARMS; a++ ) {
    for ( int j=0; j<JOINTS; j++ ) {
      for ( int f=0; f<10; f++ ) {
          int v = new int;
          v = convertPointOnRange( f, startPosition[a][j], endPosition[a][j], 0, REZ );
          s[a][j][f] = v;
          Serial.print((unsigned int)&s[a][j][f], HEX);
          Serial.print("=");
          // Serial.print(f);
          // Serial.print(": ");
          // Serial.print(v);
          Serial.print(s[a][j][f]);
          Serial.print(", ");
      }
      Serial.print("\n");
    }
    Serial.print("\n");
  }
  Serial.print("\n");
  Serial.println("/transformToPosition");
  return;
}

int convertPointOnRange( int n, int minR0, int maxR0, int minR1, int maxR1 ) {
  int dR0 = maxR0 - minR0;
  int dR1 = maxR1 - minR1;
  return (((n - minR1) * dR0) / dR1) + minR0;
}



void actionSitBackLeft() {
  int targets[ARMS][JOINTS] = {
    { 15, 60, 120 },
    { 165, 110, 60 },
    { 165, 110, 60 },
    { 15, 60, 120 }
  };
  moveToTargets(targets, 10);
}

void actionWaveArm(int arm) {
  if ((arm < 0) || (arm > ARMS)) {
    Serial.print("ERROR: arm ");
    Serial.print(arm);
    Serial.print(" isn't valid.");
    exit;
  }

  int top = 130;
  int bottom = 0;
  for (int i=bottom; i<top; i++) {
    pwm.setPWM(arm, 0, pulseWidth(i));
    delay(10);
  }

  for (int i=top; i>bottom; i--) {
    pwm.setPWM(arm, 0, pulseWidth(i));
    delay(10);
  }
}

void actionWaveAll() {
  // Drive each PWM in a 'wave'
  for (uint16_t i=0; i<4096; i += 8) {
    for (uint8_t pwmnum=0; pwmnum < 12; pwmnum++ ) {
      Serial.println((i + (4096/12)*pwmnum) % 4096);
//      pwm.setPWM(pwmnum, 0, (i + (4096/16)*pwmnum) % 4096 );
    }
#ifdef ESP8266
    yield();  // take a breather, required for ESP8266
#endif
  }
}

void actionAttention() {
  Serial.println("Attention!");
  int targets[ARMS][JOINTS] = {
    { 15, 60, 120 },
    { 165, 110, 60 },
    { 165, 110, 60 },
    { 15, 60, 120 }
  };
  moveToTargets(targets);
}

void actionAchtung() {
  Serial.println("Achtung!");
  pwm.setPWM(0, 0, pulseWidth(0));
  pwm.setPWM(1, 0, pulseWidth(60));
  pwm.setPWM(2, 0, pulseWidth(120));

  pwm.setPWM(3, 0, pulseWidth(180));
  pwm.setPWM(4, 0, pulseWidth(120));
  pwm.setPWM(5, 0, pulseWidth(60));

  pwm.setPWM(6, 0, pulseWidth(180));
  pwm.setPWM(7, 0, pulseWidth(120));
  pwm.setPWM(8, 0, pulseWidth(60));

  pwm.setPWM(9, 0, pulseWidth(0));
  pwm.setPWM(10, 0, pulseWidth(60));
  pwm.setPWM(11, 0, pulseWidth(120));
}

void actionStomp() {
  Serial.println("Stomp!");
  moveToTargets(liftFrontRight);

  delay(2000);

  moveToTargets(stand);

  // int stand[ARMS][JOINTS] = {
  //   { 0, 40, 120 },
  //   { 165, 110, 60 },
  //   { 165, 110, 60 },
  //   { 15, 60, 120 }
  // };
  // moveToTargets(targets);
  //
  // delay(100);
  //
  // targets[1] = { 165, 130, 60 };
  // moveToTargets(targets);
  //
  // delay(200);
  //
  // targets[1] = { 165, 110, 60 };
  // moveToTargets(targets);
  //
  // delay(100);
  //
  // targets[2] = { 165, 130, 60 };
  // moveToTargets(targets);
  //
  // delay(200);
  //
  // targets[2] = { 165, 110, 60 };
  // moveToTargets(targets);
  //
  // delay(100);
  //
  // targets[3] = { 0, 40, 120 };
  // moveToTargets(targets);
  //
  // delay(200);
  //
  // targets[3] = { 0, 60, 120 };
  // moveToTargets(targets);
}

void actionCreepUp() {
  Serial.println("CreepUp!");
  pwm.setPWM(0, 0, pulseWidth(0));
  pwm.setPWM(1, 0, pulseWidth(60));
  pwm.setPWM(2, 0, pulseWidth(120));

  delay(500);

  pwm.setPWM(3, 0, pulseWidth(180));
  pwm.setPWM(4, 0, pulseWidth(120));
  pwm.setPWM(5, 0, pulseWidth(60));

  delay(500);

  pwm.setPWM(6, 0, pulseWidth(180));
  pwm.setPWM(7, 0, pulseWidth(120));
  pwm.setPWM(8, 0, pulseWidth(60));

  delay(500);

  pwm.setPWM(9, 0, pulseWidth(0));
  pwm.setPWM(10, 0, pulseWidth(60));
  pwm.setPWM(11, 0, pulseWidth(120));
}

void actionPlayDead() {
  Serial.println("PlayDead!");
  int targets[ARMS][JOINTS] = {
    { 120, 120, 120 },
    { 60, 60, 60 },
    { 60, 60, 60 },
    { 120, 120, 120 }
  };
  moveToTargets(targets);
}

void actionBodyUp() {
  Serial.println("BodyUp!");
  int targets[ARMS][JOINTS] = {
    { 60, 120, 120 },
    { 120, 60, 60 },
    { 120, 60, 60 },
    { 60, 120, 120 }
  };
  moveToTargets(targets);
}

void actionSplay() {
  Serial.println("Splay!");
  int targets[ARMS][JOINTS] = {
    { 130, 150, 90 },
    { 50, 30, 90 },
    { 50, 30, 90 },
    { 130, 150, 90 }
  };
  moveToTargets(targets);
}

void moveToTargets(int targets[ARMS][JOINTS], uint8_t ms) {
  // for ( int i=0; i<REZ; i++ ) {
  //   moveToTargets(targets);
  //   delay(ms);
  // }
  moveToTargets(targets);
}

void moveToTargets(int targets[ARMS][JOINTS] ) {
  Serial.println("moveToTargets");
  for ( int x=0; x<ARMS; x++ ) {
    for ( int y=0; y<JOINTS; y++ ) {
      Serial.print(targets[x][y]);
      Serial.print(", ");
    }
    Serial.print("\n");
  }
  Serial.print("\n");

  for ( int arm = 0; arm<ARMS; arm++ ) {
    for ( int joint=0; joint<JOINTS; joint++ ) {
      Serial.print(pulseWidth(targets[arm][joint]));
      Serial.print(", ");
      pwm.setPWM(armPorts[arm][joint], 0, pulseWidth(targets[arm][joint]));
    }
    Serial.print("\n");
  }
  Serial.print("\n");
}

int pulseWidth(int angle)
{
  int pulse_wide, analog_value;
  pulse_wide = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
//  Serial.println(analog_value);
  return analog_value;
}

void loop() {
  handleSerial();
}

void handleSerial() {
 while (Serial.available() > 0) {
   char incomingCharacter = Serial.read();
   switch (incomingCharacter) {
     case 'e':
       moveToTargets(liftFrontRight);
       break;
     case 'q':
      moveToTargets(liftFrontLeft);
      break;
     case 's':
       moveToTargets(stand);
       break;
    }
  }
}
