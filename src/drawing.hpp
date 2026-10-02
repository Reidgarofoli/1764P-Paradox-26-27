#pragma once
#include "variables.hpp"
#include "stb_image.h"
#include "lemlib/asset.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>

// Image cache: filename -> (pixels, width, height)
struct CachedImage {
    std::vector<uint32_t> pixels;  // ARGB8888 format
    int width;
    int height;
};
static std::unordered_map<std::string, CachedImage> imageCache;
static std::unordered_map<const uint8_t*, CachedImage> assetCache;

// Load image once and cache it
inline CachedImage* getCachedImage(const std::string& filename) {
    auto it = imageCache.find(filename);
    if (it != imageCache.end()) {
        return &it->second;
    }
    
    int srcWidth, srcHeight, channels;
    unsigned char *img = stbi_load(filename.c_str(), &srcWidth, &srcHeight, &channels, 4);
    if (!img) {
        printf("failed to open image: %s\n", filename.c_str());
        return nullptr;
    }
    
    // Convert to uint32_t ARGB format for fast access
    std::vector<uint32_t> pixels(srcWidth * srcHeight);
    for (int i = 0; i < srcWidth * srcHeight; i++) {
        unsigned char *px = img + (i * 4);
        pixels[i] = ((uint32_t)px[3] << 24) | ((uint32_t)px[0] << 16) | ((uint32_t)px[1] << 8) | px[2];
    }
    
    stbi_image_free(img);
    
    CachedImage &cached = imageCache[filename];
    cached.pixels = std::move(pixels);
    cached.width = srcWidth;
    cached.height = srcHeight;
    
    return &cached;
}

// Load asset image once and cache it
inline CachedImage* getCachedAsset(const asset& assetData) {
    auto it = assetCache.find(assetData.buf);
    if (it != assetCache.end()) {
        return &it->second;
    }
    
    int srcWidth, srcHeight, channels;
    unsigned char *img = stbi_load_from_memory(assetData.buf, (int)assetData.size, &srcWidth, &srcHeight, &channels, 4);
    if (!img) {
        printf("failed to load image from asset\n");
        return nullptr;
    }
    
    // Convert to uint32_t ARGB format for fast access
    std::vector<uint32_t> pixels(srcWidth * srcHeight);
    for (int i = 0; i < srcWidth * srcHeight; i++) {
        unsigned char *px = img + (i * 4);
        pixels[i] = ((uint32_t)px[3] << 24) | ((uint32_t)px[0] << 16) | ((uint32_t)px[1] << 8) | px[2];
    }
    
    stbi_image_free(img);
    
    CachedImage &cached = assetCache[assetData.buf];
    cached.pixels = std::move(pixels);
    cached.width = srcWidth;
    cached.height = srcHeight;
    
    return &cached;
}

// Fast batch drawing: accumulate same-color pixels into rectangles
inline void drawImage(const std::string& filename, int xOffset, int yOffset, int drawWidth, int drawHeight) {
    CachedImage* cached = getCachedImage(filename);
    if (!cached) return;
    
    float scaleX = (float)cached->width / drawWidth;
    float scaleY = (float)cached->height / drawHeight;
    
    // Batch consecutive pixels of same color
    for (int y = 0; y < drawHeight; y++) {
        int srcY = (int)(y * scaleY);
        int rowIdx = srcY * cached->width;
        
        for (int x = 0; x < drawWidth; ) {
            int srcX = (int)(x * scaleX);
            uint32_t pixelARGB = cached->pixels[rowIdx + srcX];
            
            // Skip transparent pixels
            if ((pixelARGB >> 24) == 0) {
                x++;
                continue;
            }
            
            // Extract RGB and set pen once
            uint32_t color = pixelARGB & 0xFFFFFF;
            pros::screen::set_pen(color);
            
            // Draw horizontal run of same color
            int runStart = x;
            int runEnd = x + 1;
            while (runEnd < drawWidth) {
                int nextSrcX = (int)(runEnd * scaleX);
                uint32_t nextPixel = cached->pixels[rowIdx + nextSrcX];
                if ((nextPixel >> 24) == 0 || (nextPixel & 0xFFFFFF) != color) break;
                runEnd++;
            }
            
            // Draw the run as a horizontal line (batch operation)
            if (runEnd - runStart > 1) {
                pros::screen::fill_rect(xOffset + runStart, yOffset + y, 
                                       xOffset + runEnd, yOffset + y + 1);
            } else {
                pros::screen::draw_pixel(xOffset + x, yOffset + y);
            }
            
            x = runEnd;
        }
    }
}



inline void drawAsset(const asset& assetData, int xOffset, int yOffset, int drawWidth, int drawHeight) {
    CachedImage* cached = getCachedAsset(assetData);
    if (!cached) return;
    
    float scaleX = (float)cached->width / drawWidth;
    float scaleY = (float)cached->height / drawHeight;
    
    // Batch consecutive pixels of same color
    for (int y = 0; y < drawHeight; y++) {
        int srcY = (int)(y * scaleY);
        int rowIdx = srcY * cached->width;
        
        for (int x = 0; x < drawWidth; ) {
            int srcX = (int)(x * scaleX);
            uint32_t pixelARGB = cached->pixels[rowIdx + srcX];
            
            // Skip transparent pixels
            if ((pixelARGB >> 24) == 0) {
                x++;
                continue;
            }
            
            // Extract RGB and set pen once
            uint32_t color = pixelARGB & 0xFFFFFF;
            pros::screen::set_pen(color);
            
            // Draw horizontal run of same color
            int runStart = x;
            int runEnd = x + 1;
            while (runEnd < drawWidth) {
                int nextSrcX = (int)(runEnd * scaleX);
                uint32_t nextPixel = cached->pixels[rowIdx + nextSrcX];
                if ((nextPixel >> 24) == 0 || (nextPixel & 0xFFFFFF) != color) break;
                runEnd++;
            }
            
            // Draw the run as a horizontal line (batch operation)
            if (runEnd - runStart > 1) {
                pros::screen::fill_rect(xOffset + runStart, yOffset + y, 
                                       xOffset + runEnd, yOffset + y + 1);
            } else {
                pros::screen::draw_pixel(xOffset + x, yOffset + y);
            }
            
            x = runEnd;
        }
    }
}

inline void drawAssetIgnoreColor(const asset& assetData, int xOffset, int yOffset, int drawWidth, int drawHeight, int colorToIgnore) {
    CachedImage* cached = getCachedAsset(assetData);
    if (!cached) return;
    
    float scaleX = (float)cached->width / drawWidth;
    float scaleY = (float)cached->height / drawHeight;
    uint32_t ignoreARGB = colorToIgnore | 0xFF000000;  // Add opaque alpha
    
    for (int y = 0; y < drawHeight; y++) {
        int srcY = (int)(y * scaleY);
        int rowIdx = srcY * cached->width;
        
        for (int x = 0; x < drawWidth; ) {
            int srcX = (int)(x * scaleX);
            uint32_t pixelARGB = cached->pixels[rowIdx + srcX];
            
            // Skip transparent or ignored color pixels
            if ((pixelARGB >> 24) == 0 || (pixelARGB & 0xFFFFFF) == (ignoreARGB & 0xFFFFFF)) {
                x++;
                continue;
            }
            
            uint32_t color = pixelARGB & 0xFFFFFF;
            pros::screen::set_pen(color);
            
            // Batch horizontal runs
            int runStart = x;
            int runEnd = x + 1;
            while (runEnd < drawWidth) {
                int nextSrcX = (int)(runEnd * scaleX);
                uint32_t nextPixel = cached->pixels[rowIdx + nextSrcX];
                if ((nextPixel >> 24) == 0 || (nextPixel & 0xFFFFFF) == (ignoreARGB & 0xFFFFFF) ||
                    (nextPixel & 0xFFFFFF) != color) break;
                runEnd++;
            }
            
            if (runEnd - runStart > 1) {
                pros::screen::fill_rect(xOffset + runStart, yOffset + y,
                                       xOffset + runEnd, yOffset + y + 1);
            } else {
                pros::screen::draw_pixel(xOffset + x, yOffset + y);
            }
            
            x = runEnd;
        }
    }
}

inline void drawRoundedRect(int x, int y, int width, int height, int radius){
    pros::screen::fill_circle(x + radius, y + radius, radius);
    pros::screen::fill_circle(x + radius, y + height - radius, radius);
    pros::screen::fill_circle(x + width - radius, y + radius, radius);
    pros::screen::fill_circle(x + width - radius, y + height - radius, radius);
    pros::screen::fill_rect(x + radius, y, x + width - radius, y + height);
    pros::screen::fill_rect(x, y + radius, x + width, y + height - radius);
}

inline bool getPressed(pros::screen_touch_status_s_t status, int x, int y, int width, int height){
    return (status.x > x && status.y > y && status.x < x + width && status.y < y + height);
}

// Scrollable list structure to track state
struct ScrollableList {
    int scrollOffset = 0;  // pixels scrolled from top
    int selectedIndex = 0;  // currently selected item index
};

// Draw a scrollable list of items
// Parameters:
//   list: ScrollableList state (scrollOffset and selectedIndex)
//   items: vector of item labels to display
//   x, y: top-left position of list
//   width, height: dimensions of list viewport
//   itemHeight: height of each item in pixels
//   textFormat: text size/format to use
//   textColor: color for normal text
//   selectedColor: color for selected item background
//   backgroundColor: background color of list
inline void drawScrollableList(
    ScrollableList& list,
    const std::vector<std::string>& items,
    int x, int y, int width, int height,
    int itemHeight,
    pros::text_format_e_t textFormat,
    uint32_t textColor,
    uint32_t selectedColor,
    uint32_t backgroundColor
) {
    if (items.empty()) return;
    
    // Draw background
    pros::screen::set_pen(backgroundColor);
    pros::screen::fill_rect(x, y, x + width, y + height);
    
    // Calculate visible items
    int maxVisibleItems = height / itemHeight;
    int firstVisibleItem = list.scrollOffset / itemHeight;
    int lastVisibleItem = std::min((int)items.size() - 1, firstVisibleItem + maxVisibleItems);
    
    // Clamp selection to valid range
    if (list.selectedIndex >= (int)items.size()) {
        list.selectedIndex = items.size() - 1;
    }
    // if (list.selectedIndex < 0) {
    //     list.selectedIndex = 0;
    // }
    
    // Draw visible items (skip items fully above or below viewport)
    for (int i = firstVisibleItem; i <= lastVisibleItem; i++) {
        int itemY = y + (i - firstVisibleItem) * itemHeight - (list.scrollOffset % itemHeight);

        // Skip items that are completely above the viewport
        if (itemY < y) continue;
        // Stop if item is completely below the viewport
        if (itemY + itemHeight > y + height) break;

        // Draw selection highlight
        if (i == list.selectedIndex) {
            pros::screen::set_pen(selectedColor);
            pros::screen::fill_rect(x, itemY, x + width, itemY + itemHeight);
            pros::screen::set_eraser(selectedColor);
        } else {
            pros::screen::set_eraser(backgroundColor);
        } 

        // Draw item text
        pros::screen::set_pen(textColor);

        int textX = x + 5;  // 5px padding
        int textY = itemY + 5;  // 5px padding

        pros::screen::print(textFormat, textX, textY, items[i].c_str());
    }
    
    // Draw border
    pros::screen::set_pen(0x404040);
    pros::screen::draw_rect(x, y, x + width, y + height);
    
    // Draw scrollbar if needed
    if ((int)items.size() * itemHeight > height) {
        int scrollbarWidth = 8;
        int scrollbarX = x + width - scrollbarWidth;
        int scrollbarHeight = (height * height) / (items.size() * itemHeight);
        int scrollbarY = y + (list.scrollOffset * height) / (items.size() * itemHeight);
        
        pros::screen::set_pen(0x808080);
        pros::screen::fill_rect(scrollbarX, scrollbarY, scrollbarX + scrollbarWidth, scrollbarY + scrollbarHeight);
    }
}

// Handle scrolling input for a list
// Returns true if the list state changed
inline bool handleListScroll(
    ScrollableList& list,
    const std::vector<std::string>& items,
    int x, int y, int width, int height,
    int itemHeight,
    pros::screen_touch_status_s_t status
) {
    if (!getPressed(status, x, y, width, height)) {
        return false;
    }
    if (items.empty()) return false;
    
    int maxVisibleItems = height / itemHeight;
    int maxScroll = std::max(0, (int)items.size() * itemHeight - height);
    
    // Check if touch is within list bounds
    
    bool changed = false;
    static int lastY = 0;
    
    if (status.touch_status == pros::last_touch_e_t::E_TOUCH_PRESSED) {
        // Calculate which item was tapped
        int relativeY = status.y - y + list.scrollOffset;
        int tappedIndex = relativeY / itemHeight;
        
        if (tappedIndex >= 0 && tappedIndex < (int)items.size()) {
            list.selectedIndex = tappedIndex;
            changed = true;
        }

        lastY = 0;
    } else if (status.touch_status == pros::last_touch_e_t::E_TOUCH_HELD) {
        // Vertical scroll: adjust offset based on drag
        // For now, implement simple scroll on hold (can enhance with velocity)
        static int lastTouchTime = 0;
        
        if (lastY != 0) {
            int delta = lastY - status.y;  // positive = scroll down
            list.scrollOffset += delta;
            
            // Clamp scroll offset
            if (list.scrollOffset < 0) list.scrollOffset = 0;
            if (list.scrollOffset > maxScroll) list.scrollOffset = maxScroll;
            
            changed = true;
        }
        lastY = status.y;
    } else if (status.touch_status == pros::last_touch_e_t::E_TOUCH_RELEASED) {
        // Reset tracking
        lastY = 0;
    }
    
    return changed;
}