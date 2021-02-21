#include "home_screen.hpp"
#include "image_resources.h"

HomeScreen::HomeScreen(int16_t x, int16_t y, int16_t w, int16_t h) : Frame() {
  x_ = x;
  y_ = y;
  width_ = w;
  height_ = h;
  update_mode_ = UPDATE_MODE_GC16;
  name_ = "HomeScreen";
}

void HomeScreen::CreateAppButton(int16_t x, int16_t y, const std::string &name,
                                 const uint8_t *icon,
                                 WButton::handler_fun_t fun) {
  auto button = WIconButton::Create(x, y, 116, 116, icon, 96, 96);
  button->Style(WidgetStyle::BORDER);
  button->SetBorderStyle(BorderStyle::ROUND);
  button->BorderColor(Grayscale::GS_BLACK);
  button->RegisterHandler(fun);
  button->Name(name);
  button->Padding(10);
  button->BorderWidth(3);
  button->SetBorderRadius(10);
  AddWidget(button);

  auto paint_label = Label::Create(x, y + 116 + 10, 116, 20, name);
  paint_label->HAlign(Label::MIDDLE);
  paint_label->Name(name);
  AddWidget(paint_label);
}

void HomeScreen::Prepare(WidgetContext *ctx) {
  auto home_dim = dimension();

  CreateAppButton(
      30, 30, "Paint", PAINTBRUSH_96_96, [home_dim, ctx](TouchEvent e) {
        if (e.type != EventType::TOUCH_UP)
          return;
        ctx->PopFrame();
        // Create the paint frame
        auto pf = Frame::Create(home_dim.x, home_dim.y, home_dim.w, home_dim.h);
        pf->UpdateMode(UPDATE_MODE_GC16);
        auto wpaint = Paint::Create(0, 0, home_dim.w, home_dim.h);
        wpaint->Style(WidgetStyle::BORDER);
        wpaint->BorderColor(Grayscale::G15);
        pf->AddWidget(wpaint);
        ctx->AddFrame(pf);
      });

  CreateAppButton(30 + 116 + 50, 30, "Settings", SETTINGS_96_96,
                  [](TouchEvent e) {});

  CreateAppButton(30 + 2 * (116 + 50), 30, "Settings", SETTINGS_96_96,
                  [](TouchEvent e) {});
}

void HomeScreen::Init(WidgetContext *ctx) {
  // The buttons need to be added before the frame is intialized.
  if (!hs_initialized_) {
    Prepare(ctx);
    hs_initialized_ = true;
  }
  Frame::Init(ctx);
}