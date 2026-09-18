#ifndef DROP_SPEED_CONTROLLER_H
#define DROP_SPEED_CONTROLLER_H

/**
 * @brief DropSpeedController - Manages Tetris block falling speed (SV5 scope)
 * 
 * Responsibilities:
 * - Stores initial, current, and minimum drop intervals (ms).
 * - Decreases drop interval whenever completed lines are cleared.
 * - Prevents falling speed from exceeding the safe minimum threshold.
 */
class DropSpeedController {
private:
    int initialInterval;
    int currentInterval;
    int minimumInterval;
    int speedStep;
    int totalLinesCleared;

public:
    /**
     * @param initialMs Starting drop interval in milliseconds (default: 500ms)
     * @param stepMs    Interval decrease per line cleared (default: 30ms)
     * @param minMs     Cap to prevent game from running impossibly fast (default: 100ms)
     */
    DropSpeedController(int initialMs = 500, int stepMs = 30, int minMs = 100)
        : initialInterval(initialMs),
          currentInterval(initialMs),
          minimumInterval(minMs),
          speedStep(stepMs),
          totalLinesCleared(0) {}

    /**
     * @brief Call when one or more lines have been successfully cleared.
     * @param count Number of cleared lines
     */
    void onLinesCleared(int count) {
        if (count <= 0) return;

        totalLinesCleared += count;
        currentInterval -= count * speedStep;

        if (currentInterval < minimumInterval) {
            currentInterval = minimumInterval;
        }
    }

    /**
     * @return Current drop interval in milliseconds for the game loop delay.
     */
    int getDropInterval() const {
        return currentInterval;
    }

    /**
     * @return Total number of lines cleared so far.
     */
    int getTotalLinesCleared() const {
        return totalLinesCleared;
    }

    int getInitialInterval() const {
        return initialInterval;
    }

    int getMinimumInterval() const {
        return minimumInterval;
    }

    int getSpeedStep() const {
        return speedStep;
    }

    /**
     * @brief Reset speed back to initial values (e.g. For a new game session).
     */
    void reset() {
        currentInterval = initialInterval;
        totalLinesCleared = 0;
    }
};

#endif // DROP_SPEED_CONTROLLER_H
