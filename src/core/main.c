#include "configuration.h"

int main() {
    if (!loadConfiguration())
        return -1;


    return 0;
}