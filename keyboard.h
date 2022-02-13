byte prev_gamepad = 0;
byte gamepad = 0;

void keyboard_update(){
  gamepad = pad_poll(0);
  
  if(gamepad&PAD_A && !prev_gamepad&PAD_A){
    add_letter('A');
  }
  
  if(gamepad&PAD_B && !prev_gamepad&PAD_B){
    remove_letter();
  }
  
  prev_gamepad = gamepad;
}