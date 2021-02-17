#include "widget_button.hpp"

bool WButton::EventInside(int16_t x, int16_t y) const {
  log_d("%d < %d < %d; %d < %d < %d", 0, x, width_, 0, y, height_);
  return 0 <= x && x < width_ && 0 <= y && y < height_;
}

void WButton::Init() {
  Widget::Init();
  Label::Init();

  downCanvas_.createCanvas(width_, height_);
  downCanvas_.fillRect(0, 0, width_, height_, 15);
}

bool WButton::Draw() {
  if (view_dirty_) {
    if (last_event_ == EventType::TOUCH_DOWN) {
      downCanvas_.pushCanvas(x_offset_, y_offset_, UPDATE_MODE_DU);
    } else {
      canvas_->pushCanvas(x_offset_, y_offset_, UPDATE_MODE_DU);
    }
    view_dirty_ = false;
  }
  return view_dirty_;
}

void WButton::InternalEventHandler(TouchEvent evt) {

  if (last_event_ != evt.type) {
    last_event_ = evt.type;
    view_dirty_ = true;
  }
}