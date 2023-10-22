#include <stdio.h>

//RED text,black BG
#define CA "160"
#define CB "4"

#define A "\e[38;5;" CA ";48;5;" CB "m"
#define B "\e[38;5;" CB ";48;5;" CA "m"

#define Z "\e[0m"
auto edit_1=A"\n"
"┌────┐\n"
"│" B "h" A "ell│\n"
"│----│\n"
"│CMD-│\n"
"└────┘" Z;

auto edit_2=A"\n"
"┌────┐\n"
"│h" B "e" A "ll│\n"
"│----│\n"
"│CMD-│\n"
"└────┘" Z;

auto edit_3=A"\n"
"┌────┐\n"
"│he" B "l" A "l│\n"
"│----│\n"
"│CMD-│\n"
"└────┘" Z;

auto edit_4=Z A"\n"
"┌────┐\n"
"│" B "h" A "ell│\n"
"│----│\n"
"│CMD-│\n"
"└────┘" Z;

int main(){
    printf("%s\n",edit_4);
}
