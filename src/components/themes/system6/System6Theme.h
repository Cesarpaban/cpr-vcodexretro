#pragma once

#include <functional>
#include <string>
#include <vector>

#include "components/themes/BaseTheme.h"

// RetroInk-style "System 6" theme, ported from RetroInk (AltFlow, MIT) to
// CPR-vCodex. Monochrome striped window bars, square controls, a checkerboard
// desktop and floating keycap button hints, all drawn as geometry directly into
// the existing one-bit framebuffer (no extra bitmaps or buffers).
namespace System6Metrics {
constexpr int titleBarHeight = 40;
constexpr ThemeMetrics makeValues() {
  auto v = BaseMetrics::values;
  v.batteryBarHeight = 0;
  v.headerHeight = 50;
  v.headerUnderlineSize = 2;
  v.homeTopPadding = 50;
  v.homeCoverHeight = 180;
  v.homeCoverTileHeight = 210;
  v.homeRecentBooksCount = 1;
  v.menuRowHeight = 44;
  v.menuSpacing = 6;
  v.listInset = 12;
  v.listSidePadding = 12;
  v.listScrollWidth = 8;
  v.listRowRadius = 0;
  v.listSelectionStyle = 0;  // inverted row, like a selected Finder item
  v.popupFrameThickness = 3;
  v.popupCornerRadius = 0;
  v.keyboardKeySpacing = 3;
  v.keyboardCenteredText = true;
  return v;
}
constexpr ThemeMetrics values = makeValues();
}  // namespace System6Metrics

// No state, image assets, or extra framebuffer. Decoration is drawn in place.
class System6Theme final : public BaseTheme {
 public:
  void drawHeader(const GfxRenderer& renderer, Rect rect, const char* title, const char* subtitle = nullptr,
                  bool backButton = true) const override;
  void drawButtonHints(GfxRenderer& renderer, const char* btn1, const char* btn2, const char* btn3,
                       const char* btn4) const override;
  void drawButtonMenu(GfxRenderer& renderer, Rect rect, int buttonCount, int selectedIndex,
                      const std::function<std::string(int index)>& buttonLabel,
                      const std::function<UIIcon(int index)>& rowIcon,
                      const std::function<std::string(int index)>& buttonSubtitle = nullptr,
                      const std::function<bool(int index)>& showAccessory = nullptr) const override;
  void drawProgressBar(const GfxRenderer& renderer, Rect rect, size_t current, size_t total) const override;
  Rect drawPopup(const GfxRenderer& renderer, const char* message) const override;
  void fillPopupProgress(const GfxRenderer& renderer, const Rect& layout, int progress) const override;
  void drawRecentBookCover(GfxRenderer& renderer, Rect rect, const std::vector<RecentBook>& recentBooks,
                           int selectorIndex, bool& coverRendered, bool& coverBufferStored, bool& bufferRestored,
                           std::function<bool()> storeCoverBuffer) const override;
};
static_assert(sizeof(System6Theme) == sizeof(BaseTheme), "Theme must not add resident state");

// Cold-boot splash for the System 6 theme: desktop checker, a titled window and
// a code-drawn Macintosh mark. Drawn into the existing framebuffer (no bitmap);
// the caller clears the screen first and flushes afterwards.
void drawSystem6BootSplash(const GfxRenderer& renderer, const char* productName, const char* statusLine,
                           const char* versionLine);
