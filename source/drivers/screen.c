#include "screen.h"

void print_char(char character, int col, int row, char attribute_byte) {

	char expect;

	int expect2;
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