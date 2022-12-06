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
int led6;

// set display pins here
// TODO: add display pins

// set input variables
bool option_button_is_pressing = false;
bool option_button_is_long_detected = false;
unsigned long option_button_pressed_time = 0;
int option_button_last_state = LOW;
int option_button_current_state;
bool passed_startup = false;


// set environment variables
int  current_mode = 0;// 0 = free_play, 1 = pattern_game, 2 = timed_game
bool game_in_progress = false;
bool advanced_mode_active;

// TODO: use flash memory to store lifetime stats
int lifetime_nails_hit = 0;

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
    // int button_status = 0;
    // int pin_value = digitalRead(nail1);
    // delay(10);
    // if (button_status != pin_value) {
    //   button_status = pin_value;
    //   Serial.println(button_status);
    // }
    
    // Serial.println(digitalRead(nail2));
    // Serial.println(digitalRead(nail2));
    // Serial.println(digitalRead(nail3));
    // Serial.println(digitalRead(option_button));
    
    // Serial.println('screw2:');
    // Serial.println(analogRead(screw2));
    // Serial.println('screw3:');
    // Serial.println(analogRead(screw3));


    // temporary code to test button press
    if (digitalRead(nail1) == LOW) {
        digitalWrite(led4, HIGH);
    } else {
        digitalWrite(led4, LOW);
    }

    if (digitalRead(nail2) == LOW) {
        digitalWrite(led5, HIGH);
    } else {
        digitalWrite(led5, LOW);
    }



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
                } else {
                    current_mode++;
                }
                Serial.println("Mode changed!");
                Serial.println(current_mode);
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
                break;
            case 2:
                // timed game mode
                break;
        }

}

int free_play() {
    game_in_progress = false;
     
    // turn on simple led when nail is hit
    if (digitalRead(nail1) == LOW) {
            digitalWrite(led4, HIGH);
            lifetime_nails_hit++;
        } else {
            digitalWrite(led4, LOW);
        }

        if (digitalRead(nail2) == LOW) {
            digitalWrite(led5, HIGH);
            lifetime_nails_hit++;
        } else {
            digitalWrite(led5, LOW);
        }

        if (digitalRead(nail3) == LOW) {
            digitalWrite(led6, HIGH);
            lifetime_nails_hit++;
        } else {
            digitalWrite(led6, LOW);
        }

    // change rgb led values based on potentiometer values
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
