#include "../drivers/image.h"

int main () {
	
	set_cursor(160);
	print_line("Successfully loaded the kernel.");
	//delay(5);
	print_line("Color test:");
	for (int i=0; i<=0xFF;i++) {
		print_char('X', -1, -1, i);
	}
	set_cursor(1120);
	print_line("Char test:");
	for (int i=0; i<=0xFF;i++) {
		print_char(i, -1, -1, 0);
	}
	//delay(5);
	clear_screen();
	print_line("SUS OS");
	print_color_matrix(amongus, -1, -1);
	return 0;
}