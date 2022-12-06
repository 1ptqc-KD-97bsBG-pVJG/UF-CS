#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// declare variables

// consider changing these ints to bytes to save memory and / or moving to a .h file
// define inputs
int nail1 = 22;
int nail2 = 24;
int nail3 = 26;

int option_button = 23;

int screw1 = A13;
int screw2 = A14;
int screw3 = A15;


// define outputs
int rgb_led1_red = 2;
int rgb_led1_green = 3;
int rgb_led1_blue = 4;

int rgb_led2_red = 5;
int rgb_led2_green = 6;
int rgb_led2_blue = 7;

int rgb_led3_red = 8;
int rgb_led3_green = 9;
int rgb_led3_blue = 10;

int led4 = 34;
int led5 = 35;
int led6 = 36;

// set display pins here
// TODO: add display pins

// set internal tracking variables
    // option button (short & long press detection)
    bool option_button_is_pressing = false;
    bool option_button_is_long_detected = false;
    unsigned long option_button_pressed_time = 0;
    int option_button_last_state = LOW;
    int option_button_current_state;
    bool passed_startup = false;
    
    // nails (short press detection)
    int nail1_last_state = HIGH;
    int nail1_current_state;
    int nail2_last_state = HIGH;
    int nail2_current_state;
    int nail3_last_state = HIGH;
    int nail3_current_state;


// set environment variables
int  current_mode = 0;// 0 = free_play, 1 = pattern_game, 2 = timed_game
bool game_in_progress = false;
bool advanced_mode_active;

// TODO: use flash memory to store lifetime stats
int lifetime_nails_hit = 0;
long lifetime_screw_distance = 0;
int lifetime_pattern_wins = 0;
int lifetime_pattern_losses = 0;

const int SHORT_PRESS_TIME = 500; // 500 milliseconds
const int LONG_PRESS_TIME = 3000; // 3 seconds

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
    
    pinMode(rgb_led2_red, OUTPUT);
    pinMode(rgb_led2_green, OUTPUT);
    pinMode(rgb_led2_blue, OUTPUT);
   
    pinMode(rgb_led3_red, OUTPUT);
    pinMode(rgb_led3_green, OUTPUT);
    pinMode(rgb_led3_blue, OUTPUT);


    pinMode(led4, OUTPUT);
    pinMode(led5, OUTPUT);
    pinMode(led6, OUTPUT);

    pinMode(option_button, INPUT_PULLUP);
    
    current_mode = 0;   // set to free play mode on start
    Serial.begin(9600);
}


void loop() {

    option_button_current_state = digitalRead(option_button);

    if (option_button_last_state == HIGH && option_button_current_state == LOW) {
        // button is currently being pushed
        option_button_pressed_time = millis();
        option_button_is_pressing = true;
        option_button_is_long_detected = false;
    } else if (option_button_last_state == LOW && option_button_current_state == HIGH) {
        // button was just released
        option_button_is_pressing = false;
        if (option_button_is_long_detected == false && passed_startup == true) {
            // button was just released and it was a short press
            // switch modes
            if (!game_in_progress) {
                if (current_mode == 2) {
                    current_mode = 0;
                    indicate_gamemode_change();
                } else {
                    current_mode++;
                    indicate_gamemode_change();
                }
            } else {
                // TODO: display error message 'can't change modes while game in progress!'
                Serial.println("Can't change modes while game in progress!");
            }
        }
        passed_startup = true;
    }

    if (option_button_is_pressing == true && option_button_is_long_detected == false) {
        long press_duration = millis() - option_button_pressed_time;

        if (press_duration > LONG_PRESS_TIME) {
            // long press detected
            option_button_is_long_detected = true;
            // toggle advanced mode
            advanced_mode_active = !advanced_mode_active;
            
            if (advanced_mode_active == true) {
                Serial.println("Advanced mode on!");
            } else {
                Serial.println("Advanced mode off!");
            }
            // TODO: display message 'advanced mode on' or 'advanced mode off'
        }
    }
    option_button_last_state = option_button_current_state;

    // activate current mode
        switch (current_mode) {
            case 0:
                // free play mode
                free_play();
                break;
            case 1:
                // pattern game mode
                pattern_game();
                break;
            case 2:
                // timed game mode
                timed_game();
                break;
        }

}

int free_play() {
    game_in_progress = false;
     
    // turn on simple led when nail is hit
        // nail 1
        nail1_current_state = digitalRead(nail1);
        if (nail1_last_state == HIGH && nail1_current_state == LOW) {
            // nail was just hit
            digitalWrite(led4, HIGH);
            lifetime_nails_hit++;
            Serial.println("Total nails hit:");
            Serial.println(lifetime_nails_hit);
        } else if (nail1_last_state == LOW && nail1_current_state == HIGH) {
            // nail was just released
            digitalWrite(led4, LOW);
        }
        nail1_last_state = nail1_current_state;

        // nail 2
        nail2_current_state = digitalRead(nail2);
        if (nail2_last_state == HIGH && nail2_current_state == LOW) {
            // nail was just hit
            digitalWrite(led5, HIGH);
            lifetime_nails_hit++;
            Serial.println("Total nails hit:");
            Serial.println(lifetime_nails_hit);
        } else if (nail2_last_state == LOW && nail2_current_state == HIGH) {
            // nail was just released
            digitalWrite(led5, LOW);
        }
        nail2_last_state = nail2_current_state;

        // nail 3
        nail3_current_state = digitalRead(nail3);
        if (nail3_last_state == HIGH && nail3_current_state == LOW) {
            // nail was just hit
            digitalWrite(led6, HIGH);
            lifetime_nails_hit++;
            Serial.println("Total nails hit:");
            Serial.println(lifetime_nails_hit);
        } else if (nail3_last_state == LOW && nail3_current_state == HIGH) {
            // nail was just released
            digitalWrite(led6, LOW);
        }
        nail3_last_state = nail3_current_state;
    
    // change rgb led values based on potentiometer values
    int potentiometer1_value = analogRead(screw1);
    int rgb1_value = map(potentiometer1_value, 0, 1023, 0, 1535);
    int rgb1_arr[3];
    rgb_value_separator(rgb1_value, rgb1_arr);
    
    analogWrite(rgb_led1_red, rgb1_arr[0]);
    analogWrite(rgb_led1_green, rgb1_arr[1]);
    analogWrite(rgb_led1_blue, rgb1_arr[2]);
    
    int potentiometer2_value = analogRead(screw2);
    int rgb2_value = map(potentiometer2_value, 0, 1023, 0, 1535);
    int rgb2_arr[3];
    rgb_value_separator(rgb2_value, rgb2_arr);
    
    analogWrite(rgb_led2_red, rgb2_arr[0]);
    analogWrite(rgb_led2_green, rgb2_arr[1]);
    analogWrite(rgb_led2_blue, rgb2_arr[2]);

    int potentiometer3_value = analogRead(screw3);
    int rgb3_value = map(potentiometer3_value, 0, 1023, 0, 1535);
    int rgb3_arr[3];
    rgb_value_separator(rgb3_value, rgb3_arr);
    
    analogWrite(rgb_led3_red, rgb3_arr[0]);
    analogWrite(rgb_led3_green, rgb3_arr[1]);
    analogWrite(rgb_led3_blue, rgb3_arr[2]);

}


void pattern_game() {
    game_in_progress = false;

    // count down to game start while allowing mode change
    unsigned long previous_millis = millis();
    while (digitalRead(option_button) == HIGH && game_in_progress == false) {
        unsigned long current_millis = millis();
        if (current_millis - previous_millis > 500) {
            analogWrite(rgb_led1_red, 255);
            analogWrite(rgb_led1_green, 0);
            analogWrite(rgb_led1_blue, 0);
        }
        if (current_millis - previous_millis > 1000) {
            analogWrite(rgb_led2_red, 158);
            analogWrite(rgb_led2_green, 208);
            analogWrite(rgb_led2_blue, 10);
        }
        if (current_millis - previous_millis > 1500) {
            analogWrite(rgb_led3_red, 0);
            analogWrite(rgb_led3_green, 255);
            analogWrite(rgb_led3_blue, 0);
        }
        if (current_millis - previous_millis > 2000) {
            // turn all off and trigger game start
            analogWrite(rgb_led1_red, 0);
            analogWrite(rgb_led1_green, 0);
            analogWrite(rgb_led1_blue, 0);
            analogWrite(rgb_led2_red, 0);
            analogWrite(rgb_led2_green, 0);
            analogWrite(rgb_led2_blue, 0);
            analogWrite(rgb_led3_red, 0);
            analogWrite(rgb_led3_green, 0);
            analogWrite(rgb_led3_blue, 0);
        }
        if (current_millis - previous_millis > 2500) {
            analogWrite(rgb_led1_red, 255);

            analogWrite(rgb_led2_red, 158);
            analogWrite(rgb_led2_green, 208);
            analogWrite(rgb_led2_blue, 10);

            analogWrite(rgb_led3_green, 255);

            digitalWrite(led4, HIGH);
            digitalWrite(led5, HIGH);
            digitalWrite(led6, HIGH);
        }
        if (current_millis - previous_millis > 2750) {
            analogWrite(rgb_led1_red, 0);
            analogWrite(rgb_led2_red, 0);
            analogWrite(rgb_led2_green, 0);
            analogWrite(rgb_led2_blue, 0);
            analogWrite(rgb_led3_green, 0);
            digitalWrite(led4, LOW);
            digitalWrite(led5, LOW);
            digitalWrite(led6, LOW);
            game_in_progress = true;
        }
    }
    if (game_in_progress == false) {
        return;
    }
    
    // game start (mode cannot be changed now)
    
    // generate pattern
    int i;
    int pattern[6];
    for (i = 0; i < 6; i++) {
        pattern[i] = i;
    }

    // randomize pattern
    const int pattern_size = sizeof(pattern) / sizeof(pattern[0]);
    for (i = 0; i < pattern_size; i++) {
        int random_index = rand() % pattern_size;
        int temp = pattern[random_index];
        pattern[random_index] = pattern[i];
        pattern[i] = temp;
    }

    // initialize random rgb values
    int random_rgb1_red;
    int random_rgb1_green;
    int random_rgb1_blue;
    int random_rgb2_red;
    int random_rgb2_green;
    int random_rgb2_blue;
    int random_rgb3_red;
    int random_rgb3_green;
    int random_rgb3_blue;

    // mark last 3 elements as invalid if not in advanced mode
    // advanced mode = 6 element long pattern, normal mode = 3 element long pattern
    int pattern_length = 6;
    if (!advanced_mode_active) {
        pattern[3] = 9;
        pattern[4] = 9;
        pattern[5] = 9;
        pattern_length = 3;
    }
    
    // display pattern
    delay(1000);
    for (i = 0; i < pattern_length; i++) {
        switch (pattern[i]) {
            // pattern: 0 = screw1, 1 = screw2, 2 = screw3, 
            //          3 = nail1, 4 = nail2, 5 = nail3, 9 = invalid
            case 0:
                random_rgb1_red = rand() % 254 + 1;
                random_rgb1_green = rand() % 254 + 1;
                random_rgb1_blue = rand() % 254 + 1;
                analogWrite(rgb_led1_red, random_rgb1_red);
                analogWrite(rgb_led1_green, random_rgb1_green);
                analogWrite(rgb_led1_blue, random_rgb1_blue);
                break;
            case 1:
                random_rgb2_red = rand() % 254 + 1;
                random_rgb2_green = rand() % 254 + 1;
                random_rgb2_blue = rand() % 254 + 1;
                analogWrite(rgb_led2_red, random_rgb2_red);
                analogWrite(rgb_led2_green, random_rgb2_green);
                analogWrite(rgb_led2_blue, random_rgb2_blue);
                break;
            case 2:
                random_rgb3_red = rand() % 254 + 1;
                random_rgb3_green = rand() % 254 + 1;
                random_rgb3_blue = rand() % 254 + 1;
                analogWrite(rgb_led3_red, random_rgb3_red);
                analogWrite(rgb_led3_green, random_rgb3_green);
                analogWrite(rgb_led3_blue, random_rgb3_blue);
                break;
            case 3:
                digitalWrite(led4, HIGH);
                break;
            case 4:
                digitalWrite(led5, HIGH);
                break;
            case 5:
                digitalWrite(led6, HIGH);
                break;
            default:
                break;
        }
        delay(2000);
    }

    // reset all leds
    all_leds_off();

    // user turn to repeat pattern
    int current_index = 0;
    int user_pattern[6] = {9, 9, 9, 9, 9, 9};
    int screw1_start_position = analogRead(screw1);
    int screw2_start_position = analogRead(screw2);
    int screw3_start_position = analogRead(screw3);


    Serial.println("pattern_length");
    Serial.println(pattern_length);
    // print user_pattern
    for (int i = 0; i < sizeof(user_pattern) / sizeof(user_pattern[0]); i++) {
        delay(100);
        Serial.print(user_pattern[i]);
    }
    Serial.println("=======");

        while (current_index < pattern_length) {
            // nails
            nail1_current_state = digitalRead(nail1);
            if (nail1_last_state == HIGH && nail1_current_state == LOW && find(user_pattern, 3) == false) {
                // nail was just hit and hit was valid
                digitalWrite(led4, HIGH);
                lifetime_nails_hit++;
                user_pattern[current_index] = 3;
                current_index++;
            }
            nail1_last_state = nail1_current_state;

            nail2_current_state = digitalRead(nail2);
            if (nail2_last_state == HIGH && nail2_current_state == LOW && find(user_pattern, 4) == false) {
                // nail was just hit and hit was valid
                digitalWrite(led5, HIGH);
                lifetime_nails_hit++;
                user_pattern[current_index] = 4;
                current_index++;
            }
            nail2_last_state = nail2_current_state;

            nail3_current_state = digitalRead(nail3);
            if (nail3_last_state == HIGH && nail3_current_state == LOW && find(user_pattern, 5) == false) {
                // nail was just hit and hit was valid
                digitalWrite(led6, HIGH);
                lifetime_nails_hit++;
                user_pattern[current_index] = 5;
                current_index++;
            }
            nail3_last_state = nail3_current_state;

            // screws
            int screw1_current_position = analogRead(screw1);

            if (!check_range(screw1_current_position, screw1_start_position, 50)) {
                if (find(user_pattern, 0) == false) {
                    // screw was just moved and move was valid
                    user_pattern[current_index] = 0;
                    current_index++;
                    lifetime_screw_distance += abs(screw1_current_position - screw1_start_position);
                    // set start position to an unreachable value so LED doesn't turn off
                    screw1_start_position = 9999;
                }
                // change rgb led values based on potentiometer values
                int rgb1_value = map(screw1_current_position, 0, 1023, 0, 1535);
                int rgb1_arr[3];
                rgb_value_separator(rgb1_value, rgb1_arr);

                analogWrite(rgb_led1_red, rgb1_arr[0]);
                analogWrite(rgb_led1_green, rgb1_arr[1]);
                analogWrite(rgb_led1_blue, rgb1_arr[2]);
            }

            int screw2_current_position = analogRead(screw2);

            if (!check_range(screw2_current_position, screw2_start_position, 50)) {
                if (find(user_pattern, 1) == false) {
                    // screw was just moved and move was valid
                    user_pattern[current_index] = 1;
                    current_index++;
                    lifetime_screw_distance += abs(screw2_current_position - screw2_start_position);
                    // set start position to an unreachable value so LED doesn't turn off
                    screw2_start_position = 9999;
                }
                // change rgb led values based on potentiometer values
                int rgb2_value = map(screw2_current_position, 0, 1023, 0, 1535);
                int rgb2_arr[3];
                rgb_value_separator(rgb2_value, rgb2_arr);

                analogWrite(rgb_led2_red, rgb2_arr[0]);
                analogWrite(rgb_led2_green, rgb2_arr[1]);
                analogWrite(rgb_led2_blue, rgb2_arr[2]);
            }

            int screw3_current_position = analogRead(screw3);

            if (!check_range(screw3_current_position, screw3_start_position, 50)) {
                if (find(user_pattern, 2) == false) {
                    // screw was just moved and move was valid
                    user_pattern[current_index] = 2;
                    current_index++;
                    lifetime_screw_distance += abs(screw3_current_position - screw3_start_position);
                    // set start position to an unreachable value so LED doesn't turn off
                    screw3_start_position = 9999;
                }
                // change rgb led values based on potentiometer values
                int rgb3_value = map(screw3_current_position, 0, 1023, 0, 1535);
                int rgb3_arr[3];
                rgb_value_separator(rgb3_value, rgb3_arr);

                analogWrite(rgb_led3_red, rgb3_arr[0]);
                analogWrite(rgb_led3_green, rgb3_arr[1]);
                analogWrite(rgb_led3_blue, rgb3_arr[2]);
            }
        }

        delay(1000);
        all_leds_off();
        delay(1000);

        // check if user_pattern is correct
        if (compare_arrays(user_pattern, pattern)) {
            // User wins
            Serial.println("User win");
            lifetime_pattern_wins++;
            // flash all lights green
            analogWrite(rgb_led1_red, 0);
            analogWrite(rgb_led1_green, 255);
            analogWrite(rgb_led1_blue, 0);
            analogWrite(rgb_led2_red, 0);
            analogWrite(rgb_led2_green, 255);
            analogWrite(rgb_led2_blue, 0);
            analogWrite(rgb_led3_red, 0);
            analogWrite(rgb_led3_green, 255);
            analogWrite(rgb_led3_blue, 0);
            digitalWrite(led4, HIGH);
            digitalWrite(led5, HIGH);
            digitalWrite(led6, HIGH);

        } else {
            // User loses
            Serial.println("User lose");
            lifetime_pattern_losses++;
            // flash rgb leds red
            analogWrite(rgb_led1_red, 255);
            analogWrite(rgb_led1_green, 0);
            analogWrite(rgb_led1_blue, 0);
            analogWrite(rgb_led2_red, 255);
            analogWrite(rgb_led2_green, 0);
            analogWrite(rgb_led2_blue, 0);
            analogWrite(rgb_led3_red, 255);
            analogWrite(rgb_led3_green, 0);
            analogWrite(rgb_led3_blue, 0);
            digitalWrite(led4, LOW);
            digitalWrite(led5, LOW);
            digitalWrite(led6, LOW);
        }
    
    delay(500);
    all_leds_off();
    delay(1500);

    // FIXME: if 6 elements and user gets 3+ wrong that includes screw, it says user losses early
    // TODO: add color specifier to advanced mode
}




void timed_game() {

}


bool compare_arrays(int arr1[], int arr2[]) {
    for (int i = 0; i < 6; i++) {
        Serial.println(arr1[i]);
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}

// custom find function for searching small arrays
bool find(int arr[], int value) {
    for (int i = 0; i < sizeof(arr); i++) {
        if (arr[i] == value) {
            return true;
        }
    }
    return false;
}

bool check_range(int value, int center, int range) {
    if (value < center - range || value > center + range) {
        return false;
    }
    return true;
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

void indicate_gamemode_change() {
    if (advanced_mode_active) {
        // TODO: display message 'gamemode changed to <gamemode>'
    } else {
        Serial.println("Flashing rgb leds to indicate gamemode change");
        Serial.println("Gamemode to flash:");
        Serial.println(current_mode);
        switch (current_mode) {
            case 0:
                Serial.println("Free play mode");
                // free play mode
                    // flash rgb leds purple
                        // set to off
                        all_leds_off();
                        delay(100);

                        // set all to purple
                        analogWrite(rgb_led1_red, 186);
                        analogWrite(rgb_led1_green, 85);
                        analogWrite(rgb_led1_blue, 211);
                        
                        analogWrite(rgb_led2_red, 186);
                        analogWrite(rgb_led2_green, 85);
                        analogWrite(rgb_led2_blue, 211);

                        analogWrite(rgb_led3_red, 186);
                        analogWrite(rgb_led3_green, 85);
                        analogWrite(rgb_led3_blue, 211);
                        delay(500);

                        // set all to off
                        all_leds_off();
                        delay(300);

                        return;

            case 1:
                Serial.println("Pattern game mode");
                // pattern game mode
                    // flash rgb leds blue
                        // set all to off
                        all_leds_off();
                        delay(100);

                        // set all to blue
                        analogWrite(rgb_led1_red, 0);
                        analogWrite(rgb_led1_green, 0);
                        analogWrite(rgb_led1_blue, 255);

                        analogWrite(rgb_led2_red, 0);
                        analogWrite(rgb_led2_green, 0);
                        analogWrite(rgb_led2_blue, 255);

                        analogWrite(rgb_led3_red, 0);
                        analogWrite(rgb_led3_green, 0);
                        analogWrite(rgb_led3_blue, 255);
                        delay(500);

                        // set all to off
                        all_leds_off();
                        delay(100);

                        return;

            case 2:
                Serial.println("Timed game mode");
                // timed game mode
                    // flash rgb leds red
                        // set all to off
                        all_leds_off();
                        delay(100);

                        // set all to red
                        analogWrite(rgb_led1_red, 255);
                        analogWrite(rgb_led1_green, 0);
                        analogWrite(rgb_led1_blue, 0);

                        analogWrite(rgb_led2_red, 255);
                        analogWrite(rgb_led2_green, 0);
                        analogWrite(rgb_led2_blue, 0);

                        analogWrite(rgb_led3_red, 255);
                        analogWrite(rgb_led3_green, 0);
                        analogWrite(rgb_led3_blue, 0);
                        delay(500);

                        // set all to off
                        all_leds_off();
                        delay(100);
                            

                        return;

        }           
    }
}

void all_leds_off() {
        analogWrite(rgb_led1_red, 0);
        analogWrite(rgb_led1_green, 0);
        analogWrite(rgb_led1_blue, 0);
        analogWrite(rgb_led2_red, 0);
        analogWrite(rgb_led2_green, 0);
        analogWrite(rgb_led2_blue, 0);
        analogWrite(rgb_led3_red, 0);
        analogWrite(rgb_led3_green, 0);
        analogWrite(rgb_led3_blue, 0);
        digitalWrite(led4, LOW);
        digitalWrite(led5, LOW);
        digitalWrite(led6, LOW);
}