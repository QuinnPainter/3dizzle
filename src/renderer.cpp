#include <algorithm>
#include "renderer.hpp"

screenTri screenTris[] = {{{200, 30, 0}, {600, 600, 0}, {30, 400, 0}}};

void setPixel(u8* screenData, int x, int y, u8 r, u8 g, u8 b) {
    if (x > 0 && x < XResolution && y > 0 && y < YResolution) {
        screenData[(y * XResolution * 3) + (x * 3)] = r;
        screenData[(y * XResolution * 3) + (x * 3) + 1] = g;
        screenData[(y * XResolution * 3) + (x * 3) + 2] = b;
    }
}

bool xbounce = false;
bool ybounce = false;
void renderFrame(u8* screenData) {
    if (xbounce) {
        screenTris[0].p3.x++;
        if (screenTris[0].p3.x > XResolution) {xbounce = !xbounce;}
    } else {
        screenTris[0].p3.x--;
        if (screenTris[0].p3.x <= 0) {xbounce = !xbounce;}
    }
    if (ybounce) {
        screenTris[0].p1.y++;
        if (screenTris[0].p1.y > YResolution) {ybounce = !ybounce;}
    } else {
        screenTris[0].p1.y--;
        if (screenTris[0].p1.y <= 0) {ybounce = !ybounce;}
    }

    for (screenTri tri : screenTris) {
        setPixel(screenData, tri.p1.x, tri.p1.y, 0xFF, 0xFF, 0);
        setPixel(screenData, tri.p2.x, tri.p2.y, 0xFF, 0xFF, 0xFF);
        setPixel(screenData, tri.p3.x, tri.p3.y, 0xFF, 0, 0xFF);

        // sort p1 to p3 by ascending Y
        if (tri.p1.y > tri.p2.y) { std::swap(tri.p1, tri.p2); }
        if (tri.p1.y > tri.p3.y) { std::swap(tri.p1, tri.p3); }
        if (tri.p2.y > tri.p3.y) { std::swap(tri.p2, tri.p3); }

        float line1Slope = (float)(tri.p3.x - tri.p1.x) / (tri.p3.y - tri.p1.y);
        
        float line1X = tri.p1.x;
        if (tri.p2.y != tri.p1.y) {
            float line2Slope = (float)(tri.p2.x - tri.p1.x) / (tri.p2.y - tri.p1.y);
            float line2X = tri.p1.x;
            for (int y = tri.p1.y; y <= tri.p2.y; y++) {
                if (line1X < line2X) {
                    for (int x = line1X; x < line2X; x++) {
                        setPixel(screenData, x, y, 0x7F, 0xFF, 0);
                    }
                } else {
                    for (int x = line2X; x < line1X; x++) {
                        setPixel(screenData, x, y, 0x7F, 0xFF, 0);
                    }
                }
                line1X += line1Slope;
                line2X += line2Slope;
            }
        }

        if (tri.p3.y != tri.p2.y) {
            float line3Slope = (float)(tri.p3.x - tri.p2.x) / (tri.p3.y - tri.p2.y);
            float line3X = tri.p2.x;
            for (int y = tri.p2.y; y <= tri.p3.y; y++) {
                if (line1X < line3X) {
                    for (int x = line1X; x < line3X; x++) {
                        setPixel(screenData, x, y, 0x7F, 0xFF, 0);
                    }
                } else {
                    for (int x = line3X; x < line1X; x++) {
                        setPixel(screenData, x, y, 0x7F, 0xFF, 0);
                    }
                }
                line1X += line1Slope;
                line3X += line3Slope;
            }
        }
    }
}
