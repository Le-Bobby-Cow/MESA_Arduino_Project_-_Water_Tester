#define LED_RATE 100000

// We'll use timer 2
HardwareTimer timer(2);
boolean writen = false;

void setup() {
    pinMode(PC13, OUTPUT);
    // Pause the timer while we're configuring it
    timer.pause();

    // Set up period
    timer.setPeriod(LED_RATE); // in microseconds

    // Set up an interrupt on channel 1
    timer.setChannel1Mode(TIMER_OUTPUT_COMPARE);
    timer.setCompare(TIMER_CH1, 1);  // Interrupt 1 count after each update
    timer.attachCompare1Interrupt(handler_led);

    // Refresh the timer's count, prescale, and overflow
    timer.refresh();

    // Start the timer counting
    timer.resume();
}

void loop() {
    // Nothing! It's all in the handler_led() interrupt:
}

void handler_led() {
    if(writen) {
      digitalWrite(PC13, HIGH);
    } else {
      digitalWrite(PC13, LOW);
    }
    writen = !writen; 
}
