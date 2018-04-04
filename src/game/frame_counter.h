#ifndef GAME_FRAME_COUNTER_H
#define GAME_FRAME_COUNTER_H

#include <string>
#include <vector>

class FrameCounter {
public:
  FrameCounter(
    double update_average_frequency_seconds = 1.0,
    unsigned moving_average_length = 5
  );
  void report_frame(double seconds_passed);

  double get_average_frames() const;

private:
  double update_average_frequency_seconds_;
  unsigned moving_average_length_;
  double last_average_update_;
  double total_seconds_;
  std::vector<unsigned> frame_counts_;
  double average_frames_;
};

#endif  // GAME_FRAME_COUNTER_H