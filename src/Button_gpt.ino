// This #include statement was automatically added by the Particle IDE.
#include <InternetButton.h>

int Color = 100;
InternetButton b = InternetButton();
bool TEXTO = false;

void setup() {
    b.begin();
    Particle.function("SMSfrom", SMS);
    Particle.function("clear", ClearRainbow);
    Serial.begin(9600);
    while (!Serial.available() && millis() < 5000) {
        delay(1000);
    }
}

void loop() {
    if (!TEXTO) {
        b.allLedsOff();
    } else {
        switch (Color) {
            case 0: {
                b.rainbow(5);
                break;
            }
            case 1: {
                spin(255, 0, 0, 1);
                b.wheel(200);
                break;
            }
            case 2: {
                spin(0, 0, 255, 1);
                b.wheel(20);
                break;
            }
            case 3: {
                spin(0, 255, 0, 1);
                b.wheel(20);
                break;
            }
        }
    }

    if (b.buttonOn(2)) {
        TEXTO = false;
        Particle.publish("button2", NULL, 60, PRIVATE);
    } else if (b.buttonOn(3)) {
        spin(25, 50, 120, 30);
        Particle.publish("button3", NULL, 60, PRIVATE);
    } else if (b.buttonOn(4)) {
        TEXTO = true;
        Particle.publish("button4", NULL, 60, PRIVATE);
    }
}

void spin(uint8_t rouge, uint8_t vert, uint8_t bleu, uint8_t attend) {
  uint16_t i, j;
  uint8_t rougediv, vertdiv, bleudiv;
     rougediv = rouge / 11;
     vertdiv = vert / 11;
     bleudiv = bleu / 11;
     for(i=0; i<25; i++) { // numbers of shadding of the colors 
       for(j=0; j< 13; j++) {
       //     b.allLedsOff();
            b.ledOn(i, max(0,rouge), max(0,vert), max(0,bleu));
			b.ledOn((i-1)%12, max(0,rouge-rougediv*2), max(0,vert-vertdiv*2), max(0,bleu-bleudiv*2));
			b.ledOn((i-2)%12, max(0,rouge-rougediv*3), max(0,vert-vertdiv*3), max(0,bleu-bleudiv*3));
			b.ledOn((i-3)%12, max(0,rouge-rougediv*4), max(0,vert-vertdiv*4), max(0,bleu-bleudiv*4));
			b.ledOn((i-4)%12, max(0,rouge-rougediv*5), max(0,vert-vertdiv*5), max(0,bleu-bleudiv*5));
			b.ledOn((i-5)%12, max(0,rouge-rougediv*6), max(0,vert-vertdiv*6), max(0,bleu-bleudiv*6));
			b.ledOn((i-6)%12, max(0,rouge-rougediv*7), max(0,vert-vertdiv*7), max(0,bleu-bleudiv*7));
			b.ledOn((i-7)%12, max(0,rouge-rougediv*8), max(0,vert-vertdiv*8), max(0,bleu-bleudiv*8));
			b.ledOn((i-8)%12, max(0,rouge-rougediv*9), max(0,vert-vertdiv*9), max(0,bleu-bleudiv*9));
			b.ledOn((i-9)%12, max(0,rouge-rougediv*10), max(0,vert-vertdiv*10), max(0,bleu-bleudiv*10));
		    b.ledOn((i-10)%12, 0, 0, 0);
		//  b.ledOn((i-10)%12, max(0,rouge-rougediv*11), max(0,vert-vertdiv*11), max(0,bleu-bleudiv*11));
		//	b.ledOn((i-11)%12, max(0,rouge-rougediv*12), max(0,vert-vertdiv*12), max(0,bleu-bleudiv*12));
            delay(attend);
       }
    }
}

int ClearRainbow(String clear) {
    if (clear == "on") {
        TEXTO = false;
        Particle.publish(clear, NULL, 60, PRIVATE);
        return 1;
    } else {
        Particle.publish(clear, NULL, 60, PRIVATE);
        return -1;
    }
}

int SMS(String command) {
    if (command == "rainbow)") {
        TEXTO = true;
        Color = 0;
        Serial.println("rainbow");
        Particle.publish(command, NULL, 60, PRIVATE);
        return 1;
    } else if (command == "red)") {
        TEXTO = true;
        Color = 1;
        Serial.println("red");
        Particle.publish(command, NULL, 60, PRIVATE);
        return 1;
    } else if (command == "blue)") {
        TEXTO = true;
        Color = 2;
        Serial.println("blue");
        Particle.publish(command, NULL, 60, PRIVATE);
        return 1;
    } else if (command == "green)") {
        TEXTO = true;
        Color = 3;
        Serial.println("green");
        Particle.publish(command, NULL, 60, PRIVATE);
        return 1;
    } else {
        Serial.println("notok");
        Serial.println(command);
        Particle.publish(command, NULL, 60, PRIVATE);
        return -1;
    }
}
