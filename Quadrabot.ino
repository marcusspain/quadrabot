#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define MIN_PULSE_WIDTH 650
#define MAX_PULSE_WIDTH 2350
#define DEFAULT_PULSE_WIDTH 1500
#define FREQUENCY 60

const int ARMS = 4;
const int JOINTS = 3;
const int REZ = 50;


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

const int liftFront[ARMS][JOINTS] = {
  { 60, 120, 120 },
  { 120, 60, 60 },
  { 165, 110, 60 },
  { 15, 60, 120 }
};

const int liftBack[ARMS][JOINTS] = {
  { 15, 60, 120 },
  { 165, 110, 60 },
  { 120, 60, 60 },
  { 60, 120, 120 }
};

const int stand[ARMS][JOINTS] = {
  { 15, 60, 120 },
  { 165, 110, 60 },
  { 165, 110, 60 },
  { 15, 60, 120 }
};

const int waveFrontRight0[ARMS][JOINTS] = {
  { 110, 0, 150 },
  { 125, 40, 30 },
  { 125, 40, 60 },
  { 35, 60, 140 }
};

const int waveFrontRight1[ARMS][JOINTS] = {
  { 20, 0, 150 },
  { 125, 40, 30 },
  { 125, 40, 60 },
  { 35, 60, 140 }
};

const int step0[ARMS][JOINTS] = {
  { 60, 90, 160 },
  { 125, 40, 60 },
  { 125, 40, 20 },
  { 35, 60, 140 }
};

const int step1[ARMS][JOINTS] = {
  { 15, 60, 120 },
  { 125, 40, 80 },
  { 125, 40, 10 },
  { 60, 60, 140 }
};

const int stepx[ARMS][JOINTS] = {
  { 80, 90, 150 },
  { 110, 60, 60 },
  { 110, 60, 30 },
  { 50, 80, 150 }
};

int currentStance[ARMS][JOINTS];


void setup()
{
  Serial.begin(115200);

  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);

  Serial.println();
  Serial.println("Alive!");

  initStance(currentStance);
  copyStance(stand, currentStance);
  moveToStance(stand);
  relax();

}

void testB() {
  const int E = 308; // 308 is the highest value that will run.  Highest address is [0B54]2900.
  // const int E = 307; // 307 is the max if varX is defined.
  // const int E = 268; // [0B04]2820
  // const int E = 265; // [0AFE]2814 - moved arr, addr, and arr2 definitions from before buffer to after print &varX.
  // int *varX = new int(0);
  //
  //
  //
  char buffer [100];
  // char buffer2 [100];
  //
  // sprintf(buffer2, "This string starts at [%04X]%d.  varX is at [%04X]%d.\n",
  //                   &buffer2,
  //                   &buffer2,
  //                   &varX,
  //                   &varX);
  // Serial.println(buffer2);

  int * arr = (int *)malloc(E*sizeof(int));
  int addr = &arr;
  int arr2[E];

  for (int i=0; i<E; i++) {
    *(arr + i) = i;
    arr2[i] = i;
  }

  for (int i=0; i<E; i++) {
    if ( i==0 || i==(E-1) ) {
      sprintf( buffer, "Pointers: [%04X]%d *(arr + %d)=%d\t\tIndexed Array: [%04X]%d arr2[%d]=%d\n",
                        &arr + i,
                        &arr + i,
                        i,
                        *(arr + i),
                        &arr2[i],
                        &arr2[i],
                        i,
                        arr2[i]
             );
      Serial.print(buffer);
    }
  }
}

void testC() {
  const int _A_ = 4;
  const int _J_ = 3;
  const int _F_ = 52;
  int frames[_A_][_J_][_F_];

  int count = 0;
  for (int a=0; a<_A_; a++) {
    for (int j=0; j<_J_; j++) {
      for (int f=0; f<_F_; f++) {
        frames[a][j][f] = count++;
        Serial.println((int)&frames[a][j][f]);
      }
    }
  }


  char buffer[100];
  sprintf(buffer, "frames[0][0][0]: [%04X]%d = %d\n",
                  &frames[0][0][0],
                  &frames[0][0][0],
                  frames[0][0][0]);
  Serial.print(buffer);
  sprintf(buffer, "frames[%d][%d][%d]: [%04X]%d = %d\n",
                  _A_-1,
                  _J_-1,
                  _F_-1,
                  &frames[_A_-1][_J_-1][_F_-1],
                  &frames[_A_-1][_J_-1][_F_-1],
                  frames[_A_-1][_J_-1][_F_-1]);
  Serial.print(buffer);
  sprintf(buffer, "buffer: [%04X]%d -- [%04X]%d\n",
                  &buffer,
                  &buffer,
                  &buffer + 100,
                  &buffer + 100);
  Serial.print(buffer);
}

void testD() {
  int frame[ARMS][JOINTS];

  for ( int f=0; f<REZ; f++ ) {
    for ( int a=0; a<ARMS; a++ ) {
      for ( int j=0; j<JOINTS; j++ ) {
        frame[a][j] = convertPointOnRange( f, stand[a][j], liftFrontRight[a][j], 0, REZ );
      }
    }
    moveToStance(frame);
    // delay(5);
  }
}

void performWaveFrontRight() {
  Serial.println("Hello World!");
  transformToStance(liftFrontRight);
  transformToStance(waveFrontRight0);
  transformToStance(waveFrontRight1);
  transformToStance(waveFrontRight0);
  transformToStance(waveFrontRight1);
  delay(500);
  transformToStance(stand);
}

void performStomp() {
  Serial.println("Grrrrrrr!");
  transformToStance(liftFrontRight);
  transformToStance(liftFrontLeft);
  transformToStance(liftBackLeft);
  transformToStance(liftBackRight);
  transformToStance(stand);
}

void performStep0() {
  Serial.print("Here I come!");

}

void transformToStance(int startPosition[ARMS][JOINTS], int endPosition[ARMS][JOINTS], int z) {
  int frame[ARMS][JOINTS];

  for ( int f=0; f<z; f++ ) {
    for ( int a=0; a<ARMS; a++ ) {
      for ( int j=0; j<JOINTS; j++ ) {
        frame[a][j] = convertPointOnRange( f, startPosition[a][j], endPosition[a][j], 0, z );
      }
    }
    moveToStance(frame);
    copyStance(frame, currentStance);
  }
}

void transformToStance(int stance[ARMS][JOINTS], int z) {
  transformToStance(currentStance, stance, z);
}

void transformToStance(int stance[ARMS][JOINTS]) {
  transformToStance(currentStance, stance, REZ);
}

int convertPointOnRange( int n, int minR0, int maxR0, int minR1, int maxR1 ) {
  int dR0 = maxR0 - minR0;
  int dR1 = maxR1 - minR1;
  return (((n - minR1) * dR0) / dR1) + minR0;
}

void moveToStance(int stance[ARMS][JOINTS], uint8_t ms) {
  moveToStance(stance);
}

void moveToStance(int stance[ARMS][JOINTS] ) {
  for ( int arm = 0; arm<ARMS; arm++ ) {
    for ( int joint=0; joint<JOINTS; joint++ ) {
      pwm.setPWM(armPorts[arm][joint], 0, pulseWidth(stance[arm][joint]));
    }
  }
}

void initStance(int stance[ARMS][JOINTS]) {
  for ( int a=0; a<ARMS; a++ ) {
    for ( int j=0; j<JOINTS; j++ ) {
      stance[a][j] = 0;
    }
  }
}

void copyStance(int stanceA[ARMS][JOINTS], int stanceB[ARMS][JOINTS]) {
  for ( int a=0; a<ARMS; a++ ) {
    for ( int j=0; j<JOINTS; j++ ) {
      stanceB[a][j] = stanceA[a][j];
    }
  }
}

void printStance(int stance[ARMS][JOINTS]) {
  for ( int a=0; a<ARMS; a++ ) {
    for ( int j=0; j<JOINTS; j++ ) {
      Serial.print(stance[a][j]);
      if ( j != JOINTS-1 ) {
        Serial.print(", ");
      }
    }
    Serial.print("\n");
  }
}

int pulseWidth(int angle)
{
  int pulse_wide, analog_value;
  pulse_wide = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
//  Serial.println(analog_value);
  return analog_value;
}

void relax() {
  Serial.println("relax");
  for ( int a=0; a<ARMS; a++ ) {
    for ( int j=0; j<JOINTS; j++ ) {
      pwm.setPWM(armPorts[a][j], 0, 4096);
    }
  }
}

void loop() {
  handleSerial();
}

void handleSerial() {
 while (Serial.available() > 0) {
   char incomingCharacter = Serial.read();
   switch (incomingCharacter) {
     case '1':
       transformToStance(liftFrontRight);
       break;
     case '2':
       transformToStance(liftFrontLeft);
       break;
     case '3':
       transformToStance(liftBackLeft);
       break;
     case '4':
       transformToStance(liftBackRight);
       break;
     case '5':
       transformToStance(liftFront);
       break;
     case '6':
       transformToStance(liftBack);
       break;
     case '7':
       transformToStance(liftBody);
       break;
     case '8':
       transformToStance(stand);
       break;
     case '!':
       transformToStance(step0);
       break;
     case '@':
       transformToStance(step1);
       break;
     case '#':
       transformToStance(liftBackLeft);
       break;
     case '$':
       transformToStance(liftBackRight);
       break;
     case '%':
       transformToStance(liftFront);
       break;
     case '^':
       transformToStance(liftBack);
       break;
     case '&':
       transformToStance(stand);
       break;
     case '*':
       transformToStance(stand);
       break;
     case ' ':
       transformToStance(stand);
       delay(500);
       relax();
       break;
     case 's':
       performStomp();
       break;
     case 'w':
       performWaveFrontRight();
       break;
     case 'r':
       relax();
       break;
    }
  }
}
