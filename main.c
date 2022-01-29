#include <stdlib.h>
#include <stdio.h>
#include <pigpiod_if2.h>

static const uint32_t white = 4;
static const uint32_t red    = 17;
static const uint32_t green  = 27;
static const uint32_t blue   = 22;
static const uint32_t freq   = 1000;

int main(int argc,void *argv)
{
    int pi_handle = 0;
    uint32_t max_duty = 0;
     pi_handle = pigpio_start(NULL, NULL);
     if (pi_handle<0)
     {
         printf("Unable to connect to PIGPIOD\r\n");
         return 1;
     }
     printf("GPIO Init\r\n");
     set_PWM_frequency(pi_handle,white, freq);
     set_PWM_frequency(pi_handle,red, freq);
     set_PWM_frequency(pi_handle,blue, freq);
     set_PWM_frequency(pi_handle,green, freq);
     max_duty = get_PWM_real_range(pi_handle,white);
     set_PWM_dutycycle(pi_handle,white,50.0*max_duty/100.0);
     printf("Setting Freq to %dhz\r\n",freq);
     printf("Frequency set to %d\r\n",get_PWM_frequency(pi_handle,white));
     printf("Available Range: 0-%d\r\n",max_duty);


     // read gpio pins
     uint32_t pins = read_bank_1(pi_handle);
     
     // clear_bank_1(pi_handle,0x1);

     //set_bank_1(pi_handle,0x1);

pigpio_stop(pi_handle);
    return 0;
}