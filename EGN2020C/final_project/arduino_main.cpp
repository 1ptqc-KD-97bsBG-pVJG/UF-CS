// declare variables

// consider changing these ints to bytes to save memory and / or moving to a .h file
// define inputs
int nail1 = 2;
int nail2 = 3;
int nail3 = 4;

int screw1 = 5;
int screw2 = 6;
int screw3 = 7;

int option_button = 8;

// define outputs
int rgb_led1_red;
int rgb_led1_green;
int rgb_led1_blue;
int led2 = 12;
int led3 = 13;
int led4;
int led5;
int led6;

// set display pins here


// set input variables
bool option_button_pressed = false;
int option_button_last_state = LOW;
int option_button_current_state;


// set environment variables
int  current_mode = 0;// 0 = free_play, 1 = pattern_game, 2 = timed_game
bool game_in_progress = false;
bool advanced_mode_active;

// TODO: use flash memory to store lifetime stats
int lifetime_nails_hit = 0;

const int SHORT_PRESS_TIME = 500; // 500 milliseconds

// set 

void setup() {
    pinMode(nail1, INPUT_PULLUP);
    pinMode(nail2, INPUT_PULLUP);
    pinMode(nail3, INPUT_PULLUP);

    pinMode(screw1, INPUT);
    pinMode(screw2, INPUT);
    pinMode(screw3, INPUT);

    pinMode(rgb_led1_red, OUTPUT);
    pinMode(rgb_led1_green, OUTPUT);
    pinMode(rgb_led1_blue, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
    pinMode(led5, OUTPUT);
    pinMode(led6, OUTPUT);

    pinMode(option_button, INPUT_PULLUP);
    
    current_mode = 0;   // set to free play mode on start
    Serial.begin(9600);
}


void loop() {
    option_button_current_state = digitalRead(option_button);

    // handle option button press (short and long presses)
    if (option_button_last_state == HIGH && option_button_current_state == LOW) { // button was just pressed
        long pressed_time = millis();
    } else if (option_button_last_state == LOW && option_button_current_state == HIGH) { // button was just released
        long released_time = millis();

        long press_duration = released_time - pressed_time;
        
        if (press_duration < SHORT_PRESS_TIME) { // short press
            // switch modes
            if (!game_in_progress) {
                if (current_mode == 2) {
                    current_mode = 0;
                } else {
                    current_mode++;
                }
            } else {
                // TODO: display error message 'can't change modes while game in progress!'
            }
        } else { // long press
            // toggle advanced mode
            advanced_mode_active = !advanced_mode_active;
            // TODO: display message 'advanced mode on' or 'advanced mode off'
        }
    }

    // activate current mode
        switch (current_mode) {
            case 0:
                // free play mode
                free_play();
                break;
            case 1:
                // pattern game mode
                break;
            case 2:
                // timed game mode
                break;
        }

}

int free_play() {
    game_in_progress = false;

    // set values for rgb leds based on potentiometers values 
    int potentiometer1_value = analogRead(screw1);
    int rgb1_value = map(potentiometer1_value, 0, 1023, 0, 1535);
    int arr[3];
    rgb_value_separator(rgb1_value, arr);
    
    analogWrite(rgb_led1_red, arr[0]);
    analog_Write(rgb_led1_green, arr[1]);
    analog_Write(rgb_led1_blue, arr[2]);
     
    
    
    // turn on led when nail is hit
    if (digitalRead(nail1) == HIGH) {
        digitalWrite(led1, HIGH);
        lifetime_nails_hit++;
    } else {
        digitalWrite(led1, LOW);
    }

    if (digitalRead(nail2) == HIGH) {
        digitalWrite(led2, HIGH);
        lifetime_nails_hit++;
    } else {
        digitalWrite(led2, LOW);
    }

    if (digitalRead(nail3) == HIGH) {
        digitalWrite(led3, HIGH);
        lifetime_nails_hit++;
    } else {
        digitalWrite(led3, LOW);
    }
}


void rgb_value_separator(int rgb_value, int arr[]) {
    int red;
    int green;
    int blue;

    if (rgb_value < 256) {
        red = 255;
        blue = rgb_value;
        green = 0;
    } else if (rgb_value < 512) {
        red = 511 - rgb_value;
        blue = 255;
        green = 0;
    } else if (rgb_value < 768) {
        red = 0;
        blue = 255;
        green = rgb_value - 512;
    } else if (rgb_value < 1024) {
        red = 0;
        blue = 1023 - rgb_value;
        green = 255;
    } else if (rgb_value < 1280) {
        red = rgb_value - 1024;
        blue = 0;
        green = 255;
    } else {
        red = 255;
        blue = 0;
        green = 1535 - rgb_value;
    }

    arr[0] = red;
    arr[1] = blue;
    arr[2] = green;
}
