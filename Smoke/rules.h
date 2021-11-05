#include <draw.h>


void applyRule(Board* boardPtr, int i, int j);
// specific rule that updates tile (i,j) while looking at local tiles nearby

void modifyStartingBoard(Board* boardPtr);
// Function that modifies the initial position

void checkRedRule(Board* boardPtr, int i, int j);
void checkBlueRule(Board* boardPtr, int i, int j);
void checkGreenRule(Board* boardPtr, int i, int j);
void checkPurpleRule(Board* boardPtr, int i, int j);
// Rules for various tile colors
