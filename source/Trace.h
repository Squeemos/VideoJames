#pragma once

#include <string>

void trace_init();
void send_trace_message(const std::string& message);
void trace_shutdown();

