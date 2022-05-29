#include "Frame.h"
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <iostream>
#include <sys/select.h>
#include <unistd.h>

namespace Tear {
    Frame::Frame() {
		open = 0 < ::pipe(descriptor.data());
    }

    Frame::~Frame() {
    }

    void FrameBuffer::recreate(int newWidth, int newHeight) {
        width = newWidth;
        height = newHeight;
        pixels.resize(width * height);
    }

    void FrameBuffer::set(int x, int y, const Pixel& cell) {
        pixels[y * width + x] = cell;
    }

    const Pixel& FrameBuffer::get(int x, int y) const {
        return pixels[y * width + x];
    }

    Pixel& FrameBuffer::get(int x, int y) {
        return pixels[y * width + x];
    }
}