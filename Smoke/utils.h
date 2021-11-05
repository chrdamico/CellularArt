#include <thread>
#include <draw.h>
#include <rules.h>

void updateBoard(Board* boardPtr);
// Updates the whole board by using two threads for bottom and top half
