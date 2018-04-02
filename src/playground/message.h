#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

static_assert(1 == 1, "One is equal to one");
static_assert(1 != 2);

#define PREPEND "test> "

void print_message(const std::string& message);

#endif  // MESSAGE_H