unsigned read_pit_count() {
	unsigned count = 0;
 
	// Disable interrupts
	cli();
 
	// al = channel in bits 6 and 7, remaining bits clear
	port_byte_out(0x43,0b0000000);
 
	count = port_byte_in(0x40);		// Low byte
	count |= port_byte_in(0x40)<<8;		// High byte
 
	return count;
}

void delay(int second) {
	for (int i=0;i<second*25;i++) {
		unsigned int t1 = read_pit_count();
		while (t1 != read_pit_count()) {}
	}
}