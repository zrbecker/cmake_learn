#include "frame_counter.h"

#include <iostream>

namespace game {
namespace engine {

FrameCounter::FrameCounter(
    double update_average_frequency_seconds,
    unsigned moving_average_length)
  : update_average_frequency_seconds_(update_average_frequency_seconds),
    moving_average_length_(moving_average_length),
    last_average_update_(0),
    total_seconds_(0),
    frame_counts_(),
    average_frames_(0) {}

void FrameCounter::report_frame(double seconds_passed) {
  if (frame_counts_.size() == 0 ||
      int(total_seconds_ + seconds_passed) - int(total_seconds_) >= 1) {
    frame_counts_.push_back(0);
  }
  total_seconds_ += seconds_passed;
  frame_counts_.back() += 1;

  double next_update = last_average_update_ + update_average_frequency_seconds_;
  if (total_seconds_ > next_update && frame_counts_.size() > 1) {
    while (frame_counts_.size() > moving_average_length_ + 1) {
      frame_counts_.erase(frame_counts_. begin());
    }
    int total_frames = 0;
    for (int i = 0; i < frame_counts_.size() - 1; ++i) {
      total_frames += frame_counts_[i];
    }
    average_frames_ = double(total_frames) / (frame_counts_.size() - 1);
    last_average_update_ = total_seconds_;
  }
}

double FrameCounter::get_average_frames() const {
  return average_frames_;
}
  
}  // namespace engine
}  // namespace game
