#ifndef GAME_FRAME_COUNTER_H
#define GAME_FRAME_COUNTER_H

#include <string>
#include <vector>

class FrameCounter {
public:
  FrameCounter(
    const std::string& name,
    double print_frequency_seconds = 1.0,
    unsigned print_moving_average_length = 5
  );
  void report_frame(double seconds_passed);

  double get_average_frames() const;

private:
  std::string name_;
  double print_frequency_seconds_;
  unsigned print_moving_average_length_;
  double last_print_message_;
  double total_seconds_;
  std::vector<unsigned> frame_counts_;
  double average_frames_;
};

#endif  // GAME_FRAME_COUNTER_H