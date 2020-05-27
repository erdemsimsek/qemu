#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#define MAX_BUF 1024
#define pipename "\\\\.\\pipe\\qemu"

void delay(int milliseconds);

int main()
{
    HANDLE pipe = CreateFile(pipename, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

    if (pipe == INVALID_HANDLE_VALUE)
    {
        printf("Error: %d", GetLastError());
    }

    delay(500);

    DWORD numWritten;
    DWORD numRead;
    char data[4] = {105,106,107,108};
    char data2[4];
    char a = 108;
    int index = 0;
#if 1
    for(index = 0; index < 4; index++){
        if(WriteFile(pipe, &data[index], 1, &numWritten, NULL)){
            printf("TX Success\n");
        }
        else{
            printf("TX Error %d\n", GetLastError());
        }
        delay(500);
    }

    while(1){
        if(ReadFile(pipe, data2, 1, &numRead, NULL)){
            printf("%s\n", data2);
            memset(data2, 0, sizeof(data2));
        }
        else{
            printf("RX Error %d\n", GetLastError());
        }

        delay(500);
    }
#else
    if(WriteFile(pipe, &a, 1, &numWritten, NULL)){
        printf("TX Success\n");
    }
    else{
        printf("TX Error %d\n", GetLastError());
    }

    while(1){
        if(ReadFile(pipe, data2, 1, &numRead, NULL)){
            printf("%s\n", data2);
            memset(data2, 0, sizeof(data2));
        }
        else{
            printf("RX Error\n %d\n", GetLastError());
        }

        delay(500);
    }
#endif



//    DWORD numWritten;
//
//    WriteFile(pipe, message, 3, &numWritten, NULL);

    return 0;
}

void delay(int milliseconds)
{
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}