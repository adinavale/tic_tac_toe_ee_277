//--------------------------------------------------------
// Application demonstrator: SNAKE game
//--------------------------------------------------------


#include "EDK_CM0.h" 
#include "core_cm0.h"
#include "edk_driver.h"
#include "edk_api.h"

#include <stdio.h>						

//Game region
#define left_boundary 5
#define right_boundary 96
#define top_boundary 5
#define bottom_boundary 116
#define boundary_thick 1

//Global variables
static int i,j;
static char key;
static int score1;
static int score2;
static int row;
static int col;

//---------------------------------------------
// Game
//---------------------------------------------
	
void Game_Init(void)
{	
	//Draw a game region
	clear_screen();
	
	//Initialise data	
	score1 = 0;
	score2 = 0;
	
	//Print instructions on text console of VGA
	printf("\n----- Tic Tac Toe Game -----");
	printf("\n---  Get three in a row ----");
	
	//First horizontal line
	for(col = 5; col < 96; col++){
		VGA_plot_pixel(col, 40, WHITE);
	}

	//Second horizontal line
	for(col = 5; col < 96; col++){
		VGA_plot_pixel(col, 80, WHITE);
	}

	//Left vertical line
	for(row = 5; row < 116; row++){
		VGA_plot_pixel(33, row, WHITE);
	}

	//Right vertical line
	for(row = 5; row < 116; row++){
		VGA_plot_pixel(66, row, WHITE);
	}

	while(KBHIT()==0); //wait till keyboard press is detected
		
	NVIC_EnableIRQ(Timer_IRQn);//start timing
	NVIC_EnableIRQ(UART_IRQn);	
}

void Game_Close(void)
{
	clear_screen();
	
	// Reset scores to 0
	score1 = 0;
	score2 = 0;
	
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");//flush screen
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	
	NVIC_DisableIRQ(Timer_IRQn);			
	NVIC_DisableIRQ(UART_IRQn);	
}
	
int GameOver(void)
{
	char key;
	
	NVIC_DisableIRQ(UART_IRQn);
	NVIC_DisableIRQ(Timer_IRQn);
	
	printf("\nGAME OVER !!!\n");
	printf("\nPress 'q' to quit");
	printf("\nPress 'r' to replay\n");
	
	while(1)
		{
			while(KBHIT()==0);
		
			key = UartGetc();
			
			if (key == RESET)
				return 1;
			
			else if (key == QUIT)
				return 0;
			
			else
				printf("\nInvalid Input! Try Again!");
		}		
}


//---------------------------------------------
// UART ISR -- used to input commands
//---------------------------------------------
void UART_ISR(void)
{	

	key=UartGetc();	
}
//---------------------------------------------
// Main Function
//---------------------------------------------
int main(void){

	//Initialise the system
	SoC_init();
	//Initialise the game
	Game_Init();
	
	//Go to sleep mode and wait for interrupts
	while(1)
		__WFI();	
}


