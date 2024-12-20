#include "screen.h"
#define bool int
#define true 1
#define false 0

void print_char(char character, int col, int row, char attribute_byte) {

	unsigned char *vidmem = (unsigned char*) VIDEO_ADDRESS;

	if (!attribute_byte) {
		attribute_byte = WHITE_ON_BLACK;
	}

	int offset;

	if (col >= 0 && row >= 0) {
		offset = get_screen_offset(col, row);
	} else {
		offset = get_cursor();
	}

	if (character == '\n') {
		int rows = offset / (2*MAX_COLS);
		offset = get_screen_offset(79, rows);
	} else {
		vidmem[offset] = character;
		vidmem[offset+1] = attribute_byte;
	}

	offset+=2;

	offset = handle_scrolling(offset);

	set_cursor(offset);
}

void print_string(char string[]) {
	int i = 0;
	while(string[i]) {
		print_char(string[i], -1, -1, 0);
		i++;
	}
}

void print_line(char string[]) {
	int i = 0;
	while(string[i]) {
		print_char(string[i], -1, -1, 0);
		i++;
	}
	print_char('\n', -1, -1, 0);
}

int get_screen_offset(int col, int row) {
	return (row * 80 + col) * 2;
}

int get_cursor() {
	port_byte_out(REG_SCREEN_CTRL, 14);
	int offset = port_byte_in(REG_SCREEN_DATA) << 8;
	port_byte_out(REG_SCREEN_CTRL, 15);
	offset += port_byte_in(REG_SCREEN_DATA);

	return offset * 2;
}

void set_cursor(int offset) {
	offset /= 2;

	port_byte_out(REG_SCREEN_CTRL, 14);
	port_byte_out(REG_SCREEN_DATA, (unsigned char) (offset >> 8 & 0xFF));
	port_byte_out(REG_SCREEN_CTRL, 15);
	port_byte_out(REG_SCREEN_DATA, (offset & 0xFF));

}

int handle_scrolling(int cursor_offset) {
	if (cursor_offset < MAX_ROWS*MAX_COLS*2) {
		return cursor_offset;
	}

	for (int i=1; i<MAX_ROWS; i++) {
		memory_copy(get_screen_offset(0,i) + VIDEO_ADDRESS, get_screen_offset(0, i-1) + VIDEO_ADDRESS, MAX_COLS*2);
	}

	char* last_line = (char*) get_screen_offset(0,MAX_ROWS-1) + VIDEO_ADDRESS;
	for (int i=0;i<MAX_COLS*2;i++) {
		last_line[i] = 0;
	}

	cursor_offset -= 2* MAX_COLS;

	return cursor_offset;
}

void fill_screen(char color) {
	unsigned char *vidmem = (unsigned char*) VIDEO_ADDRESS;
	color = color | color << 4;
	for (int i=0;i<=MAX_COLS*MAX_ROWS;i++) {
		vidmem[i*2-1] = color;
	}
}

void clear_screen() {
	unsigned char *vidmem = (unsigned char*) VIDEO_ADDRESS;

	for (int i=0;i<=MAX_COLS*MAX_ROWS*2;i++) {
		vidmem[i] = 0;
	}
	set_cursor(0);
}


void print_color_matrix(char **matrix, int x, int y, bool double_layer, int col, int row) {
	if (col >= 0 && row >= 0)
		set_cursor(get_screen_offset(col, row));
	
	for (int i=0;i<x;i++) {
		for (int n=0;n<y;n++) {
			print_char(' ', -1, -1, *((char *)matrix+i*y+n));
			if (double_layer)
				print_char(' ', -1, -1, *((char *)matrix+i*y+n));
		}
		print_char('\n', -1, -1, 0);
	}
}