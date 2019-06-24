#include "inc/lm4f120h5qr.h"

/* Port F'nin (3 renk LED ve 2 button) ayarlarini yapar. */

void init_port_F() {
	volatile unsigned long tmp; // bu degisken gecikme yapmak icin gerekli
	SYSCTL_RCGCGPIO_R |= 0x00000020; // 1) activate clock for Port F
	tmp = SYSCTL_RCGCGPIO_R; // allow time for clock to start
	GPIO_PORTF_LOCK_R = 0x4C4F434B; // 2) unlock GPIO Port F
	GPIO_PORTF_CR_R = 0x1F; // allow changes to PF4-0
	// only PF0 needs to be unlocked, other bits can't be locked
	GPIO_PORTF_AMSEL_R = 0x00; // 3) disable analog on PF
	GPIO_PORTF_PCTL_R = 0x00000000; // 4) PCTL GPIO on PF4-0
	GPIO_PORTF_DIR_R = 0x0E; // 5) PF4,PF0 in, PF3-1 out
	GPIO_PORTF_AFSEL_R = 0x00; // 6) disable alt funct on PF7-0
	GPIO_PORTF_PUR_R = 0x11; // enable pull-up on PF0 and PF4
	GPIO_PORTF_DEN_R = 0x1F; // 7) enable digital I/O on PF4-0
}
int main(void) {
	init_port_F();
	int button_sag, button_sol;
	while (1) {
		// buttonun degerini oku, degiskene degerini ata
		button_sag = GPIO_PORTF_DATA_R & 0b00001;
		// buttonun degerini oku, degiskene degerini ata
		button_sol = GPIO_PORTF_DATA_R & 0b10000;


		// kirmizi ledi yak
		if (button_sag == 0) {
			GPIO_PORTF_DATA_R |= 0b01010;
			// button basili degilse, kirimzi ledi sondur
		} else {
			GPIO_PORTF_DATA_R &= ~(0b01010);
		}

		// mavi ledi yak
		if (button_sol == 0) {
			GPIO_PORTF_DATA_R |= 0b01100;
			// button basili degilse mavi ledi sondur
		} else {
			GPIO_PORTF_DATA_R &= ~(0b01100);
		}
	}
}
