// these likely aren't necessary
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
    const int SHORT_PRESS_TIME = 500; // 500 milliseconds
    const int LONG_PRESS_TIME = 3000; // 3 seconds
    // TODO: use flash memory to store lifetime stats

    // set lifetime stats
    int lifetime_nails_hit = 0;
    long lifetime_screw_distance = 0;
    int lifetime_pattern_wins = 0;
    int lifetime_pattern_losses = 0;
    long best_time_easy = 9999;
    long best_time_advanced = 9999;

// Arduino setup function
void setup() {
    // set pinmodes
    // use INPUT_PULLUP for buttons
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


// Arduino loop function
void loop() {
    // option button press duration detection
        option_button_current_state = digitalRead(option_button);

        // check if the button state has changed
        if (option_button_last_state == HIGH && option_button_current_state == LOW) {
            // button is currently being pushed
            option_button_pressed_time = millis();
            option_button_is_pressing = true;
            option_button_is_long_detected = false;
        } else if (option_button_last_state == LOW && option_button_current_state == HIGH) {
            // button was just released
            option_button_is_pressing = false;
            // option button short press detection
            if (option_button_is_long_detected == false && passed_startup == true) {
                // button was just released and it was a short press
                // switch modes
                if (!game_in_progress) {
                    // loop back around
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
            // prevent option button from being phantom pressed on startup
            passed_startup = true;
        }

        // option button long press detection
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
        // set variables for next loop
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

// free play mode
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
            // TODO: display message 'nail hit! lifetime nails:'
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
            // TODO: display message 'nail hit! lifetime nails:'
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
            // TODO: display message 'nail hit! lifetime nails:'
        } else if (nail3_last_state == LOW && nail3_current_state == HIGH) {
            // nail was just released
            digitalWrite(led6, LOW);
        }
        nail3_last_state = nail3_current_state;
    
    // change rgb led values based on potentiometer values
        // screw1
        int potentiometer1_value = analogRead(screw1);
        // scale potentiometer value (0-1023) to combined rgb value (0 and 1535)
        int rgb1_value = map(potentiometer1_value, 0, 1023, 0, 1535);
        int rgb1_arr[3];
        // separate combined rgb value into individual rgb values
        rgb_value_separator(rgb1_value, rgb1_arr);
        
        // set led to separated rgb values
        analogWrite(rgb_led1_red, rgb1_arr[0]);
        analogWrite(rgb_led1_green, rgb1_arr[1]);
        analogWrite(rgb_led1_blue, rgb1_arr[2]);
        
        // screw2
        int potentiometer2_value = analogRead(screw2);
        int rgb2_value = map(potentiometer2_value, 0, 1023, 0, 1535);
        int rgb2_arr[3];
        rgb_value_separator(rgb2_value, rgb2_arr);
        
        analogWrite(rgb_led2_red, rgb2_arr[0]);
        analogWrite(rgb_led2_green, rgb2_arr[1]);
        analogWrite(rgb_led2_blue, rgb2_arr[2]);

        // screw3
        int potentiometer3_value = analogRead(screw3);
        int rgb3_value = map(potentiometer3_value, 0, 1023, 0, 1535);
        int rgb3_arr[3];
        rgb_value_separator(rgb3_value, rgb3_arr);
        
        analogWrite(rgb_led3_red, rgb3_arr[0]);
        analogWrite(rgb_led3_green, rgb3_arr[1]);
        analogWrite(rgb_led3_blue, rgb3_arr[2]);
}

// pattern game mode
void pattern_game() {
    game_in_progress = false;

    // count down to game start while allowing mode change
    // (delay() causes mode change to not work)
    unsigned long previous_millis = millis();
    while (digitalRead(option_button) == HIGH && game_in_progress == false) {
        unsigned long current_millis = millis();
        long duration = current_millis - previous_millis;
        // perform actions based on duration
            if (duration > 500 && duration < 1000) {
                analogWrite(rgb_led1_red, 255);
                analogWrite(rgb_led1_green, 0);
                analogWrite(rgb_led1_blue, 0);
            }
            if (duration > 1000 && duration < 1500) {
                analogWrite(rgb_led2_red, 158);
                analogWrite(rgb_led2_green, 208);
                analogWrite(rgb_led2_blue, 10);
            }
            if (duration > 1500 && duration < 2000) {
                analogWrite(rgb_led3_red, 0);
                analogWrite(rgb_led3_green, 255);
                analogWrite(rgb_led3_blue, 0);
            }
            if (duration > 2000 && duration < 2500) {
                all_leds_off();
            }
            if (duration > 2500 && duration < 2750) {
                analogWrite(rgb_led1_red, 255);
                analogWrite(rgb_led1_green, 0);
                analogWrite(rgb_led1_blue, 0);

                analogWrite(rgb_led2_red, 158);
                analogWrite(rgb_led2_green, 208);
                analogWrite(rgb_led2_blue, 10);

                analogWrite(rgb_led3_red, 0);
                analogWrite(rgb_led3_green, 255);
                analogWrite(rgb_led3_blue, 0);

                digitalWrite(led4, HIGH);
                digitalWrite(led5, HIGH);
                digitalWrite(led6, HIGH);
            }
            if (current_millis - previous_millis > 2750) {
                all_leds_off();
                game_in_progress = true;
            }
    }
    // allows mode change
    if (game_in_progress == false) {
        return;
    }
    
    // game start (mode cannot be changed now)
    
    // generate light pattern
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

    // mark the last 3 elements as invalid if not in advanced mode
    // (advanced mode = 6 element long pattern, normal mode = 3 element long pattern)
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
                // generate random rgb values (1-255)
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
                // turn on simple led (nail)
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
    
    // initialize variables
    int current_index = 0;
    int user_pattern[6] = {9, 9, 9, 9, 9, 9};
    int screw1_start_position = analogRead(screw1);
    int screw2_start_position = analogRead(screw2);
    int screw3_start_position = analogRead(screw3);


        // add to user pattern until user pattern is full
        while (current_index < pattern_length) {
            // nails
                // nail1
                nail1_current_state = digitalRead(nail1);
                if (nail1_last_state == HIGH && nail1_current_state == LOW && find(user_pattern, 3) == false) {
                    // nail was just hit and hit was valid
                    digitalWrite(led4, HIGH);
                    lifetime_nails_hit++;
                    user_pattern[current_index] = 3;
                    current_index++;
                }
                nail1_last_state = nail1_current_state;

                // nail2
                nail2_current_state = digitalRead(nail2);
                if (nail2_last_state == HIGH && nail2_current_state == LOW && find(user_pattern, 4) == false) {
                    // nail was just hit and hit was valid
                    digitalWrite(led5, HIGH);
                    lifetime_nails_hit++;
                    user_pattern[current_index] = 4;
                    current_index++;
                }
                nail2_last_state = nail2_current_state;

                // nail3
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
                // screw1
                int screw1_current_position = analogRead(screw1);
                // allow 50 units of error (voltage fluctuation from other wires, box movement, etc.)
                if (!check_range(screw1_current_position, screw1_start_position, 50)) {
                    // run once when screw is moved
                    if (find(user_pattern, 0) == false) {
                        // screw was just moved and move was valid
                        // store screw1 move in user pattern
                        // (records order and prevents logging multiple moves for one screw)
                        user_pattern[current_index] = 0;
                        // increment current index of user_pattern
                        current_index++;
                        // add to lifetime screw distance
                        lifetime_screw_distance += abs(screw1_current_position - screw1_start_position);
                        // set start position to an unreachable value so LED doesn't turn off
                        screw1_start_position = 9999;
                    }
                    // run everytime screw is moved
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
        // after user enters pattern, check if they won
        if (compare_arrays(user_pattern, pattern)) {
            // User wins
            Serial.println("User win");
            // TODO: display this on screen
            lifetime_pattern_wins++;
            // flash all lights green
            flash_green();
        } else {
            // User loses
            Serial.println("User lose");
            lifetime_pattern_losses++;
            // flash rgb leds red
            delay(500);
            flash_red();
        }
    
    // allow user to exit game while displaying results
    previous_millis = millis();
    game_in_progress = false;
    bool sleeping = true;
    while (sleeping) {
        unsigned long current_millis = millis();
        Serial.println(current_millis - previous_millis);
        if (digitalRead(option_button) == LOW) {
            return;
        }
        if (current_millis - previous_millis > 500) {
            all_leds_off();
        }
        if (current_millis - previous_millis > 2000) {
            sleeping = false;
        }
    }
    // pattern game ends, but will be called again if user did not switch modes

    // FIXME: if 6 elements and user gets 3+ wrong that includes screw, it says user losses early
    // TODO: add color specifier to advanced mode (probably not worth it, put it in timed)
}



void timed_game() {
    // randomly select 3 elements, user has to repeat them but order does not matter.
    // Timer tracks how long it takes, rgb lights flash to indicate time range at the end.

    // count down to game start while allowing mode change
    unsigned long previous_millis = millis();
    while (digitalRead(option_button) == HIGH && game_in_progress == false) {
        unsigned long current_millis = millis();
        long duration = current_millis - previous_millis;
        if (duration > 500 && duration < 1000) {
            analogWrite(rgb_led1_red, 255);
            analogWrite(rgb_led1_green, 0);
            analogWrite(rgb_led1_blue, 0);
        }
        if (duration > 1000 && duration < 1500) {
            analogWrite(rgb_led2_red, 158);
            analogWrite(rgb_led2_green, 208);
            analogWrite(rgb_led2_blue, 10);
        }
        if (duration > 1500 && duration < 2000) {
            analogWrite(rgb_led3_red, 0);
            analogWrite(rgb_led3_green, 255);
            analogWrite(rgb_led3_blue, 0);
        }
        if (duration > 2000 && duration < 2500) {
            all_leds_off();
        }
        if (duration > 2500 && duration < 2750) {
            analogWrite(rgb_led1_red, 255);
            analogWrite(rgb_led1_green, 0);
            analogWrite(rgb_led1_blue, 0);

            analogWrite(rgb_led2_red, 158);
            analogWrite(rgb_led2_green, 208);
            analogWrite(rgb_led2_blue, 10);

            analogWrite(rgb_led3_red, 0);
            analogWrite(rgb_led3_green, 255);
            analogWrite(rgb_led3_blue, 0);

            digitalWrite(led4, HIGH);
            digitalWrite(led5, HIGH);
            digitalWrite(led6, HIGH);
        }
        if (current_millis - previous_millis > 2750) {
            all_leds_off();
            game_in_progress = true;
        }
    }
    // catch if user presses button to exit game
    if (game_in_progress == false) {
        return;
    }
    
    // game start (mode cannot be changed now)
    
    // generate pattern (order does not matter in this mode)
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

    // mark last 3 elements as invalid if not in advanced mode
    // advanced mode = 6 element long pattern, normal mode = 3 element long pattern
    int pattern_length = 6;
    if (!advanced_mode_active) {
        pattern[3] = 9;
        pattern[4] = 9;
        pattern[5] = 9;
        pattern_length = 3;
    }

    // initialize random rgb values
        // generate random screw positions
        int random_screw1_position = rand() % 256;
        int random_screw2_position = rand() % 256;
        int random_screw3_position = rand() % 256;

        // convert random screw positions to rgb values
        int rgb1_value = map(random_screw1_position, 0, 1023, 0, 1535);
        int rgb1_arr[3];
        rgb_value_separator(rgb1_value, rgb1_arr);
        
        int rgb2_value = map(random_screw2_position, 0, 1023, 0, 1535);
        int rgb2_arr[3];
        rgb_value_separator(rgb2_value, rgb2_arr);

        int rgb3_value = map(random_screw3_position, 0, 1023, 0, 1535);
        int rgb3_arr[3];
        rgb_value_separator(rgb3_value, rgb3_arr);
        
        // set rgb values
        int random_rgb1_red = rgb1_arr[0];
        int random_rgb1_green = rgb1_arr[1];
        int random_rgb1_blue = rgb1_arr[2];
        int random_rgb2_red = rgb2_arr[0];
        int random_rgb2_green = rgb2_arr[1];
        int random_rgb2_blue = rgb2_arr[2];
        int random_rgb3_red = rgb3_arr[0];
        int random_rgb3_green = rgb3_arr[1];
        int random_rgb3_blue = rgb3_arr[2];


    // display pattern (all at once)
    if (find(pattern, 0)) {
        analogWrite(rgb_led1_red, random_rgb1_red);
        analogWrite(rgb_led1_green, random_rgb1_green);
        analogWrite(rgb_led1_blue, random_rgb1_blue);
    }
    if (find(pattern, 1)) {
        analogWrite(rgb_led2_red, random_rgb2_red);
        analogWrite(rgb_led2_green, random_rgb2_green);
        analogWrite(rgb_led2_blue, random_rgb2_blue);
    }
    if (find(pattern, 2)) {
        analogWrite(rgb_led3_red, random_rgb3_red);
        analogWrite(rgb_led3_green, random_rgb3_green);
        analogWrite(rgb_led3_blue, random_rgb3_blue);
    }
    if (find(pattern, 3)) {
        digitalWrite(led4, HIGH);
    }
    if (find(pattern, 4)) {
        digitalWrite(led5, HIGH);
    }
    if (find(pattern, 5)) {
        digitalWrite(led6, HIGH);
    }

    // user input starts
    // initialize variables
    long timer_start = millis();
    bool success = true;
    int user_pattern[6] = {0, 0, 0, 0, 0, 0};
    int screw1_start_position = analogRead(screw1);
    int screw2_start_position = analogRead(screw2);
    int screw3_start_position = analogRead(screw3);
    
    while (success && sum_array(user_pattern) < pattern_length) {
        // nails
        nail1_current_state = digitalRead(nail1);
        if (nail1_last_state == HIGH && nail1_current_state == LOW) {
            // nail was just hit
            lifetime_nails_hit++;
            if (find(pattern, 3)) {
                // nail was supposed to be hit
                user_pattern[3] = 1;
                digitalWrite(nail1, LOW);
            } else {
                // nail was not supposed to be hit
                success = false;
                flash_red();
                Serial.println("Wrong nail hit!");
            }
        }
        nail1_last_state = nail1_current_state;

        nail2_current_state = digitalRead(nail2);
        if (nail2_last_state == HIGH && nail2_current_state == LOW) {
            // nail was just hit
            lifetime_nails_hit++;
            if (find(pattern, 4)) {
                // nail was supposed to be hit
                user_pattern[4] = 1;
                digitalWrite(nail2, LOW);
            } else {
                // nail was not supposed to be hit
                success = false;
                flash_red();
                Serial.println("Wrong nail hit!");
            }
        }
        nail2_last_state = nail2_current_state;

        nail3_current_state = digitalRead(nail3);
        if (nail3_last_state == HIGH && nail3_current_state == LOW) {
            // nail was just hit
            lifetime_nails_hit++;
            if (find(pattern, 5)) {
                // nail was supposed to be hit
                user_pattern[5] = 1;
                digitalWrite(nail3, LOW);
            } else {
                // nail was not supposed to be hit
                success = false;
                flash_red();
                Serial.println("Wrong nail hit!");
            }
        }
        nail3_last_state = nail3_current_state;

        // screws
        int screw1_current_position = analogRead(screw1);

        // FIXME: code not complete
        if (!check_range(screw1_current_position, screw1_start_position, 50)) {
            // Screw was moved
            if (find(pattern, 0)) {
                // screw was supposed to be moved
                screw1_start_position = 9999;
                if (check_range(screw1_current_position, random_screw1_position, 10)) {
                    // screw was moved to the right position
                    user_pattern[0] = 1;
                    lifetime_screw_distance += abs(screw1_current_position - screw1_start_position);

                }
                
                // TODO: display screw position on LED when moving, target color when not
                
                user_pattern[0] = 1;

                lifetime_screw_distance += abs(screw1_current_position - screw1_start_position);
                screw1_start_position = screw1_current_position;
            } else {
                // screw was not supposed to be moved
                success = false;
                flash_red();
                lifetime_screw_distance += abs(screw1_current_position - screw1_start_position);
                Serial.println("Wrong screw moved!");

            }
            
            
            
            if (find(user_pattern, 0) == false) {
                // screw was just moved and move was valid
                // user_pattern[current_index] = 0;
                // current_index++;
                lifetime_screw_distance += abs(screw1_current_position - screw1_start_position);
                // set start position to an unreachable value so LED doesn't turn off
            }
            // change rgb led values based on potentiometer values
            int rgb1_value = map(screw1_current_position, 0, 1023, 0, 1535);
            int rgb1_arr[3];
            rgb_value_separator(rgb1_value, rgb1_arr);

            analogWrite(rgb_led1_red, rgb1_arr[0]);
            analogWrite(rgb_led1_green, rgb1_arr[1]);
            analogWrite(rgb_led1_blue, rgb1_arr[2]);
        }

    }

    // determine if user won
    if (success) {
        long timer_end = millis();
        long timer_duration = timer_end - timer_start;
        Serial.print("Time: ");
        Serial.println(timer_duration);
        // determine if new best time (based on difficulty)
        if (advanced_mode_active) {
            if (timer_duration < best_time_advanced) {
                best_time_advanced = timer_duration;
                Serial.println("New best time! (advanced)");
                // TODO: "snake" light animation (then flash)
            }
        } else {
            if (timer_duration < best_time_easy) {
                best_time_easy = timer_duration;
                Serial.println("New best time! (easy)");
            }
        }
    }
}






// helper functions

// sum array and return sum
int sum_array(int arr[]) {
    int sum = 0;
    for (int i = 0; i < sizeof(arr); i++) {
        sum += arr[i];
    }
    return sum;
}

// compare two arrays and return true if they are equal
bool compare_arrays(int arr1[], int arr2[]) {
    for (int i = 0; i < 6; i++) {
        Serial.println(arr1[i]);
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}

// custom find function for searching small arrays, returns true if value is in array
bool find(int arr[], int value) {
    for (int i = 0; i < sizeof(arr); i++) {
        if (arr[i] == value) {
            return true;
        }
    }
    return false;
}

// return true if value is within range of center
bool check_range(int value, int center, int range) {
    if (value < center - range || value > center + range) {
        return false;
    }
    return true;
}

// separate rgb value into red, green, and blue values and store in provided array
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

// flash rgb leds to indicate which gamemode was just selected
void indicate_gamemode_change() {
    if (advanced_mode_active) {
        // TODO: display message 'gamemode changed to <gamemode>'
    } else {
        // determine which gamemode was just selected
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

// turn all leds off
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

// flash rgb leds red
void flash_red() {
    all_leds_off();
    delay(500);
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
    delay(500);
    all_leds_off();
}

// flash all leds green
void flash_green() {
    all_leds_off();
    delay(1000);
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
    delay(500);
    all_leds_off();
}