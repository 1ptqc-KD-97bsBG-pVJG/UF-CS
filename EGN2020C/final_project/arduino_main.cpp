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
int led1 = 11;
int led2 = 12;
int led3 = 13;

// set display pins here


// set input variables
bool option_button_pressed = false;
int option_button_last_state = LOW;
int option_button_current_state;


// set environment variables
int current_mode = 0; // 0 = free_play, 1 = pattern_game, 2 = timed_game
bool game_in_progress = false;
bool advanced_mode_active = false;

const int SHORT_PRESS_TIME = 500; // 500 milliseconds

// set 

void setup() {
    Serial.begin(9600);
    pinMode(option_button, INPUT_PULLUP)
}


void loop() {
    option_button_current_state = digitalRead(option_button);

    // handle option button press (short and long presses)
    if (option_button_last_state == HIGH && option_button_current_state == LOW) { // button was just pressed
        pressed_time = millis();
    } else if (option_button_last_state == LOW && option_button_current_state == HIGH) { // button was just released
        released_time = millis();

        long press_duration = released_time - pressed_time;
        
        if (press_duration < SHORT_PRESS_TIME) { // short press
            // switch modes
            if (!game_in_progress) {
                if (current_mode == 2) {
                    current_mode = 0;
                } else {
                    current_mode++;
                }
                // activate current mode
                switch (current_mode) {
                    case 0:
                        // free play mode
                        break;
                    case 1:
                        // pattern game mode
                        break;
                    case 2:
                        // timed game mode
                        break;
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


}

