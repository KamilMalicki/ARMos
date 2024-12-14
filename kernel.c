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

    while (num > 0) {
        buffer[index++] = (num % 10) + '0';
        num /= 10;
    }

    for (int i = index - 1; i >= 0; i--) {
        UART0DR = buffer[i];
    }
}

#define UART0FR *((volatile unsigned int *)0x101F1018)

char getchar_uart0(int mode) {
    while (UART0FR & (1 << 4));
    char received_char = (char)UART0DR;
    if (mode == 1) {
        UART0DR = received_char;
    }
    return received_char;
}

void getstr_uart0(char *buffer, int max_length, int mode) {
    int index = 0;

    while (index < max_length - 1) {
        char received_char = getchar_uart0(0);

        if (received_char == '\n' || received_char == '\r') {
            break;
        }

        if (received_char == '\b' || received_char == 127) {
            if (index > 0) {
                index--;
                if (mode == 1) {
                    UART0DR = '\b'; 
                    UART0DR = ' ';  
                    UART0DR = '\b';  
                }
            }
        } else {
            buffer[index++] = received_char;
            if (mode == 1) {
                UART0DR = received_char;
            }
        }
    }

    buffer[index] = '\0';
}

int char_to_int(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    return -1;
}

int str_to_int(const char *str) {
    int result = 0;

    while (*str >= '0' && *str <= '9') {
        result = result * 10 + char_to_int(*str);
        str++;
    }

    return result;
}

void c_entry() {
    char *reg = "400";
    int var = str_to_int(reg);
    putnumber_uart0(var);
    //const char *hello_world = "Hello, world!\n";
    //print_uart0(hello_world);
    //char buffer[100];
    //print_uart0("wpisz:\n");
    //getstr_uart0(buffer, sizeof(buffer),1); 
    //print_uart0("dales: ");
    //print_uart0(buffer); 
    //print_uart0("\n");
    //putchar_uart0("L");
    //putascii_uart0(48);
    //putchar_uart0("\n");
    //putnumber_uart0(-524367 + 524367);
    //while (1);              
}
