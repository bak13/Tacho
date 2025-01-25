//inputs
const int left_button = 2;
const int right_button = 4;
const int res = A1;
//outputs
const int en_motion = 5;
const int to_left = 7;
const int to_right = 8;
// initial values
int buttonLeft = 0;
int buttonRight = 0;

int res_value = 0;
int rotation_speed = 0;

int pwm4stop = 191;

void setup() {
  // put your setup code here, to run once:
  pinMode(left_button, INPUT);
  pinMode(right_button, INPUT);

  pinMode(en_motion, OUTPUT);
  pinMode(to_left, OUTPUT);
  pinMode(to_right, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  res_value = analogRead(res);
  rotation_speed = map(res_value, 0, 1023, 32, 255);

  buttonLeft = digitalRead(left_button);
  buttonRight = digitalRead(right_button);

  if (buttonLeft == HIGH && buttonRight == LOW) {
    // move motor to left:
    rotate(HIGH, LOW, rotation_speed);
  } else if(buttonLeft == LOW && buttonRight == HIGH) {
    // move motor to right:
    rotate(LOW, HIGH, rotation_speed);
  } else {
    rotation_stop(pwm4stop);
  }
}

void rotate(int left, int right, int pwm){
  analogWrite(en_motion, pwm);
  digitalWrite(to_left, left);
  digitalWrite(to_right, right);
}

void rotation_stop(int pwm){
  analogWrite(en_motion, pwm);
  digitalWrite(to_left, LOW);
  digitalWrite(to_right, LOW);
}
