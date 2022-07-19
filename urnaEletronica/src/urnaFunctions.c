#include "urnaFunctions.h"
#include <atmel_start.h>
#include <hal_gpio.h>
#include "gfx_mono_main.h"
#include "gfx_mono_font_basic_6x7.h"


void printCandidatos(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	// Candidates to print
	const uint8_t [spongeBob] = "1 - Sponge Bob Square Pants";
	const uint8_t [patrickStar] = "2 - Patrick Red Star";
	const uint8_t [squidwardTentacles] "3 - Squidward Tentacles";
	
	// Enable SPI and OLED
	spi_m_sync_enable(&DISPLAY_SPI);
	gfx_mono_init();
	
	// Draw the candidates
	gfx_mono_text_draw_string(&MONOCHROME_TEXT_desc, spongeBob, 0, 0, &basic_6x7);
	gfx_mono_text_draw_string(&MONOCHROME_TEXT_desc, patrickStar, 10, 0, &basic_6x7);
	gfx_mono_text_draw_string(&MONOCHROME_TEXT_desc, squidwardTentacles, 20, 0, &basic_6x7);

}