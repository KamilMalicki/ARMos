#define UART0DR *((volatile unsigned int *)0x101F1000)

void print_uart0(const char *str) {
    while (*str) {          
        UART0DR = *str;    
        str++;        
    }
}

void putchar_uart0(const char *chr) {        
    UART0DR = *chr;    
}

void putascii_uart0(const int num) {        
    UART0DR = num;    
}

void putnumber_uart0(int num) {
    if (num == 0) {
        UART0DR = '0';  
        return;
    }

    char buffer[10];
    int index = 0;
    
    if (num < 0) {
        UART0DR = '-';
        num = -num;
    }

    while (num > 0) {
        buffer[index++] = (num % 10) + '0';
        num /= 10;
    }

    for (int i = index - 1; i >= 0; i--) UART0DR = buffer[i];
}

void c_entry() {
    const char *hello_world = "Hello, world!\n";
    print_uart0(hello_world); 
    putchar_uart0("L");
    putascii_uart0(48);
    putchar_uart0("\n");
    putnumber_uart0(-524367 + 524367);
    //while (1);              
}
