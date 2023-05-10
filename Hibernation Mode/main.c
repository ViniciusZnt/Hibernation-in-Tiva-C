#include <stdint.h>
#include <stdbool.h>
#include "C:\ti\TivaWare_C_Series-2.2.0.295\utils\ustdlib.h"
#include "C:\ti\TivaWare_C_Series-2.2.0.295\inc\hw_types.h"
#include "C:\ti\TivaWare_C_Series-2.2.0.295\inc\hw_memmap.h"
#include "C:\ti\TivaWare_C_Series-2.2.0.295\driverlib\sysctl.h"
#include "C:\ti\TivaWare_C_Series-2.2.0.295\driverlib\pin_map.h"
#include "C:\ti\TivaWare_C_Series-2.2.0.295\driverlib\debug.h"
#include "C:\ti\TivaWare_C_Series-2.2.0.295\driverlib\hibernate.h"
#include "C:\ti\TivaWare_C_Series-2.2.0.295\driverlib\gpio.h"


int main(void){
    //Clock Setup
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    //GPIO Configuration
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    //LED pin 1 = RED, pin 2 = BLUE, pin 3 = GREEN
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x08);

    //Hibernate Configuration
    SysCtlPeripheralEnable(SYSCTL_PERIPH_HIBERNATE); //Enable Hibernation Mode
    HibernateEnableExpClk(SysCtlClockGet()); //Clock Hibernation Setup
    HibernateGPIORetentionEnable(); //Enable GPIO pin state during hibernation and remain active even in hibernation
    SysCtlDelay(64000000);
    HibernateWakeSet(HIBERNATE_WAKE_PIN); //Wake from Hibernation
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3, 0x00); //Turn off the green LED before goes to sleep

    //Hibernate Request, the function request to disable the external regulator, removing power from the processors and peripherals
    HibernateRequest();
    while(1)
    {
    }
}
