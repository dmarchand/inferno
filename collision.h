#ifndef COLLISION_H
#define COLLISION_H

// Simple utility function that takes two rectangles and sees if they intersect
bool doRectanglesCollide(int x1, int y1, int xEnd1, int yEnd1, int x2, int y2, int xEnd2, int yEnd2) {
    if (x1 < xEnd2 && xEnd1 > x2 &&
        y1 < yEnd2 && yEnd1 > y2) {
        return true;
    }
    return false;
}

#endif

