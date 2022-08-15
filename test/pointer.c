#include <stdio.h>

char* printChar(char character, int col, int row) {
		// Create a pointer to a char , and point it to the first text cell of video memory (i.e. the top - left of the screen )
	char *video_memory = (char*) 0xb8000 + 2 * (row*80+col);

	
	return video_memory;
}
int main () {
	printf("%x\n",printChar('X',0,0));
	printf("%x\n",printChar('D',1,0));
	return 0;
}
