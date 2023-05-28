#include "uart.h"

/***
 * Ex E6.0
 *
 * Your task is to write code which handles a sequence of input characters
 * from the UART interface, and respond with the output specified below.
 * It is strongly recommended that you design a state machine to complete
 * this task, and practice drawing a state machine diagram before you
 * begin coding.
 *
 * On receipt of the character sequence:
 *   "foo" your programme should print '0' to the UART interface.
 *   "bar" your programme should print '1' to the UART interface.
 *   "foobar" your program should not print either '0' nor '1' as
 *   specified above, but should instead print a linefeed ('\n')
 *   character.
 *
 * Your solution should use a baud rate of 9600, and 8N1 frame format.
 * Your solution MUST NOT use qutyio.o or qutyserial.o.
 *
 * Examples:
 *
 *   Input:
 *     ...foo.bar.foo.barfoobarfood
 *   Output:
 *     0101
 *     0
 *
 *   Input:
 *     barsfoosbarforbarfoobarrforfoobarfoobarfood
 *   Output:
 *     1011
 *
 *
 *     0
 */
typedef enum

{
    START,
    F,
    FO,
    FOO,
    FOOB,
    FOOBA,
    FOOBAR,
    B,
    BA,
    BAR

} ch_state;

ch_state cur_char = START;
volatile char input;
int main(void)
{
    uart_init();
    while (1)
    {
        switch (cur_char)
        {
        case START:
            input = uart_getc();
            if (input == 'f')
            {
                cur_char = F;
            }
            else if (input == 'b')
            {
                cur_char = B;
            }

            break;

        case F:
            input = uart_getc();
            if (input == 'o')
            {
                cur_char = FO;
            }
            else if (input == 'b')
            {
                cur_char = B;
            }
            break;
        case FO:
            input = uart_getc();
            if (input == 'o')
            {
                cur_char = FOO;
            }
            else if (input == 'b')
            {
                cur_char = B;
            }
            break;
        case FOOB:
            input = uart_getc();
            if (input == 'a')
            {
                cur_char = FOOBA;
            }
            else if (input == 'b')
            {
                cur_char = B;
            }
            break;
        case FOOBA:
            input = uart_getc();
            if (input == 'r')
            {
                cur_char = FOOBAR;
            }
            else if (input == 'b')
            {
                cur_char = B;
            }
            break;

        case B:
            if (input == 'a')
            {
                cur_char = BA;
            }
            else if (input == 'f')
            {
                cur_char = F;
            }
            break;
        case BA:
            input = uart_getc();
            if (input == 'r')
            {
                cur_char = BAR;
            }
            else if (input == 'f')
            {
                cur_char = F;
            }
            break;
        case FOO:
            input = uart_getc();
            if (input == 'b')
            {
                cur_char = FOOB;
            }
            else
            {

                uart_putc('0');
                cur_char = START;
            }
            break;
        case BAR:
            uart_putc('1');
            cur_char = START;
            break;
        case FOOBAR:
            uart_putc('\n');
            cur_char = START;
            break;

        default:
            cur_char = START;
            break;
        }

    } // end while

} // end main()