#define BOARD_X_START 6

#define TILE_X_SIZE 4
#define TILE_Y_SIZE 4



byte current_letter = 0;
byte current_attempt = 0;

char current_guess[WORD_SIZE]; 

// B0 B4 B1
// B4    B4
// B2 B1 B3
void setup_board(){
  for(i = 0; i < 6; i++){
    vram_adr(NTADR_A(BOARD_X_START, TILE_Y_SIZE * i + 2));
    for(j = 0; j < WORD_SIZE; j++){
      vram_put(0xB0);
      vram_put(0xB4);
      vram_put(0xB1);
      vram_put(0xB5);
    }
    
    
    vram_adr(NTADR_A(BOARD_X_START, TILE_Y_SIZE * i + 3));
    for(j = 0; j < WORD_SIZE; j++){
      vram_put(0xB4);
      vram_put(0xB4);
      vram_put(0xB4);
      vram_put(0xB5);
    }
    
    vram_adr(NTADR_A(BOARD_X_START, TILE_Y_SIZE * i + 4));
    for(j = 0; j < WORD_SIZE; j++){
      vram_put(0xB2);
      vram_put(0xB4);
      vram_put(0xB3);
      vram_put(0xB5);
    }
  }
}

void check_guess(){
  for(i = 0; i < WORD_SIZE; i++){
    // First, check if the letter is in the right spot
    if(current_guess[i] == current_word[i]){
      vram_adr(0x23C0 + (i));
      vram_put((0 << 6) | (1 << 4) | (1 << 2) | (1 << 0)); // BR, BL, TR, TL
    }
  }
}

void add_letter(char letter){
  if(current_letter < WORD_SIZE){
    //ppu_off();
    vram_adr(NTADR_A(TILE_X_SIZE * current_letter + BOARD_X_START + 1, TILE_Y_SIZE * current_attempt + 3));
    vram_put(letter);
    current_guess[current_letter] = letter;
    current_letter++;
    //ppu_on_all();
  }
  else{
    check_guess();
  }
}

void remove_letter(){
  if(current_letter > 0){
    ppu_off();
    current_letter--;
    vram_adr(NTADR_A(TILE_X_SIZE * current_letter + BOARD_X_START + 1, TILE_Y_SIZE * current_attempt + 3));
    vram_put(0xb4);
    ppu_on_all();
  }
}

