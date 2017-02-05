#include <wirish/wirish.h>
#include <libmaple/adc.h>
#include <libmaple/timer.h>

#define LED PB1

void setup() {}
void loop() {
  digitalWrite(LED, LOW);
  delay(125);
  digitalWrite(LED, HIGH);
  delay(125);
}


int main(void) {
    setup();

    while (true) {
        loop();
    }

    return 0;
}
