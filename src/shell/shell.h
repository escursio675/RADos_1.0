#pragma once

void shell_init(void* addr);
void shell_input(char c);
void shell_execute(const char* cmd);