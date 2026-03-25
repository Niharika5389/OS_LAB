#include <stdio.h>

int main() {
    int logical_address;
    int page_size = 32;

    printf("Enter logical address (0 - 255): ");
    scanf("%d", &logical_address);

    int page_number = logical_address / page_size;
    int offset = logical_address % page_size;

    printf("\nLogical Address: %d\n", logical_address);
    printf("Page Number: %d\n", page_number);
    printf("Offset: %d\n", offset);

    return 0;
}