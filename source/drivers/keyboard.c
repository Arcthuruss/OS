#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_COMMAND_REGISTER 0x64
#define KEYBOARD_STATUS_REGISTER 0x64
#define CONTROL_PORT_MASTER_PIC 0x20
/*
char get_key() {
    char key = port_byte_in(KEYBOARD_DATA_PORT);
    port_byte_out(CONTROL_PORT_MASTER_PIC, 0x20);
    return key;
}
void kb_send_command(char command, char second_command) {
    int output_buffer;
    int status;
    do {
        status = port_byte_in(KEYBOARD_STATUS_REGISTER);
    } while (status & 0x1);
}*/