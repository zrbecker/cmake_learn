#ifndef GAME_FRAME_COUNTER_H
#define GAME_FRAME_COUNTER_H

#include <string>
#include <vector>

class FrameCounter {
public:
  FrameCounter(const std::string& name);
  void report_frame(double seconds_passed);

private:
  std::string name_;
  double last_print_message_;
  double total_seconds_;
  std::vector<unsigned> frame_counts_;
};

#endif  // GAME_FRAME_COUNTER_H