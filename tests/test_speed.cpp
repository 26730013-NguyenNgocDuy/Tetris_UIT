#include <iostream>
#include <cassert>
#include "DropSpeedController.h"

using namespace std;

void testInitialState() {
    DropSpeedController controller;
    assert(controller.getDropInterval() == 500);
    assert(controller.getTotalLinesCleared() == 0);
    assert(controller.getLevel() == 1);
    assert(controller.getScore() == 0);
    assert(controller.getComboStreak() == 0);
    cout << "[PASS] Test 1: Initial state verified (500ms, Level 1, Score 0, Combo 0)" << endl;
}

void testSingleLineClear() {
    DropSpeedController controller;
    controller.onLinesCleared(1);
    assert(controller.getTotalLinesCleared() == 1);
    assert(controller.getDropInterval() == 475); // 500 - 25
    assert(controller.getLevel() == 1);
    assert(controller.getScore() == 100);
    assert(controller.getComboStreak() == 1);
    cout << "[PASS] Test 2: Single line clear speed reduction verified (475ms, +100 pts)" << endl;
}

void testComboAndMultiLineClear() {
    DropSpeedController controller;
    controller.onLinesCleared(1); // combo 1
    assert(controller.getComboStreak() == 1);

    // Consecutive clear triggers combo bonus
    controller.onLinesCleared(4); // Tetris clear with combo 2
    assert(controller.getComboStreak() == 2);
    assert(controller.getTotalLinesCleared() == 5);
    assert(controller.getDropInterval() == 500 - (5 * 25)); // 375ms
    
    // Score: 100 (from 1st) + 800 (Tetris) + (combo 2 bonus: (2-1)*50*1) = 950
    assert(controller.getScore() == 950);
    cout << "[PASS] Test 3: Multi-line Tetris and combo streak bonus verified (375ms, Score 950)" << endl;
}

void testComboReset() {
    DropSpeedController controller;
    controller.onLinesCleared(2);
    assert(controller.getComboStreak() == 1);

    controller.resetCombo();
    assert(controller.getComboStreak() == 0);

    // Next clear starts fresh streak
    controller.onLinesCleared(1);
    assert(controller.getComboStreak() == 1);
    cout << "[PASS] Test 4: Combo streak reset verified" << endl;
}

void testMinimumIntervalBoundaryClamp() {
    DropSpeedController controller(500, 25, 80);
    // Clearing 30 lines: 500 - (30 * 25) = -250ms -> MUST clamp to 80ms
    controller.onLinesCleared(30);
    assert(controller.getTotalLinesCleared() == 30);
    assert(controller.getDropInterval() == 80);
    assert(controller.getLevel() == 4); // 1 + 30/10 = 4
    cout << "[PASS] Test 5: Minimum interval boundary clamp verified (Clamped safely at 80ms)" << endl;
}

void testResetFunctionality() {
    DropSpeedController controller;
    controller.onLinesCleared(15);
    controller.addDropScore(200);
    controller.reset();

    assert(controller.getDropInterval() == 500);
    assert(controller.getTotalLinesCleared() == 0);
    assert(controller.getScore() == 0);
    assert(controller.getLevel() == 1);
    assert(controller.getComboStreak() == 0);
    cout << "[PASS] Test 6: Game session reset back to initial values verified" << endl;
}

int main() {
    cout << "==================================================" << endl;
    cout << "  RUNNING DROPSPEEDCONTROLLER UNIT TESTS (SV5)    " << endl;
    cout << "==================================================" << endl;

    testInitialState();
    testSingleLineClear();
    testComboAndMultiLineClear();
    testComboReset();
    testMinimumIntervalBoundaryClamp();
    testResetFunctionality();

    cout << "==================================================" << endl;
    cout << "  ALL 6/6 UNIT TESTS PASSED SUCCESSFULLY! (100%)  " << endl;
    cout << "==================================================" << endl;
    return 0;
}
