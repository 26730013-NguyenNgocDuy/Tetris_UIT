#ifndef DROP_SPEED_CONTROLLER_H
#define DROP_SPEED_CONTROLLER_H

/**
 * @brief DropSpeedController - Manages Tetris block falling speed (SV5 scope)
 * 
 * Responsibilities:
 * - Stores initial, current, and minimum drop intervals (ms).
 * - Decreases drop interval whenever completed lines are cleared.
 * - Prevents falling speed from exceeding the safe minimum threshold.
 * - Tracks score, level, and lines cleared for HUD display.
 */
class DropSpeedController {
private:
    int initialInterval;
    int currentInterval;
    int minimumInterval;
    int speedStep;
    int totalLinesCleared;
    int score;
    int level;

public:
    /**
     * @param initialMs Starting drop interval in milliseconds (default: 500ms)
     * @param stepMs    Interval decrease per line cleared (default: 25ms)
     * @param minMs     Cap to prevent game from running impossibly fast (default: 80ms)
     */
    DropSpeedController(int initialMs = 500, int stepMs = 25, int minMs = 80)
        : initialInterval(initialMs),
          currentInterval(initialMs),
          minimumInterval(minMs),
          speedStep(stepMs),
          totalLinesCleared(0),
          score(0),
          level(1) {}

    /**
     * @brief Call when one or more lines have been successfully cleared.
     * @param count Number of cleared lines
     */
    void onLinesCleared(int count) {
        if (count <= 0) return;

        totalLinesCleared += count;
        
        // Classic Tetris scoring formula scaled with level
        int baseScore = 0;
        switch (count) {
            case 1: baseScore = 100; break;
            case 2: baseScore = 300; break;
            case 3: baseScore = 500; break;
            case 4: baseScore = 800; break; // Tetris!
            default: baseScore = count * 200; break;
        }
        score += baseScore * level;

        // Level up every 10 lines
        level = 1 + (totalLinesCleared / 10);

        // Accelerate fall speed
        currentInterval = initialInterval - (totalLinesCleared * speedStep);
        if (currentInterval < minimumInterval) {
            currentInterval = minimumInterval;
        }
    }

    /**
     * @brief Bonus score for soft dropping / hard dropping
     */
    void addDropScore(int points) {
        if (points > 0) score += points;
    }

    int getDropInterval() const {
        return currentInterval;
    }

    int getTotalLinesCleared() const {
        return totalLinesCleared;
    }

    int getScore() const {
        return score;
    }

    int getLevel() const {
        return level;
    }

    void reset() {
        currentInterval = initialInterval;
        totalLinesCleared = 0;
        score = 0;
        level = 1;
    }
};

#endif // DROP_SPEED_CONTROLLER_H
