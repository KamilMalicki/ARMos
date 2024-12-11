#define UART0DR *((volatile unsigned int *)0x101F1000)

void print_uart0(const char *str) {
    while (*str) {          
        UART0DR = *str;    
        str++;        
    }
}

void c_entry() {
    const char *hello_world = "Hello, world!\n";
    print_uart0(hello_world); 
    while (1);              
}
